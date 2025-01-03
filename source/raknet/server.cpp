
// Include
#include "server.h"
#include "../utils/functions.h"
#include "../utils/logger.h"
#include "../game/creature.h"

#include <MessageIdentifiers.h>
#include <RakSleep.h>
#include <RakNetTypes.h>
#include <RakNetworkFactory.h>
#include <BitStream.h>
#include <GetTime.h>

#include <ctime>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <array>

/*
	C2S or C2C
		???

	S2C or C2C
		ID_CONNECTION_REQUEST,
		ID_CONNECTION_REQUEST_ACCEPTED,
		ID_CONNECTION_ATTEMPT_FAILED,
		ID_ALREADY_CONNECTED, (should never happen?)
		ID_NEW_INCOMING_CONNECTION,
		ID_DISCONNECTION_NOTIFICATION,
		ID_CONNECTION_LOST,
		ID_MODIFIED_PACKET, (should never happen?)
		ID_REMOTE_DISCONNECTION_NOTIFICATION, (unexpected in client)
		ID_REMOTE_CONNECTION_LOST, (unexpected in client)
		ID_REMOTE_NEW_INCOMING_CONNECTION (unexpected in client)

	Client packet reliability
		UNRELIABLE
		UNRELIABLE_SEQUENCED
		RELIABLE
		RELIABLE_ORDERED

	Client packet priority
		HIGH_PRIORITY
		MEDIUM_PRIORITY (default)
		LOW_PRIORITY
*/

#define DEFINE_HASH(x) constexpr auto x = utils::hash_id(#x)

namespace Hash {
	DEFINE_HASH(cSpaceshipCameraTuning);
	DEFINE_HASH(SpaceshipTuning);
	DEFINE_HASH(cToolPos);
	DEFINE_HASH(cAssetQueryString);
	DEFINE_HASH(cLayerPrefs);
	DEFINE_HASH(EditorPrefs);
	DEFINE_HASH(cCinematicView);
	DEFINE_HASH(Cinematic);
	DEFINE_HASH(PopupTip);
	DEFINE_HASH(UnlockDef);
	DEFINE_HASH(UnlocksTuning);
	DEFINE_HASH(WeaponDef);
	DEFINE_HASH(WeaponTuning);
	DEFINE_HASH(labsCharacter);
	DEFINE_HASH(labsCrystal);
	DEFINE_HASH(labsPlayer);
	DEFINE_HASH(cControllerState);
	DEFINE_HASH(CatalogEntry);
	DEFINE_HASH(Catalog);
	DEFINE_HASH(TestAsset);
	DEFINE_HASH(TestProcessedAsset);
	DEFINE_HASH(cLootData);
	DEFINE_HASH(LootData);
	DEFINE_HASH(LootSuffix);
	DEFINE_HASH(LootPrefix);
	DEFINE_HASH(LootRigblock);
	DEFINE_HASH(LootPreferences);
	DEFINE_HASH(cKeyAsset);
	DEFINE_HASH(PlayerClass);
	DEFINE_HASH(cLongDescription);
	DEFINE_HASH(cEliteAffix);
	DEFINE_HASH(NonPlayerClass);
	DEFINE_HASH(ClassAttributes);
	DEFINE_HASH(CharacterAnimation);
	DEFINE_HASH(CharacterType);
	DEFINE_HASH(ServerEvent);
	DEFINE_HASH(cAudioEventData);
	DEFINE_HASH(cHardpointInfo);
	DEFINE_HASH(cEffectEventData);
	DEFINE_HASH(ServerEventDef);
	DEFINE_HASH(CombatEvent);
	DEFINE_HASH(InteractableDef);
	DEFINE_HASH(cInteractableData);
	DEFINE_HASH(CombatantDef);
	DEFINE_HASH(cCombatantData);
	DEFINE_HASH(cGfxComponentDef);
	DEFINE_HASH(Gfx);
	DEFINE_HASH(cSPBoundingBox);
	DEFINE_HASH(ExtentsCategory);
	DEFINE_HASH(ObjectExtents);
	DEFINE_HASH(cThumbnailCaptureParameters);
	DEFINE_HASH(Noun);
	DEFINE_HASH(DifficultyTuning);
	DEFINE_HASH(cAttributeData);
	DEFINE_HASH(cAgentBlackboard);
	DEFINE_HASH(NavMeshLayer);
	DEFINE_HASH(NavPowerTuning);
	DEFINE_HASH(Markerset);
	DEFINE_HASH(LevelMarkerset);
	DEFINE_HASH(LevelCameraSettings);
	DEFINE_HASH(LevelKey);
	DEFINE_HASH(LevelObjectives);
	DEFINE_HASH(Level);
	DEFINE_HASH(DirectorClass);
	DEFINE_HASH(LevelConfig);
	DEFINE_HASH(DirectorBucket);
	DEFINE_HASH(SectionConfig);
	DEFINE_HASH(SpawnPointDef);
	DEFINE_HASH(SpawnTriggerDef);
	DEFINE_HASH(DirectorTuning);
	DEFINE_HASH(cAIDirector);
	DEFINE_HASH(cMapCameraData);
	DEFINE_HASH(LocomotionTuning);
	DEFINE_HASH(cLobParams);
	DEFINE_HASH(cProjectileParams);
	DEFINE_HASH(cLocomotionData);
	DEFINE_HASH(TriggerVolumeEvents);
	DEFINE_HASH(TriggerVolumeDef);
	DEFINE_HASH(NPCAffix);
	DEFINE_HASH(cAffixDifficultyTuning);
	DEFINE_HASH(EliteNPCGlobals);
	DEFINE_HASH(CrystalDef);
	DEFINE_HASH(CrystalDropDef);
	DEFINE_HASH(CrystalLevel);
	DEFINE_HASH(CrystalTuning);
	DEFINE_HASH(cGameObjectGfxStateData);
	DEFINE_HASH(cGameObjectGfxStates);
	DEFINE_HASH(GameObjectGfxStateTuning);
	DEFINE_HASH(cVolumeDef);
	DEFINE_HASH(cPressureSwitchDef);
	DEFINE_HASH(cSwitchDef);
	DEFINE_HASH(cDoorDef);
	DEFINE_HASH(cNewGfxState);
	DEFINE_HASH(cWaterSimData);
	DEFINE_HASH(cGraphicsData);
	DEFINE_HASH(cGrassData);
	DEFINE_HASH(cSplineCameraData);
	DEFINE_HASH(cAnimatorData);
	DEFINE_HASH(cAnimatedData);
	DEFINE_HASH(cLabsMarker);
	DEFINE_HASH(sporelabsObject);
	DEFINE_HASH(cGameObjectCreateData);
	DEFINE_HASH(cAssetProperty);
	DEFINE_HASH(cAssetPropertyList);
	DEFINE_HASH(ability);
	DEFINE_HASH(AIDefinition);
	DEFINE_HASH(cAINode);
	DEFINE_HASH(Phase);
	DEFINE_HASH(Condition);
	DEFINE_HASH(cGambitDefinition);
	DEFINE_HASH(cAICondition);
	DEFINE_HASH(MagicNumbers);
	DEFINE_HASH(cWaterData);
	DEFINE_HASH(TeleporterDef);
	DEFINE_HASH(SpaceshipSpawnPointDef);
	DEFINE_HASH(SharedComponentData);
	DEFINE_HASH(cPointLightData);
	DEFINE_HASH(cSpotLightData);
	DEFINE_HASH(cLineLightData);
	DEFINE_HASH(cParallelLightData);
	DEFINE_HASH(cSplineCameraNodeBaseData);
	DEFINE_HASH(cSplineCameraNodeData);
	DEFINE_HASH(cOccluderData);
	DEFINE_HASH(EventListenerData);
	DEFINE_HASH(EventListenerDef);
	DEFINE_HASH(cDecalData);
	DEFINE_HASH(cCameraComponentData);
	DEFINE_HASH(cCameraComponent);
	DEFINE_HASH(AudioTriggerDef);
	DEFINE_HASH(objective);
	DEFINE_HASH(affix);
	DEFINE_HASH(AffixTuning);
	DEFINE_HASH(GravityForce);
	DEFINE_HASH(CollisionVolumeDef);
	DEFINE_HASH(ProjectileDef);
	DEFINE_HASH(OrbitDef);
	DEFINE_HASH(TriggerVolumeComponentDef);
}
#undef DEFINE_HASH

