
#pragma once
#include <string.h>

#pragma pack(push, 1)

const int PAYLOADSIZE = 10;

typedef enum
{
	Device1_Id = 101,
	Device2_Id = 102,
} DeviceIdType;

typedef enum
{
	Message1_Id = 1,
	Message2_Id = 2,
	Message3_Id = 3,
} MessageIdType;

struct DeviceHeader {
	char startchar {};
	int deviceId {};
	int length {};
};

struct DeviceBody {
	char msgId;
	char field[PAYLOADSIZE];
};

struct DeviceMessage
{
	DeviceHeader header;
	DeviceBody body;
	char checksum;
};

union Device
{
	DeviceMessage message{};
    char dataArr[sizeof(DeviceMessage)];
	Device() { 
		memset(this, 0, sizeof(*this));
		message.header.length = sizeof(*this);
	}
};
#pragma pack(pop)

