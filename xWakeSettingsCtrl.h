#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "xWakeSetting.h"
using namespace std;
class xWakeSettingsCtrl
{
public:
	xWakeSettingsCtrl();
	// Read/Write to file
	void readSettingsFromFile();
	bool saveSettingsToFile();

	// Checks if settings were input in a correct format
	// Format : [bool bool bool bool int int int]
	bool validateSetting(string setting);
	string createSetting(string setting);
	bool updateSetting(string name, string setting);
	bool deleteSetting(string name);
	vector<string> getSavedSettings();

private:
	// Split a string into separate words
	vector<string> spliceString(string str);
	// Stores all saved settings in a map
	map<string, xWakeSetting> settingsMap;
}; 

