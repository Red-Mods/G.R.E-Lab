#include <pch.h>



namespace rage
{
	sagPlayer* sagPlayerMgr::GetLocalPlayer()
	{
		if (!SigsDatabase::s_LocalPlayer)
			return nullptr;

		return *SigsDatabase::s_LocalPlayer;
	}
}