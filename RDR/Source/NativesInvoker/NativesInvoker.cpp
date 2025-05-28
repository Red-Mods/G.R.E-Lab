#include <pch.h>



namespace rage
{
	static f_NativeHandler o_CREATE_OBJECTSET_IN_LAYOUT;
	static void n_CREATE_OBJECTSET_IN_LAYOUT(NativeCallContext* _NativeCallContext)
	{
		const char* name = _NativeCallContext->GetArgument<const char*>(0);
		int layout = _NativeCallContext->GetArgument<int>(1);
		int type = _NativeCallContext->GetArgument<int>(2);
		bool unk = _NativeCallContext->GetArgument<bool>(3);

		// LOG_DEV_WARNING("%s %d %d %d", name, layout, type, unk);

		return o_CREATE_OBJECTSET_IN_LAYOUT(_NativeCallContext);
	}



	static f_NativeHandler o_FIND_TRAFFIC_PATH;
	static void n_FIND_TRAFFIC_PATH(NativeCallContext* _NativeCallContext)
	{
		float* unk5 = _NativeCallContext->GetArgument<float*>(5);

		if (unk5)
			LOG_DEV_WARNING("FIND_TRAFFIC_PATH: %f", *unk5);

		o_FIND_TRAFFIC_PATH(_NativeCallContext);

		unk5 = _NativeCallContext->GetArgument<float*>(5);

		if (unk5)
			LOG_DEV_WARNING("FIND_TRAFFIC_PATH: %f", *unk5);
	}



	static f_NativeHandler o_SET_GPS_PATH;
	static void n_SET_GPS_PATH(NativeCallContext* _NativeCallContext)
	{
		// int _RegionId, int _Unk1, int _ObjectSet, float _Unk3, float _Unk4, float _Unk5, float _Unk6, const Vector3* _Unk7, bool _Unk8

		int objectSet = _NativeCallContext->GetArgument<int>(2);

		LOG_DEV_WARNING("SET_GPS_PATH: %d", objectSet);

		return o_SET_GPS_PATH(_NativeCallContext);
	}



	struct MeleeWeaponData
	{
		int m_Unk0;
		int m_Unk1;
		int m_Unk2;
		int m_Unk3;
		int m_Unk4;
		int m_Unk5;
		const char* m_Unk6;
		const char* m_Unk7;
		const char* m_Unk8;
		const char* m_Unk9;
		const char* m_Unk10;
		int m_Unk11;
		float m_Unk12;
		float m_Unk13;
		float m_Unk14;
		float m_Unk15;
		float m_Unk16; // Var0.f_84
		const char* m_Unk17;
		float m_Unk18;
		float m_Unk19;
		const char* m_Unk20;
		const char* m_Unk21;
		const char* m_Unk22;
		const char* m_Unk23;
		const char* m_Unk24;
		float m_Unk25;
		float m_Unk26;
		float m_Unk27;
		float m_Unk28;
		float m_Unk29;
		float m_Unk30;
		float m_Unk31;
		float m_Unk32;
		float m_Unk33;
		float m_Unk34;
		const char* m_Unk35;
		const char* m_Unk36;
		const char* m_Unk37;
		float m_Unk38;
		float m_Unk39;
		float m_Unk40;
		float m_Unk41;
		float m_Unk42;
		float m_Unk43;
		float m_Unk44; // Var0.f_232
		int m_Unk45;
		int m_Unk46;
		int m_Unk47;
		int m_Unk48;
		int m_Unk49;
		int m_Unk50;
		int m_Unk51;
		const char* m_Unk52;
		int m_Unk53;
		int m_Unk54;
		float m_Unk55;
		float m_Unk56;
		int m_Unk57;
		float m_Unk58;
		float m_Unk59;
	};



