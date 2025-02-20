#pragma once



#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <shellapi.h>

#include "../../Headers/Ini.hpp"



enum Plateform
{
	Retail,
	Steam,
	Epic
};



struct GameTitle
{
	std::string Name;
	std::string Executable;
	std::string EpicId;
	std::string SteamId;

	GameTitle(const std::string& _Name, const std::string& _Executable) : Name(_Name), Executable(_Executable) {}
	GameTitle(const std::string& _Name, const std::string& _Executable, const std::string& _EpicId, const std::string& _SteamId) : Name(_Name), Executable(_Executable), EpicId(_EpicId), SteamId(_SteamId) {}
};



class Launcher
{
	public:
		Launcher();

		void Start();
		bool Update();
		void Stop();

	private:
		std::unordered_map<std::string, GameTitle> m_SupportedGames;
		
		Plateform GetPlateform(const std::filesystem::path& _GameDirectory);
		bool IsModdedGame(const std::filesystem::path& _GameDirectory);
		bool LoadCore(HANDLE _Process, const std::filesystem::path& _DllFile);

		bool Launch(const std::string& _LaunchCode);
};