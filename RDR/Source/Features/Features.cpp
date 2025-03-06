#include <pch.h>



Features::Features() : Fiber()
{
    SetName("FeaturesUpdate");
}



void Features::Update()
{
    rage::sagPlayer* localPlayer = rage::sagPlayerMgr::GetLocalPlayer();

    if (!localPlayer)
        return;

    rage::sagActor* playerActor = localPlayer->GetPlayerActor();

    if (!playerActor)
        return;

    if (!playerActor->m_MoverComponent)
        return;

    // playerActor->m_MoverComponent->EnableMoverCollision(s_EnablePlayerCollision);
}