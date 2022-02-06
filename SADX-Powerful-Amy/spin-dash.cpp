#include "pch.h"

BOOL Amy_ChargeSpindash(CharObj2* co2, EntityData1* Data1)
{

    if (!SpinDashButton || (SpinDashButton & Controllers[Data1->CharIndex].PressedButtons) == 0)
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
   // QueueSound_DualEntity(767, Data1, 1, 0, 2);
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
        /**DoSoundQueueThing(767);
        DoSoundQueueThing(763);
        PlaySound(1227, 0, 0, 0);*/
        
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
                //QueueSound_DualEntity(767, a1, 1, 0, 2);
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
       /** DoSoundQueueThing(767);
        DoSoundQueueThing(763);*/
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