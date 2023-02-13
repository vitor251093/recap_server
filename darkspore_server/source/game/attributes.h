
#ifndef _GAME_ATTRIBUTES_HEADER
#define _GAME_ATTRIBUTES_HEADER

// Include
#include <cstdint>
#include <vector>
#include <bitset>

#include "predefined.h"

// Game
namespace Game {
	// Original attribute order
	enum class OriginalAttributes : uint8_t {
		Strength = 0,
		Dexterity,
		Mind,
		MaxHealthIncrease,
		MaxHealth,
		MaxMana,
		DamageReduction,
		PhysicalDefense,
		PhysicalDamageReduction,
		EnergyDefense,
		CriticalRating,								// 10
		NonCombatSpeed,
		CombatSpeed,
		DamageBuff,
		Silence,
		Immobilized,
		DefenseBoostBasicDamage,
		PhysicalDamageIncrease,
		PhysicalDamageIncreaseFlat,
		AutoCrit,
		BehindDirectDamageIncrease,					// 20
		BehindOrSideDirectDamageIncrease,
		CriticalDamageIncrease,
		AttackSpeedScale,
		CooldownScale,
		Frozen,
		ProjectileSpeedIncrease,
		AoEResistance,
		EnergyDamageBuff,
		Intangible,
		HealingReduction,							// 30
		EnergyDamageIncrease,
		EnergyDamageIncreaseFlat,
		Immune,
		StealthDetection,
		LifeSteal,
		RejectModifier,
		AoEDamage,
		TechnologyTypeDamage,
		SpacetimeTypeDamage,
		LifeTypeDamage,								// 40
		ElementsTypeDamage,
		SupernaturalTypeDamage,
		TechnologyTypeResistance,
		SpacetimeTypeResistance,
		LifeTypeResistance,
		ElementsTypeResistance,
		SupernaturalTypeResistance,
		MovementSpeedBuff,
		ImmuneToDebuffs,
		BuffDuration,								// 50
		DebuffDuration,
		ManaSteal,
		DebuffDurationIncrease,
		EnergyDamageReduction,
		Incorporeal,
		DoTDamageIncrease,
		MindControlled,
		SwapDisabled,
		ImmuneToRandomTeleport,
		ImmuneToBanish,								// 60
		ImmuneToKnockback,
		AoeRadius,
		PetDamage,
		PetHealth,
		CrystalFind,
		DNADropped,
		RangeIncrease,
		OrbEffectiveness,
		OverdriveBuildup,
		OverdriveDuration,							// 70
		LootFind,
		Surefooted,
		ImmuneToStunned,
		ImmuneToShocked,
		ImmuneToSleep,
		ImmuneToTaunted,
		ImmuneToTerrified,
		ImmuneToSilence,
		ImmuneToCursed,
		ImmuneToPoisonOrDisease,					// 80
		ImmuneToBurning,
		ImmuneToRooted,
		ImmuneToSlow,
		ImmuneToPull,
		DoTDamageDoneIncrease,
		AggroIncrease,
		AggroDecrease,
		PhysicalDamageDoneIncrease,
		PhysicalDamageDoneByAbilityIncrease,
		EnergyDamageDoneIncrease,					// 90
		EnergyDamageDoneByAbilityIncrease,
		ChannelTimeDecrease,
		CrowdControlDurationDecrease,
		DoTDurationDecrease,
		AoEDurationIncrease,
		HealIncrease,
		OnLockdown,
		HoTDoneIncrease,
		ProjectileDamageIncrease,
		DistributeDamageAmongSquad,					// 100
		DeployBonusInvincibilityTime,
		PhysicalDamageDecreaseFlat,
		EnergyDamageDecreaseFlat,
		MinWeaponDamage,
		MaxWeaponDamage,
		MinWeaponDamagePercent,
		MaxWeaponDamagePercent,
		DirectAttackDamage,
		DirectAttackDamagePercent,
		GetHitAnimDisabled,							// 110
		XPBoost,
		InvisibleToSecurityTeleporters,
		BodyScale,
		DefenseBoostPhysicalDamage,
		Count
	};

	// Combat enums
	enum class DamageSource : uint8_t {
		Physical = 0,
		Energy
	};

	enum class DamageType : uint8_t {
		Technology = 0,
		Spacetime,
		Life,
		Elements,
		Supernatural,
		Generic
	};

	enum class Descriptors : uint32_t {
		IsMelee				= 1 << 0,
		IsBasic				= 1 << 1,
		IsDoT				= 1 << 2,
		IsAoE				= 1 << 3,
		IsBuff				= 1 << 4,
		IsDebuff			= 1 << 5,
		IsPhysicalDamage	= 1 << 6,
		IsEnergyDamage		= 1 << 7,
		IsCosmetic			= 1 << 8,
		IsHaste				= 1 << 9,
		IsChannel			= 1 << 10,
		HitReactNone		= 1 << 11,
		IsHoT				= 1 << 12,
		IsProjectile		= 1 << 13,
		IgnorePlayerCount	= 1 << 14,
		IgnoreDifficulty	= 1 << 15,
		IsSelfResurrect		= 1 << 16,
		IsInteract			= 1 << 17,
		IsThorns			= 1 << 18
	};