template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> bswap(T t) {
	constexpr auto size = sizeof(T);
	if constexpr (size == 2) {
		t = (t >> 8) |
			(t << 8);
	} else if constexpr (size == 4) {
		t = (t << 24) |
			((t & 0x0000FF00U) << 8) |
			((t & 0x00FF0000U) >> 8) |
			(t >> 24);
	} else if constexpr (size == 8) {
		t = (t << 56) |
			((t & 0x000000000000FF00ULL) << 40) |
			((t & 0x0000000000FF0000ULL) << 24) |
			((t & 0x00000000FF000000ULL) << 8) |
			((t & 0x000000FF00000000ULL) >> 8) |
			((t & 0x0000FF0000000000ULL) >> 24) |
			((t & 0x00FF000000000000ULL) >> 40) |
			(t >> 56);
	}
	return t;
}

template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, T> bswap(T t) {
	T value;

	auto pValue = reinterpret_cast<uint8_t*>(&t);
	auto pNewValue = reinterpret_cast<uint8_t*>(&value);

	constexpr auto size = sizeof(T);
	for (size_t i = 0; i < size; i++) {
		pNewValue[size - 1 - i] = pValue[i];
	}

	return value;
}

template<typename T>
std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, void> Read(RakNet::BitStream& stream, T& value) {
	if constexpr (std::is_same_v<T, bool>) {
		stream.Read<uint8_t>(reinterpret_cast<uint8_t&>(value));
	} else {
		stream.Read<T>(value);
		value = bswap<T>(value);
	}
}

template<typename T>
std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, void> Write(RakNet::BitStream& stream, T value) {
	if constexpr (std::is_same_v<T, bool>) {
		stream.Write<uint8_t>(value);
	} else {
		stream.Write<T>(bswap<T>(value));
	}
}

template<typename T>
std::enable_if_t<std::is_same_v<std::remove_cvref_t<T>, uint24_t>, void> Write(RakNet::BitStream& stream, T value) {
	uint8_t* pVal = reinterpret_cast<uint8_t*>(&value.val);
	stream.Write<uint8_t>(pVal[0]);
	stream.Write<uint8_t>(pVal[1]);
	stream.Write<uint8_t>(pVal[2]);
}

template<typename T>
constexpr std::enable_if_t<std::is_integral_v<T>, T> bits_to_bytes(T bits) {
	return (bits + 7) >> 3;
}

template<typename T>
constexpr std::enable_if_t<std::is_integral_v<T>, T> bytes_to_bits(T bytes) {
	return bytes << 3;
}

#pragma warning(push)
#pragma warning(disable:4309)
template<typename T, int Bits>
constexpr T get_bits() {
	return static_cast<T>((1 << Bits) - 1);
}
#pragma warning(pop)

// TODO: add array support
class reflection {
	public:
		template<size_t FieldsInClass, typename Tuple>
		static void write(RakNet::BitStream& stream, const Tuple& tuple) {
			constexpr auto Size = std::tuple_size<Tuple>::value;
			if constexpr (FieldsInClass > 16) {
				write_field_by_field<Tuple, Size>(stream, tuple);
			} else {
				write_fields<FieldsInClass, Tuple, Size>(stream, tuple);
			}
		}
		
		template<size_t FieldsInClass, typename T, typename... Args>
		static void write_some(RakNet::BitStream& stream, Args&&... args) {
			if constexpr (FieldsInClass > 16) {
				write_some_field_by_field(stream, args...);
			} else {
				write_some_fields<FieldsInClass>(stream, args...);
			}
		}
		
	private:
		template<typename T, size_t S>
		static void write_type(RakNet::BitStream& stream, const std::array<T, S>& value) {
			for (const T& arrValue : value) {
				write_type(stream, arrValue);
			}
		}

		template<typename T>
		static void write_type(RakNet::BitStream& stream, T value) {
			if constexpr (std::is_class_v<T>) {
				value.WriteTo(stream);
			} else {
				Write<T>(stream, value);
			}
		}

		template<typename Tuple, size_t Size, size_t Idx = 0>
		static void write_field_by_field(RakNet::BitStream& stream, const Tuple& tuple) {
			if constexpr (Idx >= Size) {
				Write<uint8_t>(stream, 0xFF);
			} else {
				Write<uint8_t>(stream, Idx);
				write_type(stream, std::get<Idx>(tuple));
				write_field_by_field<Tuple, Size, Idx + 1>(stream, tuple);
			}
		}

		template<size_t FieldsInClass, typename Tuple, size_t Size, size_t Idx = 0>
		static void write_fields(RakNet::BitStream& stream, const Tuple& tuple) {
			if constexpr (Idx == 0) {
				if (FieldsInClass > 8) {
					Write<uint16_t>(stream, get_bits<uint16_t, Size>());
				} else {
					Write<uint8_t>(stream, get_bits<uint8_t, Size>());
				}
			}

			if constexpr (Idx < Size) {
				write_type(stream, std::get<Idx>(tuple));
				write_fields<FieldsInClass, Tuple, Size, Idx + 1>(stream, tuple);
			}
		}

		// write_some_field_by_field
		static void write_some_field_by_field(RakNet::BitStream& stream) {
			Write<uint8_t>(stream, 0xFF);
		}

		template<typename T, typename... Args>
		static void write_some_field_by_field(RakNet::BitStream& stream, uint8_t idx, const T& value, Args&&... args) {
			Write<uint8_t>(stream, idx);
			write_type(stream, value);
			write_some_field_by_field(stream, args...);
		}

		// write_some_fields
		static void internal_write_some_fields(RakNet::BitStream& stream, uint16_t& bits) {}

		template<typename T, typename... Args>
		static void internal_write_some_fields(RakNet::BitStream& stream, uint16_t& bits, uint8_t idx, const T& value, Args&& ... args) {
			bits |= (1 << idx);
			write_type(stream, value);
			internal_write_some_fields(stream, bits, args...);
		}

		template<size_t FieldsInClass, typename... Args>
		static void write_some_fields(RakNet::BitStream& stream, Args&& ... args) {
			size_t streamPosition = stream.GetWriteOffset();
			if constexpr (FieldsInClass > 8) {
				Write<uint16_t>(stream, 0);
			} else {
				Write<uint8_t>(stream, 0);
			}

			uint16_t bits = 0;
			internal_write_some_fields(stream, bits, args...);

			size_t currentPosition = stream.GetWriteOffset();
			stream.SetWriteOffset(streamPosition);
			if constexpr (FieldsInClass > 8) {
				Write<uint16_t>(stream, bits);
			} else {
				Write<uint8_t>(stream, bits);
			}

			stream.SetWriteOffset(currentPosition);
		}
};

