#include "pch.h"

Buttons BounceButton = Buttons_B;
Buttons LightDashButton = Buttons_Y;
Buttons SpinDashButton = Buttons_X;
bool isHomingAttack = true;

Buttons CustomButtons[3]{
	Buttons_X,
	Buttons_Y,
	Buttons_B
};

void ReadConfig(const char* path, const HelperFunctions& helperFunctions) {
	//Ini file Configuration
	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

	BounceButton = CustomButtons[config->getInt("General", "BounceButton", 2)];
	LightDashButton = CustomButtons[config->getInt("General", "LightDashButton", 1)];
	SpinDashButton = CustomButtons[config->getInt("General", "SpinDashButton", 0)];
	isHomingAttack = config->getBool("General", "isHomingAttack", true);
	delete config;

	return;
}