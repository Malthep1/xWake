#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class CLI
{
public:
	CLI();
	void print(string toPrint) const;
	void print(vector<string> toPrint) const;
	string awaitCommand() const;
	string awaitSettings() const;

};

