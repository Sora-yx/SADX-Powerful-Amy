#include "pch.h"

extern NJS_TEXLIST AmyEffR_TEXLIST;

NJS_TEXNAME DashAmyTex = { (char*)"amy_ball_a", 0, 0 };
NJS_TEXNAME DashAmyTex2 = { (char*)"amy_ball_b", 0, 0 };

NJS_TEXLIST BallTexlistDash_Amy[2] = {
    &DashAmyTex, 0,
    &DashAmyTex2, 1
};

void init_SpinDashTexture()
{
    BallTexlistDash_Amy[0].textures[0] = AmyEffR_TEXLIST.textures[0];
    BallTexlistDash_Amy[1].textures[0] = AmyEffR_TEXLIST.textures[1];
}

void effectSpinInit(EntityData1* a1)
{
    EntityData1* data1; // esi
    Angle z; // eax
    Angle x; // eax
    unsigned __int64 v4; // rax
    unsigned __int64 v5; // rax
    unsigned __int64 v6; // rax
    NJS_VECTOR a2; // [esp+8h] [ebp-18h] BYREF
    NJS_VECTOR a3; // [esp+14h] [ebp-Ch] BYREF

    data1 = EntityData1Ptrs[a1->CharIndex];
    if (data1)
    {
        a2.z = 0.0;
        a2.x = 0.0;
        a2.y = 5.0;
        njPushMatrix(_nj_unit_matrix_);
        z = data1->Rotation.z;
        if (z)
        {
            njRotateZ(0, (unsigned __int16)z);
        }
        x = data1->Rotation.x;
        if (x)
        {
            njRotateX(0, (unsigned __int16)x);
        }
        if (data1->Rotation.y)
        {
            njRotateY(0, (unsigned __int16)-LOWORD(data1->Rotation.y));
        }
        njCalcVector(0, &a2, &a1->Position);
        a2.z = 0.0;
        a2.x = 0.0;
        a2.y = (double)rand() * 0.000030517578 + 0.2;
        njPushMatrix(_nj_unit_matrix_);
        if ((unsigned int)(unsigned __int64)((double)rand() * 0.000030517578 * 65536.0))
        {
            v4 = (unsigned __int64)((double)rand() * 0.000030517578 * 65536.0);
            njRotateZ(0, (unsigned __int16)v4);
        }
        if ((unsigned int)(unsigned __int64)((double)rand() * 0.000030517578 * 65536.0))
        {
            v5 = (unsigned __int64)((double)rand() * 0.000030517578 * 65536.0);
            njRotateX(0, (unsigned __int16)v5);
        }
        if ((unsigned int)(unsigned __int64)((double)rand() * 0.000030517578 * 65536.0))
        {
            v6 = (unsigned __int64)((double)rand() * 0.000030517578 * 65536.0);
            njRotateY(0, (unsigned __int16)v6);
        }
        njCalcVector(0, &a2, &a3);
        njPopMatrix(2u);
        njAddVector(&a1->Position, &a3);
    }
    if ((double)rand() * 0.000030517578 <= 0.5)
    {
        a1->LoopData = (Loop*)&AmyEffR_TEXLIST;
    }
    else
    {
        a1->LoopData = (Loop*)&AmyEffR_TEXLIST;
    }
}

ObjectFunc(EffectSpinDisplay, 0x4A0CB0);
ObjectFunc(sub_4A0E30, 0x4A0E30);


void __cdecl EffectSpin_r(ObjectMaster* a1)
{
    effectSpinInit(a1->Data1);
    a1->MainSub = sub_4A0E30;
    a1->DisplaySub = EffectSpinDisplay;
    EffectSpinDisplay(a1);
}

ObjectFunc(EffectSpin, 0x4A2A10);
void LoadSpinDashEffect(EntityData1* data) {
    ObjectMaster* spin = LoadObject(LoadObj_Data1, 5, EffectSpin_r);
    if (spin)
    {
        spin->Data1->CharIndex = data->CharIndex;
    }
}

