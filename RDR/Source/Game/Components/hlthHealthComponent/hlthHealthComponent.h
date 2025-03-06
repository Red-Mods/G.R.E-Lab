#pragma once



namespace rage
{
	struct sagActor;



	struct hlthHealthComponent
	{
		void SetMaxHitPoints(float _MaxHitPoints);

		char m_Padding1[0x010];                      // 0x0000
		sagActor* m_Actor;                           // 0x0010
		char m_Padding2[0x004];                      // 0x0018
		float m_MaxHitPoints;                        // 0x001C
		float m_CurrentHealth;                       // 0x0020
		char m_Padding3[0x151];                      // 0x0024
		bool m_IsDrunk;                              // 0x0175
	};
}