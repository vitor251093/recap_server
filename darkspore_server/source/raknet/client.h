
#ifndef _RAKNET_CLIENT_HEADER
#define _RAKNET_CLIENT_HEADER

// Include
#include "predefined.h"
#include "types.h"

#include <RakPeerInterface.h>
#include <memory>

enum class GameState : uint32_t {
	Invalid = 0xFFFFFFFF,
	Start = 0,

	Boot = Start,			// 0x00
	Login,					// 0x01
	Spaceship,				// 0x02
	Editor,					// 0x03
	LevelEditor,			// 0x04
	PreDungeon,				// 0x05
	Dungeon,				// 0x06
	Observer,				// 0x07
	Cinematic,				// 0x08
	Spectator,				// 0x09
	Replay,					// 0x0A
	ChainVoting,			// 0x0B
	ChainCashOut,			// 0x0C
	GameOver,				// 0x0D
	Quit,					// 0x0E
	ArenaLobby,				// 0x0F
	ArenaRoundResults,		// 0x10
	JuggernautLobby,		// 0x11
	JuggernautResults,		// 0x12
	KillRaceLobby,			// 0x13
	KillRaceResults,		// 0x14

	Count					// 0x15
};

// RakNet
namespace RakNet {
	class Client {
		public:
			Client(Server& server, const SystemAddress& systemAddress);

			uint8_t GetId() const;

			const Game::PlayerPtr& GetPlayer() const;

			GameStateData& GetGameStateData();
			const GameStateData& GetGameStateData() const;

			GameState GetGameState() const;
			bool SetGameState(GameState newState);

			SporeNet::UserPtr GetUser() const;
			void SetUser(const SporeNet::UserPtr& user);

		private:
			// Client To Server
			

		private:
			Server& mServer;

			SporeNet::UserPtr mUser;
			Game::PlayerPtr mPlayer;

			SystemAddress mSystemAddress;

			uint64_t mLastPing;

			uint8_t mId;

			GameStateData mGameStateData;

			GameState mGameState = GameState::Invalid;

			friend class Server;
	};

	using ClientPtr = std::shared_ptr<Client>;
}

#endif
