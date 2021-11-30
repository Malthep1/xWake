#include "xWakeSettingsCtrl.h"




xWakeSettingsCtrl::xWakeSettingsCtrl()
{

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

bool xWakeSettingsCtrl::updateSetting(string name, string setting)
{
	map<string, xWakeSetting>::iterator it;
	it = settingsMap.find(name);
	if (it == settingsMap.end())
	{
		cout << "Failed to find \"" + name + "\"" << endl;
		return false;
	}
	settingsMap.erase(it);
	createSetting(setting);
	saveSettingsToFile();
	return true;
}

bool xWakeSettingsCtrl::deleteSetting(string name)
{
	map<string, xWakeSetting>::iterator it;
	it = settingsMap.find(name);
	if (it == settingsMap.end())
	{
		cout << "Failed to find \"" + name + "\"" << endl;
		return false;
	}
	settingsMap.erase(it);
	saveSettingsToFile();
	return true;
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


bool xWakeSettingsCtrl::validateSetting(string setting)
{
	vector<string> settings = spliceString(setting);

	if (settings.size() != 7)
	{
		return false;
	}

	// Check if the words can be converted to booleans
	for (int i = 0; i < 4; i++)
	{
		if (settings[i] != "0" && settings[i] != "1")
			return false;
	}

	// Check if the characters in the next 3 words can be converted to integers
	for (int i = 4; i < 7; i++)
	{
		for (char c : settings[i])
		{
			if (c < '0' || c > '9')
			{
				return false;
			}
		}
	}

	// Check whether hours - mins and awakening period are within the correct intervals
	if (stoi(settings[4]) < 0 || stoi(settings[4]) > 23)
		return false;
	if (stoi(settings[5]) < 0 || stoi(settings[5]) > 59)
		return false;
	if (stoi(settings[6]) < 0 || stoi(settings[6]) > 90)
		return false;


	// If we didn't return false until now, string is good to go
	return true;
}

