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

#include "SaSocket.h"


static char stringbuffer[100000];

SaSocket::SaSocket()
{
	// clear
	soc = INVALID_SOCKET;
	state = false;

	// default settings
	strcpy_s(portListen, "44400");
	verbose = false;
	tmoutTryConnect = 2000;
	userexit = 0;
}

SaSocket::~SaSocket()
{
	clear();
}

// last socket error
int SaSocket::mjSocketError(void)
{
	return WSAGetLastError();
}


// init sockets
void SaSocket::mjInitSockets(void)
{
	WSADATA wsaData;
	if (WSAStartup(0x0202, &wsaData))
		_error("error initializing Winsock");
}


// clean sockets
void SaSocket::mjClearSockets(void)
{
	if (WSACleanup())
		_error("error cleaning up Winsock");
}


// set blocking mode for socket
void SaSocket::mjSetBlocking(SOCKET s, bool block)
{
	unsigned long value = (!block);
	if (ioctlsocket(s, FIONBIO, &value))
		_error("set blocking mode failed with error %d", mjSocketError());
}


// call user-defined error, or print message and exit
void SaSocket::_error(const char* format, int i)
{
    char sbbb[1000];
    sprintf_s(sbbb,
            "\n\nA very bad error happened in sockets. %s \n",
            format);
    sprintf_s(stringbuffer, sbbb, i);
    FString Fs = FString(stringbuffer);
    DBGMSG_NT(Fs, 10);
}



// try to make connection to specified host
bool SaSocket::connectClient(int tmout, const char* host)
{
	// record start time
	int tmStart = mjGetTime();

	// try to connect
	while (tmout<0 || mjGetTime() - tmStart<tmout)
		if (tryConnect(portListen, host, tmoutTryConnect))
			break;

	return state;
}



// listen for connections
bool SaSocket::connectServer(int tmout, bool print, const char* hostServer)
{
	// what if we are already connected ???

	// get address info for local machine
	struct addrinfo* info = getHost(true, portListen, hostServer);
	if (!info)
		_error("getaddrinfo failed with error %d", mjSocketError());

	// print wait message
	if (print)
	{
		//char adr[INET_ADDRSTRLEN];
		//DBGMSG(sprintf_s("waiting for connection on %s : %s\n",
		//	inet_ntop(AF_INET, &(((struct sockaddr_in*)info->ai_addr)->sin_addr),
		//		adr, INET_ADDRSTRLEN), portListen), 10);
	}

	// create a socket for listening
	SOCKET ListenSocket = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
	if (ListenSocket == INVALID_SOCKET)
		_error("socket creation failed with error %d", mjSocketError());

	// get rid of reuse error
	int on = 1;
	if (setsockopt(ListenSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(int)))
		_error("setsockopt failed with error %d", mjSocketError());

	// bind, release addrinfo
	if (bind(ListenSocket, info->ai_addr, (int)info->ai_addrlen))
		_error("socket bind failed with error %d", mjSocketError());
	freeaddrinfo(info);

	// set keepalive and non-blocking
	if (setsockopt(ListenSocket, SOL_SOCKET, SO_KEEPALIVE, (char*)&on, sizeof(int)))
		_error("setsockopt failed with error %d", mjSocketError());
	mjSetBlocking(ListenSocket, false);

	// init timing info
	int tmStart = mjGetTime();

	// start listening
	if (listen(ListenSocket, SOMAXCONN))
		_error("listen socket failed with error %d", mjSocketError());

	// wait/accept connections
	int remaining = 0;
	while (tmout<0 || (remaining = tmout - (mjGetTime() - tmStart))>0)
		if (waitSocket(ListenSocket, true, remaining < 100 ? remaining : 100))
		{
			// accept connection
			soc = accept(ListenSocket, NULL, NULL);
			if (soc == INVALID_SOCKET)
				_error("accept socket failed with error %d", mjSocketError());
			state = true;

			// set keepalive, no-delay and non-blocking
			if (setsockopt(soc, SOL_SOCKET, SO_KEEPALIVE, (char*)&on, sizeof(on)))
				_error("setsockopt failed with error %d", mjSocketError());
			if (setsockopt(soc, IPPROTO_TCP, TCP_NODELAY, (char*)&on, sizeof(on)))
				_error("setsockopt tcp_nodelay failed with error %d", mjSocketError());
			mjSetBlocking(soc, false);

			break;
		}

	// exit if user function says so
		else if (userexit)
		{
			if (userexit())
				break;
		}

	closesocket(ListenSocket);
	return state;
}



