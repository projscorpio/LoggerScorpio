#include "Log.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

// LOGGER

FileLog::FileLog(const char* name, const char* filePath, size_t maxSize, size_t maxFiles) :
	m_FileLogger(spdlog::rotating_logger_mt(name, filePath, maxSize, maxFiles))
{
	SetPattern(LOG_DEF_FORMAT);
	SetLevel("trace");
}


void FileLog::Trace(const char* messege)
{
	m_FileLogger->trace(messege);
}


void FileLog::Info(const char* messege)
{
	m_FileLogger->info(messege);
}


void FileLog::Warn(const char* messege)
{
	m_FileLogger->warn(messege);
}


void FileLog::Error(const char* messege)
{
	m_FileLogger->error(messege);
}


void FileLog::Critical(const char* messege)
{
	m_FileLogger->critical(messege);
}


void FileLog::SetPattern(const std::string& pattern)
{
	m_FileLogger->set_pattern(pattern);
}

void FileLog::SetLevel(const std::string& level)
{
	m_FileLogger->set_level(spdlog::level::from_str(level));
}


// STATIC LOGGER


std::shared_ptr<spdlog::logger> StaticLog::s_ConsoleLogger;
std::shared_ptr<spdlog::logger> StaticLog::s_FileLogger;


void StaticLog::InitConsole()
{
	s_ConsoleLogger = spdlog::stdout_color_mt("ConsoleLogger");
	SetPatternConsole();
	// all messages by default
	s_ConsoleLogger->set_level(spdlog::level::trace);
}


void StaticLog::InitFile(const std::string& directionary, size_t maxSize, size_t maxFiles)
{
	s_FileLogger = spdlog::rotating_logger_mt("FileLogger", directionary, maxSize, maxFiles);
	SetPatternFile();
	// all messages by default
	s_FileLogger->set_level(spdlog::level::trace);
}


void StaticLog::SetConsoleLevel(const std::string& level)
{
	if(s_ConsoleLogger)
		s_ConsoleLogger->set_level(spdlog::level::from_str(level));
}


void StaticLog::SetFileLevel(const std::string& level)
{
	if (s_FileLogger)
		s_FileLogger->set_level(spdlog::level::from_str(level));
}


void StaticLog::SetPatternConsole(const std::string& pattern)
{
	if(s_ConsoleLogger)
		s_ConsoleLogger->set_pattern(pattern);
}

void StaticLog::SetPatternFile(const std::string& pattern)
{
	if(s_FileLogger)
		s_FileLogger->set_pattern(pattern);
}