#include <pch.h>



namespace rage
{
	sagActor* sagActorManager::GetActor(sagGuid _Guid)
	{
		if (!SigsDatabase::s_GeneralManagerSlots)
			return nullptr;

		return *reinterpret_cast<sagActor**>(*SigsDatabase::s_GeneralManagerSlots + 0x10i64 * (uint16_t)_Guid);
	}
}