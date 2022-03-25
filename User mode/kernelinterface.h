#pragma once

#include "communication.h"

class KernelInterface
{
public:
	HANDLE hDevice;

	KernelInterface(LPCSTR RegistryPath)
	{
		//Look into this
		hDevice = CreateFileA(RegistryPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	}

	DWORD GetClientAddress()
	{
		if (hDevice == INVALID_HANDLE_VALUE)
		{
			return 0;
		}

		ULONG Address;
		DWORD Bytes;

		//Look into this
		if (DeviceIoControl(hDevice, IOCTL_GETCLIENTADDRESS, &Address, sizeof(Address), &Address, sizeof(Address), &Bytes, NULL))
		{
			return Address;
		}

		return -1;
	}

};