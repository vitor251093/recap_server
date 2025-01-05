
// Include
#include "user.h"
#include "instance.h"

#include "blaze/component/associationcomponent.h"
#include "utils/functions.h"

#include <algorithm>
#include <array>

/*
<feed>
	<count>20</count>
	<total>161</total>
	<items>
		<item>
		<account_id>386571374</account_id>
		<id>1803</id>
		<message_id>2</message_id>
		<metadata>3524487169;1002340</metadata>
		<name>maxisjohn</name>
		<time>1296011517</time>
		</item>
		<item>
		<account_id>386571374</account_id>
		<id>1802</id>
		<message_id>2</message_id>
		<metadata>2128242117;1002339</metadata>
		<name>maxisjohn</name>
		<time>1296011487</time>
		</item>
		<item>
		<account_id>386571374</account_id>
		<id>1798</id>
		<message_id>3</message_id>
		<metadata>8</metadata>
		<name>maxisjohn</name>
		<time>1296008728</time>
		</item>
		<item>
		<account_id>386573487</account_id>
		<id>1773</id>
		<message_id>1</message_id>
		<metadata>Synesthesiac</metadata>
		<name>somegamerdood</name>
		<time>1295961120</time>
		</item>
		<item>
		<account_id>386573487</account_id>
		<id>1772</id>
		<message_id>1</message_id>
		<metadata>MaxisJohn</metadata>
		<name>somegamerdood</name>
		<time>1295961116</time>
		</item>
	</items>
</feed>
*/

// SporeNet
namespace SporeNet {
	// Account
	void Account::Read(const pugi::xml_node& node) {
		auto account = node.child("account");
		if (!account) {
			return;
		}

		tutorialCompleted = utils::xml_get_text_node(account, "tutorial_completed") == "Y";
		grantAllAccess = utils::xml_get_text_node<uint32_t>(account, "grant_all_access");
		grantOnlineAccess = utils::xml_get_text_node<uint32_t>(account, "grant_online_access");

		chainProgression = utils::xml_get_text_node<uint32_t>(account, "chain_progression");
		creatureRewards = utils::xml_get_text_node<uint32_t>(account, "creature_rewards");

		currentGameId = utils::xml_get_text_node<uint32_t>(account, "current_game_id");
		currentPlaygroupId = utils::xml_get_text_node<uint32_t>(account, "current_playgroup_id");

		defaultDeckPveId = utils::xml_get_text_node<uint32_t>(account, "default_deck_pve_id");
		defaultDeckPvpId = utils::xml_get_text_node<uint32_t>(account, "default_deck_pvp_id");

		level = utils::xml_get_text_node<uint32_t>(account, "level");
		xp = utils::xml_get_text_node<uint32_t>(account, "xp");
		dna = utils::xml_get_text_node<uint32_t>(account, "dna");
		avatarId = std::clamp<uint32_t>(utils::xml_get_text_node<uint32_t>(account, "avatar_id"), 0, 16);
		id = utils::xml_get_text_node<int64_t>(account, "id");

		newPlayerInventory = utils::xml_get_text_node<uint32_t>(account, "new_player_inventory");
		newPlayerProgress = utils::xml_get_text_node<uint32_t>(account, "new_player_progress");

		cashoutBonusTime = utils::xml_get_text_node<uint32_t>(account, "cashout_bonus_time");
		starLevel = utils::xml_get_text_node<uint32_t>(account, "star_level");

		unlockCatalysts = utils::xml_get_text_node<uint32_t>(account, "unlock_catalysts");
		unlockDiagonalCatalysts = utils::xml_get_text_node<uint32_t>(account, "unlock_diagonal_catalysts");
		unlockFuelTanks = utils::xml_get_text_node<uint32_t>(account, "unlock_fuel_tanks");
		unlockInventoryIdentify = utils::xml_get_text_node<uint32_t>(account, "unlock_inventory");
		unlockPveDecks = utils::xml_get_text_node<uint32_t>(account, "unlock_pve_decks");
		unlockPvpDecks = utils::xml_get_text_node<uint32_t>(account, "unlock_pvp_decks");
		unlockStats = utils::xml_get_text_node<uint32_t>(account, "unlock_stats");
		unlockInventoryIdentify = utils::xml_get_text_node<uint32_t>(account, "unlock_inventory_identify");
		unlockEditorFlairSlots = utils::xml_get_text_node<uint32_t>(account, "unlock_editor_flair_slots");

		upsell = utils::xml_get_text_node<uint32_t>(account, "upsell");

		capLevel = utils::xml_get_text_node<uint32_t>(account, "cap_level");
		capProgression = utils::xml_get_text_node<uint32_t>(account, "cap_progression");
	}

