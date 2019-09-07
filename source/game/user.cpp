
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
	void Account::ReadXml(const pugi::xml_node& node) {
		auto account = node.child("account");
		if (!account) {
			return;
		}

		tutorialCompleted = utils::xml::GetString(account, "tutorial_completed") == "Y";
		grantAllAccess    = utils::xml::GetString<uint32_t>(account, "grant_all_access");
		grantOnlineAccess = utils::xml::GetString<uint32_t>(account, "grant_online_access");

		chainProgression  = utils::xml::GetString<uint32_t>(account, "chain_progression");
		creatureRewards   = utils::xml::GetString<uint32_t>(account, "creature_rewards");

		currentGameId      = utils::xml::GetString<uint32_t>(account, "current_game_id");
		currentPlaygroupId = utils::xml::GetString<uint32_t>(account, "current_playgroup_id");

		defaultDeckPveId  = utils::xml::GetString<uint32_t>(account, "default_deck_pve_id");
		defaultDeckPvpId  = utils::xml::GetString<uint32_t>(account, "default_deck_pvp_id");

		level    = utils::xml::GetString<uint32_t>(account, "level");
		xp       = utils::xml::GetString<uint32_t>(account, "xp");
		dna      = utils::xml::GetString<uint32_t>(account, "dna");
		avatarId = std::clamp<uint32_t>(utils::xml::GetString<uint32_t>(account, "avatar_id"), 0, 16);
		id       = utils::xml::GetString<uint32_t>(account, "id");

		newPlayerInventory = utils::xml::GetString<uint32_t>(account, "new_player_inventory");
		newPlayerProgress  = utils::xml::GetString<uint32_t>(account, "new_player_progress");

		cashoutBonusTime = utils::xml::GetString<uint32_t>(account, "cashout_bonus_time");
		starLevel        = utils::xml::GetString<uint32_t>(account, "star_level");

		unlockCatalysts = utils::xml::GetString<uint32_t>(account, "unlock_catalysts");
		unlockDiagonalCatalysts = utils::xml::GetString<uint32_t>(account, "unlock_diagonal_catalysts");
		unlockFuelTanks         = utils::xml::GetString<uint32_t>(account, "unlock_fuel_tanks");
		unlockInventoryIdentify = utils::xml::GetString<uint32_t>(account, "unlock_inventory");
		unlockPveDecks = utils::xml::GetString<uint32_t>(account, "unlock_pve_decks");
		unlockPvpDecks = utils::xml::GetString<uint32_t>(account, "unlock_pvp_decks");
		unlockStats    = utils::xml::GetString<uint32_t>(account, "unlock_stats");
		unlockInventoryIdentify = utils::xml::GetString<uint32_t>(account, "unlock_inventory_identify");
		unlockEditorFlairSlots  = utils::xml::GetString<uint32_t>(account, "unlock_editor_flair_slots");

		upsell = utils::xml::GetString<uint32_t>(account, "upsell");

		capLevel       = utils::xml::GetString<uint32_t>(account, "cap_level");
		capProgression = utils::xml::GetString<uint32_t>(account, "cap_progression");
	}

	void Account::WriteXml(pugi::xml_node& node) const {
		if (auto account = node.append_child("account")) {
			utils::xml::Set(account, "tutorial_completed", tutorialCompleted ? "Y" : "N");
			utils::xml::Set(account, "chain_progression", chainProgression);
			utils::xml::Set(account, "creature_rewards", creatureRewards);
			utils::xml::Set(account, "current_game_id", currentGameId);
			utils::xml::Set(account, "current_playgroup_id", currentPlaygroupId);
			utils::xml::Set(account, "default_deck_pve_id", defaultDeckPveId);
			utils::xml::Set(account, "default_deck_pvp_id", defaultDeckPvpId);
			utils::xml::Set(account, "level", level);
			utils::xml::Set(account, "avatar_id", avatarId);
			utils::xml::Set(account, "blaze_id", id);
			utils::xml::Set(account, "id", id);
			utils::xml::Set(account, "dna", dna);
			utils::xml::Set(account, "new_player_inventory", newPlayerInventory);
			utils::xml::Set(account, "new_player_progress", newPlayerProgress);
			utils::xml::Set(account, "cashout_bonus_time", cashoutBonusTime);
			utils::xml::Set(account, "star_level", starLevel);
			utils::xml::Set(account, "unlock_catalysts", unlockCatalysts);
			utils::xml::Set(account, "unlock_diagonal_catalysts", unlockDiagonalCatalysts);
			utils::xml::Set(account, "unlock_fuel_tanks", unlockFuelTanks);
			utils::xml::Set(account, "unlock_inventory", unlockInventoryIdentify);
			utils::xml::Set(account, "unlock_pve_decks", unlockPveDecks);
			utils::xml::Set(account, "unlock_pvp_decks", unlockPvpDecks);
			utils::xml::Set(account, "unlock_stats", unlockStats);
			utils::xml::Set(account, "unlock_inventory_identify", unlockInventoryIdentify);
			utils::xml::Set(account, "unlock_editor_flair_slots", unlockEditorFlairSlots);
			utils::xml::Set(account, "upsell", upsell);
			utils::xml::Set(account, "xp", xp);
			utils::xml::Set(account, "grant_all_access", grantAllAccess ? "1" : "0");
			utils::xml::Set(account, "grant_online_access", grantOnlineAccess ? "1" : "0");
			utils::xml::Set(account, "cap_level", capLevel);
			utils::xml::Set(account, "cap_progression", capProgression);
		}
	}

	void Account::ReadJson(rapidjson::Value& object) { 
		tutorialCompleted       = utils::json::GetBool(object, "tutorial_completed");
		chainProgression        = utils::json::GetUint(object, "chain_progression");
		creatureRewards         = utils::json::GetUint(object, "creature_rewards");
		currentGameId           = utils::json::GetUint(object, "current_game_id");
		currentPlaygroupId      = utils::json::GetUint(object, "current_playgroup_id");
		defaultDeckPveId        = utils::json::GetUint(object, "default_deck_pve_id");
		defaultDeckPvpId        = utils::json::GetUint(object, "default_deck_pvp_id");
		level                   = utils::json::GetUint(object, "level");
		avatarId                = utils::json::GetUint(object, "avatar_id");
		id                      = utils::json::GetUint(object, "id");
		dna                     = utils::json::GetUint(object, "dna");
		newPlayerInventory      = utils::json::GetUint(object, "new_player_inventory");
		newPlayerProgress       = utils::json::GetUint(object, "new_player_progress");
		cashoutBonusTime        = utils::json::GetUint(object, "cashout_bonus_time");
		starLevel               = utils::json::GetUint(object, "star_level");
		unlockCatalysts         = utils::json::GetUint(object, "unlock_catalysts");
		unlockDiagonalCatalysts = utils::json::GetUint(object, "unlock_diagonal_catalysts");
		unlockFuelTanks         = utils::json::GetUint(object, "unlock_fuel_tanks");
		unlockInventoryIdentify = utils::json::GetUint(object, "unlock_inventory");
		unlockPveDecks          = utils::json::GetUint(object, "unlock_pve_decks");
		unlockPvpDecks          = utils::json::GetUint(object, "unlock_pvp_decks");
		unlockStats             = utils::json::GetUint(object, "unlock_stats");
		unlockInventoryIdentify = utils::json::GetUint(object, "unlock_inventory_identify");
		unlockEditorFlairSlots  = utils::json::GetUint(object, "unlock_editor_flair_slots");
		upsell                  = utils::json::GetUint(object, "upsell");
		xp                      = utils::json::GetUint(object, "xp");
		grantAllAccess          = utils::json::GetBool(object, "grant_all_access");
		grantOnlineAccess       = utils::json::GetBool(object, "grant_online_access");
		capLevel                = utils::json::GetUint(object, "cap_level");
		capProgression          = utils::json::GetUint(object, "cap_progression");
	}

	rapidjson::Value Account::WriteJson(rapidjson::Document::AllocatorType& allocator) const { 
		rapidjson::Value object = utils::json::NewObject();
		utils::json::Set(object, "tutorial_completed",        tutorialCompleted,       allocator);
		utils::json::Set(object, "chain_progression",         chainProgression,        allocator);
		utils::json::Set(object, "creature_rewards",          creatureRewards,         allocator);
		utils::json::Set(object, "current_game_id",           currentGameId,           allocator);
		utils::json::Set(object, "current_playgroup_id",      currentPlaygroupId,      allocator);
		utils::json::Set(object, "default_deck_pve_id",       defaultDeckPveId,        allocator);
		utils::json::Set(object, "default_deck_pvp_id",       defaultDeckPvpId,        allocator);
		utils::json::Set(object, "level",                     level,                   allocator);
		utils::json::Set(object, "avatar_id",                 avatarId,                allocator);
		utils::json::Set(object, "blaze_id",                  id,                      allocator);
		utils::json::Set(object, "id",                        id,                      allocator);
		utils::json::Set(object, "dna",                       dna,                     allocator);
		utils::json::Set(object, "new_player_inventory",      newPlayerInventory,      allocator);
		utils::json::Set(object, "new_player_progress",       newPlayerProgress,       allocator);
		utils::json::Set(object, "cashout_bonus_time",        cashoutBonusTime,        allocator);
		utils::json::Set(object, "star_level",                starLevel,               allocator);
		utils::json::Set(object, "unlock_catalysts",          unlockCatalysts,         allocator);
		utils::json::Set(object, "unlock_diagonal_catalysts", unlockDiagonalCatalysts, allocator);
		utils::json::Set(object, "unlock_fuel_tanks",         unlockFuelTanks,         allocator);
		utils::json::Set(object, "unlock_inventory",          unlockInventoryIdentify, allocator);
		utils::json::Set(object, "unlock_pve_decks",          unlockPveDecks,          allocator);
		utils::json::Set(object, "unlock_pvp_decks",          unlockPvpDecks,          allocator);
		utils::json::Set(object, "unlock_stats",              unlockStats,             allocator);
		utils::json::Set(object, "unlock_inventory_identify", unlockInventoryIdentify, allocator);
		utils::json::Set(object, "unlock_editor_flair_slots", unlockEditorFlairSlots,  allocator);
		utils::json::Set(object, "upsell",                    upsell,                  allocator);
		utils::json::Set(object, "xp",                        xp,                      allocator);
		utils::json::Set(object, "grant_all_access",          grantAllAccess,          allocator);
		utils::json::Set(object, "grant_online_access",       grantOnlineAccess,       allocator);
		utils::json::Set(object, "cap_level",                 capLevel,                allocator);
		utils::json::Set(object, "cap_progression",           capProgression,          allocator);
		return object;
	}



	// Feed
	void Feed::ReadXml(const pugi::xml_node& node) {
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
			feedItem.accountId = utils::xml::GetString<uint32_t>(item, "account_id");
			feedItem.id = utils::xml::GetString<uint32_t>(item, "id");
			feedItem.messageId = utils::xml::GetString<uint32_t>(item, "message_id");
			feedItem.metadata = utils::xml::GetString(item, "metadata");
			feedItem.name = utils::xml::GetString(item, "name");
			feedItem.timestamp = utils::xml::GetString<uint64_t>(item, "time");
		}
	}

	void Feed::WriteXml(pugi::xml_node& node) const {
		if (auto feed = node.append_child("feed")) {
			auto items = feed.append_child("items");
			for (const auto& feedItem : mItems) {
				auto item = items.append_child("item");
				utils::xml::Set(item, "account_id", feedItem.accountId);
				utils::xml::Set(item, "id", feedItem.id);
				utils::xml::Set(item, "message_id", feedItem.messageId);
				utils::xml::Set(item, "metadata", feedItem.metadata);
				utils::xml::Set(item, "name", feedItem.name);
				utils::xml::Set(item, "time", feedItem.timestamp);
			}
		}
	}

	void Feed::ReadJson(rapidjson::Value& object) {
		if (!object.IsArray()) return;
		mItems.clear();
		for (auto& item : object.GetArray()) {
			decltype(auto) feedItem = mItems.emplace_back();
			feedItem.accountId = utils::json::GetUint(object, "account_id");
			feedItem.id        = utils::json::GetUint(object, "id");
			feedItem.messageId = utils::json::GetUint(object, "message_id");
			feedItem.metadata  = utils::json::GetString(object, "metadata");
			feedItem.name      = utils::json::GetString(object, "name"); 
			feedItem.timestamp = utils::json::GetUint64(object, "time");
		}
	}

	rapidjson::Value Feed::WriteJson(rapidjson::Document::AllocatorType& allocator) const {
		rapidjson::Value value = utils::json::NewArray();
		for (const auto& feedItem : mItems) {
			rapidjson::Value object = utils::json::NewObject();
			utils::json::Set(object, "metadata",   feedItem.metadata,  allocator);
			utils::json::Set(object, "name",       feedItem.name,      allocator);
			utils::json::Set(object, "time",       feedItem.timestamp, allocator);
			utils::json::Set(object, "account_id", feedItem.accountId, allocator);
			utils::json::Set(object, "id",         feedItem.id,        allocator);
			utils::json::Set(object, "message_id", feedItem.messageId, allocator);
			utils::json::Add(value, object, allocator);
		}		
		return value;
	}



	// Part
	Part::Part() {

	}
	
	Part::Part(uint32_t rigblock) {
		SetRigblock(rigblock);
		SetPrefix(0, false);
		SetPrefix(0, true);
		SetSuffix(0);
	}

	Part::Part(const pugi::xml_node& node) {
		if (!ReadXml(node)) {
			SetRigblock(1);
			SetPrefix(0, false);
			SetPrefix(0, true);
			SetSuffix(0);
		}
	}

	bool Part::ReadXml(const pugi::xml_node& node) {
		std::string_view nodeName = node.name();
		if (nodeName != "part") {
			return false;
		}

		flair = utils::xml::GetString<bool>(node, "is_flair");
		cost = utils::xml::GetString<uint32_t>(node, "cost");
		equipped_to_creature_id = utils::xml::GetString<uint32_t>(node, "creature_id");
		level = utils::xml::GetString<uint16_t>(node, "level");
		market_status = utils::xml::GetString<uint8_t>(node, "market_status");
		rarity = utils::xml::GetString<uint8_t>(node, "rarity");
		status = utils::xml::GetString<uint8_t>(node, "status");
		usage = utils::xml::GetString<uint8_t>(node, "usage");
		timestamp = utils::xml::GetString<uint64_t>(node, "creation_date");

		SetRigblock(utils::xml::GetString<uint32_t>(node, "rigblock_asset_id"));
		SetPrefix(utils::xml::GetString<uint32_t>(node, "prefix_asset_id"), false);
		SetPrefix(utils::xml::GetString<uint32_t>(node, "prefix_secondary_asset_id"), true);
		SetSuffix(utils::xml::GetString<uint32_t>(node, "suffix_asset_id"));

		return true;
	}

	void Part::WriteXml(pugi::xml_node& node, uint32_t index, bool api) const {
		if (auto part = node.append_child("part")) {
			utils::xml::Set(part, "is_flair", flair);
			utils::xml::Set(part, "cost", cost);
			utils::xml::Set(part, "creature_id", equipped_to_creature_id);
			utils::xml::Set(part, "level", level);
			utils::xml::Set(part, "market_status", market_status);
			utils::xml::Set(part, "rarity", rarity);
			utils::xml::Set(part, "status", status);
			utils::xml::Set(part, "usage", usage);
			utils::xml::Set(part, "creation_date", timestamp);
			if (api) {
				utils::xml::Set(part, "id", index);
				utils::xml::Set(part, "reference_id", index);

				utils::xml::Set(part, "rigblock_asset_id", rigblock_asset_hash);
				utils::xml::Set(part, "prefix_asset_id", prefix_asset_hash);
				utils::xml::Set(part, "prefix_secondary_asset_id", prefix_secondary_asset_hash);
				utils::xml::Set(part, "suffix_asset_id", suffix_asset_hash);
			} else {
				utils::xml::Set(part, "rigblock_asset_id", rigblock_asset_id);
				utils::xml::Set(part, "prefix_asset_id", prefix_asset_id);
				utils::xml::Set(part, "prefix_secondary_asset_id", prefix_secondary_asset_id);
				utils::xml::Set(part, "suffix_asset_id", suffix_asset_id);
			}
		}
	}

	void Part::ReadJson(rapidjson::Value& object) {
		if (!object.IsObject()) return;
		flair                   = utils::json::GetBool(object, "is_flair");
		cost                    = utils::json::GetUint(object, "cost");
		equipped_to_creature_id = utils::json::GetUint(object, "creature_id");
		level                   = utils::json::GetUint16(object, "level");
		market_status           = utils::json::GetUint8(object, "market_status");
		rarity                  = utils::json::GetUint8(object, "rarity");
		status                  = utils::json::GetUint8(object, "status");
		usage                   = utils::json::GetUint8(object, "usage");
		timestamp               = utils::json::GetUint64(object, "creation_date");

		SetRigblock(utils::json::GetUint16(object, "rigblock_asset_id"));
		SetPrefix(  utils::json::GetUint16(object, "prefix_asset_id"), false);
		SetPrefix(  utils::json::GetUint16(object, "prefix_secondary_asset_id"), true);
		SetSuffix(  utils::json::GetUint16(object, "suffix_asset_id"));
	}

	rapidjson::Value Part::WriteJson(rapidjson::Document::AllocatorType& allocator, uint32_t index, bool api) const { 
		rapidjson::Value object = utils::json::NewObject();
		utils::json::Set(object, "is_flair",         flair,                   allocator);
		utils::json::Set(object, "cost",             cost,                    allocator);
		utils::json::Set(object, "creature_id",      equipped_to_creature_id, allocator);
		utils::json::Set(object, "level",            level,                   allocator);
		utils::json::Set(object, "market_status",    market_status,           allocator);
		utils::json::Set(object, "rarity",           rarity,                  allocator);
		utils::json::Set(object, "status",           status,                  allocator);
		utils::json::Set(object, "usage",            usage,                   allocator);
		utils::json::Set(object, "creation_date",    timestamp,               allocator);
		if (api) {
            utils::json::Set(object, "id",           index,                   allocator);
            utils::json::Set(object, "reference_id", index,                   allocator);

            utils::json::Set(object, "rigblock_asset_id",         rigblock_asset_hash,         allocator);
            utils::json::Set(object, "prefix_asset_id",           prefix_asset_hash,           allocator);
            utils::json::Set(object, "prefix_secondary_asset_id", prefix_secondary_asset_hash, allocator);
            utils::json::Set(object, "suffix_asset_id",           suffix_asset_hash,           allocator);
        } else {
            utils::json::Set(object, "rigblock_asset_id",         rigblock_asset_id,           allocator);
            utils::json::Set(object, "prefix_asset_id",           prefix_asset_id,             allocator);
            utils::json::Set(object, "prefix_secondary_asset_id", prefix_secondary_asset_id,   allocator);
            utils::json::Set(object, "suffix_asset_id",           suffix_asset_id,             allocator);
        }
        return object;
	}

	void Part::SetRigblock(uint16_t rigblock) {
		if (!(rigblock >= 1 && rigblock <= 1573) && !(rigblock >= 10001 && rigblock <= 10835)) {
			rigblock = 1;
		}

		const std::string& rigblock_string = "_Generated/LootRigblock" + std::to_string(rigblock) + ".LootRigblock";
		rigblock_asset_id = rigblock;
		rigblock_asset_hash = utils::hash_id(rigblock_string.c_str());
	}

	void Part::SetPrefix(uint16_t prefix, bool secondary) {
		if (!(prefix >= 1 && prefix <= 338)) {
			prefix = 0;
		}

		std::string prefix_string;
		if (prefix > 0) {
			prefix_string = "_Generated/LootPrefix" + std::to_string(prefix) + ".LootPrefix";
		}

		if (secondary) {
			prefix_secondary_asset_id = prefix;
			prefix_secondary_asset_hash = utils::hash_id(prefix_string.c_str());
		} else {
			prefix_asset_id = prefix;
			prefix_asset_hash = utils::hash_id(prefix_string.c_str());
		}
	}

	void Part::SetSuffix(uint16_t suffix) {
		if (!(suffix >= 1 && suffix <= 83) && !(suffix >= 10001 && suffix <= 10275)) {
			suffix = 0;
		}

		std::string suffix_string;
		if (suffix > 0) {
			suffix_string = "_Generated/LootSuffix" + std::to_string(suffix) + ".LootSuffix";
		}

		suffix_asset_id = suffix;
		suffix_asset_hash = utils::hash_id(suffix_string.c_str());
	}

	void Part::SetStatus(uint8_t newStatus) {
		status = newStatus;
	}



	// Parts
	void Parts::ReadXml(const pugi::xml_node& node) {
		auto parts = node.child("parts");
		if (!parts) {
			return;
		}

		for (const auto& partNode : parts) {
			decltype(auto) part = mItems.emplace_back();
			part.ReadXml(partNode);
		}
	}

	void Parts::WriteXml(pugi::xml_node& node, bool api) const {
		if (auto parts = node.append_child("parts")) {
			uint32_t index = 0;
			for (const auto& part : mItems) {
				part.WriteXml(parts, ++index, api);
			}
		}
	}

	void Parts::ReadJson(rapidjson::Value& object) {
		if (!object.IsArray()) return;
		mItems.clear();
		for (auto& partNode : object.GetArray()) {
			decltype(auto) part = mItems.emplace_back();
			part.ReadJson(partNode);
		}
	}

	rapidjson::Value Parts::WriteJson(rapidjson::Document::AllocatorType& allocator, bool api) const { 
		rapidjson::Value value = utils::json::NewArray();
		for (const auto& part : mItems) {
			uint32_t index = 0;
			rapidjson::Value partNode = part.WriteJson(allocator, ++index, api);
			utils::json::Add(value, partNode, allocator);
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
			mName = utils::xml::GetString(user, "name");
			mEmail = utils::xml::GetString(user, "email");
			mPassword = utils::xml::GetString(user, "password"); // Hash this later?

			  mAccount.ReadXml(user);
			mCreatures.ReadXml(user);
			   mSquads.ReadXml(user);
			     mFeed.ReadXml(user);
			    mParts.ReadXml(user);
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
			utils::xml::Set(user, "name", mName);
			utils::xml::Set(user, "email", mEmail);
			utils::xml::Set(user, "password", mPassword);

			  mAccount.WriteXml(user);
			mCreatures.WriteXml(user);
			   mSquads.WriteXml(user);
			     mFeed.WriteXml(user);
			    mParts.WriteXml(user);
		}
		return document;
	}

	rapidjson::Value User::ToJson(rapidjson::Document::AllocatorType& allocator) {
		rapidjson::Value object = utils::json::NewObject();
		
		utils::json::Set(object, "name",     mName,     allocator);
		utils::json::Set(object, "email",    mEmail,    allocator);
		utils::json::Set(object, "password", mPassword, allocator);

		rapidjson::Value account   =   mAccount.WriteJson(allocator);
		rapidjson::Value creatures = mCreatures.WriteJson(allocator);
		rapidjson::Value squads    =    mSquads.WriteJson(allocator);
		rapidjson::Value feed      =      mFeed.WriteJson(allocator);
		rapidjson::Value parts     =     mParts.WriteJson(allocator);

		utils::json::Set(object, "account",   account,   allocator);
		utils::json::Set(object, "creatures", creatures, allocator);
		utils::json::Set(object, "squads",    squads,    allocator);
		utils::json::Set(object, "feed",      feed,      allocator);
		utils::json::Set(object, "parts",     parts,     allocator);

		return object;
	}

	void User::FromJson(rapidjson::Document& object) {
		mName     = utils::json::GetString(object, "name");
		mEmail    = utils::json::GetString(object, "email");
		mPassword = utils::json::GetString(object, "password");

		  mAccount.ReadJson(utils::json::Get(object, "account"));
		mCreatures.ReadJson(utils::json::Get(object, "creatures"));
		   mSquads.ReadJson(utils::json::Get(object, "squads"));
		     mFeed.ReadJson(utils::json::Get(object, "feed"));
		    mParts.ReadJson(utils::json::Get(object, "parts"));
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
