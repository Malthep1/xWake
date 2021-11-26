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
	void readSettingsFromFile();
	bool validateSetting(string setting);
	string createSetting(string setting);
	bool updateSetting(string name, string setting);
	bool deleteSetting(string name);
	vector<string> getSavedSettings();
	bool saveSettingsToFile();

private:
	vector<string> spliceString(string str);
	bool settingsFileRead;
	map<string, xWakeSetting> settingsMap;
}; 

