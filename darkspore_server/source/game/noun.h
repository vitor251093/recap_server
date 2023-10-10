
#ifndef _GAME_NOUN_HEADER
#define _GAME_NOUN_HEADER

// Include
#include "collision.h"
#include "utils/functions.h"

#include <array>
#include <memory>
#include <map>
#include <unordered_map>
#include <utility>

// Game
namespace Game {
	using AnimationData = std::tuple<uint32_t, float>;

	// DoorState
	enum class DoorState : uint8_t {
		Open = 0,
		Closed = 2
	};

	// DoorData
	class DoorData {
		public:
			void Read(pugi::xml_node node);

		private:
			DoorState mInitialState { DoorState::Open };

			bool mClickToOpen { false };
			bool mClickToClose { false };
	};

	// SwitchData
	class SwitchData {
		public:
			void Read(pugi::xml_node node);
	};

	// PressureSwitchData
	class PressureSwitchData {
		public:
			void Read(pugi::xml_node node);

		private:
			BoundingShape mShape {};
	};

	// CollisionShape
	enum class CollisionShape : uint8_t {
		Sphere = 0,
		Box
	};

	// CollisionVolume
	class CollisionVolume {
		public:
			void Read(pugi::xml_node node);

			const glm::vec3& GetBoxExtents() const;
			float GetSphereRadius() const;
			CollisionShape GetShape() const;

		private:
			glm::vec3 mBoxExtents {};

			float mSphereRadius = 0;

			CollisionShape mShape = CollisionShape::Sphere;
	};

	// TargetType
	enum class TargetType : uint32_t {
		Enemies = 0,
		Allies,
		Any,
		None
	};

	// ProjectileData
	class ProjectileData {
		public:
			void Read(pugi::xml_node node);

			const std::unique_ptr<CollisionVolume>& GetCreatureCollisionVolume() const;
			const std::unique_ptr<CollisionVolume>& GetOtherCollisionVolume() const;
			TargetType GetTargetType() const;

		private:
			std::unique_ptr<CollisionVolume> mCreatureCollisionVolume;
			std::unique_ptr<CollisionVolume> mOtherCollisionVolume;

			TargetType mTargetType = TargetType::Enemies;
	};

	// OrbitData
	class OrbitData {
		public:
			void Read(pugi::xml_node node);

			float GetHeight() const;
			float GetRadius() const;
			float GetSpeed() const;

		private:
			float mHeight = 0;
			float mRadius = 0;
			float mSpeed = 0;
	};

	// ClassAttribute
	namespace ClassAttribute {
		enum Key {
			Health = 0,
			Mana,
			Strength,
			Dexterity,
			Mind,
			PhysicalDefense,
			MagicalDefense,
			EnergyDefense,
			Critical,
			CombatSpeed,
			NonCombatSpeed,
			StealthDetection,
			MovementSpeedBuff,

			BaseCount,
			MaxCount = 9
		};
	}

	// ClassAttributes
	class ClassAttributes {
		public:
			void Read(pugi::xml_node node);

			float GetBaseAttribute(ClassAttribute::Key key) const;
			float GetMaxAttribute(ClassAttribute::Key key) const;

		private:
			std::array<float, ClassAttribute::BaseCount> mBaseAttributes { 0 };
			std::array<float, ClassAttribute::MaxCount> mMaxAttributes { 0 };

			std::string mPath;

			uint32_t mId = 0;

			friend class NounDatabase;
	};

	// NpcType
	enum class NpcType : uint32_t {
		Invalid = 0xFFFFFFFF,
		Minion = 0,
		Special,
		Boss,
		Destructible,
		Interactable,
		Agent,
		Victim,
		Captain
	};

	// DropType
	enum class DropType : uint32_t {
		None = 1 << 0,
		Orbs = 1 << 1,
		Catalysts = 1 << 2,
		Loot = 1 << 3,
		DNA = 1 << 4
	};

	// Homeworld
	enum class Homeworld : uint32_t {
		ZelemsNexus = 0,
		Nocturna,
		Verdanth,
		Cryos,
		Infinity
	};

