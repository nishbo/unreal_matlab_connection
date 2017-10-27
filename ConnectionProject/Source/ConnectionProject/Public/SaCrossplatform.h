// Fill out your copyright notice in the Description page of Project Settings.

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
class CONNECTIONPROJECT_API SaCrossplatform
{
public:
	SaCrossplatform();
	~SaCrossplatform();
};


//---------------------------- Critical Section -----------------------------------------

// section object
class CONNECTIONPROJECT_API mjCriticalSection
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
class CONNECTIONPROJECT_API mjCriticalSectionLock
{
public:
	mjCriticalSectionLock(mjCriticalSection* pcs);
	~mjCriticalSectionLock();

private:
	mjCriticalSection* pcs;
};


//---------------------------- Events -------------------------------------------------

// single event
class CONNECTIONPROJECT_API mjEvent
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

class CONNECTIONPROJECT_API mjSemaphore
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