	enum class InterfaceType : uint32_t {
		Position = 0,
		Targeted,
		SelfCast,
		AutoTarget,
		CreatureTarget,
		TerrainPoint,
		CreatureTargetDefaultSelf
	};

	// AttributeType
	enum class AttributeType : uint8_t {
		Strength = 0,
		Dexterity,
		Mind,
		MaxHealthIncrease,
		MaxHealth,
		MaxMana,
		DamageReduction,
		PhysicalDefense,
		PhysicalDamageReduction,
		EnergyDefense,
		CriticalRating,
		NonCombatSpeed,
		CombatSpeed,
		DamageBuff,
		Silence,
		Immobilized,
		DefenseBoostBasicDamage,
		PhysicalDamageIncrease,
		PhysicalDamageIncreaseFlat,
		AutoCrit,
		BehindDirectDamageIncrease,
		BehindOrSideDirectDamageIncrease,
		CriticalDamageIncrease,
		AttackSpeedScale,
		CooldownScale,
		Frozen,
		ProjectileSpeedIncrease,
		AoEResistance,
		EnergyDamageBuff,
		Intangible,
		HealingReduction,
		EnergyDamageIncrease,
		EnergyDamageIncreaseFlat,
		Immune,
		StealthDetection,
		LifeSteal,
		RejectModifier,
		AoEDamage,
		TechnologyTypeDamage,
		SpacetimeTypeDamage,
		LifeTypeDamage,
		ElementsTypeDamage,
		SupernaturalTypeDamage,
		TechnologyTypeResistance,
		SpacetimeTypeResistance,
		LifeTypeResistance,
		ElementsTypeResistance,
		SupernaturalTypeResistance,
		MovementSpeedBuff,
		ImmuneToDebuffs,
		BuffDuration,
		DebuffDuration,
		ManaSteal,
		DebuffDurationIncrease,
		EnergyDamageReduction,
		Incorporeal,
		DoTDamageIncrease,
		MindControlled,
		SwapDisabled,
		ImmuneToRandomTeleport,
		ImmuneToBanish,
		ImmuneToKnockback,
		AoeRadius,
		PetDamage,
		PetHealth,
		CrystalFind,
		DNADropped,
		RangeIncrease,
		OrbEffectiveness,
		OverdriveBuildup,
		OverdriveDuration,
		LootFind,
		Surefooted,
		ImmuneToStunned,
		ImmuneToSleep,
		ImmuneToTerrified,
		ImmuneToSilence,
		ImmuneToCursed,
		ImmuneToPoisonOrDisease,
		ImmuneToBurning,
		ImmuneToRooted,
		ImmuneToSlow,
		ImmuneToPull,
		DoTDamageDoneIncrease,
		AggroIncrease,
		AggroDecrease,
		PhysicalDamageDoneIncrease,
		PhysicalDamageDoneByAbilityIncrease,
		EnergyDamageDoneIncrease,
		EnergyDamageDoneByAbilityIncrease,
		ChannelTimeDecrease,
		CrowdControlDurationDecrease,
		DoTDurationDecrease,
		AoEDurationIncrease,
		HealIncrease,
		OnLockdown,
		HoTDoneIncrease,
		ProjectileDamageIncrease,
		DeployBonusInvincibilityTime,
		PhysicalDamageDecreaseFlat,
		EnergyDamageDecreaseFlat,
		MinWeaponDamage,
		MaxWeaponDamage,
		MinWeaponDamagePercent,
		MaxWeaponDamagePercent,
		DirectAttackDamage,
		DirectAttackDamagePercent,
		GetHitAnimDisabled,
		XPBoost,
		InvisibleToSecurityTeleporters,
		BodyScale,
		ClientCount,

		ImmuneToShocked = ClientCount,
		ImmuneToTaunted,
		DistributeDamageAmongSquad,
		DefenseBoostPhysicalDamage,
		Count
	};

	// Attributes
	class Attributes {
		public:
			Attributes() = default;

			const auto& GetData() const { return mData; }
			const auto& GetErasedData() const { return mErasedData; }
			const auto& GetDataBits() const { return mDataBits; }

			float GetValue(uint8_t idx) const;
			float GetValue(AttributeType idx) const;
			void SetValue(uint8_t idx, float value);
			void SetValue(AttributeType idx, float value);

			std::tuple<float, float> GetWeaponDamage() const;
			void SetWeaponDamage(float minDamage, float maxDamage);

			ObjectPtr GetOwnerObject() const;
			void SetOwnerObject(const ObjectPtr& object);

			void WriteTo(RakNet::BitStream& stream) const;
			void WriteReflection(RakNet::BitStream& stream) const;

			void ResetReflectionBits();

		private:
			static constexpr uint8_t sClientVisibleAttributeCount = static_cast<uint8_t>(AttributeType::ClientCount) + 2;

			ObjectPtr::weak_type mOwnerObject;

			std::vector<std::tuple<uint8_t, float>> mData;
			std::vector<uint8_t> mErasedData;
			std::bitset<sClientVisibleAttributeCount> mDataBits;

			float mMinWeaponDamage = 0;
			float mMaxWeaponDamage = 0;
	};

	using AttributesPtr = std::shared_ptr<Attributes>;
}

#endif
