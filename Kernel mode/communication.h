#pragma once
#include <ntifs.h>

#define IOCTL_GETCLIENTADDRESS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x3000, METHOD_BUFFERED, FILE_ANY_ACCESS)

NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp);

NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP Irp);

NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP Irp);