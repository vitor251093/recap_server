
#ifndef _GAME_INSTANCE_HEADER
#define _GAME_INSTANCE_HEADER

// Include
#include "predefined.h"

#include "blaze/types.h"
#include "blaze/functions.h"

#include "raknet/types.h"

#include "player.h"
#include "level.h"

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <set>
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

	// CashOutData
	class CashOutData {
		public:
			void WriteTo(RakNet::BitStream& stream) const;

		private:
			std::array<uint32_t, 4> mGoldMedals {};
			std::array<uint32_t, 4> mSilverMedals {};
			std::array<uint32_t, 4> mBronzeMedals {};
			std::array<uint32_t, 4> mUniqueChances {};
			std::array<uint32_t, 4> mRareChances {};

			uint32_t mPlanetsCompleted = 0;

			float mDna = 0;

			friend class Instance;
	};

	// Predefined
	class ObjectManager;
	class Lua;

	// Instance
	class Instance {
		private:
			static InstancePtr Create(uint32_t id);

			Instance(uint32_t id);

		public:
			~Instance();

			bool Start();
			void Stop();

			bool IsLevelLoaded() const;
			bool LoadLevel();

			MarkerPtr GetMarker(uint32_t id) const;

			PlayerPtr GetPlayer(int64_t id) const;
			PlayerPtr GetPlayerByIndex(uint8_t index) const;
			PlayerPtr AddPlayer(const SporeNet::UserPtr& user, uint8_t index);
			void RemovePlayer(int64_t id);

			uint32_t GetId() const;
			uint64_t GetTime() const;
			uint64_t GetTimeElapsed() const;

			ObjectManager& GetObjectManager();
			const ObjectManager& GetObjectManager() const;

			Lua& GetLua();
			const Lua& GetLua() const;

			auto& GetServer() { return *mServer; }
			const auto& GetServer() const { return *mServer; }

			auto& GetChainData() { return mChainData; }
			const auto& GetChainData() const { return mChainData; }

			auto& GetStateData() { return mStateData; }
			const auto& GetStateData() const { return mStateData; }

			auto& GetCashOutData() { return mCashOutData; }
			const auto& GetCashOutData() const { return mCashOutData; }

			auto& GetInfo() { return mData; }
			const auto& GetInfo() const { return mData; }

			const auto& GetObjectives() const { return mObjectives; }

			void AddServerTask(std::function<void(void)> task);
			void AddClientTask(uint8_t id, RakNet::PacketID packet);

			// Events
			void OnObjectCreate(const ObjectPtr& object);
			void OnObjectDestroy(const ObjectPtr& object);
			void OnObjectDeath(const ObjectPtr& object, bool critical, bool knockback);

			void OnPlayerStart(const PlayerPtr& player);

			uint32_t AddTask(uint32_t delay, std::function<void(uint32_t)> task);
			void CancelTask(uint32_t id);

			// Network safe functions
			bool ServerUpdate() const;
			bool Update();

			void MoveObject(const ObjectPtr& object, const Locomotion& locomotionData);

			// Abilities / Combat / Etc
			void UseAbility(const ObjectPtr& object, const RakNet::CombatData& combatData);
			void SwapCharacter(const PlayerPtr& player, uint32_t creatureIndex);
			void InteractWithObject(const PlayerPtr& player, uint32_t objectId);
			void CancelAction(const PlayerPtr& player, const ObjectPtr& object);

			// Loot
			void DropLoot(const PlayerPtr& player, uint64_t lootInstanceId);
			void DropLoot(const ObjectPtr& object, const ObjectPtr& targetObject, DropType dropType);
			void DropLoot();

			void DropCatalyst(const PlayerPtr& player, uint32_t catalystSlot);
			void DropCatalyst();

			//
			void BeamOut(const PlayerPtr& player);

			// Server stuff
			void AddEffect();

			bool SendObjectCreate(const ObjectPtr& object);
			void SendObjectDelete(const ObjectPtr& object);
			void SendObjectDelete(const std::vector<ObjectPtr>& objects);
			void SendObjectUpdate(const ObjectPtr& object);
			void SendAnimationState(const ObjectPtr& object, uint32_t state, bool overlay = false, float scale = 1.f);
			void SendObjectGfxState(const ObjectPtr& object, uint32_t state);
			void SendServerEvent(const ServerEventBase& serverEvent);
			void SendServerEvent(const PlayerPtr& player, const ServerEventBase& serverEvent);
			void SendCombatEvent(const CombatEvent& combatEvent);
			void SendCooldownUpdate(const ObjectPtr& object, uint32_t id, uint64_t start, uint32_t duration);
			void SendLabsPlayerUpdate(const PlayerPtr& player);

		private:
			// Loot
			void PickupLoot(const PlayerPtr& player, const ObjectPtr& object);
			void PickupCatalyst(const PlayerPtr& player, const ObjectPtr& object);

		private:
			std::unique_ptr<RakNet::Server> mServer;
			std::unique_ptr<ObjectManager> mObjectManager;
			std::unique_ptr<Lua> mLua;

			std::unordered_map<uint32_t, MarkerPtr> mMarkers;
			std::map<int64_t, PlayerPtr> mPlayers;

			std::set<uint32_t> mEvents;

			std::vector<RakNet::Objective> mObjectives;
			std::vector<ObjectPtr> mObjects;
			std::vector<glm::vec3> mPlayerSpawnpoints;

			RakNet::ChainVoteData mChainData {};
			RakNet::GameStateData mStateData {};

			CashOutData mCashOutData {};

			Blaze::ReplicatedGameData mData {};

			uint64_t mGameStartTime = 0;
			uint64_t mGameTime = 0;
			uint64_t mGameTimeLua = 0;

			Level mLevel {};

			bool mGameStarted = false;
			bool mLevelLoaded = false;

			friend class GameManager;
	};

	using InstancePtr = std::shared_ptr<Instance>;
}

#endif
