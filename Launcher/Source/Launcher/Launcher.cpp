#include "Launcher.h"



Launcher::Launcher()
{
	m_SupportedGames =
	{
		{ "rdr",
			GameTitle
			(
				"Red Dead Redemption",
				"RDR.exe",
				"2668510",
				"2fc7ff863b5445cbb949f017fc37f023%3A65d5b9b0f0564033bf59db9e8b740edb"
			)
		}
	};
}



void Launcher::Start()
{
	std::cout << "Welcome to G.R.E Lab !\n";
	std::cout << "Please choose the desired title you want to launch:" << std::endl;

	for (const auto& [launchCode, gameTitle] : m_SupportedGames)
	{
		std::cout << "[" << launchCode << "] " << gameTitle.Name << std::endl;
	}
}



bool Launcher::Update()
{
	std::string launchCode;
	std::cin >> launchCode;

	if (launchCode == "exit")
		return false;

	return !Launch(launchCode);
}



void Launcher::Stop()
{

}



Plateform Launcher::GetPlateform(const std::filesystem::path& _GameDirectory)
{
	/*
	std::filesystem::path steamModule = _GameDirectory / "steam_api64.dll";

	if (std::filesystem::exists(steamModule))
	{
		return Steam;
	}
	*/

	std::filesystem::path epicModule = _GameDirectory / "EOSSDK-Win64-Shipping.dll";

	if (std::filesystem::exists(epicModule))
	{
		return Epic;
	}

	return Retail;
}



bool Launcher::IsModdedGame(const std::filesystem::path& _GameDirectory)
{
	std::filesystem::path winmmInjector = _GameDirectory / "winmm.dll";

	if (std::filesystem::exists(winmmInjector))
		return true;

	std::filesystem::path dinput8Injector = _GameDirectory / "dinput8.dll";

	if (std::filesystem::exists(dinput8Injector))
		return true;

	std::filesystem::path dsoundInjector = _GameDirectory / "dsound.dll";

	if (std::filesystem::exists(dsoundInjector))
		return true;

	return false;
}



bool Launcher::LoadCore(HANDLE _Process, const std::filesystem::path& _DllFile)
{
	const std::filesystem::path dataPath = "Data"_ApplicationPath;

	// We're adding our 'Data' foldeer to the list of searchable directory into the game process.
	Utils::AddDirectory(_Process, dataPath.string().c_str());

	const std::filesystem::path coreModule = dataPath / _DllFile;

	// Then we can now inject our core dll (others dlls inside 'Data' folder will be implicitely loaded)
	if (Utils::InjectDLL(_Process, coreModule.wstring().c_str()))
	{
		std::cout << "Successfully loaded " << APPLICATION_NAME << " !" << std::endl;

		return true;
	}

	std::cerr << "Failed to load " << APPLICATION_NAME << " !" << std::endl;

	return false;
}



bool Launcher::Launch(const std::string& _LaunchCode)
{
	if (!m_SupportedGames.contains(_LaunchCode))
	{
		std::cerr << _LaunchCode << " is not a valid launch code ! (Type 'exit' if you want to quit)" << std::endl;

		return false;
	}

	GameTitle gameTitle = m_SupportedGames.at(_LaunchCode);

	Ini config("Config.ini"_ApplicationPath);

	std::filesystem::path tmpGamePath;

	if (config.Exist())
	{
		std::cout << "Reading game path..." << std::endl;

		tmpGamePath = config.Read<std::string>(gameTitle.Name, "GamePath");
	}
	else
	{
		std::cout << "Choose your game path..." << std::endl;

		tmpGamePath = Utils::OpenFileDialog(GetConsoleWindow(), gameTitle.Name, gameTitle.Executable);

		config.Write(gameTitle.Name, "GamePath", tmpGamePath.string());

		std::cout << "Successfully saved game path !" << std::endl;
	}

	std::cout << "Launching game..." << std::endl;

	const std::filesystem::path gamePath = tmpGamePath;
	const std::filesystem::path gameDirectory = tmpGamePath.remove_filename();
	std::filesystem::path gameExecutable = gameTitle.Executable;
	const std::filesystem::path dllToLoad = gameExecutable.replace_extension("dll");

	if (IsModdedGame(gameDirectory))
	{
		std::cout << "Modded files has been found in your game directory, this is heavily recommended to disable/uninstall when using this application !" << std::endl;

		Sleep(1000);
	}

	DWORD gameProcessId = Utils::GetProcessIdByName(gameTitle.Executable);

	if (gameProcessId == NULL)
	{
		Plateform plateform = GetPlateform(gameDirectory);

		if (plateform == Epic)
		{
			const std::string launchString = "com.epicgames.launcher://apps/" + gameTitle.EpicId + "%3ALoon?action=launch&silent=true";

			ShellExecuteA(NULL, NULL, launchString.c_str(), NULL, NULL, SW_HIDE);
		}
		else if (plateform == Steam)
		{
			const std::string launchString = "steam://rungameid/" + gameTitle.SteamId;

			ShellExecuteA(NULL, NULL, launchString.c_str(), NULL, NULL, SW_HIDE);
		}
		else
		{
			STARTUPINFO si = { sizeof(si) };
			PROCESS_INFORMATION pi = {};

			bool success = CreateProcess
			(
				gamePath.wstring().c_str(),
				NULL,
				NULL,
				NULL,
				FALSE,
				CREATE_SUSPENDED,
				NULL,
				gameDirectory.wstring().c_str(),
				&si,
				&pi
			);

			if (success)
			{
				if (LoadCore(pi.hProcess, dllToLoad))
				{
					ResumeThread(pi.hThread);
				}
				else
				{
					TerminateProcess(pi.hProcess, EXIT_SUCCESS);
				}

				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
			}

			Sleep(500);

			return true;
		}

		std::cout << "Waiting for " << gameTitle.Name << "..." << std::endl;
	}

	// We're waiting for the game process to show up...
	do
	{
		gameProcessId = Utils::GetProcessIdByName(gameTitle.Executable);

		Sleep(1);
	}
	while (!gameProcessId);

	// Then we open a process handle from the game process id.
	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, gameProcessId);

	LoadCore(process, dllToLoad);

	Sleep(500);

	return true;
}