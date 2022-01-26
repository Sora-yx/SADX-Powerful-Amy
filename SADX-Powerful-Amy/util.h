#pragma once

void LoadAnimation(AnimationFile** info, const char* name, const HelperFunctions& helperFunctions);
ModelInfo* LoadBasicModel(const char* name);
void FreeMDL(ModelInfo* pointer);
void __cdecl PlayerClearSpeed(EntityData2* a1, CharObj2* a2);