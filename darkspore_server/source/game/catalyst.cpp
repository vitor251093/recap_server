
// Include
#include "catalyst.h"
#include "object.h"

#include "utils/functions.h"

#include "raknet/types.h"

// Game
namespace Game {
	std::string to_string(CatalystColor color) {
		switch (color) {
			case CatalystColor::Blue: return "blue";
			case CatalystColor::Prismatic: return "prismatic";
			case CatalystColor::Gold: return "yellow";
			case CatalystColor::Red: return "red";
			case CatalystColor::Green: return "green";
		}
		return "unknown";
	}

	std::string to_string(CatalystRarity rarity) {
		switch (rarity) {
			case CatalystRarity::Common: return "common";
			case CatalystRarity::Rare: return "rare";
			case CatalystRarity::Epic: return "epic";
		}
		return "unknown";
	}

	std::string to_string(CatalystType type) {
		switch (type) {
			case CatalystType::AoEDamage: return "aoedamage";
			case CatalystType::AttackSpeed: return "attackspeed";
			case CatalystType::BuffDuration: return "buffduration";
			case CatalystType::CCReduction: return "ccreduction";
			case CatalystType::Cooldown: return "cooldown";
			case CatalystType::Crit: return "crit";
			case CatalystType::Damage: return "damage";
			case CatalystType::DamageAura: return "damageaura";
			case CatalystType::DebuffDuration: return "debuffduration";
			case CatalystType::DebuffIncrease: return "debuffincrease";
			case CatalystType::DefenseRating: return "defenserating";
			case CatalystType::DeflectionRating: return "deflectionrating";
			case CatalystType::Dexterity: return "dexterity";
			case CatalystType::DodgeRating: return "dodgerating";
			case CatalystType::Health: return "health";
			case CatalystType::ImmunePoison: return "immunepoison";
			case CatalystType::ImmuneSleep: return "immunesleep";
			case CatalystType::ImmuneSlow: return "immuneslow";
			case CatalystType::ImmuneStun: return "immunestun";
			case CatalystType::Knockback: return "knockback";
			case CatalystType::LifeLeech: return "lifeleech";
			case CatalystType::Mana: return "mana";
			case CatalystType::ManaCostReduction: return "manacostreduction";
			case CatalystType::ManaLeech: return "manaleech";
			case CatalystType::Mind: return "mind";
			case CatalystType::MoveSpeed: return "movespeed";
			case CatalystType::OrbEffectiveness: return "orbeffectiveness";
			case CatalystType::OverdriveBuildup: return "overdrivebuildup";
			case CatalystType::PetDamage: return "petdamage";
			case CatalystType::PetHealth: return "pethealth";
			case CatalystType::ProjectileSpeed: return "projectilespeed";
			case CatalystType::RangeIncrease: return "rangeincrease";
			case CatalystType::Strength: return "strength";
			case CatalystType::Surefooted: return "surefooted";
			case CatalystType::Thorns: return "thorns";
		}
		return "unknown";
	}

	// Catalyst
	Catalyst::Catalyst(CatalystType type, CatalystRarity rarity, bool prismatic) : mType(type), mRarity(rarity) {
		std::string noun = "crystal_";
		if (prismatic) {
			noun += "wild_";
			mColor = CatalystColor::Prismatic;
		}

		noun += to_string(mType);
		switch (mRarity) {
			case CatalystRarity::Rare:
				noun += "_rare";
				break;

			case CatalystRarity::Epic:
				noun += "_epic";
				break;
		}

		mNounId = utils::hash_id(noun + ".noun");
		if (mColor == CatalystColor::Prismatic) {
			return;
		}

		switch (mType) {
			case CatalystType::AoEDamage:
			case CatalystType::AttackSpeed:
			case CatalystType::Crit:
			case CatalystType::Damage:
			case CatalystType::DamageAura:
			case CatalystType::DebuffIncrease:
			case CatalystType::Knockback:
			case CatalystType::Mana:
			case CatalystType::ProjectileSpeed:
				mColor = CatalystColor::Red;
				break;

			case CatalystType::BuffDuration:
			case CatalystType::DebuffDuration:
			case CatalystType::Dexterity:
			case CatalystType::Mind:
			case CatalystType::PetDamage:
			case CatalystType::PetHealth:
			case CatalystType::Strength:
				mColor = CatalystColor::Gold;
				break;

			case CatalystType::CCReduction:
			case CatalystType::DefenseRating:
			case CatalystType::DeflectionRating:
			case CatalystType::DodgeRating:
			case CatalystType::Health:
			case CatalystType::ImmunePoison:
			case CatalystType::ImmuneSleep:
			case CatalystType::ImmuneSlow:
			case CatalystType::ImmuneStun:
			case CatalystType::ManaCostReduction:
			case CatalystType::Surefooted:
			case CatalystType::Thorns:
				mColor = CatalystColor::Blue;
				break;

			case CatalystType::Cooldown:
			case CatalystType::LifeLeech:
			case CatalystType::ManaLeech:
			case CatalystType::MoveSpeed:
			case CatalystType::OrbEffectiveness:
			case CatalystType::OverdriveBuildup:
			case CatalystType::RangeIncrease:
				mColor = CatalystColor::Green;
				break;
		}
	}

	Catalyst::Catalyst(const LootData& lootData) : Catalyst(
		static_cast<CatalystType>(lootData.GetCatalystType()),
		static_cast<CatalystRarity>(lootData.GetCatalystLevel()),
		lootData.IsCatalystPrismatic()
	) {}

	uint32_t Catalyst::GetNounId() const {
		return mNounId;
	}

	CatalystType Catalyst::GetType() const {
		return mType;
	}

	CatalystColor Catalyst::GetColor() const {
		return mColor;
	}

	CatalystRarity Catalyst::GetRarity() const {
		return mRarity;
	}

	bool Catalyst::MatchingColor(const Catalyst& other) const {
		const auto color = GetColor();
		const auto otherColor = other.GetColor();
		if (color == CatalystColor::None || otherColor == CatalystColor::None) {
			return false;
		} else if (color == CatalystColor::Prismatic || otherColor == CatalystColor::Prismatic) {
			return true;
		}
		return color == otherColor;
	}

	void Catalyst::WriteTo(RakNet::BitStream& stream) const {
		Write<uint32_t>(stream, mNounId);
		Write<uint16_t>(stream, static_cast<uint16_t>(mRarity));

		// padding?
		Write<uint32_t>(stream, 0x00);
		Write<uint32_t>(stream, 0x00);
		Write<uint16_t>(stream, 0x00);
	}

	void Catalyst::WriteReflection(RakNet::BitStream& stream) const {
		RakNet::reflection_serializer<2> reflector(stream);
		reflector.begin();
		reflector.write<0>(mNounId);
		reflector.write<1>(static_cast<uint16_t>(mRarity));
		reflector.end();
	}
}