BOOL Amy_ChargeSpindash(CharObj2* co2, EntityData1* Data1)
{

    if ((SpinDashButton & Controllers[Data1->CharIndex].PressedButtons) == 0)
    {
        return 0;
    }

    Data1->Action = Act_Amy_SpinDash;
    co2->AnimationThing.Index = Anm_Amy_SpinDash; //jumpballAnim
    Data1->Status |= 0x500u;

    co2->SonicSpinTimer = 0;
    if (co2->Speed.x <= 2.0)
    {
        co2->SpindashSpeed = 2.0;
    }
    else
    {
        co2->SpindashSpeed = co2->Speed.x;
    }
    QueueSound_DualEntity(767, Data1, 1, 0, 2);
    return 1;
}

signed int Amy_ReleaseSpindash(EntityData1* a1, CharObj2* a2)
{
    __int16 spintime;
    signed int result; 

    spintime = a2->SonicSpinTimer;
    if (spintime >= 300)
    {
        a1->Status |= 0x200;
        bool isExist = !EntityData1Ptrs[0] || (a1->Status & Status_LightDash) == 0 || (SpinDashButton & Controllers[0].ReleasedButtons) != 0;
        if (!isExist)
        {
            a2->PhysicsData.MaxAccel = 0.5;
        }

        a2->SonicSpinTimer = 0;
        if (a2->Speed.x > 0.0)
        {
            a1->Action = Act_Amy_Walk;
        }
        else
        {
            a1->Action = Act_Amy_Stand;
            a2->IdleTime = 0;
        }
        a2->AnimationThing.Index = 20; //uncurl from rolling
        a1->Status &= 0xFAFFu;
        DoSoundQueueThing(767);
        DoSoundQueueThing(763);
        PlaySound(1227, 0, 0, 0);
        
        result = 1;
    }
    else if (spintime < 300)
    {
        if ((SpinDashButton & Controllers[a1->CharIndex].HeldButtons) != 0)
        {
            if (a2->SpindashSpeed < 10.0)
            {
                a2->SpindashSpeed = a2->SpindashSpeed + 0.40000001;
            }
                QueueSound_DualEntity(767, a1, 1, 0, 2);
            result = 0;
        }
        else
        {
            a1->Action = Act_Amy_Rolling;
            a2->AnimationThing.Index = Anm_Amy_Rolling;
            a2->Speed.x = a2->SpindashSpeed;
            PlaySound(821, 0, 0, 0);
            //PlaySound(Snd_SpinDashRelease, 0, 0, 0);
           // DoSoundQueueThing(767);
            //DoSoundQueueThing(763);
            a2->SonicSpinTimer = 0;
            a2->SpindashSpeed = 0.0;
            if ((a1->Status & Status_Ball) == 0)
            {
              //DoSoundQueueThing(763);
            }
            result = 1;
        }
    }
    else
    {
        a2->SonicSpinTimer = 0;
        if (a2->Speed.x > 0.0)
        {
            a1->Action = 2;
        }
        else
        {
            a1->Action = 1;
            a2->IdleTime = 0;
        }
        a2->AnimationThing.Index = 20; //uncurl from rolling
        a1->Status &= 0xFAFFu;
        DoSoundQueueThing(767);
        DoSoundQueueThing(763);
        result = 1;
    }

    return result;
}


void Do_SpinDash(CharObj2* co2, EntityData1* data, EntityData2* data2)
{

    if (Amy_CheckBeInTheAir(data, co2, data2))
    {
        co2->AnimationThing.Index = Anm_Amy_SpinDash; //jumpballAnim
        co2->SpindashSpeed = 5.0f;       // 5.0
        data->Status |= 0x500u;
        //PlaySound(Snd_SpinDash, 0, 0, 0);
        //DoSoundQueueThing(767);
        //DoSoundQueueThing(763);
    }
    else
    {
        Amy_ReleaseSpindash(data, co2);
    }
}