#include "communication.h"
#include "ghDriver.h"
#include "messages.h"
#include "events.h"
#include "data.h"

#pragma warning(disable : 6273 4047 4024)

/*
NOTES
[PG 47]
The actual CreateFile call made by Process Explorer
(or any other client) based on the symbolic link must be prepended with \\.\. This is necessary so
that the object manager’s parser will not assume the string “PROCEXP152” (for example) indicates a file in the
current directory.

https://googleprojectzero.blogspot.com/2015/10/windows-drivers-are-truely-tricky.html
Symbolic links are stored in \\DosDevice\\ and devices are stored in \\Devices\\
*/

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegsitryPath)
{
	UNREFERENCED_PARAMETER(pRegsitryPath);
	pDriverObject->DriverUnload = UnloadDriver;

	
	DebugMessage("Welcome to my first driver!\n");
	
	PsSetLoadImageNotifyRoutine(ImageLoadCallback);

	//The path for the device object we are going to make
	RtlInitUnicodeString(&dev, L"\\Device\\ghDevice");
	//The path for the symbolic link we are going to make
	RtlInitUnicodeString(&dos, L"\\DosDevices\\ghLink");

	IoCreateDevice(pDriverObject, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	IoCreateSymbolicLink(&dos, &dev);

	pDriverObject->MajorFunction[IRP_MJ_CREATE] = CreateCall;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = CloseCall;
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;

	pDeviceObject->Flags |= DO_DIRECT_IO;
	pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

	return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject)
{
	UNREFERENCED_PARAMETER(pDriverObject);
	DebugMessage("Ight imma head out\n");
	PsRemoveLoadImageNotifyRoutine(ImageLoadCallback);

	IoDeleteSymbolicLink(&dos);
	IoDeleteDevice(pDriverObject->DeviceObject);

	return STATUS_SUCCESS;
}