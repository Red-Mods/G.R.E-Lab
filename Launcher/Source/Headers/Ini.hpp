#pragma once



#include "Utils.hpp"



class Ini
{
	public:
		Ini() = default;
		Ini(const std::filesystem::path& _FilePath)
		{
			m_FilePath = _FilePath;
		}

		template<typename T>
		void Write(const std::string& _Section, const std::string& _Key, T _Value)
		{
			if constexpr (std::is_same_v<T, bool>)
			{
				WriteBool(_Section, _Key, _Value);
			}
			else if constexpr (std::is_same_v<T, int>)
			{
				WriteInt(_Section, _Key, _Value);
			}
			else if constexpr (std::is_same_v<T, float>)
			{
				WriteFloat(_Section, _Key, _Value);
			}
			else if constexpr (std::is_same_v<T, const char*> || std::is_same_v<T, std::string> || std::is_same_v<T, const std::string>)
			{
				WriteString(_Section, _Key, _Value);
			}
		}

		template<typename T>
		T Read(const std::string& _Section, const std::string& _Key)
		{
			if constexpr (std::is_same_v<T, bool>)
			{
				return ReadBool(_Section, _Key);
			}
			else if constexpr (std::is_same_v<T, int>)
			{
				return ReadInt(_Section, _Key);
			}
			else if constexpr (std::is_same_v<T, float>)
			{
				return ReadFloat(_Section, _Key);
			}
			else if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, const std::string>)
			{
				return ReadString(_Section, _Key);
			}
		}

		bool Exist() const
		{
			return std::filesystem::exists(m_FilePath);
		}

	private:
		std::filesystem::path m_FilePath;

		void WriteBool(const std::string& _Section, const std::string& _Key, bool _Value)
		{
			WritePrivateProfileStringA(_Section.c_str(), _Key.c_str(), _Value ? "true" : "false", m_FilePath.string().c_str());
		}

		bool ReadBool(const std::string& _Section, const std::string& _Key)
		{
			static char buffer[6];
			GetPrivateProfileStringA(_Section.c_str(), _Key.c_str(), "false", buffer, sizeof(buffer), m_FilePath.string().c_str());

			return std::string(buffer) == "true" ? true : false;
		}

		void WriteInt(const std::string& _Section, const std::string& _Key, int _Value)
		{
			WritePrivateProfileStringA(_Section.c_str(), _Key.c_str(), std::to_string(_Value).c_str(), m_FilePath.string().c_str());
		}

		int ReadInt(const std::string& _Section, const std::string& _Key)
		{
			return GetPrivateProfileIntA(_Section.c_str(), _Key.c_str(), 0, m_FilePath.string().c_str());
		}

		void WriteFloat(const std::string& _Section, const std::string& _Key, float _Value)
		{
			WritePrivateProfileStringA(_Section.c_str(), _Key.c_str(), std::to_string(_Value).c_str(), m_FilePath.string().c_str());
		}

		float ReadFloat(const std::string& _Section, const std::string& _Key)
		{
			static char buffer[50];
			GetPrivateProfileStringA(_Section.c_str(), _Key.c_str(), "0.0", buffer, sizeof(buffer), m_FilePath.string().c_str());

			return strtof(buffer, NULL);
		}

		void WriteString(const std::string& _Section, const std::string& _Key, const std::string& _Value)
		{
			WritePrivateProfileStringA(_Section.c_str(), _Key.c_str(), _Value.c_str(), m_FilePath.string().c_str());
		}

		const std::string ReadString(const std::string& _Section, const std::string& _Key)
		{
			static char buffer[255];
			GetPrivateProfileStringA(_Section.c_str(), _Key.c_str(), "", buffer, sizeof(buffer), m_FilePath.string().c_str());

			return buffer;
		}
};