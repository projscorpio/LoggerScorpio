#ifndef LOG_HPP_
#define LOG_HPP_

#include <spdlog/spdlog.h>
// DEFINES
#define LOG_DEF_FORMAT "%^[%T] [%t] %l: %v%$"
#define LOG_DEF_PATH "logs/logfile.log"
#define LOG_DEF_MAX_SIZE 1048576 * 5 // 5MB
#define LOG_DEF_MAX_FILES 10


class FileLog {
public:

	FileLog(const char* name, const char* filePath, size_t maxSize = LOG_DEF_MAX_SIZE, size_t maxFiles = LOG_DEF_MAX_FILES);

	void Trace(const char* messege);
	void Info(const char* messege);
	void Warn(const char* messege);
	void Error(const char* messege);
	void Critical(const char* messege);
	void SetPattern(const std::string& pattern = LOG_DEF_FORMAT);
	void SetLevel(const std::string& level);


private:
	std::shared_ptr<spdlog::logger> m_FileLogger;
};


class StaticLog final {
public:
	// for now it's a singleton
	StaticLog() = delete;
	StaticLog(const StaticLog& other) = delete;

	// must be called at the beggining of the programm
	static void InitConsole();
	static void InitFile(const std::string& directionary = LOG_DEF_PATH, size_t maxSize = LOG_DEF_MAX_SIZE, size_t maxFiles = LOG_DEF_MAX_FILES);

	// easy access to both logger static objects
	static inline std::shared_ptr<spdlog::logger>& GetConsoleLogger() { return s_ConsoleLogger; }
	static inline std::shared_ptr<spdlog::logger>& GetFileLogger() { return s_FileLogger; }

	// changing log levels for standard logget
	static void SetConsoleLevel(const std::string& level);
	static void SetFileLevel(const std::string& level);

	// Sets pattern to both file and console output
	static void SetPatternConsole(const std::string& pattern = LOG_DEF_FORMAT);
	static void SetPatternFile(const std::string& pattern = LOG_DEF_FORMAT);

private:
	static std::shared_ptr<spdlog::logger> s_ConsoleLogger;
	static std::shared_ptr<spdlog::logger> s_FileLogger;
};


// bunch of defines, that wont get compiled if needed
#ifndef NO_LOG

#define INIT_CONSOLE_LOG  StaticLog::InitConsole()
#define LOG_TRACE(...)    StaticLog::GetConsoleLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)     StaticLog::GetConsoleLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)     StaticLog::GetConsoleLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    StaticLog::GetConsoleLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) StaticLog::GetConsoleLogger()->critical(__VA_ARGS__)

#define INIT_FILE_LOG(dir, size, maxFile) StaticLog::InitFile(dir, size, maxFile)
#define FILE_TRACE(...)    StaticLog::GetFileLogger()->trace(__VA_ARGS__)
#define FILE_INFO(...)     StaticLog::GetFileLogger()->info(__VA_ARGS__)
#define FILE_WARN(...)     StaticLog::GetFileLogger()->warn(__VA_ARGS__)
#define FILE_ERROR(...)    StaticLog::GetFileLogger()->error(__VA_ARGS__)
#define FILE_CRITICAL(...) StaticLog::GetFileLogger()->critical(__VA_ARGS__)

#else // NO_LOG

#define INIT_CONSOLE_LOG
#define TRACE(...)
#define INFO(...)
#define WARN(...)
#define ERROR(...)
#define CRITICAL(...)

#define INIT_FILE_LOG(dir, size, maxFile)
#define FILE_TRACE(...)    
#define FILE_INFO(...)     
#define FILE_WARN(...)     
#define FILE_ERROR(...)    
#define FILE_CRITICAL(...)

#endif // NO_LOG


#endif // LOG_HPP_