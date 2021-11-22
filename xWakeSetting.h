#pragma once
#include <string>
using namespace std;
class xWakeSetting
{
public:
	xWakeSetting();
	xWakeSetting(bool, bool, bool, bool, int, int, int, string);
private:
	bool lightEngaged;
	bool curtainEngaged;
	bool speakerEngaged;
	bool pressurePlateEngaged;
	int wakeUpHour;
	int wakeUpMinute;
	int awakeningPeriod;
	string name;

	char boolToChar(bool val) const;
public:
	bool getLightEngaged() const;
	bool getCurtainEngaged() const;
	bool getSpeakerEngaged() const;
	bool getPressurePlateEngaged() const;
	int getWakeUpHour() const;
	int getWakeUpMinute() const;
	int getAwakeningPeriod() const;

	// Convert all data to a single string
	string toString() const;

};

