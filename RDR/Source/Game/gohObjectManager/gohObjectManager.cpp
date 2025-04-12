#include <pch.h>



namespace rage
{
	gohBase* gohObjectManager::GetObjectFromGuid(gohGuid _Guid)
	{
		if (!SigsDatabase::s_GohBaseManagerSlots)
			return nullptr;

		return *reinterpret_cast<gohBase**>(*SigsDatabase::s_GohBaseManagerSlots + 0x10i64 * (uint16_t)_Guid);
	}
}