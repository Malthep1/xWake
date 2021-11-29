#include "CommandCtrl.h"


CommandCtrl::CommandCtrl()
{

}

void CommandCtrl::getNextCommand()
{
	string command = commandLine.awaitCommand();
	
	executeCommand(command);
}

void CommandCtrl::executeCommand(string input)
{
	vector<string> command;
	string word;

	// parse the string
	string delim = " ";
	string::size_type position;

	while((position = input.find(delim)) != string::npos)
	{
		word = input.substr(0, position);
		input.erase(0, position + delim.length());
		
		command.push_back(word);
	}
	command.push_back(input);

	if (command[0] == "new")
	{
		commandLine.print("Creating new setting: " + command[1]);
		commandLine.print("Please Input settings: ");
		string newSettings = commandLine.awaitSettings();
		
		// TODO: Validate settings here.

		settingsController.createSetting(newSettings + " " + command[1]);
	}
	else if (command[0] == "update")
	{
		// TODO update
		commandLine.print("Updating setting: " + command[1]);
	}
	else if (command[0] == "delete")
	{
		// TODO delete
		commandLine.print("Deleting setting: " + command[1]);
	}
	else if (command[0] == "quit" || command[0] == "exit")
	{
		running = false;
	}
	else
	{
		commandLine.print("Unrecognized command.");
		commandLine.print("Syntax: {command , name} ");
	}
}
