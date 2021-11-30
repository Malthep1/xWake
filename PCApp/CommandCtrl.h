#pragma once
#include "CLI.h"
#include "xWakeSettingsCtrl.h"
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
	//UARTCom obj declaration

	void executeCommand(string command);
	// splices the string with delimiter ' ' and returns each word separately in a vector
	vector<string> spliceString(string str);
	// Returns true if settings parameter follows the specific format
	// Format: bool bool bool bool int int int

};

