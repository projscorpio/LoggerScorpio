#include <filesystem>
#include <time.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include "SPDLogWrapper.hpp"

namespace ScorpioLog {

std::shared_ptr<spdlog::logger> SPDLogWrapper::consoleLogger_;
std::shared_ptr<spdlog::logger> SPDLogWrapper::fileLogger_;

void SPDLogWrapper::initConsole()
{
	consoleLogger_ = spdlog::stdout_color_mt("ConsoleLogger");
	setPatternConsole();
	// all messages by default
	consoleLogger_->set_level(spdlog::level::trace);
}

void SPDLogWrapper::initFile()
{
	backupOldFiles();

	// create time string and replace each space with underscore
	time_t currentTime = time(NULL);
	char* dir = strdup(ctime(&currentTime));
	for(size_t i = 0; i < strlen(dir); i++)
		if(dir[i] == ' ') dir[i] = '_';

	fileLogger_ = spdlog::rotating_logger_mt(
		"FileLogger", 
		fmt::format("{}{}{}", LOG_FOLDER, dir, LOG_SUFIX), 
		DEFAULT_MAX_FILE_SIZE, 
		DEFAULT_MAX_FILES
		);

	setPatternFile();
	// all messages by default
	fileLogger_->set_level(spdlog::level::trace);
	free(dir);
}

void SPDLogWrapper::setLevelConsole(const std::string& level)
{
	if(consoleLogger_)
		consoleLogger_->set_level(spdlog::level::from_str(level));
}

void SPDLogWrapper::setLevelConsole(spdlog::level::level_enum level)
{
	if(consoleLogger_)
		consoleLogger_->set_level(level);
}

void SPDLogWrapper::setLevelFile(const std::string& level)
{
	if (fileLogger_)
		fileLogger_->set_level(spdlog::level::from_str(level));
}

void SPDLogWrapper::setLevelFile(spdlog::level::level_enum level)
{
	if (fileLogger_)
		fileLogger_->set_level(level);
}

void SPDLogWrapper::setPatternConsole(const std::string& pattern)
{
	if(consoleLogger_)
		consoleLogger_->set_pattern(pattern);
}

void SPDLogWrapper::setPatternFile(const std::string& pattern)
{
	if(fileLogger_)
		fileLogger_->set_pattern(pattern);
}

void SPDLogWrapper::backupOldFiles()
{
	namespace fs = std::filesystem;
	// create folder for backup
	if (!createFolder(BACKUP_FOLER))
	{
		if (consoleLogger_)
			consoleLogger_->critical("Unable to create folder {}", BACKUP_FOLER);
		exit(0);
	}
	// create folder for new logs
	if (!createFolder(LOG_FOLDER))
	{
		if (consoleLogger_)
			consoleLogger_->critical("Unable to create folder {}", LOG_FOLDER);
		exit(0);
	}
	else
	{
		fs::copy(LOG_FOLDER, BACKUP_FOLER);
		fs::remove_all(LOG_FOLDER);
	}
}

bool SPDLogWrapper::createFolder(const char *dir)
{
	namespace fs = std::filesystem;

	if(!fs::exists(dir))
		return fs::create_directory(dir);

	return true;
}

} // ScorpioLog 