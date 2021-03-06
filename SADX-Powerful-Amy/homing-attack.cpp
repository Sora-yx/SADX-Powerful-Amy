#include "pch.h"

signed int CheckHomingAttack(CharObj2* co2, EntityData1* data, EntityData2* data2) {

	if ((Controllers[data->CharIndex].PressedButtons & Buttons_A) == 0 || !isHomingAttack)
	{
		return 0;
	}

	data->Action = Act_Amy_HomingAttack;
    data->Status |= Status_Ball | Status_Attack;
    co2->AnimationThing.Index = Anm_Amy_Rolling;
	DoHomingAttackThing(co2, data, data2);
	return 1;
}

void DoHomingAttack(CharObj2* co2, EntityData1* data, EntityData2* data2)
{
    auto mwk = (motionwk2*)data2;
    int colID;
    int timer;
    char pnum = data->CharIndex;

    if (!Amy_NAct(co2, data2, data))
    {
        CollisionInfo* colObj = data->CollisionInfo->CollidingObject;
        timer = co2->LightdashTimer;
        co2->LightdashTimer = timer + 1;

        if (timer >= 360 || colObj && ((colID = colObj->id) == 0 || colID == 2 || colID == 3))
        {
            co2->LightdashTime = -1;

            //patch height killed for whatever reason
            co2->Speed = { 1.0f, 2.5f, 0.0f };
            data->Action = Act_Amy_Jump;
            co2->AnimationThing.Index = Anm_Amy_HammerSomerTrickA;
        }
        else
        {
            timer = co2->LightdashTime;
            if ((double)(int)timer >= 6.0
                || (AttackButtons & Controllers[pnum].PressedButtons) != 0)
            {
                co2->LightdashTime = 0;
                data->Action = Act_Amy_Fall;
                co2->AnimationThing.Index = Anm_Amy_Fall;
                data->Status &= 0xFAu;
            }
            else if ((data->Status & 3) != 0)
            {
                data->Status &= 0xFAu;
                if (Player_CheckBreak((taskwk*)data) && co2->Speed.x > 0.0)
                {
                    data->Action = Act_Amy_Brake;
                    co2->AnimationThing.Index = Anm_Amy_Brake;
                    data->Rotation.x = mwk->ang_aim.x;
                    data->Rotation.z = mwk->ang_aim.z;
                }
                else
                {
                    data->Rotation.x = mwk->ang_aim.x;
                    data->Rotation.z = mwk->ang_aim.z;

                    if (!Amy_CheckStop(co2, data, data2))
                    {
                        return;
                    }

                    co2->AnimationThing.Index = 2;
                }
            }
        }
    }
    return;
}