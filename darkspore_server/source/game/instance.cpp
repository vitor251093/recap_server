
// Include
#include "instance.h"

#include "objectmanager.h"
#include "lua.h"
#include "serverevent.h"
#include "catalyst.h"
#include "scheduler.h"

#include "raknet/server.h"
#include "sporenet/instance.h"
#include "sporenet/user.h"
#include "utils/functions.h"

#include <iostream>
#include <array>

/*
	eeh... maybe not

	TODO: Rename Game namespace to SporeNet? Same for RakNet?
		Game -> SporeNet
		RakNet -> SporeNet
*/

// Game
namespace Game {
	// CashOutData
	void CashOutData::WriteTo(RakNet::BitStream& stream) const {
		using RakNet::bytes_to_bits;
		using RakNet::ReallocateStream;

		constexpr auto size = bytes_to_bits(0x2C8);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x00));
		Write(stream, mPlanetsCompleted);
		Write(stream, mDna);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x34));
		for (const auto medalCount : mGoldMedals) { Write(stream, medalCount); }
		for (const auto medalCount : mSilverMedals) { Write(stream, medalCount); }
		for (const auto medalCount : mBronzeMedals) { Write(stream, medalCount); }

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x64));
		for (const auto chance : mUniqueChances) { Write(stream, chance); }
		for (const auto chance : mRareChances) { Write(stream, chance); }

		stream.SetWriteOffset(writeOffset + size);
	}

	// Instance
	InstancePtr Instance::Create(uint32_t id) {
		return InstancePtr(new Instance(id));
	}

	Instance::Instance(uint32_t id) {
		mData.id = id;

		constexpr std::array<std::string_view, 5> objectiveTypes {
			"FinishLevelQuickly",
			"DoDamageOften",
			"TouchAllObelisks",
			"DefeatAllMonsters",
			"HugeDamage"
		};

		for (const auto& objectiveName : objectiveTypes) {
			decltype(auto) objective = mObjectives.emplace_back();
			objective.id = utils::hash_id(objectiveName);
			objective.value = 1;
			objective.medal = RakNet::ObjectiveMedal::Gold;
			objective.description = "Do some stuff bruh";
		}
	}

	Instance::~Instance() {
		Stop();
	}

	bool Instance::Start() {
		Stop();

		mObjectManager = std::make_unique<ObjectManager>(*this);
		mLua = std::make_unique<Lua>(*this);
		mServer = std::make_unique<RakNet::Server>(*this);

		mServer->start(mData.hostNetwork.exip.port);
		mGameStartTime = utils::get_milliseconds();

		mServer->add_task([this] {
			mLua->Initialize();
		});
		return true;
	}

	void Instance::Stop() {
		if (!mEvents.empty()) {
			auto& scheduler = GetApp().GetScheduler();
			for (uint32_t id : mEvents) {
				scheduler.CancelTask(id);
			}
		}

		mEvents.clear();
		if (mServer && mServer->is_running()) {
			mServer->stop();
			// wait until it stops
		}

		mServer.reset();
		mLua.reset();
		mObjectManager.reset();
	}

	bool Instance::LoadLevel() {
		if (mLevelLoaded) {
			return true;
		}

		std::string levelName = mChainData.GetName().data();
		mLevelLoaded = mLevel.Load(mChainData.GetDifficultyName(), levelName);
		if (mLevelLoaded) {
			LevelConfig config;
			if (mChainData.IsCompleted()) {
				config = mLevel.GetConfig();
			} else {
				config = mLevel.GetFirstTimeConfig();
			}

			const auto& nounDatabase = NounDatabase::Instance();
			for (uint32_t i = 0; i < 3; ++i) {
				const auto& minion = config.GetMinion(i);
				mChainData.SetEnemyNoun(minion.GetNounName(), i);

				const auto& special = config.GetSpecial(i);
				mChainData.SetEnemyNoun(special.GetNounName(), i + 3);

				auto noun = nounDatabase.Get(utils::hash_id(minion.GetNounName()));
				if (auto npcData = noun->GetNonPlayerClassData()) {
					std::cout << npcData->GetName() << std::endl;
				}

				noun = nounDatabase.Get(utils::hash_id(special.GetNounName()));
				if (auto npcData = noun->GetNonPlayerClassData()) {
					std::cout << npcData->GetName() << std::endl;
				}
			}

			Markerset markerset;
			if (mLevel.GetMarkerset(levelName + "_design.Markerset", markerset)) {
				const auto& markers = markerset.GetMarkersByType(utils::hash_id("CameraSpawnPoint.Noun"));
				for (const auto& marker : markers) {
					mPlayerSpawnpoints.push_back(marker->GetPosition());
				}
			}

			// Check design_spawners
			if (mPlayerSpawnpoints.empty()) {
				if (mLevel.GetMarkerset(levelName + "_design_spawners.Markerset", markerset)) {
					const auto& markers = markerset.GetMarkersByType(utils::hash_id("CameraSpawnPoint.Noun"));
					for (const auto& marker : markers) {
						mPlayerSpawnpoints.push_back(marker->GetPosition());
					}
				}
			}
		}

		return mLevelLoaded;
	}

	MarkerPtr Instance::GetMarker(uint32_t id) const {
		auto it = mMarkers.find(id);
		return (it != mMarkers.end()) ? it->second : nullptr;
	}

	PlayerPtr Instance::GetPlayer(int64_t id) const {
		auto it = mPlayers.find(id);
		return (it != mPlayers.end()) ? it->second : nullptr;
	}

	PlayerPtr Instance::GetPlayerByIndex(uint8_t index) const {
		for (const auto& [_, player] : mPlayers) {
			if (player->GetId() == index) {
				return player;
			}
		}
		return nullptr;
	}

	PlayerPtr Instance::AddPlayer(const SporeNet::UserPtr& user, uint8_t index) {
		if (!user) {
			return nullptr;
		}

		auto it = mPlayers.try_emplace(user->get_id());
		if (it.second) {
			it.first->second = std::make_shared<Player>(*this, user, index);
		}

		return it.first->second;
	}

	void Instance::RemovePlayer(int64_t id) {
		mPlayers.erase(id);
	}

	uint32_t Instance::GetId() const {
		return mData.id;
	}

	uint64_t Instance::GetTime() const {
		return mGameTime;
	}

	uint64_t Instance::GetTimeElapsed() const {
		return utils::get_milliseconds() - mGameStartTime;
	}

	ObjectManager& Instance::GetObjectManager() {
		return *mObjectManager;
	}

	const ObjectManager& Instance::GetObjectManager() const {
		return *mObjectManager;
	}

	Lua& Instance::GetLua() {
		return *mLua;
	}

	const Lua& Instance::GetLua() const {
		return *mLua;
	}
	
	void Instance::AddServerTask(std::function<void(void)> task) {
		mServer->add_task(std::move(task));
	}

	void Instance::AddClientTask(uint8_t id, RakNet::PacketID packet) {
		mServer->add_client_task(id, packet);
	}

	void Instance::OnObjectCreate(const ObjectPtr& object) {
		//
	}

	void Instance::OnObjectDestroy(const ObjectPtr& object) {
		//
	}

	void Instance::OnObjectDeath(const ObjectPtr& object, bool critical, bool knockback) {
		if (!object) {
			return;
		}

		SendObjectGfxState(object, utils::hash_id("dead"));

		const auto& noun = object->GetNoun();
		if (noun) {
			if (noun->IsCreature()) {
				object->SetHasCollision(false);
			}

			const auto& animation = noun->GetCharacterAnimation();
			if (animation) {
				uint32_t deathState = 0;
				if (critical) {
					// replace 0 with damage type
					uint8_t type = 0 * static_cast<uint8_t>(critical);
					type += static_cast<uint8_t>(knockback);

					std::tie(deathState, std::ignore) = animation->GetAnimationData(
						utils::enum_helper<CharacterAnimationType>::next(CharacterAnimationType::MeleeCriticalDeath, type)
					);
				} else {
					std::tie(deathState, std::ignore) = animation->GetAnimationData(CharacterAnimationType::MeleeDeath);
				}

				if (deathState == 0) {
					std::tie(deathState, std::ignore) = animation->GetAnimationData(CharacterAnimationType::Death);
				}

				if (deathState != 0) {
					SendAnimationState(object, deathState);
				}
			}

			if (critical) {
				object->MarkForDeletion();
			}
		}
	}

	void Instance::OnPlayerStart(const PlayerPtr& player) {
		std::cout << "Player Start" << std::endl;

		mLua->PreloadAbilities();
		mGameStarted = LoadLevel();

		if (mGameStarted) {
			std::string levelName = mChainData.GetName().data();

			// create level objects and whatnot
			Markerset markerset;
			if (mLevel.GetMarkerset(levelName + "_obelisk_1.Markerset", markerset)) {
				const auto& healthObelisks = markerset.GetMarkersByType(utils::hash_id("prefab_health_obelisk.Noun"));
				for (const auto& marker : healthObelisks) {
					mObjectManager->Create(marker);
				}

				const auto& bossObelisks = markerset.GetMarkersByType(utils::hash_id("prefab_boss_obelisk.Noun"));
				for (const auto& marker : bossObelisks) {
					mObjectManager->Create(marker);
				}
			}

			constexpr std::array<const char*, 2> designSets { "_design", "_design_spawners" };
			for (const char* designSet : designSets) {
				if (mLevel.GetMarkerset(levelName + designSet + ".Markerset", markerset)) {
					for (const auto& marker : markerset.GetMarkers()) {
						mMarkers[marker->GetId()] = marker;

						const auto& teleporterData = marker->GetTeleporterData();
						if (teleporterData) {
							mObjectManager->Create(marker);
						}
					}
				}
			}

			const auto TestEnemy = [this](const auto& markerset) {
				for (const auto& marker : markerset.GetMarkers()) {
					mMarkers[marker->GetId()] = marker;

					switch (marker->GetNoun()) {
						case utils::hash_id("SpawnPoint_Director.Noun"):
						case utils::hash_id("SpawnPoint_DirectorA.Noun"):
						case utils::hash_id("SpawnPoint_DirectorB.Noun"):
						case utils::hash_id("SpawnPoint_DirectorWanderer.Noun"):
						{
							const auto& object = mObjectManager->Create(mChainData.GetEnemyNoun(utils::random::get<uint32_t>(0, 5)));
							if (object) {
								object->SetPosition(marker->GetPosition());
								object->SetOrientation(marker->GetRotation());
							}
							break;
						}

						default:
						{
							std::cout << "Unknown enemy noun: '" << marker->GetNounName() << "'" << std::endl;
							break;
						}
					}

					// temporary
					break;
				}
			};

			if (mLevel.GetMarkerset(levelName + "_AI_Wander.Markerset", markerset)) {
				TestEnemy(markerset);
			}
			
			if (mLevel.GetMarkerset(levelName + "_AI_WandererA.Markerset", markerset) || mLevel.GetMarkerset(levelName + "_AI_Wanderers_A.Markerset", markerset)) {
				TestEnemy(markerset);
			}

			if (mLevel.GetMarkerset(levelName + "_AI_WandererB.Markerset", markerset) || mLevel.GetMarkerset(levelName + "_AI_Wanderers_B.Markerset", markerset)) {
				TestEnemy(markerset);
			}

			if (mLevel.GetMarkerset(levelName + "_AI_WandererC.Markerset", markerset) || mLevel.GetMarkerset(levelName + "_AI_Wanderers_C.Markerset", markerset)) {
				TestEnemy(markerset);
			}
			
		}

		// mLua->LoadFile("data/lua/player_start.lua");

		// Set objectives
		const auto& client = mServer->GetClient(player->GetId());
		if (client) {
			mServer->SendObjectivesInitForLevel(client);
			for (uint8_t i = 0, l = static_cast<uint8_t>(mObjectives.size()); i < l; ++i) {
				mServer->SendObjectiveUpdate(client, i, 0);
			}

			// Create all existing objects
			for (const auto& object : mObjectManager->GetActiveObjects()) {
				// Create object in client
				SendObjectCreate(object);

				// Apply effects

			}
		}

		// Create creatures
		glm::vec3 spawnpoint;
		if (player->GetId() < mPlayerSpawnpoints.size()) {
			spawnpoint = mPlayerSpawnpoints[player->GetId()];
		}

		// Force send character objects so the client can find them when swapping.
		for (uint32_t i = 0; i < 3; ++i) {
			const auto& characterObject = player->GetCharacterObject(i);
			if (!characterObject) {
				continue;
			}

			characterObject->SetPosition(spawnpoint);
			characterObject->SetVisible(true); // i == creatureIndex

			characterObject->SetAttributeValue(AttributeType::InvisibleToSecurityTeleporters, 1);
			characterObject->SetAttributeValue(AttributeType::AttackSpeedScale, 1);
			characterObject->SetAttributeValue(AttributeType::CooldownScale, 1);

			SendObjectUpdate(characterObject);
		}
	}

	uint32_t Instance::AddTask(uint32_t delay, std::function<void(uint32_t)> task) {
		auto id = GetApp().GetScheduler().AddTask(delay, task);
		mEvents.insert(id);
		return id;
	}

	void Instance::CancelTask(uint32_t id) {
		GetApp().GetScheduler().CancelTask(id);
		mEvents.erase(id);
	}

	bool Instance::ServerUpdate() const {
		return (utils::get_milliseconds() - mGameTime) >= 10;
	}

	bool Instance::Update() {
		// It is safe to send packets in this function.
		auto newGameTime = utils::get_milliseconds();

		if (auto delta = (newGameTime - mGameTimeLua); delta >= 1) {
			mGameTimeLua = newGameTime;
			mLua->Update();
		}

		if (auto delta = (newGameTime - mGameTime); delta >= 50) {
			mGameTime = newGameTime;
			mObjectManager->Update(delta / 1000.f); // Maybe send update time so we can compensate for lag?
			for (const auto& [_, player] : mPlayers) {
				SendLabsPlayerUpdate(player);
			}

			const auto& client = mServer->GetClient(static_cast<uint8_t>(0));
			if (client) {
				auto& objective = mObjectives.front();
				if (objective.id == utils::hash_id("FinishLevelQuickly")) {
					objective.value = static_cast<uint32_t>(GetTimeElapsed() / 1000);
					mServer->SendObjectiveUpdate(client, 0, utils::hash_id("vo_ship_obelisk_accessed"));
				}
			}

			return true;
		}

		return false;
	}

	void Instance::MoveObject(const ObjectPtr& object, const Locomotion& locomotionData) {
		if (!object) {
			return;
		}

		const auto goalFlags = locomotionData.GetGoalFlags();
		if (goalFlags & 0x002) {
			object->SetOrientation(glm::quat(locomotionData.GetFacing()));
		}

		bool teleport = goalFlags & 0x020;
		if (teleport) {
			object->SetPosition(locomotionData.GetGoalPosition());
			for (const auto& [_, client] : mServer->GetClients()) {
				mServer->SendObjectTeleport(client, object, object->GetPosition(), object->GetOrientation());
			}
		} else {
			object->SetPosition(locomotionData.GetPartialGoalPosition());
			for (const auto& [_, client] : mServer->GetClients()) {
				mServer->SendObjectPlayerMove(client, object, locomotionData);
			}
		}
	}

	void Instance::UseAbility(const ObjectPtr& object, const RakNet::CombatData& combatData) {
		if (!object) {
			return;
		}

		if (object->HasCooldown(combatData.abilityId)) {
			return;
		}

		const auto& ability = mLua->GetAbility(combatData.abilityId);
		if (ability) {
			// ability:tick(object, target, cursorPosition, rank)
			ability->Tick(object, mObjectManager->Get(combatData.targetId), combatData.cursorPosition, combatData.abilityRank);
		}
	}

	void Instance::SwapCharacter(const PlayerPtr& player, uint32_t creatureIndex) {
		if (!player) {
			return;
		}

		// TODO: proper functions for these things
		if (!player->SwapCharacter(creatureIndex)) {
			return;
		}

		// set player current creature
		for (const auto& [_, client] : mServer->GetClients()) {
			mServer->SendPlayerCharacterDeploy(client, player, creatureIndex);
		}

		SendLabsPlayerUpdate(player);
	}

	void Instance::InteractWithObject(const PlayerPtr& player, uint32_t objectId) {
		if (!player) {
			return;
		}

		const auto& object = mObjectManager->Get(objectId);
		if (!object || object->IsMarkedForDeletion()) {
			return;
		}

		// Check for interactable ability

		const auto& interactableData = object->GetInteractableData();
		if (interactableData) {
			interactableData->SetTimesUsed(interactableData->GetTimesUsed() + 1);
		}

		const auto& noun = object->GetNoun();
		if (noun) {
			switch (noun->GetType()) {
				case NounType::Loot:
					PickupLoot(player, object);
					break;

				case NounType::Crystal:
					PickupCatalyst(player, object);
					break;

				default:
					const auto& characterObject = player->GetDeployedCharacterObject();
					DropLoot(characterObject, characterObject, utils::enum_helper<DropType>::bor(DropType::Catalysts, DropType::Orbs));
					break;
			}
		} else {
			const auto& characterObject = player->GetDeployedCharacterObject();
			DropLoot(characterObject, characterObject, utils::enum_helper<DropType>::bor(DropType::Catalysts, DropType::Orbs));
		}
	}

	void Instance::CancelAction(const PlayerPtr& player, const ObjectPtr& object) {
		// TODO: Change this to not force lua updates
		if (!player || !object) {
			return;
		}

		auto luaThread = object->GetLuaThread();
		if (!luaThread) {
			// No active action
			return;
		}

		luaThread->stop();
		/*
		sol::table privateTable = mLua->GetPrivateTable(object->GetId());
		if (privateTable == sol::nil) {
			return;
		}

		if (sol::object action = privateTable["CURRENT_ACTION"]; action.is<uint32_t>()) {
			CancelTask(action.as<uint32_t>());
			privateTable["CURRENT_ACTION"] = sol::nil;
		}
		*/
	}

	void Instance::DropLoot(const PlayerPtr& player, uint64_t lootInstanceId) {
		if (!player) {
			return;
		}

		const auto& user = player->GetUser();
		if (!user) {
			return;
		}

		// get temporary part and drop
	}

	void Instance::DropLoot() {
		constexpr std::array<std::string_view, 4> dropRarityNouns {
			"loot_container_white.Noun",
			"loot_container_green.Noun",
			"loot_drop.noun",
			"loot_container_purple.Noun"
		};

		const auto& clients = mServer->GetClients();
		if (clients.empty()) {
			return;
		}

		auto firstClient = clients.begin()->second;
		auto player = firstClient->GetPlayer();
		auto characterObject = player->GetCharacterObject(1);

		auto position = characterObject->GetPosition();

		static uint64_t lootId = 0;
		for (uint32_t i = 0; i < 4; ++i) {
			auto part = SporeNet::Part(i);
			part.SetRarity(static_cast<SporeNet::PartRarity>(i));

			//
			auto containerType = static_cast<int32_t>(part.GetRarity());
			if (containerType >= dropRarityNouns.size()) {
				containerType = 0;
			}

			auto object = mObjectManager->Create(utils::hash_id(dropRarityNouns[containerType]));
			object->SetPosition(position);
			object->SetInteractableState(0);
			
			const auto& lootData = object->CreateLootData();
			lootData->SetId(++lootId);
			lootData->SetInstanceId(lootId);
			lootData->SetPart(part);

			const auto& interactableData = object->CreateInteractableData();
			interactableData->SetUsesAllowed(1);
			interactableData->SetTimesUsed(0);
			interactableData->SetAbility(utils::hash_id("PickUpLoot"));

			if (SendObjectCreate(object)) {
				for (const auto& [_, client] : clients) {
					mServer->SendLootDataUpdate(client, object, *lootData);
					mServer->SendInteractableDataUpdate(client, object, *interactableData);
				}
			}

			mObjects.push_back(std::move(object));
			position.x += 5;
		}
	}

	void Instance::DropLoot(const ObjectPtr& object, const ObjectPtr& targetObject, DropType dropType) {
		if (!object || !targetObject) {
			return;
		}

		const auto& interactableData = object->GetInteractableData();
		if (interactableData) {

		}

		const auto& position = object->GetPosition(); // client uses "GetClosestPosition" but no way in hell im implementing that.
		const auto& footprintRadius = object->GetFootprintRadius();
		if (utils::enum_helper<DropType>::test(dropType, DropType::Orbs)) {
			float orbDifficultyScale;
			if (mChainData.GetLevelIndex() < 72) {
				orbDifficultyScale = 5.f;
			} else {
				orbDifficultyScale = 1.f;
			}

			uint32_t orbType = 1;
			uint32_t orbServerEvent = 0;
			switch (orbType) {
				case 1:
					orbType = utils::hash_id("HealthOrb.Noun");
					orbServerEvent = utils::hash_id("health_orb_drop.ServerEventDef");
					break;

				case 2:
					orbType = utils::hash_id("ManaOrb.Noun");
					orbServerEvent = utils::hash_id("mana_orb_drop.ServerEventDef");
					break;

				case 3:
					orbType = utils::hash_id("ResurrectOrb.Noun");
					orbServerEvent = utils::hash_id("resurrect_orb_drop.ServerEventDef");
					break;
			}

			if (orbType) {
				ServerEvent serverEvent;
				serverEvent.mServerEventDef = orbServerEvent;
				serverEvent.mTargetPoint = position;

				const auto& object = mObjectManager->Create(orbType);
				object->SetPosition(position);

				SendObjectCreate(object);
				SendServerEvent(serverEvent);
			}
		}

		if (utils::enum_helper<DropType>::test(dropType, DropType::Catalysts)) {
			auto crystalFind = targetObject->GetAttributeValue(AttributeType::CrystalFind);
			switch (object->GetTeam()) {
				case 2:
					break;

				default:
					break;
			}

			static uint64_t test_id = 0;

			Catalyst catalyst(CatalystType::AttackSpeed, CatalystRarity::Common, false);

			const auto& object = mObjectManager->Create(catalyst.GetNounId());
			object->SetPosition(position);

			const auto& lootData = object->CreateLootData();
			lootData->SetId(++test_id);
			lootData->SetCatalyst(catalyst);

			const auto& interactableData = object->CreateInteractableData();
			interactableData->SetUsesAllowed(1);
			interactableData->SetTimesUsed(0);
			interactableData->SetAbility(utils::hash_id("PickUpLoot"));

			SendObjectCreate(object);
		}

		if (utils::enum_helper<DropType>::test(dropType, DropType::DNA)) {
			//
		}

		if (utils::enum_helper<DropType>::test(dropType, DropType::Loot)) {
			//
		}
	}

	void Instance::DropCatalyst(const PlayerPtr& player, uint32_t catalystSlot) {
		if (!player) {
			return;
		}

		auto characterObject = player->GetDeployedCharacterObject();
		if (!characterObject) {
			return;
		}

		auto catalyst = player->GetCatalyst(catalystSlot);
		if (!catalyst) {
			return;
		}

		player->SetCatalyst(Catalyst(), catalystSlot);
		{
			static uint64_t lootId = 0;

			auto object = mObjectManager->Create(catalyst.GetNounId());
			object->SetPosition(characterObject->GetPosition());
			object->SetInteractableState(0);

			const auto& lootData = object->CreateLootData();
			lootData->SetId(++lootId);
			lootData->SetCatalyst(catalyst);

			const auto& interactableData = object->CreateInteractableData();
			interactableData->SetUsesAllowed(1);
			interactableData->SetTimesUsed(0);
			interactableData->SetAbility(utils::hash_id("PickUpLoot"));

			SendObjectCreate(object);
		}
	}

	void Instance::DropCatalyst() {
		const auto& clients = mServer->GetClients();
		if (clients.empty()) {
			return;
		}

		const auto& firstClient = clients.begin()->second;
		const auto& player = firstClient->GetPlayer();

		auto characterObject = player->GetDeployedCharacterObject();
		if (!characterObject) {
			return;
		}

		auto position = characterObject->GetPosition();

		static uint64_t lootId = 0;
		for (uint32_t i = 0; i < 4; ++i) {
			Catalyst catalyst(static_cast<CatalystType>(i), static_cast<CatalystRarity>(i % 3), i & 1);

			auto object = mObjectManager->Create(catalyst.GetNounId());
			object->SetPosition(position);
			object->SetInteractableState(0);

			const auto& lootData = object->CreateLootData();
			lootData->SetId(++lootId);
			lootData->SetCatalyst(catalyst);

			const auto& interactableData = object->CreateInteractableData();
			interactableData->SetUsesAllowed(1);
			interactableData->SetTimesUsed(0);
			interactableData->SetAbility(utils::hash_id("PickUpLoot"));

			if (SendObjectCreate(object)) {
				for (const auto& [_, client] : clients) {
					mServer->SendLootDataUpdate(client, object, *lootData);
					mServer->SendInteractableDataUpdate(client, object, *interactableData);
				}
			}

			mObjects.push_back(std::move(object));
			position.x += 5;
		}
	}

	void Instance::BeamOut(const PlayerPtr& player) {
		const auto& client = mServer->GetClient(player->GetId());
		if (client) {
			mChainData.SetCompleted(true);
			mChainData.SetProgression(1);

			mCashOutData.mDna = 50;
			mCashOutData.mPlanetsCompleted = 2;
			mCashOutData.mGoldMedals.fill(3);
			mCashOutData.mSilverMedals.fill(1);
			mCashOutData.mBronzeMedals.fill(4);
			mCashOutData.mUniqueChances.fill(50);
			mCashOutData.mRareChances.fill(30);

			mServer->SendReconnectPlayer(client, GameState::ChainVoting);
			mServer->SendDebugPing(client);
		}

		/*
		ClientEvent cashOutEvent;
		cashOutEvent.SetEventId(ClientEventID::PlayerCashOut);

		SendServerEvent(player, cashOutEvent);
		*/
	}

	/*
		HealthOrb.noun - Orb_Pickup
		HealthOrbPlaced.noun - Orb_Pickup
		JuggernautOrb.noun - Juggernaut_Pickup
		Loot_drop.noun - PickupLoot
		loot_questCrystal.noun - PickupQuestCrystal
		ManaOrb.noun - Orb_Pickup
		ManaOrbPlaced.noun - Orb_Pickup
		ResurrectOrb.noun - PickupResurrectOrb
		DNA.noun - DNA_Pickup
	*/

	bool Instance::SendObjectCreate(const ObjectPtr& object) {
		if (!object) {
			return false;
		}
#if 0
		for (const auto& [_, client] : mServer->GetClients()) {
			mServer->SendObjectCreate(client, object);
		}
#else
		if (!mGameStarted) {
			return false;
		}

		auto flags = object->GetFlags();
		if (flags & Object::Created) {
			return true;
		}

		for (const auto& [_, client] : mServer->GetClients()) {
			mServer->SendObjectCreate(client, object);
		}

		object->SetFlags(flags | Object::Created);
		object->ResetUpdateBits();
#endif
		return true;
	}

	void Instance::SendObjectDelete(const ObjectPtr& object) {
		for (const auto& [_, client] : mServer->GetClients()) {
			mServer->SendObjectDelete(client, object);
		}
	}

	void Instance::SendObjectDelete(const std::vector<ObjectPtr>& objects) {
		for (const auto& [_, client] : mServer->GetClients()) {
			mServer->SendObjectDelete(client, objects);
		}
	}

	void Instance::SendObjectUpdate(const ObjectPtr& object) {
		if (!SendObjectCreate(object)) {
			return;
		}

		auto flags = object->GetFlags();
		auto newFlags = flags;

		for (const auto& [_, client] : mServer->GetClients()) {
			const auto& player = client->GetPlayer();
			if (object == player->GetDeployedCharacterObject()) {
				player->SyncCharacterData();
			}

			if (object->mDataBits.any()) {
				mServer->SendObjectUpdate(client, object);
			}

			if (flags & Object::UpdateCombatant) {
				mServer->SendCombatantDataUpdate(client, object, *object->GetCombatantData());
				newFlags &= ~Object::UpdateCombatant;
			}

			if (flags & Object::UpdateAttributes) {
				mServer->SendAttributeDataUpdate(client, object, *object->GetAttributeData());
				newFlags &= ~Object::UpdateAttributes;
			}

			if (flags & Object::UpdateLootData) {
				mServer->SendLootDataUpdate(client, object, *object->GetLootData());
				newFlags &= ~Object::UpdateLootData;
			}

			if (flags & Object::UpdateAgentBlackboardData) {
				mServer->SendAgentBlackboardUpdate(client, object, *object->GetAgentBlackboardData());
				newFlags &= ~Object::UpdateAgentBlackboardData;
			}

			if (flags & Object::UpdateInteractableData) {
				mServer->SendInteractableDataUpdate(client, object, *object->GetInteractableData());
				newFlags &= ~Object::UpdateInteractableData;
			}

			if (flags & Object::UpdateLocomotion) {
				const auto& locomotion = object->GetLocomotionData();
				if (object->IsPlayerControlled()) {
					mServer->SendObjectPlayerMove(client, object, *locomotion);
				} else {
					if (locomotion->GetGoalFlags() & 0x20) {
						mServer->SendObjectTeleport(client, object, object->GetPosition(), locomotion->GetFacing());
					} else {
#if 0 // If unreliable update
						mServer->SendLocomotionDataUnreliableUpdate(client, object, locomotion->GetGoalPosition());
#else
						mServer->SendLocomotionDataUpdate(client, object, *locomotion);
#endif
					}
				}
				newFlags &= ~Object::UpdateLocomotion;
			}
		}

		object->SetFlags(newFlags);
		object->ResetUpdateBits();
	}

	void Instance::SendAnimationState(const ObjectPtr& object, uint32_t state, bool overlay, float scale) {
		if (!object) {
			return;
		}

		const auto timestamp = GetTime();
		if (!overlay) {
			object->mLastAnimationState = state;
			object->mLastAnimationPlayTime = timestamp;
		}

		for (const auto& [_, client] : mServer->GetClients()) {
			mServer->SendAnimationState(client, object, state, timestamp, overlay, scale);
		}
	}

	void Instance::SendObjectGfxState(const ObjectPtr& object, uint32_t state) {
		if (!object) {
			return;
		}

		const auto timestamp = GetTime();
		object->mGraphicsState = state;
		object->mGraphicsStateStartTime = timestamp;

		for (const auto& [_, client] : mServer->GetClients()) {
			mServer->SendObjectGfxState(client, object, state, timestamp);
		}
	}

	void Instance::SendServerEvent(const ServerEventBase& serverEvent) {
		if (!serverEvent) {
			return;
		}

		for (const auto& [_, client] : mServer->GetClients()) {
			mServer->SendServerEvent(client, serverEvent);
		}
	}

	void Instance::SendServerEvent(const PlayerPtr& player, const ServerEventBase& serverEvent) {
		if (!serverEvent || !player) {
			return;
		}

		const auto& client = mServer->GetClient(player->GetId());
		if (client) {
			mServer->SendServerEvent(client, serverEvent);
		}
	}

	void Instance::SendCombatEvent(const CombatEvent& combatEvent) {
		for (const auto& [_, client] : mServer->GetClients()) {
			mServer->SendCombatEvent(client, combatEvent);
		}
	}

	void Instance::SendCooldownUpdate(const ObjectPtr& object, uint32_t id, uint64_t start, uint32_t duration) {
		if (!object) {
			return;
		}

		for (const auto& [_, client] : mServer->GetClients()) {
			mServer->SendCooldownUpdate(client, object, id, start, duration);
		}
	}

	void Instance::SendLabsPlayerUpdate(const PlayerPtr& player) {
		if (!player || !player->NeedUpdate()) {
			return;
		}

		for (const auto& [_, client] : mServer->GetClients()) {
			mServer->SendLabsPlayerUpdate(client, player);
		}

		player->ResetUpdateBits();
	}

	void Instance::PickupLoot(const PlayerPtr& player, const ObjectPtr& object) {
		if (!player || !object || object->IsMarkedForDeletion()) {
			return;
		}

		object->MarkForDeletion();
		if (!object->HasLootData()) {
			return;
		}

		ClientEvent lootEvent;
		lootEvent.SetLootPickup(player->GetId(), *object->GetLootData());

		for (const auto& [_, client] : mServer->GetClients()) {
			mServer->SendServerEvent(client, lootEvent);
		}
	}

	void Instance::PickupCatalyst(const PlayerPtr& player, const ObjectPtr& object) {
		if (!player || !object || object->IsMarkedForDeletion()) {
			return;
		}

		uint32_t slot = player->GetOpenCatalystSlot();
		if (slot != 0xFFFFFFFF) {
			object->MarkForDeletion();
			
			const auto& lootData = object->GetLootData();
			if (!lootData) {
				// Actual object contains no catalyst, ignore.
				return;
			}

			auto catalyst = Catalyst(*lootData);
			player->SetCatalyst(catalyst, slot);

			const auto& client = mServer->GetClient(player->GetId());
			mServer->SendCrystalMessage(client, 0, 0, slot, catalyst);
		} else {
			// TODO: add bounce
			ClientEvent catalystEvent;
			catalystEvent.SetCatalystPickup(player->GetId());

			for (const auto& [_, client] : mServer->GetClients()) {
				mServer->SendServerEvent(client, catalystEvent);
			}
		}
	}
}
