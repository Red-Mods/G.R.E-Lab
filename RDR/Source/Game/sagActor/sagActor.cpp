#include <pch.h>



namespace rage
{
	gohBase* sagActor::GetGohObject() const
	{
		return gohObjectManager::GetObjectFromGuid(m_GohGuid);
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