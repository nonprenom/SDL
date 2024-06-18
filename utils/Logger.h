class Logger
{
private:
	Logger() = default;
	~Logger() = default;

public:
	static void log(const char *logType, const char *sourceFile, const int sourceLine, const char *fmt, ...);
};

#define LOG_INFO(...) Logger::log("INFO", __FILE__, __LINE__, __VA_ARGS__)
#define LOG_DBG(...) Logger::log("DEBUG", __FILE__, __LINE__, __VA_ARGS__)
