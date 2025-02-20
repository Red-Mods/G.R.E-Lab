#pragma once



struct FontData
{
	LPVOID Data;
	DWORD Length;
};



namespace Utils
{
	static ImVec2 GetGameWindowResolution()
	{
		static HWND gameWindow = FindWindowA(GAME_WINDOW_CLASS_NAME, NULL);

		RECT rect;
		GetClientRect(gameWindow, &rect);

		return ImVec2((float)(rect.right - rect.left), (float)(rect.bottom - rect.top));
	}

	static FontData LoadFont(HMODULE _Module, const WCHAR* _Name, const WCHAR* _Format)
	{
		HRSRC resource = FindResourceW(_Module, _Name, _Format);

		if (resource)
		{
			HGLOBAL resourceData = LoadResource(_Module, resource);

			if (resourceData)
			{
				FontData fontData{};
				fontData.Data = LockResource(resourceData);
				fontData.Length = SizeofResource(_Module, resource);

				return fontData;
			}
		}

		return {};
	}

	static const std::vector<std::string> GetAllFilesFromDirectory(const std::string& _Path)
	{
		std::vector<std::string> names;

		WIN32_FIND_DATAA fd;

		HANDLE hFind = FindFirstFileA(_Path.c_str(), &fd);

		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					names.push_back(fd.cFileName);
				}
			}
			while (FindNextFileA(hFind, &fd));

			FindClose(hFind);
		}

		return names;
	}

	static tm GetSystemTime()
	{
		tm time_struct;
		time_t current_time = time(NULL);

		localtime_s(&time_struct, &current_time);

		return time_struct;
	}

	static BYTE StringToByte(const std::string& _Str)
	{
		std::istringstream iss(_Str);
		uint32_t value = 0;

		iss >> std::hex >> value;

		return static_cast<BYTE>(value);
	}

	static const std::string GetFilename(const std::string& _Filename)
	{
		size_t lastIndex = _Filename.find_last_of("\\") + 1;

		return _Filename.substr(lastIndex, _Filename.length() - lastIndex);
	}

	static const std::string GetFilenameWithoutExtension(const std::string& _Filename)
	{
		size_t lastIndex = _Filename.find_last_of(".");

		if (lastIndex == -1)
		{
			return _Filename;
		}

		return _Filename.substr(0, lastIndex);
	}

	static const std::string GetModuleFullName(HMODULE _Module)
	{
		char buffer[MAX_PATH];
		GetModuleFileNameA(_Module, buffer, MAX_PATH);

		return buffer;
	}

	static const std::string GetModuleName(HMODULE _Module)
	{
		return GetFilename(GetModuleFullName(_Module));
	}

	static const std::string GetModuleNameWithoutExtension(HMODULE _Module)
	{
		const std::string fileNameWithExtension = GetModuleName(_Module);

		return GetFilenameWithoutExtension(fileNameWithExtension);
	}

	static const std::string ToUpper(const std::string& _Str)
	{
		std::string str = _Str;

		std::transform(str.begin(), str.end(), str.begin(), toupper);

		return str;
	}

	static const std::string ToLower(const std::string& _Str)
	{
		std::string str = _Str;

		std::transform(str.begin(), str.end(), str.begin(), tolower);

		return str;
	}
}