// close socket
void SaSocket::clear(void)
{
	if (state && closesocket(soc))
		if (verbose) {
			//DBGMSG(sprintf_s("close socket error %d", mjSocketError()), 10);
		}

	state = false;
}



// flush input buffer
void SaSocket::flushInput(void)
{
	while (waitSocket(soc, true, 0))
		recvBuffer(dummy, 1000, 0);
}



// send buffer
int SaSocket::sendBuffer(const char *buf, int len, int tmout)
{
	int n, ndone = 0, tmStart = mjGetTime();

	if (verbose) {
		//DBGMSG(sprintf_s("SEND BUFFER %d\n", len), 10);
	}
	// socket assumed closed
	if (!state)
		return mjSOC_CLOSED;

	// send in chunks (usually necessary)
	while (ndone<len)
	{
		// prepare timeout info
		int remaining;
		if (tmout >= 0)
		{
			remaining = tmout - (mjGetTime() - tmStart);

			// handle timeout
			if (remaining<0)
				return mjSOC_TIMEOUT;
		}
		else
			remaining = -1;

		// wait for socket to become writable, write
		if (waitSocket(soc, false, remaining))
		{
			if (verbose) {
				//DBGMSG(sprintf_s(" trying to send %d bytes\n", len - ndone), 10);
			}
			// send
			n = send(soc, buf + ndone, len - ndone, 0);

			// handle socket error
			if (n <= 0)
			{
				int err = mjSocketError();
				clear();

				if (verbose) {}
					//DBGMSG(sprintf_s("error in sendBuffer: %d\n", err), 10);

				return err;
			}
			else if (verbose) {}
				//DBGMSG(sprintf_s(" sent %d bytes\n", len - ndone), 10);


			// add to done
			ndone += n;
		}
	}

	return mjSOC_OK;
}



// receive buffer
int SaSocket::recvBuffer(char *buf, int len, int tmout)
{
	int n, ndone = 0, tmStart = mjGetTime();

	if (verbose) {}
		//DBGMSG(sprintf_s("RECEIVE BUFFER %d\n", len), 10);

	// socket assumed closed
	if (!state)
	{
		if (verbose) {}
			//DBGMSG(sprintf_s("--- bad state\n"), 10);
		return mjSOC_CLOSED;
	}

	// receive in chunks (usually necessary)
	while (ndone<len)
	{
		// prepare timeout info
		int remaining;
		if (tmout >= 0)
		{
			remaining = tmout - (mjGetTime() - tmStart);

			// handle timeout
			if (remaining <= 0)
			{
				if (verbose) {}
					/*DBGMSG(sprintf_s("--- timeout: %d, %d, %d, %d\n",
						tmout, remaining, mjGetTime(), tmStart), 10);*/
				return mjSOC_TIMEOUT;
			}
		}
		else
			remaining = -1;

		// wait for socket to become readable, read
		if (waitSocket(soc, true, remaining))
		{
			if (verbose) {}
				//DBGMSG(sprintf_s(" waiting for %d bytes\n", len - ndone), 10);

			// recv
			n = recv(soc, buf + ndone, len - ndone, 0);

			// handle socket error
			if (n <= 0)
			{
				int err = (n == 0) ? 2 : mjSocketError();
				clear();

				if (verbose) {}
					//DBGMSG(sprintf_s("error in recvBuffer: %d\n", err), 10);

				return err;
			}
			else if (verbose) {}
				//DBGMSG(sprintf_s(" received %d bytes\n", n), 10);

			// add to done
			ndone += n;
		}
		else if (verbose) {}
			//DBGMSG(sprintf_s("could not wait: %d\n", remaining), 10);
	}

	return mjSOC_OK;
}



