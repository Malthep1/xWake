#pragma once
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
	string createSetting(string setting);
	xWakeSetting updateSetting(string);
	bool deleteSetting(string);
	vector<string> getSavedSettings();

private:
	bool settingsFileRead;
	map<string, xWakeSetting> settingsMap;
	
	bool saveSettingsToFile();
}; 

