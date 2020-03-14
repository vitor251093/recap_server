#ifndef _UTILS_LOGGER_HEADER
#define _UTILS_LOGGER_HEADER

#include <string>

#ifdef GetObject
#	undef GetObject
#endif


class logger {
	private:
		static const int priority = 2;

		static void setConsoleTextColor(int k);
		static std::string time(const char* format);

	public:
		static void info(const std::string& msg);
		static void warn(const std::string& msg);
		static void error(const std::string& msg);
		static void log(const std::string& msg);
};

#endif