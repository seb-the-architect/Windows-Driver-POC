#include "events.h"
#include "messages.h"
#include "data.h"

#pragma warning(disable : 6273 4047)

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{
	//DebugMessage("Image loaded with the name %ls\n", FullImageName->Buffer);
	if (wcsstr(FullImageName->Buffer, L"DitW Internal 2.0.dll"))
	{
		DebugMessage("Our cheat was just injected amen.\n");
		CheatDllAddress = ImageInfo->ImageBase;

		DebugMessage("Process ID: %d\n", ProcessId);
	}

	return STATUS_SUCCESS;
}