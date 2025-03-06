#include <pch.h>



void SigsDatabase::Scan()
{
	if (s_HasBeenScanned)
		return;

	Pattern("mvrMoverComponent::EnableMoverCollision", "E8 ? ? ? ? C6 87 ? ? ? ? ? 0F B6 47 5A").Scan([](const Pattern& _This)
	{
		s_mvrMoverComponent__EnableMoverCollision = _This.Add(1).Rip().As<decltype(s_mvrMoverComponent__EnableMoverCollision)>();
	});

	s_HasBeenScanned = true;
}