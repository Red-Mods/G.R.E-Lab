#pragma once



namespace rage
{
	class ioMouse
	{
		public:
			static void DisableCursorAlteration(bool _Disable);

			static void UnlockAndShowCursor(bool _Toggle);
	};
}