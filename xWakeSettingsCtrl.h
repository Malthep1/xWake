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
	// updateSetting
	bool deleteSetting(string);

private:
	bool settingsFileRead;
	map<string, xWakeSetting> settingsMap;
};

