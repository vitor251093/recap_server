#ifndef _UTILS_LOGGER_HEADER
#define _UTILS_LOGGER_HEADER

#include <string>
#include <iostream>
#include <chrono>
#include <ctime>  
#include <windows.h>
#include <stdio.h>
#include <time.h>

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
		static std::string time() {
			std::time_t now = std::time(0);
			struct tm  tstruct;
			char buf[80];
			tstruct = *localtime(&now);
			strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
			return buf;
		}

	public:
		static void info(const std::string& msg) {
			if (priority >= 2) {
				setConsoleTextColor(11);
				log(msg);
				setConsoleTextColor(15);
			}
		}
		static void warn(const std::string& msg) {
			if (priority >= 1) {
				setConsoleTextColor(14);
				log(msg);
				setConsoleTextColor(15);
			}
		}
		static void error(const std::string& msg) {
			if (priority >= 0) {
				setConsoleTextColor(12);
				log(msg);
				setConsoleTextColor(15);
			}
		}
		static void log(const std::string& msg) {
			if (priority >= -1) {
				std::cout << "[" + time() + "] " + msg << std::endl;
			}
		}
};

#endif