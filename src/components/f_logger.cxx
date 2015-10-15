#include "f_logger.hpp"

#include <istream>

INITIALIZE_EASYLOGGINGPP

namespace fengine {
	const std::string FLogger::kDefaultConfiguration = R"(
* GLOBAL:
	FORMAT = "%datetime %msg"
	FILENAME = "game.log"
	ENABLED = true
	TO_FILE = true
	TO_STANDARD_OUTPUT = true
	MILLISECONDS_WIDTH = 3
	PERFORMANCE_TRACKING = true
	MAX_LOG_FILE_SIZE = 2097152 ## 2MB - Comment starts with two hashes(##)
	LOG_FLUSH_THRESHOLD = 100 ## Flush after every 100 logs
* DEBUG:
	FORMAT = "%datetime{%d/%M} %func %msg")";

	FLogger::FLogger() {}

	FLogger::~FLogger() {}

	int FLogger::SetDefaultConfiguration()
	{
		return SetConfiguration(kDefaultConfiguration);
	}

	int FLogger::LoadConfiguration(const FString & file_name)
	{
		std::ifstream in_cfg(file_name);
		if (!in_cfg) {
			LOG(WARNING) << "Can't load loggers configuration from file. Set default configuration.";
			if (SetDefaultConfiguration() != 0)
			{
				LOG(WARNING) << "Can't set default configuration.";
			}
			return -1;
		}
		FString str_cfg;

		in_cfg.seekg(std::ifstream::end);
		str_cfg.reserve(in_cfg.tellg());
		in_cfg.seekg(std::ifstream::beg);

		str_cfg.assign(std::istreambuf_iterator<char>(in_cfg), std::istreambuf_iterator<char>());
		
		in_cfg.close();

		return SetConfiguration(str_cfg);
	}

	int FLogger::SetConfiguration(const FString & str_cfg)
	{
		el::Configurations logger_cfg;
		if (!logger_cfg.parseFromText(str_cfg)) {
			return -1;
		}
		//el::Loggers::configureFromGlobal
		el::Loggers::reconfigureAllLoggers(logger_cfg);
		return 0;
	}
}