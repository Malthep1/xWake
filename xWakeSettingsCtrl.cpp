#include "xWakeSettingsCtrl.h"
#include <iostream>



xWakeSettingsCtrl::xWakeSettingsCtrl()
{
	settingsFileRead = false;
}

void xWakeSettingsCtrl::readSettingsFromFile()
{
}

// Would using arrays instea of vectors be faster? Containers have set length, so don't need dynamic size.
string xWakeSettingsCtrl::createSetting(string setting)
{
	vector<string> toSet;
	vector<bool> booleans;
	vector<int> timeSettings;
	string word;
	string delim = " ";
	string::size_type position;

	// parse the string. Put each word separately into "toSet" vector
	while ((position = setting.find(delim)) != string::npos)
	{
		word = setting.substr(0, position);
		setting.erase(0, position + delim.length());

		toSet.push_back(word);
	}
	toSet.push_back(setting);

	// Check the first 4 words, convert to booleans and put them in a vector
	for (int i = 0; i < 4; i++)
	{
		string examined = toSet[i];
		if (examined == "1")
			booleans.push_back(true);
		else if (examined == "0")
			booleans.push_back(false);
	}

	// Check the next 3 words, convert to int and put them in a vector
	for (int i = 4; i < 7; i++)
		timeSettings.push_back(stoi(toSet[i]));

	// The last word has to be a name string
	xWakeSetting newSetting(booleans[0], booleans[1], booleans[2], booleans[3], timeSettings[0], timeSettings[1], timeSettings[2], toSet[7]);
	settingsMap[toSet[7]] = newSetting;

	// DEBUG
	//cout << booleans[0] << " " << booleans[1] << " " << booleans[2] << " " << booleans[3] << " ";
	//cout << timeSettings[0] << " " << timeSettings[1] << " " << timeSettings[2] << " ";
	cout << newSetting.toString() << endl;

	return newSetting.toString();
}

bool xWakeSettingsCtrl::deleteSetting(string)
{
	return false;
}
