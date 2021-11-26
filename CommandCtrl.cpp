#include "CommandCtrl.h"


CommandCtrl::CommandCtrl()
{
	settingsController.readSettingsFromFile();
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

		if (validateSetting(newSettings))
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

bool CommandCtrl::validateSetting(string setting)
{
	vector<string> settings = spliceString(setting);
	
	if (settings.size() != 7)
	{
		commandLine.print("Incorrect no of arguments in settings.");
		return false;
	}

	// Check if the words can be converted to booleans
	for (int i = 0; i < 4; i++)
	{
		if (settings[i] != "0" && settings[i] != "1")
			return false;
	}
	
	// Check if the characters in the next 3 words can be converted to integers
	for (int i = 4; i < 7; i++)
	{
		for (char c : settings[i])
		{
			if (c < '0' || c > '9')
			{
				return false;
			}
		}
	}

	// Check whether hours - mins and awakening period are within the correct intervals
	if (stoi(settings[4]) < 0 || stoi(settings[4]) > 23)
		return false;
	if (stoi(settings[5]) < 0 || stoi(settings[5]) > 59)
		return false;
	if (stoi(settings[6]) < 0 || stoi(settings[6]) > 90)
		return false;


	// If we didn't return false until now, string is good to go
	return true;
}


