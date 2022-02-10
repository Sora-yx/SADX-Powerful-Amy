#include "pch.h"

extern bool instantSpin;
extern bool hammerjumpBuff;

float hammerJumpSpd = 2.5;

int AmyCheckEndDrum_r(EntityData1* a1, CharObj2* a2)
{
	return 0;
}

static void __declspec(naked) AmyCheckEndDrumASM()
{
	__asm
	{
		push esi // a2
		push eax // a1
		call AmyCheckEndDrum_r

		add esp, 4 // a1<eax> is also used for return value
		pop esi // a2
		retn
	}
}


int AmyCheckStartDrum_r(EntityData1* a1, CharObj2* a2)
{
	return 0;
}


static void __declspec(naked) AmyCheckStartDrumASM()
{
	__asm
	{
		push esi // a2
		push edi // a1
		call AmyCheckStartDrum_r

		pop edi // a1
		pop esi // a2
		retn
	}
}


int Amy_InstantSpin_r(EntityData1* a1, CharObj2* a2)
{
	a2->field_84 = 0;

	if (GetAnalog(a1, 0, 0))
	{
		return 1;
	}

	return 0;
}

static void __declspec(naked) Amy_CheckSpinStickTurns()
{
	__asm
	{
		push esi
		push eax
		call Amy_InstantSpin_r
		add esp, 4
		pop esi
		retn
	}
}

void init_Helper()
{
	if (instantSpin)
	{
		WriteJump((void*)0x485970, Amy_CheckSpinStickTurns);
	}

	WriteJump((void*)0x485870, AmyCheckStartDrumASM); //remove drum that create conflict with spin dash / homing attack
	WriteJump((void*)0x4858E0, AmyCheckEndDrumASM);

	if (hammerjumpBuff)
		WriteData((float**)0x489a95, &hammerJumpSpd);
}