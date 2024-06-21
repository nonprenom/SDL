#include <stdint.h>
#include <windows.h>
#include <fstream>
#include <iostream>
class Logger
{
public:
	Logger(Logger const &) = delete;
	void operator=(Logger const &) = delete;
	static Logger &getInstance();

	enum
	{
		NOT_INITIALIZED = 0,
		INITIALIZED = 1,
		OUTPUT_TO_CONSOLE = 2,
		OUTPUT_TO_FILE = 4
	};

	void log(const char *logType, const char *sourceFile, const int sourceLine, const char *fmt, ...);

private:
	Logger() = default;
	~Logger();

	uint8_t m_outputs = NOT_INITIALIZED;
	std::ofstream m_file;

	void initialize();
};

#define LOG_INFO(...) Logger::getInstance().log("INFO", __FILE__, __LINE__, __VA_ARGS__)
#define LOG_DBG(...) Logger::getInstance().log("DEBUG", __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) Logger::getInstance().log("ERROR", __FILE__, __LINE__, __VA_ARGS__)
