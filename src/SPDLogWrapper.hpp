#ifndef LOG_HPP_
#define LOG_HPP_

#include <spdlog/spdlog.h>

namespace ScorpioLog {

class SPDLogWrapper final {
public:
	static constexpr const char* DEFAULT_FORMAT = "%^[%T] [%t] %l: %v%$";
	static constexpr const char* DEFAULT_FILE_PATH = "logs/logfile.log";
	static constexpr size_t DEFAULT_MAX_FILE_SIZE = 1048576U * 5U; // 5MB
	static constexpr size_t DEFAULT_MAX_FILES = 10U;

	SPDLogWrapper() = delete;
	SPDLogWrapper(const SPDLogWrapper& other) = delete;

	// must be called at the beggining of the programm
	static void InitConsole();
	static void InitFile(const std::string& directionary = DEFAULT_FILE_PATH, size_t maxSize = DEFAULT_MAX_FILE_SIZE, size_t maxFiles = DEFAULT_MAX_FILE_SIZE);

	template <typename... Params>
	static void trace(Params &&... params)
	{
		if (s_ConsoleLogger)
			s_ConsoleLogger->trace(params...);
		if (s_FileLogger)
			s_FileLogger->trace(params...);
	}


	template <typename... Params>
	static void info(Params &&... params)
	{
		if (s_ConsoleLogger)
			s_ConsoleLogger->info(params...);
		if (s_FileLogger)
			s_FileLogger->info(params...);
	}


	template <typename... Params>
	static void warn(Params &&... params)
	{
		if (s_ConsoleLogger)
			s_ConsoleLogger->warn(params...);
		if (s_FileLogger)
			s_FileLogger->warn(params...);
	}


	template <typename... Params>
	static void error(Params &&... params)
	{
		if (s_ConsoleLogger)
			s_ConsoleLogger->error(params...);
		if (s_FileLogger)
			s_FileLogger->error(params...);
	}


	template <typename... Params>
	static void critical(Params &&... params)
	{
		if (s_ConsoleLogger)
			s_ConsoleLogger->critical(params...);
		if (s_FileLogger)
			s_FileLogger->critical(params...);
	}


	static void SetLevelConsole(const std::string& level);
	static void SetLevelFile(const std::string& level);

	static void SetPatternConsole(const std::string& pattern = DEFAULT_FORMAT);
	static void SetPatternFile(const std::string& pattern = DEFAULT_FORMAT);

private:
	static std::shared_ptr<spdlog::logger> s_ConsoleLogger;
	static std::shared_ptr<spdlog::logger> s_FileLogger;
};

} // ScorpioLog 

#ifdef SCORPIO_LOG

#define LOGGER_INIT_CONSOLE  ScorpioLog::SPDLogWrapper::InitConsole()
#define LOGGER_INIT_FILE     ScorpioLog::SPDLogWrapper::InitFile()
				    
#define LOGGER_TRACE(...)    ScorpioLog::SPDLogWrapper::trace(__VA_ARGS__)
#define LOGGER_INFO(...)     ScorpioLog::SPDLogWrapper::info(__VA_ARGS__)
#define LOGGER_WARN(...)     ScorpioLog::SPDLogWrapper::warn(__VA_ARGS__)
#define LOGGER_ERROR(...)    ScorpioLog::SPDLogWrapper::error(__VA_ARGS__)
#define LOGGER_CRITICAL(...) ScorpioLog::SPDLogWrapper::critical(__VA_ARGS__)

#else // SCORPIO_LOG

#define LOGGER_INIT_CONSOLE
#define LOGGER_INIT_FILE

#define LOGGER_TRACE(...)    
#define LOGGER_INFO(...)     
#define LOGGER_WARN(...)     
#define LOGGER_ERROR(...)    
#define LOGGER_CRITICAL(...) 

#endif // SCORPIO_LOG

#endif // LOG_HPP_