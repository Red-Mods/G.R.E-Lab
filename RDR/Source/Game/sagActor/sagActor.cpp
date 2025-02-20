#include <pch.h>



namespace rage
{
	void hlthHealthComponent::SetMaxHitPoints(float _MaxHitPoints)
	{
		m_MaxHitPoints = _MaxHitPoints;
	}



	bool sagActor::IsAlive() const
	{
		return m_HealthComponent && m_HealthComponent->m_CurrentHealth > 0.0f;
	}



	bool sagActor::IsDrunk() const
	{
		return m_HealthComponent && m_HealthComponent->m_IsDrunk;
	}
}