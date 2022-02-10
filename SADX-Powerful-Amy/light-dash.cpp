#include "pch.h"

HomingAttackTarget* isLightDashAllowed(CharObj2* co2, EntityData1* a2, float distance)
{
	HomingAttackTarget* v3;
	EntityData1* targetData; 
	CollisionInfo* v6;
	CollisionData* targetDataColArray; 
	double v8;
	float v9;
	float v10;
	double v11; 
	double v12; 
	NJS_VECTOR* v13; 
	HomingAttackTarget* i; 
	float v15; 
	NJS_VECTOR a1; 
	NJS_VECTOR a2a;

	if (!IsIngame())
		return 0;

	v3 = HomingAttackTarget_Sonic_B;
	if (a2->CharIndex)
	{
		v3 = HomingAttackTarget_Sonic_C;
	}

	if (!v3 || !v3->entity)
	{
		return 0;
	}
	a2a.x = 1.0;
	a2a.y = 0.0;
	a2a.z = 0.0;
	PConvertVector_P2G((taskwk*)a2, &a2a);
	njUnitVector(&a2a);
	targetData = v3->entity;

	for (i = 0; targetData; ++v3)
	{
		v6 = targetData->CollisionInfo;

		if (!v6)
			return 0;

		targetDataColArray = v6->CollisionArray;

		if (!targetDataColArray)
			return 0;

		v8 = targetDataColArray->center.x;
		a1.x = targetData->Position.x;
		v9 = targetData->Position.y;
		v10 = targetData->Position.z;
		a1.x = v8 + a1.x;
		a1.y = v9;
		v11 = targetDataColArray->center.y;
		a1.z = v10;
		a1.y = v11 + v9;
		v12 = targetDataColArray->center.z + v10;
		v13 = &a2->CollisionInfo->CollisionArray->center;
		a1.z = v12;
		a1.x = a1.x - v13->x;
		a1.y = a1.y - v13->y;
		a1.z = a1.z - v13->z;

		if ((double)distance >= njScalor(&a1))
		{
			njUnitVector(&a1);

			if (VectorAngle(&a2a, &a1, 0) <= 12288 && (!i || v15 > (double)v3->distance))
			{
				i = v3;
				v15 = v3->distance;
			}
		}

		targetData = v3[1].entity;
	}

	return i;
}

Bool Amy_CheckLightDash(CharObj2* a1, EntityData1* a2)
{
	Bool result; // eax

	if (!LightDashButton || !isLightDashAllowed(a1, a2, 32.0f) || (Controllers[0].PressedButtons & LightDashButton) == 0)
	{
		return 0;
	}

	a2->Action = Act_Amy_LightDash;
	a1->AnimationThing.Index = 16;
	a1->LightdashTime = 10;
	a1->LightdashTimer = 0;

	a2->Status &= ~2u;
	a1->Speed.x = 8.0;
	a2->Status = a2->Status & ~0x100 | 0x400;
	//PlaySound(764, 0, 0, 0);

	//DoSoundQueueThing(0x4CB);

	int rng = rand() % 3;

	if (rng == 1)
		PlayVoice(7400);

	if (rng == 2)
		PlayVoice(7401);

	result = 1;
	return result;
}

void StopLightDash(EntityData1* data, CharObj2* co2)
{
	data->Status &= ~Status_LightDash;
	data->Action = Act_Amy_Brake; //stop
	float speed_x = co2->Speed.x;
	co2->AnimationThing.Index = Anm_Amy_Brake;
	if (speed_x > 2.0)
	{
		co2->Speed.x = 2.0;
	}

	data->Status &= ~4u;
	co2->LightdashTime = 0;
	co2->LightdashTimer = 0;
	//DoSoundQueueThing(764);
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