	void Account::Write(pugi::xml_node& node) const {
		utils::xml_add_text_node(node, "tutorial_completed", tutorialCompleted ? "Y" : "N");
		utils::xml_add_text_node(node, "chain_progression", chainProgression);
		utils::xml_add_text_node(node, "creature_rewards", creatureRewards);
		utils::xml_add_text_node(node, "current_game_id", currentGameId);
		utils::xml_add_text_node(node, "current_playgroup_id", currentPlaygroupId);
		utils::xml_add_text_node(node, "default_deck_pve_id", defaultDeckPveId);
		utils::xml_add_text_node(node, "default_deck_pvp_id", defaultDeckPvpId);
		utils::xml_add_text_node(node, "dna", dna);
		utils::xml_add_text_node(node, "level", level);
		utils::xml_add_text_node(node, "avatar_id", avatarId);
		utils::xml_add_text_node(node, "id", id);
		utils::xml_add_text_node(node, "new_player_inventory", newPlayerInventory);
		utils::xml_add_text_node(node, "new_player_progress", newPlayerProgress);
		utils::xml_add_text_node(node, "cashout_bonus_time", cashoutBonusTime);
		utils::xml_add_text_node(node, "star_level", starLevel);
		utils::xml_add_text_node(node, "unlock_catalysts", unlockCatalysts);
		utils::xml_add_text_node(node, "unlock_diagonal_catalysts", unlockDiagonalCatalysts);
		utils::xml_add_text_node(node, "unlock_fuel_tanks", unlockFuelTanks);
		utils::xml_add_text_node(node, "unlock_inventory", unlockInventoryIdentify);
		utils::xml_add_text_node(node, "unlock_pve_decks", unlockPveDecks);
		utils::xml_add_text_node(node, "unlock_pvp_decks", unlockPvpDecks);
		utils::xml_add_text_node(node, "unlock_stats", unlockStats);
		utils::xml_add_text_node(node, "unlock_inventory_identify", unlockInventoryIdentify);
		utils::xml_add_text_node(node, "unlock_editor_flair_slots", unlockEditorFlairSlots);
		utils::xml_add_text_node(node, "upsell", upsell);
		utils::xml_add_text_node(node, "xp", xp);
		utils::xml_add_text_node(node, "grant_all_access", grantAllAccess ? 1 : 0);
		// utils::xml_add_text_node(node, "grant_online_access", grantOnlineAccess ? 1 : 0);
		utils::xml_add_text_node(node, "cap_level", capLevel);
		utils::xml_add_text_node(node, "cap_progression", capProgression);
	}

	// Feed
	void Feed::Read(const pugi::xml_node& node) {
		auto feed = node.child("feed");
		if (!feed) {
			return;
		}

		auto items = feed.child("items");
		if (!items) {
			return;
		}

		for (const auto& item : items) {
			decltype(auto) feedItem = mItems.emplace_back();
			feedItem.accountId = utils::xml_get_text_node<uint32_t>(item, "account_id");
			feedItem.id = utils::xml_get_text_node<uint32_t>(item, "id");

			auto messageId = utils::xml_get_text_node<FeedMessageType>(item, "message_id");
			switch (messageId) {
				case FeedMessageType::Friend: // metadata = friend account id
				case FeedMessageType::Creature: // metadata = creature_id;localized_name_id
				case FeedMessageType::Upgrade: // metadata = maybe upgrade id?
					feedItem.messageId = messageId;
					break;
			}

			feedItem.metadata = utils::xml_get_text_node(item, "metadata");
			feedItem.name = utils::xml_get_text_node(item, "name");
			feedItem.timestamp = utils::xml_get_text_node<uint64_t>(item, "time");
		}
	}

	void Feed::Write(pugi::xml_node& node) const {
		auto feed = node.append_child("feed");
		if (mItems.empty()) {
			return;
		}

		auto items = feed.append_child("items");
		for (const auto& feedItem : mItems) {
			auto item = items.append_child("item");
			utils::xml_add_text_node(item, "account_id", feedItem.accountId);
			utils::xml_add_text_node(item, "id", feedItem.id);
			utils::xml_add_text_node(item, "message_id", feedItem.messageId);
			utils::xml_add_text_node(item, "metadata", feedItem.metadata);
			utils::xml_add_text_node(item, "name", feedItem.name);
			utils::xml_add_text_node(item, "time", feedItem.timestamp);
		}
	}

