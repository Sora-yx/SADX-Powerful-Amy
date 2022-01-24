#include "pch.h"

bool rebound = false;

signed int Amy_CheckBounceAttack(CharObj2* a1, EntityData1* a2)
{
	if ((BounceButton & Controllers[a2->CharIndex].PressedButtons) == 0)
	{
		return 0;
	}
	a1->AnimationThing.Index = Anm_Amy_Rolling;
	a2->Action = Act_Amy_Bounce;
	a2->Status |= Status_Attack | Status_Ball;
	a1->Speed.y = -5.0;
	rebound = 0;
	PlayVoice(4570);
	return 1;
}

signed int Amy_PerformBounce(CharObj2* co2, EntityData1* a2)
{
	if ((BounceButton & Controllers[a2->CharIndex].PressedButtons) == 0)
	{
		return 0;
	}
	co2->AnimationThing.Index = Anm_Amy_Rolling;
	a2->Status |= Status_Attack | Status_Ball;
	a2->Action = Act_Amy_Bounce;
	co2->Speed.y = -7.0;
	PlayVoice(4570);
	return 1;
}

float getGrav = 0.0;

void Do_BounceDown(EntityData1* data1, CharObj2* co2, motionwk2* data2) {

	if ((data1->Status & (Status_OnColli | Status_Ground)) != 0)

	{
		//PlayCustomSoundVolume(CharSound_Sonic_Bounce, 1);
		data1->Action = Act_Amy_BounceUp;
		data1->Rotation.x = data2->ang_aim.x;
		data1->Rotation.z = data2->ang_aim.z;
		if (rebound) {
			co2->Speed.y = 4.0999999;
		}
		else {
			co2->Speed.y = 3.5999999;
			rebound = 1;
		}
		RumbleA(0, 1);
		return;
	}
	if ((data1->Status & 0x4000) != 0)
	{
		return;
	}
	if ((JumpButtons & Controllers[data1->CharIndex].PressedButtons) == 0)
	{
		return;
	}
	getGrav = fabs(Gravity.y);
	if (getGrav == 1.0)
	{
		getGrav = fabs(co2->_struct_a3.DistanceMax - data1->Position.y);
		if (getGrav <= 8.0)
		{
			return;
		}
	}
	co2->Speed.x = 5.0;
	data1->Action = Act_Amy_HomingAttack;
	DoHomingAttackThing(co2, data1, (EntityData2*)data2);
}

void Do_BounceUP(EntityData1* data1, CharObj2* co2, motionwk2* data2) {

	if ((data1->Status & (Status_OnColli | Status_Ground)) != 0)
	{
		if (PCheckBreak((taskwk*)data1) && co2->Speed.x > 0.0)
		{
			data1->Action = Act_Amy_Brake;
			co2->AnimationThing.Index = Anm_Amy_Brake; 
			data1->Status &= 0xFAFFu;
		}
		else
		{
			if (Amy_CheckStop(co2, data1, (EntityData2*)data2))
			{
				data1->Rotation.x = data2->ang_aim.x;
				data1->Rotation.z = data2->ang_aim.z;
				if (njScalor((const NJS_VECTOR*)&data2->spd) >= 1.0)
				{
					if (njScalor((const NJS_VECTOR*)&data2->spd) >= 2.5)
						RumbleA(0, 15);
				}
				data1->Status &= 0xFAFFu;
				co2->AnimationThing.Index = 1;
			}
			else
			{
				data1->Rotation.x = data2->ang_aim.x;
				data1->Rotation.z = data2->ang_aim.z;
				data1->Action = Act_Amy_Walk;
				data1->Status &= 0xFAFFu;
			}
		}
	}
	else if ((data1->Status & 0x4000) != 0
		|| ((JumpButtons & Controllers[data1->CharIndex].PressedButtons) == 0)
		|| (getGrav = fabs(Gravity.y), getGrav == 1.0)
		&& (getGrav = fabs(co2->_struct_a3.DistanceMax - data1->Position.y), getGrav <= 8.0))
	{
		if (!Amy_PerformBounce(co2, data1))
		{
			if (co2->AnimationThing.field_A == 14 && co2->Speed.y <= 0.0)
			{
				co2->AnimationThing.field_A = Anm_Amy_Fall; //falling
			}
		}
	}
	else
	{
		co2->Speed.x = 5.0;
		data1->Action = Act_Amy_HomingAttack;
		DoHomingAttackThing(co2, data1, (EntityData2*)data2);
	}
	return;
}