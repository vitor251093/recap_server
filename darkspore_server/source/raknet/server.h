
#ifndef _RAKNET_SERVER_HEADER
#define _RAKNET_SERVER_HEADER

// #define PACKET_LOGGING

// Include
#include "predefined.h"
#include "types.h"
#include "client.h"

#include "game/catalyst.h"

#include "blaze/types.h"

#ifdef PACKET_LOGGING
#	include <PacketLogger.h>
#endif

#define __BITSTREAM_NATIVE_END
#include <BitStream.h>

#include <cstdint>
#include <thread>
#include <mutex>
#include <vector>
#include <map>
#include <array>
#include <queue>
#include <functional>

// RakNet
namespace RakNet {
	// Packet
	/*namespace PacketID {
		constexpr MessageID HelloPlayerRequest = 0x7F;
		constexpr MessageID HelloPlayer = 0x80;
		constexpr MessageID ReconnectPlayer = 0x81;
		constexpr MessageID Connected = 0x82;
		constexpr MessageID Goodbye = 0x83;
		constexpr MessageID PlayerJoined = 0x84;
		constexpr MessageID PartyMergeComplete = 0x85;
		constexpr MessageID PlayerDeparted = 0x86;
		constexpr MessageID VoteKickStarted = 0x87;
		constexpr MessageID PlayerStatusUpdate = 0x88;
		constexpr MessageID GameAborted = 0x89;
		constexpr MessageID GameState = 0x8A;
		constexpr MessageID DirectorState = 0x8B;
		constexpr MessageID ObjectCreate = 0x8C;
		constexpr MessageID ObjectUpdate = 0x8D;
		constexpr MessageID ObjectDelete = 0x8E;
		constexpr MessageID ObjectJump = 0x8F;
		constexpr MessageID ObjectTeleport = 0x90;
		constexpr MessageID ObjectPlayerMove = 0x91;
		constexpr MessageID ForcePhysicsUpdate = 0x92;
		constexpr MessageID PhysicsChanged = 0x93;
		constexpr MessageID LocomotionDataUpdate = 0x94;
		constexpr MessageID LocomotionDataUnreliableUpdate = 0x95;
		constexpr MessageID AttributeDataUpdate = 0x96;
		constexpr MessageID CombatantDataUpdate = 0x97;
		constexpr MessageID InteractableDataUpdate = 0x98;
		constexpr MessageID AgentBlackboardUpdate = 0x99;
		constexpr MessageID LootDataUpdate = 0x9A;
		constexpr MessageID ServerEvent = 0x9B;
		constexpr MessageID ActionCommandMsgs = 0x9C;
		constexpr MessageID PlayerDamage = 0x9E;
		constexpr MessageID LootSpawned = 0x9F;
		constexpr MessageID LootAcquired = 0xA0;
		constexpr MessageID LabsPlayerUpdate = 0xA1;
		constexpr MessageID ModifierCreated = 0xA2;
		constexpr MessageID ModifierUpdated = 0xA3;
		constexpr MessageID ModifierDeleted = 0xA4;
		constexpr MessageID SetAnimationState = 0xA5;
		constexpr MessageID SetObjectGfxState = 0xA6;
		constexpr MessageID PlayerCharacterDeploy = 0xA7;
		constexpr MessageID ActionCommandResponse = 0xA8;
		constexpr MessageID ChainVoteMsgs = 0xA9;
		constexpr MessageID ChainLevelResultsMsgs = 0xAA;
		constexpr MessageID ChainCashOutMsgs = 0xAB;
		constexpr MessageID ChainPlayerMsgs = 0xAC;
		constexpr MessageID ChainGameMsgs = 0xAD;
		constexpr MessageID ChainGameOverMsgs = 0xAE;
		constexpr MessageID QuickGameMsgs = 0xAF;
		constexpr MessageID GamePrepareForStart = 0xB0;
		constexpr MessageID GameStart = 0xB1;
		constexpr MessageID CheatMessageDontUseInReleaseButDontChangeTheIndexOfTheMessagesBelowInCaseWeAreRunningOnADevServer = 0xB2;
		constexpr MessageID ArenaPlayerMsgs = 0xB3;
		constexpr MessageID ArenaLobbyMsgs = 0xB4;
		constexpr MessageID ArenaGameMsgs = 0xB5;
		constexpr MessageID ArenaResultsMsgs = 0xB6;
		constexpr MessageID ObjectivesInitForLevel = 0xB7;
		constexpr MessageID ObjectiveUpdated = 0xB8;
		constexpr MessageID ObjectivesComplete = 0xB9;
		constexpr MessageID CombatEvent = 0xBA;
		constexpr MessageID JuggernautPlayerMsgs = 0xBB;
		constexpr MessageID JuggernautLobbyMsgs = 0xBC;
		constexpr MessageID JuggernautGameMsgs = 0xBD;
		constexpr MessageID JuggernautResultsMsgs = 0xBE;
		constexpr MessageID ReloadLevel = 0xBF;
		constexpr MessageID GravityForceUpdate = 0xC0;
		constexpr MessageID CooldownUpdate = 0xC1;
		constexpr MessageID CrystalDragMessage = 0xC2;
		constexpr MessageID CrystalMessage = 0xC3;
		constexpr MessageID KillRacePlayerMsgs = 0xC4;
		constexpr MessageID KillRaceLobbyMsgs = 0xC5;
		constexpr MessageID KillRaceGameMsgs = 0xC6;
		constexpr MessageID KillRaceResultsMsgs = 0xC7;
		constexpr MessageID TutorialGameMsgs = 0xC8;
		constexpr MessageID CinematicMsgs = 0xC9;
		constexpr MessageID ObjectiveAdd = 0xCA;
		constexpr MessageID LootDropMessage = 0xCB;
		constexpr MessageID DebugPing = 0xCC;
	}*/

