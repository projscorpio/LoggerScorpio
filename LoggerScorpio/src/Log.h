#pragma once // je¿eli kompilator tego nie obs³uguje, to mo¿na spokojnie wywaliæ

#ifndef H_LOGGER
#define H_LOGGER

#include <spdlog/spdlog.h>

class Log
{
public:

	// must be called at the beggining of the programm
	static void Init();

	// easy access to both logger objects
	static inline std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
	static inline std::shared_ptr<spdlog::logger>& GetErrorLogget() { return s_StdErr; }

	// changing log levels for standard logget
	static void LogSetLevel(const std::string& level);
	static void StdErrSetLevel(const std::string& level);

private:
	static std::shared_ptr<spdlog::logger> s_Logger;
	static std::shared_ptr<spdlog::logger> s_StdErr;
};

// bunch of defines, that wont get compiled in final version
#ifndef NO_LOG

#define LOG_TRACE(...)    Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)     Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)     Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    Log::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) Log::GetLogger()->critical(__VA_ARGS__)

#define ERR_TRACE(...)    Log::GetErrorLogget()->trace(__VA_ARGS__)
#define ERR_INFO(...)     Log::GetErrorLogget()->info(__VA_ARGS__)
#define ERR_WARN(...)     Log::GetErrorLogget()->warn(__VA_ARGS__)
#define ERR_ERROR(...)    Log::GetErrorLogget()->error(__VA_ARGS__)
#define ERR_CRITICAL(...) Log::GetErrorLogget()->critical(__VA_ARGS__)

#else // NO_LOG

#define TRACE(...)
#define INFO(...)
#define WARN(...)
#define ERROR(...)
#define CRITICAL(...)

#define ERR_TRACE(...)  
#define ERR_INFO(...)   
#define ERR_WARN(...)     
#define ERR_ERROR(...)   
#define ERR_CRITICAL(...)

#endif // NO_LOG


#endif // H_LOGGER