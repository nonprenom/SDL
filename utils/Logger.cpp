#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <windows.h>
#include <string>
#include <stdio.h>

#include "Logger.h"

Logger &Logger::getInstance()
{
	static Logger instance;
	return instance;
}

Logger::~Logger()
{
	LOG_DBG("Closing Logger");
	if (m_outputs & OUTPUT_TO_FILE)
	{
		m_file.close();
	}
}

void Logger::initialize()
{
	// build the INI filename (process_name.ini)
	char INIfileName[MAX_PATH + 1];
	GetModuleFileName(NULL, INIfileName, sizeof(INIfileName));
	strncat(INIfileName, ".ini", sizeof(INIfileName) - strlen(INIfileName));

	// build the default log file name (process_name.log)
	char LOGfileName[MAX_PATH + 1];
	GetModuleFileName(NULL, LOGfileName, sizeof(LOGfileName));
	strncat(LOGfileName, ".log", sizeof(LOGfileName) - strlen(LOGfileName));

	m_outputs = INITIALIZED;

	// Read the config from file
	char buf[8];

	GetPrivateProfileString("Logger", "Console", "true", buf, 5, INIfileName);
	m_outputs |= (std::string(_strlwr(buf)) == "true") * OUTPUT_TO_CONSOLE;

	GetPrivateProfileString("Logger", "File", "false", buf, 5, INIfileName);
	m_outputs |= (std::string(_strlwr(buf)) == "true") * OUTPUT_TO_FILE;

	GetPrivateProfileString("Logger", "Filename", LOGfileName, LOGfileName, sizeof(LOGfileName), INIfileName);

	if (m_outputs & OUTPUT_TO_FILE)
	{
		m_file.open(LOGfileName, std::ios_base::app);
		if (m_file.is_open() == false)
		{
			m_outputs = OUTPUT_TO_CONSOLE;
			LOG_ERROR("Unable to open the log file %s : ", strerror(errno));
		}
	}

	LOG_INFO("Read configuration:");
	LOG_INFO("Console : %s", (m_outputs & OUTPUT_TO_CONSOLE) ? "yes" : "no");
	LOG_INFO("File : %s", (m_outputs & OUTPUT_TO_FILE) ? "yes" : "no");
	LOG_INFO("Filename : %s", LOGfileName);
}

void Logger::log(const char *logType, const char *sourceFile, const int sourceLine, const char *fmt, ...)
{
	if (m_outputs == NOT_INITIALIZED)
	{
		initialize();
	}

	if (m_outputs == INITIALIZED /* only */)
	{
		return;
	}

	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	struct tm *timeinfo = localtime(&ts.tv_sec);

#define MAXLOGLINESIZE 1024

	char output[MAXLOGLINESIZE];
	strftime(output, sizeof(output), "%d/%m/%y %H:%M:%S", timeinfo);
	snprintf(output + strlen(output), MAXLOGLINESIZE - strlen(output), ".%03ld [%-6s] (%s:%d) ", ts.tv_nsec / 1000000, logType, sourceFile, sourceLine);

	va_list args;
	va_start(args, fmt);
	vsnprintf(output + strlen(output), MAXLOGLINESIZE - strlen(output), fmt, args);
	va_end(args);
	sprintf(output + strlen(output), "\n");

	if (m_outputs & OUTPUT_TO_CONSOLE)
	{
		printf(output);
	}
	if (m_outputs & OUTPUT_TO_FILE)
	{
		m_file.write(output, strlen(output));
	}
}
