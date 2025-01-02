
#ifndef _GAME_OBJECT_HEADER
#define _GAME_OBJECT_HEADER

// Include
#include "noun.h"
#include "attributes.h"
#include "locomotion.h"
#include "lua.h"

#include <map>
#include <tuple>

// Predefined
namespace SporeNet { class Part; }

// Game
namespace Game {
	// Cooldown = tuple(Start + milliseconds, milliseconds)
	using Cooldown = std::tuple<uint64_t, uint32_t>;

	class Object;
	class ObjectManager;

	using ObjectPtr = std::shared_ptr<Object>;

	// StealthType
	enum class StealthType : uint8_t {
		None = 0,
		Technology,
		Supernatural,
		FullyInvisible
	};

	// EffectList
	class EffectList {
		public:
			uint8_t Add(uint32_t effect);
			uint8_t Remove(uint32_t effect);
			bool RemoveByIndex(uint8_t index);

		private:
			uint8_t GetOpenIndex();

		private:
			std::map<uint32_t, uint8_t> mIndexByEffect;

			std::vector<uint8_t> mOpenIndexes;
			std::vector<uint8_t> mUsedIndexes;
	};

	// CorpseState
	enum class CorpseState : uint32_t {
		Alive = 0,
		Unknown,
		Vaporized
	};

	// CombatantData
	class CombatantData {
		public:
			void WriteTo(RakNet::BitStream& stream) const;
			void WriteReflection(RakNet::BitStream& stream) const;

		private:
			CorpseState mCorpseState = CorpseState::Alive;

			float mHitPoints = 0;
			float mManaPoints = 0;

			bool mCorpseFadingAway = false;

			friend class Object;
	};

	// InteractableData
	class InteractableData {
		public:
			InteractableData(const ObjectPtr& object);

			uint32_t GetAbility() const;
			void SetAbility(uint32_t ability);

			int32_t GetTimesUsed() const;
			void SetTimesUsed(int32_t timesUsed);

			int32_t GetUsesAllowed() const;
			void SetUsesAllowed(int32_t usesAllowed);

			void WriteTo(RakNet::BitStream& stream) const;
			void WriteReflection(RakNet::BitStream& stream) const;

		private:
			ObjectPtr mObject;

			uint32_t mAbility = 0;

			int32_t mTimesUsed = 0;
			int32_t mUsesAllowed = 0;

			friend class Object;
	};

	// LootData
	class LootData {
		public:
			LootData(const ObjectPtr& object);

			uint32_t GetRigblockAsset() const;
			uint32_t GetPrefixAsset() const;
			uint32_t GetPrefixSecondaryAsset() const;
			uint32_t GetSuffixAsset() const;

			int32_t GetLevel() const;
			int32_t GetRarity() const;
			int32_t GetCatalystLevel() const;
			int32_t GetCatalystType() const;

			bool IsCatalystPrismatic() const;

			void SetId(uint64_t id);
			void SetInstanceId(uint64_t id);

			void SetPart(const SporeNet::Part& part);
			void SetDNAAmount(float amount);
			void SetCatalyst(const Catalyst& catalyst);

			void WriteTo(RakNet::BitStream& stream) const;
			void WriteReflection(RakNet::BitStream& stream) const;

		private:
			ObjectPtr mObject;

			uint64_t mId = 0;
			uint64_t mInstanceId = 0;

			uint32_t mRigblockAsset = 0;
			uint32_t mSuffixAssetId = 0;
			uint32_t mPrefixAssetId = 0;
			uint32_t mSecondaryPrefixAssetId = 0;

			int32_t mItemLevel = 0;
			int32_t mRarity = 0;
			int32_t mCatalystLevel = 0;
			int32_t mCatalystType = 0;

			float mDNAAmount = 0;

			bool mCatalystPrismatic = false;

			friend class Object;
	};

	// AgentBlackboard
	class AgentBlackboard {
		public:
			AgentBlackboard(const ObjectPtr& object);

			uint32_t GetTargetId() const;
			void SetTargetId(uint32_t id);

			uint32_t GetNumAttackers() const;
			void SetNumAttackers(uint32_t attackers);

			StealthType GetStealthType() const;
			void SetStealthType(StealthType stealthType);

