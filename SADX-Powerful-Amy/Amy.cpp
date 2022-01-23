#include "pch.h"
#include "abilities.h"

Trampoline* Amy_Exec_t = nullptr;
Trampoline* Amy_RunsActions_t = nullptr;
Trampoline* Sonic_Main_t = nullptr;

void Amy_RunsActions_r(EntityData1* data, EntityData2* data2, CharObj2* co2)
{

	switch (data->Action)
	{
	case Act_Amy_Stand:
	case Act_Amy_Walk:

		if (Amy_ChargeSpindash(co2, data))
		{
			return;
		}

		break;
	case Act_Amy_SpinDash:
		Do_SpinDash(co2, data, data2);
		break;
	case Act_Amy_Rolling:
		DoRolling(data, co2, data2);
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

	co2->SpindashSpeed = co2->SpindashSpeed;

}

void init_AmyHacks() {
	Amy_Exec_t = new Trampoline((int)Amy_Main, (int)Amy_Main + 0x7, Amy_Main_r);
	Amy_RunsActions_t = new Trampoline(0x488880, 0x488888, Amy_RunsActions_r);
	Sonic_Main_t = new Trampoline((int)Sonic_Main, (int)Sonic_Main + 0x7, Sonic_Main_r);
}