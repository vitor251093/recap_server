
#ifndef _GAME_CONFIG_HEADER
#define _GAME_CONFIG_HEADER

// Include
#include <string>
#include <array>

// Game
namespace Game {
	// Config
	enum ConfigKey {
		CONFIG_SKIP_LAUNCHER = 0,
		CONFIG_VERSION_LOCKED,
		CONFIG_SINGLEPLAYER_ONLY,
		CONFIG_SERVER_HOST,
		CONFIG_SERVER_PORT,
		CONFIG_STORAGE_PATH,
		CONFIG_WWW_STATIC_PATH,
		CONFIG_DARKSPORE_INDEX_PAGE_PATH,
		CONFIG_TEMPLATE_CREATURE_PATH,
		CONFIG_TEMPLATE_CREATURE_PARTS_PATH,
		CONFIG_END
	};

	class Config {
		public:
			static std::string RecapVersion();

			static void Load(const std::string& path);

			static const std::string& Get(ConfigKey key);
			static bool GetBool(ConfigKey key);
			static int16_t GetI16(ConfigKey key);
			static int32_t GetI32(ConfigKey key);
			static int64_t GetI64(ConfigKey key);
			static uint16_t GetU16(ConfigKey key);
			static uint32_t GetU32(ConfigKey key);
			static uint64_t GetU64(ConfigKey key);
			static void Set(ConfigKey key, const std::string& value);

		private:
			static void GenerateDefault(const std::string& path);
		
		private:
			static std::array<std::string, CONFIG_END> mConfig;
	};
}

#endif
