
#ifndef _GAME_CATALYST_HEADER
#define _GAME_CATALYST_HEADER

// Include
#include "predefined.h"

#include <cstdint>
#include <string>
#include <memory>

// Game
namespace Game {
	enum class CatalystColor : uint8_t {
		None = 0xFF,
		Blue = 0,
		Prismatic,
		Gold,
		Red,
		Green
	};

	enum class CatalystRarity : uint8_t {
		None = 0xFF,
		Common = 0,
		Rare,
		Epic
	};

	enum class CatalystType : uint8_t {
		None = 0xFF,
		AoEDamage = 0,
		AttackSpeed,
		BuffDuration,
		CCReduction,
		Cooldown,
		Crit,
		Damage,
		DamageAura,
		DebuffDuration,
		DebuffIncrease,
		DefenseRating,
		DeflectionRating,
		Dexterity,
		DodgeRating,
		Health,
		ImmunePoison,
		ImmuneSleep,
		ImmuneSlow,
		ImmuneStun,
		Knockback,
		LifeLeech,
		Mana,
		ManaCostReduction,
		ManaLeech,
		Mind,
		MoveSpeed,
		OrbEffectiveness,
		OverdriveBuildup,
		PetDamage,
		PetHealth,
		ProjectileSpeed,
		RangeIncrease,
		Strength,
		Surefooted,
		Thorns
	};

	std::string to_string(CatalystColor color);
	std::string to_string(CatalystRarity rarity);
	std::string to_string(CatalystType type);

	// Catalyst
	class Catalyst {
		public:
			Catalyst() = default;
			Catalyst(CatalystType type, CatalystRarity rarity, bool prismatic);
			Catalyst(const LootData& lootData);

			explicit operator bool() const { return mNounId != 0; }

			uint32_t GetNounId() const;

			CatalystType GetType() const;
			CatalystColor GetColor() const;
			CatalystRarity GetRarity() const;

			bool MatchingColor(const Catalyst& other) const;

			void WriteTo(RakNet::BitStream& stream) const;
			void WriteReflection(RakNet::BitStream& stream) const;

		private:
			uint32_t mNounId = 0;

			CatalystType mType = CatalystType::None;

			CatalystColor mColor = CatalystColor::None;

			CatalystRarity mRarity = CatalystRarity::None;
	};
}

#endif
