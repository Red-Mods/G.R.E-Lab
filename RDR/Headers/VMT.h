#pragma once



class VMT
{
	public:
		VMT() : m_VTablePtr(nullptr) {}
		VMT(void* _Address)
		{
			m_VTablePtr = _Address;
			m_OriginalVTable = {};
		}

		~VMT() = default;

		void operator=(void* _Address)
		{
			m_VTablePtr = _Address;
			m_OriginalVTable = {};
		}

		void Hook(size_t _Index, void* _NewFunction)
		{
			if (m_VTablePtr == nullptr)
			{
				return;
			}

			void** vtable = (void**)m_VTablePtr;

			m_OriginalVTable.emplace(_Index, vtable[_Index]);

			DWORD old_protect;
			VirtualProtect(&vtable[_Index], sizeof(void*), PAGE_EXECUTE_READWRITE, &old_protect);

			vtable[_Index] = _NewFunction;

			VirtualProtect(&vtable[_Index], sizeof(void*), old_protect, &old_protect);
		}

		template<typename T1, typename T2>
		void Hook(size_t _Index, T1 _NewFunction, T2** _OriginalFunction)
		{
			if (m_VTablePtr == nullptr)
			{
				return;
			}

			void** vtable = (void**)m_VTablePtr;

			*reinterpret_cast<void**>(_OriginalFunction) = vtable[_Index];

			m_OriginalVTable.emplace(_Index, vtable[_Index]);

			DWORD old_protect;
			VirtualProtect(&vtable[_Index], sizeof(void*), PAGE_EXECUTE_READWRITE, &old_protect);

			vtable[_Index] = (void*)_NewFunction;

			VirtualProtect(&vtable[_Index], sizeof(void*), old_protect, &old_protect);
		}

		void Unhook(size_t _Index)
		{
			if (m_VTablePtr == nullptr)
			{
				return;
			}

			if (!m_OriginalVTable.contains(_Index))
			{
				return;
			}

			void** vtable = (void**)m_VTablePtr;

			DWORD old_protect;
			VirtualProtect(&vtable[_Index], sizeof(void*), PAGE_EXECUTE_READWRITE, &old_protect);

			vtable[_Index] = m_OriginalVTable.at(_Index);

			VirtualProtect(&vtable[_Index], sizeof(void*), old_protect, &old_protect);
		}

		void UnhookAll()
		{
			size_t count = GetFunctionsCount();

			for (size_t i = 0; i < count; i++)
			{
				Unhook(i);
			}
		}

		template<typename R, typename ...A>
		R CallOriginal(size_t _Index, A... _Args)
		{
			return ((R(*)(A...))m_OriginalVTable[_Index])(_Args...);
		}

		template<typename R, typename ...A>
		R Call(size_t _Index, A... _Args)
		{
			void** vtable = (void**)m_VTablePtr;

			return ((R(*)(A...))vtable[_Index])(_Args...);
		}

		void* GetVTablePtr()
		{
			return m_VTablePtr;
		}

		void* GetVTableFunctionPtr(size_t _Index)
		{
			void** vtable = (void**)m_VTablePtr;

			return vtable[_Index];
		}

		size_t GetFunctionsCount()
		{
			MEMORY_BASIC_INFORMATION mbi;
			size_t i = 0;

			void** vtable = (void**)m_VTablePtr;

			while (VirtualQuery(reinterpret_cast<LPCVOID>(vtable[i]), &mbi, sizeof(mbi)))
			{
				#define PAGE_EXECUTABLE (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)

				if ((mbi.State != MEM_COMMIT) || (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) || !(mbi.Protect & PAGE_EXECUTABLE))
				{
					break;
				}

				++i;
			}

			return i;
		}

	private:
		void* m_VTablePtr;
		std::unordered_map<size_t, void*> m_OriginalVTable;
};