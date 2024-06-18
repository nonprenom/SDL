#include <cstdarg>
#include <cstdio>
#include <ctime>

#include "Logger.h"

void Logger::log(const char *logType, const char *sourceFile, const int sourceLine, const char *fmt, ...)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	struct tm *timeinfo = localtime(&ts.tv_sec);

	char buff[100];

	strftime(buff, sizeof(buff), "%d/%m/%y %H:%M:%S", timeinfo);
	fprintf(stdout, "%s.%03ld [%-6s] (%s:%d) ", buff, ts.tv_nsec / 1000000, logType, sourceFile, sourceLine);
	va_list args;
	va_start(args, fmt);
	fprintf(stdout, fmt, args);
	va_end(args);
	fprintf(stdout, "\r\n");
}
