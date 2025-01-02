
#ifndef _GAME_SERVEREVENT_HEADER
#define _GAME_SERVEREVENT_HEADER

// Include
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <BitStream.h>
#include <cstdint>

// predefined
namespace SporeNet {
	class Part;
}

// Game
namespace Game {
	class LootData;

	// ServerEvent & ClientEvent (same thing really)
	enum class ClientEventID : uint32_t {
		None = 0,

		AbilityRequiresTarget = 0x6A72BE7D,
		AbilityNotReady = 0xA5F61911,
		SquadAbilityUnavailable = 0xBE855F87,

		OverdriveNotCharged = 0x566C721B,
		OverdriveReady = 0xAD451342,

		PlayerReady = 0x4995368F,
		PlayerCashOut = 0x53B598F9,
		PlayerDeath = 0x62C30464,
		PlayerFreed = 0x414B80B8,
		PlayerLeftGame = 0x459E0873,
		PlayerTrapped = 0x6F8812D2,
		PlayerUnlockedSecondCreature = 0x71E2BC36,
		PlayerEnteredTunnel = 0x8D5AB239,
		PlayerExitedTunnel = 0xE7BE61B3,
		GameOver = 0xF7DA68A5,

		LootRoll = 0x502A2D7E,
		LootPickup = 0x615F3861,
		LootPlayerDrop = 0xA717F30B,
		CatalystPickup = 0x6EA4091E,

		TeleportersDeactivated = 0x57CCFCE5,
		SwitchUnavailable = 0x46C0BC39,
		InvalidTargetArea = 0x38C1D4BE,
		CannotSwitchHeroPerished = 0x38571612,
		WarningFinalHero = 0x28E9B8EC,
		SwitchOnCooldown = 0xA2BC2E34,

		AllyReconnected = 0x0BEDBF7F,
		AllyDisconnected = 0xD30B856C,

		NotEnoughMana = 0x17162DC8,
		HealthLow = 0x72B1FC37,
		ManaLow = 0xD55FA389,

		HordeIncoming = 0x1D42121D,
		HordeDefeated = 0x8047EAF4,

		Unknown = 0x865593D9
	};

	class ServerEventBase {
		public:
			virtual ~ServerEventBase() = default;

			virtual explicit operator bool() const = 0;

			void SetIgnoredPlayerBits(uint8_t bits);

			// virtual void WriteTo(RakNet::BitStream& stream) const = 0; // UNUSED
			virtual void WriteReflection(RakNet::BitStream& stream) const = 0;

		protected:
			static constexpr size_t ReflectionLength = 26;

			uint8_t mIgnoreFlags = 0; // Ignored players
	};

	class ServerEvent : public ServerEventBase {
		public:
			explicit operator bool() const override;

			void WriteReflection(RakNet::BitStream& stream) const override;

		public:
			glm::quat mOrientation {};
			glm::vec3 mPosition {};
			glm::vec3 mFacing {};
			glm::vec3 mTargetPoint {};

			uint32_t mSimpleSwarmEffectId = 0;
			uint32_t mServerEventDef = 0;
			uint32_t mObjectId = 0;
			uint32_t mSecondaryObjectId = 0;
			uint32_t mAttackerId = 0;

			uint8_t mEffectIndex = 0;

			bool mRemove = false;
			bool mHardStop = false;
			bool mForceAttach = false;
			bool mCritical = false;
	};

	class ClientEvent : public ServerEventBase {
		public:
			explicit operator bool() const override;

			void SetEventId(ClientEventID eventId);
			void SetLootPickup(uint8_t playerId, const SporeNet::Part& part);
			void SetLootPickup(uint8_t playerId, const LootData& lootData);
			void SetCatalystPickup(uint8_t playerId);
			void SetPlayerDropLoot(uint8_t playerId, uint64_t lootInstanceId);

			void WriteReflection(RakNet::BitStream& stream) const override;

		private:
			uint64_t mLootInstanceId = 0; // LootPlayerDrop
			uint64_t mLootReferenceId = 0;
			uint64_t mLootCreationTime = 0;

			ClientEventID mEventId = ClientEventID::None;

			uint32_t mLootRigblockId = 0;
			uint32_t mLootSuffixAssetId = 0;
			uint32_t mLootPrefixAssetId1 = 0;
			uint32_t mLootPrefixAssetId2 = 0;
			uint32_t mObjectId = 0; // PlayerFreed, PlayerTrapped

			int32_t mLootItemLevel = 0;
			int32_t mLootRarity = 0;
			int32_t mTextValue = 0; // PlayerCashOut, PlayerLeftGame, PlayerReady, LootDrop
	};

	// CombatEvent
	enum class CombatEventFlags : uint32_t {
		None = 0x000000,
		KillingBlow = 0x000004,
		Critical = 0x000008,
		Deflect = 0x000010,
		Dodge = 0x000020,
		Immune = 0x000040,
		Resist = 0x000080,
		Resurrected = 0x000100,
		Flag0200 = 0x000200,
		Slowed = 0x000800,
		Stunned = 0x001000,
		Taunted = 0x004000,
		Supressed = 0x008000,
		Rooted = 0x010000,
		Terrified = 0x020000,
		Banished = 0x040000,
	};

	class CombatEvent {
		public:
			void WriteReflection(RakNet::BitStream& stream) const;

		public:
			glm::vec3 mDirection {};

			CombatEventFlags mFlags = CombatEventFlags::None;

			uint32_t mTargetId = 0;
			uint32_t mSourceId = 0;
			uint32_t mAbilityId = 0;

			int32_t mIntegerHpChange = 0;

			float mDeltaHealth = 0;
			float mAbsorbedAmount = 0;
	};

	/*
	struct ServerEvent {
		uint32_t simpleSwarmEffectID = 0;
		uint8_t objectFxIndex = 0;
		bool bRemove = false;
		bool bHardStop = false;
		bool bForceAttach = false;
		bool bCritical = false;
		asset ServerEventDef = 0;
		tObjID objectId = 0;
		tObjID secondaryObjectId = 0;
		tObjID attackerId = 0;
		glm::vec3 position {};
		glm::vec3 facing {};
		glm::quat orientation {};
		glm::vec3 targetPoint {};
		int32_t textValue = 0;
		uint32_t clientEventID = 0;
		uint8_t clientIgnoreFlags = 0;
		uint64_t lootReferenceId = 0;
		uint64_t lootInstanceId = 0;
		uint32_t lootRigblockId = 0;
		uint32_t lootSuffixAssetId = 0;
		uint32_t lootPrefixAssetId1 = 0;
		uint32_t lootPrefixAssetId2 = 0;
		int32_t lootItemLevel = 0;
		int32_t lootRarity = 0;
		uint64_t lootCreationTime = 0;

		void WriteTo(BitStream& stream) const;
		void WriteReflection(BitStream& stream) const;
	};
	*/
}

#endif
