#include "pch.h"

extern NJS_TEXLIST AmyEffR_TEXLIST;
NJS_TEXLIST Amy_BallTexlistDash[2];

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
        a1->LoopData = (Loop*)&Amy_BallTexlistDash[1];
    }
    else
    {
        a1->LoopData = (Loop*)&Amy_BallTexlistDash;
    }
}

void __cdecl EffectSpin_r(ObjectMaster* a1)
{
    effectSpinInit(a1->Data1);
    a1->MainSub = sub_4A0E30;
    a1->DisplaySub = EffectSpinDisplay;
    EffectSpinDisplay(a1);
}

void LoadSpinDashEffect(EntityData1* data) {

    ObjectMaster* spin = LoadObject(LoadObj_Data1, 5, EffectSpin_r);

    if (spin)
    {
        spin->Data1->CharIndex = data->CharIndex;
    }
}

void HomingAura_Init(EntityData1* a1)
{
    EntityData1* v1; // esi
    Angle v2; // eax
    Angle v3; // eax
    int v4; // [esp+4h] [ebp-10h]
    NJS_VECTOR a2; // [esp+8h] [ebp-Ch] BYREF

    v1 = EntityData1Ptrs[a1->CharIndex];
    if (v1)
    {
        a2.z = 0.0;
        a2.x = 0.0;
        a2.y = 5.0;
        njPushMatrix(_nj_unit_matrix_);
        v2 = v1->Rotation.z;
        if (v2)
        {
            njRotateZ(0, (unsigned __int16)v2);
        }
        v3 = v1->Rotation.x;
        if (v3)
        {
            njRotateX(0, (unsigned __int16)v3);
        }
        if (v1->Rotation.y)
        {
            njRotateY(0, (unsigned __int16)-LOWORD(v1->Rotation.y));
        }
        njCalcVector(0, &a2, &a1->Position);
        njAddVector(&a1->Position, &v1->Position);
        njPopMatrix(1u);
    }
    v4 = rand();
    a1->Scale.x = 3.0;
    if ((double)v4 * 0.000030517578 <= 0.5)
    {
        a1->LoopData = (Loop*)&Amy_BallTexlistDash[1];
    }
    else
    {
        a1->LoopData = (Loop*)Amy_BallTexlistDash;
    }
}

ObjectFunc(sub_4A1000, 0x4A1000);

void __cdecl Load_HomingAttackAura(ObjectMaster* a1)
{
    if (EntityData1Ptrs[a1->Data1->CharIndex]->CharID == Characters_Amy) {
        HomingAura_Init(a1->Data1);
        a1->MainSub = (ObjectFuncPtr)0x4A10E0;
        a1->DisplaySub = sub_4A1000;
        sub_4A1000(a1);
        return;
    }
    else {
        return sub_4A2A70(a1);
    }
}

void init_AuraTexture()
{
    Amy_BallTexlistDash[0].nbTexture = 1;
    Amy_BallTexlistDash[0].textures = AmyEffR_TEXLIST.textures;

    Amy_BallTexlistDash[1].nbTexture = 1;
    Amy_BallTexlistDash[1].textures = AmyEffR_TEXLIST.textures;

    WriteData((ObjectFuncPtr*)0x494bad, Load_HomingAttackAura);
}
