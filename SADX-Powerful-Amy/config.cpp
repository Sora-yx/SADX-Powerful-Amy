#include "pch.h"

Buttons BounceButton = Buttons_X;
Buttons LightDashButton = Buttons_Y;


void ReadConfig(const char* path, const HelperFunctions& helperFunctions) {
	//Ini file Configuration
	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

	delete config;

	return;
}