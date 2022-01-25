#include "pch.h"
#include "abilities.h"


Trampoline* Amy_Exec_t = nullptr;
Trampoline* Amy_RunsActions_t = nullptr;

Trampoline* Sonic_Main_t = nullptr;

NJS_TEXNAME AmyEffR_TEXNAMES[40];
NJS_TEXLIST AmyEffR_TEXLIST = { arrayptrandlength(AmyEffR_TEXNAMES) };


static Trampoline* LoadLevelObject_t = nullptr;

PhysicsData Amy_SA2Physics = { 60, 2, 16, 16, 1.3, 0.6,	1.3, 3, 0.23, 0.46, 1.39, 2.3, 3.7, 5.09, 0.076, 0.048, 0.031, -0.06, -0.18, -0.17, -0.028, -0.008, -0.01, -0.4, -0.1, -0.6, -0.2825, 0.3, 4, 10, 0.08, 7,	5.4 };
PhysicsData Amy_HeroesPhysics = { 60, 2, 32, 32, 4.5, 0.6, 1.66, 3, 0.23, 0.46, 1.39, 2.3, 3.7, 5.09, 0.076, 0.09, 0.031, -0.06, -0.18, -0.14, -0.028, -0.008, -0.01, -0.4, -0.1, -0.6, -0.2825, 0.3, 4, 10, 0.08, 7, 5.4 };


