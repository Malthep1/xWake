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
	CLI commandLine;
	xWakeSettingsCtrl settingsController;
	//UARTCom obj declaration

	void executeCommand(string command);
};

