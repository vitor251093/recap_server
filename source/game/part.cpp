
// Include
#include "user.h"
#include "config.h"
#include "part.h"
#include "../utils/functions.h"
#include <algorithm>
#include <filesystem>

// Game
namespace Game {

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

		cost          = utils::xml::GetString<uint32_t>(node, "cost");
		level         = utils::xml::GetString<uint16_t>(node, "level");
		market_status = utils::xml::GetString<uint8_t>(node, "market_status");
		rarity        = utils::xml::GetString<uint8_t>(node, "rarity");
		usage         = utils::xml::GetString<uint8_t>(node, "usage");

		stats                  = utils::xml::GetString(node, "stats");
		type_full              = utils::xml::GetString(node, "type_full");
		class_types_full       = utils::xml::GetString(node, "class_types_full");
		science_types_full     = utils::xml::GetString(node, "science_types_full");
		rarity_full            = utils::xml::GetString(node, "rarity_full");
		png_key                = utils::xml::GetString(node, "png_key");
		weapon_damage_modifier = utils::xml::GetString(node, "weapon_damage_modifier");
		modifiers              = utils::xml::GetString(node, "modifiers");
		rand_seed              = utils::xml::GetString(node, "rand_seed");

		SetRigblock(utils::xml::GetString<uint32_t>(node, "rigblock_asset_id"));
		SetPrefix(utils::xml::GetString<uint32_t>(node, "prefix_asset_id"), false);
		SetPrefix(utils::xml::GetString<uint32_t>(node, "prefix_secondary_asset_id"), true);
		SetSuffix(utils::xml::GetString<uint32_t>(node, "suffix_asset_id"));

		return true;
	}

	void Part::WriteXml(pugi::xml_node& node, uint32_t index, bool api) const {
		if (auto part = node.append_child("part")) {
			utils::xml::Set(part, "cost", cost);
			utils::xml::Set(part, "level", level);
			utils::xml::Set(part, "market_status", market_status);
			utils::xml::Set(part, "rarity", rarity);
			utils::xml::Set(part, "usage", usage);

			if (api) {
				utils::xml::Set(part, "id", index);
				utils::xml::Set(part, "reference_id", index);

				utils::xml::Set(part, "rigblock_asset_id", rigblock_asset_hash);
				utils::xml::Set(part, "prefix_asset_id", prefix_asset_hash);
				utils::xml::Set(part, "prefix_secondary_asset_id", prefix_secondary_asset_hash);
				utils::xml::Set(part, "suffix_asset_id", suffix_asset_hash);
			}
			else {
				utils::xml::Set(part, "rigblock_asset_id", rigblock_asset_id);
				utils::xml::Set(part, "prefix_asset_id", prefix_asset_id);
				utils::xml::Set(part, "prefix_secondary_asset_id", prefix_secondary_asset_id);
				utils::xml::Set(part, "suffix_asset_id", suffix_asset_id);
			}

			utils::xml::Set(part, "stats", stats);
			utils::xml::Set(part, "type_full", type_full);
			utils::xml::Set(part, "class_types_full", class_types_full);
			utils::xml::Set(part, "science_types_full", science_types_full);
			utils::xml::Set(part, "rarity_full", rarity_full);
			utils::xml::Set(part, "png_key", png_key);
			utils::xml::Set(part, "weapon_damage_modifier", weapon_damage_modifier);
			utils::xml::Set(part, "modifiers", modifiers);
			utils::xml::Set(part, "rand_seed", rand_seed);
		}
	}

	void Part::ReadJson(rapidjson::Value& object) {
		if (!object.IsObject()) return;

		cost = utils::json::GetUint(object, "cost");
		level = utils::json::GetUint16(object, "level");
		market_status = utils::json::GetUint8(object, "market_status");
		rarity = utils::json::GetUint8(object, "rarity");
		usage = utils::json::GetUint8(object, "usage");

		stats = utils::json::GetString(object, "stats");
		type_full = utils::json::GetString(object, "type_full");
		class_types_full = utils::json::GetString(object, "class_types_full");
		science_types_full = utils::json::GetString(object, "science_types_full");
		rarity_full = utils::json::GetString(object, "rarity_full");
		png_key = utils::json::GetString(object, "png_key");
		weapon_damage_modifier = utils::json::GetString(object, "weapon_damage_modifier");
		modifiers = utils::json::GetString(object, "modifiers");
		rand_seed = utils::json::GetString(object, "rand_seed");
		
		SetRigblock(utils::json::GetUint16(object, "rigblock_asset_id"));
		SetPrefix(utils::json::GetUint16(object, "prefix_asset_id"), false);
		SetPrefix(utils::json::GetUint16(object, "prefix_secondary_asset_id"), true);
		SetSuffix(utils::json::GetUint16(object, "suffix_asset_id"));
	}

	rapidjson::Value Part::WriteJson(rapidjson::Document::AllocatorType& allocator, uint32_t index, bool api) const {
		rapidjson::Value object = utils::json::NewObject();
		utils::json::Set(object, "cost", cost, allocator);
		utils::json::Set(object, "level", level, allocator);
		utils::json::Set(object, "market_status", market_status, allocator);
		utils::json::Set(object, "rarity", rarity, allocator);
		utils::json::Set(object, "usage", usage, allocator);

		if (api) {
			utils::json::Set(object, "id", index, allocator);
			utils::json::Set(object, "reference_id", index, allocator);

			utils::json::Set(object, "rigblock_asset_id", rigblock_asset_hash, allocator);
			utils::json::Set(object, "prefix_asset_id", prefix_asset_hash, allocator);
			utils::json::Set(object, "prefix_secondary_asset_id", prefix_secondary_asset_hash, allocator);
			utils::json::Set(object, "suffix_asset_id", suffix_asset_hash, allocator);
		}
		else {
			utils::json::Set(object, "rigblock_asset_id", rigblock_asset_id, allocator);
			utils::json::Set(object, "prefix_asset_id", prefix_asset_id, allocator);
			utils::json::Set(object, "prefix_secondary_asset_id", prefix_secondary_asset_id, allocator);
			utils::json::Set(object, "suffix_asset_id", suffix_asset_id, allocator);
		}

		utils::json::Set(object, "stats", stats, allocator);
		utils::json::Set(object, "type_full", type_full, allocator);
		utils::json::Set(object, "class_types_full", class_types_full, allocator);
		utils::json::Set(object, "science_types_full", science_types_full, allocator);
		utils::json::Set(object, "rarity_full", rarity_full, allocator);
		utils::json::Set(object, "png_key", png_key, allocator);
		utils::json::Set(object, "weapon_damage_modifier", weapon_damage_modifier, allocator);
		utils::json::Set(object, "modifiers", modifiers, allocator);
		utils::json::Set(object, "rand_seed", rand_seed, allocator);

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
		}
		else {
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



	// Parts
	Part* Parts::GetPartById(uint32_t id) {
		Part* partPtr = nullptr;
		for (auto& part : mItems) {
			if (part.rigblock_asset_id == id) {
				partPtr = &part;
				break;
			}
		}
		return partPtr;
	}

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

	void Parts::Add(Part part) {
		mItems.emplace_back(part);
	}
}