// Test classes
namespace Hash {
	constexpr auto Zero = utils::hash_id("0");
	// constexpr auto Noun = utils::hash_id("Noun");
}

// Abilities
namespace Ability {
	enum : uint32_t {
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
		AoeResistance,
		EnergyDamageBuff,
		Intangible,
		HealingReduction,
		EnergyDamageIncrease,
		EnergyDamageIncreaseFlat,
		Immune,
		StealthDetection,
		LifeSteal,
		RejectModifier,
		AoeDamage,
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
		DotDamageIncrease,
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
		DotDamageDoneIncrease,
		AggroIncrease,
		AggroDecrease,
		PhysicalDamageDoneIncrease,
		PhysicalDamageDoneByAbilityIncrease,
		EnergyDamageDoneIncrease,
		EnergyDamageDoneByAbilityIncrease,
		ChannelTimeDecrease,
		CrowdControlDurationDecrease,
		DotDurationDecrease,
		AoeDurationIncrease,
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
		Count
	};
}

using tObjID = uint32_t;

struct cSPVector3 {
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	void WriteTo(RakNet::BitStream& stream) const {
		Write(stream, x);
		Write(stream, y);
		Write(stream, z);
	}
};

struct cSPQuaternion {
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float w = 0.f;

	void WriteTo(RakNet::BitStream& stream) const {
		Write(stream, x);
		Write(stream, y);
		Write(stream, z);
		Write(stream, w);
	}
};

struct labsCharacter {
	/*
		memory layout (hex)
			0 : unk
			8 : assetID
			10 : version
			B4 : nounDef

			B8 - 1DC : mAttribute (0x4A)
			1E4 : mAttribute (0x01)
			1EC - 244 : mAttribute (0x17)
			24C - 27C : mAttribute (0x0D)

			3B8 : mCreatureType

			3C0 : mDeployCooldownMs
			3C8 : mAbilityPoints
			3CC : mAbilityRanks

			3F0 : mHealthPoints
			3F4 : mMaxHealthPoints
			3F8 : mManaPoints
			3FC : mMaxManaPoints
			400 : mGearScore
			404 : mGearScoreFlattened
	*/

	int32_t version = 0;
	uint32_t nounDef = 0;
	uint64_t assetID = 0;
	uint32_t mCreatureType = 0;
	uint64_t mDeployCooldownMs = 0;
	uint32_t mAbilityPoints = 0;
	uint32_t mAbilityRanks = 0;
	float mHealthPoints = 50.f;
	float mMaxHealthPoints = 100.f;
	float mManaPoints = 75.f;
	float mMaxManaPoints = 100.f;
	float mGearScore = 300.f;
	float mGearScoreFlattened = 300.f;

	// make some sort of map?
	float mAttribute[Ability::Count];

	void WriteTo(RakNet::BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x620);

		auto writeOffset = stream.GetWriteOffset();
		stream.AddBitsAndReallocate(size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x008));
		Write(stream, assetID);
		Write(stream, version);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x0B4));
		Write(stream, nounDef);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x0B8));
		for (size_t i = 0; i < 0x4A; ++i) {
			Write(stream, mAttribute[i]);
		}

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1E4));
		Write(stream, mAttribute[0x4B]);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1EC));
		for (size_t i = 0x4C; i < 0x63; ++i) {
			Write(stream, mAttribute[i]);
		}

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x24C));
		for (size_t i = 0x64; i < 0x6F; ++i) {
			Write(stream, mAttribute[i]);
		}

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x3B8));
		Write(stream, mCreatureType);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x3C0));
		Write(stream, mDeployCooldownMs);
		Write(stream, mAbilityPoints);
		Write(stream, mAbilityRanks);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x3F0));
		Write(stream, mHealthPoints);
		Write(stream, mMaxHealthPoints);
		Write(stream, mManaPoints);
		Write(stream, mMaxManaPoints);
		Write(stream, mGearScore);
		Write(stream, mGearScoreFlattened);

		stream.SetWriteOffset(writeOffset + size);
	}

	void WriteReflection(RakNet::BitStream& stream) const {
		reflection::write<124>(stream, std::make_tuple(
			version, nounDef,
			assetID, mCreatureType,
			mDeployCooldownMs, mAbilityPoints,
			mAbilityRanks, mHealthPoints,
			mMaxHealthPoints, mManaPoints,
			mMaxManaPoints, mGearScore,
			mGearScoreFlattened
		));
	}
};

struct labsCrystal {
	enum Type {
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

	uint32_t crystalNoun;
	uint16_t level;

	labsCrystal() : crystalNoun(0), level(0) {}
	labsCrystal(Type type, uint16_t rarity, bool prismatic) {
		level = rarity;

		std::string nounName = "crystal_";
		if (prismatic) {
			nounName += "wild_";
		}

		switch (type) {
			case AoEDamage:
				nounName += "aoedamage";
				break;

			case AttackSpeed:
				nounName += "attackspeed";
				break;

			case BuffDuration:
				nounName += "buffduration";
				break;

			case CCReduction:
				nounName += "ccreduction";
				break;

			case Cooldown:
				nounName += "cooldown";
				break;

			case Crit:
				nounName += "crit";
				break;

			case Damage:
				nounName += "damage";
				break;

			case DamageAura:
				nounName += "damageaura";
				break;

			case DebuffDuration:
				nounName += "debuffduration";
				break;

			case DebuffIncrease:
				nounName += "debuffincrease";
				break;

			case DefenseRating:
				nounName += "defenserating";
				break;

			case DeflectionRating:
				nounName += "deflectionrating";
				break;

			case Dexterity:
				nounName += "dexterity";
				break;

			case DodgeRating:
				nounName += "dodgerating";
				break;

			case Health:
				nounName += "health";
				break;

			case ImmunePoison:
				nounName += "immunepoison";
				break;

			case ImmuneSleep:
				nounName += "immunesleep";
				break;

			case ImmuneSlow:
				nounName += "immuneslow";
				break;

			case ImmuneStun:
				nounName += "immunestun";
				break;

			case Knockback:
				nounName += "knockback";
				break;

			case LifeLeech:
				nounName += "lifeleech";
				break;

			case Mana:
				nounName += "mana";
				break;

			case ManaCostReduction:
				nounName += "manacostreduction";
				break;

			case ManaLeech:
				nounName += "manaleech";
				break;

			case Mind:
				nounName += "mind";
				break;

			case MoveSpeed:
				nounName += "movespeed";
				break;

			case OrbEffectiveness:
				nounName += "orbeffectiveness";
				break;

			case OverdriveBuildup:
				nounName += "overdrivebuildup";
				break;

			case PetDamage:
				nounName += "petdamage";
				break;

			case PetHealth:
				nounName += "pethealth";
				break;

			case ProjectileSpeed:
				nounName += "projectilespeed";
				break;

			case RangeIncrease:
				nounName += "rangeincrease";
				break;

			case Strength:
				nounName += "strength";
				break;

			case Surefooted:
				nounName += "surefooted";
				break;

			case Thorns:
				nounName += "thorns";
				break;

		}

		if (level == 1) {
			nounName += "_rare";
		} else if (level == 2) {
			nounName += "_epic";
		}

		crystalNoun = utils::hash_id((nounName + ".noun").c_str());
	}

