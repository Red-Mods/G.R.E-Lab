#pragma once



#include "Defines.hpp"
#include <filesystem>



inline const std::filesystem::path operator ""_ApplicationPath(const char* _Path, std::size_t)
{
	static char buffer[MAX_PATH];

	GetModuleFileNameA(HINST_THISCOMPONENT, buffer, MAX_PATH);

	std::filesystem::path modulePath(buffer);

	return modulePath.remove_filename() / _Path;
}