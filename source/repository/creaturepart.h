
#ifndef _GAME_REPO_CREATUREPART_HEADER
#define _GAME_REPO_CREATUREPART_HEADER

// Include
#include <string>
#include <map>
#include <vector>
#include "../utils/functions.h"
#include "../game/creaturepart.h"

// Game
namespace Repository {

	class CreatureParts {
	public:
		static void Add(Game::CreaturePartPtr part);
		static void Remove(Game::CreaturePartPtr part);
		static void Remove(uint64_t id);

		static Game::CreaturePartPtr getById(uint64_t id);
		static void Load();
		static bool Save();
		static std::vector<Game::CreaturePartPtr> ListAll();

	private:
		static std::map<uint64_t, Game::CreaturePartPtr> mPartsById;
		friend class Game::CreaturePart;
	};
}

#endif
