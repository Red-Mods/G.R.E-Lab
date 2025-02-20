#include <pch.h>



const std::unordered_map<LogType, const char*> Log::s_Types =
{
	{ Log_Init, "[Init]" },

	{ Log_Info, "[Info]" },
	{ Log_Warning, "[Warning]" },
	{ Log_Error, "[Error]" },

	{ Log_Dev_Info, "[Dev] [Info]" },
	{ Log_Dev_Warning, "[Dev] [Warning]" },
	{ Log_Dev_Error, "[Dev] [Error]" },

	{ Log_ConsoleOnly, "[Console]" }
};



const std::unordered_map<LogType, LogColor> Log::s_Colors =
{
	{ Log_Init, { 0.5f, 0.5f, 0.5f, 0.8f } },

	{ Log_Info, { 0.0f, 1.0f, 0.5f, 0.8f } },
	{ Log_Warning, { 1.0f, 0.5f, 0.0f, 0.8f } },
	{ Log_Error, { 1.0f, 0.0f, 0.0f, 0.8f } },

	{ Log_Dev_Info, { 0.2f, 0.2f, 0.2f, 0.8f } },
	{ Log_Dev_Warning, { 0.75f, 0.5f, 0.0f, 0.8f } },
	{ Log_Dev_Error, { 0.75f, 0.0f, 0.0f, 0.8f } },

	{ Log_ConsoleOnly, { 0.0f, 1.0f, 0.5f, 0.8f } }
};



void Log::Print(LogType _Type, const char* _Format, ...)
{
	std::lock_guard<std::mutex> lock(s_Mutex);

	FILE* file;
	if (fopen_s(&file, APPLICATION_NAME ".Log", _Type == Log_Init ? "w" : "a") == 0)
	{
		tm time = Utils::GetSystemTime();

		char buffer[0x100];

		va_list vaBuffer;

		va_start(vaBuffer, _Format);
		_vsnprintf_s(buffer, sizeof(buffer), _Format, vaBuffer);
		va_end(vaBuffer);

		char tempBuffer[0x200];
		sprintf_s(tempBuffer, "[%02d:%02d:%02d] %s %s\n", time.tm_hour, time.tm_min, time.tm_sec, s_Types.at(_Type), buffer);

		fprintf_s(file, "%s", tempBuffer);

		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

		if (console != INVALID_HANDLE_VALUE)
		{
			DWORD unused;
			WriteConsoleA(console, tempBuffer, (DWORD)strlen(tempBuffer), &unused, NULL);
		}

		fclose(file);

		AddToCache(_Type, "[%02d:%02d:%02d] %s", time.tm_hour, time.tm_min, time.tm_sec, buffer);
	}
}



void Log::RegisterOnLogReceived(std::function<void()> _OnLogReceived)
{
	s_OnLogReceived = _OnLogReceived;
}



const LogLine* Log::GetCachedLogs()
{
	return s_Content;
}



void Log::AddToCache(LogType _Type, const char* _Format, ...)
{
	static int count = 0;

	LogLine line;
	line.Color = s_Colors.at(_Type);
	line.Tag = s_Types.at(_Type);

	std::erase(line.Tag, '[');
	std::erase(line.Tag, ']');

	static char buffer[0x200];

	va_list va_buffer;

	va_start(va_buffer, _Format);
	_vsnprintf_s(buffer, sizeof(buffer), _Format, va_buffer);
	va_end(va_buffer);

	line.Text = buffer;

	if (count >= MAX_CACHED_LOGS)
	{
		LogLine dummy;
		dummy.Tag = "";

		for (size_t i = 0; i < MAX_CACHED_LOGS; i++)
		{
			s_Content[i] = dummy;
		}

		count = 0;
	}

	s_Content[count] = line;

	if (s_OnLogReceived)
		s_OnLogReceived();

	count++;
}