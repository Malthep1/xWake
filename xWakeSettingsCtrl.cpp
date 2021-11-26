#include "xWakeSettingsCtrl.h"




xWakeSettingsCtrl::xWakeSettingsCtrl()
{
	settingsFileRead = false;
	
}

void xWakeSettingsCtrl::readSettingsFromFile()
{
	ifstream rfile("xWakeSettings.txt");
	vector<string> toMap;
	string line;
	
	if (rfile.is_open())
	{
		while (rfile)
		{
			getline(rfile, line);
			if(line != "")
				toMap.push_back(line);
		}
	}
	
	for (string line : toMap)
	{
		createSetting(line);
	}
	
}

// Would using arrays instea of vectors be faster? Containers have set length, so don't need dynamic size.
string xWakeSettingsCtrl::createSetting(string setting)
{
	vector<string> toSet;
	vector<bool> booleans;
	vector<int> timeSettings;

	// parse the string. Put each word separately into "toSet" vector
	toSet = spliceString(setting);

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

	return newSetting.toString();
}

xWakeSetting xWakeSettingsCtrl::updateSetting(string)
{
	return xWakeSetting();
}

bool xWakeSettingsCtrl::deleteSetting(string)
{
	return false;
}

vector<string> xWakeSettingsCtrl::getSavedSettings()
{
	vector<string> toReturn;
	
	for (auto iter = settingsMap.begin(); iter != settingsMap.end(); iter++ )
	{
		toReturn.push_back(iter->second.toString());
	}
	return toReturn;
}

bool xWakeSettingsCtrl::saveSettingsToFile()
{
	// Open the settings file
	ofstream file;
	file.open("xWakeSettings.txt");
	
	// Iterate through settingsMap, write each setting to a single line
	map<string, xWakeSetting>::iterator it = settingsMap.begin();

	while (it != settingsMap.end())
	{
		file << (*it).second.toString() << endl;
		
		it++;
	}
	return false;
}

vector<string> xWakeSettingsCtrl::spliceString(string str)
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
