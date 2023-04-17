1- The project was develeoped with visual studio 2022. It is console application, contains
no windows dependent code.

2- Source codes are under the "Source Files" and "Header Files" directories.

3- It is assumed that there are 2 devices, which are communicating through 2 different
channels. The communication is assumed to be one way only and periodic. It is assumed
that devices are sending message bytes via the communication channel.

4- It is used two "vector<char>" to simulate the channels, which are named as "channel1"
and channel2. Two thread methods "senderfunc1()" and "senderfunc2()" push the message bytes
of "channel1" and "channel2" respectively.

5- In the file "DeviceDefinition.h", there are message defition of message bytes. It is used,
for preparing the message bytes to be sent, and it is also used for parsing the received bytes
through the channels.

6- The MessageReceiver class is used for receiving the bytes from channel1 and channel2, stores
the received bytes in a buffer order for preventing byte losses, parses them, and prints to the
screen the received packages from each individual channel, also the received message payload
is printed to the screen.

7- There are 4 threads, 2 for sending via the channel, and 2 for receiving the bytes, storing
and processing. There are two mutexes for preventing the critical section for simultaneous
reading and writing.
