#include <pch.h>



namespace rage
{
	void ioMouse::DisableCursorAlteration(bool _Disable)
	{
		if (!SigsDatabase::s_DisableCursorAlteration)
			return;

		*SigsDatabase::s_DisableCursorAlteration = _Disable;
	}



	void ioMouse::UnlockAndShowCursor(bool _Toggle)
	{
		if (!SigsDatabase::s_UnlockAndShowCursor)
			return;

		SigsDatabase::s_UnlockAndShowCursor(_Toggle);
	}
}