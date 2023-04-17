#include <iostream>
#include <thread>
#include "DeviceDefinition.h"
#include "MessageReceiver.h"
#include <vector>
#include <mutex>

using namespace std;

vector<char> channel1;
vector<char> channel2;

std::mutex mutex_1;
std::mutex mutex_2;

void senderfunc1(char* data, int size) {

	while (true)
	{
		mutex_1.lock();
		for (int i = 0; i < size; i++) {
			channel1.push_back(data[i]);
		}
		mutex_1.unlock();
		std::this_thread::sleep_for(800ms);
	}
}

void senderfunc2(char* data, int size) {

	while (true)
	{
		mutex_2.lock();
		for (int i = 0; i < size; i++) {
			channel2.push_back(data[i]);
		}
		mutex_2.unlock();
		std::this_thread::sleep_for(900ms);
	}
}

void receiverfunc1(MessageReceiver* receiver)
{
	while (true) {

		mutex_1.lock();
		while ( !channel1.empty() )
		{
			receiver->receiveQueue.push_back(channel1[0]);
			channel1.erase(channel1.begin());
		}
		mutex_1.unlock();

		receiver->ProcessMessages();
		
		//std::this_thread::sleep_for(900ms);
	}
}

void receiverfunc2(MessageReceiver* receiver)
{
	while (true) {

		mutex_2.lock();
		while (!channel2.empty())
		{
			receiver->receiveQueue.push_back(channel2[0]);
			channel2.erase(channel2.begin());
		}
		mutex_2.unlock();

		receiver->ProcessMessages();
		//std::this_thread::sleep_for(800ms);
	}
}

int main(void) {
	
	//prepare device package data for device-1
	Device device1;
	device1.message.header.startchar = 0xA;
	device1.message.header.deviceId = Device1_Id;
	device1.message.body.msgId = Message1_Id;
	for (int i = 0, y = 'a'; i < PAYLOADSIZE; i++)
		device1.message.body.field[i] = y++;

	//prepare device package data for device-2
	Device device2;
	device2.message.header.startchar = 0xB;
	device2.message.header.deviceId = Device2_Id;
	device2.message.body.msgId = Message2_Id;
	for (int i = 0, y = 'k'; i < PAYLOADSIZE; i++)
		device2.message.body.field[i] = y++;

	channel1.reserve(device1.message.header.length * 1000);
	channel2.reserve(device2.message.header.length * 1000);

	MessageReceiver receiver1;
	MessageReceiver receiver2;

	std::thread t1(senderfunc1, device1.dataArr, device1.message.header.length);
	std::thread t2(receiverfunc1, &receiver1);

	std::thread t3(senderfunc2, device2.dataArr, device2.message.header.length);
	std::thread t4(receiverfunc2, &receiver2);
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();

	return 0;
}