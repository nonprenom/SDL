#include <cstdarg>
#include <cstdio>
#include <time.h>

#include "Logger.h"

void Logger::info(const char *source_file, const int source_line, const char *fmt...)
{
	time_t rawTime = time(NULL);
	struct tm *timeinfo = localtime(&rawTime);
	char buff[80];

	strftime(buff, 80, "%d/%m/%y %H:%M:%S", timeinfo);
	fprintf(stdout, "%s (%s:%d) ", buff, source_file, source_line);
	va_list args;
	va_start(args, fmt);
	fprintf(stdout, fmt, args);
	va_end(args);
	fprintf(stdout, "\r\n");
}
