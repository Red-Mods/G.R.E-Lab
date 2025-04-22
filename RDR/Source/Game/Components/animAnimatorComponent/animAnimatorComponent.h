#pragma once



namespace rage
{
	struct sagActor;



	struct animAnimatorComponent
	{
		double GetCurrentAnimDuration();

		char m_Padding1[0x010];                      // 0x0000
		sagActor* m_Actor;                           // 0x0010
		char m_Padding2[0xA54];                      // 0x0018
		float m_UnkFloat1;                           // 0x0A6C
		char m_Padding3[0x014];                      // 0x0A70
		float m_UnkFloat2;                           // 0x0A84
	};
}