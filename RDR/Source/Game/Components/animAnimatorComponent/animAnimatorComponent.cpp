#include <pch.h>



namespace rage
{
	double animAnimatorComponent::GetCurrentAnimDuration()
	{
		if (!SigsDatabase::s_animAnimatorComponent__GetCurrentAnimDuration)
			return 0.0;

		return SigsDatabase::s_animAnimatorComponent__GetCurrentAnimDuration(this);
	}
}