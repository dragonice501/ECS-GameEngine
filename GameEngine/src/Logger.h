#pragma once

#include <string>
#include <vector>

enum LogType
{
	ELT_LOG_INFO,
	ELT_LOG_WARNING,
	ELT_LOG_ERROR
};

struct LogEntry
{
	LogType type;
	std::string message;
};

class Logger
{
private:
	static std::vector<LogEntry> mLogs;

private:
	static std::string CurrentDateTimeToString();

public:
	static void Log(const std::string& message);
	static void Error(const std::string& message);
};