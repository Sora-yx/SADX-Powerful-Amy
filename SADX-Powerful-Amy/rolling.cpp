#include "pch.h"

void DoRolling(EntityData1* data, CharObj2* co2, EntityData2* data2)
{

    if (Amy_NAct(co2, data2, data))
    {
        return;
    }

    if (Amy_CheckBeInTheAir(data, co2, data2))
    {
        co2->AnimationThing.Index = 22; //jumpballAnim
        co2->SpindashSpeed = 5.0f;       // 5.0
        data->Status |= 0x500u;
        /**DoSoundQueueThing(767);
        DoSoundQueueThing(763);*/
    }

    if (Amy_CheckJump(co2, data, data2))
    {
        data->Status = data->Status & ~0x2000 | 0x500;
        return;
    }

    sub_4930D0(co2, data);

   if (co2->Speed.x >= co2->PhysicsData.RollEnd)
   {
       if ((AttackButtons & Controllers[data->CharIndex].PressedButtons) != 0)
       {
           data->Action = 2;
           co2->AnimationThing.Index = 29;
           data->Status &= 0xFAFFu;
       }
   }
   else {
       if (co2->Speed.x > 0.0)
       {
           data->Action = Act_Amy_Walk;
       }
       else
       {
           data->Action = Act_Amy_Stand;
           co2->IdleTime = 0;
       }
       co2->AnimationThing.Index = 20; //uncurl from rolling
       data->Status &= 0xFAFFu;
   }

    return;
}