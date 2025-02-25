#include <pch.h>



namespace rage
{
	void gohObjectManager::__LoadSigs()
	{
		Pattern("rage::aGuidGohBase::sm_ManagerSlots", "4C 8B 05 ? ? ? ? 0F B7 D1 8B C2 C1 E9 10 48 03 C0 66 41 39 4C C0 ? 75 50 48 03 D2 49 8B 14 D0").Scan([](const Pattern& _This)
		{
			s_GohBaseManagerSlots = _This.Add(3).Rip().As<decltype(s_GohBaseManagerSlots)>();
		});
	}



	gohBase* gohObjectManager::GetObjectFromGuid(gohGuid _Guid)
	{
		if (!s_GohBaseManagerSlots)
			return nullptr;

		return *reinterpret_cast<gohBase**>(*s_GohBaseManagerSlots + 0x10i64 * (uint16_t)_Guid);
	}
}