	// NpcAffix
	class NpcAffix {
		public:
			void Read(pugi::xml_node node);

			const std::shared_ptr<NpcAffix>& GetChild() const;
			const std::shared_ptr<NpcAffix>& GetParent() const;

		private:
			std::shared_ptr<NpcAffix> mChild;
			std::shared_ptr<NpcAffix> mParent;

			std::string mChildName;
			std::string mParentName;
			std::string mModifier;
			std::string mPath;

			uint32_t mId = 0;

			friend class NounDatabase;
	};

	// EliteAffix
	class EliteAffix {
		public:
			void Read(pugi::xml_node node);

		private:
			std::shared_ptr<NpcAffix> mNpcAffix;

			int32_t mMinDifficulty = 0;
			int32_t mMaxDifficulty = 0;
	};

	// PlayerAbility
	enum class PlayerAbility : uint8_t {
		Basic = 0,
		Special1,
		Special2,
		Special3,
		Passive
	};

	// PrimaryAttribute
	enum class PrimaryAttribute : uint32_t {
		Invalid = 0xFFFFFFFF,
		Strength = 0,
		Dexterity,
		Mind
	};

	// PlayerClass
	class PlayerClass {
		public:
			void Read(pugi::xml_node node);

			const std::shared_ptr<ClassAttributes>& GetAttributes() const;

			uint32_t GetAbility(PlayerAbility ability) const;

			const glm::vec3& GetSharedAbilityOffset() const;

			Homeworld GetHomeworld() const;
			PrimaryAttribute GetPrimaryAttribute() const;

		private:
			std::shared_ptr<ClassAttributes> mAttributes;

			std::array<std::string, 5> mAbilities;

			glm::vec3 mSharedAbilityOffset;

			std::string mName;
			std::string mEffect;
			std::string mPath;

			Homeworld mHomeworld = Homeworld::ZelemsNexus;
			PrimaryAttribute mPrimaryAttribute = PrimaryAttribute::Invalid;

			uint32_t mCreatureType = 0;
			uint32_t mCreatureClass = 0;
			uint32_t mId = 0;

			int32_t mUnlockLevel = 0;

			float mWeaponMinDamage = 0;
			float mWeaponMaxDamage = 0;

			bool mNoHands = false;
			bool mNoFeet = false;

			friend class NounDatabase;
	};

	// NonPlayerClass
	class NonPlayerClass {
		public:
			void Read(pugi::xml_node node);
			
			const std::shared_ptr<ClassAttributes>& GetAttributes() const;

			const std::string& GetName() const;
			const std::string& GetDescription() const;

			NpcType GetType() const;

			float GetAggroRange() const;
			float GetAlertRange() const;
			float GetDropAggroRange() const;
			float GetDropDelay() const;

			bool IsTargetable() const;
			bool IsPet() const;

		private:
			std::shared_ptr<ClassAttributes> mAttributes;

			std::map<uint32_t, std::string> mLongDescriptions;

			std::vector<EliteAffix> mEliteAffixes;
			std::vector<DropType> mDropTypes;

			std::string mName;
			std::string mDescription;
			std::string mEffect;
			std::string mPath;

			NpcType mNpcType = NpcType::Minion;

			uint32_t mCreatureType = 0;
			uint32_t mId = 0;

			int32_t mChallengeValue = 0;
			int32_t mNpcRank = 0;

			float mAggroRange = 0;
			float mAlertRange = 0;
			float mDropAggroRange = 0;
			float mDropDelay = 0;
			float mPlayerCountHealthScale = 0;

			bool mTargetable = false;
			bool mIsPet = false;

			friend class NounDatabase;
	};

	// AssetProperty
	class AssetProperty {
		public:
			void Read(pugi::xml_node node);

		private:
			std::string mName;
			std::string mValue;

			uint32_t mKey = 0;
			uint32_t mType = 0;
	};

	// GambitDefinition
	class GambitDefinition {
		public:
			void Read(pugi::xml_node node);

			const std::vector<AssetProperty>& GetConditionProperties() const;
			const std::vector<AssetProperty>& GetAbilityProperties() const;