	static f_NativeHandler o_INIT_NATIVE_WEAPONENUM_MELEE;
	static void n_INIT_NATIVE_WEAPONENUM_MELEE(NativeCallContext* _NativeCallContext)
	{
		MeleeWeaponData* weaponData = _NativeCallContext->GetArgument<MeleeWeaponData*>(2);

		if (weaponData)
		{
			LOG_DEV_WARNING("%d", weaponData->m_Unk0);
			LOG_DEV_WARNING("%d", weaponData->m_Unk1);
			LOG_DEV_WARNING("%d", weaponData->m_Unk2);
			LOG_DEV_WARNING("%d", weaponData->m_Unk3);
			LOG_DEV_WARNING("%d", weaponData->m_Unk4);
			LOG_DEV_WARNING("%d", weaponData->m_Unk5);
			LOG_DEV_WARNING("%s", weaponData->m_Unk6);
			LOG_DEV_WARNING("%s", weaponData->m_Unk7);
			LOG_DEV_WARNING("%s", weaponData->m_Unk8);
			LOG_DEV_WARNING("%s", weaponData->m_Unk9);
			LOG_DEV_WARNING("%s", weaponData->m_Unk10);
			LOG_DEV_WARNING("%d", weaponData->m_Unk11);
			LOG_DEV_WARNING("%f", weaponData->m_Unk12);
			LOG_DEV_WARNING("%f", weaponData->m_Unk13);
			LOG_DEV_WARNING("%f", weaponData->m_Unk14);
			LOG_DEV_WARNING("%f", weaponData->m_Unk15);
			LOG_DEV_WARNING("%f", weaponData->m_Unk16);
			LOG_DEV_WARNING("%s", weaponData->m_Unk17);
			LOG_DEV_WARNING("%f", weaponData->m_Unk18);
			LOG_DEV_WARNING("%f", weaponData->m_Unk19);
			LOG_DEV_WARNING("%s", weaponData->m_Unk20);
			LOG_DEV_WARNING("%s", weaponData->m_Unk21);
			LOG_DEV_WARNING("%s", weaponData->m_Unk22);
			LOG_DEV_WARNING("%s", weaponData->m_Unk23);
			LOG_DEV_WARNING("%s", weaponData->m_Unk24);
			LOG_DEV_WARNING("%f", weaponData->m_Unk25);
			LOG_DEV_WARNING("%f", weaponData->m_Unk26);
			LOG_DEV_WARNING("%f", weaponData->m_Unk27);
			LOG_DEV_WARNING("%f", weaponData->m_Unk28);
			LOG_DEV_WARNING("%f", weaponData->m_Unk29);
			LOG_DEV_WARNING("%f", weaponData->m_Unk30);
			LOG_DEV_WARNING("%f", weaponData->m_Unk31);
			LOG_DEV_WARNING("%f", weaponData->m_Unk32);
			LOG_DEV_WARNING("%f", weaponData->m_Unk33);
			LOG_DEV_WARNING("%f", weaponData->m_Unk34);
			LOG_DEV_WARNING("%s", weaponData->m_Unk35);
			LOG_DEV_WARNING("%s", weaponData->m_Unk36);
			LOG_DEV_WARNING("%s", weaponData->m_Unk37);
			LOG_DEV_WARNING("%f", weaponData->m_Unk38);
			LOG_DEV_WARNING("%f", weaponData->m_Unk39);
			LOG_DEV_WARNING("%f", weaponData->m_Unk40);
			LOG_DEV_WARNING("%f", weaponData->m_Unk41);
			LOG_DEV_WARNING("%f", weaponData->m_Unk42);
			LOG_DEV_WARNING("%f", weaponData->m_Unk43);
			LOG_DEV_WARNING("%f", weaponData->m_Unk44);
			LOG_DEV_WARNING("%d", weaponData->m_Unk45);
			LOG_DEV_WARNING("%d", weaponData->m_Unk46);
			LOG_DEV_WARNING("%d", weaponData->m_Unk47);
			LOG_DEV_WARNING("%d", weaponData->m_Unk48);
			LOG_DEV_WARNING("%d", weaponData->m_Unk49);
			LOG_DEV_WARNING("%d", weaponData->m_Unk50);
			LOG_DEV_WARNING("%d", weaponData->m_Unk51);
			LOG_DEV_WARNING("%s", weaponData->m_Unk52);
			LOG_DEV_WARNING("%d", weaponData->m_Unk53);
			LOG_DEV_WARNING("%d", weaponData->m_Unk54);
			LOG_DEV_WARNING("%f", weaponData->m_Unk55);
			LOG_DEV_WARNING("%f", weaponData->m_Unk56);
			LOG_DEV_WARNING("%d", weaponData->m_Unk57);
			LOG_DEV_WARNING("%f", weaponData->m_Unk58);
			LOG_DEV_WARNING("%f", weaponData->m_Unk59);
		}

		return o_INIT_NATIVE_WEAPONENUM_MELEE(_NativeCallContext);
	}



