#pragma once

void Do_SpinDash(CharObj2* co2, EntityData1* data, EntityData2* data2);
BOOL Amy_ChargeSpindash(CharObj2* co2, EntityData1* Data1);
void DoRolling(EntityData1* data, CharObj2* co2, EntityData2* data2);

void Do_BounceDown(EntityData1* data1, CharObj2* co2, motionwk2* data2);
void Do_BounceUP(EntityData1* data1, CharObj2* co2, motionwk2* data2);
signed int CheckHomingAttack(CharObj2* co2, EntityData1* data, EntityData2* data2);
void DoHomingAttack(CharObj2* co2, EntityData1* data, EntityData2* data2);
signed int Amy_CheckBounceAttack(CharObj2* a1, EntityData1* a2);