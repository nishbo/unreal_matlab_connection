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

#include "stdio.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

#define PATHSYMBOL '\\'


/**
 *
 */
class SOCKETSERVERCONNECTION_API SaCrossplatform
{
public:
	SaCrossplatform();
	~SaCrossplatform();
};


//---------------------------- Critical Section -----------------------------------------

// section object
class SOCKETSERVERCONNECTION_API mjCriticalSection
{
public:
	mjCriticalSection();
	~mjCriticalSection();

	void Enter(void);
	void Leave(void);
	bool TryEnter(void);

private:
	CRITICAL_SECTION cs;
};


// lock critical section
class SOCKETSERVERCONNECTION_API mjCriticalSectionLock
{
public:
	mjCriticalSectionLock(mjCriticalSection* pcs);
	~mjCriticalSectionLock();

private:
	mjCriticalSection* pcs;
};


//---------------------------- Events -------------------------------------------------

// single event
class SOCKETSERVERCONNECTION_API mjEvent
{
public:
	mjEvent();
	~mjEvent();

	bool Get(void);
	void Set(void);
	void Reset(void);
	bool Wait(int msec = -1);

private:
	HANDLE ev;
};


//---------------------------- Semaphores -----------------------------------------------

class SOCKETSERVERCONNECTION_API mjSemaphore
{
public:
	mjSemaphore(int initCount = 0);
	~mjSemaphore();

	bool Wait(int msec = -1);		// -1: infinite wait; 0: return immediately
	void Increase(int count = 1);

private:
	HANDLE sem;
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
