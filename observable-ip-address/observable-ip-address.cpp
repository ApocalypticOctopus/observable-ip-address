// observable-ip-address.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <windows.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	OVERLAPPED overlap;
	DWORD ret;

	HANDLE hand = NULL;
	overlap.hEvent = WSACreateEvent();

	ret = NotifyAddrChange(&hand, &overlap);

	if (ret != NO_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			printf("NotifyAddrChange error...%d\n", WSAGetLastError());
			return 1;
		}
	}

	if (WaitForSingleObject(overlap.hEvent, INFINITE) == WAIT_OBJECT_0)
		printf("IP Address table changed..\n");

	return 0;
}
