#pragma once
// Enables serial communication with CSerial
#include "Serial.h"
// Used to splice string
#include "common.h"
#include <string>
// Used for time functionality
#include <time.h>
// Used for uint8_t
#include <stdint.h>
#include <vector>
// uses sleep()
#include <stdlib.h>
#include <iostream>

using std::string; using std::vector; using std::stoi;

class UARTCom
{
public:
	// Does not automatically detect COM. Baudrate should be 38400 default (or same as UART in PSoC)
	UARTCom(int COM, int baudRate);
	~UARTCom();
	bool turnOn();
	void turnOff();
	bool programSystem(string);
	// Controls UART communication
	CSerial uartCtrl;

private:
	bool sendTime();
	int convertUARTProtocol(string);
	void initBuffer();

	// Need to send time, so we need appropriate time variables
	time_t timeObj;
	struct tm* timeInfo;
	vector<uint8_t>* rx_buffer;
	int COM_;
	int baudRate_;
};

