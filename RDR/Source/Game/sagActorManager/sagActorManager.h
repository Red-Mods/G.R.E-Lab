#pragma once



#include "../sagActor/sagActor.h"



namespace rage
{
	class sagActorManager
	{
		public:
			static sagActor* GetActor(sagGuid _Guid);
	};
}