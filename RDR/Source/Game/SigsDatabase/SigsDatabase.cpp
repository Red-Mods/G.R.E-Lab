#include <pch.h>



void SigsDatabase::Scan()
{
	if (s_HasBeenScanned)
		return;

	Pattern("rage::ioMouse::sm_DisableCursorAlteration", "0F B6 0D ? ? ? ? 84 C9").Scan([](const Pattern& _This)
	{
		s_DisableCursorAlteration = _This.Add(3).Rip().As<decltype(s_DisableCursorAlteration)>();
	});

	Pattern("rage::ioMouse::UnlockAndShowCursor", "40 53 48 83 EC 20 0F B6 D9 0F B6 0D ? ? ? ?").Scan([](const Pattern& _This)
	{
		s_UnlockAndShowCursor = _This.As<decltype(s_UnlockAndShowCursor)>();
	});

	Pattern("rage::UIInput::sm_DisableAllInputs", "48 83 BB ? ? ? ? ? 74 5A").Scan([](const Pattern& _This)
	{
		s_DisableAllInputs = _This.Sub(1).As<decltype(s_DisableAllInputs)>();
	});

	Pattern("rage::aGuidGohBase::sm_ManagerSlots", "4C 8B 05 ? ? ? ? 0F B7 D1 8B C2 C1 E9 10 48 03 C0 66 41 39 4C C0 ? 75 50 48 03 D2 49 8B 14 D0").Scan([](const Pattern& _This)
	{
		s_GohBaseManagerSlots = _This.Add(3).Rip().As<decltype(s_GohBaseManagerSlots)>();
	});

	Pattern("rage::aGuidGeneral::sm_ManagerSlots", "48 8B 05 ? ? ? ? 0F B7 CA 48 03 C9 C1 EA 10 66 39 54 C8 ? 75 03 B0 01 C3 32 C0 C3 CC 48 89 5C 24 ?").Scan([](const Pattern& _This)
	{
		s_GeneralManagerSlots = _This.Add(3).Rip().As<decltype(s_GeneralManagerSlots)>();
	});

	Pattern("rage::sagPlayer::sm_LocalPlayer", "48 89 15 ? ? ? ? E9 ? ? ? ?").Scan([](const Pattern& _This)
	{
		s_LocalPlayer = _This.Add(3).Rip().As<decltype(s_LocalPlayer)>();
	});

	Pattern("rage::animAnimatorComponent::GetCurrentAnimDuration", "E8 ? ? ? ? 0F 2F 05 ? ? ? ? 0F 82 ? ? ? ? 48 8D 15 ? ? ? ?").Scan([](const Pattern& _This)
	{
		s_animAnimatorComponent__GetCurrentAnimDuration = _This.Add(1).Rip().As<decltype(s_animAnimatorComponent__GetCurrentAnimDuration)>();
	});

	Pattern("rage::mvrMoverComponent::EnableMoverCollision", "E8 ? ? ? ? C6 87 ? ? ? ? ? 0F B6 47 5A").Scan([](const Pattern& _This)
	{
		s_mvrMoverComponent__EnableMoverCollision = _This.Add(1).Rip().As<decltype(s_mvrMoverComponent__EnableMoverCollision)>();
	});

	s_HasBeenScanned = true;
}