	// User
	User::User(const std::string& username) : mUsername(username) {
		// Empty
	}

	User::User(const std::string& name, const std::string& username, const std::string& password) : mName(name), mUsername(username), mPassword(password) {
		// Empty
	}

	User::~User() {
		// Empty
	}

	bool User::UpdateState(uint32_t newState) {
		if (mState != newState) {
			mState = newState;
			return true;
		}
		return false;
	}

	CreaturePtr User::GetCreatureById(uint32_t id) const {
		for (const auto& creature : mCreatures) {
			if (creature->GetId() == id) {
				return creature;
			}
		}
		return nullptr;
	}

	uint32_t User::UnlockCreature(uint32_t templateId) {
		if (mAccount.creatureRewards > 0) {
			mAccount.creatureRewards--;
			return mCreatures.Add(templateId);
		}
		return 0;
	}

	const std::vector<SquadPtr>& User::GetSquads() const {
		return mSquads;
	}

	SquadPtr User::GetSquadById(uint32_t id) const {
		for (const auto& squad : mSquads) {
			if (squad->GetId() == id) {
				return squad;
			}
		}
		return nullptr;
	}

	void User::UpdateSquad(uint32_t slot, const std::string& creatureStringList, bool pvp) {
		auto squad = GetSquadById(slot);
		if (!squad) {
			// Squad doesn't exist.
			return;
		}

		auto creatureIds = utils::explode_string(creatureStringList, ',');

		uint8_t creatureIndex = 0;
		for (const auto& idString : creatureIds) {
			auto id = utils::to_number<uint32_t>(idString);
			if (id == 0) {
				continue;
			}

			auto creature = mCreatures.Get(id);
			if (creature) {
				squad->SetCreatureId(creatureIndex++, creature->GetId());
			}
			/*
			else {
				auto templateCreature = SporeNet::Get().GetTemplateDatabase().Get(id);
				if (templateCreature) {

				}
			}
			*/
		}
	}

	bool User::UnlockUpgrade(uint32_t unlockId) {
		constexpr std::array<uint32_t, 64> unlockCost {
			0,

			// Catalysts
			2000, 6000, 16000,
			30000, 80000, 150000,

			// Catalyst diagonal bonus
			300000,

			// Stats
			200, 350, 500,
			700, 900, 1200,
			1600, 4000, 8000,
			13000, 19000, 29000,
			42000, 57000, 76000,
			100000, 160000, 250000,
			
			// Inventory
			5000, 25000, 50000,
			100000, 200000, 400000,
			1000000, 2500000, 5000000,
			10000000,

			// PVE Squads
			500, 4000,

			// PVP Unlock
			0,

			// Nothing
			0, 0, 0,

			// Ship fuel tanks
			400, 1200, 4000,

			// Nothing
			0,

			// Editor detail slots
			1000, 5000, 10000,

			// Inventory (again)
			200, 600, 1200,
			20000000
		};

		if (unlockId >= unlockCost.size()) {
			return false;
		}

		const auto cost = unlockCost[unlockId];
		if (cost > mAccount.dna) {
			return false;
		}

		mAccount.dna -= cost;
		switch (unlockId) {
			// Catalysts
			case 1: case 2: case 3:
			case 4: case 5: case 6: {
				mAccount.unlockCatalysts = unlockId - 1 + 4;
				break;
			}

			// Catalyst diagonal bonus
			case 7: {
				mAccount.unlockDiagonalCatalysts = 1;
				break;
			}
			
			// Stats
			case 8: case 9: case 10:
			case 11: case 12: case 13:
			case 14: case 15: case 16:
			case 17: case 18: case 19:
			case 20: case 21: case 22:
			case 23: case 24: case 25: {
				mAccount.unlockStats = unlockId - 8 + 1;
				break;
			}

			// Inventory
			case 26: case 27: case 28:
			case 29: case 30: case 31:
			case 32: case 33: case 34:
			case 35: {
				mAccount.unlockInventory = unlockId - 26 + 4;
				mAccount.unlockInventoryIdentify = 180 + 30 * mAccount.unlockInventory;
				break;
			}

			// PVE Squads
			case 36: case 37: {
				// TODO: make squads solution better
				mAccount.unlockPveDecks = unlockId - 36 + 2;
				// mSquads.Create();
				break;
			}

			// PVP Unlock
			case 38: {
				mAccount.unlockPvpDecks = 1;
				break;
			}

			// Ship engine
			case 42: case 43: case 44: {
				mAccount.unlockFuelTanks = unlockId - 42 + 3;
				break;
			}

			// Editor detail slots
			case 46: case 47: case 48: {
				mAccount.unlockEditorFlairSlots = unlockId - 46 + 4;
				break;
			}

			// Inventory (again)
			case 49: case 50: case 51: {
				mAccount.unlockInventory = unlockId - 49 + 1;
				mAccount.unlockInventoryIdentify = 180 + 30 * mAccount.unlockInventory;
				break;
			}

			case 52: {
				mAccount.unlockInventory = unlockId - 52 + 14;
				mAccount.unlockInventoryIdentify = 180 + 30 * mAccount.unlockInventory;
				break;
			}

			default:
				break;
		}

		return true;
	}

