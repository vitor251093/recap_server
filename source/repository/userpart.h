
#ifndef _GAME_REPO_CREATUREPART_HEADER
#define _GAME_REPO_CREATUREPART_HEADER

// Include
#include <string>
#include <map>
#include <vector>
#include "../utils/functions.h"
#include "../game/userpart.h"

// Game
namespace Repository {

	class UserParts {
	public:
		static void Add(Game::UserPartPtr part);
		static void Remove(Game::UserPartPtr part);
		static void Remove(uint64_t id);

		static Game::UserPartPtr getById(uint64_t id);
		static void Load();
		static bool Save();
		static std::vector<Game::UserPartPtr> ListAll();

	private:
		static std::map<uint64_t, Game::UserPartPtr> mPartsById;
		friend class Game::UserPart;
	};
}

#endif
