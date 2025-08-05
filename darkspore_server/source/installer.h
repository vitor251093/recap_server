//
// Created by vitor on 8/4/25.
//

#ifndef INSTALLER_H
#define INSTALLER_H

#include <filesystem>

// Application
class Installer {
	private:
		static bool running;
		static std::string label;

	public:
		static bool isRunning() {return running;}
		static std::string getLabel() {return label;}

		static void LoadDarksporeData(std::string darksporeInstallPath, std::string darksporeInstallVersion);
		static void RunCommand(const std::string& cmd);
		static void MergeDirectories(const std::filesystem::path& source, const std::filesystem::path& destination);
};

#endif //INSTALLER_H
