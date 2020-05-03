#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"


std::shared_ptr<spdlog::logger> Log::s_Logger;
std::shared_ptr<spdlog::logger> Log::s_StdErr;


void Log::Init()
{
	spdlog::set_pattern("%^[%T] [%t] [%n]: %v%$");

	s_Logger = spdlog::stdout_color_mt("Logger");
	s_StdErr = spdlog::stderr_color_mt("Stderr");

	// all messages by default
	s_Logger->set_level(spdlog::level::trace);
	s_Logger->set_level(spdlog::level::trace);
}


// ========================
// Log levels
// ========================


void Log::LogSetLevel(const std::string& level)
{
	s_Logger->set_level(spdlog::level::from_str(level));
}


void Log::StdErrSetLevel(const std::string& level)
{
	s_Logger->set_level(spdlog::level::from_str(level));
}