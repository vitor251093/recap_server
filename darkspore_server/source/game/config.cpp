
// Include
#include "config.h"

#include <pugixml.hpp>

#include <array>
#include <iostream>
#include <string>
#include <vector>

#ifdef _MSC_VER
#include <string.h>
#define STRCMP_CASE_SENSITIVE _stricmp
#else
#include <strings.h>
#define STRCMP_CASE_SENSITIVE strcasecmp
#endif

// Game
namespace Game {
	// Config
	std::array<std::string, CONFIG_END> Config::mConfig;

	std::string Config::RecapVersion() {
		return "0.2.3";
	}

	void Config::Load(const std::string& path) {
		const auto get_path_value = [](std::string& value) -> std::string& {
			if (value.back() != '/') {
				value.push_back('/');
			}
			return value;
		};

		const auto parse_config_value = [&](pugi::xml_node& node) {
			std::string name = node.attribute("key").value();
			std::string value = node.attribute("value").value();
			if (name == "SKIP_LAUNCHER") {
				mConfig[CONFIG_SKIP_LAUNCHER] = value;
			} else if (name == "VERSION_LOCKED") {
				mConfig[CONFIG_VERSION_LOCKED] = value;
			} else if (name == "SINGLEPLAYER_ONLY") {
				mConfig[CONFIG_SINGLEPLAYER_ONLY] = value;
			} else if (name == "SERVER_HOST") {
				mConfig[CONFIG_SERVER_HOST] = value;
			} else if (name == "SERVER_PORT") {
				mConfig[CONFIG_SERVER_PORT] = value;
			} else if (name == "STORAGE_PATH") {
				mConfig[CONFIG_STORAGE_PATH] = get_path_value(value);
			} else if (name == "WWW_STATIC_PATH") {
				mConfig[CONFIG_WWW_STATIC_PATH] = value;
			} else if (name == "DARKSPORE_INDEX_PAGE_PATH") {
				mConfig[CONFIG_DARKSPORE_INDEX_PAGE_PATH] = value;
			} else if (name == "TEMPLATE_CREATURE_PATH") {
				mConfig[CONFIG_TEMPLATE_CREATURE_PATH] = value;
			} else if (name == "TEMPLATE_CREATURE_PARTS_PATH") {
				mConfig[CONFIG_TEMPLATE_CREATURE_PARTS_PATH] = value;
			} else {
				std::cout << "Game::Config: Unknown config value '" << name << "'" << std::endl;
			}
		};

		mConfig[CONFIG_SKIP_LAUNCHER] = "false";
		mConfig[CONFIG_VERSION_LOCKED] = "false";
		mConfig[CONFIG_SINGLEPLAYER_ONLY] = "true";
		mConfig[CONFIG_SERVER_HOST] = "127.0.0.1";
		mConfig[CONFIG_SERVER_PORT] = "80";
		mConfig[CONFIG_STORAGE_PATH] = "storage/";
		mConfig[CONFIG_WWW_STATIC_PATH] = "data/www/static/";
		mConfig[CONFIG_DARKSPORE_INDEX_PAGE_PATH] = "index.html";
		mConfig[CONFIG_TEMPLATE_CREATURE_PATH] = "data/creature_templates.json";
		mConfig[CONFIG_TEMPLATE_CREATURE_PARTS_PATH] = "data/creature_parts_templates.json";

		pugi::xml_document document;
		if (auto parse_result = document.load_file(path.c_str())) {
			for (auto& child : document.child("configs")) {
				parse_config_value(child);
			}
		} else {
			GenerateDefault(path);
		}
	}

	const std::string& Config::Get(ConfigKey key) {
		return mConfig[key];
	}

	bool Config::GetBool(ConfigKey key) {
		const auto& str = Get(key);
		if (str == "1") {
			return true;
		} else if (STRCMP_CASE_SENSITIVE(str.c_str(), "true") == 0) {
			return true;
		} else {
			return false;
		}
 	}

	int16_t Config::GetI16(ConfigKey key) {
		return static_cast<int16_t>(std::stol(Get(key), nullptr, 0));
	}

	int32_t Config::GetI32(ConfigKey key) {
		return static_cast<int32_t>(std::stol(Get(key), nullptr, 0));
	}

	int64_t Config::GetI64(ConfigKey key) {
		return static_cast<int64_t>(std::stoll(Get(key), nullptr, 0));
	}

	uint16_t Config::GetU16(ConfigKey key) {
		return static_cast<uint16_t>(std::stoul(Get(key), nullptr, 0));
	}

	uint32_t Config::GetU32(ConfigKey key) {
		return static_cast<uint32_t>(std::stoul(Get(key), nullptr, 0));
	}

	uint64_t Config::GetU64(ConfigKey key) {
		return static_cast<uint64_t>(std::stoull(Get(key), nullptr, 0));
	}

	void Config::Set(ConfigKey key, const std::string& value) {
		mConfig[key] = value;
	}

	void Config::GenerateDefault(const std::string& path) {
		const auto value_to_string = [](ConfigKey value) {
			switch (value) {
				case CONFIG_SKIP_LAUNCHER: return "SKIP_LAUNCHER";
				case CONFIG_VERSION_LOCKED: return "VERSION_LOCKED";
				case CONFIG_SINGLEPLAYER_ONLY: return "SINGLEPLAYER_ONLY";
				case CONFIG_SERVER_HOST: return "SERVER_HOST";
				case CONFIG_STORAGE_PATH: return "STORAGE_PATH";
				case CONFIG_WWW_STATIC_PATH: return "WWW_STATIC_PATH";
				case CONFIG_DARKSPORE_INDEX_PAGE_PATH: return "DARKSPORE_INDEX_PAGE_PATH";
				case CONFIG_TEMPLATE_CREATURE_PATH: return "TEMPLATE_CREATURE_PATH";
				case CONFIG_TEMPLATE_CREATURE_PARTS_PATH: return "TEMPLATE_CREATURE_PARTS_PATH";
				default: return "UNKNOWN";
			}
		};

		pugi::xml_document document;
		if (auto configs = document.append_child("configs")) {
			for (size_t i = 0; i < mConfig.size(); ++i) {
				auto config = configs.append_child("config");
				config.append_attribute("key").set_value(value_to_string(static_cast<ConfigKey>(i)));
				config.append_attribute("value").set_value(mConfig[i].c_str());
			}
		}

		if (document.save_file(path.c_str(), "\t", 1U, pugi::encoding_latin1)) {
			std::cout << "Generated a default config.xml" << std::endl;
		} else {
			std::cout << "Could not generate a default config.xml" << std::endl;
		}
	}
}
