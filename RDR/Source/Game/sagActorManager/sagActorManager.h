#pragma once



#include "../sagActor/sagActor.h"



namespace rage
{
	class sagActorManager
	{
		public:
			static void __LoadSigs();

			static sagActor* GetActor(sagGuid _Guid);

		private:
			static inline uintptr_t* s_GeneralManagerSlots;
	};
}