
#ifndef _GAME_LEADERBOARD_HEADER
#define _GAME_LEADERBOARD_HEADER

#include <cstdint>
#include <vector>
#include <string>

// Game
namespace Game {

	struct LeaderboardPlayerXp {
		uint32_t id;
		std::string name;
		uint32_t rank;

		uint64_t xp;
		uint64_t totalKills;
		uint64_t deaths;
		uint64_t killDeathRatio;
		uint64_t damageMax;
		uint64_t healingMax;
	};
}

#endif
