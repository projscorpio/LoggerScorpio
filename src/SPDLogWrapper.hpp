#ifndef LOG_HPP_
#define LOG_HPP_

#include <errno.h>
#include <string.h>

#ifdef _WIN32
#define strerror_r(buf, bufsz, errnum) strerror_s(buf, bufsz, errnum)
#endif // _WIN32

#include <spdlog/spdlog.h>

namespace ScorpioLog {

class SPDLogWrapper final {
public:
	SPDLogWrapper() = delete;
	SPDLogWrapper(const SPDLogWrapper& other) = delete;

	// must be called at the beggining of the programm
	static void initConsole();
	static void initFile();

	template <typename String, typename... Params>
	static void trace(const String &string, const Params &... params)
	{
		if (consoleLogger_)
			consoleLogger_->trace(string, params...);
		if (fileLogger_)
			fileLogger_->trace(string, params...);
	}

	template <typename String, typename... Params>
	static void info(const String &string, const Params &... params)
	{
		if (consoleLogger_)
			consoleLogger_->info(string,params...);
		if (fileLogger_)
			fileLogger_->info(string, params...);
	}

	template <typename String, typename... Params>
	static void warn(const String &string, const Params &... params)
	{
		if (consoleLogger_)
			consoleLogger_->warn(string, params...);
		if (fileLogger_)
			fileLogger_->warn(string, params...);
	}

	template <typename String, typename... Params>
	static void error(const String &string, const Params &... params)
	{
		if (consoleLogger_)
			consoleLogger_->error(string, params...);
		if (fileLogger_)
			fileLogger_->error(string, params...);
	}

	template <typename String, typename... Params>
	static void perror(const String &string, const Params &... params)
	{
		char message[PERR_BUF_LEN];
		const char *error_msg = strerror_r(errno, message, PERR_BUF_LEN);
		error(string, error_msg, params...);
	}

	template <typename String, typename... Params>
	static void critical(const String &string, const Params &... params)
	{
		if (consoleLogger_)
			consoleLogger_->critical(string, params...);
		if (fileLogger_)
			fileLogger_->critical(string, params...);
	}

	static void setLevelConsole(const std::string& level);
	static void setLevelConsole(spdlog::level::level_enum level);
	static void setLevelFile(const std::string& level);
	static void setLevelFile(spdlog::level::level_enum level);

	static void setPatternConsole(const std::string& pattern = DEFAULT_FORMAT);
	static void setPatternFile(const std::string& pattern = DEFAULT_FORMAT);

private:

	static void backupOldFiles();
	static bool createFolder(const char* dir);

	static constexpr const char* DEFAULT_FORMAT = "%^[%T] [%t] %l: %v%$";
	static constexpr const char* LOG_FOLDER = "logs/";
	static constexpr const char* BACKUP_FOLER = "logs_backup/";
	static constexpr const char* LOG_SUFIX = ".log";
	static constexpr size_t DEFAULT_MAX_FILE_SIZE = 1048576U * 5U; // 5MB
	static constexpr size_t DEFAULT_MAX_FILES = 20U;

	static constexpr size_t PERR_BUF_LEN = 256;
	static std::shared_ptr<spdlog::logger> consoleLogger_;
	static std::shared_ptr<spdlog::logger> fileLogger_;
};

} // ScorpioLog 

#ifdef SCORPIO_LOG

#define LOGGER_INIT_CONSOLE  ScorpioLog::SPDLogWrapper::initConsole()
#define LOGGER_INIT_FILE     ScorpioLog::SPDLogWrapper::initFile()
				    
#define LOGGER_TRACE(...)    ScorpioLog::SPDLogWrapper::trace(__VA_ARGS__)
#define LOGGER_INFO(...)     ScorpioLog::SPDLogWrapper::info(__VA_ARGS__)
#define LOGGER_WARN(...)     ScorpioLog::SPDLogWrapper::warn(__VA_ARGS__)
#define LOGGER_ERROR(...)    ScorpioLog::SPDLogWrapper::error(__VA_ARGS__)
#define LOGGER_PERROR(...)    ScorpioLog::SPDLogWrapper::perror(__VA_ARGS__)
#define LOGGER_CRITICAL(...) ScorpioLog::SPDLogWrapper::critical(__VA_ARGS__)


#else // SCORPIO_LOG

#define LOGGER_INIT_CONSOLE
#define LOGGER_INIT_FILE

#define LOGGER_TRACE(...)    
#define LOGGER_INFO(...)     
#define LOGGER_WARN(...)     
#define LOGGER_ERROR(...)    
#define LOGGER_PERROR(...)
#define LOGGER_CRITICAL(...) 

#endif // SCORPIO_LOG

#endif // LOG_HPP_