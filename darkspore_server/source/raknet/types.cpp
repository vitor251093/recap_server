
// Include
#include "types.h"
#include "utils/functions.h"

#include <numbers>

// Campaign level order
constexpr std::array<std::string_view, 25> levelNames {
	// tutorial
	"Darkspore_Tutorial_cryos_1_v2",

	// 1-1 to 1-4
	"zelems_1",
	"zelems_3",
	"nocturna_4",
	"nocturna_1",

	// 2-1 to 2-4
	"verdanth_1",
	"verdanth_3",
	"zelems_2",
	"zelems_4",

	// 3-1 to 3-4
	"cryos_4",
	"cryos_3",
	"verdanth_2",
	"verdanth_4",

	// 4-1 to 4-4
	"infinity_2",
	"infinity_3",
	"cryos_1",
	"cryos_2",

	// 5-1 to 5-4
	"nocturna_3",
	"nocturna_2",
	"infinity_1",
	"infinity_4",

	// 6-1 to 6-4
	"scaldron_1",
	"scaldron_2",
	"scaldron_3",
	"scaldron_4"
};

// RakNet
namespace RakNet {
	// helpers
	BitSize_t ReallocateStream(RakNet::BitStream& stream, BitSize_t sizeInBits) {
		const auto writeOffset = stream.GetWriteOffset();
		if ((writeOffset & 7) > 0) {
			printf("ReallocateStream: not full bytes");
		}
		stream.AddBitsAndReallocate(sizeInBits);
		return writeOffset;
	}

	// to_string
	std::string to_string(PacketID type) {
		switch (type) {
			case PacketID::HelloPlayerRequest: return "HelloPlayerRequest";
			case PacketID::HelloPlayer: return "HelloPlayer";
			case PacketID::ReconnectPlayer: return "ReconnectPlayer";
			case PacketID::Connected: return "Connected";
			case PacketID::Goodbye: return "Goodbye";
			case PacketID::PlayerJoined: return "PlayerJoined";
			case PacketID::PartyMergeComplete: return "PartyMergeComplete";
			case PacketID::PlayerDeparted: return "PlayerDeparted";
			case PacketID::VoteKickStarted: return "VoteKickStarted";
			case PacketID::PlayerStatusUpdate: return "PlayerStatusUpdate";
			case PacketID::GameAborted: return "GameAborted";
			case PacketID::GameState: return "GameState";
			case PacketID::DirectorState: return "DirectorState";
			case PacketID::ObjectCreate: return "ObjectCreate";
			case PacketID::ObjectUpdate: return "ObjectUpdate";
			case PacketID::ObjectDelete: return "ObjectDelete";
			case PacketID::ObjectJump: return "ObjectJump";
			case PacketID::ObjectTeleport: return "ObjectTeleport";
			case PacketID::ObjectPlayerMove: return "ObjectPlayerMove";
			case PacketID::ForcePhysicsUpdate: return "ForcePhysicsUpdate";
			case PacketID::PhysicsChanged: return "PhysicsChanged";
			case PacketID::LocomotionDataUpdate: return "LocomotionDataUpdate";
			case PacketID::LocomotionDataUnreliableUpdate: return "LocomotionDataUnreliableUpdate";
			case PacketID::AttributeDataUpdate: return "AttributeDataUpdate";
			case PacketID::CombatantDataUpdate: return "CombatantDataUpdate";
			case PacketID::InteractableDataUpdate: return "InteractableDataUpdate";
			case PacketID::AgentBlackboardUpdate: return "AgentBlackboardUpdate";
			case PacketID::LootDataUpdate: return "LootDataUpdate";
			case PacketID::ServerEvent: return "ServerEvent";
			case PacketID::ActionCommandMsgs: return "ActionCommandMsgs";
			case PacketID::PlayerDamage: return "PlayerDamage";
			case PacketID::LootSpawned: return "LootSpawned";
			case PacketID::LootAcquired: return "LootAcquired";
			case PacketID::LabsPlayerUpdate: return "LabsPlayerUpdate";
			case PacketID::ModifierCreated: return "ModifierCreated";
			case PacketID::ModifierUpdated: return "ModifierUpdated";
			case PacketID::ModifierDeleted: return "ModifierDeleted";
			case PacketID::SetAnimationState: return "SetAnimationState";
			case PacketID::SetObjectGfxState: return "SetObjectGfxState";
			case PacketID::PlayerCharacterDeploy: return "PlayerCharacterDeploy";
			case PacketID::ActionCommandResponse: return "ActionCommandResponse";
			case PacketID::ChainVoteMsgs: return "ChainVoteMsgs";
			case PacketID::ChainLevelResultsMsgs: return "ChainLevelResultsMsgs";
			case PacketID::ChainCashOutMsgs: return "ChainCashOutMsgs";
			case PacketID::ChainPlayerMsgs: return "ChainPlayerMsgs";
			case PacketID::ChainGameMsgs: return "ChainGameMsgs";
			case PacketID::ChainGameOverMsgs: return "ChainGameOverMsgs";
			case PacketID::QuickGameMsgs: return "QuickGameMsgs";
			case PacketID::GamePrepareForStart: return "GamePrepareForStart";
			case PacketID::GameStart: return "GameStart";
			case PacketID::CheatMessageDontUseInReleaseButDontChangeTheIndexOfTheMessagesBelowInCaseWeAreRunningOnADevServer: return "CheatMessageDontUseInReleaseButDontChangeTheIndexOfTheMessagesBelowInCaseWeAreRunningOnADevServer";
			case PacketID::ArenaPlayerMsgs: return "ArenaPlayerMsgs";
			case PacketID::ArenaLobbyMsgs: return "ArenaLobbyMsgs";
			case PacketID::ArenaGameMsgs: return "ArenaGameMsgs";
			case PacketID::ArenaResultsMsgs: return "ArenaResultsMsgs";
			case PacketID::ObjectivesInitForLevel: return "ObjectivesInitForLevel";
			case PacketID::ObjectiveUpdated: return "ObjectiveUpdated";
			case PacketID::ObjectivesComplete: return "ObjectivesComplete";
			case PacketID::CombatEvent: return "CombatEvent";
			case PacketID::JuggernautPlayerMsgs: return "JuggernautPlayerMsgs";
			case PacketID::JuggernautLobbyMsgs: return "JuggernautLobbyMsgs";
			case PacketID::JuggernautGameMsgs: return "JuggernautGameMsgs";
			case PacketID::JuggernautResultsMsgs: return "JuggernautResultsMsgs";
			case PacketID::ReloadLevel: return "ReloadLevel";
			case PacketID::GravityForceUpdate: return "GravityForceUpdate";
			case PacketID::CooldownUpdate: return "CooldownUpdate";
			case PacketID::CrystalDragMessage: return "CrystalDragMessage";
			case PacketID::CrystalMessage: return "CrystalMessage";
			case PacketID::KillRacePlayerMsgs: return "KillRacePlayerMsgs";
			case PacketID::KillRaceLobbyMsgs: return "KillRaceLobbyMsgs";
			case PacketID::KillRaceGameMsgs: return "KillRaceGameMsgs";
			case PacketID::KillRaceResultsMsgs: return "KillRaceResultsMsgs";
			case PacketID::TutorialGameMsgs: return "TutorialGameMsgs";
			case PacketID::CinematicMsgs: return "CinematicMsgs";
			case PacketID::ObjectiveAdd: return "ObjectiveAdd";
			case PacketID::LootDropMessage: return "LootDropMessage";
			case PacketID::DebugPing: return "DebugPing";
		}
		return "unknown packet type";
	}