void __cdecl Amy_Display_r(ObjectMaster* obj)
{

	__int16 curAnim; // ax
	double v5; // st7
	double v6; // st7
	NJS_OBJECT* HammerChild; // edx
	NJS_OBJECT* HammerObj; // ecx
	unsigned int v9; // eax
	Uint32 v10; // ebx
	int Anim; // ebx
	Angle v12; // eax
	double v14; // st7
	Angle v15; // eax
	Angle v16; // eax
	Angle v17; // eax
	float frameNumber; 
	NJS_VECTOR v; 
	NJS_VECTOR a2; 
	NJS_VECTOR vs; 

	EntityData1* data1 = obj->Data1;
	CharObj2* co2 = ((EntityData2*)obj->Data2)->CharacterData;
	EntityData2* data2 = (EntityData2*)obj->Data2;


	Direct3D_SetZFunc(3u);
	if (co2->LightdashTime != 1)
	{
		if (EV_MainThread_ptr != 0)
		{
			goto LABEL_6;
		}
		curAnim = co2->AnimationThing.Index;
		if (curAnim == 13)
		{
			co2->SomeFrameNumberThing = 1.0;
			goto LABEL_7;
		}
		if ((unsigned __int16)curAnim < 85u)
		{
		LABEL_6:
			co2->SomeFrameNumberThing = 0.0;
		}
	}
LABEL_7:
	v5 = co2->TailsFlightTime + 0.1;
	if (v5 >= co2->SomeFrameNumberThing)
	{
		v6 = co2->TailsFlightTime - 0.1;
		if (v6 <= co2->SomeFrameNumberThing)
		{
			co2->TailsFlightTime = co2->SomeFrameNumberThing;
		}
		else
		{
			co2->TailsFlightTime = v6;
		}
	}
	else
	{
		co2->TailsFlightTime = v5;
	}
	HammerObj = AMY_OBJECTS[36]->sibling;
	HammerChild = HammerObj->child;
	HammerObj->scl[0] = co2->TailsFlightTime;
	HammerObj->scl[1] = co2->TailsFlightTime;
	HammerObj->scl[2] = co2->TailsFlightTime;
	HammerChild->scl[0] = co2->TailsFlightTime;
	HammerChild->scl[1] = co2->TailsFlightTime;
	HammerChild->scl[2] = co2->TailsFlightTime;
	if (co2->TailsFlightTime == 0.0)
	{
		HammerObj->evalflags |= 8u;
		v9 = HammerChild->evalflags | 8;
	}
	else
	{
		HammerObj->evalflags &= 0xFFFFFFF7;
		HammerChild->evalflags &= 0xFFFFFFF7;
		v10 = HammerObj->evalflags;

		if (co2->TailsFlightTime == 1)
		{
			HammerObj->evalflags = v10 | 4;
			v9 = HammerChild->evalflags | 4;
		}
		else
		{
			HammerObj->evalflags = v10 & 0xFFFFFFFB;
			v9 = HammerChild->evalflags & 0xFFFFFFFB;
		}
	}
	HammerChild->evalflags = v9;
	Anim = (unsigned __int16)co2->AnimationThing.Index;
	if (co2->AnimationThing.State == 2)
	{
		Anim = (unsigned __int16)co2->AnimationThing.LastIndex;
	}
	if ((data1->InvulnerableTime & 2) == 0)
	{
		njSetTexture(&AMY_TEXLIST);
		Direct3D_PerformLighting(2);
		njControl3D_Backup();
		njControl3D(NJD_CONTROL_3D_CONSTANT_MATERIAL);
		SetMaterialAndSpriteColor_Float(1.0, 1.0, 1.0, 1.0);
		njPushMatrix(0);
		v14 = co2->PhysicsData.CollisionSize * 0.5;
		vs.z = 0.0;
		vs.x = 0.0;
		vs.y = v14;
		njPushMatrix(_nj_unit_matrix_);
		v12 = data1->Rotation.z;
		if (v12)
		{
			njRotateZ(0, (unsigned __int16)v12);
		}
		v15 = data1->Rotation.x;
		if (v15)
		{
			njRotateX(0, (unsigned __int16)v15);
		}
		if (data1->Rotation.y)
		{
			njRotateY(0, (unsigned __int16)-LOWORD(data1->Rotation.y));
		}
		njCalcVector(0, &vs, &a2);
		njPopMatrix(1u);
		njAddVector(&a2, &data1->Position);
		njTranslateV(0, &a2);
		data1->CollisionInfo->CollisionArray->center = a2;

		v16 = data1->Rotation.z;
		if (v16)
		{
			njRotateZ(0, (unsigned __int16)v16);
		}
		v17 = data1->Rotation.x;
		if (v17)
		{
			njRotateX(0, (unsigned __int16)v17);
		}
	
		if (data1->Rotation.y != 0x8000)
		{
			njRotateY(0, (unsigned __int16)(0x8000 - data1->Rotation.y));
		}
		if (Anim == Anm_Amy_SpinDash && (data1->Status & 3) != 0)
		{
			v.x = 0.0;
			v.y = -1.0;
			v.z = 0.0;
			njTranslateV(0, &v);
			njRotateZ(0, 0x2000);
			v.x = 0.69999999;
			v.y = 1.1;
			v.z = 0.80000001;
			njScaleV(0, &v);
		}
		if (*((_DWORD*)data1->field_3C + 16))
		{
			DrawEventAction(data1);
		}
		else if ((Controllers[data1->CharIndex].HeldButtons & 0x400) != 0 && data1->Action == 53)
		{

			dsDrawObject(co2->AnimationThing.AnimData[(unsigned __int16)co2->AnimationThing.Index].Animation->object);
		}
		else
		{
			frameNumber = co2->AnimationThing.Frame;
			if (co2->AnimationThing.State == 2)
			{
				njAction(co2->AnimationThing.action, frameNumber);
			}
			else
			{
				if ( (data1->Status & Status_Ball) != 0 && (co2->SonicSpinTimer & 0x11) != 0 && data1->Action != Act_Amy_Jump && data1->Action != Act_Amy_Fall)
				{
					njSetTexture(&AmyEffR_TEXLIST);
					Anim = Anm_Amy_SpinBall;
				}
				else {
					njSetTexture(&AMY_TEXLIST);
				}

				njAction(co2->AnimationThing.AnimData[Anim].Animation, frameNumber);
			}
		}

		njPopMatrix(1u);
		ClampGlobalColorThing_Thing();
		njControl3D_Restore();
		Direct3D_PerformLighting(0);
	}
	Direct3D_ResetZFunc();
	if (IsGamePaused())
	{
		DrawCharacterShadow(data1, (shadowwk*)&co2->_struct_a3);
	}
}

