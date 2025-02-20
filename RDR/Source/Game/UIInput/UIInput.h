#pragma once



namespace rage
{
	class UIInput
	{
		public:
			static void __LoadSigs();
			
			static void DisableAllInputs(bool _Disable);

		private:
			static inline void* s_DisableAllInputs;
	};
}