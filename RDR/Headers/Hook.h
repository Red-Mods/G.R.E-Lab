#pragma once



class Hook
{
	public:
		template<typename T>
		static bool Create(const char* _Name, void* _Target, T _NewFunction)
		{
			MH_Initialize();

			MH_STATUS status = MH_CreateHook(_Target, _NewFunction, NULL);

			if (status != MH_OK)
			{
				LOG_ERROR("Failed to create hook '%s'", _Name);

				return false;
			}

			status = MH_EnableHook(_Target);

			if (status != MH_OK)
			{
				LOG_ERROR("Failed to enable hook '%s'", _Name);

				return false;
			}

			LOG_DEV_INFO("Hooked '%s'", _Name);

			return true;
		}

		static bool Create(const char* _Name, void* _Target, void* _NewFunction)
		{
			MH_Initialize();

			MH_STATUS status = MH_CreateHook(_Target, _NewFunction, NULL);

			if (status != MH_OK)
			{
				LOG_ERROR("Failed to create hook '%s'", _Name);

				return false;
			}

			status = MH_EnableHook(_Target);

			if (status != MH_OK)
			{
				LOG_ERROR("Failed to enable hook '%s'", _Name);

				return false;
			}

			LOG_DEV_INFO("Hooked '%s'", _Name);

			return true;
		}

		template<typename T>
		static bool Create(const char* _Name, void* _Target, void* _NewFunction, T** _Original)
		{
			MH_Initialize();

			MH_STATUS status = MH_CreateHook(_Target, _NewFunction, reinterpret_cast<void**>(_Original));

			if (status != MH_OK)
			{
				LOG_ERROR("Failed to create hook '%s'", _Name);

				return false;
			}

			status = MH_EnableHook(_Target);

			if (status != MH_OK)
			{
				LOG_ERROR("Failed to enable hook '%s'", _Name);

				return false;
			}

			LOG_DEV_INFO("Hooked '%s'", _Name);

			return true;
		}

		static void Remove(void* _Target)
		{
			MH_DisableHook(_Target);
			MH_RemoveHook(_Target);

			LOG_DEV_INFO("Unhooked '0x%p'", _Target);
		}

		static void RemoveAll()
		{
			MH_DisableHook(MH_ALL_HOOKS);
			MH_RemoveHook(MH_ALL_HOOKS);
		}
};