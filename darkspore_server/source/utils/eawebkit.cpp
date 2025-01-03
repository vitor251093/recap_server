
// Include
#include "eawebkit.h"
#include "base64.h"
#include "functions.h"
#include "../game/config.h"
#include "logger.h"

// utils
namespace utils {

	std::string EAWebKit::loadFile(std::string file) {
		std::string contentsFolder = Game::Config::Get(Game::CONFIG_STORAGE_PATH);
		std::string file_data = utils::get_file_text(contentsFolder + file);

		utils::string_replace(file_data, "{{isDev}}", "true");
		utils::string_replace(file_data, "{{recap-version}}", Game::Config::recapVersion());
		utils::string_replace(file_data, "{{host}}", Game::Config::Get(Game::CONFIG_SERVER_HOST));
		utils::string_replace(file_data, "{{game-mode}}", Game::Config::GetBool(Game::CONFIG_SINGLEPLAYER_ONLY) ? "singleplayer" : "multiplayer");

		return file_data;
	}
}
