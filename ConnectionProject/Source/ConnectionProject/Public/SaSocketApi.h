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

#pragma once

#include "CoreMinimal.h"

#include "SaSocket.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

/**
 *
 */
class CONNECTIONPROJECT_API SaSocketApi : public FRunnable
{
public:
	SaSocketApi();
	virtual ~SaSocketApi();

    // data in
    float* dataIn;
    int* NIn;

    // data out
    float* dataOut;
    int* NOut;
    // float* outUpdateTime;
    // double* outUpdateTimePrecise;

    /** Stop this thread? Uses Thread Safe Counter */
    FThreadSafeCounter StopTaskCounter;

    // Begin FRunnable interface.
    virtual bool Init();
    virtual uint32 Run();
    virtual void Stop();
    // End FRunnable interface

    void changePort(const char* port);

};


// this is a C API
extern "C" {

	// API return codes
	typedef enum
	{
		saOK = 0,                               // success
		saERROR                                 // error; call sa_last_result for description
	} saResult;


	// message codes
	typedef enum
	{
		// client-to-server, standard API
		mjCOM_INFO = 1,

		mjCOM_CLOSE,

        mjCOM_SENDDATA,
        mjCOM_REQUESTDATA,
        mjCOM_REPLYDATA,
	} mjtComCode;


	void do_nothing(void);

	void eternal_respond(void);

	//--------------------------- API functions ---------------------------------------------

    // change default port - workaround for sa_connect
    saResult sa_change_port(const char* port);

	// connect to specified host (name or IP address, NULL: local host); port is ignored
	saResult sa_connect(const char* host, const char* port);

	// connect to specified host (name or IP address, NULL: local host); port is ignored -----
	saResult sa_connect_server(const char* host, const char* port);

	// close connection to simulator
	saResult sa_close(void);

	// text description of last saResult returned by any API function call
	const char* sa_last_result(void);


	//-------------------------------- constants --------------------------------------------

	// predefined size for array allocation
#define mjMAXSZ 1000


	// API return codes
	typedef enum
	{
		mjCOM_OK = 0,            // success

        // server-to-client errors
        mjCOM_BADSIZE = -1,           // data has invalid size
        mjCOM_BADINDEX = -2,           // object has invalid index
        mjCOM_BADTYPE = -3,           // invalid object type
        mjCOM_BADCOMMAND = -4,           // unknown command
        mjCOM_CANNOTSEND = -5,           // could not send data
        mjCOM_CANNOTRECV = -6,           // could not receive data
        mjCOM_TIMEOUT = -7,           // receive timeout
        mjCOM_BADPORT       = -8,           // bad port specified

        // client-side errors
        mjCOM_NOCONNECTION = -9,           // connection not established
        mjCOM_CONNECTED = -10,          // already connected
	} mjtResult;


	//------------------------------- mj api
	mjtResult mj_connect(const char* host);

	mjtResult mj_close(void);

	mjtResult mj_result(void);

	mjtResult mj_respond(void);
	//------------------------- Data structures -----------------

	// Info about build number ??
	struct _mjInfo
	{
		int n;
	};
	typedef struct _mjInfo mjInfo;

    // simplest data structure, needed for both sending and receiving
    struct _mjData
    {
        int n;                              // number of elements
        float dat[mjMAXSZ];
    };
    typedef struct _mjData mjData;

    // simplest data structure, needed for both sending and receiving
    struct _mjDataReturnTime
    {
        int n;                              // number of elements
        float dat[mjMAXSZ];
        float lastUpdateTime;
        float lastUpdateDelta;
    };
    typedef struct _mjDataReturnTime mjDataReturnTime;


	//--------------------------- API request/reply functions ----------------------


    // requests the server, is called on client
    mjtResult mj_request_data(mjDataReturnTime* res);

    // reply to a request by server
    mjtResult mj_respond_data(void);

    // send data to server
    mjtResult mj_send_data(const mjData* rqs);

    // receive data on server
    mjtResult mj_receive_data(void);

    // request information from server
    mjtResult mj_request_info(mjInfo* res);

    // reply with information
    mjtResult mj_respond_info(void);


}
