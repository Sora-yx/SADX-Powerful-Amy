#pragma once

void LoadAnimation(AnimationFile** info, const char* name, const HelperFunctions& helperFunctions);
ModelInfo* LoadBasicModel(const char* name);
void FreeMDL(ModelInfo* pointer);
void __cdecl PlayerClearSpeed(EntityData2* a1, CharObj2* a2);

void njRotateX_(Angle x);
void njRotateY_(Angle y);
void njRotateZ_(Angle z);
bool isNewTrick();