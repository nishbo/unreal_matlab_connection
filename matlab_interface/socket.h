/*
  MuJoCo socket library

  Written by Emo Todorov

  Copyright (C) 2017 Roboti LLC
  
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

#include "crossplatform.h"


#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <winsock2.h>
	#include <ws2tcpip.h>

#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netinet/tcp.h>
	#include <arpa/inet.h>
	#include <errno.h>
	#include <fcntl.h>

	#define SOCKET int
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define WSAEINPROGRESS EINPROGRESS
	#define WSAEWOULDBLOCK EWOULDBLOCK
	#define closesocket close
#endif


//------------------------- Socket functions -------------------------------------------

typedef enum _mjtSoc		// results from socket send/receive
{
	mjSOC_OK = 0,			// success
	mjSOC_TIMEOUT,			// timeout
	mjSOC_CLOSED			// socket is in closed (or otherwise bad) state
} mjtSoc;


// type of socket error callback
typedef void (*mjfSocErr)(const char* format, int i);


class mjSocket				// socket functionality
{
public:
	mjSocket();
	~mjSocket();

	//-------------- initialization and error functions 

	// user-defined error function pointer
	void (*_errorfunc)(const char* format, int i);

	// error function
	void _error(const char* format, int i = 0);

	// last socket error
	int mjSocketError(void);

	// init sockets (needed in Windows only)
	void mjInitSockets(void);

	// clean sockets (needed in Windows only)
	void mjClearSockets(void);

	// set blocking mode for socket
	void mjSetBlocking(SOCKET s, bool block);

	//-------------- main API

	// active: try to connect
	bool connectClient(int tmout = -1, const char* host = 0); 

	// passive: listen for connections
	bool connectServer(int tmout = -1, bool print = false, 
					   const char* hostServer = 0);

	// clear socket
	void clear(void);

	// flush input
	void flushInput(void);

	// send buffer; return mjtSoc or socket error if negative
	int sendBuffer(const char* buf, int len, int tmout = -1);

	// receive buffer; return mjtSoc or socket error if negative
	int recvBuffer(char* buf, int len, int tmout = -1);

	// receive as much as possible; tmout1 for first chunk, tmout2 for subsequent
	int recvImmediate(char* buf, int len, int* received, int tmout1, int tmout2);

	// read-only access
	SOCKET getSoc(void)	{return soc;}
	bool getState(void)	{return state;}

	//---------------- utility functions

	// getaddrinfo for host (default: this machine)
	struct addrinfo* getHost(bool passive, const char* port, const char* host = 0);

	// make connection
	bool tryConnect(const char* port, const char* host, int tmout);

	// use select() to wait for socket read/write, true if not timeout
	bool waitSocket(SOCKET s, bool read, int tmout);


	//---------------- settings

	char portListen[100];			// port for listening (user can change the default)
	bool verbose;					// print diagnostics
	int tmoutTryConnect;			// timeout for each connect attempt
	bool (*userexit)(void);			// check if user wants to exit before listen timeout

private:
	SOCKET	soc;					// socket object
	bool	state;					// last known state (true: connected)
	char	dummy[1000];			// used to flush input
};
