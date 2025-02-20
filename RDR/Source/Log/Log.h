#pragma once



enum LogType
{
	Log_Init,

	Log_Info,
	Log_Warning,
	Log_Error,

	Log_Dev_Info,
	Log_Dev_Warning,
	Log_Dev_Error,

	Log_ConsoleOnly
};



struct LogColor
{
	float R;
	float G;
	float B;
	float A;
};



struct LogLine
{
	LogColor Color;
	std::string Tag;
	std::string Text;
};



class Log
{
	public:
		static void Print(LogType _Type, const char* _Format, ...);

		static void AddToCache(LogType _Type, const char* _Format, ...);

		static void RegisterOnLogReceived(std::function<void()> _OnLogReceived);
		
		static const LogLine* GetCachedLogs();

	private:
		static inline std::mutex s_Mutex;
		static const std::unordered_map<LogType, const char*> s_Types;
		static const std::unordered_map<LogType, LogColor> s_Colors;

		static inline LogLine s_Content[MAX_CACHED_LOGS];
		static inline std::function<void()> s_OnLogReceived;
};



#define LOG_INIT(fmt, ...) Log::Print(Log_Init, fmt __VA_OPT__(,) __VA_ARGS__)
#define LOG_INFO(fmt, ...) Log::Print(Log_Info, fmt __VA_OPT__(,) __VA_ARGS__)
#define LOG_WARNING(fmt, ...) Log::Print(Log_Warning, fmt __VA_OPT__(,) __VA_ARGS__)
#define LOG_ERROR(fmt, ...) Log::Print(Log_Error, fmt __VA_OPT__(,) __VA_ARGS__)



#ifdef IS_DEV_BUILD
#define LOG_DEV_INFO(fmt, ...) Log::Print(Log_Dev_Info, fmt __VA_OPT__(,) __VA_ARGS__)
#define LOG_DEV_WARNING(fmt, ...) Log::Print(Log_Dev_Warning, fmt __VA_OPT__(,) __VA_ARGS__)
#define LOG_DEV_ERROR(fmt, ...) Log::Print(Log_Dev_Error, fmt __VA_OPT__(,) __VA_ARGS__)
#else
#define LOG_DEV_INFO(fmt, ...)
#define LOG_DEV_WARNING(fmt, ...)
#define LOG_DEV_ERROR(fmt, ...)
#endif