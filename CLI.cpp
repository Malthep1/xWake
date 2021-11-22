#include "CLI.h"

CLI::CLI()
{
	// CLI contains no attributes or dynamic mem allocation so the constructor is empty
}

void CLI::print(string toPrint) const
{
	cout << toPrint << endl;
}

void CLI::print(vector<string> toPrint) const
{
	for (string element : toPrint)
		cout << element << endl;
}

string CLI::awaitCommand() const
{
	string input;
	getline(cin, input);
	return input;
}

string CLI::awaitSettings() const
{
	string input;
	getline(cin, input);
	return input;
}
