
#ifndef _GAME_REPO_PART_HEADER
#define _GAME_REPO_PART_HEADER

// Include
#include <string>
#include <map>
#include <vector>
#include "../utils/functions.h"
#include "../game/part.h"

// Game
namespace Repository {

	using PartPtr = std::shared_ptr<Game::Part>;

	class Parts {
	public:
		static PartPtr getById(uint16_t id);
		static void Load();
		static std::vector<PartPtr> ListAll();

	private:
		static std::map<uint32_t, PartPtr> mParts;
		friend class Game::Part;
	};
}

#endif
