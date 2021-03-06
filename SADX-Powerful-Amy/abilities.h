#pragma once

void Do_SpinDash(CharObj2* co2, EntityData1* data, EntityData2* data2);
BOOL Amy_ChargeSpindash(CharObj2* co2, EntityData1* Data1);
void DoRolling(EntityData1* data, CharObj2* co2, EntityData2* data2);

void Do_BounceDown(EntityData1* data1, CharObj2* co2, motionwk2* data2);
void Do_BounceUP(EntityData1* data1, CharObj2* co2, motionwk2* data2);
signed int CheckHomingAttack(CharObj2* co2, EntityData1* data, EntityData2* data2);
void DoHomingAttack(CharObj2* co2, EntityData1* data, EntityData2* data2);
signed int Amy_CheckBounceAttack(CharObj2* a1, EntityData1* a2);
void DoLightDashAction(EntityData1* data, CharObj2* co2, EntityData2* data2);
Bool Amy_CheckLightDash(CharObj2* a1, EntityData1* a2);
void LoadSpinDashEffect(EntityData1* data);
void init_AuraTexture();
HomingAttackTarget* isLightDashAllowed(CharObj2* co2, EntityData1* a2, float a3);
void Fix_HammerAttackSpinAnim(CharObj2* co2, EntityData1* data);
void Hammer_Attack_r(CharObj2* co2, EntityData1* data, EntityData2* data2);
void DoAmySpinAttack(EntityData1* data, EntityData2* data2, CharObj2* co2);

