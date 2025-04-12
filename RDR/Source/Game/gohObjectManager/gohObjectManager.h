#pragma once



#include "../gohBase/gohBase.h"



namespace rage
{
	class gohObjectManager
	{
		public:
			static gohBase* GetObjectFromGuid(gohGuid _Guid);
	};
}