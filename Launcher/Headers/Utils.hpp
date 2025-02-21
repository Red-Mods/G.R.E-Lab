#pragma once



#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <filesystem>
#include <ShObjIdl_core.h>
#include <TlHelp32.h>



namespace Utils
{
	template<class I>
	static void SafeRelease(I** _InterfaceToRelease)
	{
		if (*_InterfaceToRelease != nullptr)
		{
			(*_InterfaceToRelease)->Release();
			(*_InterfaceToRelease) = nullptr;
		}
	}

	static const std::string WstringToString(const std::wstring& _Wstr, const std::locale& _Locale = std::locale{})
	{
		std::vector<char> buf(_Wstr.size());
		std::use_facet<std::ctype<wchar_t>>(_Locale).narrow(_Wstr.data(), _Wstr.data() + _Wstr.size(), '?', buf.data());

		return std::string(buf.data(), buf.size());
	}

	static const std::wstring StringToWstring(const std::string& _Str, const std::locale& _Locale = std::locale{})
	{
		std::vector<wchar_t> buf(_Str.size());
		std::use_facet<std::ctype<wchar_t>>(_Locale).widen(_Str.data(), _Str.data() + _Str.size(), buf.data());

		return std::wstring(buf.data(), buf.size());
	}

	static const std::filesystem::path OpenFileDialog(HWND _WindowOwner, const std::string& _FilterAppName, const std::string& _FilterTypeName)
	{
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

		if (SUCCEEDED(hr))
		{
			IFileOpenDialog* fileOpenDialog;
			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&fileOpenDialog));

			if (!SUCCEEDED(hr))
			{
				SafeRelease(&fileOpenDialog);

				CoUninitialize();

				return "NULL";
			}

			const std::wstring filterAppName = StringToWstring(_FilterAppName);
			const std::wstring filterTypeName = StringToWstring(_FilterTypeName);

			COMDLG_FILTERSPEC filters[1] = { { filterAppName.c_str(), filterTypeName.c_str() } };
			hr = fileOpenDialog->SetFileTypes(1, filters);

			if (!SUCCEEDED(hr))
			{
				SafeRelease(&fileOpenDialog);

				CoUninitialize();

				return "NULL";
			}

			hr = fileOpenDialog->Show(_WindowOwner);

			if (!SUCCEEDED(hr))
			{
				SafeRelease(&fileOpenDialog);

				CoUninitialize();

				return "NULL";
			}

			IShellItem* shellItem;
			hr = fileOpenDialog->GetResult(&shellItem);

			if (!SUCCEEDED(hr))
			{
				SafeRelease(&fileOpenDialog);
				SafeRelease(&shellItem);

				CoUninitialize();

				return "NULL";
			}

			WCHAR* filePath;
			hr = shellItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath);

			SafeRelease(&fileOpenDialog);
			SafeRelease(&shellItem);

			if (SUCCEEDED(hr))
			{
				CoUninitialize();

				return filePath;
			}
		}

		CoUninitialize();

		return "NULL";
	}

	static void AddDirectory(HANDLE _Handle, const char* _ModulePath)
	{
		if (_Handle == INVALID_HANDLE_VALUE)
			return;

		HMODULE kernel32 = GetModuleHandle(L"kernel32.dll");

		if (!kernel32)
			return;

		LPVOID setDllDirectory = (LPVOID)GetProcAddress(kernel32, "SetDllDirectoryA");

		if (!setDllDirectory)
			return;

		LPVOID alloc = VirtualAllocEx(_Handle, NULL, strlen(_ModulePath), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		if (!alloc)
			return;

		WriteProcessMemory(_Handle, alloc, _ModulePath, strlen(_ModulePath), NULL);

		HANDLE thread = CreateRemoteThread(_Handle, NULL, NULL, (LPTHREAD_START_ROUTINE)setDllDirectory, alloc, NULL, NULL);

		if (!thread)
			return;

		WaitForSingleObject(thread, INFINITE);

		VirtualFreeEx(_Handle, alloc, strlen(_ModulePath), MEM_FREE);

		CloseHandle(thread);
	}

	static bool InjectDLL(HANDLE _Process, const WCHAR* _DllPath)
	{
		static WCHAR fullPath[MAX_PATH];

		// Get full path of the dll.
		DWORD pathLength = GetFullPathName(_DllPath, MAX_PATH, fullPath, NULL);

		if (pathLength == NULL)
		{
			printf("GetFullPathName (%u)\n", GetLastError());

			return false;
		}

		// Alloc memory for the dll.
		LPVOID virtualAlloc = VirtualAllocEx(_Process, NULL, pathLength * sizeof(WCHAR), MEM_COMMIT, PAGE_EXECUTE_READWRITE);

		if (!virtualAlloc)
		{
			printf("VirtualAlloc (%u)\n", GetLastError());

			return false;
		}

		// Check if we are able to write in memory.
		BOOL ableToWrite = WriteProcessMemory(_Process, virtualAlloc, fullPath, pathLength * sizeof(WCHAR), NULL);

		if (!ableToWrite)
		{
			printf("WriteProcessMemory (%u)\n", GetLastError());

			return false;
		}

		// Check if we are able to load the dll.
		HMODULE kernel32 = LoadLibrary(L"kernel32");

		if (!kernel32)
		{
			printf("LoadLibrary (%u)\n", GetLastError());

			return false;
		}

		// Check if we can get process address.
		LPTHREAD_START_ROUTINE loadLibrary = reinterpret_cast<LPTHREAD_START_ROUTINE>(GetProcAddress(kernel32, "LoadLibraryW"));

		if (!loadLibrary)
		{
			printf("GetProcAddress (%u)\n", GetLastError());

			return false;
		}

		// Create a remote thread to load the dll.
		DWORD threadId = 0;
		HANDLE threadHandle = CreateRemoteThread(_Process, NULL, NULL, loadLibrary, virtualAlloc, NULL, &threadId);

		if (!threadHandle)
		{
			printf("CreateRemoteThread (%u)\n", GetLastError());

			return false;
		}

		return true;
	}

	static DWORD GetProcessIdByName(const std::string& _ProcessName)
	{
		// Get list of all opened processes.
		HANDLE processSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (processSnapshot == INVALID_HANDLE_VALUE)
		{
			return NULL;
		}

		// Set the size of the structure before using it.
		PROCESSENTRY32 pe32{};
		pe32.dwSize = sizeof(PROCESSENTRY32);

		// Retrieve information about the first process and exit if unsuccessful.
		if (!Process32First(processSnapshot, &pe32))
		{
			CloseHandle(processSnapshot);

			return NULL;
		}

		const std::wstring processName = StringToWstring(_ProcessName);

		// Check for processes in the list.
		do
		{
			if (wcscmp(pe32.szExeFile, processName.c_str()) == 0)
			{
				CloseHandle(processSnapshot);

				return pe32.th32ProcessID;
			}
		}
		while (Process32Next(processSnapshot, &pe32));

		CloseHandle(processSnapshot);

		return NULL;
	}
}