/*
  MuJoCo OS-specific functions

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


//------------------------- OS-specific include, libraries, defines --------------------

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <mmsystem.h>
	
	#define PATHSYMBOL '\\'

#else
	#include <pthread.h>
	#include <semaphore.h>
	#include <sys/types.h>
	#include <errno.h>
	#include <netdb.h>
	#include <unistd.h>
	#include <X11/Xlib.h>

	#define PATHSYMBOL '/'
#endif


//---------------------------- Critical Section -----------------------------------------

// section object
class mjCriticalSection
{
public:
	mjCriticalSection();
	~mjCriticalSection();

	void Enter(void);
	void Leave(void);
	bool TryEnter(void);

private:
#ifdef _WIN32
	CRITICAL_SECTION cs;
#else
	pthread_mutex_t mtx;
#endif
};


// lock critical section
class mjCriticalSectionLock
{
public:
	mjCriticalSectionLock(mjCriticalSection* pcs);
	~mjCriticalSectionLock();

private:
	mjCriticalSection* pcs;
};


//---------------------------- Events -------------------------------------------------

// single event
class mjEvent
{
public:
	mjEvent();
	~mjEvent();

	bool Get(void);
	void Set(void);
	void Reset(void);
	bool Wait(int msec = -1);

private:
#ifdef _WIN32
	HANDLE ev;
#else
	pthread_mutex_t mtx;
	pthread_cond_t cnd;
	struct timespec tmout;
	bool state;
#endif
};


//---------------------------- Semaphores -----------------------------------------------

class mjSemaphore
{
public:
	mjSemaphore(int initCount = 0);
	~mjSemaphore();

	bool Wait(int msec = -1);		// -1: infinite wait; 0: return immediately
	void Increase(int count = 1);

private:
#ifdef _WIN32
	HANDLE sem;
#else
	sem_t sem;
	struct timespec tmout;
#endif
};


// get the number of processor cores on the local machine
int mjGetNCores(void);


//---------------------------- Timing ---------------------------------------------------

// initialize 1 msec timer (on Windows), record base time
void mjBeginTime(void);

// close timer (on Windows)
void mjEndTime(void);

// get time in milliseconds scince mjBeginTime
int mjGetTime(void);

// get time in microseconds since mjBeginTime
long long int mjGetTimeHR(void);

// sleep for given number of milliseconds
void mjSleep(unsigned int msec);
