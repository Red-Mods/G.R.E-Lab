#pragma once



#include "../gohBase/gohBase.h"



namespace rage
{

	class gohObjectManager
	{
		public:
			static void __LoadSigs();

			static gohBase* GetObjectFromGuid(gohGuid _Guid);

		private:
			static inline uintptr_t* s_GohBaseManagerSlots;
	};
}