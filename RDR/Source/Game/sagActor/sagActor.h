#pragma once



namespace rage
{
	using sagGuid = uint32_t;

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



	struct animAnimatorComponent
	{
		char m_Padding1[0x010];                      // 0x0000
		sagActor* m_Actor;                           // 0x0010
		char m_Padding2[0xA54];                      // 0x0018
		float m_UnkFloat1;                           // 0x0A6C
		char m_Padding3[0x014];                      // 0x0A70
		float m_UnkFloat2;                           // 0x0A84
	};



	struct unkStruct1
	{
		char m_Padding1[0x038];                      // 0x0000
		animAnimatorComponent* m_AnimatorComponent;  // 0x0038
	};



	struct unkStruct2
	{
		char m_Padding1[0x030];                      // 0x0000
		Vector3 m_Position;                          // 0x0030
	};



	struct sagActorComponent
	{
		char m_Padding1[0x010];                      // 0x0000
		unkStruct1* m_UnkStruct1;                    // 0x0010
		unkStruct2* m_UnkStruct2;                    // 0x0018
		char m_Padding2[0x014];                      // 0x0020
		float m_Unk;                                 // 0x0034
	};



	struct sagActor
	{
		bool IsAlive() const;
		bool IsDrunk() const;

		char m_Padding1[0x008];                      // 0x0000
		sagGuid m_Guid;                              // 0x0008
		char m_Padding2[0x050];                      // 0x0010
		hlthHealthComponent* m_HealthComponent;      // 0x0060
		char m_Padding3[0x048];                      // 0x0068
		sagActorComponent* m_ActorComponent;         // 0x00B0
	};
}