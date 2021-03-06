#include "pch.h"

Buttons BounceButton = Buttons_B;
Buttons LightDashButton = Buttons_B;
Buttons SpinDashButton = Buttons_X;
Buttons HammerJumpButton = Buttons_B;
Buttons HammerAttackButton = Buttons_Y;


void ActionRemap_Config(const IniFile* config)
{
    BounceButton = (Buttons)config->getInt("Controller", "BounceButton", Buttons_B);
    LightDashButton = (Buttons)config->getInt("Controller", "LightDashButton", Buttons_B);
    SpinDashButton = (Buttons)config->getInt("Controller", "SpinDashButton", Buttons_X);
    HammerJumpButton = (Buttons)config->getInt("Controller", "HammerJumpButton", Buttons_B);
    HammerAttackButton = (Buttons)config->getInt("Controller", "HammerAttackButton", Buttons_Y);
}

signed int AmyCheckHammerAttack_r(EntityData1* data1, CharObj2* co2) {

    if ((Controllers[data1->CharIndex].PressedButtons & GetHammerAttackButton()) == 0)
    {
        return 0;
    }

    data1->Action = Act_Amy_HammerAttackR;
    data1->Status &= ~Status_Ball;
    NewAmyAnimData[86].NextAnim = 88;
    co2->SonicSpinTimeProbably = 0;
    hammer_count = 0;
    co2->AnimationThing.Index = 85;
    PlaySound(1288, 0, 0, 0);
    csts* cstsArray = (csts*)co2->array_1x132;
    if ((data1->Status & 0x20) != 0)
    {
        cstsArray->anaspdv.y = 0.0;
    }
    return 1;
}

FunctionPointer(void, AmyEffectPutFallHeart, (float* a1, int rotX, int rotZ), 0x4C5970);
ObjectFunc(AmyPutHammerWave, 0x485B00);

void Hammer_Attack_r(CharObj2* co2, EntityData1* data, EntityData2* data2)
{

    if (Amy_NAct(co2, (EntityData2*)data2, data)
        || Amy_CheckBeInTheAir(data, co2, data2))
    {
        return;
    }

    NJS_VECTOR vs;
    NJS_VECTOR a3;

   int curAnimHammer = co2->AnimationThing.Index;
    if (curAnimHammer == 87)
    {
        co2->SomeFrameNumberThing = 0.0;
    }
    else
    {
        co2->SomeFrameNumberThing = 1.0;
    }
    if (curAnimHammer == 86 && co2->AnimationThing.Frame >= 3.0 && co2->AnimationThing.Frame < 4.0)
    {
        ObjectMaster* hammerWave = LoadObject(LoadObj_Data1, 6, AmyPutHammerWave);
        if (hammerWave)
        {
            vs.x = 15.0;
            vs.z = 0.0;
            vs.y = 0.0;
            njPushMatrix(_nj_unit_matrix_);
  
            njRotateZ_(data->Rotation.z);
            njRotateX_(data->Rotation.z);
            njRotateX_(-data->Rotation.y);

            njCalcVector(0, &vs, &a3);
            njPopMatrix(1u);
            hammerWave->Data1->Position.x = a3.x + data->Position.x;
            hammerWave->Data1->Position.y = a3.y + data->Position.y;
            hammerWave->Data1->Position.z = a3.z + data->Position.z;
            hammerWave->Data1->Rotation.x = data->Rotation.x;
            hammerWave->Data1->Rotation.z = data->Rotation.z;
            hammerWave->Data1->InvulnerableTime = 10;
            hammerWave->Data1->Index = 1;
            AmyEffectPutFallHeart(&hammerWave->Data1->Position.x, data->Rotation.x, data->Rotation.z);
        }
        if ((co2->Upgrades & Upgrades_LongHammer) == 0)
        {
            PlaySound(796, 0, 0, 0);
        }
        else
        {
            PlaySound(797, 0, 0, 0);
        }
        RumbleA(data->CharIndex, 0);
    }

    curAnimHammer = co2->AnimationThing.Index;
    if (curAnimHammer)
    {
        if (curAnimHammer == 88)
        {
            co2->SonicSpinTimeProbably = 0;
            data->Action = Act_Amy_SpinR;
   
        }
        else
        {
            if ((co2->Upgrades & Upgrades_WarriorFeather) == 0
                || (GetHammerAttackButton() & Controllers[data->CharIndex].HeldButtons) == 0)
            {
                NewAmyAnimData[86].NextAnim = 87;
            }
            if (co2->AnimationThing.Index >= 87u)
            {
               AmyCheckHammerAttack_r(data, co2);
            }
        }
    }
    else
    {

        Amy_ResetActionAnim(co2, data, data2);
    }
    return;
}

