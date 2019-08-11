
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

		tutorialCompleted = utils::xml_get_text_node(account, "tutorial_completed") == "Y";
		grantAllAccess    = utils::xml_get_text_node<uint32_t>(account, "grant_all_access");
		grantOnlineAccess = utils::xml_get_text_node<uint32_t>(account, "grant_online_access");

		chainProgression  = utils::xml_get_text_node<uint32_t>(account, "chain_progression");
		creatureRewards   = utils::xml_get_text_node<uint32_t>(account, "creature_rewards");

		currentGameId      = utils::xml_get_text_node<uint32_t>(account, "current_game_id");
		currentPlaygroupId = utils::xml_get_text_node<uint32_t>(account, "current_playgroup_id");

		defaultDeckPveId  = utils::xml_get_text_node<uint32_t>(account, "default_deck_pve_id");
		defaultDeckPvpId  = utils::xml_get_text_node<uint32_t>(account, "default_deck_pvp_id");

		level    = utils::xml_get_text_node<uint32_t>(account, "level");
		xp       = utils::xml_get_text_node<uint32_t>(account, "xp");
		dna      = utils::xml_get_text_node<uint32_t>(account, "dna");
		avatarId = std::clamp<uint32_t>(utils::xml_get_text_node<uint32_t>(account, "avatar_id"), 0, 16);
		id       = utils::xml_get_text_node<uint32_t>(account, "id");

		newPlayerInventory = utils::xml_get_text_node<uint32_t>(account, "new_player_inventory");
		newPlayerProgress  = utils::xml_get_text_node<uint32_t>(account, "new_player_progress");

		cashoutBonusTime = utils::xml_get_text_node<uint32_t>(account, "cashout_bonus_time");
		starLevel        = utils::xml_get_text_node<uint32_t>(account, "star_level");

		unlockCatalysts = utils::xml_get_text_node<uint32_t>(account, "unlock_catalysts");
		unlockDiagonalCatalysts = utils::xml_get_text_node<uint32_t>(account, "unlock_diagonal_catalysts");
		unlockFuelTanks         = utils::xml_get_text_node<uint32_t>(account, "unlock_fuel_tanks");
		unlockInventoryIdentify = utils::xml_get_text_node<uint32_t>(account, "unlock_inventory");
		unlockPveDecks = utils::xml_get_text_node<uint32_t>(account, "unlock_pve_decks");
		unlockPvpDecks = utils::xml_get_text_node<uint32_t>(account, "unlock_pvp_decks");
		unlockStats    = utils::xml_get_text_node<uint32_t>(account, "unlock_stats");
		unlockInventoryIdentify = utils::xml_get_text_node<uint32_t>(account, "unlock_inventory_identify");
		unlockEditorFlairSlots  = utils::xml_get_text_node<uint32_t>(account, "unlock_editor_flair_slots");

		upsell = utils::xml_get_text_node<uint32_t>(account, "upsell");

		capLevel       = utils::xml_get_text_node<uint32_t>(account, "cap_level");
		capProgression = utils::xml_get_text_node<uint32_t>(account, "cap_progression");
	}

	void Account::WriteXml(pugi::xml_node& node) const {
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

	void Account::ReadJson(utils::jsonObject& object) { 
		tutorialCompleted       = object.GetBool("tutorial_completed");
		chainProgression        = object.GetUint("chain_progression");
		creatureRewards         = object.GetUint("creature_rewards");
		currentGameId           = object.GetUint("current_game_id");
		currentPlaygroupId      = object.GetUint("current_playgroup_id");
		defaultDeckPveId        = object.GetUint("default_deck_pve_id");
		defaultDeckPvpId        = object.GetUint("default_deck_pvp_id");
		level                   = object.GetUint("level");
		avatarId                = object.GetUint("avatar_id");
		id                      = object.GetUint("id");
		dna                     = object.GetUint("dna");
		newPlayerInventory      = object.GetUint("new_player_inventory");
		newPlayerProgress       = object.GetUint("new_player_progress");
		cashoutBonusTime        = object.GetUint("cashout_bonus_time");
		starLevel               = object.GetUint("star_level");
		unlockCatalysts         = object.GetUint("unlock_catalysts");
		unlockDiagonalCatalysts = object.GetUint("unlock_diagonal_catalysts");
		unlockFuelTanks         = object.GetUint("unlock_fuel_tanks");
		unlockInventoryIdentify = object.GetUint("unlock_inventory");
		unlockPveDecks          = object.GetUint("unlock_pve_decks");
		unlockPvpDecks          = object.GetUint("unlock_pvp_decks");
		unlockStats             = object.GetUint("unlock_stats");
		unlockInventoryIdentify = object.GetUint("unlock_inventory_identify");
		unlockEditorFlairSlots  = object.GetUint("unlock_editor_flair_slots");
		upsell                  = object.GetUint("upsell");
		xp                      = object.GetUint("xp");
		grantAllAccess          = object.GetBool("grant_all_access");
		grantOnlineAccess       = object.GetBool("grant_online_access");
		capLevel                = object.GetUint("cap_level");
		capProgression          = object.GetUint("cap_progression");
	}

	void Account::WriteJson(utils::jsonObject& object) const { 
		object.Set("tutorial_completed",        tutorialCompleted);
		object.Set("chain_progression",         chainProgression);
		object.Set("creature_rewards",          creatureRewards);
		object.Set("current_game_id",           currentGameId);
		object.Set("current_playgroup_id",      currentPlaygroupId);
		object.Set("default_deck_pve_id",       defaultDeckPveId);
		object.Set("default_deck_pvp_id",       defaultDeckPvpId);
		object.Set("level",                     level);
		object.Set("avatar_id",                 avatarId);
		object.Set("blaze_id",                  id);
		object.Set("id",                        id);
		object.Set("dna",                       dna);
		object.Set("new_player_inventory",      newPlayerInventory);
		object.Set("new_player_progress",       newPlayerProgress);
		object.Set("cashout_bonus_time",        cashoutBonusTime);
		object.Set("star_level",                starLevel);
		object.Set("unlock_catalysts",          unlockCatalysts);
		object.Set("unlock_diagonal_catalysts", unlockDiagonalCatalysts);
		object.Set("unlock_fuel_tanks",         unlockFuelTanks);
		object.Set("unlock_inventory",          unlockInventoryIdentify);
		object.Set("unlock_pve_decks",          unlockPveDecks);
		object.Set("unlock_pvp_decks",          unlockPvpDecks);
		object.Set("unlock_stats",              unlockStats);
		object.Set("unlock_inventory_identify", unlockInventoryIdentify);
		object.Set("unlock_editor_flair_slots", unlockEditorFlairSlots);
		object.Set("upsell",                    upsell);
		object.Set("xp",                        xp);
		object.Set("grant_all_access",          grantAllAccess);
		object.Set("grant_online_access",       grantOnlineAccess);
		object.Set("cap_level",                 capLevel);
		object.Set("cap_progression",           capProgression);
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
			feedItem.accountId = utils::xml_get_text_node<uint32_t>(item, "account_id");
			feedItem.id = utils::xml_get_text_node<uint32_t>(item, "id");
			feedItem.messageId = utils::xml_get_text_node<uint32_t>(item, "message_id");
			feedItem.metadata = utils::xml_get_text_node(item, "metadata");
			feedItem.name = utils::xml_get_text_node(item, "name");
			feedItem.timestamp = utils::xml_get_text_node<uint64_t>(item, "time");
		}
	}

	void Feed::WriteXml(pugi::xml_node& node) const {
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

	void Feed::ReadJson(utils::jsonArray& array) {
		mItems.clear();
		for (auto& object : array) {
			auto item = object.GetAsObject();
			decltype(auto) feedItem = mItems.emplace_back();
			feedItem.accountId = item.GetUint("account_id");
			feedItem.id        = item.GetUint("id");
			feedItem.messageId = item.GetUint("message_id");
			feedItem.metadata  = item.GetString("metadata");
			feedItem.name      = item.GetString("name"); 
			feedItem.timestamp = item.GetUint64("time");
		}
	}

	void Feed::WriteJson(utils::jsonArray& array) const {
		for (const auto& feedItem : mItems) {
			auto object = array.NewObject();
			object.Set("metadata",   feedItem.metadata);
			object.Set("name",       feedItem.name);
			object.Set("time",       feedItem.timestamp);
			object.Set("account_id", feedItem.accountId);
			object.Set("id",         feedItem.id);
			object.Set("message_id", feedItem.messageId);
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

		flair = utils::xml_get_text_node<bool>(node, "is_flair");
		cost = utils::xml_get_text_node<uint32_t>(node, "cost");
		equipped_to_creature_id = utils::xml_get_text_node<uint32_t>(node, "creature_id");
		level = utils::xml_get_text_node<uint16_t>(node, "level");
		market_status = utils::xml_get_text_node<uint8_t>(node, "market_status");
		rarity = utils::xml_get_text_node<uint8_t>(node, "rarity");
		status = utils::xml_get_text_node<uint8_t>(node, "status");
		usage = utils::xml_get_text_node<uint8_t>(node, "usage");
		timestamp = utils::xml_get_text_node<uint64_t>(node, "creation_date");

		SetRigblock(utils::xml_get_text_node<uint32_t>(node, "rigblock_asset_id"));
		SetPrefix(utils::xml_get_text_node<uint32_t>(node, "prefix_asset_id"), false);
		SetPrefix(utils::xml_get_text_node<uint32_t>(node, "prefix_secondary_asset_id"), true);
		SetSuffix(utils::xml_get_text_node<uint32_t>(node, "suffix_asset_id"));

		return true;
	}

	void Part::WriteXml(pugi::xml_node& node, uint32_t index, bool api) const {
		if (auto part = node.append_child("part")) {
			utils::xml_add_text_node(part, "is_flair", flair);
			utils::xml_add_text_node(part, "cost", cost);
			utils::xml_add_text_node(part, "creature_id", equipped_to_creature_id);
			utils::xml_add_text_node(part, "level", level);
			utils::xml_add_text_node(part, "market_status", market_status);
			utils::xml_add_text_node(part, "rarity", rarity);
			utils::xml_add_text_node(part, "status", status);
			utils::xml_add_text_node(part, "usage", usage);
			utils::xml_add_text_node(part, "creation_date", timestamp);
			if (api) {
				utils::xml_add_text_node(part, "id", index);
				utils::xml_add_text_node(part, "reference_id", index);

				utils::xml_add_text_node(part, "rigblock_asset_id", rigblock_asset_hash);
				utils::xml_add_text_node(part, "prefix_asset_id", prefix_asset_hash);
				utils::xml_add_text_node(part, "prefix_secondary_asset_id", prefix_secondary_asset_hash);
				utils::xml_add_text_node(part, "suffix_asset_id", suffix_asset_hash);
			} else {
				utils::xml_add_text_node(part, "rigblock_asset_id", rigblock_asset_id);
				utils::xml_add_text_node(part, "prefix_asset_id", prefix_asset_id);
				utils::xml_add_text_node(part, "prefix_secondary_asset_id", prefix_secondary_asset_id);
				utils::xml_add_text_node(part, "suffix_asset_id", suffix_asset_id);
			}
		}
	}

	void Part::ReadJson(utils::jsonObject& object) {
		flair                   = object.GetBool("is_flair");
		cost                    = object.GetUint("cost");
		equipped_to_creature_id = object.GetUint("creature_id");
		level                   = object.GetUint("level");
		market_status           = object.GetUint("market_status");
		rarity                  = object.GetUint("rarity");
		status                  = object.GetUint("status");
		usage                   = object.GetUint("usage");
		timestamp               = object.GetUint64("creation_date");

		SetRigblock(object.GetUint("rigblock_asset_id"        ));
		SetPrefix(  object.GetUint("prefix_asset_id"          ), false);
		SetPrefix(  object.GetUint("prefix_secondary_asset_id"), true);
		SetSuffix(  object.GetUint("suffix_asset_id"          ));
	}

	void Part::WriteJson(utils::jsonObject& object, uint32_t index, bool api) const { 
		object.Set("is_flair",         flair);
		object.Set("cost",             cost);
		object.Set("creature_id",      equipped_to_creature_id);
		object.Set("level",            level);
		object.Set("market_status",    market_status);
		object.Set("rarity",           rarity);
		object.Set("status",           status);
		object.Set("usage",            usage);
		object.Set("creation_date",  timestamp);
		if (api) {
            object.Set("id",           index);
            object.Set("reference_id", index);

            object.Set("rigblock_asset_id",         rigblock_asset_hash);
            object.Set("prefix_asset_id",           prefix_asset_hash);
            object.Set("prefix_secondary_asset_id", prefix_secondary_asset_hash);
            object.Set("suffix_asset_id",           suffix_asset_hash);
        } else {
            object.Set("rigblock_asset_id",         rigblock_asset_id);
            object.Set("prefix_asset_id",           prefix_asset_id);
            object.Set("prefix_secondary_asset_id", prefix_secondary_asset_id);
            object.Set("suffix_asset_id",           suffix_asset_id);
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

	void Parts::ReadJson(utils::jsonArray& object) {
		mItems.clear();
		for (auto& partNode : object) {
			decltype(auto) part = mItems.emplace_back();
			part.ReadJson(partNode.GetAsObject());
		}
	}

	void Parts::WriteJson(utils::jsonArray& object, bool api) const { 
		for (const auto& part : mItems) {
            uint32_t index = 0;
			part.WriteJson(object.NewObject(), ++index, api);
		}
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
			utils::xml_add_text_node(user, "name", mName);
			utils::xml_add_text_node(user, "email", mEmail);
			utils::xml_add_text_node(user, "password", mPassword);

			  mAccount.WriteXml(user);
			mCreatures.WriteXml(user);
			   mSquads.WriteXml(user);
			     mFeed.WriteXml(user);
			    mParts.WriteXml(user);
		}
		return document;
	}

	rapidjson::Value User::ToJson(utils::jsonObject& object) {
		object.Set("name",     mName);
		object.Set("email",    mEmail);
		object.Set("password", mPassword);
		
		  mAccount.WriteJson(object.NewObject("account"));

		object.AddMember("account",     mAccount.WriteJson(allocator), allocator);
		object.AddMember("creatures", mCreatures.WriteJson(allocator), allocator);
		object.AddMember("squads",       mSquads.WriteJson(allocator), allocator);
		object.AddMember("feed",           mFeed.WriteJson(allocator), allocator);
		object.AddMember("parts",         mParts.WriteJson(allocator), allocator);

		return object;
	}

	void User::FromJson(utils::jsonObject& object) {
		mName     = object.GetString("name");
		mEmail    = object.GetObject("email");
		mPassword = object.GetObject("password");

		  mAccount.ReadJson(object.GetObject()["account"]);
		mCreatures.ReadJson(object.GetObject()["creatures"]);
		   mSquads.ReadJson(object.GetObject()["squads"]);
		     mFeed.ReadJson(object.GetObject()["feed"]);
		    mParts.ReadJson(object.GetObject()["parts"]);
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
