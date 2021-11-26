#pragma once
#include "CLI.h"
#include "xWakeSettingsCtrl.h"
#include <string>
class CommandCtrl
{
public:
	CommandCtrl();
	void getNextCommand();
	bool running = true;

private:
	// These are automatically created in default constructor
	CLI commandLine;
	xWakeSettingsCtrl settingsController;
	//UARTCom obj declaration

	void executeCommand(string command);
	// splices the string with delimiter ' ' and returns each word separately in a vector
	vector<string> spliceString(string str);
	// Returns true if settings parameter follows the specific format
	// Format: bool bool bool bool int int int

};