	//
	struct CrystalData {
		uint32_t slot = 0;
		uint32_t unk = 0;
		uint32_t color = 0;
		uint32_t level = 0;
	};

	// Server
	class Server {
		public:
			Server(Game::Instance& game);
			~Server();

			void start(uint16_t port);
			void stop();
			bool is_running();

			void run_one();

			void add_task(std::function<void(void)> task);
			void add_client_task(uint8_t id, PacketID packet);

			Game::Instance& GetGame();

		private:
			void ParseRakNetPackets(Packet* packet, uint8_t packetType);
			void ParseSporeNetPackets(Packet* packet, uint8_t packetType);

			ClientPtr AddClient(Packet* packet);
			void RemoveClient(Packet* packet);
			ClientPtr GetClient(Packet* packet) const;
			ClientPtr GetClient(uint8_t id) const;

			const auto& GetClients() const { return mClients; }

			void Send(BitStream& stream, const ClientPtr& client);
			void SendBroadcast(BitStream& stream);
			
			// RakNet
			void OnNewIncomingConnection(Packet* packet);

			// SporeNet
			void OnHelloPlayerRequest(const ClientPtr& client);
			void OnPlayerStatusUpdate(const ClientPtr& client);
			void OnActionCommandMsgs(const ClientPtr& client);
			void OnChainPlayerMsgs(const ClientPtr& client);
			void OnCrystalDragMessage(const ClientPtr& client);
			void OnLootDropMessage(const ClientPtr& client);
			void OnDebugPing(const ClientPtr& client);

			void PrepareGameStart(const ClientPtr& client, uint8_t unknown, uint32_t squadId);

			// Packet commands
			void SendHelloPlayer(const ClientPtr& client);
			void SendReconnectPlayer(const ClientPtr& client, GameState gameState);
			void SendConnected(const ClientPtr& client);
			void SendPlayerJoined(const ClientPtr& client);
			void SendPlayerDeparted(const ClientPtr& client);
			void SendPlayerStatusUpdate(const ClientPtr& client, uint8_t playerState);
			void SendGameState(const ClientPtr& client, const GameStateData& data);
			void SendGameState();
			void SendPlayerCharacterDeploy(const ClientPtr& client, const Game::PlayerPtr& player, uint32_t creatureIndex);
			void SendLabsPlayerUpdate(const ClientPtr& client, const Game::PlayerPtr& player);

			void SendObjectCreate(const ClientPtr& client, const Game::ObjectPtr& object);
			void SendObjectUpdate(const ClientPtr& client, const Game::ObjectPtr& object);
			void SendObjectDelete(const ClientPtr& client, const Game::ObjectPtr& object);
			void SendObjectDelete(const ClientPtr& client, const std::vector<Game::ObjectPtr>& objects);

			void SendActionCancel(const ClientPtr& client, uint8_t value, uint32_t otherValue);

