#include "MessageReceiver.h"
#include <vector>

void MessageReceiver::ProcessMessages() {

	if (receiveQueue.size() == 0)
		return;
	std::vector<char> tmpbuf;
	tmpbuf.reserve(receivedMessage->message.header.length);
	while ( receiveQueue.size() > 0 )
	{
		tmpbuf.push_back (receiveQueue.front() );
		//receivedMessage.dataArr[i] = receiveQueue.front();
		if (!receiveQueue.empty())
			receiveQueue.pop_front();
	}
	copy(tmpbuf.begin(), tmpbuf.end(), receivedMessage->dataArr);

	if (receivedMessage->message.header.deviceId == Device1_Id) {
		count1++;
		std::cout << "message received from Device-1, package total: " << count1 << std::endl;
		std::cout << "package content: ";
		for (int i = 0; i < PAYLOADSIZE; i++) {
			std::cout << receivedMessage->message.body.field[i] << ",";
		}
		std::cout << std::endl << "-----------------------------------------\n";
	}
	else if (receivedMessage->message.header.deviceId == Device2_Id) {
		count2++;
		std::cout << "message received from Device-2, package total: " << count2 << std::endl;
		std::cout << "package content: ";
		for (int i = 0; i < PAYLOADSIZE; i++) {
			std::cout << receivedMessage->message.body.field[i] << ",";
		}
		std::cout << std::endl << "-----------------------------------------\n";
	}
}