	void WriteTo(RakNet::BitStream& stream) const {
		Write<uint32_t>(stream, crystalNoun);
		Write<uint16_t>(stream, level);

		// padding
		Write<uint32_t>(stream, 0x00);
		Write<uint32_t>(stream, 0x00);
		Write<uint16_t>(stream, 0x00);
	}

	void WriteReflection(RakNet::BitStream& stream) const {
		reflection::write<2>(stream, std::make_tuple(crystalNoun, level));
	}
};

struct labsPlayer {
	bool mbDataSetup = false;
	int32_t mCurrentDeckIndex = 0;
	int32_t mQueuedDeckIndex = 0;
	std::array<labsCharacter, 3> mCharacters;
	uint8_t mPlayerIndex = 0;
	uint8_t mTeam = 0;
	uint64_t mPlayerOnlineId = 0;
	uint32_t mStatus = 0;
	float mStatusProgress = 0.f;
	tObjID mCurrentCreatureId = 0;
	float mEnergyPoints = 0.f;
	bool mbIsCharged = false;
	int32_t mDNA = 0;

	std::array<labsCrystal, 9> mCrystals;
	std::array<bool, 8> mCrystalBonuses;

	uint32_t mAvatarLevel = 0;
	float mAvatarXP = 0.f;
	uint32_t mChainProgression = 0;
	bool mLockCamera = false;
	bool mbLockedOverdrive = false;
	bool mbLockedCrystals = false;
	uint32_t mLockedAbilityMin;
	uint32_t mLockedDeckIndexMin;
	uint32_t mDeckScore;

	void WriteTo(RakNet::BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x14B8);

		auto writeOffset = stream.GetWriteOffset();
		stream.AddBitsAndReallocate(size);

		stream.SetWriteOffset(writeOffset);
		Write(stream, mbDataSetup);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x0004));
		Write(stream, mStatus);
		Write(stream, mStatusProgress);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x000C));
		Write(stream, mCurrentDeckIndex);
		Write(stream, mQueuedDeckIndex);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x0018));
		for (const auto& character : mCharacters) {
			character.WriteTo(stream);
		}

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1278));
		Write(stream, mPlayerIndex);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x12DC));
		Write(stream, mTeam);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1280));
		Write(stream, mPlayerOnlineId);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x12E0));
		Write(stream, mCurrentCreatureId);
		Write(stream, mEnergyPoints);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x12EC));
		Write(stream, mbIsCharged);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x12F0));
		Write(stream, mDNA);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x12F8));
		Write(stream, mAvatarXP);
		Write(stream, mAvatarLevel);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1304));
		Write(stream, mChainProgression);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x133C));
		for (const auto& crystal : mCrystals) {
			crystal.WriteTo(stream);
		}

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x13CC));
		for (auto crystalBonus : mCrystalBonuses) {
			Write(stream, crystalBonus);
		}

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1408));
		Write(stream, mLockCamera);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x140C));
		Write(stream, mDeckScore);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1414));
		Write(stream, mbLockedOverdrive);
		Write(stream, mbLockedCrystals);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1418));
		Write(stream, mLockedAbilityMin);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1420));
		Write(stream, mLockedDeckIndexMin);

		stream.SetWriteOffset(writeOffset + size);
	}

	void WriteReflection(RakNet::BitStream& stream) const {
		reflection::write<24>(stream, std::make_tuple(
			mbDataSetup, mCurrentDeckIndex,
			mQueuedDeckIndex,
			mCharacters, mPlayerIndex, mTeam,
			mPlayerOnlineId, mStatus,
			mStatusProgress, mCurrentCreatureId,
			mEnergyPoints, mbIsCharged, mDNA,
			mCrystals, mCrystalBonuses,
			mAvatarLevel, mAvatarXP,
			mChainProgression, mLockCamera,
			mbLockedOverdrive, mbLockedCrystals,
			mLockedAbilityMin, mLockedDeckIndexMin,
			mDeckScore
		));
	}
};

struct cGameObjectCreateData {
	/* 00h */    uint32_t noun;
	/* 04h */    cSPVector3 position;
	/* 10h */    float rotXDegrees;
	/* 14h */    float rotYDegrees;
	/* 1Ch */    float rotZDegrees;
	/* 20h */    uint64_t assetId;
	/* 28h */    float scale;
	/* 2Ch */    uint8_t team;
	/* 2Dh */    bool hasCollision;
	/* 2Eh */    bool playerControlled;

	void WriteTo(RakNet::BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x70);

		auto writeOffset = stream.GetWriteOffset();
		stream.AddBitsAndReallocate(size);

		stream.SetWriteOffset(writeOffset);
		Write(stream, noun);
		position.WriteTo(stream);
		Write(stream, rotXDegrees);
		Write(stream, rotYDegrees);
		Write(stream, rotZDegrees);
		Write(stream, assetId);
		Write(stream, scale);
		Write(stream, team);
		Write(stream, hasCollision);
		Write(stream, playerControlled);

		stream.SetWriteOffset(writeOffset + size);
	}

	void WriteReflection(RakNet::BitStream& stream) const {
		reflection::write<10>(stream, std::make_tuple(
			noun, position,
			rotXDegrees, rotYDegrees, rotZDegrees,
			assetId, scale, team,
			hasCollision, playerControlled
		));
	}
};

struct sporelabsObject {
	uint8_t mTeam;
	bool mbPlayerControlled;
	uint32_t mInputSyncStamp;
	uint8_t mPlayerIdx;
	cSPVector3 mLinearVelocity;
	cSPVector3 mAngularVelocity;
	cSPVector3 mPosition;
	cSPQuaternion mOrientation;
	float mScale;
	float mMarkerScale;
	uint32_t mLastAnimationState;
	uint64_t mLastAnimationPlayTimeMs;
	uint32_t mOverrideMoveIdleAnimationState;
	uint32_t mGraphicsState;
	uint64_t mGraphicsStateStartTimeMs;
	uint64_t mNewGraphicsStateStartTimeMs;
	bool mVisible;
	bool mbHasCollision;
	tObjID mOwnerID = utils::hash_id("none");
	uint8_t mMovementType;
	bool mDisableRepulsion;
	uint32_t mInteractableState;
	uint32_t sourceMarkerKey_markerId;

	sporelabsObject() {}
	sporelabsObject(cGameObjectCreateData data) :
		mTeam(data.team), mbPlayerControlled(data.playerControlled),
		mInputSyncStamp(0), mPlayerIdx(0),
		mLinearVelocity {}, mAngularVelocity {},
		mPosition(data.position), mOrientation {},
		mScale(data.scale), mMarkerScale(1.f),
		mLastAnimationState(0), mLastAnimationPlayTimeMs(0),
		mOverrideMoveIdleAnimationState(0),
		mGraphicsState(0), mGraphicsStateStartTimeMs(0),
		mNewGraphicsStateStartTimeMs(0),
		mVisible(true), mbHasCollision(data.hasCollision),
		mMovementType(0), mDisableRepulsion(false),
		mInteractableState(0), sourceMarkerKey_markerId(0) {}

	void WriteTo(RakNet::BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x308);