			uint32_t GetCondition() const;
			uint32_t GetAbility() const;

		private:
			std::vector<AssetProperty> mConditionProperties;
			std::vector<AssetProperty> mAbilityProperties;

			uint32_t mCondition = 0;
			uint32_t mAbility = 0;

			bool mRandomizeCooldown = false;
	};

	// PhaseType
	enum class PhaseType : uint8_t {
		PrioritizedList = 0,
		Sequential,
		Random
	};

	// Phase
	class Phase {
		public:
			void Read(pugi::xml_node node);

			const std::vector<GambitDefinition>& GetGambit() const;

			PhaseType GetType() const;

			bool IsStartNode() const;

		private:
			std::vector<GambitDefinition> mGambit;

			std::string mPath;

			uint32_t mId = 0;

			PhaseType mType = PhaseType::PrioritizedList;

			bool mIsStartNode = false;

			friend class NounDatabase;
	};

	// Condition
	class Condition {
		public:

		private:
			std::string mCondition;
	};

	// AINode
	class AINode {
		public:
			void Read(pugi::xml_node node);

			const std::shared_ptr<Phase>& GetPhaseData() const;
			const std::shared_ptr<Condition>& GetConditionData() const;

		private:
			std::vector<int32_t> mOutput;

			std::shared_ptr<Phase> mPhase;
			std::shared_ptr<Condition> mCondition;

			int32_t mX;
			int32_t mY;
	};

	// AIDefinition
	class AIDefinition {
		public:
			void Read(pugi::xml_node node);

			const std::vector<AINode>& GetNodes() const;

			uint32_t GetDeathAbility() const;
			uint32_t GetDeathCondition() const;
			uint32_t GetFirstAggroAbility() const;
			uint32_t GetSecondaryFirstAggroAbility() const;
			uint32_t GetFirstAlertAbility() const;
			uint32_t GetSubsequentAggroAbility() const;
			uint32_t GetPassiveAbility() const;

			bool FaceTarget() const;
			bool AlwaysRun() const;
			bool RandomizeCooldowns() const;

		private:
			std::vector<AINode> mNodes;

			std::string mPath;
			std::string mCombatIdle;
			std::string mSecondaryCombatIdle;
			std::string mSecondaryCombatIdleCondition;
			std::string mPassiveIdle;
			std::string mPreAggroIdle;
			std::string mSecondaryPreAggroIdle;
			std::string mTargetTooFar;

			uint32_t mId = 0;
			uint32_t mDeathAbility = 0;
			uint32_t mDeathCondition = 0;
			uint32_t mFirstAggroAbility = 0;
			uint32_t mSecondaryFirstAggroAbility = 0;
			uint32_t mFirstAlertAbility = 0;
			uint32_t mSubsequentAggroAbility = 0;
			uint32_t mPassiveAbility = 0;
			uint32_t mAggroType = 0;
			uint32_t mCombatIdleCooldown = 0;
			uint32_t mSecondaryCombatIdleCooldown = 0;
			uint32_t mTargetTooFarCooldown = 0;

			float mUseSecondaryStart = 0;

			bool mFaceTarget = false;
			bool mAlwaysRun = false;
			bool mRandomizeCooldowns = false;

			friend class NounDatabase;
	};

	// CharacterAnimationType
	enum class CharacterAnimationType : uint8_t {
		PreAggro = 0,
		Idle,
		LobbyIdle,
		SpecialIdle,
		WalkStop,
		VictoryIdle,
		CombatIdle,
		Move,
		CombatMove,
		Death,
		Aggro,
		SubsequentAggro,
		EnterPassiveIdle,
		Dance,
		Taunt,
		MeleeDeath,
		MeleeCriticalDeath,
		MeleeCriticalKnockbackDeath,
		CyberCriticalDeath,
		CyberCriticalKnockbackDeath,
		PlasmaCriticalDeath,
		PlasmaCriticalKnockbackDeath,
		BioCriticalDeath,
		BioCriticalKnockbackDeath,
		NecroCriticalDeath,
		NecroCriticalKnockbackDeath,
		SpacetimeCriticalDeath,
		SpacetimeCriticalKnockbackDeath,
		BodyFade,

