class Logger
{
private:
	Logger() = default;
	~Logger() = default;

public:
	static void info(const char *source_file, const int source_line, const char *fmt, ...);
};

#define LOG_INFO(...) Logger::info(__FILE__, __LINE__, __VA_ARGS__)