static void __declspec(naked) AmyCheckStartHammerASM()
{
    __asm
    {
        push esi // co2
        push edi // data
        call AmyCheckHammerAttack_r

        pop edi // data
        pop esi // co2
        retn
    }
}

void DoAmySpinAttack(EntityData1* data, EntityData2* data2, CharObj2* co2) {

    if (Amy_NAct(co2, data2, data) || (data->Status & Status_Ground | Status_OnColli) == 0) {
        return;
    }

    if ((Controllers[data->CharIndex].HeldButtons & HammerAttackButton) == 0)
    {
        data->Status &= ~Status_Attack;
        data->Action = 1;
        co2->AnimationThing.Index = 1;
        return;
    }

    int v40;
    int curAnim = co2->AnimationThing.Index;
    int timerDizzy = co2->field_84;
    int a2;
    float v39;

    switch (curAnim)
    {
    case 88:
        co2->SomeFrameNumberThing = 1.0;
        break;
    case 89:
        v39 = (double)HIBYTE(co2->SonicSpinTimeProbably);
        a2 = HIBYTE(co2->SonicSpinTimer);
        co2->SomeFrameNumberThing = v39 * 0.041666668 * 0.5 + 1.0;
        co2->SpindashSpeed = fabs((double)(int)a2) * 0.059999999 + 0.1;

        if (HIBYTE(co2->SonicSpinTimer) <= 0)
        {
            co2->SpindashSpeed = 1.0;
        }
        else
        {
            co2->SpindashSpeed = -1.0;
        }
        co2->field_84 = 0;
        co2->AnimationThing.Index = 90;
        PlaySound(798, 0, 0, 0);

        break;
    case 90:
        a2 = ++co2->field_84;
        v40 = (double)(int)a2;
        co2->SomeFrameNumberThing = 1.5;
        if (v40 > 300.0)          // dizzy timer
        {
            co2->Speed.z = 0.0;
            co2->Speed.y = 0.0;
            co2->Speed.x = 0.0;
            co2->field_84 = 0;
            co2->AnimationThing.Index = 1;
            data->Action = 1;
        }
        if ((co2->field_84 & 7) == 0)
        {
            ObjectMaster* wave = LoadObject(LoadObj_Data1, 6, AmyPutHammerWave);
            if (wave)
            {
                wave->Data1->Position = data->Position;
                wave->Data1->Position.y = co2->PhysicsData.CollisionSize * 0.5 + wave->Data1->Position.y;
                wave->Data1->Rotation = data->Rotation;
                wave->Data1->InvulnerableTime = 4;
                wave->Data1->Index = 0;
            }
            RumbleA(data->CharIndex, 0);
        }
        break;
    default:
        return;
    }
    return;

}

void init_ActionRemap() {
    if (HammerAttackButton > 0) {    
        WriteData((Buttons**)0x489561, &HammerAttackButton);       
        WriteData((Buttons**)0x485806, &HammerAttackButton);        
        WriteData((Buttons**)0x4894CF, &HammerAttackButton); 

        WriteData((Buttons**)0x489763, &HammerAttackButton); // Dizzy, just in case

        WriteJump((void*)0x485800, AmyCheckStartHammerASM);
    }

    if (HammerJumpButton > 0) {
        WriteData((Buttons**)0x4857b6, &HammerJumpButton);
    }

 
    return;
}