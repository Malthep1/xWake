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