		auto writeOffset = stream.GetWriteOffset();
		stream.AddBitsAndReallocate(size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x010));
		Write(stream, mScale);
		Write(stream, mMarkerScale);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x018));
		mPosition.WriteTo(stream);
		mOrientation.WriteTo(stream);
		mLinearVelocity.WriteTo(stream);
		mAngularVelocity.WriteTo(stream);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x050));
		Write(stream, mOwnerID);
		Write(stream, mTeam);
		Write(stream, mPlayerIdx);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x058));
		Write(stream, mInputSyncStamp);
		Write(stream, mbPlayerControlled);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x05F));
		Write(stream, mVisible);
		Write(stream, mbHasCollision);
		Write(stream, mMovementType);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x088));
		Write(stream, sourceMarkerKey_markerId);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x0AC));
		Write(stream, mLastAnimationState);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x0B8));
		Write(stream, mLastAnimationPlayTimeMs);
		Write(stream, mOverrideMoveIdleAnimationState);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x258));
		Write(stream, mGraphicsState);
		Write(stream, mGraphicsStateStartTimeMs);
		Write(stream, mNewGraphicsStateStartTimeMs);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x284));
		Write(stream, mDisableRepulsion);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x288));
		Write(stream, mInteractableState);

		stream.SetWriteOffset(writeOffset + size);
	}

	void WriteReflection(RakNet::BitStream& stream) const {
		reflection::write<23>(stream, std::make_tuple(
			mTeam, mbPlayerControlled,
			mInputSyncStamp, mPlayerIdx,
			mLinearVelocity, mAngularVelocity,
			mPosition, mOrientation,
			mScale, mMarkerScale,
			mLastAnimationState, mLastAnimationPlayTimeMs,
			mOverrideMoveIdleAnimationState, mGraphicsState,
			mGraphicsStateStartTimeMs, mNewGraphicsStateStartTimeMs,
			mVisible, mbHasCollision,
			mOwnerID, mMovementType,
			mDisableRepulsion, mInteractableState,
			sourceMarkerKey_markerId
		));
	}
};

/*
	ServerEvent types (append .ServerEventDef)
		character_filter_exit_bio
		character_filter_exit_necro
		character_filter_exit_spacetime
		character_filter_exit_plasma_electric
		character_filter_exit_cyber
		character_filter_entry_bio
		character_filter_entry_necro
		character_filter_entry_spacetime
		character_filter_entry_plasma_electric
		character_filter_entry_cyber
		character_filter_character_holo_effect_locked
		character_filter_character_holo_effect
		character_filter_base_ring1_effect
		character_filter_base_ring2_effect
		character_lobby_swap_effect
		character_lobby_dias_glow_effect
		dna_pickup
		resurrect_orb_full
		resurrect_orb_pickup
		mana_orb_full
		mana_orb_pickup
		health_orb_full
		health_orb_pickup
		combattext_damage
		combattext_damage_critical
		combattext_enemy_damage
		combattext_enemy_damage_critical
		combattext_absorb
		combattext_absorb_critical
		combattext_enemy_absorb
		combattext_enemy_absorb_critical
		combattext_heal
		combattext_critical_heal
		life_healing_target_effect
		combattext_dodge
		combattext_deflect
		combattext_resist
		combattext_immune
		combattext_resurrected
		combattext_slowed
		combattext_stunned
		combattext_taunted
		combattext_suppressed
		combattext_rooted
		combattext_terrified
		combattext_banished
		common_death_regular_melee_effect_bio
		common_death_regular_melee_effect_cyber
		common_death_regular_melee_effect_necro
		common_death_regular_melee_effect_plasma
		common_death_regular_melee_effect_spacetime
		common_death_critical_melee_effect_bio
		common_death_critical_melee_effect_cyber
		common_death_critical_melee_effect_necro
		common_death_critical_melee_effect_plasma
		common_death_critical_melee_effect_spacetime
		common_death_regular_melee_effect_bio_noblood
		common_death_regular_melee_effect_cyber_noblood
		common_death_regular_melee_effect_necro_noblood
		common_death_regular_melee_effect_plasma_noblood
		common_death_regular_melee_effect_spacetime_noblood
		common_death_critical_melee_effect_bio_noblood
		common_death_critical_melee_effect_cyber_noblood
		common_death_critical_melee_effect_necro_noblood
		common_death_critical_melee_effect_plasma_noblood
		common_death_critical_melee_effect_spacetime_noblood
		common_death_critical_cyber_effect_bio
		common_death_critical_cyber_effect_cyber
		common_death_critical_cyber_effect_necro
		common_death_critical_cyber_effect_plasma
		common_death_critical_cyber_effect_spacetime
		common_death_critical_cyber_effect_bio_noblood
		common_death_critical_cyber_effect_cyber_noblood
		common_death_critical_cyber_effect_necro_noblood
		common_death_critical_cyber_effect_plasma_noblood
		common_death_critical_cyber_effect_spacetime_noblood
		common_death_critical_plasma_effect_bio
		common_death_critical_plasma_effect_cyber
		common_death_critical_plasma_effect_necro
		common_death_critical_plasma_effect_plasma
		common_death_critical_plasma_effect_spacetime
		common_death_critical_plasma_effect_bio_noblood
		common_death_critical_plasma_effect_cyber_noblood
		common_death_critical_plasma_effect_necro_noblood
		common_death_critical_plasma_effect_plasma_noblood
		common_death_critical_plasma_effect_spacetime_noblood
		common_death_critical_bio_effect_bio
		common_death_critical_bio_effect_cyber
		common_death_critical_bio_effect_necro
		common_death_critical_bio_effect_plasma
		common_death_critical_bio_effect_spacetime
		common_death_critical_bio_effect_bio_noblood
		common_death_critical_bio_effect_cyber_noblood
		common_death_critical_bio_effect_necro_noblood
		common_death_critical_bio_effect_plasma_noblood
		common_death_critical_bio_effect_spacetime_noblood
		common_death_critical_necro_effect_bio
		common_death_critical_necro_effect_cyber
		common_death_critical_necro_effect_necro
		common_death_critical_necro_effect_plasma
		common_death_critical_necro_effect_spacetime
		common_death_critical_necro_effect_bio_noblood
		common_death_critical_necro_effect_cyber_noblood
		common_death_critical_necro_effect_necro_noblood
		common_death_critical_necro_effect_plasma_noblood
		common_death_critical_necro_effect_spacetime_noblood
		common_death_critical_spacetime_effect_bio
		common_death_critical_spacetime_effect_cyber
		common_death_critical_spacetime_effect_necro
		common_death_critical_spacetime_effect_plasma
		common_death_critical_spacetime_effect_spacetime
		common_death_critical_spacetime_effect_bio_noblood
		common_death_critical_spacetime_effect_cyber_noblood
		common_death_critical_spacetime_effect_necro_noblood
		common_death_critical_spacetime_effect_plasma_noblood
		common_death_critical_spacetime_effect_spacetime_noblood
*/
struct ServerEvent {
	uint32_t simpleSwarmEffectID;
	uint8_t objectFxIndex;
	bool bRemove;
	bool bHardStop;
	bool bForceAttach;
	bool bCritical;
	uint32_t asset;
	tObjID objectId;
	tObjID secondaryObjectId;
	tObjID attackerId;
	cSPVector3 position;
	cSPVector3 facing;
	cSPQuaternion orientation;
	cSPVector3 targetPoint;
	int32_t textValue;
	uint32_t clientEventID;
	uint8_t clientIgnoreFlags;
	uint64_t lootReferenceId;
	uint64_t lootInstanceId;
	uint32_t lootRigblockId;
	uint32_t lootSuffixAssetId;
	uint32_t lootPrefixAssetId1;
	uint32_t lootPrefixAssetId2;
	int32_t lootItemLevel;
	int32_t lootRarity;
	uint64_t lootCreationTime;

	void WriteTo(RakNet::BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x98);

