#include "communication.h"
#include "messages.h"
#include "data.h"

#pragma warning(disable : 4047)

//This is the function that actually checks what IOCTL has been received and acts upon it
NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	ULONG ByteIO = 0;
	PULONG output;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	switch (stack->Parameters.DeviceIoControl.IoControlCode)
	{
	case IOCTL_GETCLIENTADDRESS:
		output = (PULONG)Irp->AssociatedIrp.SystemBuffer;
		*output = (PULONG)CheatDllAddress;

		ByteIO = sizeof(*output);
		status = STATUS_SUCCESS;
		DebugMessage("IOCTL_GETCLIENTADDRESS has been handled.\n");
		break;

	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;
	}

	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = ByteIO;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	DebugMessage("IOCTL has been handled.\n");
	return status;
}

//This function essentially approves the finalisation of the request
NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	//Indicates the status that this request would complete with
	Irp->IoStatus.Status = STATUS_SUCCESS;

	//a polymorphic member, meaning different things in different requests. In the case of Createand Close, a zero value is just fine.
	Irp->IoStatus.Information = 0;

	//Completes the IRP, IO_NO_INCREMENT says that the caller does not get a priority boost
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	DebugMessage("IO Request Finalisation Authorised\n");
	return STATUS_SUCCESS;
}

//This function essentially approves the acceptance of the request
NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	//Indicates the status that this request would complete with
	Irp->IoStatus.Status = STATUS_SUCCESS;

	//a polymorphic member, meaning different things in different requests. In the case of Createand Close, a zero value is just fine.
	Irp->IoStatus.Information = 0;

	//Completes the IRP, IO_NO_INCREMENT says that the caller does not get a priority boost
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	DebugMessage("IO Request Authorised\n");
	return STATUS_SUCCESS;
}