			bool IsInCombat() const;
			void SetInCombat(bool inCombat);

			bool IsTargetable() const;
			void SetTargetable(bool targetable);

			void WriteTo(RakNet::BitStream& stream) const;
			void WriteReflection(RakNet::BitStream& stream) const;

		private:
			ObjectPtr mObject;

			uint32_t mTargetId = 0;
			uint32_t mNumAttackers = 0;

			StealthType mStealthType = StealthType::None;

			bool mInCombat = false;
			bool mTargetable = false;
	};

	// Modifier
	class Modifier {
		public:
			Modifier(const ObjectPtr& object, uint32_t id);

			uint32_t GetDuration() const;
			void SetDuration(uint32_t duration);
			void ResetDuration();

			uint8_t GetStackCount() const;
			void SetStackCount(uint8_t count);

		private:
			ObjectPtr mObject;
			ObjectPtr mTargetObject;

			uint64_t mTimestamp = 0;

			uint32_t mId = 0;
			uint32_t mDuration = 0xFFFFFFFF;

			uint8_t mStackCount = 0;

			bool mBind = false;
			bool mDirty = true;
	};

	// AI
	class AI {
		public:
			AI(const ObjectPtr& object);

			void OnTick();

		private:
			bool SearchForTarget();

			bool UseAbility(uint32_t id);
			void UseAbility();

		private:
			std::map<uint32_t, float> mAggroMap;

			ObjectPtr mObject;
			ObjectPtr mTargetObject;

			uint8_t mNode = 0;
			uint8_t mGambit = 0;

			bool mFirstAggro = false;
	};

	// ObjectDataBits
	namespace ObjectDataBits {
		enum : uint8_t {
			Team = 0,
			PlayerControlled,
			InputSyncStamp,
			PlayerIndex,
			LinearVelocity,
			AngularVelocity,
			Position,
			Orientation,
			Scale,
			MarkerScale,
			LastAnimationState,
			LastAnimationPlayTime,
			OverrideMoveIdleAnimationState,
			GraphicsState,
			GraphicsStateStartTime,
			NewGraphicsStateStartTime,
			Visible,
			HasCollision,
			OwnerId,
			MovementType,
			DisableRepulsion,
			InteractableState,
			MarkerId,
			Count
		};
	}

	// Object
	class Object : public std::enable_shared_from_this<Object> {
		public:
			enum Flags : uint16_t {
				None							= 0,
				MarkedForDeletion				= 1 << 0,
				Created							= 1 << 1,
				Dirty							= 1 << 2,
				UpdateCombatant					= 1 << 3,
				UpdateAttributes				= 1 << 4,
				UpdateLootData					= 1 << 5,
				UpdateAgentBlackboardData		= 1 << 6,
				UpdateInteractableData			= 1 << 7,
				UpdateLocomotion				= 1 << 8,

				UpdateFlags = UpdateCombatant | UpdateAttributes | UpdateLootData | UpdateAgentBlackboardData | UpdateInteractableData | UpdateLocomotion
			};

		protected:
			Object(ObjectManager& manager, uint32_t id, uint32_t noun);

		public:
			virtual ~Object() = default;

			virtual void Initialize();

			virtual bool IsTrigger() const { return false; }
			bool IsCreature() const;

			virtual void OnActivate();
			virtual void OnDeactivate();
			virtual void OnTick(float deltaTime);

			void SetTickOverride(sol::protected_function func);
			void SetPassiveAbility(const AbilityPtr& ability);

			ObjectManager& GetObjectManager();
			const ObjectManager& GetObjectManager() const;

			Instance& GetGame();
			const Instance& GetGame() const;

			LuaThread* GetLuaThread() const;
			void SetLuaThread(LuaThread* thread);
			
			bool HasCombatantData() const;
			const std::unique_ptr<CombatantData>& CreateCombatantData();
			const std::unique_ptr<CombatantData>& GetCombatantData() const;

			bool HasInteractableData() const;
			const std::unique_ptr<InteractableData>& CreateInteractableData();
			const std::unique_ptr<InteractableData>& GetInteractableData() const;

			bool HasAttributeData() const;
			const std::unique_ptr<Attributes>& GetAttributeData() const;

