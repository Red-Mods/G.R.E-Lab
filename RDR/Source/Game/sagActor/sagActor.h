#pragma once



namespace rage
{
	struct unkStruct
	{
		char m_Padding1[0x038];                      // 0x0000
		animAnimatorComponent* m_AnimatorComponent;  // 0x0038
	};



	struct Node
	{
		char m_Padding1[0x008];                      // 0x0000
		uint32_t m_Id;                               // 0x0008
	};



	struct ActionNode
	{
		virtual void VFunction000() = 0;
		// virtual void VFunction001() = 0;
		virtual Node* GetNode() = 0; // It should be index 2 (3rd functions), there is something wrong somewhere
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
		unkStruct* m_UnkStruct;                      // 0x0010
		Matrix34* m_Transform;                       // 0x0018
		char m_Padding2[0x090];                      // 0x0020
		ActionNode* m_CurrentActionNode;             // 0x00B0
		ActionNode* m_RequestedActionNode;           // 0x00B8
	};



	struct sagActor
	{
		gohBase* GetGohObject() const;

		bool IsAlive() const;
		bool IsDrunk() const;

		virtual void VFunction000() = 0;

		sagGuid m_Guid;                              // 0x0008
		char m_Padding2[0x02C];                      // 0x000C
		animAnimatorComponent* m_AnimatorComponent;  // 0x0038
		char m_Padding3[0x020];                      // 0x0040
		hlthHealthComponent* m_HealthComponent;      // 0x0060
		char m_Padding4[0x020];                      // 0x0068
		mvrMoverComponent* m_MoverComponent;         // 0x0088
		char m_Padding5[0x020];                      // 0x0090
		sagActorComponent* m_ActorComponent;         // 0x00B0
		char m_Padding6[0x0D0];                      // 0x00B8
		gohGuid m_GohGuid;                           // 0x0188

		/*
		sagGuid m_Guid;                              // 0x0008
		char m_Padding2[0x054];                      // 0x000C
		hlthHealthComponent* m_HealthComponent;      // 0x0060
		char m_Padding3[0x020];                      // 0x0068
		mvrMoverComponent* m_MoverComponent;         // 0x0088
		char m_Padding4[0x020];                      // 0x0090
		sagActorComponent* m_ActorComponent;         // 0x00B0
		char m_Padding5[0x0D0];                      // 0x00B8
		gohGuid m_GohGuid;                           // 0x0188
		*/
	};
}