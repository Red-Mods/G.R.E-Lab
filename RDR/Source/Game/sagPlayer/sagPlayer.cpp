#include <pch.h>

#include "../sagActorManager/sagActorManager.h"



namespace rage
{
	sagGuid sagPlayer::GetPlayerGuid() const
	{
		return m_Guid;
	}



	sagActor* sagPlayer::GetPlayerActor() const
	{
		return sagActorManager::GetActor(m_Guid);
	}



	unkStruct4* sagPlayer::MaybeGetCurrentWeapon() const
	{
		return m_CurrentWeapon;
	}



	void sagPlayer::DisablePlayerControl(bool _Disable)
	{
		m_PlayerMovementsFlag = _Disable;
		m_CameraMovementsFlag = _Disable;
		m_StrafeMovementsFlag = _Disable;
		m_UnkMovementsFlag = _Disable;
	}
}