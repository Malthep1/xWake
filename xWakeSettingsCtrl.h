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
	xWakeSetting updateSetting(string);
	bool deleteSetting(string);
	vector<string> getSavedSettings();
	bool saveSettingsToFile();

private:
	vector<string> spliceString(string str);
	bool settingsFileRead;
	map<string, xWakeSetting> settingsMap;
}; 

