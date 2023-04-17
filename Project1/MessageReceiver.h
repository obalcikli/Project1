#pragma once
#include<deque>
#include<iostream>
#include"DeviceDefinition.h"

class MessageReceiver
{
public:
	std::deque<char> receiveQueue;
	Device* receivedMessage;
	int count1 = 0, count2 = 0;

	MessageReceiver() {
		receivedMessage = new Device();
	}

	~MessageReceiver() {
		delete receivedMessage;
	}

	void ProcessMessages();
};

