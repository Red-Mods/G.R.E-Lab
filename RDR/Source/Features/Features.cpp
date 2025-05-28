#include <pch.h>



Features::Features() : Fiber()
{
    SetName("FeaturesUpdate");
}



static void ReleaseGPSObjectSet(ObjectSet_t _ObjectSet)
{
	if (!OBJECT::IS_OBJECTSET_VALID(_ObjectSet))
	{
		return;
	}

	while (OBJECT::GET_OBJECTSET_SIZE(_ObjectSet) >= 0)
	{
		Object_t object = OBJECT::GET_INDEXED_OBJECT_IN_OBJECTSET(0, _ObjectSet);

		OBJECT::REMOVE_OBJECT_FROM_OBJECTSET(object, _ObjectSet);

		OBJECT::CLEAN_OBJECTSET(_ObjectSet);

		if (OBJECT::IS_OBJECT_VALID(object))
		{
			CURVES::RELEASE_CURVE(OBJECT::GET_CURVE_FROM_OBJECT(object));
		}

		ThisFiber::Wait(0);
	}
}



void Features::Start()
{
	/*
	// Clear existing GPS path on the map
	HUD::CLEAR_GPS_PATH(0);
	HUD::CLEAR_GPS_PATH(1);
	HUD::CLEAR_GPS_PATH(2);

	Layout_t layout = OBJECT::FIND_NAMED_LAYOUT("usergps");

	if (!OBJECT::IS_LAYOUTREF_VALID(layout))
	{
		layout = OBJECT::CREATE_LAYOUT("usergps");
	}

	if (!OBJECT::IS_OBJECTSET_VALID(GPSObjectSet))
	{
		GPSObjectSet = OBJECT::CREATE_OBJECTSET_IN_LAYOUT("UserGPSPath", layout, OBJECT_TYPE_ObjectSet, true);
	}

	// Set a GPS path on the map
	Vector3 destCoords = Vector3(-2175.62f, 16.31f, 2613.50f);

	Actor_t localPlayerActor = ACTOR::GET_PLAYER_ACTOR(-1);

	Vector3 srcPosition = ACTOR::GET_POSITION(localPlayerActor);

	int unk = -1;
	if (HUD::FIND_TRAFFIC_PATH(layout, GPSObjectSet, &srcPosition, &destCoords, 0x60030, &unk))
	{
		HUD::SET_GPS_PATH(0, -1, GPSObjectSet, 0.41f, 0.57f, 0.23f, 1.0f, &destCoords, true);
		ACTOR::REGISTER_GPS_CURVE_OBJECTSET(GPSObjectSet);
	}
	*/
}



void Features::Update()
{
	rage::sagPlayer* localPlayer = rage::sagPlayerMgr::GetLocalPlayer();

	if (!localPlayer)
		return;

	rage::sagActor* playerActor = localPlayer->GetPlayerActor();

	if (!playerActor)
		return;

	if (rage::ioKeyboard::KeyPressed(KEY_F1))
	{
		playerActor->m_AnimatorComponent->StopCurrentAnim(true);
	}

	if (rage::ioKeyboard::KeyPressed(KEY_F2))
	{
		playerActor->m_AnimatorComponent->StopCurrentAnim(false);
	}

    /*
    rage::sagPlayer* localPlayer = rage::sagPlayerMgr::GetLocalPlayer();

    if (!localPlayer)
        return;

    rage::sagActor* playerActor = localPlayer->GetPlayerActor();

    if (!playerActor)
        return;

    if (!playerActor->m_MoverComponent)
        return;

    // playerActor->m_MoverComponent->EnableMoverCollision(s_EnablePlayerCollision);
    */
}