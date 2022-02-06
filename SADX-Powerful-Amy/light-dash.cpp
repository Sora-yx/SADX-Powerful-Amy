#include "pch.h"

HomingAttackTarget* isLightDashAllowed(CharObj2* co2, EntityData1* a2, float a3)
{
	HomingAttackTarget* v4; // edi
	EntityData1* v5; // ebx
	EntityData1* v6; // esi
	long double v7; // st7
	CollisionData* v8; // eax
	long double v9; // st7
	CollisionData* v10; // eax
	int v11; // eax
	double v12; // st7
	float v13; // eax
	float v14; // ecx
	float v15; // edx
	float v16; // eax
	NJS_VECTOR vd; // [esp+Ch] [ebp-18h] BYREF
	NJS_VECTOR v18; // [esp+18h] [ebp-Ch] BYREF
	float a1a; // [esp+28h] [ebp+4h]

	v4 = HomingAttackTarget_Sonic_B;
	if (a2->CharIndex)
	{
		v4 = HomingAttackTarget_Sonic_C;
	}
	if (!v4->entity)
	{
		return 0;
	}

	v18.x = 1.0;
	v18.y = 0.0;
	v18.z = 0.0;
	PConvertVector_P2G((taskwk*)a2, &v18);
	njUnitVector(&v18);
	v6 = v4->entity;
	v5 = 0;
	if (v4->entity)
	{
		do
		{
			v8 = v6->CollisionInfo->CollisionArray;
			vd = v6->Position;
			njAddVector(&vd, &v8->center);
			njSubVector(&vd, &a2->Position);
			v7 = sqrt(vd.y * vd.y + vd.z * vd.z + vd.x * vd.x);
			if (v7 == 0.0)
			{
				vd.z = 0.0;
				vd.y = 0.0;
				vd.x = 0.0;
			}
			else
			{
				v9 = 1.0 / v7;
				vd.x = vd.x * v9;
				vd.y = vd.y * v9;
				vd.z = v9 * vd.z;
			}
			if ((double)a3 >= njScalor(&vd))
			{
				njUnitVector(&vd);

				if (VectorAngle(&v18, &vd, 0) <= 12288 && (!v5 || v4->distance < (double)*(float*)&a3))
				{
					v5 = v6;
				}
			}
			v6 = v4[1].entity;
			++v4;
		} while (v6);
	}

	return v4;
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
	data->Status &= ~Status_LightDash;
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
