
#ifndef _GAME_PLAYER_HEADER
#define _GAME_PLAYER_HEADER

// Include
#include "predefined.h"
#include "character.h"
#include "catalyst.h"

// Game
namespace Game {
	// PlayerDataBits
	namespace PlayerDataBits {
		enum : uint8_t {
			DataSetup = 0,
			CurrentDeckIndex,
			QueuedDeckIndex,
			CharacterData,
			PlayerIndex,
			Team,
			PlayerOnlineId,
			Status,
			StatusProgress,
			CurrentCreatureId,
			EnergyPoints,
			IsCharged, // overdrive
			DNA,
			CrystalData,
			CrystalBonuses,
			Level,
			Experience,
			ChainProgression,
			LockCamera,
			LockOverdrive,
			LockCrystals,
			LockAbilityMin,
			LockDeckIndexMin,
			DeckScore,
			Count
		};
	}

	// PlayerUpdateBits
	enum PlayerUpdateBits {
		// Characters (creatures)
		CharacterBits = 1 << 0,
		CharacterLeft = CharacterBits << 0,
		CharacterCenter = CharacterBits << 1,
		CharacterRight = CharacterBits << 2,
		CharacterMask = CharacterLeft | CharacterCenter | CharacterRight,

		// Crystals (catalysts)
		CrystalBits = 1 << 3,
		CrystalTopLeft = CrystalBits << 0,
		CrystalTopCenter = CrystalBits << 1,
		CrystalTopRight = CrystalBits << 2,
		CrystalMidLeft = CrystalBits << 3,
		CrystalMidCenter = CrystalBits << 4,
		CrystalMidRight = CrystalBits << 5,
		CrystalBottomLeft = CrystalBits << 6,
		CrystalBottomCenter = CrystalBits << 7,
		CrystalBottomRight = CrystalBits << 8,
		CrystalMask = CrystalTopLeft | CrystalTopCenter | CrystalTopRight |
			CrystalMidLeft | CrystalMidCenter | CrystalMidRight |
			CrystalBottomLeft | CrystalBottomCenter | CrystalBottomRight,

		// Player data
		PlayerBits = 1 << 12,

		// Mask
		Mask = CharacterMask | CrystalMask | PlayerBits
	};

	// Player
	class Player {
		public:
			static uint32_t GetXPForLevel(uint32_t level);

		public:
			Player(Instance& instance, const SporeNet::UserPtr& user, uint8_t playerIndex);

			const SporeNet::UserPtr& GetUser() const;

			uint64_t GetOnlineId() const;
			uint8_t GetId() const;

			uint32_t GetCurrentDeckIndex() const;
			uint32_t GetAbilityId(uint8_t creatureIndex, uint8_t abilityIndex) const;
			uint32_t GetAbilityRank(uint8_t creatureIndex, uint8_t abilityIndex) const;
			bool IsAbilityLocked(uint8_t abilityIndex) const;

			bool IsOverdriveCharged() const;

			void Setup();

			void GetStatus(uint32_t& status, float& progress) const;
			void SetStatus(uint32_t status, float progress);

			ObjectPtr GetCharacterObject(uint32_t index) const;
			ObjectPtr GetDeployedCharacterObject() const;

			bool SwapCharacter(uint32_t index);
			bool SyncCharacterData();

			SporeNet::SquadPtr GetSquad() const;
			void SetSquad(const SporeNet::SquadPtr& squad);

			const Character& GetCharacter(uint32_t index) const;

			uint32_t GetOpenCatalystSlot() const;
			Catalyst GetCatalyst(uint32_t index) const;
			void SetCatalyst(const Catalyst& crystal, uint32_t index);

			uint16_t GetUpdateBits() const;
			void SetUpdateBits(uint16_t bits);
			void ResetUpdateBits();

			void WriteTo(RakNet::BitStream& stream) const;
			void WriteReflection(RakNet::BitStream& stream) const;

		private:
			bool NeedUpdate() const;

			void SetCharacter(Character&& character, uint32_t index);

			void UpdateCatalystBonuses();

		private:
			Instance& mInstance;

			SporeNet::UserPtr mUser;
			SporeNet::SquadPtr mSquad;

			std::array<ObjectPtr, 3> mCharacterObjects;
			std::array<Character, 3> mCharacterData;
			std::array<Catalyst, 9> mCatalysts {};
			std::array<bool, 8> mCatalystBonuses { false };

			uint64_t mPlayerOnlineId = 0;

			uint32_t mStatus = 0;
			uint32_t mCurrentCreatureId = 0;
			uint32_t mAvatarLevel = 0;
			uint32_t mChainProgression = 0;
			uint32_t mLockedAbilityMin = 0;
			uint32_t mLockedDeckIndexMin = 0;
			uint32_t mDeckScore = 0;

			int32_t mCurrentDeckIndex = 0;
			int32_t mQueuedDeckIndex = 0;
			int32_t mDNA = 0;

			float mStatusProgress = 0.f;
			float mEnergyPoints = 0.f;
			float mAvatarXP = 0.f;

			uint8_t mPlayerIndex = 0;
			uint8_t mTeam = 0;

			bool mbDataSetup = false; // if true then game thinks your lvl/xp is capped (demo mode?)
			bool mbIsCharged = false;
			bool mLockCamera = false;
			bool mbLockedOverdrive = false;
			bool mbLockedCrystals = false;

			std::bitset<PlayerDataBits::Count> mDataBits;
			uint16_t mUpdateBits = 0;

			friend class Instance;
	};

	using PlayerPtr = std::shared_ptr<Player>;
}

#endif
