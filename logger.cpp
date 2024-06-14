#include <cstdio>
#include <sstream>
#include "logger.h"

const std::string Logger::GetClassName(const char* name) const
{
	std::string fullFilePath(name);
	size_t lastSeparator = fullFilePath.find_last_of("/\\");

	if (lastSeparator == std::string::npos)
	{
		return fullFilePath;
	}

	return fullFilePath.substr(lastSeparator + 1);
}

const std::string Logger::GetLogTypeMessage(const LogLevel& type) const
{
	std::stringstream ss;
	ss << className << ", line: " << line << std::endl;
	const std::string msg = ss.str();

	switch (type)
	{
	default:
	case INFO:
		return msg + "[INFO] ";

	case DEBUG:
		return msg + "[DEBUG] ";

	case TRACE:
		return msg + "[TRACE] ";

	case WARNING:
		return msg + "[WARNING] ";

	case ERROR:
		return msg + "[ERROR] ";
	}
}
