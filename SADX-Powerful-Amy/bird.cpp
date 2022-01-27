#include "pch.h"

//might add the other bird someday

void init_BirdHack() {
    WriteData<1>((void*)0x4c6875, 0x74); //Force Amy's bird to load at every stage. (from JNZ 75 to JZ 74)
}