		auto writeOffset = stream.GetWriteOffset();
		stream.AddBitsAndReallocate(size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x04));
		Write(stream, simpleSwarmEffectID);
		Write(stream, objectFxIndex);
		Write(stream, bRemove);
		Write(stream, bHardStop);
		Write(stream, bForceAttach);
		Write(stream, bCritical);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x10));
		Write(stream, asset);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x18));
		Write(stream, objectId);
		Write(stream, secondaryObjectId);
		Write(stream, attackerId);
		position.WriteTo(stream);
		facing.WriteTo(stream);
		orientation.WriteTo(stream);
		targetPoint.WriteTo(stream);
		Write(stream, textValue);
		Write(stream, clientEventID);
		Write(stream, clientIgnoreFlags);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x68));
		Write(stream, lootReferenceId);
		Write(stream, lootInstanceId);
		Write(stream, lootRigblockId);
		Write(stream, lootSuffixAssetId);
		Write(stream, lootPrefixAssetId1);
		Write(stream, lootPrefixAssetId2);
		Write(stream, lootItemLevel);
		Write(stream, lootRarity);
		Write(stream, lootCreationTime);

		stream.SetWriteOffset(writeOffset + size);
	}

	void WriteReflection(RakNet::BitStream& stream) const {
		reflection::write<26>(stream, std::make_tuple(
			simpleSwarmEffectID,
			objectFxIndex,
			bRemove,
			bHardStop,
			bForceAttach,
			bCritical,
			asset,
			objectId,
			secondaryObjectId,
			attackerId,
			position,
			facing,
			orientation,
			targetPoint,
			textValue,
			clientEventID,
			clientIgnoreFlags,
			lootReferenceId,
			lootInstanceId,
			lootRigblockId,
			lootSuffixAssetId,
			lootPrefixAssetId1,
			lootPrefixAssetId2,
			lootItemLevel,
			lootRarity,
			lootCreationTime
		));
	}
};

// RakNet
namespace RakNet {
	enum GState : int32_t {
		Boot = 0,
		Login,
		Spaceship,
		Editor,
		PreDungeon,
		Dungeon,
		Observer,
		Cinematic,
		Spectator,
		ChainVoting,
		ChainCashOut,
		GameOver,
		Quit,
		ArenaLobby,
		ArenaRoundResults,
		JuggernautLobby,
		JuggernautResults,
		KillRaceLobby,
		KillRaceResults
	};

	enum class LuaGState : int32_t {
		Invalid = -1,
		Start = 0,
		Login,
		Spaceship,
		Editor,
		LevelEditor,
		PreDungeon,
		Dungeon,
		Observer,
		Cinematic,
		Replay,
		ChainVoting,
		ChainCashOut,
		GameOver,
		Quit,
		ArenaLobby,
		ArenaRoundResults,
		JuggernautLobby,
		JuggernautResults,
		KillRaceLobby,
		KillRaceResults
	};

	// Server
	Server::Server(uint16_t port, uint32_t gameId) : mGameId(gameId) {
		mThread = std::thread([this, port] {
			mSelf = RakNetworkFactory::GetRakPeerInterface();
			mSelf->SetTimeoutTime(30000, UNASSIGNED_SYSTEM_ADDRESS);
#ifdef PACKET_LOGGING
			mSelf->AttachPlugin(&mLogger);
#endif
			if (mSelf->Startup(4, 30, &SocketDescriptor(port, nullptr), 1)) {
				mSelf->SetMaximumIncomingConnections(4);
				mSelf->SetOccasionalPing(true);
				mSelf->SetUnreliableTimeout(1000);
				while (is_running()) {
					run_one();
					RakSleep(30);
				}
			}

			mSelf->Shutdown(300);
			RakNetworkFactory::DestroyRakPeerInterface(mSelf);
		});
	}

	Server::~Server() {
		stop();
	}

	void Server::stop() {
		mMutex.lock();
		mRunning = false;
		mMutex.unlock();
		if (mThread.joinable()) {
			mThread.join();
		}
	}

	bool Server::is_running() {
		std::lock_guard<std::mutex> lock(mMutex);
		return mRunning;
	}

	void Server::run_one() {
		const auto GetPacketIdentifier = [this]() -> MessageID {
			uint8_t message;
			if (mInStream.GetData()) {
				mInStream.Read<uint8_t>(message);
				if (message == ID_TIMESTAMP) {
					constexpr auto timestampSize = sizeof(MessageID) + sizeof(RakNetTime);
					RakAssert((mInStream.GetNumberOfUnreadBits() >> 3) > timestampSize);

					mInStream.IgnoreBytes(timestampSize - 1);
					mInStream.Read<uint8_t>(message);
				}
			} else {
				message = 0xFF;
			}
			return message;
		};

		for (Packet* packet = mSelf->Receive(); packet; mSelf->DeallocatePacket(packet), packet = mSelf->Receive()) {
			mInStream = BitStream(packet->data, packet->bitSize * 8, false);

			uint8_t packetType = GetPacketIdentifier();
			logger::warn("--- "  + std::to_string((int)packetType) + " gotten from raknet ---");
			switch (packetType) {
				case ID_DISCONNECTION_NOTIFICATION:    logger::warn("ID_DISCONNECTION_NOTIFICATION from " + std::string(packet->systemAddress.ToString(true))); break;
				case ID_NEW_INCOMING_CONNECTION:       OnNewIncomingConnection(packet); break;
				case ID_CONNECTION_REQUEST:            logger::warn("Trying to connect to RakNet"); break;
				case ID_INCOMPATIBLE_PROTOCOL_VERSION: logger::warn("ID_INCOMPATIBLE_PROTOCOL_VERSION"); break;
				case ID_CONNECTION_LOST:               logger::warn("ID_CONNECTION_LOST from " + std::string(packet->systemAddress.ToString(true))); break;
				case ID_SND_RECEIPT_ACKED:             break; // Packet was successfully accepted.
				case ID_SND_RECEIPT_LOSS:              break; // Packet was dropped. Add code to resend?
				case ID_USER_PACKET_ENUM:              OnHelloPlayer(packet); break;
				default: {
					ParsePacket(packet, packetType);
					break;
				}
			}
		}

		mInStream.Reset();
	}

	void Server::ParsePacket(Packet* packet, MessageID packetType) {
		switch (packetType) {
			case PacketID::HelloPlayer:        OnHelloPlayer(packet); break;
			case PacketID::PlayerStatusUpdate: OnPlayerStatusUpdate(packet); break;
			case PacketID::ActionCommandMsgs:  OnActionCommandMsgs(packet); break;
			case PacketID::DebugPing:          OnDebugPing(packet); break;
			default: {
				logger::error("Unknown packet id: " + static_cast<int32_t>(packetType));
				break;
			}
		}
	}

	void Server::OnNewIncomingConnection(Packet* packet) {
		SendConnected(packet);
	}

	void Server::OnHelloPlayer(Packet* packet) {
		SendHelloPlayer(packet);
		// if ok
		SendPlayerJoined(packet);
		// else
		// SendPlayerDeparted(packet);

		// SendTestPacket(packet, PacketID::ModifierDeleted, { 0x12, 0x34, 0x56, 0x78 });

		// Party is ok
		SendPartyMergeComplete(packet);
		
		// Send player stuff
		SendObjectCreate(packet, 0x0000000A, static_cast<uint32_t>(Game::CreatureTemplateID::BlitzAlpha));
		SendLabsPlayerUpdate(packet, true);
		
		// Prepare to start
		SendGamePrepareForStart(packet);
	}

