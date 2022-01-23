#include "pch.h"

void LoadAnimation(AnimationFile** info, const char* name, const HelperFunctions& helperFunctions)
{
	std::string fullPath = "system\\anim\\";
	fullPath = fullPath + name + ".saanim";

	AnimationFile* anm = new AnimationFile(helperFunctions.GetReplaceablePath(fullPath.c_str()));

	if (anm->getmodelcount() == 0)
	{
		delete anm;
		*info = nullptr;
	}
	else
	{
		*info = anm;
	}
};

ModelInfo* LoadBasicModel(const char* name) {
	PrintDebug("Loading basic model: %s... ", name);

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