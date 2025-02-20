#include <pch.h>



namespace Rage
{
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