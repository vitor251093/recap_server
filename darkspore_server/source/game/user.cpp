
// Include
#include "user.h"
#include "config.h"

#include "../utils/functions.h"
#include <algorithm>
#include <filesystem>

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

// Game
namespace Game {
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
		id = utils::xml_get_text_node<uint32_t>(account, "id");

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
		if (auto account = node.append_child("account")) {
			utils::xml_add_text_node(account, "tutorial_completed", tutorialCompleted ? "Y" : "N");
			utils::xml_add_text_node(account, "chain_progression", chainProgression);
			utils::xml_add_text_node(account, "creature_rewards", creatureRewards);
			utils::xml_add_text_node(account, "current_game_id", currentGameId);
			utils::xml_add_text_node(account, "current_playgroup_id", currentPlaygroupId);
			utils::xml_add_text_node(account, "default_deck_pve_id", defaultDeckPveId);
			utils::xml_add_text_node(account, "default_deck_pvp_id", defaultDeckPvpId);
			utils::xml_add_text_node(account, "level", level);
			utils::xml_add_text_node(account, "avatar_id", avatarId);
			utils::xml_add_text_node(account, "blaze_id", id);
			utils::xml_add_text_node(account, "id", id);
			utils::xml_add_text_node(account, "dna", dna);
			utils::xml_add_text_node(account, "new_player_inventory", newPlayerInventory);
			utils::xml_add_text_node(account, "new_player_progress", newPlayerProgress);
			utils::xml_add_text_node(account, "cashout_bonus_time", cashoutBonusTime);
			utils::xml_add_text_node(account, "star_level", starLevel);
			utils::xml_add_text_node(account, "unlock_catalysts", unlockCatalysts);
			utils::xml_add_text_node(account, "unlock_diagonal_catalysts", unlockDiagonalCatalysts);
			utils::xml_add_text_node(account, "unlock_fuel_tanks", unlockFuelTanks);
			utils::xml_add_text_node(account, "unlock_inventory", unlockInventoryIdentify);
			utils::xml_add_text_node(account, "unlock_pve_decks", unlockPveDecks);
			utils::xml_add_text_node(account, "unlock_pvp_decks", unlockPvpDecks);
			utils::xml_add_text_node(account, "unlock_stats", unlockStats);
			utils::xml_add_text_node(account, "unlock_inventory_identify", unlockInventoryIdentify);
			utils::xml_add_text_node(account, "unlock_editor_flair_slots", unlockEditorFlairSlots);
			utils::xml_add_text_node(account, "upsell", upsell);
			utils::xml_add_text_node(account, "xp", xp);
			utils::xml_add_text_node(account, "grant_all_access", grantAllAccess ? "1" : "0");
			utils::xml_add_text_node(account, "grant_online_access", grantOnlineAccess ? "1" : "0");
			utils::xml_add_text_node(account, "cap_level", capLevel);
			utils::xml_add_text_node(account, "cap_progression", capProgression);
		}
	}

	rapidjson::Value Account::Write(rapidjson::Document::AllocatorType& allocator) const { 
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember("tutorial_completed",        rapidjson::Value{}.SetBool(tutorialCompleted),       allocator);
		object.AddMember("chain_progression",         rapidjson::Value{}.SetUint(chainProgression),        allocator);
		object.AddMember("creature_rewards",          rapidjson::Value{}.SetUint(creatureRewards),         allocator);
		object.AddMember("current_game_id",           rapidjson::Value{}.SetUint(currentGameId),           allocator);
		object.AddMember("current_playgroup_id",      rapidjson::Value{}.SetUint(currentPlaygroupId),      allocator);
		object.AddMember("default_deck_pve_id",       rapidjson::Value{}.SetUint(defaultDeckPveId),        allocator);
		object.AddMember("default_deck_pvp_id",       rapidjson::Value{}.SetUint(defaultDeckPvpId),        allocator);
		object.AddMember("level",                     rapidjson::Value{}.SetUint(level),                   allocator);
		object.AddMember("avatar_id",                 rapidjson::Value{}.SetUint(avatarId),                allocator);
		object.AddMember("blaze_id",                  rapidjson::Value{}.SetUint(id),                      allocator);
		object.AddMember("id",                        rapidjson::Value{}.SetUint(id),                      allocator);
		object.AddMember("dna",                       rapidjson::Value{}.SetUint(dna),                     allocator);
		object.AddMember("new_player_inventory",      rapidjson::Value{}.SetUint(newPlayerInventory),      allocator);
		object.AddMember("new_player_progress",       rapidjson::Value{}.SetUint(newPlayerProgress),       allocator);
		object.AddMember("cashout_bonus_time",        rapidjson::Value{}.SetUint(cashoutBonusTime),        allocator);
		object.AddMember("star_level",                rapidjson::Value{}.SetUint(starLevel),               allocator);
		object.AddMember("unlock_catalysts",          rapidjson::Value{}.SetUint(unlockCatalysts),         allocator);
		object.AddMember("unlock_diagonal_catalysts", rapidjson::Value{}.SetUint(unlockDiagonalCatalysts), allocator);
		object.AddMember("unlock_fuel_tanks",         rapidjson::Value{}.SetUint(unlockFuelTanks),         allocator);
		object.AddMember("unlock_inventory",          rapidjson::Value{}.SetUint(unlockInventoryIdentify), allocator);
		object.AddMember("unlock_pve_decks",          rapidjson::Value{}.SetUint(unlockPveDecks),          allocator);
		object.AddMember("unlock_pvp_decks",          rapidjson::Value{}.SetUint(unlockPvpDecks),          allocator);
		object.AddMember("unlock_stats",              rapidjson::Value{}.SetUint(unlockStats),             allocator);
		object.AddMember("unlock_inventory_identify", rapidjson::Value{}.SetUint(unlockInventoryIdentify), allocator);
		object.AddMember("unlock_editor_flair_slots", rapidjson::Value{}.SetUint(unlockEditorFlairSlots),  allocator);
		object.AddMember("upsell",                    rapidjson::Value{}.SetUint(upsell),                  allocator);
		object.AddMember("xp",                        rapidjson::Value{}.SetUint(xp),                      allocator);
		object.AddMember("grant_all_access",          rapidjson::Value{}.SetBool(grantAllAccess),          allocator);
		object.AddMember("grant_online_access",       rapidjson::Value{}.SetBool(grantOnlineAccess),       allocator);
		object.AddMember("cap_level",                 rapidjson::Value{}.SetUint(capLevel),                allocator);
		object.AddMember("cap_progression",           rapidjson::Value{}.SetUint(capProgression),          allocator);
		return object;
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
			feedItem.messageId = utils::xml_get_text_node<uint32_t>(item, "message_id");
			feedItem.metadata = utils::xml_get_text_node(item, "metadata");
			feedItem.name = utils::xml_get_text_node(item, "name");
			feedItem.timestamp = utils::xml_get_text_node<uint64_t>(item, "time");
		}
	}

	void Feed::Write(pugi::xml_node& node) const {
		if (auto feed = node.append_child("feed")) {
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
	}

	rapidjson::Value Feed::Write(rapidjson::Document::AllocatorType& allocator) const {
		rapidjson::Value value(rapidjson::kArrayType);
		for (const auto& feedItem : mItems) {
			rapidjson::Value object(rapidjson::kObjectType);
			utils::json_add_text_to_object(object, "metadata", feedItem.metadata, allocator);
			utils::json_add_text_to_object(object, "name",     feedItem.name,     allocator);
			object.AddMember("time",       rapidjson::Value{}.SetUint64(feedItem.timestamp), allocator);
			object.AddMember("account_id", rapidjson::Value{}.SetUint(feedItem.accountId),   allocator);
			object.AddMember("id",         rapidjson::Value{}.SetUint(feedItem.id),          allocator);
			object.AddMember("message_id", rapidjson::Value{}.SetUint(feedItem.messageId),   allocator);
			value.PushBack(object, allocator);
		}		
		return value;
	}

	// User
	User::User(const std::string& name, const std::string& email, const std::string& password) : mName(name), mEmail(email), mPassword(password) {
		// Empty
	}

	User::User(const std::string& email) : mEmail(email) {
		// Empty
	}

	User::~User() {
		
	}

	bool User::UpdateState(uint32_t newState) {
		if (mState != newState) {
			mState = newState;
			return true;
		}
		return false;
	}

	Creature* User::GetCreatureById(uint32_t id) {
		Creature* creaturePtr = nullptr;
		for (auto& creature : mCreatures) {
			if (creature.id == id) {
				creaturePtr = &creature;
				break;
			}
		}
		return creaturePtr;
	}

	const Creature* User::GetCreatureById(uint32_t id) const {
		const Creature* creaturePtr = nullptr;
		for (const auto& creature : mCreatures) {
			if (creature.id == id) {
				creaturePtr = &creature;
				break;
			}
		}
		return creaturePtr;
	}

	void User::UnlockCreature(uint32_t templateId) {
		if (mAccount.creatureRewards > 0) {
			mCreatures.Add(templateId);
			mAccount.creatureRewards--;
		}
	}

	void User::UnlockUpgrade(uint32_t unlockId) {
		switch (unlockId) {
			case 1: // Catalysts
				mAccount.unlockCatalysts++;
				break;

			case 8: // Stats
			case 9:
				mAccount.unlockStats++;
				break;

			case 36: // PVE Squads
				mAccount.unlockPveDecks++;
				break;

			case 38: // PVP Squads
				mAccount.unlockPvpDecks++;
				break;

			case 46: // Editor detail slots
				mAccount.unlockEditorFlairSlots++;
				break;

			default:
				break;
		}
	}

	void User::Logout() {
		UserManager::RemoveUser(mEmail);
		Save();
	}

	bool User::Load() {
		std::string filepath = Config::Get(CONFIG_STORAGE_PATH) + "users/" + mEmail + ".xml";

		pugi::xml_document document;
		if (!document.load_file(filepath.c_str())) {
			return false;
		}

		if (auto user = document.child("user")) {
			mName = utils::xml_get_text_node(user, "name");
			mEmail = utils::xml_get_text_node(user, "email");
			mPassword = utils::xml_get_text_node(user, "password"); // Hash this later?

			mAccount.Read(user);
			mCreatures.Read(user);
			mSquads.Read(user);
			mFeed.Read(user);
		}

		return true;
	}

	bool User::Save() {
		pugi::xml_document document = ToXml();
		std::string filepath = Config::Get(CONFIG_STORAGE_PATH) + "users/" + mEmail + ".xml";
		return document.save_file(filepath.c_str(), "\t", 1U, pugi::encoding_latin1);
	}

	pugi::xml_document User::ToXml() {
		pugi::xml_document document;
		if (auto user = document.append_child("user")) {
			utils::xml_add_text_node(user, "name", mName);
			utils::xml_add_text_node(user, "email", mEmail);
			utils::xml_add_text_node(user, "password", mPassword);

			mAccount.Write(user);
			mCreatures.Write(user);
			mSquads.Write(user);
			mFeed.Write(user);
		}
		return document;
	}

	rapidjson::Value User::ToJson(rapidjson::Document::AllocatorType& allocator) {
		rapidjson::Value object(rapidjson::kObjectType);
		
		utils::json_add_text_to_object(object, "name",     mName,     allocator);
		utils::json_add_text_to_object(object, "email",    mEmail,    allocator);
		utils::json_add_text_to_object(object, "password", mPassword, allocator);

		object.AddMember("account",   mAccount.Write(allocator),   allocator);
		object.AddMember("creatures", mCreatures.Write(allocator), allocator);
		object.AddMember("squads",    mSquads.Write(allocator),    allocator);
		object.AddMember("feed",      mFeed.Write(allocator),      allocator);

		return object;
	}

	// UserManager
	std::map<std::string, UserPtr> UserManager::sUsersByEmail;

	std::vector<std::string> UserManager::GetAllUserNames() {
		std::vector<std::string> users;
		
		std::string folderPath = Config::Get(CONFIG_STORAGE_PATH) + "users/";
		for (const auto & entry : std::filesystem::directory_iterator(folderPath)) {
			if (entry.path().extension() == ".xml") {
				users.push_back(entry.path().stem().string());
			}
		}

		return users;
	}

	std::vector<std::string> UserManager::GetLoggedUserNames() {
		std::vector<std::string> users;
		
		for (const auto & pair : sUsersByEmail) {
			users.push_back(pair.first);
		}

		return users;
	}

	UserPtr UserManager::GetUserByEmail(const std::string& email, const bool shouldLogin) {
		UserPtr user;

		auto it = sUsersByEmail.find(email);
		if (it != sUsersByEmail.end()) {
			user = it->second;
		} else {
			user = std::make_shared<User>(email);
			if (user->Load()) {
				if (shouldLogin) sUsersByEmail.emplace(email, user);
			}
			else {
				user.reset();
			}
		}

		return user;
	}

	UserPtr UserManager::CreateUserWithNameMailAndPassword(const std::string& name, const std::string& email, const std::string& password) {
		UserPtr user;

		auto it = sUsersByEmail.find(email);
		if (it != sUsersByEmail.end()) {
			return NULL;
		} else {
			user = std::make_shared<User>(name, email, password);
			if (user->Save()) {
				sUsersByEmail.emplace(email, user);
			}
			else {
				user.reset();
			}
		}

		return user;
	}

	UserPtr UserManager::GetUserByAuthToken(const std::string& authToken) {
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