	void Server::OnPlayerStatusUpdate(Packet* packet) {
		uint8_t value;
		mInStream.Read<uint8_t>(value);

		logger::info("Player Status Update: " + (int)value);

		switch (value) {
			case 2: {
				SendGameState(packet, GState::PreDungeon);
				break;
			}

			case 4: {
				// SendArenaGameMessages(packet);
				SendObjectivesInitForLevel(packet);
				SendPlayerDeparted(packet);
				break;
			}

			case 8: {
				SendGameState(packet, GState::Dungeon);
				SendGameStart(packet);

				SendPlayerCharacterDeploy(packet, 0x0000000A);
				break;
			}

			default:
				logger::error("Player Status Update: " + (int)value);
		}
	}

	void Server::OnActionCommandMsgs(Packet* packet) {
		std::cout << "OnActionCommandMsgs" << std::endl;
		std::cout << std::hex;

		uint32_t value;
		for (size_t i = 0; i < 16; ++i) {
			mInStream.Read<uint32_t>(value);
			for (size_t j = 0; j < 4; ++j) {
				std::cout << std::setw(2) << std::setfill('0') << static_cast<int>(reinterpret_cast<uint8_t*>(&value)[j]) << " ";
			}
		}
		std::cout << std::resetiosflags(0) << std::endl;
	}
	
	void Server::OnDebugPing(Packet* packet) {
		// Packet size: 0x08
		uint64_t time;
		mInStream.Read<uint64_t>(time);

		std::chrono::milliseconds ms(time);
		std::chrono::time_point<std::chrono::system_clock> debugTime(ms);

		auto debugTime_c = std::chrono::system_clock::to_time_t(debugTime);
		auto debugTime_c2 = std::ctime(&debugTime_c);
		if (debugTime_c2) {
			logger::info("Debug ping: " + std::string(debugTime_c2));
		} else {
			// TODO: That log sometimes causes an exception; investigate
			//logger::info("Debug ping: " + time);
			logger::info("Debug ping: ?");
		}
	}

