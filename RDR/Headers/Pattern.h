#pragma once



class Pattern
{
	public:
		Pattern() = default;
		explicit Pattern(void* _Handle) : m_Handle(_Handle), m_Name(nullptr), m_Pattern(nullptr) {}
		explicit Pattern(std::uintptr_t _Ptr) : m_Handle(reinterpret_cast<void*>(_Ptr)), m_Name(nullptr), m_Pattern(nullptr) {}
		explicit Pattern(const char* _Name, const char* _Pattern) : m_Handle(nullptr), m_Name(_Name), m_Pattern(_Pattern) {}

		void Scan(std::function<void(const Pattern&)> _Callback, size_t _Skip = 0, bool _NoLog = false)
		{
			size_t skipAmount = _Skip;

			std::vector<BYTE> patternBytes;
			std::istringstream iss(m_Pattern);
			std::string w;

			while (iss >> w)
			{
				const char* data = w.data();

				if (data[0] == '?') // Push an empty byte if it's a '?'.
				{
					patternBytes.push_back(NULL);
				}
				else if (w.length() == 2 && isxdigit(data[0]) && isxdigit(data[1])) // Check if it's a valid hex byte.
				{
					patternBytes.push_back(Utils::StringToByte(w));
				}
				else
				{
					LOG_DEV_ERROR("Invalid pattern format '%s'", m_Name);

					return;
				}
			}

			MODULEINFO moduleInfo;
			GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &moduleInfo, sizeof MODULEINFO);

			std::uintptr_t moduleStart = std::uintptr_t(moduleInfo.lpBaseOfDll);

			for (DWORD i = 0; i < moduleInfo.SizeOfImage; i++)
			{
				BYTE* data = reinterpret_cast<BYTE*>(moduleStart + i);

				bool found = true;

				for (size_t j = 0; j < patternBytes.size(); j++)
				{
					if (patternBytes[j] != NULL && data[j] != patternBytes[j])
					{
						found = false;

						break;
					}
				}

				if (found)
				{
					LOG_DEV_INFO("Found '%s'", m_Name);

					if (skipAmount > 0)
					{
						skipAmount--;

						continue;
					}

					m_Handle = data;

					_Callback(*this);

					return;
				}
			}

			LOG_ERROR("Failed to find '%s'", m_Name);
		}

		void ScanAll(std::function<void(const Pattern&)> _Callback)
		{
			std::vector<BYTE> patternBytes;
			std::istringstream iss(m_Pattern);
			std::string w;

			while (iss >> w)
			{
				const char* data = w.data();

				if (data[0] == '?') // Push an empty byte if it's a '?'.
				{
					patternBytes.push_back(NULL);
				}
				else if (w.length() == 2 && isxdigit(data[0]) && isxdigit(data[1])) // Check if it's a valid hex byte.
				{
					patternBytes.push_back(Utils::StringToByte(w));
				}
				else
				{
					LOG_DEV_ERROR("Invalid pattern format '%s'", m_Name);

					return;
				}
			}

			MODULEINFO moduleInfo;
			GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &moduleInfo, sizeof MODULEINFO);

			std::uintptr_t moduleStart = std::uintptr_t(moduleInfo.lpBaseOfDll);

			for (DWORD i = 0; i < moduleInfo.SizeOfImage; i++)
			{
				BYTE* data = reinterpret_cast<BYTE*>(moduleStart + i);

				bool found = true;

				for (size_t j = 0; j < patternBytes.size(); j++)
				{
					if (patternBytes[j] != NULL && data[j] != patternBytes[j])
					{
						found = false;

						break;
					}
				}

				if (found)
				{
					m_Handle = data;

					_Callback(*this);
				}
			}
		}

		template <typename T>
		std::enable_if_t<std::is_pointer_v<T>, T> As() const
		{
			return static_cast<T>(m_Handle);
		}

		template <typename T>
		std::enable_if_t<std::is_lvalue_reference_v<T>, T> As() const
		{
			return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(m_Handle);
		}

		template <typename T>
		std::enable_if_t<std::is_same_v<T, std::uintptr_t>, T> As() const
		{
			return reinterpret_cast<std::uintptr_t>(m_Handle);
		}

		template <typename T>
		Pattern Add(T _Offset) const
		{
			return Pattern(this->As<std::uintptr_t>() + _Offset);
		}

		template <typename T>
		Pattern Sub(T _Offset) const
		{
			return Pattern(this->As<std::uintptr_t>() - _Offset);
		}

		Pattern Rip() const
		{
			return this->Add(this->As<int&>()).Add(sizeof(int));
		}

		Pattern Deref(size_t _Count = 1) const
		{
			uintptr_t out = this->As<std::uintptr_t>();

			while (out && _Count > 0)
			{
				out = *reinterpret_cast<uintptr_t*>(out);

				if (!out)
				{
					return Pattern(m_Handle);
				}

				_Count--;
			}

			return Pattern(out);
		}

		void Nop(size_t _Size) const
		{
			return Memory::Nop(m_Handle, _Size);
		}

		void Put(BYTE _Value) const
		{
			// Function not yet implemented
		}

		template <typename T>
		void Write(T _Value) const
		{
			return Memory::Write(m_Handle, _Value);
		}

		void WriteBytes(std::vector<BYTE> _Bytes) const
		{
			return Memory::WriteBytes(m_Handle, _Bytes);
		}

		template<typename T>
		bool Hook(const char* _Name, T _NewFunction) const
		{
			return Hook::Create(_Name, m_Handle, _NewFunction);
		}

		template<typename T>
		bool Hook(const char* _Name, LPVOID _NewFunction, T** _Original) const
		{
			return Hook::Create(_Name, m_Handle, _NewFunction, _Original);
		}

	private:
		const char* m_Name;
		const char* m_Pattern;

		void* m_Handle;
};