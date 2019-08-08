
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

	void Account::ReadJson(rapidjson::Value& object) { 
		tutorialCompleted       = object.GetObject()["tutorial_completed"        ].GetBool();
		chainProgression        = object.GetObject()["chain_progression"         ].GetUint();
		creatureRewards         = object.GetObject()["creature_rewards"          ].GetUint();
		currentGameId           = object.GetObject()["current_game_id"           ].GetUint();
		currentPlaygroupId      = object.GetObject()["current_playgroup_id"      ].GetUint();
		defaultDeckPveId        = object.GetObject()["default_deck_pve_id"       ].GetUint();
		defaultDeckPvpId        = object.GetObject()["default_deck_pvp_id"       ].GetUint();
		level                   = object.GetObject()["level"                     ].GetUint();
		avatarId                = object.GetObject()["avatar_id"                 ].GetUint();
		id                      = object.GetObject()["id"                        ].GetUint();
		dna                     = object.GetObject()["dna"                       ].GetUint();
		newPlayerInventory      = object.GetObject()["new_player_inventory"      ].GetUint();
		newPlayerProgress       = object.GetObject()["new_player_progress"       ].GetUint();
		cashoutBonusTime        = object.GetObject()["cashout_bonus_time"        ].GetUint();
		starLevel               = object.GetObject()["star_level"                ].GetUint();
		unlockCatalysts         = object.GetObject()["unlock_catalysts"          ].GetUint();
		unlockDiagonalCatalysts = object.GetObject()["unlock_diagonal_catalysts" ].GetUint();
		unlockFuelTanks         = object.GetObject()["unlock_fuel_tanks"         ].GetUint();
		unlockInventoryIdentify = object.GetObject()["unlock_inventory"          ].GetUint();
		unlockPveDecks          = object.GetObject()["unlock_pve_decks"          ].GetUint();
		unlockPvpDecks          = object.GetObject()["unlock_pvp_decks"          ].GetUint();
		unlockStats             = object.GetObject()["unlock_stats"              ].GetUint();
		unlockInventoryIdentify = object.GetObject()["unlock_inventory_identify" ].GetUint();
		unlockEditorFlairSlots  = object.GetObject()["unlock_editor_flair_slots" ].GetUint();
		upsell                  = object.GetObject()["upsell"                    ].GetUint();
		xp                      = object.GetObject()["xp"                        ].GetUint();
		grantAllAccess          = object.GetObject()["grant_all_access"          ].GetBool();
		grantOnlineAccess       = object.GetObject()["grant_online_access"       ].GetBool();
		capLevel                = object.GetObject()["cap_level"                 ].GetUint();
		capProgression          = object.GetObject()["cap_progression"           ].GetUint();
	}

	rapidjson::Value Account::WriteJson(rapidjson::Document::AllocatorType& allocator) const { 
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

	void Feed::ReadJson(rapidjson::Value& object) {
		mItems.clear();
		for (auto& item : object.GetArray()) {
			decltype(auto) feedItem = mItems.emplace_back();
			feedItem.accountId = item.GetObject()["account_id"].GetUint();
			feedItem.id        = item.GetObject()["id"].GetUint();
			feedItem.messageId = item.GetObject()["message_id"].GetUint();
			feedItem.metadata  = item.GetObject()["metadata"].GetString();
			feedItem.name      = item.GetObject()["name"].GetString(); 
			feedItem.timestamp = item.GetObject()["time"].GetUint64();
		}
	}

	rapidjson::Value Feed::WriteJson(rapidjson::Document::AllocatorType& allocator) const {
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



	// Part
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

	void Part::ReadJson(rapidjson::Value& object) {
		flair                   = object.GetObject()["is_flair"     ].GetBool();
		cost                    = object.GetObject()["cost"         ].GetUint();
		equipped_to_creature_id = object.GetObject()["creature_id"  ].GetUint();
		level                   = object.GetObject()["level"        ].GetUint();
		market_status           = object.GetObject()["market_status"].GetUint();
		rarity                  = object.GetObject()["rarity"       ].GetUint();
		status                  = object.GetObject()["status"       ].GetUint();
		usage                   = object.GetObject()["usage"        ].GetUint();
		timestamp               = object.GetObject()["creation_date"].GetUInt64();

		SetRigblock(object.GetObject()["rigblock_asset_id"        ].GetUint());
		SetPrefix(  object.GetObject()["prefix_asset_id"          ].GetUint(), false);
		SetPrefix(  object.GetObject()["prefix_secondary_asset_id"].GetUint(), true);
		SetSuffix(  object.GetObject()["suffix_asset_id"          ].GetUint());
	}

	rapidjson::Value Part::WriteJson(rapidjson::Document::AllocatorType& allocator, uint32_t index, bool api) const { 
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember("is_flair",         rapidjson::Value{}.SetBool(gearScore),  allocator);
		object.AddMember("cost",             rapidjson::Value{}.SetUint(itemPoints), allocator);
		object.AddMember("creature_id",      rapidjson::Value{}.SetUint(nounId),     allocator);
		object.AddMember("level",            rapidjson::Value{}.SetUint(id),         allocator);
		object.AddMember("market_status",    rapidjson::Value{}.SetUint(version),    allocator);
		object.AddMember("rarity",           rapidjson::Value{}.SetUint(itemPoints), allocator);
		object.AddMember("status",           rapidjson::Value{}.SetUint(nounId),     allocator);
		object.AddMember("usage",            rapidjson::Value{}.SetUint(id),         allocator);
		object.AddMember("creation_date",    rapidjson::Value{}.SetUint64(version),  allocator);
		if (api) {
            object.AddMember("id",           rapidjson::Value{}.SetUint(index),      allocator);
            object.AddMember("reference_id", rapidjson::Value{}.SetUint(index),      allocator);

            object.AddMember("rigblock_asset_id",         rapidjson::Value{}.SetUint(rigblock_asset_hash),         allocator);
            object.AddMember("prefix_asset_id",           rapidjson::Value{}.SetUint(prefix_asset_hash),           allocator);
            object.AddMember("prefix_secondary_asset_id", rapidjson::Value{}.SetUint(prefix_secondary_asset_hash), allocator);
            object.AddMember("suffix_asset_id",           rapidjson::Value{}.SetUint(suffix_asset_hash),           allocator);
        } else {
            object.AddMember("rigblock_asset_id",         rapidjson::Value{}.SetUint(rigblock_asset_id),           allocator);
            object.AddMember("prefix_asset_id",           rapidjson::Value{}.SetUint(prefix_asset_id),             allocator);
            object.AddMember("prefix_secondary_asset_id", rapidjson::Value{}.SetUint(prefix_secondary_asset_id),   allocator);
            object.AddMember("suffix_asset_id",           rapidjson::Value{}.SetUint(suffix_asset_id),             allocator);
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
		mItems.clear();
		for (auto& partNode : object.GetArray())
			decltype(auto) part = mItems.emplace_back();
			part.ReadJson(partNode);
		}
	}

	rapidjson::Value Parts::WriteJson(rapidjson::Document::AllocatorType& allocator, bool api) const { 
		rapidjson::Value value(rapidjson::kArrayType);
		for (const auto& part : mItems) {
            uint32_t index = 0;
			value.PushBack(part.WriteJson(allocator, ++index, api), allocator);
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

	rapidjson::Value User::ToJson(rapidjson::Document::AllocatorType& allocator) {
		rapidjson::Value object(rapidjson::kObjectType);
		
		utils::json_add_text_to_object(object, "name",     mName,     allocator);
		utils::json_add_text_to_object(object, "email",    mEmail,    allocator);
		utils::json_add_text_to_object(object, "password", mPassword, allocator);

		object.AddMember("account",     mAccount.WriteJson(allocator), allocator);
		object.AddMember("creatures", mCreatures.WriteJson(allocator), allocator);
		object.AddMember("squads",       mSquads.WriteJson(allocator), allocator);
		object.AddMember("feed",           mFeed.WriteJson(allocator), allocator);
		object.AddMember("parts",         mParts.WriteJson(allocator), allocator);

		return object;
	}

	void User::FromJson(rapidjson::Document& object) {
		mName     = object.GetObject()["name"].GetString();
		mEmail    = object.GetObject()["email"].GetString();
		mPassword = object.GetObject()["password"].GetString();

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
