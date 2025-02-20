#pragma once



namespace rage
{
	class ioMouse
	{
		public:
			static void __LoadSigs();

			static void DisableCursorAlteration(bool _Disable);

			static void UnlockAndShowCursor(bool _Toggle);

		private:
			using f_UnlockAndShowCursor = bool(*)(bool _Toggle);

			static inline bool* s_DisableCursorAlteration;

			static inline f_UnlockAndShowCursor s_UnlockAndShowCursor;
	};
}