			bool HasLootData() const;
			const std::unique_ptr<LootData>& CreateLootData();
			const std::unique_ptr<LootData>& GetLootData() const;

			bool HasLocomotionData() const;
			const std::unique_ptr<Locomotion>& CreateLocomotionData();
			const std::unique_ptr<Locomotion>& GetLocomotionData() const;

			bool HasAgentBlackboardData() const;
			const std::unique_ptr<AgentBlackboard>& CreateAgentBlackboardData();
			const std::unique_ptr<AgentBlackboard>& GetAgentBlackboardData() const;

			uint64_t GetAssetId() const;
			void SetAssetId(uint64_t assetId);

			const NounPtr& GetNoun() const;

			uint32_t GetId() const;
			uint32_t GetNounId() const;

			NounType GetType() const;
			NpcType GetNpcType() const;

			const glm::vec3& GetPosition() const;
			void SetPosition(const glm::vec3& position);
			void SetPositionSimulated(const glm::vec3& position);

			const glm::quat& GetOrientation() const;
			void SetOrientation(const glm::quat& orientation);

			const glm::vec3& GetLinearVelocity() const;
			void SetLinearVelocity(const glm::vec3& velocity);

			const glm::vec3& GetAngularVelocity() const;
			void SetAngularVelocity(const glm::vec3& velocity);

			const BoundingBox& GetBoundingBox() const;

			const glm::vec3& GetExtent() const;
			void SetExtent(const glm::vec3& extent);

			float GetFootprintRadius() const;
			glm::vec3 GetCenterPoint() const;

			float GetCurrentSpeed() const;
			float GetModifiedMovementSpeed() const;
			
			// Physics
			std::vector<ObjectPtr> GetCollidingObjectsWith(const CollisionVolume& collisionVolume, const std::vector<NounType>& types) const;
			bool IsColliding() const;

			// Effects
			uint8_t AddEffect(uint32_t effect);
			bool RemoveEffect(uint32_t effect);
			bool RemoveEffectByIndex(uint8_t index);

			// Cooldown
			bool HasCooldown(uint32_t abilityId) const;
			Cooldown AddCooldown(uint32_t abilityId, uint32_t milliseconds);
			Cooldown RemoveCooldown(uint32_t abilityId, uint32_t milliseconds);
			Cooldown ScaleCooldown(uint32_t abilityId, float scale);

			// Properties
			float GetAttributeValue(uint8_t idx) const;
			float GetAttributeValue(AttributeType type) const;
			void SetAttributeValue(uint8_t idx, float value);
			void SetAttributeValue(AttributeType type, float value);

			PrimaryAttribute GetPrimaryAttribute() const;
			float GetPrimaryAttributeValue() const;

			float GetHealth() const;
			float GetMaxHealth() const;
			void SetHealth(float newHealth);

			float GetMana() const;
			float GetMaxMana() const;
			void SetMana(float newMana);

			ObjectPtr GetOwnerObject() const;
			void SetOwnerObject(const ObjectPtr& object);

			uint32_t GetInputSyncStamp() const;
			void SetInputSyncStamp(uint32_t inputSyncStamp);

			uint32_t GetInteractableState() const;
			void SetInteractableState(uint32_t interactableState);

			uint32_t GetMarkerId() const;
			void SetMarkerId(uint32_t markerId);

			float GetScale() const;
			void SetScale(float scale);

			uint8_t GetTeam() const;
			void SetTeam(uint8_t team);

			MovementType GetMovementType() const;
			void SetMovementType(MovementType movementType);

			PlayerPtr GetPlayer() const;
			uint8_t GetPlayerIndex() const;
			void SetPlayerIndex(uint8_t playerIndex);

			bool IsPlayerControlled() const;
			bool IsImmobilized() const;

			bool HasCollision() const;
			void SetHasCollision(bool collision);

			bool IsVisible() const;
			void SetVisible(bool visible);

			bool IsDirty() const;
			void SetDirty(bool dirty);

			bool IsMarkedForDeletion() const;
			void MarkForDeletion();

			// Combatant functions
			bool IsOverdriveCharged() const;