		// Ability states
		RandomAbility1,
		RandomAbility2,
		RandomAbility3,
		Overlay1,
		Overlay2,
		Overlay3,

		//
		Count
	};

	// CharacterAnimation
	class CharacterAnimation {
		public:
			void Read(pugi::xml_node node);

			AnimationData GetAnimationData(CharacterAnimationType type) const;

		private:
			std::array<AnimationData, std::to_underlying(CharacterAnimationType::Count)> mAnimationData;

			std::string mPath;

			uint32_t mId = 0;

			friend class NounDatabase;
	};

	// NounType
	enum class NounType : uint32_t {
		None					= 0x00000000,
		Creature				= 0x06C27D00,
		Vehicle					= 0x78BDDF27,
		Obstacle				= 0x02ADB47A,
		SpawnPoint				= 0xD9EAF104,
		PathPoint				= 0x9D99F2FA,
		Trigger					= 0x3CE46113,
		PointLight				= 0x93555DCB,
		SpotLight				= 0xBCD9673B,
		LineLight				= 0x3D58111D,
		ParallelLight			= 0x8B1018A4,
		HemisphereLight			= 0xE615AFDB,
		Animator				= 0xF90527D6,
		Animated				= 0xF3051E56,
		GraphicsControl			= 0xE9A24895,
		Material				= 0xE6640542,
		Flora					= 0x5BDCEC35,
		LevelshopObject			= 0xA12B2C18,
		Terrain					= 0x151DB008,
		Weapon					= 0xE810D505,
		Building				= 0xC710B6E9,
		Handle					= 0xADB0A86B,
		HealthOrb				= 0x75B43FF2,
		ManaOrb					= 0xF402465F,
		ResurrectOrb			= 0xC035AAAD,
		Movie					= 0x4927FA7F,
		Loot					= 0x292FEA33,
		PlacableEffect			= 0x383A0A75,
		LuaJob					= 0xA2908A12,
		AbilityObject			= 0x485FC991,
		LevelExitPoint			= 0x087E8047,
		Decal					= 0x4D7784B8,
		Water					= 0x9E3C3DFA,
		Grass					= 0xFD3D2ED9,
		Door					= 0x6FEDAE4D,
		Crystal					= 0xCD482419,
		Interactable			= 0x0977AF61,
		Projectile				= 0x253F6F5C,
		DestructibleOrnament	= 0x0013FBB4,
		MapCamera				= 0xFBFB36D0,
		Occluder				= 0x071FD3D4,
		SplineCamera			= 0x6CB99FFF,
		SplineCameraNode		= 0xFD487097,
		BossPortal				= 0xC1B461BC
	};

	// PresetExtents
	enum class PresetExtents : uint32_t {
		None = 0,
		CritterVertical,
		CritterHorizontal,
		MinionVertical,
		MinionHorizontal,
		EliteMinionVertical,
		EliteMinionHorizontal,
		PlayerTempest,
		PlayerRavager,
		PlayerSentinel,
		LieutenantVertical,
		LieutenantHorizontal,
		EliteLieutenantVertical,
		EliteLieutenantHorizontal,
		CaptainVertical,
		CaptainHorizontal,
		BossVertical,
		BossHorizontal
	};

	// MovementType
	enum class MovementType : uint8_t {
		Default = 0,
		Pathfinding = Default,
		Projectile,
		Ballistic,
		HomingProjectile,
		Lobbed,
		OrbitOwner,
		None,
		GroundRoll
	};

	// Noun
	class Noun {
		public:
			void Read(pugi::xml_node node);

			static std::tuple<glm::vec3, float> GetExtents(PresetExtents preset);

			const BoundingBox& GetBoundingBox() const;

			const std::unique_ptr<DoorData>& GetDoorData() const;
			const std::unique_ptr<SwitchData>& GetSwitchData() const;
			const std::unique_ptr<PressureSwitchData>& GetPressureSwitchData() const;
			const std::unique_ptr<ProjectileData>& GetProjectileData() const;
			const std::unique_ptr<OrbitData>& GetOrbitData() const;

