#pragma once
#include <Windows.h>

#define IOCTL_GETCLIENTADDRESS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x3000, METHOD_BUFFERED, FILE_ANY_ACCESS)