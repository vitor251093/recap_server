
// Include
#include "object.h"
#include "objectmanager.h"
#include "instance.h"
#include "catalyst.h"

#include "sporenet/part.h"

#include "utils/functions.h"
#include "utils/log.h"

// magic numbers
constexpr std::array<float, 19> magicNumbers {
	1.f, // DamagePerPointOfStrength
	1.f, // DamagePerPointOfDexterity
	1.f, // DamagePerPointOfMind
	5.f, // HealthPerPointofStrength
	6.f, // PhysicalDefensePerPointofDexterity
	4.f, // CritRatingPerPointofDexterity
	6.f, // EnergyDefensePerPointofMind
	1.f, // ManaPerPointofMind
	6.f, // DefenseRatingDecreaseMultiplier
	1.05f, // DefenseRatingDecreaseBase
	6.f, // CriticalRatingDecreaseMultiplier
	1.05f, // CriticalRatingDecreaseBase
	2.f, // CriticalDamageBonus
	8.f, // PrimaryAttributeIgnoreAmount
	0.5f, // LeechEffectivenessForAoE
	1.f, // LeechEffectivenessForAbilities
	1.f, // LeechEffectivenessForBasics
	0.8f, // DodgePercentCap
	0.8f // ResistPercentCap
};

// difficulty tuning

// Game
namespace Game {
	// EffectList
	uint8_t EffectList::Add(uint32_t effect) {
		uint8_t index = GetOpenIndex();
		if (index != 0) {
			mIndexByEffect[effect] = index;
		}
		return index;
	}

	uint8_t EffectList::Remove(uint32_t effect) {
		auto mapEnd = mIndexByEffect.end();
		auto mapIt = mIndexByEffect.find(effect);
		if (mapIt != mapEnd) {
			uint8_t index = mapIt->second;

			auto end = mUsedIndexes.end();
			auto it = std::find(mUsedIndexes.begin(), end, index);
			if (it != end) {
				std::swap(*it, mUsedIndexes.back());
				mUsedIndexes.pop_back();
				mOpenIndexes.push_back(index);
			}

			mIndexByEffect.erase(mapIt);
			return index;
		}
		return 0;
	}

	bool EffectList::RemoveByIndex(uint8_t index) {
		auto end = mUsedIndexes.end();
		auto it = std::find(mUsedIndexes.begin(), end, index);
		if (it != end) {
			std::swap(*it, mUsedIndexes.back());
			mUsedIndexes.pop_back();
			mOpenIndexes.push_back(index);

			auto mapEnd = mIndexByEffect.end();
			auto mapIt = std::find_if(mIndexByEffect.begin(), mapEnd, [index](const auto& entry) { return entry.second == index; });
			if (mapIt != mapEnd) {
				mIndexByEffect.erase(mapIt);
			}
			return true;
		}
		return false;
	}

	uint8_t EffectList::GetOpenIndex() {
		uint8_t index;
		if (mOpenIndexes.empty()) {
			if (mUsedIndexes.size() < 0xFF) {
				mUsedIndexes.push_back(static_cast<uint8_t>(mUsedIndexes.size()) + 1);
				index = mUsedIndexes.back();
			} else {
				index = 0;
			}
		} else {
			index = mOpenIndexes.back();
			mOpenIndexes.pop_back();
			mUsedIndexes.push_back(index);
		}
		return index;
	}

