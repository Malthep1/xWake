#include "CommandCtrl.h"


CommandCtrl::CommandCtrl()
{
	commandLine.print("xWake application initialized.");
	settingsController.readSettingsFromFile();
	commandLine.print("Settings loaded.");
}

void CommandCtrl::getNextCommand()
{
	string command = commandLine.awaitCommand();
	
	executeCommand(command);
}

void CommandCtrl::executeCommand(string input)
{
	vector<string> command = spliceString(input);

	if (command[0] == "new")
	{
		commandLine.print("Creating new setting: " + command[1]);
		commandLine.print("Please Input settings: ");
		string newSettings = commandLine.awaitSettings();

		if (settingsController.validateSetting(newSettings))
		{
			commandLine.print("New setting created: ");
			settingsController.createSetting(newSettings + " " + command[1]);
			settingsController.saveSettingsToFile();
		}

		else
			commandLine.print("Incorrect settings format || Numbers are not within the allowed interval");
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
	else if (command[0] == "list")
	{
		// TODO list
		vector<string> allSettings = settingsController.getSavedSettings();
		commandLine.print("Following settings are available: ");
		commandLine.print(allSettings);
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

vector<string> CommandCtrl::spliceString(string str)
{
	vector<string> splicedString;
	string word;

	// parse the string
	string delim = " ";
	string::size_type position;

	while ((position = str.find(delim)) != string::npos)
	{
		word = str.substr(0, position);
		str.erase(0, position + delim.length());

		splicedString.push_back(word);
	}
	splicedString.push_back(str);
	return splicedString;
}


