#include "pch.h"


void LoadAnimation(AnimationFile** info, const char* name, const HelperFunctions& helperFunctions)
{
	PrintDebug("[Powerful Amy] Loading Animation: %s... ", name);

	std::string fullPath = "system\\anim\\";
	fullPath = fullPath + name + ".saanim";

	AnimationFile* anm = new AnimationFile(helperFunctions.GetReplaceablePath(fullPath.c_str()));

	if (anm->getmodelcount() == 0)
	{
		PrintDebug("Failed!\n");
		delete anm;
		*info = nullptr;
	}
	else
	{
		*info = anm;
		PrintDebug("Done.\n");
	}

};

ModelInfo* LoadBasicModel(const char* name) {
	PrintDebug("[Powerful Amy] Loading basic model: %s... ", name);

	std::string fullPath = "system\\mdl\\";
	fullPath = fullPath + name + ".sa1mdl";

	ModelInfo* mdl = new ModelInfo(HelperFunctionsGlobal.GetReplaceablePath(fullPath.c_str()));

	if (mdl->getformat() != ModelFormat_Basic) {
		PrintDebug("Failed!\n");
		delete mdl;
		return nullptr;
	}

	PrintDebug("Done.\n");
	return mdl;
}

void FreeMDL(ModelInfo* pointer) {
	if (pointer) {
		PrintDebug("[SHM] Freeing model: %s... \n", pointer->getdescription().c_str());
		delete(pointer);
		pointer = nullptr;
	}
}

void __cdecl PlayerClearSpeed(EntityData2* a1, CharObj2* a2)
{
	if (a2)
	{
		a2->Speed.z = 0.0;
		a2->Speed.y = 0.0;
		a2->Speed.x = 0.0;
	}
	if (a1)
	{
		a1->VelocityDirection.z = 0.0;
		a1->VelocityDirection.y = 0.0;
		a1->VelocityDirection.x = 0.0;
	}
}

Buttons GetHammerAttackButton() {

	if (HammerAttackButton > 0)
		return HammerAttackButton;

	return AttackButtons;
}

bool isNewTrick() {

	HMODULE dll = GetModuleHandle(L"sadx-new-tricks");

	if (dll)
		return true;

	return false;
}

void njRotateX_(Angle x) {
	if (x) {
		njRotateX(_nj_current_matrix_ptr_, x);
	}
}

void njRotateY_(Angle y) {
	if (y) {
		njRotateY(_nj_current_matrix_ptr_, y);
	}
}

void njRotateZ_(Angle z) {
	if (z) {
		njRotateZ(_nj_current_matrix_ptr_, z);
	}
}