
#ifndef _GAME_INSTANCE_HEADER
#define _GAME_INSTANCE_HEADER

// Include
#include "predefined.h"

#include "blaze/types.h"
#include "blaze/functions.h"

#include "objectmanager.h"
#include "player.h"

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>

// Game
namespace Game {
	// GameInfo
	struct GameInfo {
		std::map<std::string, std::string> attributes;

		std::vector<uint32_t> capacity;
		std::vector<uint32_t> slots { 0 };

		std::string name;
		std::string level;
		std::string type;

		uint64_t settings = 0;

		int64_t clientId = 0;

		Blaze::IpAddress internalIP;
		Blaze::IpAddress externalIP;

		Blaze::PresenceMode presenceMode;
		Blaze::GameState state;
		Blaze::GameNetworkTopology networkTopology;
		Blaze::VoipTopology voipTopology;

		uint16_t maxPlayers = 0;
		uint16_t queueCapacity = 0;

		bool resetable = false;
		bool ignore = false;
	};

	using GameInfoPtr = std::shared_ptr<GameInfo>;

	// Rule
	struct Rule {
		std::string name;
		std::string thld;
		std::string value;
	};

	// Criteria
	struct Criteria {
		// Custom
		uint32_t ida;
		// NAT
		// PSR
		// RANK
		std::vector<Rule> rules;

	};

	// Matchmaking
	struct Matchmaking {
		GameInfoPtr gameInfo;
		std::string id;
	};

	class Instance {
		private:
			static InstancePtr Create(uint32_t id);

			Instance(uint32_t id);

		public:
			~Instance();

			bool Start();
			void Stop();

			PlayerPtr GetPlayer(int64_t id) const;
			PlayerPtr GetPlayerByIndex(uint8_t index) const;
			PlayerPtr AddPlayer(const SporeNet::UserPtr& user, uint8_t index);
			void RemovePlayer(int64_t id);

			uint32_t GetId() const;

			auto& GetChainData() { return mChainData; }
			const auto& GetChainData() const { return mChainData; }

			auto& GetStateData() { return mStateData; }
			const auto& GetStateData() const { return mStateData; }

			auto& GetInfo() { return mData; }
			const auto& GetInfo() const { return mData; }

			auto& GetObjectManager() { return *mObjectManager; }
			const auto& GetObjectManager() const { return *mObjectManager; }

			const auto& GetObjectives() const { return mObjectives; }

			uint64_t GetTime() const;
			uint64_t GetTimeElapsed() const;

			void AddServerTask(std::function<void(void)> task);
			void AddClientTask(uint8_t id, MessageID packet);

			// Network safe functions
			bool Update();

			void MoveObject(const ObjectPtr& object, const RakNet::cSPVector3& position, RakNet::cLocomotionData& locomotionData);

			// Abilities / Combat / Etc
			void UseAbility(const ObjectPtr& object, const RakNet::CombatData& combatData);
			void SwapCharacter(const PlayerPtr& player, uint32_t creatureIndex);

			// Loot
			void PickupLoot(const PlayerPtr& player, uint32_t lootObjectId);
			void DropLoot(const PlayerPtr& player, uint64_t lootInstanceId);
			void DropLoot();

			void PickupCatalyst(const PlayerPtr& player, uint32_t catalystObjectId);
			void DropCatalyst(const PlayerPtr& player, uint32_t catalystSlot);
			void DropCatalyst();

		private:
			std::unique_ptr<RakNet::Server> mServer;
			std::unique_ptr<ObjectManager> mObjectManager;

			std::map<int64_t, PlayerPtr> mPlayers;

			std::vector<RakNet::Objective> mObjectives;
			std::vector<ObjectPtr> mObjects;

			RakNet::ChainVoteData mChainData;
			RakNet::GameStateData mStateData;

			Blaze::ReplicatedGameData mData;

			uint64_t mGameStartTime = 0;
			uint64_t mGameTime = 0;

			friend class GameManager;
	};

	using InstancePtr = std::shared_ptr<Instance>;
}

#endif