	// CombatantData
	void CombatantData::WriteTo(RakNet::BitStream& stream) const {
		using RakNet::bytes_to_bits;
		using RakNet::ReallocateStream;

		constexpr auto size = bytes_to_bits(0x70);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x40));
		Write(stream, mHitPoints);
		Write(stream, mManaPoints);

		stream.SetWriteOffset(writeOffset + size);
	}

	void CombatantData::WriteReflection(RakNet::BitStream& stream) const {
		RakNet::reflection_serializer<2> reflector(stream);
		reflector.begin();
		reflector.write<0>(mHitPoints);
		reflector.write<1>(mManaPoints);
		reflector.end();
	}

	// InteractableData
	InteractableData::InteractableData(const ObjectPtr& object) : mObject(object) {}

	uint32_t InteractableData::GetAbility() const {
		return mAbility;
	}

	void InteractableData::SetAbility(uint32_t ability) {
		mAbility = ability;
		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateInteractableData);
	}

	int32_t InteractableData::GetTimesUsed() const {
		return mTimesUsed;
	}

	void InteractableData::SetTimesUsed(int32_t timesUsed) {
		mTimesUsed = timesUsed;
		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateInteractableData);
	}

	int32_t InteractableData::GetUsesAllowed() const {
		return mUsesAllowed;
	}

	void InteractableData::SetUsesAllowed(int32_t usesAllowed) {
		mUsesAllowed = usesAllowed;
		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateInteractableData);
	}

	void InteractableData::WriteTo(RakNet::BitStream& stream) const {
		using RakNet::bytes_to_bits;
		using RakNet::ReallocateStream;

		constexpr auto size = bytes_to_bits(0x34);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x08));
		Write(stream, mTimesUsed);
		Write(stream, mUsesAllowed);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x14));
		Write(stream, mAbility);

		stream.SetWriteOffset(writeOffset + size);
	}

	void InteractableData::WriteReflection(RakNet::BitStream& stream) const {
		RakNet::reflection_serializer<3> reflector(stream);
		reflector.begin();
		reflector.write<0>(mTimesUsed);
		reflector.write<1>(mUsesAllowed);
		reflector.write<2>(mAbility);
		reflector.end();
	}

	// LootData
	LootData::LootData(const ObjectPtr& object) : mObject(object) {}

	uint32_t LootData::GetRigblockAsset() const {
		return mRigblockAsset;
	}

	uint32_t LootData::GetPrefixAsset() const {
		return mPrefixAssetId;
	}

	uint32_t LootData::GetPrefixSecondaryAsset() const {
		return mSecondaryPrefixAssetId;
	}

	uint32_t LootData::GetSuffixAsset() const {
		return mSuffixAssetId;
	}

	int32_t LootData::GetLevel() const {
		return mItemLevel;
	}

	int32_t LootData::GetRarity() const {
		return mRarity;
	}

	int32_t LootData::GetCatalystLevel() const {
		return mCatalystLevel;
	}

	int32_t LootData::GetCatalystType() const {
		return mCatalystType;
	}

	bool LootData::IsCatalystPrismatic() const {
		return mCatalystPrismatic;
	}

	void LootData::SetId(uint64_t id) {
		mId = id;
		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateLootData);
	}

	void LootData::SetInstanceId(uint64_t id) {
		mInstanceId = id;
		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateLootData);
	}

	void LootData::SetPart(const SporeNet::Part& part) {
		mRigblockAsset = part.GetRigblockAssetHash();
		mSuffixAssetId = part.GetSuffixAssetHash();
		mPrefixAssetId = part.GetPrefixAssetHash();
		mSecondaryPrefixAssetId = part.GetPrefixSecondaryAssetHash();
		mItemLevel = part.GetLevel();
		mRarity = static_cast<int32_t>(part.GetRarity());
		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateLootData);
	}

	void LootData::SetDNAAmount(float amount) {
		mDNAAmount = amount;
		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateLootData);
	}

	void LootData::SetCatalyst(const Catalyst& catalyst) {
		mCatalystType = static_cast<int32_t>(catalyst.GetType());
		mCatalystLevel = static_cast<int32_t>(catalyst.GetRarity());
		mCatalystPrismatic = catalyst.GetColor() == CatalystColor::Prismatic;
		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateLootData);
	}

	void LootData::WriteTo(RakNet::BitStream& stream) const {
		using RakNet::bytes_to_bits;
		using RakNet::ReallocateStream;

		constexpr auto size = bytes_to_bits(0x80);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x08));
		Write(stream, mCatalystLevel);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x10));
		Write(stream, mId);
		Write(stream, mRigblockAsset);
		Write(stream, mSuffixAssetId);
		Write(stream, mPrefixAssetId);
		Write(stream, mSecondaryPrefixAssetId);
		Write(stream, mItemLevel);
		Write(stream, mRarity);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x40));
		Write(stream, mInstanceId);
		Write(stream, mDNAAmount);

		stream.SetWriteOffset(writeOffset + size);
	}

	void LootData::WriteReflection(RakNet::BitStream& stream) const {
		RakNet::reflection_serializer<10> reflector(stream);
		reflector.begin();
		reflector.write<0>(mCatalystLevel);
		reflector.write<1>(mId);
		reflector.write<2>(mRigblockAsset);
		reflector.write<3>(mSuffixAssetId);
		reflector.write<4>(mPrefixAssetId);
		reflector.write<5>(mSecondaryPrefixAssetId);
		reflector.write<6>(mItemLevel);
		reflector.write<7>(mRarity);
		reflector.write<8>(mInstanceId);
		reflector.write<9>(mDNAAmount);
		reflector.end();
	}

	// AgentBlackboard
	AgentBlackboard::AgentBlackboard(const ObjectPtr& object) : mObject(object) {}

	uint32_t AgentBlackboard::GetTargetId() const {
		return mTargetId;
	}

	void AgentBlackboard::SetTargetId(uint32_t id) {
		mTargetId = id;
		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateAgentBlackboardData);
	}

	uint32_t AgentBlackboard::GetNumAttackers() const {
		return mNumAttackers;
	}

	void AgentBlackboard::SetNumAttackers(uint32_t attackers) {
		mNumAttackers = attackers;
		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateAgentBlackboardData);
	}

	StealthType AgentBlackboard::GetStealthType() const {
		return mStealthType;
	}

	void AgentBlackboard::SetStealthType(StealthType stealthType) {
		mStealthType = stealthType;
		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateAgentBlackboardData);
	}

	bool AgentBlackboard::IsInCombat() const {
		return mInCombat;
	}

	void AgentBlackboard::SetInCombat(bool inCombat) {
		mInCombat = inCombat;
		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateAgentBlackboardData);
	}

	bool AgentBlackboard::IsTargetable() const {
		return mTargetable;
	}

	void AgentBlackboard::SetTargetable(bool targetable) {
		mTargetable = targetable;
		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateAgentBlackboardData);
	}

	void AgentBlackboard::WriteTo(RakNet::BitStream& stream) const {
		using RakNet::bytes_to_bits;
		using RakNet::ReallocateStream;

		constexpr auto size = bytes_to_bits(0x598);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x550));
		Write(stream, mTargetId);
		Write(stream, mInCombat);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x556));
		Write(stream, mStealthType);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x578));
		Write(stream, mTargetable);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x57C));
		Write(stream, mNumAttackers);

		stream.SetWriteOffset(writeOffset + size);
	}

	void AgentBlackboard::WriteReflection(RakNet::BitStream& stream) const {
		RakNet::reflection_serializer<5> reflector(stream);
		reflector.begin();
		reflector.write<0>(mTargetId);
		reflector.write<1>(mInCombat);
		reflector.write<2>(mStealthType);
		reflector.write<3>(mTargetable);
		reflector.write<4>(mNumAttackers);
		reflector.end();
	}

	// Modifier
	Modifier::Modifier(const ObjectPtr& object, uint32_t id) : mObject(object), mId(id) {
		// 
	}

	uint32_t Modifier::GetDuration() const {
		return mDuration;
	}

	void Modifier::SetDuration(uint32_t duration) {
		mDuration = duration;
	}

	void Modifier::ResetDuration() {
		mTimestamp = mObject->GetGame().GetTime();
		mDirty = true;
	}

	uint8_t Modifier::GetStackCount() const {
		return mStackCount;
	}

	void Modifier::SetStackCount(uint8_t count) {
		mStackCount = count;
		mDirty = true;
	}

	// AI
	AI::AI(const ObjectPtr& object) : mObject(object) {
		// TODO: Make some booleans to determine if certain variables are accessable
	}

	void AI::OnTick() {
		if (!SearchForTarget()) {
			return;
		}

		const auto& aidefinition = mObject->GetNoun()->GetAIDefinition();
		if (!aidefinition) {
			return;
		}

		// First time we see a target.
		if (!mFirstAggro) {
			UseAbility(aidefinition->GetFirstAggroAbility());
			mFirstAggro = true;
		}

		UseAbility();

		if (aidefinition->FaceTarget()) {
			mObject->GetLocomotionData()->SetFacing(mTargetObject->GetPosition());
		}
	}

	bool AI::SearchForTarget() {
		if (mTargetObject) {
			return true;
		}

		const auto& data = mObject->GetNoun()->GetNonPlayerClassData();
		if (!data) {
			// If we don't have class data then we cannot have a target.
			return false;
		}
#if 1
		const auto& objectManager = mObject->GetObjectManager();

		const auto searchRadius = data->GetAggroRange();
		const auto& objects = objectManager.GetObjectsInRadius(BoundingSphere(mObject->GetPosition(), searchRadius), { NounType::Creature });
		for (const auto& possibleTarget : objects) {
			if (possibleTarget->IsPlayerControlled()) {
				mTargetObject = possibleTarget;
				break;
			}
		}
#endif
		if (mTargetObject) {
			return true;
		}

		return false;
	}

	bool AI::UseAbility(uint32_t id) {
		if (!mObject->HasCooldown(id)) {
			const auto& ability = mObject->GetGame().GetLua().GetAbility(id);
			if (ability) {
				return ability->Tick(mObject, mTargetObject, mTargetObject->GetPosition(), 1);
			}
		}
		return false;
	}

	void AI::UseAbility() {
		const auto& aidefinition = mObject->GetNoun()->GetAIDefinition();
		const auto& nodes = aidefinition->GetNodes();
		if (nodes.empty()) {
			// No nodes, no AI.
			return;
		}

		if (mNode >= nodes.size()) {
			// Reset data
			mNode = 0;
			mGambit = 0;
		}

		const auto& node = nodes[mNode];
		const auto& condition = node.GetConditionData();
		if (condition) {
			// test some stuff, if false return
		}

		const auto& phase = node.GetPhaseData();
		if (phase) {
			const auto& gambit = phase->GetGambit();
			switch (phase->GetType()) {
				case PhaseType::PrioritizedList: {
					for (const auto& gambitData : gambit) {
						if (UseAbility(gambitData.GetAbility())) {
							break;
						}
					}
					break;
				}

				case PhaseType::Sequential: {
					const auto& gambitData = gambit[mGambit];
					if (UseAbility(gambitData.GetAbility())) {
						mGambit++;
						mGambit = mGambit == gambit.size() ? 0 : mGambit;
					}
					break;
				}

				case PhaseType::Random: {
					mGambit = utils::random::get<uint8_t>(0, static_cast<uint8_t>(gambit.size() - 1));

					const auto& gambitData = gambit[mGambit];
					UseAbility(gambitData.GetAbility());

					break;
				}
			}
		}
	}

	// Object
	Object::Object(ObjectManager& manager, uint32_t id, uint32_t noun) : mManager(manager), mId(id), mNounId(noun) {
		mNoun = NounDatabase::Instance().Get(mNounId);

		mBoundingBox.center = glm::vec3(0);
		mBoundingBox.extent = glm::vec3(1);
	}

	void Object::Initialize() {
		if (!mNoun) {
			return;
		}

		mAssetId = mNoun->GetAssetId();
		mTeam = mNoun->GetTeam();
		mMovementType = mNoun->GetMovementType();

		// BoundingBox stuff
		switch (mNoun->GetPresetExtents()) {
			case PresetExtents::None: {
				mBoundingBox = mNoun->GetBoundingBox();
				break;
			}

			// All others
			default: {
				break;
			}
		}

		if (mNoun->HasLocomotion()) {
			CreateLocomotionData();
		}

		// Mob data
		const auto& playerClassData = mNoun->GetPlayerClassData();
		const auto& npcClassData = mNoun->GetNonPlayerClassData();
		const auto& aiDefinition = mNoun->GetAIDefinition();
		if (playerClassData || npcClassData || aiDefinition) {
			CreateAgentBlackboardData();
		}

		if (mNoun->IsCreature()) {
			CreateCombatantData();
		}

		if (aiDefinition) {
			// Create "ai brain" (thats what they called it)
		}

		if (const auto& projectile = mNoun->GetProjectileData()) {
			const auto& otherCollision = projectile->GetOtherCollisionVolume();
			if (otherCollision) {
				switch (otherCollision->GetShape()) {
					case CollisionShape::Sphere:
						mBoundingBox.extent = glm::vec3(otherCollision->GetSphereRadius());
						break;

					case CollisionShape::Box:
						mBoundingBox.extent = otherCollision->GetBoxExtents() * 0.5f;
						break;
				}
			}
		}

		if (mNoun->IsPlayer()) {
			const auto& data = mNoun->GetPlayerClassData();
			if (!data) {
				return;
			}

			// Otherwise enemies can't use any abilities on you.
			SetTargetable(true);

			const auto& attributes = data->GetAttributes();
			if (attributes) {
				auto health = attributes->GetBaseAttribute(ClassAttribute::Health);
				if (health > 0) {
					SetAttributeValue(AttributeType::MaxHealth, health);
					SetHealth(GetMaxHealth());
				}

				auto mana = attributes->GetBaseAttribute(ClassAttribute::Mana);
				if (mana > 0) {
					SetAttributeValue(AttributeType::MaxMana, mana);
					SetMana(GetMaxMana());
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::Strength); value > 0) {
					SetAttributeValue(AttributeType::Strength, value);
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::Dexterity); value > 0) {
					SetAttributeValue(AttributeType::Dexterity, value);
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::Mind); value > 0) {
					SetAttributeValue(AttributeType::Mind, value);
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::PhysicalDefense); value > 0) {
					SetAttributeValue(AttributeType::PhysicalDefense, value);
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::MagicalDefense); value > 0) {
					// Unused
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::EnergyDefense); value > 0) {
					SetAttributeValue(AttributeType::EnergyDefense, value);
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::Critical); value > 0) {
					SetAttributeValue(AttributeType::CriticalRating, value);
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::NonCombatSpeed); value > 0) {
					SetAttributeValue(AttributeType::NonCombatSpeed, value);
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::CombatSpeed); value > 0) {
					SetAttributeValue(AttributeType::CombatSpeed, value);
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::StealthDetection); value > 0) {
					SetAttributeValue(AttributeType::StealthDetection, value);
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::MovementSpeedBuff); value > 0) {
					SetAttributeValue(AttributeType::MovementSpeedBuff, value);
				}

				mAttributes->SetWeaponDamage(1, 5);
			}
		} else {
			// All nonplayer objects should have an AI object
			mAI = std::make_unique<AI>(shared_from_this());

			const auto& data = mNoun->GetNonPlayerClassData();
			if (!data) {
				return;
			}

			SetTargetable(data->IsTargetable());

			const auto& attributes = data->GetAttributes();
			if (attributes) {
				auto health = attributes->GetBaseAttribute(ClassAttribute::Health);
				if (health > 0) {
					SetAttributeValue(AttributeType::MaxHealth, health);
					SetHealth(GetMaxHealth());
				}

				auto mana = attributes->GetBaseAttribute(ClassAttribute::Mana);
				if (mana > 0) {
					SetAttributeValue(AttributeType::MaxMana, mana);
					SetMana(GetMaxMana());
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::Strength); value > 0) {
					SetAttributeValue(AttributeType::Strength, value);
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::Dexterity); value > 0) {
					SetAttributeValue(AttributeType::Dexterity, value);
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::Mind); value > 0) {
					SetAttributeValue(AttributeType::Mind, value);
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::PhysicalDefense); value > 0) {
					SetAttributeValue(AttributeType::PhysicalDefense, value);
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::MagicalDefense); value > 0) {
					// Unused
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::EnergyDefense); value > 0) {
					SetAttributeValue(AttributeType::EnergyDefense, value);
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::Critical); value > 0) {
					SetAttributeValue(AttributeType::CriticalRating, value);
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::NonCombatSpeed); value > 0) {
					SetAttributeValue(AttributeType::NonCombatSpeed, value);
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::CombatSpeed); value > 0) {
					SetAttributeValue(AttributeType::CombatSpeed, value);
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::StealthDetection); value > 0) {
					SetAttributeValue(AttributeType::StealthDetection, value);
				}

				if (auto value = attributes->GetBaseAttribute(ClassAttribute::MovementSpeedBuff); value > 0) {
					SetAttributeValue(AttributeType::MovementSpeedBuff, value);
				}
			}
		}
	}

	bool Object::IsCreature() const {
		return mNoun ? mNoun->IsCreature() : false;
	}

	void Object::OnActivate() {
		if (mPassiveAbility) {
			mPassiveAbility->Activate(shared_from_this());
		}
	}

	void Object::OnDeactivate() {
		if (mPassiveAbility) {
			mPassiveAbility->Deactivate(shared_from_this());
		}
	}

	void Object::OnTick(float deltaTime) {
		if (mLocomotionData) {
			mLocomotionData->Update(deltaTime);
		}

		if (mTickOverride != sol::nil) {
			mTickOverride.call<void>(mPassiveAbility, shared_from_this());
		} else if (mPassiveAbility) {
			mPassiveAbility->Tick(shared_from_this(), nullptr, glm::zero<glm::vec3>(), 1);
		}

		if (mAI) {
			mAI->OnTick();
		}
	}

	void Object::SetTickOverride(sol::protected_function func) {
		mTickOverride = func;
		mPassiveAbility = nullptr;
	}

	void Object::SetPassiveAbility(const AbilityPtr& ability) {
		mPassiveAbility = ability;
		if (mPassiveAbility) {
			mTickOverride = sol::nil;
		}
	}

	ObjectManager& Object::GetObjectManager() {
		return mManager;
	}

	const ObjectManager& Object::GetObjectManager() const {
		return mManager;
	}

	Instance& Object::GetGame() {
		return mManager.GetGame();
	}

	const Instance& Object::GetGame() const {
		return mManager.GetGame();
	}

	LuaThread* Object::GetLuaThread() const {
		return mLuaThread;
	}

	void Object::SetLuaThread(LuaThread* thread) {
		mLuaThread = thread;
	}

	bool Object::HasCombatantData() const {
		return static_cast<bool>(mCombatantData);
	}

	const std::unique_ptr<CombatantData>& Object::CreateCombatantData() {
		if (!mCombatantData) {
			mCombatantData = std::make_unique<CombatantData>();
			SetFlags(GetFlags() | Flags::UpdateCombatant);
		}
		return GetCombatantData();
	}

	const std::unique_ptr<CombatantData>& Object::GetCombatantData() const {
		return mCombatantData;
	}

	bool Object::HasInteractableData() const {
		return static_cast<bool>(mInteractableData);
	}

	const std::unique_ptr<InteractableData>& Object::CreateInteractableData() {
		if (!mInteractableData) {
			mInteractableData = std::make_unique<InteractableData>(shared_from_this());
			SetFlags(GetFlags() | Flags::UpdateInteractableData);
		}
		return GetInteractableData();
	}

	const std::unique_ptr<InteractableData>& Object::GetInteractableData() const {
		return mInteractableData;
	}

	bool Object::HasAttributeData() const {
		return static_cast<bool>(mAttributes);
	}

	const std::unique_ptr<Attributes>& Object::GetAttributeData() const {
		return mAttributes;
	}

	bool Object::HasLootData() const {
		return static_cast<bool>(mLootData);
	}

	const std::unique_ptr<LootData>& Object::CreateLootData() {
		if (!mLootData) {
			mLootData = std::make_unique<LootData>(shared_from_this());
			SetFlags(GetFlags() | Flags::UpdateLootData);
		}
		return GetLootData();
	}

	const std::unique_ptr<LootData>& Object::GetLootData() const {
		return mLootData;
	}

	bool Object::HasLocomotionData() const {
		return static_cast<bool>(mLocomotionData);
	}

	const std::unique_ptr<Locomotion>& Object::CreateLocomotionData() {
		if (!mLocomotionData) {
			mLocomotionData = std::make_unique<Locomotion>(shared_from_this());
			SetFlags(GetFlags() | Flags::UpdateLocomotion);
		}
		return GetLocomotionData();
	}

	const std::unique_ptr<Locomotion>& Object::GetLocomotionData() const {
		return mLocomotionData;
	}

	bool Object::HasAgentBlackboardData() const {
		return static_cast<bool>(mAgentBlackboardData);
	}

	const std::unique_ptr<AgentBlackboard>& Object::CreateAgentBlackboardData() {
		if (!mAgentBlackboardData) {
			mAgentBlackboardData = std::make_unique<AgentBlackboard>(shared_from_this());
			SetFlags(GetFlags() | Flags::UpdateAgentBlackboardData);
		}
		return GetAgentBlackboardData();
	}

	const std::unique_ptr<AgentBlackboard>& Object::GetAgentBlackboardData() const {
		return mAgentBlackboardData;
	}

	uint64_t Object::GetAssetId() const {
		return mAssetId;
	}

	void Object::SetAssetId(uint64_t assetId) {
		mAssetId = assetId;
	}

	const NounPtr& Object::GetNoun() const {
		return mNoun;
	}

	uint32_t Object::GetId() const {
		return mId;
	}

	uint32_t Object::GetNounId() const {
		return mNounId;
	}

	NounType Object::GetType() const {
		return mNoun ? mNoun->GetType() : NounType::None;
	}

	NpcType Object::GetNpcType() const {
		if (mNoun) {
			const auto& npcData = mNoun->GetNonPlayerClassData();
			if (npcData) {
				return npcData->GetType();
			}
		}
		return NpcType::Invalid;
	}

	const glm::vec3& Object::GetPosition() const {
		return mBoundingBox.center;
	}

	void Object::SetPosition(const glm::vec3& position) {
		SetPositionSimulated(position);
		mDataBits.set(ObjectDataBits::Position);
	}

	void Object::SetPositionSimulated(const glm::vec3& position) {
		bool dirty = position != mBoundingBox.center;
		mBoundingBox.center = position;
		if (dirty) {
			SetDirty(true);
		}
	}

	const glm::quat& Object::GetOrientation() const {
		return mOrientation;
	}

	void Object::SetOrientation(const glm::quat& orientation) {
		mOrientation = orientation;
		mDataBits.set(ObjectDataBits::Orientation);
	}

	const glm::vec3& Object::GetLinearVelocity() const {
		return mLinearVelocity;
	}

	void Object::SetLinearVelocity(const glm::vec3& velocity) {
		mLinearVelocity = velocity;
		mDataBits.set(ObjectDataBits::LinearVelocity);
	}

	const glm::vec3& Object::GetAngularVelocity() const {
		return mAngularVelocity;
	}

	void Object::SetAngularVelocity(const glm::vec3& velocity) {
		mAngularVelocity = velocity;
		mDataBits.set(ObjectDataBits::AngularVelocity);
	}

	const BoundingBox& Object::GetBoundingBox() const {
		return mBoundingBox;
	}

	const glm::vec3& Object::GetExtent() const {
		return mBoundingBox.extent;
	}

	void Object::SetExtent(const glm::vec3& extent) {
		bool dirty = extent != mBoundingBox.extent;
		mBoundingBox.extent = glm::abs(extent);
		if (dirty) {
			SetDirty(true);
		}
	}

	float Object::GetFootprintRadius() const {
		float result = 0;
		if (mNoun) {
			const auto& [extent, scale] = Noun::GetExtents(mNoun->GetPresetExtents());
			if (scale == 0) {
				const auto& bBox = mNoun->GetBoundingBox();

				auto min = bBox.GetMin();
				auto max = bBox.GetMax();

				result = glm::length(glm::min(glm::abs(min), glm::abs(max)));
			} else {
				result = glm::sqrt(glm::dot(extent.x, extent.x) * 2) * 0.5f;
			}
		}

		return result * GetScale();
	}

	glm::vec3 Object::GetCenterPoint() const {
		glm::vec3 center(0, 0, 1);
		if (mNoun) {
			const auto& [extent, scale] = Noun::GetExtents(mNoun->GetPresetExtents());
			if (scale == 0) {
				center.z = mNoun->GetBoundingBox().GetMax().z;
			} else {
				center.z = extent.z;
			}
		}

		center = GetPosition() + GetScale() * center * 0.5f;
		return std::move(center);
	}

	float Object::GetCurrentSpeed() const {
		auto speed = mLinearVelocity;
		if (mMovementType != MovementType::Default && HasAttributeData()) {
			speed *= GetAttributeValue(AttributeType::MovementSpeedBuff) + 1.0f;
		}
		return glm::length(speed);
	}

	float Object::GetModifiedMovementSpeed() const {
		if (!HasAttributeData()) {
			return 0;
		}

		AttributeType attribute = AttributeType::NonCombatSpeed;
		if (IsInCombat()) { // || GetGame().GetType() == GameType::Arena
			attribute = AttributeType::CombatSpeed;
		}

		return (GetAttributeValue(attribute) + 1.f) * GetAttributeValue(AttributeType::MovementSpeedBuff);
	}

	// Physics
	std::vector<ObjectPtr> Object::GetCollidingObjectsWith(const CollisionVolume& collisionVolume, const std::vector<NounType>& types) const {
		static thread_local BoundingSphere localSphere {};
		static thread_local BoundingBox localBox {};

		std::vector<ObjectPtr> result;
		switch (collisionVolume.GetShape()) {
			case CollisionShape::Sphere: {
				localSphere.center = mBoundingBox.center;
				localSphere.radius = collisionVolume.GetSphereRadius();
				mManager.GetObjectsInRadius(localSphere, types);

				// Line of sight for sphere
				break;
			}

			case CollisionShape::Box: {
				localBox.center = mBoundingBox.center;
				localBox.extent = collisionVolume.GetBoxExtents();
				mManager.GetObjectsInRegion(localBox, types);

				// Line of sight for box
				break;
			}
		}

		return result;
	}

	bool Object::IsColliding() const {
		if (!mNoun) {
			return false;
		}

		const auto& projectile = mNoun->GetProjectileData();
		if (!projectile) {
			return false;
		}

		const auto& otherCollision = projectile->GetOtherCollisionVolume();
		if (!otherCollision) {
			return false;
		}

		return !GetCollidingObjectsWith(*otherCollision, {}).empty();
	}

	// Effects
	uint8_t Object::AddEffect(uint32_t effect) {
		if (effect == 0) {
			return 0;
		}

		if (!mEffects) {
			mEffects = std::make_unique<EffectList>();
		}
		return mEffects->Add(effect);
	}

	bool Object::RemoveEffect(uint32_t effect) {
		if (mEffects) {
			return mEffects->Remove(effect);
		}
		return false;
	}

	bool Object::RemoveEffectByIndex(uint8_t index) {
		if (mEffects) {
			return mEffects->RemoveByIndex(index);
		}
		return false;
	}

	// Cooldown
	bool Object::HasCooldown(uint32_t abilityId) const {
		// TODO: check if ability has global cooldown
		if (auto it = mCooldowns.find(abilityId); it != mCooldowns.end()) {
			return std::get<0>(it->second) > GetGame().GetTime();
		}
		return false;
	}

	Cooldown Object::AddCooldown(uint32_t abilityId, uint32_t milliseconds) {
		const auto time = GetGame().GetTime();
		const auto& [it, inserted] = mCooldowns.try_emplace(abilityId);
		if (inserted || time > std::get<0>(it->second)) {
			it->second = std::make_tuple(time + milliseconds, milliseconds);
		} else {
			const auto& [end, duration] = it->second;
			const auto newDuration = static_cast<uint32_t>(end - time + milliseconds);
			it->second = std::make_tuple(end - duration + newDuration, newDuration);
		}
		return it->second;
	}

	Cooldown Object::RemoveCooldown(uint32_t abilityId, uint32_t milliseconds) {
		Cooldown cooldown;
		if (auto it = mCooldowns.find(abilityId); it != mCooldowns.end()) {
			const auto time = GetGame().GetTime();
			
			auto& [end, duration] = it->second;
			if (milliseconds >= duration) {
				mCooldowns.erase(it);
			} else {
				end -= milliseconds;
				duration -= milliseconds;
				cooldown = it->second;
			}
		}
		return cooldown;
	}

	Cooldown Object::ScaleCooldown(uint32_t abilityId, float scale) {
		return Cooldown {};
	}

	// Properties
	float Object::GetAttributeValue(uint8_t idx) const {
		if (mAttributes) {
			return mAttributes->GetValue(idx);
		}
		return 0.f;
	}

	float Object::GetAttributeValue(AttributeType type) const {
		return GetAttributeValue(static_cast<uint8_t>(type));
	}

	void Object::SetAttributeValue(uint8_t idx, float value) {
		if (!mAttributes) {
			mAttributes = std::make_unique<Attributes>();
			mAttributes->SetOwnerObject(shared_from_this());
		}
		mAttributes->SetValue(idx, value);
		SetFlags(GetFlags() | Flags::UpdateAttributes);
	}

	void Object::SetAttributeValue(AttributeType type, float value) {
		SetAttributeValue(static_cast<uint8_t>(type), value);
	}

	PrimaryAttribute Object::GetPrimaryAttribute() const {
		if (mNoun) {
			const auto& playerClassData = mNoun->GetPlayerClassData();
			if (playerClassData) {
				return playerClassData->GetPrimaryAttribute();
			}
		}
		return PrimaryAttribute::Invalid;
	}

	float Object::GetPrimaryAttributeValue() const {
		switch (GetPrimaryAttribute()) {
			case PrimaryAttribute::Strength: return GetAttributeValue(AttributeType::Strength);
			case PrimaryAttribute::Dexterity: return GetAttributeValue(AttributeType::Dexterity);
			case PrimaryAttribute::Mind: return GetAttributeValue(AttributeType::Mind);
		}
		return 0.f;
	}

	float Object::GetHealth() const {
		if (HasCombatantData()) {
			return mCombatantData->mHitPoints;
		}
		return 0.f;
	}

	float Object::GetMaxHealth() const {
		if (mAttributes) {
			return mAttributes->GetValue(AttributeType::MaxHealth);
		}
		return 100.f;
	}

	void Object::SetHealth(float newHealth) {
		if (HasCombatantData()) {
			mCombatantData->mHitPoints = std::max<float>(0, std::min<float>(newHealth, GetMaxHealth()));
			SetFlags(GetFlags() | Flags::UpdateCombatant);
		}
	}

	float Object::GetMana() const {
		if (HasCombatantData()) {
			return mCombatantData->mManaPoints;
		}
		return 0.f;
	}

	float Object::GetMaxMana() const {
		if (mAttributes) {
			return mAttributes->GetValue(AttributeType::MaxMana);
		}
		return 100.f;
	}

	void Object::SetMana(float newMana) {
		if (HasCombatantData()) {
			mCombatantData->mManaPoints = std::max<float>(0, std::min<float>(newMana, GetMaxMana()));
			SetFlags(GetFlags() | Flags::UpdateCombatant);
		}
	}

	ObjectPtr Object::GetOwnerObject() const {
		return mOwnerObject.lock();
	}

	void Object::SetOwnerObject(const ObjectPtr& object) {
		mOwnerObject = object;
		mDataBits.set(ObjectDataBits::OwnerId);
	}

	uint32_t Object::GetInputSyncStamp() const {
		return mInputSyncStamp;
	}

	void Object::SetInputSyncStamp(uint32_t inputSyncStamp) {
		mInputSyncStamp = inputSyncStamp;
		mDataBits.set(ObjectDataBits::InputSyncStamp);
	}

	uint32_t Object::GetInteractableState() const {
		return mInteractableState;
	}

	void Object::SetInteractableState(uint32_t interactableState) {
		mInteractableState = interactableState;
		mDataBits.set(ObjectDataBits::InteractableState);
	}

	uint32_t Object::GetMarkerId() const {
		return mMarkerId;
	}

	void Object::SetMarkerId(uint32_t markerId) {
		mMarkerId = markerId;
		mDataBits.set(ObjectDataBits::MarkerId);
	}

	float Object::GetScale() const {
		return mScale;
	}

	void Object::SetScale(float scale) {
		mScale = scale;
		mDataBits.set(ObjectDataBits::Scale);
	}

	uint8_t Object::GetTeam() const {
		return mTeam;
	}

	void Object::SetTeam(uint8_t team) {
		mTeam = team;
		mDataBits.set(ObjectDataBits::Team);
	}

	MovementType Object::GetMovementType() const {
		return mMovementType;
	}

	void Object::SetMovementType(MovementType movementType) {
		mMovementType = movementType;
		mDataBits.set(ObjectDataBits::MovementType);
	}

	PlayerPtr Object::GetPlayer() const {
		return mManager.GetGame().GetPlayerByIndex(mPlayerIndex);
	}

	uint8_t Object::GetPlayerIndex() const {
		return mPlayerIndex;
	}

	void Object::SetPlayerIndex(uint8_t playerIndex) {
		mPlayerIndex = playerIndex;
		mbPlayerControlled = mPlayerIndex < 0xFF;
		mDataBits.set(ObjectDataBits::PlayerIndex);
		mDataBits.set(ObjectDataBits::PlayerControlled);
	}

	bool Object::IsPlayerControlled() const {
		return mbPlayerControlled;
	}

	bool Object::IsImmobilized() const {
		return GetAttributeValue(AttributeType::Immobilized) > 0;
	}

	bool Object::HasCollision() const {
		return mbHasCollision;
	}

	void Object::SetHasCollision(bool collision) {
		mbHasCollision = collision;
		mDataBits.set(ObjectDataBits::HasCollision);
	}

	bool Object::IsVisible() const {
		return mVisible;
	}

	void Object::SetVisible(bool visible) {
		mVisible = visible;
		mDataBits.set(ObjectDataBits::Visible);
	}

	bool Object::IsDirty() const {
		return mFlags & Flags::Dirty;
	}

	void Object::SetDirty(bool dirty) {
		if (dirty) {
			SetFlags(GetFlags() | Flags::Dirty);
		} else {
			SetFlags(GetFlags() & ~Flags::Dirty);
		}
	}

	bool Object::IsMarkedForDeletion() const {
		return mFlags & Flags::MarkedForDeletion;
	}

	void Object::MarkForDeletion() {
		mManager.MarkForDeletion(shared_from_this());
		SetFlags(GetFlags() | Flags::MarkedForDeletion);
	}

	// Combatant functions
	bool Object::IsOverdriveCharged() const {
		if (IsPlayerControlled()) {
			const auto& player = GetPlayer();
			return player ? player->IsOverdriveCharged() : false;
		}
		return false;
	}

	std::tuple<bool, float, bool> Object::TakeDamage(
		const AttributesPtr& attackerAttributes,
		const std::tuple<float, float>& damageRange,
		DamageType damageType, DamageSource damageSource, float damageCoefficient,
		Descriptors descriptors, float damageMultiplier, const glm::vec3& direction
	) {
		// Move this to Instance?

		// calculate damage stuff
		float damage = 0;
		bool critical = false;
		if (damage <= 0) {
			damage = utils::random::get<float>(std::get<0>(damageRange), std::get<1>(damageRange));

			critical = CheckCritical(attackerAttributes);
			if (critical) {
				auto criticalIncrease = attackerAttributes->GetValue(AttributeType::CriticalDamageIncrease);
				damage *= criticalIncrease + 1;
			}
		}
		
		if (damage > 0) {
			SetHealth(GetHealth() - damage);
			if (GetHealth() <= 0) {
				GetGame().OnObjectDeath(shared_from_this(), critical, false);
			}
		}

		return { true, damage, critical };
	}

	std::tuple<float, bool> Object::Heal(
		const AttributesPtr& attackerAttributes,
		const std::tuple<float, float>& healRange,
		float healCoefficient,
		Descriptors descriptors,
		bool allowMultipliers,
		bool ignoreCritical
	) {
		if (!HasCombatantData()) {
			return { 0.f, false };
		}

		float value = utils::random::get<float>(std::get<0>(healRange), std::get<1>(healRange));
		bool critical = false;

		if (allowMultipliers) {
			float multiplier = 1.f;

			uint8_t attackerPlayerIndex = 0xFF;
			if (attackerAttributes) {
				const auto& attackerOwner = attackerAttributes->GetOwnerObject();
				if (attackerOwner) {
					attackerPlayerIndex = attackerOwner->GetPlayerIndex();
					if (attackerPlayerIndex != 0xFF) {
						healCoefficient *= attackerOwner->GetPrimaryAttributeValue() - magicNumbers[13];
					}
				}

				multiplier += attackerAttributes->GetValue(AttributeType::HealIncrease);
				if (utils::enum_helper<Descriptors>::test(descriptors, Descriptors::IsHoT)) {
					multiplier += attackerAttributes->GetValue(AttributeType::HoTDoneIncrease);
				}
			}

			value *= multiplier * (healCoefficient + 1.f);
			if (!ignoreCritical) {
				critical = CheckCritical(attackerAttributes);
				if (critical) {
					value *= magicNumbers[12];
				}
			}
		}

		value *= 1.f - GetAttributeValue(AttributeType::HealingReduction);

		float maxHealth = GetMaxHealth();
		float health = GetHealth();

		SetHealth(health + value);
		if (value > 0) {


// Check if we should resurrect.
if (health <= 0) {
	// SendResurrectEvent();
	OnResurrect();
}
		}

		float remainder = std::max<float>(0.f, health - maxHealth);
		if (remainder > 0 && GetPlayerIndex() != 0xFF) {
			DistributeDamageAmongSquad(remainder);
		}

		return { value, critical };
	}

	bool Object::CheckCritical(const AttributesPtr& attackerAttributes) const {
		if (!attackerAttributes) {
			return false;
		}

		if (attackerAttributes->GetValue(AttributeType::AutoCrit) > 0) {
			return true;
		}

		const auto& attacker = attackerAttributes->GetOwnerObject();
		if (!attacker) {
			return false;
		}

		float value = 1.f;
		if (attacker->GetPlayerIndex() != 0xFF) {
			// value = DifficultyTuning::RatingConversion[0] - 4 + difficulty * 4;
		}

		return utils::random::get<float>(0.f, 1.f) < (attackerAttributes->GetValue(AttributeType::CriticalRating) / (value * 100.f));
	}

	void Object::DistributeDamageAmongSquad(float damage) {
		float distribute = GetAttributeValue(AttributeType::DistributeDamageAmongSquad);
		if (distribute <= 0) {
			return;
		}

		//
	}

	int32_t Object::CanUseAbility(
		const AbilityPtr& ability,
		uint32_t abilityIndex,
		int32_t rank,
		const ObjectPtr& target,
		const glm::vec3& targetPosition
	) {
		if (!ability) {
			return -9984;
		}

		if (rank > 7) {
			// Rank cannot be higher than 7?
			return -9994;
		}

		if (IsPlayerControlled()) {
			const auto& player = GetPlayer();
			if (player) {
				if (player->IsAbilityLocked(abilityIndex)) {
					return -9988;
				}

				if (abilityIndex >= 6) {
					const auto& character = player->GetCharacter(abilityIndex - 6);
					if (character.GetHealth() <= 0) {
						return -9990;
					}
				}
			}
		}

		const auto descriptors = utils::enum_wrapper { ability->GetDescriptors() };
		if (descriptors.test(Game::Descriptors::IsBasic)) {
			if (target && target->GetHealth() <= 0) {
				return -9989;
			}
		} else {
			if (GetAttributeValue(AttributeType::Silence) != 0) {
				return -9993;
			}
		}

		// Cooldown
		if (HasCooldown(ability->GetId())) {
			return -10000;
		}

		// Get scaling attribute
		auto scalingAttribute = utils::enum_wrapper { ability->GetScalingAttribute() };
		if (scalingAttribute.value() == decltype(scalingAttribute)().bnot().value()) {
			scalingAttribute = static_cast<AttributeType>(GetPrimaryAttribute());
		}

		const auto& self = shared_from_this();

		// TODO: probably not use shared_from_this here somehow.
		float attributeValue = GetAttributeValue(scalingAttribute);
		// also check object player index?
		if (GetMana() < ability->GetManaCost(self, rank, attributeValue)) {
			return -9997;
		}
		
		if (!ability->IsInRange(self, target, targetPosition, rank)) {
			return ability->ShouldPursue();
		}

		if (ability->IsAbleToHit(self, target, targetPosition, rank)) {
			//
		}

		return 0;
	}

	void Object::RequestAbility(const AbilityPtr& ability, const ObjectPtr& attacker) {
		// auto value = CanUseAbility(ability);
		// if (value != 0) {
		// 	return;
		// }

		// if (ability->RequiresAgent()) {

		// }


	}

	void Object::RequestModifier(const ObjectPtr& attacker) {

	}

	void Object::OnChangeHealth(float healthChange) {
		// TODO: Add scripting event (lua)
		SetHealth(GetHealth() + healthChange);
	}

	void Object::OnChangeMana(float manaChange) {
		// TODO: Add scripting event (lua)
		SetMana(GetMana() + manaChange);
	}

	void Object::OnDeath() {
		//
	}

	void Object::OnResurrect() {
		// Set corpse state to "Not dead"
		if (HasCombatantData()) {
			mCombatantData->mCorpseState = CorpseState::Alive;
		}

		// If we have a noun then...
		if (!mNoun) {
			return;
		}

		// Restart any passive ability
		if (IsPlayerControlled()) {
			const auto& playerClassData = mNoun->GetPlayerClassData();
			if (playerClassData) {
				const auto abilityId = playerClassData->GetAbility(PlayerAbility::Passive);
				if (abilityId != 0) {
					// RequestModifier(abilityId, etc);
				}
			}
		} else {
			const auto& aiDefinition = mNoun->GetAIDefinition();
			if (aiDefinition) {
				const auto abilityId = aiDefinition->GetPassiveAbility();
				if (abilityId != 0) {
					// RequestModifier(abilityId, etc);
				}
			}
		}
	}

	// Interactable data
	bool Object::HasInteractableUsesLeft() const {
		if (mNoun) {
			if (mNoun->GetDoorData() != nullptr ||
				mNoun->GetSwitchData() != nullptr ||
				mNoun->GetPressureSwitchData() != nullptr
			) {
				return true;
			}
		}

		if (HasInteractableData()) {
			return mInteractableData->GetTimesUsed() < mInteractableData->GetUsesAllowed();
		}
		return false;
	}

	// Agent Blackboard
	uint32_t Object::GetTargetId() const {
		return HasAgentBlackboardData() ? mAgentBlackboardData->GetTargetId() : 0;
	}

	void Object::SetTargetId(uint32_t id) {
		if (HasAgentBlackboardData()) {
			mAgentBlackboardData->SetTargetId(id);
		}
	}

	StealthType Object::GetStealthType() const {
		return HasAgentBlackboardData() ? mAgentBlackboardData->GetStealthType() : StealthType::None;
	}

	void Object::SetStealthType(StealthType stealthType) {
		if (HasAgentBlackboardData()) {
			mAgentBlackboardData->SetStealthType(stealthType);
		}
	}

	bool Object::IsInCombat() const {
		return HasAgentBlackboardData() ? mAgentBlackboardData->IsInCombat() : 0;
	}

	void Object::SetInCombat(bool inCombat) {
		if (HasAgentBlackboardData()) {
			mAgentBlackboardData->SetInCombat(inCombat);
		}
	}

	bool Object::IsTargetable() const {
		return HasAgentBlackboardData() ? mAgentBlackboardData->IsTargetable() : 0;
	}

	void Object::SetTargetable(bool targetable) {
		if (HasAgentBlackboardData()) {
			mAgentBlackboardData->SetTargetable(targetable);
		}
	}

	// Network & reflection
	void Object::WriteTo(RakNet::BitStream& stream) const {
		// This seems unused.

		using RakNet::bytes_to_bits;
		using RakNet::ReallocateStream;

		constexpr auto size = bytes_to_bits(0x308);
		const auto writeOffset = ReallocateStream(stream, size);

		// Find a nicer solution but... just dont store an extra int because i dont wanna.
		const auto& owner = GetOwnerObject();

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x010));
		Write<float>(stream, mScale);
		Write<float>(stream, mMarkerScale);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x018));
		Write(stream, GetPosition());
		Write(stream, mOrientation);
		Write(stream, mLinearVelocity);
		Write(stream, mAngularVelocity);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x050));
		Write<uint32_t>(stream, owner ? owner->GetId() : 0);
		Write<uint8_t>(stream, mTeam);
		Write<uint8_t>(stream, mPlayerIndex);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x058));
		Write<uint32_t>(stream, mInputSyncStamp);
		Write<bool>(stream, mbPlayerControlled);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x05F));
		Write<bool>(stream, mVisible);
		Write<bool>(stream, mbHasCollision);
		Write<uint8_t>(stream, static_cast<uint8_t>(mMovementType));

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x088));
		Write(stream, mMarkerId);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x0AC));
		Write(stream, mLastAnimationState);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x0B8));
		Write(stream, mLastAnimationPlayTime);
		Write(stream, mOverrideMoveIdleAnimationState);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x258));
		Write(stream, mGraphicsState);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x260));
		Write(stream, mGraphicsStateStartTime);
		Write(stream, mNewGraphicsStateStartTime);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x284));
		Write(stream, mDisableRepulsion);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x288));
		Write(stream, mInteractableState);

		stream.SetWriteOffset(writeOffset + size);
	}

	void Object::WriteReflection(RakNet::BitStream& stream) const {
		RakNet::reflection_serializer<23> reflector(stream);
		reflector.begin();
		if (mDataBits.any()) {
			if (mDataBits.test(0)) { reflector.write<0>(mTeam); }
			if (mDataBits.test(1)) { reflector.write<1>(mbPlayerControlled); }
			if (mDataBits.test(2)) { reflector.write<2>(mInputSyncStamp); }
			if (mDataBits.test(3)) { reflector.write<3>(mPlayerIndex); }
			if (mDataBits.test(4)) { reflector.write<4>(mLinearVelocity); }
			if (mDataBits.test(5)) { reflector.write<5>(mAngularVelocity); }
			if (mDataBits.test(6)) { reflector.write<6>(GetPosition()); }
			if (mDataBits.test(7)) { reflector.write<7>(mOrientation); }
			if (mDataBits.test(8)) { reflector.write<8>(mScale); }
			if (mDataBits.test(9)) { reflector.write<9>(mMarkerScale); }
			if (mDataBits.test(10)) { reflector.write<10>(mLastAnimationState); }
			if (mDataBits.test(11)) { reflector.write<11>(mLastAnimationPlayTime); }
			if (mDataBits.test(12)) { reflector.write<12>(mOverrideMoveIdleAnimationState); }
			if (mDataBits.test(13)) { reflector.write<13>(mGraphicsState); }
			if (mDataBits.test(14)) { reflector.write<14>(mGraphicsStateStartTime); }
			if (mDataBits.test(15)) { reflector.write<15>(mNewGraphicsStateStartTime); }
			if (mDataBits.test(16)) { reflector.write<16>(mVisible); }
			if (mDataBits.test(17)) { reflector.write<17>(mbHasCollision); }

			if (mDataBits.test(18)) {
				const auto& owner = GetOwnerObject();
				reflector.write<18>(owner ? owner->GetId() : 0);
			}

			if (mDataBits.test(19)) { reflector.write<19>(mMovementType); }
			if (mDataBits.test(20)) { reflector.write<20>(mDisableRepulsion); }
			if (mDataBits.test(21)) { reflector.write<21>(mInteractableState); }
			if (mDataBits.test(22)) { reflector.write<22>(mMarkerId); }
		}
		reflector.end();
	}

	void Object::ResetUpdateBits() {
		mDataBits.reset();
	}

	bool Object::NeedUpdate() const {
		return (mFlags & Object::UpdateFlags) || mDataBits.any();
	}

	uint16_t Object::GetFlags() const {
		return mFlags;
	}

	void Object::SetFlags(uint16_t flags) {
		mFlags = static_cast<Flags>(flags);
	}
}