			const std::shared_ptr<NonPlayerClass>& GetNonPlayerClassData() const;
			const std::shared_ptr<PlayerClass>& GetPlayerClassData() const;
			const std::shared_ptr<AIDefinition>& GetAIDefinition() const;
			const std::shared_ptr<CharacterAnimation>& GetCharacterAnimation() const;

			const std::string& GetName() const;

			uint64_t GetAssetId() const;
			uint32_t GetId() const;
			uint8_t GetTeam() const;

			NounType GetType() const;
			PresetExtents GetPresetExtents() const;
			MovementType GetMovementType() const;

			bool HasLocomotion() const;
			bool IsCreature() const;
			bool IsPlayer() const;

		private:
			BoundingBox mBoundingBox;

			std::unique_ptr<DoorData> mDoorData;
			std::unique_ptr<SwitchData> mSwitchData;
			std::unique_ptr<PressureSwitchData> mPressureSwitchData;
			std::unique_ptr<ProjectileData> mProjectileData;
			std::unique_ptr<OrbitData> mOrbitData;

			std::shared_ptr<NonPlayerClass> mNpcClassData;
			std::shared_ptr<PlayerClass> mPlayerClassData;
			std::shared_ptr<AIDefinition> mAIDefinition;
			std::shared_ptr<CharacterAnimation> mCharacterAnimation;

			std::vector<uint64_t> mEliteAssetIds;

			std::string mName;

			uint64_t mAssetId = 0;
			uint32_t mId = 0;
			uint8_t mTeam = 0;

			NounType mType = NounType::None;
			PresetExtents mPresetExtents = PresetExtents::None;
			MovementType mMovementType = MovementType::Default;

			bool mHasLocomotion = false;
			bool mIsFlora = false;
			bool mIsMineral = false;
			bool mIsCreature = false;
			bool mIsPlayer = false;
			bool mIsSpawned = false;

			friend class NounDatabase;
	};

	using NounPtr = std::shared_ptr<Noun>;

	// NounDatabase
	class NounDatabase {
		public:
			static NounDatabase& Instance();

			bool Load();

			NounPtr Get(uint32_t id) const;
			std::shared_ptr<NonPlayerClass> GetNonPlayerClass(uint32_t id) const;
			std::shared_ptr<PlayerClass> GetPlayerClass(uint32_t id) const;
			std::shared_ptr<NpcAffix> GetNpcAffix(uint32_t id) const;
			std::shared_ptr<ClassAttributes> GetClassAttributes(uint32_t id) const;
			std::shared_ptr<AIDefinition> GetAIDefinition(uint32_t id) const;
			std::shared_ptr<CharacterAnimation> GetCharacterAnimation(uint32_t id) const;
			std::shared_ptr<Phase> GetPhase(uint32_t id) const;

		private:
			bool LoadNouns();
			bool LoadNonPlayerClasses();
			bool LoadPlayerClasses();
			bool LoadNpcAffixes();
			bool LoadClassAttributes();
			bool LoadAIDefinitions();
			bool LoadCharacterAnimations();
			bool LoadPhases();

		private:
			std::unordered_map<uint32_t, NounPtr> mNouns;
			std::unordered_map<uint32_t, std::shared_ptr<NonPlayerClass>> mNonPlayerClasses;
			std::unordered_map<uint32_t, std::shared_ptr<PlayerClass>> mPlayerClasses;
			std::unordered_map<uint32_t, std::shared_ptr<NpcAffix>> mNpcAffixes;
			std::unordered_map<uint32_t, std::shared_ptr<ClassAttributes>> mClassAttributes;
			std::unordered_map<uint32_t, std::shared_ptr<AIDefinition>> mAIDefinitions;
			std::unordered_map<uint32_t, std::shared_ptr<CharacterAnimation>> mCharacterAnimations;
			std::unordered_map<uint32_t, std::shared_ptr<Phase>> mPhases;

			bool mLoaded = false;
	};
}

#endif
