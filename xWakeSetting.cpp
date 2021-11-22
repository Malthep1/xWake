#include "xWakeSetting.h"

xWakeSetting::xWakeSetting()
{
	lightEngaged = false; curtainEngaged = false; speakerEngaged = false; pressurePlateEngaged = false;
	wakeUpHour = 0; wakeUpMinute = 0; awakeningPeriod = 0;
	name = "default";
}

xWakeSetting::xWakeSetting(bool light, bool curtains, bool speaker, bool pressurePlate, int hour, int minute, int duration, string newName)
{
	lightEngaged = light;  curtainEngaged = curtains; speakerEngaged = speaker; pressurePlateEngaged = pressurePlate;
	wakeUpHour = hour; wakeUpMinute = minute; awakeningPeriod = duration;
	name = newName;
}

bool xWakeSetting::getLightEngaged() const
{
	return lightEngaged;
}

bool xWakeSetting::getCurtainEngaged() const
{
	return curtainEngaged;
}

bool xWakeSetting::getSpeakerEngaged() const
{
	return speakerEngaged;
}

bool xWakeSetting::getPressurePlateEngaged() const
{
	return pressurePlateEngaged;
}

int xWakeSetting::getWakeUpHour() const
{
	return wakeUpHour;
}

int xWakeSetting::getWakeUpMinute() const
{
	return wakeUpMinute;
}

int xWakeSetting::getAwakeningPeriod() const
{
	return awakeningPeriod;
}

char xWakeSetting::boolToChar(bool val) const
{
	if (val)
		return '1';

	return '0';
}

string xWakeSetting::toString() const
{	
	string strSettings = "";
	strSettings = strSettings + boolToChar(getLightEngaged()) + " ";
	strSettings = strSettings + boolToChar(getCurtainEngaged()) + " ";
	strSettings = strSettings + boolToChar(getSpeakerEngaged()) + " ";
	strSettings = strSettings + boolToChar(getPressurePlateEngaged()) + " ";
	strSettings = strSettings + to_string(wakeUpHour) + " " + to_string(wakeUpMinute) + " " + to_string(awakeningPeriod) + " " + name;


	return strSettings;
}

