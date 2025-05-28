#pragma once



namespace rage
{
	struct sagActor;



	struct unkAnimStruct1
	{
		char m_Padding1[0x030];                      // 0x0000
		const char* m_UnkName;                       // 0x0030
	};



	struct unkAnimStruct2
	{
		char m_Padding1[0x0A0];                      // 0x0000
		const char* m_UnkName;                       // 0x00A0
	};



	struct animAnimatorComponent
	{
		void StopCurrentAnim(bool _Instant);
		double GetCurrentAnimDuration();

		char m_Padding1[0x008];                      // 0x0000
		unkAnimStruct1* m_UnkAnimStruct1;            // 0x0008
		sagActor* m_Actor;                           // 0x0010
		char m_Padding2[0xA54];                      // 0x0018
		float m_UnkFloat1;                           // 0x0A6C
		char m_Padding3[0x014];                      // 0x0A70
		float m_UnkFloat2;                           // 0x0A84
		float m_UnkFloat3;                           // 0x0A88
		float m_UnkFloat4;                           // 0x0A8C
		float m_CustomAnimSpeed;                     // 0x0A90
		char m_Padding4[0x07C];                      // 0x0A94
		unkAnimStruct2* m_UnkAnimStruct2;            // 0x0B10
	};
}