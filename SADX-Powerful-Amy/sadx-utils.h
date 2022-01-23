#pragma once

FunctionPointer(void, PResetPosition, (taskwk* a1, motionwk2* a2, playerwk* a3), 0x43EE70);

// int __usercall Amy_CheckBeInTheAir@<eax>(EntityData1 *a1@<ecx>, CharObj2 *a2@<eax>, EntityData2 *data2)
static const void* const Amy_CheckAirPtr = (void*)0x485730;
static inline int Amy_CheckBeInTheAir(EntityData1* a1, CharObj2* a2, EntityData2* data2)
{
	int result;
	__asm
	{
		push[data2]
		mov eax, [a2]
		mov ecx, [a1]
		call Amy_CheckAirPtr
		mov result, eax
		add esp, 4
	}
	return result;
}

// signed int __usercall Amy_CheckNextAction@<eax>(CharObj2 *a1@<ecx>, EntityData2 *a2@<edi>, EntityData1 *a3@<esi>)
static const void* const Amy_NActPtr = (void*)0x487810;
static inline int Amy_NAct(CharObj2* a1, EntityData2* a2, EntityData1* a3)
{
	int result;
	__asm
	{
		mov esi, [a3]
		mov edi, [a2]
		mov ecx, [a1]
		call Amy_NActPtr
		mov result, eax
	}
	return result;
}


// signed int __usercall Amy_CheckNextAction@<eax>(CharObj2 *a1@<ecx>, EntityData2 *a2@<edi>, EntityData1 *a3@<esi>)
static const void* const Amy_JumpPtr = (void*)0x487640;
static inline int Amy_CheckJump(CharObj2* a1, EntityData1* a2, EntityData2* a3)
{
	int result;
	__asm
	{
		mov ebx, [a3]
		mov ecx, [a2]
		mov eax, [a1]
		call Amy_JumpPtr
		mov result, eax
	}
	return result;
}

FastcallFunctionPointer(void, sub_4930D0, (CharObj2* a1, EntityData1* a2), 0x4930D0);