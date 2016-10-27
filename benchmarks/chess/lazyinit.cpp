/********************************************************
*                                                       *
*     Copyright (C) Microsoft. All rights reserved.     *
*                                                       *
********************************************************/

#include <windows.h>


CRITICAL_SECTION lock;

int x = 0;

DWORD WINAPI foo(LPVOID param) {
	EnterCriticalSection(&lock);
	LeaveCriticalSection(&lock);
	return 0;
}

extern "C" 
__declspec(dllexport) int ChessTestRun(){

	DWORD tid;
	HANDLE hThread;

	InitializeCriticalSection(&lock);

	if(x == 0){
	  EnterCriticalSection(&lock);
	  LeaveCriticalSection(&lock);
	}


	hThread = CreateThread(NULL, 0, foo, NULL, 0, &tid);
	EnterCriticalSection(&lock);
	x++;
	LeaveCriticalSection(&lock);

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	DeleteCriticalSection(&lock);
	return 0;
}