	// Rooms
	const RoomPtr& User::GetRoom() const {
		return mRoom;
	}

	void User::SetRoom(const RoomPtr& room) {
		mRoom = room;
	}

	// Storage
	void User::Logout() {
		SporeNet::Get().GetUserManager().RemoveUser(mUsername);
		Save();
	}

	bool User::Load() {
		std::string filepath = "data/user/" + mUsername + ".xml";

		pugi::xml_document document;
		if (!document.load_file(filepath.c_str())) {
			return false;
		}

		if (auto docUser = document.child("user")) {
			mName = utils::xml_get_text_node(docUser, "name");
			mPassword = utils::xml_get_text_node(docUser, "password"); // Hash this later?

			mAccount.Read(docUser);
			mCreatures.Read(docUser);
			if (auto docSquads = docUser.child("squads")) {
				for (const auto& docSquad : docSquads) {
					auto squad = std::make_shared<Squad>();
					if (squad->Read(docSquad)) {
						mSquads.push_back(std::move(squad));
					}
				}
			}

			mFeed.Read(docUser);
			mParts.Read(docUser);
			/*
			for (uint16_t i = 0x7F; i < 0xFF; ++i) {
				Part part(267 + (i++));
				part.SetCreationDate(utils::get_unix_time() + i);
				part.SetIsFlair(false);
				part.SetMarketStatus(1);
				part.SetCost(1000);
				part.SetLevel(30);
				part.SetRarity(PartRarity::Rare);
				part.SetStatus(i);
				part.SetUsage(1);

				mParts.data().push_back(std::move(part));
			}
			*/
		}

		return true;
	}

	bool User::Save() {
		std::string filepath = "data/user/" + mUsername + ".xml";

		pugi::xml_document document;
		if (auto docUser = document.append_child("user")) {
			utils::xml_add_text_node(docUser, "name", mName);
			utils::xml_add_text_node(docUser, "password", mPassword);

			if (auto docAccount = docUser.append_child("account")) {
				mAccount.Write(docAccount);
			}

			mCreatures.Write(docUser);
			if (auto docSquads = docUser.append_child("squads")) {
				for (const auto& squad : mSquads) {
					squad->Write(docSquads);
				}
			}

			mFeed.Write(docUser);
			mParts.Write(docUser);
		}

		return document.save_file(filepath.c_str(), "\t", 1U, pugi::encoding_latin1);
	}

	bool User::IsFriend(const User& user) const {
		auto it = mAssociationLists.find(Blaze::AssociationListId::Friend);
		if (it == mAssociationLists.end()) {
			return false;
		}

		const auto& friendList = it->second;
		for (const auto& memberInfo : friendList.memberList) {
			const auto& memberId = memberInfo.id;
			if (memberId.id == user.get_account().id) {
				return true;
			}
		}

		return false;
	}

	void User::AddFriendUser(const User& user) {
		if (IsFriend(user)) {
			return;
		}

		auto& friendList = mAssociationLists[Blaze::AssociationListId::Friend];
		auto& memberInfo = friendList.memberList.emplace_back();

		memberInfo.id.id = user.get_account().id;
		memberInfo.id.name = user.get_name();

		memberInfo.time = utils::get_unix_time();
	}

	void User::RemoveFriendUser(const User& user) {
		auto& friendList = mAssociationLists[Blaze::AssociationListId::Friend];
	}

	bool User::IsIgnored(const User& user) const {
		auto it = mAssociationLists.find(Blaze::AssociationListId::Ignore);
		if (it == mAssociationLists.end()) {
			return false;
		}

		const auto& ignoreList = it->second;
		for (const auto& memberInfo : ignoreList.memberList) {
			const auto& memberId = memberInfo.id;
			if (memberId.id == user.get_account().id) {
				return true;
			}
		}

		return false;
	}