	// cAIDirector
	void cAIDirector::WriteTo(BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x4D0);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x00D));
		Write<bool>(stream, mbBossSpawned);
		Write<bool>(stream, mbBossHorde);
		Write<bool>(stream, mbCaptainSpawned);
		Write<bool>(stream, mbBossComplete);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x014));
		Write<tObjID>(stream, mBossId);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x47C));
		Write<int32_t>(stream, mActiveHordeWaves);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x48C));
		Write<bool>(stream, mbHordeSpawned);

		stream.SetWriteOffset(writeOffset + size);
	}

	void cAIDirector::WriteReflection(BitStream& stream) const {
		reflection_serializer<7> reflector(stream);
		reflector.begin();
		reflector.write<0>(mbBossSpawned);
		reflector.write<1>(mbBossHorde);
		reflector.write<2>(mbCaptainSpawned);
		reflector.write<3>(mbBossComplete);
		reflector.write<4>(mbHordeSpawned);
		reflector.write<5>(mBossId);
		reflector.write<6>(mActiveHordeWaves);
		reflector.end();
	}

	// labsCharacter
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

	// labsCrystal
	labsCrystal::labsCrystal(Type type, uint16_t rarity, bool prismatic) {
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

		crystalNoun = utils::hash_id(nounName + ".noun");
	}

	uint32_t labsCrystal::GetType() const {
		return 0;
	}

	void labsCrystal::WriteTo(BitStream& stream) const {
		Write<uint32_t>(stream, crystalNoun);
		Write<uint16_t>(stream, level);

		// padding?
		Write<uint32_t>(stream, 0x00);
		Write<uint32_t>(stream, 0x00);
		Write<uint16_t>(stream, 0x00);
	}

	void labsCrystal::WriteReflection(BitStream& stream) const {
		reflection_serializer<2> reflector(stream);
		reflector.begin();
		reflector.write<0>(crystalNoun);
		reflector.write<1>(level);
		reflector.end();
	}

	// cGameObjectCreateData
	void cGameObjectCreateData::WriteTo(BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x70);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset);
		Write(stream, noun);
		Write(stream, position);
		Write(stream, rotXDegrees);
		Write(stream, rotYDegrees);
		Write(stream, rotZDegrees);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x20));
		Write(stream, assetId);
		Write(stream, scale);
		Write(stream, team);
		Write(stream, hasCollision);
		Write(stream, playerControlled);

		stream.SetWriteOffset(writeOffset + size);
	}

	void cGameObjectCreateData::WriteReflection(BitStream& stream) const {
		reflection_serializer<10> reflector(stream);
		reflector.begin();
		reflector.write<0>(noun);
		reflector.write<1>(position);
		reflector.write<2>(rotXDegrees);
		reflector.write<3>(rotYDegrees);
		reflector.write<4>(rotZDegrees);
		reflector.write<5>(assetId);
		reflector.write<6>(scale);
		reflector.write<7>(team);
		reflector.write<8>(hasCollision);
		reflector.write<9>(playerControlled);
		reflector.end();
	}

	// sporelabsObject
	/*
		Extra data ([offset] = value)
			0x99 = mark cannot drop loot
			0x9A = mark not worth xp

			-- internal pointers --
			0x2C4 = attribute data (edited via attribute update packet)
			0x298 = locomotion data (edited via locomotion update packet(s))
			0x2CC = combatant data (edited via combatant update packet)
			0x2F0 = interactable data
			0x2B0 = agent blackboard data
			0x2E8 = loot data
			0x2EC = gravity force
			0x2C0 = team data?
	*/
	sporelabsObject::sporelabsObject() :
		mTeam(1), mbPlayerControlled(false),
		mInputSyncStamp(0), mPlayerIdx(0),
		mLinearVelocity(0, 0, 0), mAngularVelocity(0, 0, 0),
		mPosition(0, 0, 0), mOrientation {},
		mScale(1.f), mMarkerScale(1.f),
		mLastAnimationState(0), mLastAnimationPlayTimeMs(0),
		mOverrideMoveIdleAnimationState(0),
		mGraphicsState(0), mGraphicsStateStartTimeMs(0),
		mNewGraphicsStateStartTimeMs(0),
		mVisible(true), mbHasCollision(false),
		mMovementType(0), mDisableRepulsion(false),
		mInteractableState(0), sourceMarkerKey_markerId(0) {}

	void sporelabsObject::WriteTo(BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x308);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x010));
		Write<float>(stream, mScale);
		Write<float>(stream, mMarkerScale);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x018));
		Write(stream, mPosition);
		Write(stream, mOrientation);
		Write(stream, mLinearVelocity);
		Write(stream, mAngularVelocity);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x050));
		Write<tObjID>(stream, mOwnerID);
		Write<uint8_t>(stream, mTeam);
		Write<uint8_t>(stream, mPlayerIdx);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x058));
		Write<uint32_t>(stream, mInputSyncStamp);
		Write<bool>(stream, mbPlayerControlled);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x05F));
		Write<bool>(stream, mVisible);
		Write<bool>(stream, mbHasCollision);
		Write<uint8_t>(stream, mMovementType);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x088));
		Write(stream, sourceMarkerKey_markerId);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x0AC));
		Write(stream, mLastAnimationState);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x0B8));
		Write(stream, mLastAnimationPlayTimeMs);
		Write(stream, mOverrideMoveIdleAnimationState);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x258));
		Write(stream, mGraphicsState);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x260));
		Write(stream, mGraphicsStateStartTimeMs);
		Write(stream, mNewGraphicsStateStartTimeMs);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x284));
		Write(stream, mDisableRepulsion);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x288));
		Write(stream, mInteractableState);

		stream.SetWriteOffset(writeOffset + size);
	}

	void sporelabsObject::WriteReflection(BitStream& stream) const {
		reflection_serializer<23> reflector(stream);
		reflector.begin();
		reflector.write<0>(mTeam);
		reflector.write<1>(mbPlayerControlled);
		reflector.write<2>(mInputSyncStamp);
		reflector.write<3>(mPlayerIdx);
		reflector.write<4>(mLinearVelocity);
		reflector.write<5>(mAngularVelocity);
		reflector.write<6>(mPosition);
		reflector.write<7>(mOrientation);
		reflector.write<8>(mScale);
		reflector.write<9>(mMarkerScale);
		reflector.write<10>(mLastAnimationState);
		reflector.write<11>(mLastAnimationPlayTimeMs);
		reflector.write<12>(mOverrideMoveIdleAnimationState);
		reflector.write<13>(mGraphicsState);
		reflector.write<14>(mGraphicsStateStartTimeMs);
		reflector.write<15>(mNewGraphicsStateStartTimeMs);
		reflector.write<16>(mVisible);
		reflector.write<17>(mbHasCollision);
		reflector.write<18>(mOwnerID);
		reflector.write<19>(mMovementType);
		reflector.write<20>(mDisableRepulsion);
		reflector.write<21>(mInteractableState);
		reflector.write<22>(sourceMarkerKey_markerId);
		reflector.end();
	}

	// cAgentBlackboard
	void cAgentBlackboard::WriteTo(BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x598);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x550));
		Write(stream, targetId);
		Write(stream, mbInCombat);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x556));
		Write(stream, mStealthType);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x578));
		Write(stream, mbTargetable);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x57C));
		Write(stream, mNumAttackers);

		stream.SetWriteOffset(writeOffset + size);
	}

	void cAgentBlackboard::WriteReflection(BitStream& stream) const {
		reflection_serializer<5> reflector(stream);
		reflector.begin();
		reflector.write<0>(targetId);
		reflector.write<1>(mbInCombat);
		reflector.write<2>(mStealthType);
		reflector.write<3>(mbTargetable);
		reflector.write<4>(mNumAttackers);
		reflector.end();
	}

	// cLobParams
	void cLobParams::WriteTo(BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x54);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x18));
		Write(stream, lobUpDir);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x30));
		Write(stream, bounceNum);
		Write(stream, bounceRestitution);
		Write(stream, groundCollisionOnly);
		Write(stream, stopBounceOnCreatures);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x3C));
		Write(stream, planeDir);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x48));
		Write(stream, planeDirLinearParam);
		Write(stream, upLinearParam);
		Write(stream, upQuadraticParam);

		stream.SetWriteOffset(writeOffset + size);
	}

	void cLobParams::WriteReflection(BitStream& stream) const {
		reflection_serializer<9> reflector(stream);
		reflector.begin();
		reflector.write<0>(planeDirLinearParam);
		reflector.write<1>(upLinearParam);
		reflector.write<2>(upQuadraticParam);
		reflector.write<3>(lobUpDir);
		reflector.write<4>(planeDir);
		reflector.write<5>(bounceNum);
		reflector.write<6>(bounceRestitution);
		reflector.write<7>(groundCollisionOnly);
		reflector.write<8>(stopBounceOnCreatures);
		reflector.end();
	}

	// cProjectileParams
	void cProjectileParams::WriteTo(BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x3C);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset);
		Write(stream, mSpeed);
		Write(stream, mAcceleration);
		Write(stream, mJinkInfo);
		Write(stream, mRange);
		Write(stream, mSpinRate);
		Write(stream, mDirection);
		Write(stream, mProjectileFlags);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x24));
		Write(stream, mHomingDelay);
		Write(stream, mTurnRate);
		Write(stream, mTurnAcceleration);
		Write(stream, mPiercing);
		Write(stream, mIgnoreGroundCollide);
		Write(stream, mIgnoreCreatureCollide);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x34));
		Write(stream, mEccentricity);
		Write(stream, mCombatantSweepHeight);

		stream.SetWriteOffset(writeOffset + size);
	}

	void cProjectileParams::WriteReflection(BitStream& stream) const {
		reflection_serializer<15> reflector(stream);
		reflector.begin();
		reflector.write<0>(mSpeed);
		reflector.write<1>(mAcceleration);
		reflector.write<2>(mJinkInfo);
		reflector.write<3>(mRange);
		reflector.write<4>(mSpinRate);
		reflector.write<5>(mDirection);
		reflector.write<6>(mProjectileFlags);
		reflector.write<7>(mHomingDelay);
		reflector.write<8>(mTurnRate);
		reflector.write<9>(mTurnAcceleration);
		reflector.write<10>(mEccentricity);
		reflector.write<11>(mPiercing);
		reflector.write<12>(mIgnoreGroundCollide);
		reflector.write<13>(mIgnoreCreatureCollide);
		reflector.write<14>(mCombatantSweepHeight);
		reflector.end();
	}

	// LocomotionData
	void LocomotionData::SetGoalPosition(const glm::vec3& position) {
		constexpr auto vec3_zero = glm::zero<glm::vec3>();

		// reset data
		mTargetObjectId = 0;
		mFacing = vec3_zero;
		mTargetPosition = vec3_zero;
		mExternalLinearVelocity = vec3_zero;

		// set data
		mGoalFlags = 0x001;
		mGoalPosition = position;
		mAllowedStopDistance = 0;
		mDesiredStopDistance = 0;
	}

	void LocomotionData::SetGoalPositionWithDistance(const glm::vec3& position, float distance) {
		SetGoalPosition(position);

		mAllowedStopDistance = distance;
		mDesiredStopDistance = distance;
	}
	/*
	void LocomotionData::SetGoalObject(const Game::ObjectPtr& object, float distance) {
		if (!object) {
			return;
		}

		// distance = GetAllowedStoppingDistance(object) + distance;
		SetGoalPosition(data, object->GetPosition());

		// mGoalFlags |= (1 & 0x40);
		// mGoalFlags |= (2 & 0x80);

		mAllowedStopDistance = distance;
		mDesiredStopDistance = distance;
	}
	
	void LocomotionData::SetGoalObjectEx(const Game::ObjectPtr& object, float distance) {
		constexpr auto vec3_zero = glm::zero<glm::vec3>();
		if (!object) {
			return;
		}

		// reset data
		mTargetObjectId = 0;
		mFacing = vec3_zero;
		mTargetPosition = vec3_zero;
		mExternalLinearVelocity = vec3_zero;

		// set data
		mGoalFlags = 0x400;
		// mGoalFlags = 1 & 0x040;
		mTargetObjectId = object->GetId();
		mGoalPosition = object->GetPosition();
		mAllowedStopDistance = distance;
		mDesiredStopDistance = distance;
	}
	*/
	void LocomotionData::Stop() {
		constexpr auto vec3_zero = glm::zero<glm::vec3>();

		// reset data
		mTargetObjectId = 0;
		mFacing = vec3_zero;

		// set data
		mGoalFlags = 0x020;
	}
	/*
	void LocomotionData::MoveToPointWhileFacingTarget(const glm::vec3& position, const Game::ObjectPtr& object) {
		constexpr auto vec3_zero = glm::zero<glm::vec3>();
		if (!object) {
			return;
		}

		// reset data
		mFacing = vec3_zero;
		mTargetPosition = vec3_zero;
		mExternalLinearVelocity = vec3_zero;

		// set data
		mGoalFlags = 0x001 | 0x100;
		mGoalPosition = position;
		mTargetObjectId = object->GetId();
		mAllowedStopDistance = 0;
		mDesiredStopDistance = 0;

		// extra_func(0x100);
	}
	*/
	void LocomotionData::ApplyExternalVelocity(const glm::vec3& velocity) {
		constexpr auto vec3_zero = glm::zero<glm::vec3>();

		// reset data
		mTargetObjectId = 0;
		mFacing = vec3_zero;

		// set data
		mGoalFlags = 0x008;
		mExternalLinearVelocity = velocity;
	}

	void LocomotionData::ClearExternalVelocity(const glm::vec3& velocity) {
		// set data
		mGoalFlags = 0x020;
		mExternalLinearVelocity = glm::zero<glm::vec3>();
	}

	void LocomotionData::WriteTo(BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x290);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x08));
		Write(stream, reflectedLastUpdate);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x44));
		mProjectileParams.WriteTo(stream);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x84));
		Write(stream, mExpectedGeoCollision);
		Write(stream, mTargetObjectId);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x9C));
		Write(stream, mInitialDirection);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0xD8));
		Write(stream, lobStartTime);
		Write(stream, lobPrevSpeedModifier);
		lobParams.WriteTo(stream);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x138));
		Write(stream, mOffset);
		Write(stream, mGoalFlags);
		Write(stream, mGoalPosition);
		Write(stream, mPartialGoalPosition);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x178));
		Write(stream, mFacing);
		Write(stream, mExternalLinearVelocity);
		Write(stream, mExternalForce);
		Write(stream, mAllowedStopDistance);
		Write(stream, mDesiredStopDistance);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1AC));
		Write(stream, mTargetPosition);

		stream.SetWriteOffset(writeOffset + size);
	}

	void LocomotionData::WriteReflection(BitStream& stream) const {
		reflection_serializer<18> reflector(stream);
		reflector.begin();
		reflector.write<0>(lobStartTime);
		reflector.write<1>(lobPrevSpeedModifier);
		reflector.write<2>(lobParams);
		reflector.write<3>(mProjectileParams);
		reflector.write<4>(mGoalFlags);
		reflector.write<5>(mGoalPosition);
		reflector.write<6>(mPartialGoalPosition);
		reflector.write<7>(mFacing);
		reflector.write<8>(mExternalLinearVelocity);
		reflector.write<9>(mExternalForce);
		reflector.write<10>(mAllowedStopDistance);
		reflector.write<11>(mDesiredStopDistance);
		reflector.write<12>(mTargetObjectId);
		reflector.write<13>(mTargetPosition);
		reflector.write<14>(mExpectedGeoCollision);
		reflector.write<15>(mInitialDirection);
		reflector.write<16>(mOffset);
		reflector.write<17>(reflectedLastUpdate);
		reflector.end();
	}

	// cCombatantData
	void cCombatantData::WriteTo(BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x70);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x40));
		Write(stream, mHitPoints);
		Write(stream, mManaPoints);

		stream.SetWriteOffset(writeOffset + size);
	}

	void cCombatantData::WriteReflection(BitStream& stream) const {
		reflection_serializer<2> reflector(stream);
		reflector.begin();
		reflector.write<0>(mHitPoints);
		reflector.write<1>(mManaPoints);
		reflector.end();
	}

	// cInteractableData
	void cInteractableData::WriteTo(BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x34);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x08));
		Write(stream, mNumTimesUsed);
		Write(stream, mNumUsesAllowed);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x14));
		Write(stream, mInteractableAbility);

		stream.SetWriteOffset(writeOffset + size);
	}

	void cInteractableData::WriteReflection(BitStream& stream) const {
		reflection_serializer<3> reflector(stream);
		reflector.begin();
		reflector.write<0>(mNumTimesUsed);
		reflector.write<1>(mNumUsesAllowed);
		reflector.write<2>(mInteractableAbility);
		reflector.end();
	}

	// cLootData
	void cLootData::WriteTo(BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x80);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x08));
		Write(stream, crystalLevel);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x10));
		Write(stream, mId);
		Write(stream, mRigblockAsset);
		Write(stream, mSuffixAssetId);
		Write(stream, mPrefixAssetId1);
		Write(stream, mPrefixAssetId2);
		Write(stream, mItemLevel);
		Write(stream, mRarity);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x40));
		Write(stream, mLootInstanceId);
		Write(stream, mDNAAmount);

		stream.SetWriteOffset(writeOffset + size);
	}

	void cLootData::WriteReflection(BitStream& stream) const {
		reflection_serializer<10> reflector(stream);
		reflector.begin();
		reflector.write<0>(crystalLevel);
		reflector.write<1>(mId);
		reflector.write<2>(mRigblockAsset);
		reflector.write<3>(mSuffixAssetId);
		reflector.write<4>(mPrefixAssetId1);
		reflector.write<5>(mPrefixAssetId2);
		reflector.write<6>(mItemLevel);
		reflector.write<7>(mRarity);
		reflector.write<8>(mLootInstanceId);
		reflector.write<9>(mDNAAmount);
		reflector.end();
	}

	// GravityForce
	void GravityForce::WriteTo(BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x20);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x08));
		Write(stream, radius);
		Write(stream, force);
		Write(stream, forceForMover);

		stream.SetWriteOffset(writeOffset + size);
	}

	void GravityForce::WriteReflection(BitStream& stream) const {
		reflection_serializer<3> reflector(stream);
		reflector.begin();
		reflector.write<0>(radius);
		reflector.write<1>(force);
		reflector.write<2>(forceForMover);
		reflector.end();
	}

	// CombatEvent
	void CombatEvent::WriteTo(BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x28);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset);
		Write(stream, flags);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x04));
		Write(stream, deltaHealth);
		Write(stream, absorbedAmount);
		Write(stream, targetID);
		Write(stream, sourceID);
		Write(stream, abilityID);
		Write(stream, damageDirection);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x24));
		Write(stream, integerHpChange);

		stream.SetWriteOffset(writeOffset + size);
	}

	void CombatEvent::WriteReflection(BitStream& stream) const {
		reflection_serializer<8> reflector(stream);
		reflector.begin();
		reflector.write<0>(flags);
		reflector.write<1>(deltaHealth);
		reflector.write<2>(absorbedAmount);
		reflector.write<3>(targetID);
		reflector.write<4>(sourceID);
		reflector.write<5>(abilityID);
		reflector.write<6>(damageDirection);
		reflector.write<7>(integerHpChange);
		reflector.end();
	}

	// DifficultyTuning
	void DifficultyTuning::WriteTo(BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x48);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x00));
		Write<float>(stream, HealthPercentIncrease[0]);
		Write<float>(stream, HealthPercentIncrease[1]);

		Write<float>(stream, DamagePercentIncrease[0]);
		Write<float>(stream, DamagePercentIncrease[1]);

		Write<float>(stream, ItemLevelRange[0]);
		Write<float>(stream, ItemLevelRange[1]);

		Write(stream, GearScoreRange);
		Write(stream, GearScoreMax);

		Write<int32_t>(stream, ExpectedAvatarLevel[0]);
		Write<int32_t>(stream, ExpectedAvatarLevel[1]);

		Write<float>(stream, RatingConversion[0]);
		Write<float>(stream, RatingConversion[1]);

		Write<float>(stream, StarModeHealthMult);
		Write<float>(stream, StarModeDamageMult);
		Write<float>(stream, StarModeEliteChanceAdd);
		Write<float>(stream, StarModeSuggestedLevelAdd);

		stream.SetWriteOffset(writeOffset + size);
	}

	void DifficultyTuning::WriteReflection(BitStream& stream) const {
		reflection_serializer<11> reflector(stream);
		reflector.begin();
		reflector.write<0>(HealthPercentIncrease);
		reflector.write<1>(DamagePercentIncrease);
		reflector.write<2>(ItemLevelRange);
		reflector.write<3>(GearScoreRange);
		reflector.write<4>(GearScoreMax);
		reflector.write<5>(ExpectedAvatarLevel);
		reflector.write<6>(RatingConversion);
		reflector.write<7>(StarModeHealthMult);
		reflector.write<8>(StarModeDamageMult);
		reflector.write<9>(StarModeEliteChanceAdd);
		reflector.write<10>(StarModeSuggestedLevelAdd);
		reflector.end();
	}

	// PlanetData
	void PlanetData::WriteTo(BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x19);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x00));

		Write<uint32_t>(stream, kills);
		Write<uint32_t>(stream, unk);

		Write<float>(stream, damageDealt);
		Write<float>(stream, damageTaken);
		Write<float>(stream, healingDone);
		Write<float>(stream, healingReceived);

		Write<uint8_t>(stream, playerIndex);

		stream.SetWriteOffset(writeOffset + size);
	}

	// ChainVoteData
	ChainVoteData::ChainVoteData() {
		// 1-1
		mEnemyNouns[0] = utils::hash_id("VerdanthBasicMelee.Noun");
		mEnemyNouns[1] = utils::hash_id("ZelemBasicHybrid.Noun");
		mEnemyNouns[2] = utils::hash_id("ZelemBasicPackMelee.Noun");
		mEnemyNouns[3] = utils::hash_id("ZelemBasicRangedHoming.Noun");
		mEnemyNouns[4] = utils::hash_id("ZelemBasicFlyingMelee.Noun");
		mEnemyNouns[5] = utils::hash_id("NomadSnipe.Noun");

		mLevelNouns[0] = utils::hash_id("ZelemBoss.Noun");
		mLevelNouns[1] = utils::hash_id("NomadSpacetimeAgent.Noun");
	}

	float ChainVoteData::GetTimeRemaining() const {
		return mTimeRemaining;
	}

	void ChainVoteData::SetTimeRemaining(float milliseconds) {
		mTimeRemaining = milliseconds;
	}

	std::string ChainVoteData::GetDifficultyName() const {
		if (GetLevelIndex() == 0) {
			return "tutorial";
		}
		return std::to_string(GetMajorDifficulty()) + "-" + std::to_string(GetMinorDifficulty());
	}

	std::string_view ChainVoteData::GetName() const {
		return levelNames[mLevelIndex];
	}

	uint32_t ChainVoteData::GetLevel() const {
		return mLevel;
	}

	void ChainVoteData::SetLevel(uint32_t level) {
		mLevel = level;
		mLevelIndex = 0;
	}

	uint8_t ChainVoteData::GetProgression() const {
		return mProgression;
	}

	void ChainVoteData::SetProgression(uint8_t progression) {
		// Client limit of 5 planets in 1 run
		mProgression = std::min<uint8_t>(5, progression);
	}

	uint32_t ChainVoteData::GetLevelIndex() const {
		return mLevelIndex;
	}

	void ChainVoteData::SetLevelByIndex(uint32_t index) {
		if (index < levelNames.size()) {
			mLevelIndex = index;
			mLevel = utils::hash_id(GetName().data() + std::string(".Level"));
		}
	}

	void ChainVoteData::SetLevelInstance(uint32_t index) {
		mLevelIndex = index;
	}

	uint32_t ChainVoteData::GetMarkerSet() const {
		std::string markerSet = "levelshop";
		markerSet = "ai_1";

		std::string levelName = GetName().data();
		levelName += "_" + markerSet + ".Markerset";
		return utils::hash_id(levelName);
	}

	uint32_t ChainVoteData::GetMinorDifficulty() const {
		return ((mLevelIndex - 1) % 4) + 1;
	}

	uint32_t ChainVoteData::GetMajorDifficulty() const {
		return ((mLevelIndex - 1) / 4) + 1;
	}

	uint32_t ChainVoteData::GetStarLevel() const {
		return mStarLevel;
	}

	void ChainVoteData::SetStarLevel(uint32_t starLevel) {
		mStarLevel = starLevel;
	}

	bool ChainVoteData::IsCompleted() const {
		return mCompletedLevel;
	}

	void ChainVoteData::SetCompleted(bool completed) {
		mCompletedLevel = completed;
	}

	uint32_t ChainVoteData::GetEnemyNoun(uint32_t index) const {
		if (index < mEnemyNouns.size()) {
			return mEnemyNouns[index];
		}
		return 0;
	}

	void ChainVoteData::SetEnemyNoun(std::string_view nounStr, uint32_t index) {
		if (index < mEnemyNouns.size()) {
			mEnemyNouns[index] = utils::hash_id(nounStr);
		}
	}

	void ChainVoteData::WriteTo(RakNet::BitStream& stream) const {
		// This data is set directly into the state machine?

		/*
			0x00 - 0x13 = memcpy'd in client ()
			0x4D - 0x8E = memcpy'd in client (Maybe DifficultyTuning)
		*/

		/*
			Player progress
				6500 = start mission
				6800 = on chainvote data sent?
		*/

		constexpr auto size = bytes_to_bits(0x151);

		uint32_t minorDifficulty;
		uint32_t majorDifficulty;
		if (mLevelIndex > 0) {
			minorDifficulty = GetMinorDifficulty();
			majorDifficulty = GetMajorDifficulty();
		} else {
			minorDifficulty = 0;
			majorDifficulty = 0;
		}

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x00));
		if (mCompletedLevel) {
			// this is different somehow.
			Write<uint32_t>(stream, minorDifficulty);
			Write<uint32_t>(stream, majorDifficulty);
			Write<float>(stream, 15 * 60 * 1000.f); // time completed?
			Write<float>(stream, 30 * 60 * 1000.f); // time remaining?
		} else {
			Write<uint32_t>(stream, mLevel);
			Write<uint32_t>(stream, mLevelIndex);
			Write<uint32_t>(stream, mStarLevel);
			Write<float>(stream, 30 * 60 * 1000.f); // time remaining?
		}

		// progression (max 5?)
		Write<uint8_t>(stream, mProgression);

		// enemy data
		for (const auto enemy : mEnemyNouns) {
			Write<uint32_t>(stream, enemy);
		}

		// TODO: understand this. (same function tests these as the enemy nouns)
		for (const auto data : mLevelNouns) {
			Write<uint32_t>(stream, data);
		}
		
		if (mCompletedLevel) {
			Write<uint32_t>(stream, 4); // 1
			Write<uint32_t>(stream, 3); // 2
		}

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x39));
		Write<uint32_t>(stream, 0); // party value?, used in sub_5313B0
		Write<uint32_t>(stream, utils::hash_id("fmv_02_zelems.vp6")); // some value
		Write<uint32_t>(stream, utils::hash_id("fmv_02_zelems.vp6")); // some value

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x45));
		Write<uint32_t>(stream, utils::hash_id("vo_ship_flow_reinfect_zelems")); // voiceover clip
		Write<uint32_t>(stream, 0); // tests against "mCompletedLevel" for something, but this is not a boolean.

		if (mCompletedLevel) {
			stream.SetWriteOffset(writeOffset + bytes_to_bits(0x4D));
			Write<uint32_t>(stream, 0);
			Write<uint32_t>(stream, mLevelIndex);

			// DNA
			for (int i = 0; i < 4; ++i) {
				Write<uint32_t>(stream, 30 + i * 30);
			}

			// ?
			for (int i = 0; i < 4; ++i) {
				Write<uint32_t>(stream, 40 + i * 40);
			}
#if 0
			stream.SetWriteOffset(writeOffset + bytes_to_bits(0x76));
			for (const auto& data : mChainSummary) {
				data.WriteTo(stream);
			}
#else
			for (int i = 0; i < 4; ++i) {
				stream.SetWriteOffset(writeOffset + bytes_to_bits((i * 0x19) + 0x76));
				Write<uint32_t>(stream, 10 + i * 10); // pve kills
				Write<uint32_t>(stream, 5); // unknown

				Write<float>(stream, 15); // damage dealt
				Write<float>(stream, 10); // damage taken

				Write<float>(stream, 25); // healing done
				Write<float>(stream, 5); // healing received

				Write<uint8_t>(stream, i);
			}
#endif
		}

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0xD9));
		Write<uint32_t>(stream, 0); // overrides party value
		Write<uint32_t>(stream, utils::hash_id("fmv_03_nocturna.vp6")); // ignored?
		Write<uint32_t>(stream, utils::hash_id("fmv_03_nocturna.vp6")); // ignored?

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0xE9));
		Write<uint32_t>(stream, mLevel); // some hash, finds text in labsplanet.locale

		/*
		auto writeDebugData = [](auto& stream, size_t length) {
			constexpr std::array<uint8_t, 8> bytes { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
			constexpr size_t bytesMask = bytes.size() - 1;
			for (size_t i = 0; i < length; ++i) {
				Write<uint8_t>(stream, bytes[i & bytesMask]);
			}
		};
		writeDebugData(stream, 0x68);
		*/

		// Previous planet stuff
		if (mCompletedLevel) {
#if 0
			stream.SetWriteOffset(writeOffset + bytes_to_bits(0xEE));
			for (const auto& data : mPlanetData) {
				data.WriteTo(stream);
			}
#else
			for (int i = 0; i < 4; ++i) {
				stream.SetWriteOffset(writeOffset + bytes_to_bits((i * 0x19) + 0xEE));
				Write<uint32_t>(stream, 10 + i * 10); // pve kills
				Write<uint32_t>(stream, 5); // unknown

				Write<float>(stream, 125); // damage dealt
				Write<float>(stream, 1231); // damage taken

				Write<float>(stream, 515151); // healing done
				Write<float>(stream, 23123); // healing received

				Write<uint8_t>(stream, i);
			}
#endif
		}

		Write<uint32_t>(stream, 10);
		Write<uint32_t>(stream, 20);
		Write<uint32_t>(stream, 30);
		Write<uint32_t>(stream, 40);
		Write<uint32_t>(stream, 50);
		Write<uint32_t>(stream, 60);

		stream.SetWriteOffset(writeOffset + size);
	}

	// Objective
	void Objective::WriteTo(RakNet::BitStream& stream) const {
		constexpr size_t maxDescriptionLength = 0x30;
		constexpr size_t objectiveSize = sizeof(uint32_t) + sizeof(uint32_t) + maxDescriptionLength;

		const auto writeOffset = ReallocateStream(stream, objectiveSize);

		stream.SetWriteOffset(writeOffset);
		Write<uint32_t>(stream, id);
		Write<uint32_t>(stream, value);

		auto writeDebugData = [](auto& stream, size_t length) {
			constexpr std::array<uint8_t, 8> bytes { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
			constexpr size_t bytesMask = bytes.size() - 1;
			for (size_t i = 0; i < length; ++i) {
				Write<uint8_t>(stream, bytes[i & bytesMask]);
			}
		};
		writeDebugData(stream, 0x40);
		/*
		size_t length = std::min<size_t>(maxDescriptionLength, description.length());
		size_t padding = maxDescriptionLength - length;

		for (size_t i = 0; i < length; ++i) { Write<char>(stream, description[i]); }
		for (size_t i = 0; i < padding; ++i) { Write<char>(stream, 0x00); }
		*/
		stream.SetWriteOffset(writeOffset + objectiveSize);
	}
}
