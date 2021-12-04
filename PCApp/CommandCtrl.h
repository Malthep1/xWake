#pragma once
#include "CLI.h"
#include "xWakeSettingsCtrl.h"
#include "UARTCom.h"
#include <string>

class CommandCtrl

{
public:
	// The main controller class of the PCApp
	// Gets commands from CLI, and executes them
	// Available settings : [new, update, delete, list, exit (quit)]
	// TODO : program setting on a device

	CommandCtrl();
	// running can be used in the main loop. Disabled by "exit" command
	bool running = true;
	void getNextCommand();
	
private:
	// These are automatically created in default constructor
	CLI commandLine;
	xWakeSettingsCtrl settingsController;

	void executeCommand(string command);

};

