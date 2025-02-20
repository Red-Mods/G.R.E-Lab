#pragma once



#include "../sagActor/sagActor.h"



namespace rage
{
	struct unkStruct4
	{
		char m_Padding1[0x014];                     // 0x0000
		uint32_t m_IsWeaponZoomed;                  // 0x0014
	};



	class sagPlayer
	{
		public:
			sagGuid GetPlayerGuid() const;
			sagActor* GetPlayerActor() const;

			unkStruct4* MaybeGetCurrentWeapon() const;

			void DisablePlayerControl(bool _Disable);

		private:
			char m_Padding1[0x104];                 // 0x0000
			uint16_t m_PlayerMovementsFlag;         // 0x0104
			uint16_t m_CameraMovementsFlag;         // 0x0106
			uint16_t m_StrafeMovementsFlag;         // 0x0108
			uint16_t m_UnkMovementsFlag;            // 0x010A
			char m_Padding2[0x304];                 // 0x010C
			unkStruct4* m_CurrentWeapon;            // 0x0410
			char m_Padding3[0x1D1];                 // 0x0418
			bool m_HasControl;                      // 0x05E9
			char m_Padding4[0x002];                 // 0x05EA
			sagGuid m_Guid;                         // 0x05EC
			char m_Padding5[0x00C];                 // 0x05F0
			int m_Unk;                              // 0x05FC
	};
}