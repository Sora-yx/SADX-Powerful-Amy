#include "pch.h"

Buttons BounceButton = Buttons_B;
Buttons LightDashButton = Buttons_Y;
Buttons SpinDashButton = Buttons_X;
bool isHomingAttack = true;

PhysicsData Amy_SA2Physics = { 60, 2, 16, 16, 1.3, 0.6,	1.3, 3, 0.23, 0.46, 1.39, 2.3, 3.7, 5.09, 0.076, 0.048, 0.031, -0.06, -0.18, -0.17, -0.028, -0.008, -0.01, -0.4, -0.1, -0.6, -0.2825, 0.3, 4, 10, 0.08, 7,	5.4 };
PhysicsData Amy_HeroesPhysics = { 60, 2, 32, 32, 4.5, 0.6, 1.66, 3, 0.23, 0.46, 1.39, 2.3, 3.7, 5.09, 0.076, 0.09, 0.031, -0.06, -0.18, -0.14, -0.028, -0.008, -0.01, -0.4, -0.1, -0.6, -0.2825, 0.3, 4, 10, 0.08, 7, 5.4 };


enum AmyPhysicsE {
	SADXPhysics,
	SA2Physics,
	HeroesPhysics
};

int amyPhysics = SA2Physics;

Buttons CustomButtons[3]{
	Buttons_X,
	Buttons_Y,
	Buttons_B
};

void ReadConfig(const char* path, const HelperFunctions& helperFunctions) {
	//Ini file Configuration
	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

	amyPhysics = config->getInt("General", "amyPhysics", SA2Physics);
	isHomingAttack = config->getBool("General", "isHomingAttack", true);

	BounceButton = (Buttons)config->getInt("Controller", "BounceButton", Buttons_B);
	LightDashButton = (Buttons)config->getInt("Controller", "LightDashButton", Buttons_Y);
	SpinDashButton = (Buttons)config->getInt("Controller", "SpinDashButton", Buttons_X);

	delete config;

	if (amyPhysics == SA2Physics)
	{
		memcpy(&PhysicsArray[Characters_Amy], &Amy_SA2Physics, sizeof(PhysicsArray[Characters_Amy]));
	}
	if (amyPhysics == HeroesPhysics)
	{
		memcpy(&PhysicsArray[Characters_Amy], &Amy_HeroesPhysics, sizeof(PhysicsArray[Characters_Amy]));
	}

	return;
}