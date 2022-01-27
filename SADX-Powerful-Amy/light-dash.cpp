#include "pch.h"

Trampoline* Ring_Main_t;

Bool Amy_CheckLightDash(CharObj2* a1, EntityData1* a2)
{
	Bool result; // eax

	if ((Controllers[a2->CharIndex].PressedButtons & LightDashButton) == 0 || (a2->Status & Status_LightDash) == 0)
	{
		return 0;
	}

	a2->Status &= ~2u;
	a2->Action = Act_Amy_LightDash;
	a1->AnimationThing.Index = 16;
	a1->LightdashTime = 10;
	a1->LightdashTimer = 0;
	a1->Speed.x = 8.0;
	a2->Status = a2->Status & ~0x100 | 0x400;
	PlaySound(764, 0, 0, 0);

	DoSoundQueueThing(0x4CB);
	int rng = rand() % 2;

	if (rng > 0)
		PlayVoice(1743);

	result = 1;

	return result;
}

void StopLightDash(EntityData1* data, CharObj2* co2)
{
	data->Action = Act_Amy_Brake; //stop
	float speed_x = co2->Speed.x;
	co2->AnimationThing.Index = Anm_Amy_Brake;
	if (speed_x > 2.0)
	{
		co2->Speed.x = 2.0;
	}
	data->Status &= ~Status_LightDash;
	data->Status &= ~4u;
	co2->LightdashTime = 0;
	DoSoundQueueThing(764);
}

void DoLightDashAction(EntityData1* data, CharObj2* co2, EntityData2* data2) {

	__int16 ld_time;
	__int16 ld_timer;
	NJS_VECTOR calcPos;
	float pos_length;
	NJS_VECTOR idk;

	if (Amy_NAct(co2, data2, data))
	{
		co2->LightdashTime = 0;
		DoSoundQueueThing(764);
		if (co2->Speed.x > 2.0)
		{
			co2->Speed.x = 2.0;         // 2.0
		}
		data->Status &= ~Status_LightDash;
		data->Status &= ~4u;
	}
	else
	{
		ld_time = co2->LightdashTime;
		co2->LightdashTime = ld_time - 1;
		if (ld_time <= 0)
		{
			StopLightDash(data, co2);
			return;
		}
		ld_timer = co2->LightdashTimer;
		co2->LightdashTimer = ld_timer + 1;
		if (ld_timer > 360)
		{
			StopLightDash(data, co2);
			return;
		}
		CollisionInfo* col = data->CollisionInfo->CollidingObject;
		if (col)
		{
			ObjectMaster* v17 = col->Object;
			if (v17)
			{
				if (v17->Data1->Unknown == 11)
				{
					co2->LightdashTimer = 0;
				}
			}
		}
		GetBufferedPositionAndRotation(data->CharIndex, 1, &idk, 0);
		calcPos.z = idk.z - data->Position.z;
		calcPos.y = idk.y - data->Position.y;
		calcPos.x = idk.x - data->Position.x;
		pos_length = calcPos.x * calcPos.x + calcPos.y * calcPos.y + calcPos.z * calcPos.z;

		if (squareroot(pos_length) <= 1.5)
		{
			StopLightDash(data, co2);
		}
	}
	return;
}

void Ring_Main_r(ObjectMaster* obj) {

	if (IsPlayerInsideSphere(&obj->Data1->Position, 20) && EntityData1Ptrs[0]->CharID == Characters_Amy)
	{
		EntityData1Ptrs[0]->Status |= Status_LightDash;
	}

	ObjectFunc(original, Ring_Main_t->Target());
	original(obj);
}

void init_LightDashHack() {
	Ring_Main_t = new Trampoline((int)Ring_Main, (int)Ring_Main + 0x6, Ring_Main_r);
}