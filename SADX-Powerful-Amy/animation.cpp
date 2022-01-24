#include "pch.h"

static constexpr int amyAnimcount = 4;
static AnimationFile* NewAmyAnims[amyAnimcount];
static NJS_ACTION NewAmyActions[amyAnimcount];
AnimData NewAmyAnimData[102 + amyAnimcount];
static const int AmyAnimData_Length = 102;

AnimationFile* SpinDashMotion = nullptr;
AnimationFile* RollingMotion = nullptr;
AnimationFile* UncurlMotion = nullptr;
AnimationFile* SpinBallMotion = nullptr;


AnimData SpinDashAnim = { nullptr, 78, 10, Anm_Amy_SpinDash, 0.25f, 0.20f };
AnimData RollingAnim = { nullptr, 78, 9, Anm_Amy_Rolling, 0.25f, 0.70f };
AnimData UncurlAnim = { nullptr, 78, 4, Anm_Amy_Uncurl, 0.0625f, 1.0f };
AnimData SpinBallAnim = { nullptr, 78, 3, Anm_Amy_SpinBall, 0.50f, 1.0f };

ModelInfo* JumpBallMDL = nullptr;

void Load_AmyNewMDlAnim() {

	JumpBallMDL = LoadBasicModel("JumpBall");

	LoadAnimation(&SpinDashMotion, "SpinDash", HelperFunctionsGlobal);
	SpinDashAnim.Animation = new NJS_ACTION;
	SpinDashAnim.Animation->motion = SpinDashMotion->getmotion();

	LoadAnimation(&RollingMotion, "Rolling", HelperFunctionsGlobal);
	RollingAnim.Animation = new NJS_ACTION;
	RollingAnim.Animation->motion = RollingMotion->getmotion();

	LoadAnimation(&SpinBallMotion, "SpinBall", HelperFunctionsGlobal);
	SpinBallAnim.Animation = new NJS_ACTION;
	SpinBallAnim.Animation->motion = SpinBallMotion->getmotion();

	return;

	//TODO ADD THIS
	LoadAnimation(&UncurlMotion, "Uncurl", HelperFunctionsGlobal);
	UncurlAnim.Animation = new NJS_ACTION;
	UncurlAnim.Animation->motion = UncurlMotion->getmotion();

}

//Extend Amy Animation list: We make a new list, copy the old one with a memcpy and add all the new animations after.

void InitSA2AnimHack(AnimThing* animinfo)
{
	memcpy(NewAmyAnimData, AmyAnimData, AmyAnimData_Length * sizeof(AnimData_t));

	SpinDashAnim.Animation->object = AMY_OBJECTS[0];
	NewAmyAnimData[Anm_Amy_SpinDash] = SpinDashAnim;

	RollingAnim.Animation->object = AMY_OBJECTS[0];
	NewAmyAnimData[Anm_Amy_Rolling] = RollingAnim;

	SpinBallAnim.Animation->object = JumpBallMDL->getmodel();
	NewAmyAnimData[Anm_Amy_SpinBall] = SpinBallAnim;
}

void Init_AmyNewAnim() {
	WriteData((AnimData**)0x48acd8, NewAmyAnimData);
	WriteData((AnimData**)0x485f8F, NewAmyAnimData);
							
	WriteData((AnimData**)0x485caB, NewAmyAnimData);
	WriteData((AnimData**)0x486011, NewAmyAnimData);	
			
	WriteData((AnimData**)0x488777, NewAmyAnimData);	

	//WriteData((AnimData**)0x48717A, NewAmyAnimData);
	return;
}