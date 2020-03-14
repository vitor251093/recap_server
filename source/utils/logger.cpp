
// Include
#include <iostream>
#include <chrono>
#include <ctime>  
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <time.h>

#include "logger.h"
#include "../game/config.h"

void logger::setConsoleTextColor(int k) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
}
std::string logger::time(const char* format) {
	std::time_t now = std::time(0);
	struct tm  tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), format, &tstruct);
	return buf;
}


void logger::info(const std::string& msg) {
	if (priority >= 2) {
		setConsoleTextColor(11);
		log(msg);
		setConsoleTextColor(15);
	}
}
void logger::warn(const std::string& msg) {
	if (priority >= 1) {
		setConsoleTextColor(14);
		log(msg);
		setConsoleTextColor(15);
	}
}
void logger::error(const std::string& msg) {
	if (priority >= 0) {
		setConsoleTextColor(12);
		log(msg);
		setConsoleTextColor(15);
	}
}


void logger::log(const std::string& msg) {
	if (priority >= -1) {
		std::string completeMsg = "[" + time("%Y-%m-%d %X") + "] " + msg;
		std::cout << completeMsg << std::endl;

		std::string filePath = Game::Config::Get(Game::CONFIG_STORAGE_PATH) + "/logs/recap_" + time("%Y-%m-%d") + ".log";
		std::ofstream log_file(filePath.c_str(), std::ios_base::out | std::ios_base::app);
		log_file << completeMsg << '\n';
		log_file.close();
	}
}

