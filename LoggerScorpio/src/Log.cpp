#include "Log.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"


std::shared_ptr<spdlog::logger> Log::s_ConsoleLogger;
std::shared_ptr<spdlog::logger> Log::s_FileLogger;


void Log::InitConsole()
{
	SetPatternConsole();
	s_ConsoleLogger = spdlog::stdout_color_mt("ConsoleLogger");
	// all messages by default
	s_ConsoleLogger->set_level(spdlog::level::trace);
}


void Log::InitFile(const std::string& directionary, size_t maxSize, size_t maxFiles)
{
	SetPatternFile();
	s_FileLogger = spdlog::rotating_logger_mt("FileLogger", directionary, maxSize, maxFiles);
	// all messages by default
	s_FileLogger->set_level(spdlog::level::trace);
}


void Log::SetConsoleLevel(const std::string& level)
{
	s_ConsoleLogger->set_level(spdlog::level::from_str(level));
}


void Log::SetFileLevel(const std::string& level)
{
	s_FileLogger->set_level(spdlog::level::from_str(level));
}


void Log::SetPatternConsole(const std::string& pattern)
{
	s_ConsoleLogger->set_pattern(pattern);
}

void Log::SetPatternFile(const std::string& pattern)
{
	s_FileLogger->set_pattern(pattern);
}


