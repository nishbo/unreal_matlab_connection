// Fill out your copyright notice in the Description page of Project Settings.
/*
    Written by Anton Sobinov
    Based on the code by Emo Todorov

    Copyright (C) 2017 Roboti LLC
    Copyright (C) 2018 Anton Sobinov

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "SaSocketApi.h"

//------------------------- static global variables -------------------------------------

static SaSocket soc;						// socket object

static const int BUFSZ = 100000;			// buffer size
static char buffer[BUFSZ + 8];				// preallocated buffer (plus 2-int header)
static int* cmd = (int*)buffer;				// command field
static int* size = ((int*)buffer) + 1;		// size field
static int* data = ((int*)buffer) + 2;		// first data field

static int lastError = 0;					// result from last operation

static char stringbuffer2[BUFSZ];


//------------------------- static utility functions ----------------------------

int globalNIn = 0;
float globalDataIn[BUFSZ];

int globalNOut = 0;
float globalDataOut[BUFSZ];
// float** globalDataOutP = (float**)&globalDataOut;
double globalOutUpdateTimePrecise = -1.;
double globalOutUpdateDeltaPrecise = -1.;


static void mjSetError(int err)
{
	// save result
	lastError = err;
}


static void mjSend(int message, int sz)
{
	// make sure we have connection
	if (!soc.getState())
	{
		mjSetError(mjCOM_CANNOTSEND);
		return;
	}

	// flush input buffer, in case earlier call timed out and data came later
	soc.flushInput();

	// set header
	*cmd = message;
	*size = sz;

	// try to send
	if (soc.sendBuffer(buffer, *size + 2 * sizeof(int), 1000))
	{
		soc.clear();
		mjSetError(mjCOM_CANNOTSEND);
	}
	else
		mjSetError(mjCOM_OK);
}



static void mjRecv(void)
{
	// skip if (send) error already detected
	if (lastError != mjCOM_OK)
		return;

	// get message header, disconnect on error or timeout
	int res = soc.recvBuffer(buffer, 2 * sizeof(int), 100000);
	if (res)
	{
		soc.clear();
		mjSetError(res == mjSOC_TIMEOUT ? mjCOM_TIMEOUT : mjCOM_CANNOTRECV);
		return;
	}
	else
	{
		mjSetError(*cmd);
		if (lastError < 0)
			return;
	}

	// get message data, disconnect on error
	if (*size>0 && *size <= BUFSZ)
	{
		if (soc.recvBuffer((char*)data, *size, 1000))
		{
			soc.clear();
			mjSetError(mjCOM_CANNOTRECV);
		}
	}
	else if (*size)
	{
		soc.clear();
		mjSetError(mjCOM_BADSIZE);
	}
}


static void mjServerWaitForConnection(void)
{
	DBGMSG("Waiting for connection here", 10);
	while (sa_connect_server(0, 0) != mjCOM_OK) {
  //       sprintf_s(stringbuffer2,
  //               "Waiting for client connection... Return message: %s.",
  //               sa_last_result());
  //       FString Fs = FString(stringbuffer2);
		// DBGMSG_NT(Fs, 10);
    }
	mjSetError(mjCOM_OK);
	DBGMSG("Connected a client.\n", 10);
}


// return 1 if connection to simulator is live, 0 otherwise
static int mjConnected(void)
{
	return (int)soc.getState();
}


// copy float data, return size
template <class T>
static int copydata(T* dst, const T* src, int n)
{
	if (n)
		memcpy(dst, src, n * sizeof(T));

	return n;
}



// copy 2D data, return size
template <class T, int DIM>
static int copydata2(T dst[][DIM], const T* src, int n)
{
	int i, j;
	if (n)
		for (i = 0; i<n; i++)
			for (j = 0; j<DIM; j++)
				dst[i][j] = src[i*DIM + j];

	return n*DIM;
}



// set float 2D data, return size
template <int DIM>
static int setdata2(float* dst, const float src[][DIM], int n)
{
	int i, j;
	if (n)
		for (i = 0; i<n; i++)
			for (j = 0; j<DIM; j++)
				dst[i*DIM + j] = src[i][j];

	return n*DIM;
}



// require connection
#define REQCONSA if(!soc.getState()) {mjSetError(mjCOM_NOCONNECTION); return saERROR; }
#define REQCON if(!soc.getState()) {mjSetError(mjCOM_NOCONNECTION); return (mjtResult)lastError; }


// check maximum size
#define CHECK(x) if((x)>mjMAXSZ) {mjSetError(mjCOM_BADSIZE); return mjCOM_BADSIZE;}


// check buffer size
#define VERIFY(ptr) if((char*)ptr - (char*)data != *size) mjSetError(mjCOM_BADSIZE);



void do_nothing(void)
{
	DBGMSG("Doing Nothing.\n", 10);
}

void eternal_respond(void)
{
	while (mj_respond() == mjCOM_OK)
	{

	}
	sa_close();
}

//------------------------- Standard API implementation ---------------------------------

// change default port to connect to
saResult sa_change_port(const char* port)
{
    // do not change port when connected
    if( soc.getState() )
    {
        mjSetError(mjCOM_CONNECTED);
        return saERROR;
    }

    for (int i = 0; i < strlen(port); ++i)
    {
        if (!isdigit(port[i]))
        {
            mjSetError(mjCOM_BADPORT);
            return saERROR;
        }
    }

    strcpy(soc.portListen, port);
    return saOK;
}

// connect to simulator on specified host (name or IP address, NULL: local host)
saResult sa_connect(const char* host, const char* port)
{
	static bool firstcall = true;

	// init sockets and clear info only once
	if (firstcall)
	{
		if (port)
			strcpy_s(soc.portListen, port);
		soc.mjInitSockets();
		firstcall = false;
	}

	// do not connect again
	if (soc.getState())
	{
		mjSetError(mjCOM_CONNECTED);
		return saERROR;
	}

	// try to connect for 5 seconds
	mjSetError(mjCOM_OK);
	if (soc.connectClient(5000, host))
		return saOK;
	else
	{
		mjSetError(mjCOM_NOCONNECTION);
		return saERROR;
	}
}


// connect to simulator on specified host (name or IP address, NULL: local host)
saResult sa_connect_server(const char* host, const char* port)
{
	static bool firstcall = true;

	// init sockets and clear info only once
	if (firstcall)
	{
		if (port)
			strcpy_s(soc.portListen, port);
		soc.mjInitSockets();
		firstcall = false;
	}

	// do not connect again
	if (soc.getState())
	{
		mjSetError(mjCOM_CONNECTED);
		return saERROR;
	}

	// try to connect for 6 seconds
	mjSetError(mjCOM_OK);
	if (soc.connectServer(6000, true, host))
		return saOK;
	else
	{
		mjSetError(mjCOM_NOCONNECTION);
		return saERROR;
	}
}



// close connection to simulator
saResult sa_close(void)
{
	REQCONSA

		mjSend(mjCOM_CLOSE, 0);

	soc.clear();
	mjSetError(mjCOM_OK);
	return saOK;
}


// text description of last saResult returned by any API function call
const char* sa_last_result(void)
{
	switch (lastError)
	{
	case mjCOM_OK:
		return "OK";

	case mjCOM_BADSIZE:
		return "Bad data size";

	case mjCOM_BADINDEX:
		return "Bad object index";

	case mjCOM_BADCOMMAND:
		return "Invalid command";

	case mjCOM_CANNOTSEND:
		return "Could not send data, disconnecting";

	case mjCOM_CANNOTRECV:
		return "Could not receive data, disconnecting";

	case mjCOM_TIMEOUT:
		return "Socket timeout, disconnecting";

    case mjCOM_BADPORT:
        return "Bad port specified, closing";

	case mjCOM_NOCONNECTION:
		return "No connection to host";

	case mjCOM_CONNECTED:
		return "Already connected";

	default:
		return "Unknown error";
	}
}


//-------------------------- API
// connect to simulator
mjtResult mj_connect(const char* host)
{
	if (sa_connect(host, 0) == saOK)
		return mjCOM_OK;
	else
		return (mjtResult)lastError;
}


// close connection to simulator
mjtResult mj_close(void)
{
	if (!soc.getState())
        return mjCOM_OK;

	soc.clear();
	mjSetError(mjCOM_OK);
	DBGMSG("Closed connection to client.\n", 10);
	return mjCOM_OK;
}



// return last result code
mjtResult mj_result(void)
{
	return (mjtResult)lastError;
}


//------------------------- API request/reply functions ---------------------------------------
// server automatic reply choices
mjtResult mj_respond(void)
{
    if (!mjConnected())
        mjServerWaitForConnection();

    mjRecv();

    switch (lastError) {
        case mjCOM_INFO         :
            mj_respond_info();
            break;

        case mjCOM_CLOSE        :
            mj_close();
            break;

        case mjCOM_SENDDATA   :
            return mj_receive_data();
            break;

        case mjCOM_REQUESTDATA   :
            return mj_respond_data();
            break;

        default:
            DBGMSG("Unknown command received.", 10);
    }

    return (mjtResult)lastError;
}

mjtResult mj_request_data(mjDataReturnTime* res)
{
    REQCON

    // exchange
    mjSend(mjCOM_REQUESTDATA, 0);
    mjRecv();

    // copy data if OK
    if( lastError==mjCOM_OK )
    {
        // sizes
        CHECK( res->n = data[0] );

        // data
        float* num = (float*)(data+1);
        res->lastUpdateTime = num[0];
        res->lastUpdateDelta = num[1];
        num += 2;
        num += copydata(res->dat,  num, res->n);

        // VERIFY(num);
    }

    return (mjtResult)lastError;
}


mjtResult mj_respond_data(void)
{
    mjSetError(mjCOM_OK);
    mjDataReturnTime res;
    memset(&res, 0, sizeof(mjDataReturnTime));

    /// HERE BE CALCULATIONS
    res.n = globalNOut;
    for (int i = 0; i < res.n; ++i)
        res.dat[i] = globalDataOut[i];

    double currentTime = FPlatformTime::Seconds();
    if (globalOutUpdateTimePrecise >= 0)
        globalOutUpdateDeltaPrecise = currentTime - globalOutUpdateTimePrecise;
        globalOutUpdateTimePrecise = currentTime;

    res.lastUpdateTime = (float) globalOutUpdateTimePrecise;
    res.lastUpdateDelta = (float) globalOutUpdateDeltaPrecise;

    // sprintf_s(stringbuffer2,
    //         "dat1: %f, dat2: %f",
    //         res.dat[0], res.dat[1]);
    // FString Fs = FString(stringbuffer2);
    // DBGMSG_NT(Fs, 10);

    // sizes
    CHECK( data[0] = res.n );

    // data
    float* num = (float*)(data+1);
    num[0] = res.lastUpdateTime;
    num[1] = res.lastUpdateDelta;
    num += 2;
    num += copydata(num, res.dat,  res.n);

    // exchange
    mjSend(mjCOM_OK, 1*sizeof(int) + (res.n+2)*sizeof(float));

    return (mjtResult)lastError;
}

mjtResult mj_send_data(const mjData* rqs)
{
    REQCON

    // sizes
    CHECK(data[0] = rqs->n);

    // data
    float* num = (float*)(data + 1);
    num += copydata(num, rqs->dat, rqs->n);

    // exchange
    mjSend(mjCOM_SENDDATA, 1 * sizeof(int) + (rqs->n) * sizeof(float));
    mjRecv();

    return (mjtResult)lastError;
}

mjtResult mj_receive_data(void)
{

    mjSetError(mjCOM_OK);
    mjData rqs;
    memset(&rqs, 0, sizeof(mjData));

    // sizes
    CHECK(rqs.n = data[0]);

    // data
    float* num = (float*)(data + 1);
    num += copydata(rqs.dat, num, rqs.n);

    VERIFY(num);

    /// HERE BE CALCULATIONS and saving the data somewhere
    globalNIn = rqs.n;
    for (int i = 0; i < globalNIn; ++i)
        globalDataIn[i] = rqs.dat[i];



    // acknowledge
    mjSend(mjCOM_OK, 0);

    return (mjtResult)lastError;
}


mjtResult mj_request_info(mjInfo* res)
{
    REQCON

    // exchange
    mjSend(mjCOM_INFO, 0);
    mjRecv();

    // copy data if OK
    if( lastError==mjCOM_OK )
        res->n = data[0];

    return (mjtResult)lastError;
}


mjtResult mj_respond_info(void)
{
    mjSetError(mjCOM_OK);

    data[0] = 14;

    // exchange
    mjSend(mjCOM_OK, 1*sizeof(int));

    return (mjtResult)lastError;
}


//------------------------------- runnable

SaSocketApi::SaSocketApi()
{
    dataIn = globalDataIn;
    NIn = &globalNIn;

    dataOut = globalDataOut;
    NOut = &globalNOut;
    // outUpdateTime = &globalOutUpdateTime;
    // outUpdateTimePrecise = &globalOutUpdateTimePrecise;
}

SaSocketApi::~SaSocketApi()
{

    if (soc.getState())
        mj_close();
}

void SaSocketApi::changePort(const char* port)
{
    sa_change_port(port);
}

//Init
bool SaSocketApi::Init()
{
    return true;
}

//Run
uint32 SaSocketApi::Run()
{
    //Initial wait before starting
    FPlatformProcess::Sleep(0.003);

    //While not told to stop this thread
    //      and not yet finished finding Prime Numbers
    while (StopTaskCounter.GetValue() == 0 && mj_respond() == mjCOM_OK)
    {
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //prevent thread from using too many resources
        //FPlatformProcess::Sleep(0.01);
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    }

    //Run SaSocketApi::Shutdown() from the timer in Game Thread that is watching
        //to see when SaSocketApi::IsThreadFinished()
    mj_close();

    return 0;
}

//stop
void SaSocketApi::Stop()
{
    // StopTaskCounter.Increment();

    // UE_LOG(LogTemp, Warning, TEXT("StopTaskCounter currently references %p address."), (void *) &StopTaskCounter);
    // UE_LOG(LogTemp, Warning, TEXT("It has value %d."), StopTaskCounter.GetValue());
    StopTaskCounter.Increment();
    // UE_LOG(LogTemp, Warning, TEXT("After increment it has value %d."), StopTaskCounter.GetValue());
}