// receive as much as possible; tmout1 for first chunk, tmout2 for subsequent
int SaSocket::recvImmediate(char* buf, int len, int* received, int tmout1, int tmout2)
{
	if (verbose) {}
		//DBGMSG(sprintf_s("RECEIVE IMMEDIATE %d\n", len), 10);

	// socket assumed closed
	if (!state)
	{
		if (verbose) {}
			//DBGMSG(sprintf_s("--- bad state\n"), 10);
		return mjSOC_CLOSED;
	}

	// receive in chunks, return on first (short) timeout
	*received = 0;
	while (*received<len)
	{
		// wait for socket to become readable, read
		if (waitSocket(soc, true, *received ? tmout2 : tmout1))
		{
			// recv
			int n = recv(soc, buf + *received, len - *received, 0);

			// handle socket error
			if (n <= 0)
			{
				int err = (n == 0) ? 2 : mjSocketError();
				clear();

				if (verbose) {}
					//DBGMSG(sprintf_s("error in recvBuffer: %d\n", err), 10);

				return err;
			}
			else if (verbose) {}
				//DBGMSG(sprintf_s("received %d bytes\n", n), 10);

			// add to received
			*received += n;
		}
		else
			return mjSOC_TIMEOUT;
	}

	return mjSOC_OK;
}



//-------------------------mjSocket utility functions ---------------------------------

// getaddrinfo for host (default: this machine)
struct addrinfo* SaSocket::getHost(bool passive, const char* port, const char* host)
{
	struct addrinfo* info = 0;

	// set hints
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (passive)
		hints.ai_flags = AI_PASSIVE;

	// get address info
	char autoname[100];
	gethostname(autoname, 100);

	if (getaddrinfo((host ? host : autoname), port, &hints, &info))
		return 0;
	else
		return info;
}



// make one active connection
bool SaSocket::tryConnect(const char* port, const char* host, int tmout)
{
	// resolve the server address and port
	struct addrinfo* info = getHost(false, port, host);
	if (!info)
	{
		if (verbose) {}
			//DBGMSG(sprintf_s("tryConnect could not getaddrinfo for %s:%s\n", host, port), 10);
		return false;
	}

	// create socket, free addrinfo
	soc = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
	if (soc == INVALID_SOCKET)
		_error("socket creation failed with error %d", mjSocketError());

	// set keepalive and non-blocking
	int on = 1;
	if (setsockopt(soc, SOL_SOCKET, SO_KEEPALIVE, (char*)&on, sizeof(on)))
		_error("setsockopt failed with error %d", mjSocketError());
	if (setsockopt(soc, IPPROTO_TCP, TCP_NODELAY, (char*)&on, sizeof(on)))
		_error("setsockopt tcp_nodelay failed with error %d", mjSocketError());
	mjSetBlocking(soc, false);

	// print
	if (verbose)
	{
		//char adr[INET_ADDRSTRLEN];
		//DBGMSG(sprintf_s("\ntryConnect: host = %s, port = %s, ip = %s\n",
		//	host, port, inet_ntop(AF_INET, &(((struct sockaddr_in*)info->ai_addr)->sin_addr),
		//		adr, INET_ADDRSTRLEN)), 10);
	}

	// try to connect (expect EINPROGRESS or WWOULDBLOCK), free info
	int res = connect(soc, info->ai_addr, (int)info->ai_addrlen);
	int err = mjSocketError();
	if (res && (err != WSAEINPROGRESS && err != WSAEWOULDBLOCK))
		_error("connect socket failed with error %d", mjSocketError());
	freeaddrinfo(info);

	// if connection was not made immediately, wait
	if (res == 0 || waitSocket(soc, false, tmout))
	{
		// check for error
		int err = 0;
		socklen_t size = sizeof(int);
		if (getsockopt(soc, SOL_SOCKET, SO_ERROR, (char*)&err, &size))
			_error("getsockopt failed with error %d", mjSocketError());

		// no error: connection successful
		if (!err)
		{
			if (verbose) {}
				//DBGMSG(sprintf_s("   successful connection\n"), 10);
			state = true;
			return true;
		}
	}

	// failure
	closesocket(soc);
	return false;
}



// use select() to wait for socket operation, true if not timeout
bool SaSocket::waitSocket(SOCKET s, bool read, int tmout)
{
	// make set with socket s
	fd_set set;
	FD_ZERO(&set);
	FD_SET(s, &set);

	// timeout structure
	struct timeval tm;
	tm.tv_sec = tmout / 1000;
	tm.tv_usec = ((long)(tmout % 1000)) * 1000;

	// call with read or write set
	int result = 0;
	if (read)
		result = select((int)s + 1, &set, 0, 0, tmout >= 0 ? &tm : 0);
	else
		result = select((int)s + 1, 0, &set, 0, tmout >= 0 ? &tm : 0);

	// check for error
	if (result == SOCKET_ERROR)
		_error("select socket failed with error %d", mjSocketError());

	return (result == 1);
}
