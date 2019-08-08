
// Include
#include "part.h"

#include "../utils/functions.h"
#include <algorithm>
#include <filesystem>

// Game
namespace Game {

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
		cost                    = object.GetObject()["cost"         ].GetUInt();
		equipped_to_creature_id = object.GetObject()["creature_id"  ].GetUInt();
		level                   = object.GetObject()["level"        ].GetUInt();
		market_status           = object.GetObject()["market_status"].GetUInt();
		rarity                  = object.GetObject()["rarity"       ].GetUInt();
		status                  = object.GetObject()["status"       ].GetUInt();
		usage                   = object.GetObject()["usage"        ].GetUInt();
		timestamp               = object.GetObject()["creation_date"].GetUInt64();

		SetRigblock(object.GetObject()["rigblock_asset_id"        ].GetUInt());
		SetPrefix(  object.GetObject()["prefix_asset_id"          ].GetUInt(), false);
		SetPrefix(  object.GetObject()["prefix_secondary_asset_id"].GetUInt(), true);
		SetSuffix(  object.GetObject()["suffix_asset_id"          ].GetUInt());
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

}
