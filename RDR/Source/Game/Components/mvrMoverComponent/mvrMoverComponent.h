#pragma once



namespace rage
{
	struct mvrMoverComponent
	{
		void EnableMoverCollision(bool _Value);

		Vector3 GetPosition() const;
		Vector3 GetRotation() const;

		char m_Padding1[0x010];                      // 0x0000
		sagActor* m_Actor;                           // 0x0010
		char m_Padding2[0x028];                      // 0x0018
		Matrix34 m_Transform;                        // 0x0040
		char m_Padding3[0xAB8];                      // 0x0080
		uint32_t m_SomeFlag1;                        // 0x0B38
		char m_Padding4[0x049];                      // 0x0B3C
		uint32_t m_SomeFlag2;                        // 0x0B85
	};
}