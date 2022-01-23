#include "pch.h"
#include "abilities.h"

ModelInfo* JumpBallMDL = nullptr;
AnimationFile* SpinDashMotion = nullptr;
AnimationFile* RollingMotion = nullptr;
AnimationFile* UncurlMotion = nullptr;
AnimationFile* SpinBallMotion = nullptr;

Trampoline* Amy_Exec_t = nullptr;
Trampoline* Amy_RunsActions_t = nullptr;

Trampoline* Sonic_Main_t = nullptr;

AnimData SpinDashAnim = { nullptr, 78, 10, Anm_Amy_SpinDash, 0.25f, 0.20f };
AnimData RollingAnim = { nullptr, 78, 9, Anm_Amy_Rolling, 0.25f, 0.70f };
AnimData UncurlAnim = { nullptr, 78, 4, Anm_Amy_Uncurl, 0.0625f, 1.0f };
AnimData SpinBallAnim = { nullptr, 78, 3, Anm_Amy_SpinBall, 0.50f, 1.0f };

NJS_TEXNAME AmyEffR_TEXNAMES[40];
NJS_TEXLIST AmyEffR_TEXLIST = { arrayptrandlength(AmyEffR_TEXNAMES) };

static Trampoline* LoadLevelObject_t = nullptr;

void Amy_RunsActions_r(EntityData1* data, EntityData2* data2, CharObj2* co2)
{

	auto mwp = (motionwk2*)data2;

	switch (data->Action)
	{
	case Act_Amy_Stand:
	case Act_Amy_Walk:

		if (Amy_ChargeSpindash(co2, data))
		{
			return;
		}

		break;
	case Act_Amy_Jump:

		if (CheckHomingAttack(co2, data, data2))
			return;

		if (Amy_CheckBounceAttack(co2, data))
			return;

		break;
	case Act_Amy_SpinDash:
		Do_SpinDash(co2, data, data2);
		break;
	case Act_Amy_Rolling:
		DoRolling(data, co2, data2);
		break;
	case Act_Amy_HomingAttack:
		DoHomingAttack(co2, data, data2);
		break;
	case Act_Amy_Bounce:
		if (!Amy_NAct(co2, data2, data))
		{
			Do_BounceDown(data, co2, mwp);
		}
		break;
	case Act_Amy_BounceUp:
		if (!Amy_NAct(co2, data2, data))
		{
			Do_BounceUP(data, co2, mwp);
		}
		break;
	}

	FunctionPointer(void, original, (EntityData1* data, EntityData2* data2, CharObj2* co2), Amy_RunsActions_t->Target());
	return original(data, data2, co2);
}

void Amy_Main_r(ObjectMaster* obj)
{
	task* tsk = (task*)obj;
	EntityData1* data = (EntityData1*)tsk->twp;
	auto wp = (taskwk*)tsk->twp; // main task containing position, rotation, scale
	auto mwp = (motionwk2*)tsk->mwp; // task containing movement information
	auto pwk = (playerwk*)mwp->work.ptr; // physics, animation info, and countless other things
	auto co2 = (CharObj2*)pwk;
	auto data2 = (EntityData2*)mwp;

	switch (data->Action)
	{
	case Act_Amy_SpinDash:
        PGetRotation(wp, mwp, pwk);
        PGetBreak(wp, mwp, pwk);
		PGetSpeed(wp, mwp, pwk);
        PSetPosition(wp, mwp, pwk);
        PResetPosition(wp, mwp, pwk);
		break;
	case Act_Amy_Rolling:
		PGetRotation(wp, mwp, pwk);
		PGetInertia(wp, mwp, pwk);
		PGetSpeed(wp, mwp, pwk);
		PSetPosition(wp, mwp, pwk);
		PResetPosition(wp, mwp, pwk);
		break;
	case Act_Amy_HomingAttack:
		PResetAngle(wp, mwp, pwk);
		Sonic_HomingAttackThing(co2, data, data2);
		PSetPosition(wp, mwp, pwk);
		PResetPosition(wp, mwp, pwk);
		//LoadSonicDashTrail(data);
		co2->SonicSpinTimeProbably |= 1u;
		//PSetSpinDashEffect(data);
		break;
	case Act_Amy_Bounce:
	case Act_Amy_BounceUp:
		PResetAngle(wp, mwp, pwk);
		PGetGravity(wp, mwp, pwk);
		PGetAccelerationAir(wp, mwp, pwk);
		PGetSpeed(wp, mwp, pwk);
		PSetPosition(wp, mwp, pwk);
		PResetPosition(wp, mwp, pwk);
		//LoadObject(LoadObj_Data1, 6, SonicDashTrail_Init)->Data1->CharIndex = data->CharIndex;
		break;
	}

	ObjectFunc(original, Amy_Exec_t->Target());
	original(obj);
}

void __cdecl Sonic_Main_r(ObjectMaster* obj)
{
	ObjectFunc(original, Sonic_Main_t->Target());
	original(obj);

	EntityData1* data = (EntityData1*)obj->Data1;
	auto ed2 = (EntityData2*)obj->Data2;
	auto co2 = ed2->CharacterData;
}

void Load_AmyNewMDlAnim() {

	JumpBallMDL = LoadBasicModel("JumpBall");

	return;

	LoadAnimation(&SpinDashMotion, "SpinDash", HelperFunctionsGlobal);
	SpinDashAnim.Animation = new NJS_ACTION;
	SpinDashAnim.Animation->motion = SpinDashMotion->getmotion();

	LoadAnimation(&RollingMotion, "Rolling", HelperFunctionsGlobal);
	RollingAnim.Animation = new NJS_ACTION;
	RollingAnim.Animation->motion = RollingMotion->getmotion();

	LoadAnimation(&UncurlMotion, "Uncurl", HelperFunctionsGlobal);
	UncurlAnim.Animation = new NJS_ACTION;
	UncurlAnim.Animation->motion = UncurlMotion->getmotion();

	LoadAnimation(&SpinBallMotion, "SpinBall", HelperFunctionsGlobal);
	SpinBallAnim.Animation = new NJS_ACTION;
	SpinBallAnim.Animation->motion = UncurlMotion->getmotion();
}

void __cdecl LoadLevelObject_r() {

	LoadPVM("SON_EFF", &SON_EFF_TEXLIST);
	LoadPVM("amy_efftex", &AmyEffR_TEXLIST);

	auto original = reinterpret_cast<decltype(LoadLevelObject_r)*>(LoadLevelObject_t->Target());
	original();
}

void init_AmyHacks() {
	Amy_Exec_t = new Trampoline((int)Amy_Main, (int)Amy_Main + 0x7, Amy_Main_r);
	Amy_RunsActions_t = new Trampoline(0x488880, 0x488888, Amy_RunsActions_r);
	Sonic_Main_t = new Trampoline((int)Sonic_Main, (int)Sonic_Main + 0x7, Sonic_Main_r);
	LoadLevelObject_t = new Trampoline((int)LoadLevelObject, (int)LoadLevelObject + 0x7, LoadLevelObject_r);

	Load_AmyNewMDlAnim();
	return;
}