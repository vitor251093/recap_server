
#ifndef _BLAZE_COMPONENT_GAMEMANAGER_HEADER
#define _BLAZE_COMPONENT_GAMEMANAGER_HEADER

// Include
#include "predefined.h"
#include "blaze/component.h"

// Blaze
namespace Blaze {
	// GameManagerComponent
	class GameManagerComponent : public Component {
		public:
			enum : uint16_t { Id = 0x04 };

			uint16_t GetId() const override;

			std::string_view GetName() const override;
			std::string_view GetReplyPacketName(uint16_t command) const override;
			std::string_view GetNotificationPacketName(uint16_t command) const override;

			bool ParsePacket(Request& request) override;

		public:
			// Notifications
			static void NotifyMatchmakingFailed(Request& request, uint32_t id, MatchmakingResult result);
			static void NotifyMatchmakingAsyncStatus(Request& request, uint32_t id);
			static void NotifyGameCreated(Request& request, uint32_t gameId);
			static void NotifyGameRemoved(Request& request, uint32_t gameId, DestroyGameReason reason);
			static void NotifyGameSetup(Request& request, ReplicatedGameData& gameData, std::vector<ReplicatedGamePlayer>& gamePlayers);
			static void NotifyPlayerJoining(Request& request, const ReplicatedGamePlayer& gamePlayer);
			static void NotifyPlayerJoinCompleted(Request& request, uint32_t gameId, uint32_t personaId);
			static void NotifyPlayerRemoved(Request& request, uint32_t gameId, uint32_t personaId, PlayerRemovedReason reason);
			static void NotifyPlatformHostInitialized(Request& request, uint64_t gameId);
			static void NotifyGameStateChange(Request& request, uint64_t gameId, GameState gameState);
			static void NotifyGameReset(Request& request, ReplicatedGameData& gameData);
			static void NotifyGameSessionUpdated(Request& request, uint32_t gameId);
			static void NotifyGamePlayerStateChange(Request& request, uint32_t gameId, uint32_t personaId, PlayerState playerState);
			static void NotifyCreateDynamicDedicatedServerGame(Request& request, GameManager::CreateGameRequest& gameData);

		private:
			// Responses
			static void WriteCreateGame(TDF::Packet& packet, uint32_t gameId);
			static void WriteJoinGame(TDF::Packet& packet, uint32_t gameId);
			static void WriteStartMatchmaking(TDF::Packet& packet, uint32_t id);
			static void WriteCancelMatchmaking(TDF::Packet& packet, uint32_t id);

			// Requests
			static void CreateGame(Request& request);
			static void DestroyGame(Request& request);
			static void SetPlayerAttributes(Request& request);
			static void JoinGame(Request& request);
			static void RemovePlayer(Request& request);
			static void StartMatchmaking(Request& request);
			static void CancelMatchmaking(Request& request);
			static void FinalizeGameCreation(Request& request);
			static void ResetDedicatedServer(Request& request);
			static void UpdateMeshConnection(Request& request);
	};
}

#endif
