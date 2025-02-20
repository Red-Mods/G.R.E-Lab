#pragma once



namespace rage
{
	class sagPlayerMgr
	{
		public:
			static void __LoadSigs();

			static sagPlayer* GetLocalPlayer();

		private:
			static inline sagPlayer** s_LocalPlayer;
	};
}