	void Server::SendHelloPlayer(Packet* packet) {
		// Packet size: 0x08
		const auto& guid = mSelf->GetGuidFromSystemAddress(UNASSIGNED_SYSTEM_ADDRESS);

		auto addr = mSelf->GetSystemAddressFromGuid(guid);
		if (1) { // add check for local
			addr = SystemAddress("127.0.0.1", addr.port);
		}

		/*
			u8: type
			u8: gameIndex
			u32: ip
			u16: port
		*/

		BitStream outStream(8);
		outStream.Write(PacketID::HelloPlayer);
		outStream.Write<uint8_t>(0x01); // Player id?
		outStream.Write<uint8_t>(mGameId);
		outStream.WriteBits(reinterpret_cast<const uint8_t*>(&addr.binaryAddress), sizeof(addr.binaryAddress) * 8, true);
		outStream.Write(addr.port);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendConnected(Packet* packet) {
		// TODO: verify incoming connection

		BitStream outStream(8);
		outStream.Write(PacketID::Connected);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendPlayerJoined(Packet* packet) {
		// Packet size: 0x01
		BitStream outStream(8);
		outStream.Write(PacketID::PlayerJoined);
		outStream.Write<uint8_t>(mGameId);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendPlayerDeparted(Packet* packet) {
		// Packet size: 0x01
		BitStream outStream(8);
		outStream.Write(PacketID::PlayerDeparted);
		outStream.Write<uint8_t>(mGameId);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendPlayerStatusUpdate(Packet* packet, Blaze::PlayerState playerState) {
		BitStream outStream(8);
		outStream.Write(PacketID::PlayerStatusUpdate);
		outStream.Write<uint8_t>(static_cast<uint8_t>(playerState));

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendGameState(Packet* packet, uint32_t gameState) {
		// Packet size: 0x19
		BitStream outStream(8);
		outStream.Write(PacketID::GameState);

		Write<uint32_t>(outStream, gameState);
		Write<uint32_t>(outStream, 0x99);
		Write<uint32_t>(outStream, 0x82);
		Write<uint32_t>(outStream, 0x66);
		Write<uint32_t>(outStream, 0x31);
		Write<uint8_t>(outStream, 0x00);
		Write<uint32_t>(outStream, 0x52);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendLabsPlayerUpdate(Packet* packet, bool fullUpdate) {
		BitStream outStream(8);
		outStream.Write(PacketID::LabsPlayerUpdate);

		// Player ID?
		Write<uint8_t>(outStream, 0x01);
		Write<uint16_t>(outStream, fullUpdate ? 0x1000 : 0x0000);

		labsPlayer player;
		player.mPlayerOnlineId = 0x01;
		player.mbDataSetup = true;
		player.mAvatarLevel = 50;
		player.mAvatarXP = 0.5f;
		player.mCurrentDeckIndex = 100;
		player.mCurrentCreatureId = 10;
		player.mDNA = 98765;

		// Characters
		{
			auto& character = player.mCharacters[0];
			character.nounDef = static_cast<uint32_t>(Game::CreatureTemplateID::BlitzAlpha);
			character.version = 2;
		} {
			auto& character = player.mCharacters[1];
			character.nounDef = utils::hash_id("none");
			character.version = 0;
		} {
			auto& character = player.mCharacters[2];
			character.nounDef = utils::hash_id("none");
			character.version = 0;
		}

		// Crystals
		player.mCrystals[0] = labsCrystal(labsCrystal::Damage, 0, true);

		// write player
		player.WriteReflection(outStream);

		// write characters
		for (const auto& character : player.mCharacters) {
			character.WriteReflection(outStream);
		}

		// write crystals
		for (const auto& crystal : player.mCrystals) {
			crystal.WriteReflection(outStream);
		}

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendDirectorState(Packet* packet) {
		// Packet size: reflection(variable)
		BitStream outStream(8);
		outStream.Write(PacketID::DirectorState);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendPlayerCharacterDeploy(Packet* packet, uint32_t id) {
		/*
			0 : u8 (unk)
			1 : u8 (1-16)
			2 : u8 (unk)
			3 : u8 (unk)

			if [1] == 1 {
				0 : u8 (arg0 -> sub_4E21D0)
				4 : u32 (hash, default 'none', arg0 -> sub_9DFB40)
				8 : u32 (compared to 0?, var -> sub_9DFB40)

				16 : u32 (arg0 -> sub_9D7A00)
				20 : u32 (arg1 -> sub_9D7A00)

				24 : u32 (arg0 -> sub_9D7A00)
				28 : u32 (arg1 -> sub_9D7A00)

				32 : u32 (arg0 -> sub_9D7A00)
				36 : u32 (arg1 -> sub_9D7A00)

				40 : u32 (arg0 -> sub_9D7A00)
				44 : u32 (arg1 -> sub_9D7A00)

				52 : u32 (arg1 -> sub_4E21D0)
			}
		*/

		constexpr uint32_t hash_none = utils::hash_id("none");

		// Packet size: 0x09
		BitStream outStream(8);
		outStream.Write(PacketID::PlayerCharacterDeploy);

		Write<uint32_t>(outStream, static_cast<uint32_t>(Game::CreatureTemplateID::BlitzAlpha));
		Write<uint8_t>(outStream, 0x01);
		Write<uint32_t>(outStream, id);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendObjectCreate(Packet* packet, uint32_t id, uint32_t noun) {
		// Packet size: 0x04
		BitStream outStream(8);
		outStream.Write(PacketID::ObjectCreate);

		// set object id to 1?
		Write<uint32_t>(outStream, id);

		// reflection
		cGameObjectCreateData data;
			data.noun = noun;
			data.position = { 100.f, 100.f, 100.f };
			data.rotXDegrees = 0.f;
			data.rotYDegrees = 0.f;
			data.rotZDegrees = 0.f;
			data.assetId = 0;
			data.scale = 1.f;
			data.team = 0;
			data.hasCollision = true;
			data.playerControlled = true;
		data.WriteReflection(outStream);

		sporelabsObject sporeObject(data);
			sporeObject.mPlayerIdx = 0x01;
		sporeObject.WriteReflection(outStream);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendObjectUpdate(Packet* packet) {
		// Packet size: 0x04
		BitStream outStream(8);
		outStream.Write(PacketID::ObjectUpdate);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendObjectDelete(Packet* packet) {
		// Packet size: 0x04
		BitStream outStream(8);
		outStream.Write(PacketID::ObjectDelete);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendActionCommandResponse(Packet* packet) {
		// Packet size: 0x2C
		BitStream outStream(8);
		outStream.Write(PacketID::ActionCommandResponse);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendObjectPlayerMove(Packet* packet) {
		// Packet size: 0x20
		BitStream outStream(8);
		outStream.Write(PacketID::ObjectPlayerMove);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendObjectTeleport(Packet* packet) {
		// Packet size: 0x50
		BitStream outStream(8);
		outStream.Write(PacketID::ObjectTeleport);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendForcePhysicsUpdate(Packet* packet) {
		// Packet size: 0x28
		BitStream outStream(8);
		outStream.Write(PacketID::ForcePhysicsUpdate);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendPhysicsChanged(Packet* packet) {
		// Packet size: 0x05
		BitStream outStream(8);
		outStream.Write(PacketID::PhysicsChanged);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendLocomotionDataUpdate(Packet* packet) {
		// Packet size: 0x04
		BitStream outStream(8);
		outStream.Write(PacketID::LocomotionDataUpdate);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendLocomotionDataUnreliableUpdate(Packet* packet) {
		// Packet size: 0x10
		BitStream outStream(8);
		outStream.Write(PacketID::LocomotionDataUnreliableUpdate);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendAttributeDataUpdate(Packet* packet) {
		// Packet size: 0x04
		BitStream outStream(8);
		outStream.Write(PacketID::AttributeDataUpdate);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendCombatantDataUpdate(Packet* packet) {
		// Packet size: 0x04
		BitStream outStream(8);
		outStream.Write(PacketID::CombatantDataUpdate);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendInteractableDataUpdate(Packet* packet) {
		// Packet size: 0x04
		BitStream outStream(8);
		outStream.Write(PacketID::InteractableDataUpdate);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendAgentBlackboardUpdate(Packet* packet) {
		// Packet size: 0x04
		BitStream outStream(8);
		outStream.Write(PacketID::AgentBlackboardUpdate);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendLootDataUpdate(Packet* packet) {
		// Packet size: 0x04
		BitStream outStream(8);
		outStream.Write(PacketID::LootDataUpdate);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendServerEvent(Packet* packet) {
		// Packet size: variable
		BitStream outStream(8);
		outStream.Write(PacketID::ServerEvent);

		ServerEvent event;
		event.WriteReflection(outStream);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendModifierCreated(Packet* packet) {
		// Packet size: 0x15
		BitStream outStream(8);
		outStream.Write(PacketID::ModifierCreated);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendModifierUpdated(Packet* packet) {
		// Packet size: 0x08
		BitStream outStream(8);
		outStream.Write(PacketID::ModifierUpdated);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendModifierDeleted(Packet* packet) {
		// Packet size: 0x19
		BitStream outStream(8);
		outStream.Write(PacketID::ModifierDeleted);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendGamePrepareForStart(Packet* packet) {
		// C8AC4657 = zelems_1
		// 0xEEB4D1D9 = nocturna_1?
		// 0xA3ADE6F2 = tutorial v1
		// 0xEEB4D1D9 = tutorial v2
		// 0x3ABA8857 = unk

		// Packet size: 0x10
		BitStream outStream(8);
		outStream.Write(PacketID::GamePrepareForStart);

		Write<uint32_t>(outStream, utils::hash_id("Darkspore_Tutorial_cryos_1_v2.level"));
		Write<uint32_t>(outStream, utils::hash_id("Darkspore_Tutorial_cryos_1_v2_default.Markerset"));
		Write<uint32_t>(outStream, utils::hash_id("Darkspore_Tutorial_cryos_1_v2_default.Markerset"));

		// marker set for tutorial: 0xe6335cf5

		// level index? must be (>= 0 %% <= 72)
		Write<uint32_t>(outStream, 0x00000001);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendGameStart(Packet* packet) {
		// Packet size: 0x04
		BitStream outStream(8);
		outStream.Write(PacketID::GameStart);

		Write<uint32_t>(outStream, 0x00000001);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendArenaGameMessages(Packet* packet) {
		// Packet size: 0x04
		BitStream outStream(8);
		outStream.Write(PacketID::ArenaGameMsgs);

		Write<uint8_t>(outStream, 0x09);
		Write<float>(outStream, 1.25f);
		Write<uint16_t>(outStream, 0x0001);
		Write<uint16_t>(outStream, 0);
		Write<uint16_t>(outStream, 0x0001);
		Write<uint16_t>(outStream, 0);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendObjectivesInitForLevel(Packet* packet) {
		// Packet size: variable
		BitStream outStream(8);
		outStream.Write(PacketID::ObjectivesInitForLevel);

		uint8_t count = 0x01;
		Write<uint8_t>(outStream, count);

		for (uint8_t i = 0; i < count; ++i) {
			Write<uint32_t>(outStream, utils::hash_id("DontUseHealthObelisks"));

			Write<uint8_t>(outStream, 0x01);
			Write<uint8_t>(outStream, 0x01);
			Write<uint8_t>(outStream, 0x01);
			Write<uint8_t>(outStream, 0x01);

			std::string description = "Do some stuff bruh";

			size_t length = std::min<size_t>(0x30, description.length());
			size_t padding = 0x30 - length;

			for (size_t i = 0; i < length; ++i) {
				Write<char>(outStream, description[i]);
			}

			for (size_t i = 0; i < padding; ++i) {
				Write<char>(outStream, 0x00);
			}
		}

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendPartyMergeComplete(Packet* packet) {
		// Packet size: 0x08
		BitStream outStream(8);
		outStream.Write(PacketID::PartyMergeComplete);
		outStream.Write<uint64_t>(utils::get_unix_time());

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendDebugPing(Packet* packet) {
		// Packet size: 0x08
		BitStream outStream(8);
		outStream.Write(PacketID::DebugPing);
		outStream.Write<uint64_t>(utils::get_unix_time());

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendTutorial(Packet* packet) {
		BitStream outStream(8);
		outStream.Write(PacketID::TutorialGameMsgs);

		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}

	void Server::SendTestPacket(Packet* packet, MessageID id, const std::vector<uint8_t>& data) {
		BitStream outStream(8);
		outStream.Write(id);
		for (auto byte : data) {
			outStream.Write(byte);
		}
		mSelf->Send(&outStream, HIGH_PRIORITY, UNRELIABLE_WITH_ACK_RECEIPT, 0, packet->systemAddress, false);
	}
}