			void SendActionCommandResponse(const ClientPtr& client, uint8_t type);
			void SendActionCommandResponse(const ClientPtr& client, const AbilityCommandResponse& data);
			void SendObjectJump(
				const ClientPtr& client, const Game::ObjectPtr& object, const glm::vec3& destination, const glm::vec3& direction,
				float speed, float minJumpHeight, float maxJumpHeight, float rangeToHitMaxJumpHeight
			);
			void SendObjectTeleport(const ClientPtr& client, const Game::ObjectPtr& object, const glm::vec3& position, const glm::quat& orientation);
			void SendObjectPlayerMove(const ClientPtr& client, const Game::ObjectPtr& object, const Game::Locomotion& locomotionData);
			void SendForcePhysicsUpdate(const ClientPtr& client, const Game::ObjectPtr& object);
			void SendPhysicsChanged(const ClientPtr& client, const Game::ObjectPtr& object, bool hasCollision);
			void SendLocomotionDataUpdate(const ClientPtr& client, const Game::ObjectPtr& object, const Game::Locomotion& locomotionData);
			void SendLocomotionDataUnreliableUpdate(const ClientPtr& client, const Game::ObjectPtr& object, const glm::vec3& position);
			void SendAttributeDataUpdate(const ClientPtr& client, const Game::ObjectPtr& object, const Game::Attributes& attributes);
			void SendCombatantDataUpdate(const ClientPtr& client, const Game::ObjectPtr& object, const Game::CombatantData& combatantData);
			void SendInteractableDataUpdate(const ClientPtr& client, const Game::ObjectPtr& object, const Game::InteractableData& interactableData);
			void SendAgentBlackboardUpdate(const ClientPtr& client, const Game::ObjectPtr& object, const Game::AgentBlackboard& agentBlackboard);
			void SendLootDataUpdate(const ClientPtr& client, const Game::ObjectPtr& object, const Game::LootData& lootData);
			void SendCooldownUpdate(const ClientPtr& client, const Game::ObjectPtr& object, uint32_t id, uint64_t start, uint32_t duration);
			void SendServerEvent(const ClientPtr& client, const Game::ServerEventBase& serverEvent);
			void SendActionCommandMessages(const ClientPtr& client, const Game::PlayerPtr& player);
			void SendCombatEvent(const ClientPtr& client, const Game::CombatEvent& combatEvent);
			void SendModifierCreated(const ClientPtr& client, const Game::ObjectPtr& object);
			void SendModifierUpdated(const ClientPtr& client, const Game::ObjectPtr& object, uint32_t modifierId, uint64_t timestamp, uint32_t stackCount, bool bind);
			void SendModifierDeleted(const ClientPtr& client, const Game::ObjectPtr& object, uint32_t modifierId);
			void SendAnimationState(const ClientPtr& client, const Game::ObjectPtr& object, uint32_t state, uint64_t timestamp, bool overlay, float scale);
			void SendObjectGfxState(const ClientPtr& client, const Game::ObjectPtr& object, uint32_t state, uint64_t timestamp);
			void SendGamePrepareForStart(const ClientPtr& client);
			void SendGameStart(const ClientPtr& client);
			void SendArenaGameMessages(const ClientPtr& client);
			void SendChainVoteMessages(const ClientPtr& client, uint8_t value);
			void SendChainCashOutMessages(const ClientPtr& client, uint8_t value);
			void SendObjectivesInitForLevel(const ClientPtr& client);
			void SendObjectiveUpdate(const ClientPtr& client, uint8_t id, uint32_t voiceover);
			void SendObjectivesComplete(const ClientPtr& client);
			void SendObjectiveAdd(const ClientPtr& client, const Objective& objective);
			void SendDirectorState(const ClientPtr& client, const cAIDirector& director);
			void SendPartyMergeComplete(const ClientPtr& client);
			void SendReloadLevel(const ClientPtr& client);
			void SendCrystalMessage(const ClientPtr& client, uint8_t moveType, uint32_t slot, uint32_t newSlot, const Game::Catalyst& catalyst);

			void SendQuickGame(const ClientPtr& client);
			void SendChainGame(const ClientPtr& client, uint8_t state);
			void SendJuggernautGame(const ClientPtr& client);
			void SendKillRaceGame(const ClientPtr& client);
			void SendCinematic(const ClientPtr& client);
			void SendTutorial(const ClientPtr& client);

			void SendDebugPing(const ClientPtr& client);

			void SendTestPacket(const ClientPtr& client, MessageID id, const std::vector<uint8_t>& data);

		private:
			Game::Instance& mGame;

			std::map<SystemAddress, ClientPtr> mClients;

			// Thread
			std::thread mThread;
			std::mutex mMutex;

			// Task queue
			std::queue<std::function<void(void)>> mTasks;
			std::mutex mTaskMutex;

			// Misc
#ifdef PACKET_LOGGING
			PacketLogger mLogger;
#endif

			BitStream mInStream;

			RakPeerInterface* mSelf = nullptr;

			bool mRunning = true;

			friend class Game::Instance;
	};
}

#endif
