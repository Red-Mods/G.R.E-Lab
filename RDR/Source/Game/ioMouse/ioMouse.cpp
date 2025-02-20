#include <pch.h>



namespace rage
{
	void ioMouse::__LoadSigs()
	{
		Pattern("rage::ioMouse::sm_DisableCursorAlteration", "0F B6 0D ? ? ? ? 84 C9").Scan([](const Pattern& _This)
		{
			s_DisableCursorAlteration = _This.Add(3).Rip().As<decltype(s_DisableCursorAlteration)>();
		});

		Pattern("rage::ioMouse::UnlockAndShowCursor", "40 53 48 83 EC 20 0F B6 D9 0F B6 0D ? ? ? ?").Scan([](const Pattern& _This)
		{
			s_UnlockAndShowCursor = _This.As<decltype(s_UnlockAndShowCursor)>();
		});
	}



	void ioMouse::DisableCursorAlteration(bool _Disable)
	{
		if (!s_DisableCursorAlteration)
			return;

		*s_DisableCursorAlteration = _Disable;
	}



	void ioMouse::UnlockAndShowCursor(bool _Toggle)
	{
		s_UnlockAndShowCursor(_Toggle);
	}
}