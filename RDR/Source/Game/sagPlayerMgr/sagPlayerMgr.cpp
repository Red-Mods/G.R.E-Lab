#include <pch.h>



namespace rage
{
	void sagPlayerMgr::__LoadSigs()
	{
		Pattern("rage::sagPlayer::sm_LocalPlayer", "48 89 15 ? ? ? ? E9 ? ? ? ?").Scan([](const Pattern& _This)
		{
			s_LocalPlayer = _This.Add(3).Rip().As<decltype(s_LocalPlayer)>();
		});
	}



	sagPlayer* sagPlayerMgr::GetLocalPlayer()
	{
		if (!s_LocalPlayer)
			return nullptr;

		return *s_LocalPlayer;
	}
}