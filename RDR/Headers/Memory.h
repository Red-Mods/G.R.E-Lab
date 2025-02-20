#pragma once



class Memory
{
	public:
		static std::uintptr_t GetGameBaseAddress()
		{
			return reinterpret_cast<std::uintptr_t>(GetModuleHandle(NULL));
		}

		template<typename Addr, typename T>
		static void Write(Addr _address, T _value)
		{
			DWORD oldProtect;
			VirtualProtect((void*)_address, sizeof _value, PAGE_EXECUTE_READWRITE, &oldProtect);

			memcpy((void*)_address, &_value, sizeof _value);

			VirtualProtect((void*)_address, sizeof _value, oldProtect, &oldProtect);
		}

		template<typename Addr>
		static void WriteBytes(Addr _address, const std::vector<BYTE>& _bytes)
		{
			for (size_t i = 0; i < _bytes.size(); i++)
			{
				Write((uintptr_t)_address + i, _bytes[i]);
			}
		}

		template<typename Addr>
		static void Nop(Addr _Address, size_t _Size)
		{
			DWORD oldProtect;
			VirtualProtect((void*)_Address, _Size, PAGE_EXECUTE_READWRITE, &oldProtect);

			memset((void*)_Address, 0x90, _Size);

			VirtualProtect((void*)_Address, _Size, oldProtect, &oldProtect);
		}
};