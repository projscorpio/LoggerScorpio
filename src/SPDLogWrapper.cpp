#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include "SPDLogWrapper.hpp"

namespace ScorpioLog {

std::shared_ptr<spdlog::logger> SPDLogWrapper::s_ConsoleLogger;
std::shared_ptr<spdlog::logger> SPDLogWrapper::s_FileLogger;

void SPDLogWrapper::InitConsole()
{
	s_ConsoleLogger = spdlog::stdout_color_mt("ConsoleLogger");
	SetPatternConsole();
	// all messages by default
	s_ConsoleLogger->set_level(spdlog::level::trace);
}

void SPDLogWrapper::InitFile(const std::string& directionary, size_t maxSize, size_t maxFiles)
{
	s_FileLogger = spdlog::rotating_logger_mt("FileLogger", directionary, maxSize, maxFiles);
	SetPatternFile();
	// all messages by default
	s_FileLogger->set_level(spdlog::level::trace);
}

void SPDLogWrapper::SetLevelConsole(const std::string& level)
{
	if(s_ConsoleLogger)
		s_ConsoleLogger->set_level(spdlog::level::from_str(level));
}

void SPDLogWrapper::SetLevelFile(const std::string& level)
{
	if (s_FileLogger)
		s_FileLogger->set_level(spdlog::level::from_str(level));
}

void SPDLogWrapper::SetPatternConsole(const std::string& pattern)
{
	if(s_ConsoleLogger)
		s_ConsoleLogger->set_pattern(pattern);
}

void SPDLogWrapper::SetPatternFile(const std::string& pattern)
{
	if(s_FileLogger)
		s_FileLogger->set_pattern(pattern);
}

} // ScorpioLog 