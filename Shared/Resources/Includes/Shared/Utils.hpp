#pragma once



#include "Defines.hpp"
#include <filesystem>



namespace Utils
{
	static const std::string Replace(const std::string& _Str, const std::string& _OldValue, const std::string& _NewValue)
	{
		std::string str = _Str;

		while (str.find(_OldValue) != std::string::npos)
		{
			size_t index = str.find(_OldValue);

			str = str.replace(index, _OldValue.size(), _NewValue);
		}

		return str;
	}
}



inline const std::filesystem::path operator ""_ApplicationPath(const char* _Path, std::size_t)
{
	static char buffer[MAX_PATH];

	GetModuleFileNameA(HINST_THISCOMPONENT, buffer, MAX_PATH);

	std::filesystem::path modulePath(buffer);

	return modulePath.remove_filename() / _Path;
}