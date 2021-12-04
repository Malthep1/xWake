#include "common.h"

vector<string> common::spliceString(string str)
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
