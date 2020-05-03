#pragma once // je¿eli kompilator tego nie obs³uguje, to mo¿na spokojnie wywaliæ

#ifndef H_LOGGER
#define H_LOGGER

#include <spdlog/spdlog.h>
// DEFINES
#define DEF_FORMAT "%^[%T] [%t] %l: %v%$"
#define DEF_PATH "logs/logfile"
#define DEF_MAX_SIZE 1048576 * 5 // 5MB
#define DEF_MAX_FILES 10

class Log
{
public:
	// must be called at the beggining of the programm
	static void InitConsole();
	static void InitFile(const std::string& directionary = DEF_PATH, size_t maxSize = DEF_MAX_SIZE, size_t maxFiles = DEF_MAX_FILES);

	// easy access to both logger static objects
	static inline std::shared_ptr<spdlog::logger>& GetConsoleLogger() { return s_ConsoleLogger; }
	static inline std::shared_ptr<spdlog::logger>& GetFileLogger() { return s_FileLogger; }


	// changing log levels for standard logget
	static void SetConsoleLevel(const std::string& level);
	static void SetFileLevel(const std::string& level);

private:
	static void SetPattern();

	static std::shared_ptr<spdlog::logger> s_ConsoleLogger;
	static std::shared_ptr<spdlog::logger> s_FileLogger;
};


// bunch of defines, that wont get compiled if needed
#ifndef NO_LOG

#define LOG_TRACE(...)    Log::GetConsoleLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)     Log::GetConsoleLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)     Log::GetConsoleLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    Log::GetConsoleLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) Log::GetConsoleLogger()->critical(__VA_ARGS__)

#define FILE_TRACE(...)    Log::GetFileLogger()->trace(__VA_ARGS__)
#define FILE_INFO(...)     Log::GetFileLogger()->info(__VA_ARGS__)
#define FILE_WARN(...)     Log::GetFileLogger()->warn(__VA_ARGS__)
#define FILE_ERROR(...)    Log::GetFileLogger()->error(__VA_ARGS__)
#define FILE_CRITICAL(...) Log::GetFileLogger()->critical(__VA_ARGS__)

#else // NO_LOG

#define TRACE(...)
#define INFO(...)
#define WARN(...)
#define ERROR(...)
#define CRITICAL(...)

#define FILE_TRACE(...)    
#define FILE_INFO(...)     
#define FILE_WARN(...)     
#define FILE_ERROR(...)    
#define FILE_CRITICAL(...)

#endif // NO_LOG


#endif // H_LOGGER