#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <typeinfo>
#include <type_traits>

class Logger;

#define LOGGER	\
	Logger(__FILE__, __LINE__)

typedef enum
{
	INFO,
	DEBUG,
	TRACE,
	WARNING,
	ERROR
} LogLevel;

class Logger
{
	int line;
	std::string className;

	const std::string GetClassName(const char* name) const;

	const std::string GetLogTypeMessage(const LogLevel& type) const;

	// Prevent the use of copy constructor and assignment operator for safety.
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

public:
	template <class Class>
	Logger(Class c, int lineNumber)
		: line(lineNumber)
	{
		if constexpr (std::is_same_v<Class, const char*>)
			className = GetClassName(c);
		else
		{
			const std::string name = typeid(c).name();
			size_t pos = name.find(' ', 0) + 1;

			className = (pos == std::string::npos) ? name.c_str() : (name.c_str() + pos);
		}
	}

	template<typename T>
	const Logger& operator<<(const T& value) const
	{
#if defined(_DFLT_LVL_INFO)
		Info(value);
#elif defined(_DFLT_LVL_DEBUG)
		Debug(value);
#elif defined(_DFLT_LVL_TRACE)
		Trace(value);
#elif defined(_DFLT_LVL_WARNING)
		Warning(value);
#else
		Error(value);
#endif // !_DFLT_LVL_
		return *this;
	}

	template<typename... Args>
	inline void Log(const LogLevel& logType, const char* msg, Args... args) const
	{
		std::printf(GetLogTypeMessage(logType).c_str());
		std::printf(msg, args...);
		std::cout << std::endl;

#ifdef _LOG_FILE
		const std::string filename = className + "_log_file.log";
		std::fstream fileStream(filename, std::ios::in | std::ios::out | std::ios::trunc);

		if (fileStream.is_open())
			fileStream << GetLogTypeMessage(logType) << msg << std::endl;
		else
			std::cerr << "Failed opening file!" << std::endl;

		fileStream.close();
#endif // _LOG_FILE
	}

	template<typename... Args>
	void Info(const char* msg, Args... args) const
	{
		Log(INFO, msg, args...);
	}

	template<typename... Args>
	void Debug(const char* msg, Args... args) const
	{
		Log(DEBUG, msg, args...);
	}

	template<typename... Args>
	void Trace(const char* msg, Args... args) const
	{
		Log(TRACE, msg, args...);
	}

	template<typename... Args>
	void Warning(const char* msg, Args... args) const
	{
		Log(WARNING, msg, args...);
	}

	template<typename... Args>
	void Error(const char* msg, Args... args) const
	{
		Log(ERROR, msg, args...);
	}

	template<typename... Args>
	void Error(const std::exception& ex, Args... args) const
	{
		Log(ERROR, ex.what(), args...);
	}
};