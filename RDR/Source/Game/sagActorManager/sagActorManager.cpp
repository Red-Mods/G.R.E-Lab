#include <pch.h>



namespace rage
{
	void sagActorManager::__LoadSigs()
	{
		Pattern("rage::aGuidGeneral::sm_ManagerSlots", "48 8B 05 ? ? ? ? 0F B7 CA 48 03 C9 C1 EA 10 66 39 54 C8 ? 75 03 B0 01 C3 32 C0 C3 CC 48 89 5C 24 ?").Scan([](const Pattern& _This)
		{
			s_GeneralManagerSlots = _This.Add(3).Rip().As<decltype(s_GeneralManagerSlots)>();
		});
	}



	sagActor* sagActorManager::GetActor(sagGuid _Guid)
	{
		if (!s_GeneralManagerSlots)
			return nullptr;

		return *reinterpret_cast<sagActor**>(*s_GeneralManagerSlots + 0x10i64 * (uint16_t)_Guid);
	}
}