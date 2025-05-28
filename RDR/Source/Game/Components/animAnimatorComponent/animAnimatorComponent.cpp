#include <pch.h>



namespace rage
{
	void animAnimatorComponent::StopCurrentAnim(bool _Instant)
	{
		if (!SigsDatabase::s_animAnimatorComponent__StopCurrentAnim)
			return;

		return SigsDatabase::s_animAnimatorComponent__StopCurrentAnim(this, _Instant);
	}



	double animAnimatorComponent::GetCurrentAnimDuration()
	{
		if (!SigsDatabase::s_animAnimatorComponent__GetCurrentAnimDuration)
			return 0.0;

		return SigsDatabase::s_animAnimatorComponent__GetCurrentAnimDuration(this);
	}
}