	void User::AddIgnoredUser(const User& user) {
		auto& ignoreList = mAssociationLists[Blaze::AssociationListId::Ignore];
	}

	void User::RemoveIgnoredUser(const User& user) {
		auto& ignoreList = mAssociationLists[Blaze::AssociationListId::Ignore];

	}

	void User::WriteAccountAPI(pugi::xml_node& node) const {
		mAccount.Write(node);
	}

	void User::WriteCreaturesAPI(pugi::xml_node& node) const {
		// TODO: 
	}

	void User::WriteSquadsAPI(pugi::xml_node& node) const {
		// Also known as "decks" internally
		auto squadsNode = node.append_child("decks");
		for (const auto& squad : mSquads) {
			if (!squad) {
				continue;
			}

			auto squadNode = squadsNode.append_child("deck");
			utils::xml_add_text_node(squadNode, "name", squad->GetName());
			utils::xml_add_text_node(squadNode, "category", squad->GetCategory());
			utils::xml_add_text_node(squadNode, "id", squad->GetId());
			utils::xml_add_text_node(squadNode, "slot", squad->GetSlot());
			utils::xml_add_text_node(squadNode, "locked", squad->IsLocked() ? 1 : 0);
			
			auto creaturesNode = squadNode.append_child("creatures");
			for (uint32_t creatureId : squad->GetCreatureIds()) {
				const auto& creature = mCreatures.Get(creatureId);
				if (!creature) {
					continue;
				}

				auto creatureNode = creaturesNode.append_child("creature");
				utils::xml_add_text_node(creatureNode, "id", creature->GetId());
				utils::xml_add_text_node(creatureNode, "name", creature->GetName());
				utils::xml_add_text_node(creatureNode, "noun_id", creature->GetNoun());
				utils::xml_add_text_node(creatureNode, "version", creature->GetVersion());
				utils::xml_add_text_node(creatureNode, "gear_score", creature->GetGearScore());
				utils::xml_add_text_node(creatureNode, "item_points", creature->GetItemPoints());
			}
		}
	}

	// UserManager
	UserPtr UserManager::SignUp(const std::string& name, const std::string& username, const std::string& password) {
		UserPtr user;

		auto it = sUsersByEmail.find(username);
		if (it != sUsersByEmail.end()) {
			return NULL;
		}
		else {
			user = std::make_shared<User>(name, username, password);

			srand(time(NULL));
			user->get_account().id = rand();

			if (user->Save()) {
				sUsersByEmail.emplace(username, user);
			}
			else {
				user.reset();
			}
		}

		return user;
	}
	std::tuple<UserPtr, bool, bool> UserManager::Login(const std::string& username, const std::string& password) {
		UserPtr user;

		bool success = false;
		bool alreadyLoggedIn = false;

		auto it = sUsersByEmail.find(username);
		if (it != sUsersByEmail.end()) {
			user = it->second;
			alreadyLoggedIn = true;
		} else {
			user = std::make_shared<User>(username);
			if (user->Load() && user->get_password() == password) {
				success = true;
			}
		}

		if (success) {
			sUsersByEmail.emplace(username, user);
		}

		return std::make_tuple(user, success, alreadyLoggedIn);
	}

	std::vector<UserPtr> UserManager::GetUsers() const {
		// Cache this somewhere
		std::vector<UserPtr> result;
		for (const auto& [_, user] : sUsersByEmail) {
			result.push_back(user);
		}
		return result;
	}

	UserPtr UserManager::GetUserById(int64_t id) const {
		for (const auto& [_, user] : sUsersByEmail) {
			if (user->get_id() == id) {
				return user;
			}
		}
		return nullptr;
	}

	UserPtr UserManager::GetUserByEmail(const std::string& username) const {
		if (auto it = sUsersByEmail.find(username); it != sUsersByEmail.end()) {
			return it->second;
		}
		return nullptr;
	}

	UserPtr UserManager::GetUserByAuthToken(const std::string& authToken) const {
		for (const auto& [_, user] : sUsersByEmail) {
			if (user->get_auth_token() == authToken) {
				return user;
			}
		}
		return nullptr;
	}

	void UserManager::RemoveUser(const std::string& email) {
		auto it = sUsersByEmail.find(email);
		if (it != sUsersByEmail.end()) {
			sUsersByEmail.erase(it);
		}
	}
}
