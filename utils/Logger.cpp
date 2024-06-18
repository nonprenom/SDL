#include <cstdarg>
#include <cstdio>
#include <time.h>

#include "Logger.h"

void Logger::log(const char *logType, const char *sourceFile, const int sourceLine, const char *fmt, ...)
{
	time_t rawTime = time(NULL);
	struct tm *timeinfo = localtime(&rawTime);
	char buff[80];

	strftime(buff, 80, "%d/%m/%y %H:%M:%S", timeinfo);
	fprintf(stdout, "%s [%-6s] (%s:%d) ", buff, logType, sourceFile, sourceLine);
	va_list args;
	va_start(args, fmt);
	fprintf(stdout, fmt, args);
	va_end(args);
	fprintf(stdout, "\r\n");
}