bool IsPlayVoice = false;

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

		if (Amy_CheckLightDash(co2, data))
			return;

		break;
	case Act_Amy_Jump:
		data->Status &= ~Status_Ball;
		IsPlayVoice = false;

		if (CheckHomingAttack(co2, data, data2))
			return;

		if (Amy_CheckBounceAttack(co2, data))
			return;

		if (Amy_CheckLightDash(co2, data))
			return;

		break;
	case Act_Amy_Fall:
		if (Amy_CheckBounceAttack(co2, data))
			return;

		if (Amy_CheckLightDash(co2, data))
			return;
		break;
	case Act_Amy_Launch:
	case Act_Amy_Spring:

	case Act_Amy_Push:

		if (Amy_CheckLightDash(co2, data))
			return;
		break;
	case Act_Amy_HammerProp:
		if (co2->Speed.x > 3.0 && !IsPlayVoice)
		{
			PlayVoice(1743);
			IsPlayVoice = true;
			return;
		}
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
	case Act_Amy_LightDash:
		DoLightDashAction(data, co2, data2);
		break;
	}

	FunctionPointer(void, original, (EntityData1 * data, EntityData2 * data2, CharObj2 * co2), Amy_RunsActions_t->Target());
	return original(data, data2, co2);
}

bool isLoaded = false;

void Amy_Main_r(ObjectMaster* obj)
{
	task* tsk = (task*)obj;
	EntityData1* data = (EntityData1*)tsk->twp;
	auto wk = (taskwk*)tsk->twp; // main task containing position, rotation, scale
	auto mwp = (motionwk2*)tsk->mwp; // task containing movement information
	auto pwk = (playerwk*)mwp->work.ptr; // physics, animation info, and countless other things
	auto co2 = (CharObj2*)pwk;
	auto data2 = (EntityData2*)mwp;

	switch (data->Action)
	{
	case 0:
		init_SpinDashTexture();
		InitSA2AnimHack(&co2->AnimationThing);
		break;
	case Act_Amy_SpinDash:
		PGetRotation(wk, mwp, pwk);
		PGetBreak(wk, mwp, pwk);
		PGetSpeed(wk, mwp, pwk);
		PSetPosition(wk, mwp, pwk);
		PResetPosition(wk, mwp, pwk);
		LoadSpinDashEffect(data);
		break;
	case Act_Amy_Rolling:
		PGetRotation(wk, mwp, pwk);
		PGetInertia(wk, mwp, pwk);
		PGetSpeed(wk, mwp, pwk);
		PSetPosition(wk, mwp, pwk);
		PResetPosition(wk, mwp, pwk);
		break;
	case Act_Amy_HomingAttack:
		PResetAngle(wk, mwp, pwk);
		Sonic_HomingAttackThing(co2, data, data2);
		PSetPosition(wk, mwp, pwk);
		PResetPosition(wk, mwp, pwk);
		LoadSonicDashTrail(data);
		co2->SonicSpinTimeProbably |= 1u;
		//PSetSpinDashEffect(data);
		break;
	case Act_Amy_Bounce:
	case Act_Amy_BounceUp:
		PResetAngle(wk, mwp, pwk);
		PGetGravity(wk, mwp, pwk);
		PGetAccelerationAir(wk, mwp, pwk);
		PGetSpeed(wk, mwp, pwk);
		PSetPosition(wk, mwp, pwk);
		PResetPosition(wk, mwp, pwk);
		//LoadObject(LoadObj_Data1, 6, SonicDashTrail_Init)->Data1->CharIndex = data->CharIndex;
		break;
	case Act_Amy_LightDash:
		Sonic_InitLightDash(data, data2, co2);
		if (PSetPosition(wk, mwp, pwk) == 2)
		{
			PlaySound(1222, 0, 0, 0);
			data->Action = Act_Amy_Knocked; //knocked back
			co2->AnimationThing.Index = 25; //hurt recover
			data->Status &= 0xFBu;
			co2->LightdashTime = 0;
			DoSoundQueueThing(764);
			PSetCrashEffect(wk);
		}
		else
		{
			PResetPosition(wk, mwp, pwk);
			//LoadSonicDashTrail(data);
			co2->SonicSpinTimeProbably |= 1u;
		}
		break;
	}

	if ((data->Status & Status_Ball) != 0)
	{
		if (co2)
			++co2->SonicSpinTimer;
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

	memcpy(&PhysicsArray[Characters_Amy], &Amy_SA2Physics, sizeof(PhysicsArray[Characters_Amy]));
	//memcpy(&PhysicsArray[Characters_Amy], &Amy_HeroesPhysics, sizeof(PhysicsArray[Characters_Amy]));

	init_LightDashHack();

	WriteJump(Amy_Display, Amy_Display_r);
	Init_AmyNewAnim();
	return;
}