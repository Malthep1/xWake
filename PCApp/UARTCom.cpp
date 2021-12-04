#include "UARTCom.h"

UARTCom::UARTCom(int COM, int baudRate)
{
	initBuffer();
	baudRate_ = baudRate;
	COM_ = COM;
	timeInfo = { 0 };
	timeObj = 0;
}

UARTCom::~UARTCom()
{
	delete rx_buffer;
}

bool UARTCom::turnOn()
{
	if (uartCtrl.Open(COM_, baudRate_))
		return true;
	else
		return false;
}

void UARTCom::turnOff()
{
	uartCtrl.Close();
}

bool UARTCom::programSystem(string setting)
{
	// First try to send time, if succesful, send the rest of the characters
	if (sendTime())
	{
		convertUARTProtocol(setting);
		int charactersSent;
		char toSend[5];
		// convert uint8_t buffer to char and send them
		for (int i = 0; i < rx_buffer->size(); i++)
		{
			toSend[i] = (char)rx_buffer->at(i);
		}
		charactersSent = uartCtrl.SendData(toSend, 5);
		if (charactersSent == 5)
		{
			std::cout << timeInfo->tm_hour << ":" << timeInfo->tm_min << ":" << timeInfo->tm_sec << std::endl;
			return true;
		}
		else
			return false;
			
	}
	else
	{
		return false;
	}
}

bool UARTCom::sendTime()
{
	
	time(&timeObj);
	timeInfo = localtime(&timeObj);
	char toSend[4];
	// Special code for sending local time. Works only with x10 transmitter
	toSend[0] = 0xFB;
	toSend[1] = timeInfo->tm_hour;
	toSend[2] = timeInfo->tm_min;
	toSend[3] = timeInfo->tm_sec;
	int charactersSent = uartCtrl.SendData(toSend, 4);
	if (charactersSent == 4)
	{
		Sleep(3000);
		return true;
	}
		return false;
}

int UARTCom::convertUARTProtocol(string setting)
{
	// Special code for sending data to store. Works only with x10 transmitter
	rx_buffer->at(0) = 0xFA;
	vector<string> setToConvert = common::spliceString(setting);
	uint8_t toSend = 0;

	for (int i = 0; i < 4; i++)
	{
		toSend = toSend | (stoi(setToConvert[i]) << i);
	}
	rx_buffer->at(1) = toSend;

	for (uint8_t i = 4; i < 7; i++)
	{
		toSend = stoi(setToConvert[i]);
		rx_buffer->at(i - 2) = toSend;
	}

	return 0;
}

void UARTCom::initBuffer()
{
	rx_buffer = new vector<uint8_t>(5);
}