	static f_NativeHandler o_ADD_IDLEFX_TO_WEAPON;
	static void n_ADD_IDLEFX_TO_WEAPON(NativeCallContext* _NativeCallContext)
	{
		int weaponModel = _NativeCallContext->GetArgument<int>(0);
		const char* fxName = _NativeCallContext->GetArgument<const char*>(1);
		Vector2 offsetXY = _NativeCallContext->GetArgument<Vector2>(2);
		float offsetZ = _NativeCallContext->GetArgument<float>(3);

		LOG_DEV_WARNING("%d | %s | %f %f %f", weaponModel, fxName, offsetXY.X, offsetXY.Y, offsetZ);

		return o_ADD_IDLEFX_TO_WEAPON(_NativeCallContext);
	}



	void NativesInvoker::Initialize()
	{
		Pattern("rage::scrThread::sm_CommandsRegistrationTable", "4C 8B 1D ? ? ? ? 41 8B C1").Scan([](const Pattern& _This)
		{
			s_NativeRegistration = _This.Add(3).Rip().As<decltype(s_NativeRegistration)>();
		});

		Pattern("rage::scrThread::RegisterCommand", "48 89 5C 24 ? 57 48 83 EC 20 44 8B 0D ? ? ? ?").Scan([](const Pattern& _This)
		{
			s_RegisterNative = _This.As<decltype(s_RegisterNative)>();
		});

		LOG_INFO("Waiting for native invoker...");

		while (!IsInitialized())
		{
			Sleep(1);
		}

		// Hook::Create("INIT_NATIVE_WEAPONENUM_MELEE", GetNativeHandler(0xA6C4E59F), &n_INIT_NATIVE_WEAPONENUM_MELEE, &o_INIT_NATIVE_WEAPONENUM_MELEE);
		// Hook::Create("ADD_IDLEFX_TO_WEAPON", GetNativeHandler(0xF4641CF4), &n_ADD_IDLEFX_TO_WEAPON, &o_ADD_IDLEFX_TO_WEAPON);

		//Hook::Create("CREATE_OBJECTSET_IN_LAYOUT", GetNativeHandler(0x921B5F2B), &n_CREATE_OBJECTSET_IN_LAYOUT, &o_CREATE_OBJECTSET_IN_LAYOUT);
		//Hook::Create("FIND_TRAFFIC_PATH", GetNativeHandler(0xA5BDC21D), &n_FIND_TRAFFIC_PATH, &o_FIND_TRAFFIC_PATH);
		//Hook::Create("SET_GPS_PATH", GetNativeHandler(0xD82F910C), &n_SET_GPS_PATH, &o_SET_GPS_PATH);

		LOG_INFO("Successfully initialized natives invoker");
	}



	bool NativesInvoker::IsInitialized()
	{
		if (!s_NativeRegistration)
			return false;

		if (*s_NativeRegistration == NULL)
			return false;

		uint32_t modulator = *((uint32_t*)s_NativeRegistration + 2);

		uint32_t lastHash = 0xA0AE0C98;
		uint32_t index = lastHash % modulator;
		uint32_t tempHash = lastHash;

		uint32_t hash = *((uint32_t*)*s_NativeRegistration + 4 * index);

		while (hash != lastHash)
		{
			tempHash = (tempHash >> 1) + 1;
			index = (tempHash + index) % modulator;

			hash = *((uint32_t*)*s_NativeRegistration + 4 * index);

			if (!hash)
			{
				return false;
			}
		}

		return true;
	}



	f_NativeHandler NativesInvoker::GetNativeHandler(unsigned int _Hash)
	{
		uint32_t modulator = *((uint32_t*)s_NativeRegistration + 2);

		uint32_t index = _Hash % modulator;
		uint32_t tempHash = _Hash;

		uint32_t hash = *(uint32_t*)(*s_NativeRegistration + 16i64 * index);

		while (hash != _Hash)
		{
			tempHash = (tempHash >> 1) + 1;
			index = (tempHash + index) % modulator;

			hash = *(uint32_t*)(*s_NativeRegistration + 16i64 * index);

			if (!hash)
			{
				LOG_ERROR("Failed to find native with hash 0x%08X", _Hash);

				return nullptr;
			}
		}
		
		return (f_NativeHandler)*(uintptr_t*)(*s_NativeRegistration + 16i64 * index + 8);
	}



	void NativesInvoker::RegisterNative(uint32_t _Hash, f_NativeHandler _Handler)
	{
		return s_RegisterNative(nullptr, _Hash, _Handler);
	}
}