			std::tuple<bool, float, bool> TakeDamage(
				const AttributesPtr& attackerAttributes,
				const std::tuple<float, float>& damageRange,
				DamageType damageType, DamageSource damageSource, float damageCoefficient,
				Descriptors descriptors, float damageMultiplier, const glm::vec3& direction
			);

			std::tuple<float, bool> Heal(
				const AttributesPtr& attackerAttributes,
				const std::tuple<float, float>& healRange,
				float healCoefficient,
				Descriptors descriptors,
				bool allowMultipliers,
				bool ignoreCritical
			);

			bool CheckCritical(const AttributesPtr& attackerAttributes) const;
			void DistributeDamageAmongSquad(float damage);

			int32_t CanUseAbility(
				const AbilityPtr& ability,
				uint32_t abilityIndex,
				int32_t rank,
				const ObjectPtr& target,
				const glm::vec3& targetPosition
			);
			
			void RequestAbility(const AbilityPtr& ability, const ObjectPtr& attacker);
			void RequestModifier(const ObjectPtr& attacker);

			void OnChangeHealth(float healthChange);
			void OnChangeMana(float manaChange);

			void OnDeath();
			void OnResurrect();

			// Interactable data
			bool HasInteractableUsesLeft() const;

			// Agent Blackboard
			uint32_t GetTargetId() const;
			void SetTargetId(uint32_t id);

			StealthType GetStealthType() const;
			void SetStealthType(StealthType stealthType);

			bool IsInCombat() const;
			void SetInCombat(bool inCombat);

			bool IsTargetable() const;
			void SetTargetable(bool targetable);

			// Network & reflection
			void WriteTo(RakNet::BitStream& stream) const;
			void WriteReflection(RakNet::BitStream& stream) const;

			void ResetUpdateBits();

		protected:
			bool NeedUpdate() const;

			uint16_t GetFlags() const;
			void SetFlags(uint16_t flags);

		protected:
			ObjectManager& mManager;

			// TODO: add some better way for handling the abilities
			LuaThread* mLuaThread { nullptr };

			sol::protected_function mTickOverride = sol::nil;
			AbilityPtr mPassiveAbility;

			BoundingBox mBoundingBox;

			std::unordered_map<uint32_t, std::shared_ptr<Modifier>> mModifiers;
			std::map<uint32_t, Cooldown> mCooldowns;

			std::unique_ptr<EffectList> mEffects;
			std::unique_ptr<Attributes> mAttributes;
			std::unique_ptr<CombatantData> mCombatantData;
			std::unique_ptr<InteractableData> mInteractableData;
			std::unique_ptr<LootData> mLootData;
			std::unique_ptr<Locomotion> mLocomotionData;
			std::unique_ptr<AgentBlackboard> mAgentBlackboardData;
			std::unique_ptr<AI> mAI;

			NounPtr mNoun;

			ObjectPtr::weak_type mOwnerObject;

			uint64_t mAssetId;

			uint32_t mId;
			uint32_t mNounId;

			MovementType mMovementType = MovementType::Default;

			Flags mFlags = Flags::None;

			// mostly reflection for now
			glm::quat mOrientation {};
			glm::vec3 mLinearVelocity {};
			glm::vec3 mAngularVelocity {};

			uint64_t mLastAnimationPlayTime = 0;
			uint64_t mGraphicsStateStartTime = 0;
			uint64_t mNewGraphicsStateStartTime = 0;

			uint32_t mInputSyncStamp = 0;
			uint32_t mLastAnimationState = 0;
			uint32_t mOverrideMoveIdleAnimationState = 0;
			uint32_t mGraphicsState = 0;
			uint32_t mInteractableState = 0;
			uint32_t mMarkerId = 0;

			float mScale = 1;
			float mMarkerScale = 1;

			uint8_t mTeam = 0;
			uint8_t mPlayerIndex = 0xFF;

			bool mbPlayerControlled = false;
			bool mVisible = true;
			bool mbHasCollision = true;
			bool mDisableRepulsion = false;

			std::bitset<ObjectDataBits::Count> mDataBits;

			friend class Instance;
			friend class ObjectManager;
			friend class InteractableData;
			friend class LootData;
			friend class AgentBlackboard;
			friend class Locomotion;
	};
}

#endif
