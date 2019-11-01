#ifndef _UTILS_LOGGER_HEADER
#define _UTILS_LOGGER_HEADER

#include <string>
#include <iostream>
#include <windows.h>

#ifdef GetObject
#	undef GetObject
#endif


class logger {
	private:
		static const int priority = 2;

		static void setConsoleTextColor(int k) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, k);
		}

	public:
		static void info(const std::string& msg) {
			if (priority >= 2) {
				setConsoleTextColor(11);
				std::cout << msg << std::endl;
			}
		}
		static void warn(const std::string& msg) {
			if (priority >= 1) {
				setConsoleTextColor(14);
				std::cout << msg << std::endl;
			}
		}
		static void error(const std::string& msg) {
			if (priority >= 0) {
				setConsoleTextColor(12);
				std::cout << msg << std::endl;
			}
		}
		static void log(const std::string& msg) {
			if (priority >= -1) {
				setConsoleTextColor(15);
				std::cout << msg << std::endl;
			}
		}
};

#endif