#pragma once



struct FontData
{
	LPVOID Data;
	DWORD Length;
};



namespace Utils
{
	ImVec2 GetGameWindowResolution();

	FontData LoadFont(HMODULE _Module, const WCHAR* _Name, const WCHAR* _Format);

	const std::vector<std::string> GetAllFilesFromDirectory(const std::string& _Path);

	tm GetSystemTime();
	
	BYTE StringToByte(const std::string& _Str);

	const std::string GetFilename(const std::string& _Filename);
	const std::string GetFilenameWithoutExtension(const std::string& _Filename);
	const std::string GetModuleFullName(HMODULE _Module);
	const std::string GetModuleName(HMODULE _Module);
	const std::string GetModuleNameWithoutExtension(HMODULE _Module);

	const std::string ToUpper(const std::string& _Str);
	const std::string ToLower(const std::string& _Str);
}