#pragma once



namespace rage
{
	struct sagActor;



	struct Matrix34
	{
		alignas(8) Vector3 Forward;                  // 0x0000
		alignas(8) Vector3 Up;                       // 0x0010
		alignas(8) Vector3 Right;                    // 0x0020
		alignas(8) Vector3 Position;                 // 0x0030
	};



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
		float GetHeading()
		{
			int unk = 2;
			Matrix34* transform = GetTransform(&unk);

			if (!transform)
				return 0.0f;

			return atan2(transform->Right.X, transform->Right.Z) * Math<float>::RadToDeg;
		}

		virtual void VFunction000() = 0;
		virtual void VFunction001() = 0;
		virtual void VFunction002() = 0;
		virtual void VFunction003() = 0;
		virtual void VFunction004() = 0;
		virtual void VFunction005() = 0;
		virtual void VFunction006() = 0;
		virtual void VFunction007() = 0;
		virtual void VFunction008() = 0;
		virtual void VFunction009() = 0;
		virtual void VFunction010() = 0;
		virtual void VFunction011() = 0;
		virtual Matrix34* GetTransform(int* _Unk) = 0;

		char m_Padding1[0x008];                      // 0x0008
		unkStruct1* m_UnkStruct1;                    // 0x0010
		unkStruct2* m_UnkStruct2;                    // 0x0018
	};



	struct mvrMoverComponent
	{
		Vector3 GetPosition() const;
		Vector3 GetRotation() const;

		char m_Padding1[0x040];                      // 0x0000
		Matrix34 m_Transform;                        // 0x0040
		char m_Padding2[0xAB8];                      // 0x0080
		uint32_t m_SomeFlag1;                        // 0x0B38
		char m_Padding3[0x049];                      // 0x0B3C
		uint32_t m_SomeFlag2;                        // 0x0B85
	};



	struct sagActor
	{
		gohBase* GetGohObject() const;

		bool IsAlive() const;
		bool IsDrunk() const;

		virtual void VFunction000() = 0;

		sagGuid m_Guid;                              // 0x0008
		char m_Padding2[0x050];                      // 0x0010
		hlthHealthComponent* m_HealthComponent;      // 0x0060
		char m_Padding3[0x020];                      // 0x0068
		mvrMoverComponent* m_MoverComponent;         // 0x0088
		char m_Padding4[0x020];                      // 0x0090
		sagActorComponent* m_ActorComponent;         // 0x00B0
		char m_Padding5[0x0D0];                      // 0x00B8
		gohGuid m_GohGuid;                           // 0x0188
	};
}