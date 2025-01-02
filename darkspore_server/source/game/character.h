
#ifndef _GAME_CHARACTER_HEADER
#define _GAME_CHARACTER_HEADER

// Include
#include "attributes.h"

#include <array>

// Game
namespace Game {
	// CharacterDataBits
	namespace CharacterDataBits {
		enum : uint8_t {
			Version = 0,
			NounId,
			AssetId,
			CreatureType,
			DeployCooldown,
			AbilityPoints,
			AbilityRanks,
			Health,
			MaxHealth,
			Mana,
			MaxMana,
			GearScore,
			GearScoreFlattened,
			Count
		};
	}

	// Character
	class Character {
		public:
			Character();
			~Character();

			uint32_t GetNoun() const;
			void SetNoun(uint32_t id);

			uint32_t GetCreatureType() const;
			void SetCreatureType(uint32_t newCreatureType);

			int32_t GetVersion() const;
			void SetVersion(int32_t newVersion);

			float GetHealth() const;
			void SetHealth(float newHealth);
			float GetMaxHealth() const;
			void SetMaxHealth(float newMaxHealth);

			float GetMana() const;
			void SetMana(float newMana);
			float GetMaxMana() const;
			void SetMaxMana(float newMaxMana);

			float GetGearScore() const;
			void SetGearScore(float newGearScore);

			float GetGearScoreFlattened() const;
			void SetGearScoreFlattened(float newGearScoreFlattened);

			void WriteTo(RakNet::BitStream& stream) const;
			void WriteReflection(RakNet::BitStream& stream) const;

			void ResetUpdateBits();

		private:
			Attributes mPartAttributes;

			std::array<uint32_t, 9> mAbilityRanks { 0 };

			uint64_t mAssetId = 0;
			uint64_t mDeployCooldown = 0;

			uint32_t mNounId = 0;
			uint32_t mAbilityPoints = 0;
			uint32_t mCreatureType = 0;

			int32_t mVersion = 0;

			float mHealthPoints = 0;
			float mMaxHealthPoints = 0;
			float mManaPoints = 0;
			float mMaxManaPoints = 0;
			float mGearScore = 300.f;
			float mGearScoreFlattened = 300.f;

			std::bitset<CharacterDataBits::Count> mDataBits;

			friend class Player;
	};

	using CharacterPtr = std::shared_ptr<Character>;
}

#endif
