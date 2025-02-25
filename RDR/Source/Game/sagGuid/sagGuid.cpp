#include <pch.h>



namespace rage
{
	gohGuid sagGuid::GetGOHGUID()
	{
		/*
		if (*(uint16_t*)(MEMORY[0x714F1381F0] + 16 * (uint16_t)Value + 8) == HIWORD(Value))
			return *(gohGuid*)(*(uintptr_t*)(MEMORY[0x714F1381F0] + 16 * (uint16_t)Value) + 0x190);
		else
			return 0;
		*/

		// Need to be implemented...

		return 0;
	}
}