
// Include
#include "game.h"

// Game
namespace Game {
	// Manager
	std::map<uint64_t, GameInfoPtr> Manager::sGames;
	std::map<std::string, Matchmaking> Manager::sMatchmaking;

	GameInfoPtr Manager::CreateGame() {
		uint64_t id;
		if (sGames.empty()) {
			id = 1;
		} else {
			id = sGames.rbegin()->first + 1;
		}

		auto game = std::make_shared<GameInfo>();
		game->id = id;

		sGames[game->id] = game;
		return game;
	}

	void Manager::RemoveGame(uint64_t id) {
		auto it = sGames.find(id);
		if (it != sGames.end()) {
			sGames.erase(it);
		}
	}

	GameInfoPtr Manager::GetGame(uint64_t id) {
		auto it = sGames.find(id);
		return (it != sGames.end()) ? it->second : nullptr;
	}

	Matchmaking& Manager::StartMatchmaking() {
		return sMatchmaking["test"];
	}
}
