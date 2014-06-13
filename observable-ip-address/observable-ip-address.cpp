// observable-ip-address.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <windows.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("Usage: %s \"<command to run each time an IP address changes>\"\n", argv[0]);
		system("pause");
		return 1;
	}

	OVERLAPPED overlap;
	DWORD ret;

	HANDLE hand = NULL;
	overlap.hEvent = WSACreateEvent();

	while (true)
	{
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
		{
			system((const char*)argv[1]);
		}
	}

	return 0;
}

