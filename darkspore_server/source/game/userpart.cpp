
// Include
#include "user.h"
#include "config.h"
#include "userpart.h"
#include "../utils/functions.h"
#include "../repository/part.h"
#include <algorithm>
#include <filesystem>

// Game
namespace Game {
	
	// Part
	UserPart::UserPart() {

	}

	UserPart::UserPart(uint64_t identifier, uint32_t rigblock, uint64_t creator_id) {
		id = identifier;
		rigblock_asset_id = rigblock;
		user_id = creator_id;
	}

	UserPart::UserPart(const pugi::xml_node& node) {
		if (!ReadXml(node)) {
			rigblock_asset_id = 1;
		}
	}

	bool UserPart::ReadXml(const pugi::xml_node& node) {
		std::string_view nodeName = node.name();
		if (nodeName != "part") {
			return false;
		}

		id = utils::xml::GetString<uint16_t>(node, "id");
		user_id = utils::xml::GetString<uint64_t>(node, "user_id");
		equipped_to_creature_id = utils::xml::GetString<uint32_t>(node, "creature_id");
		status = utils::xml::GetString<uint8_t>(node, "status");
		flair = utils::xml::GetString<bool>(node, "is_flair");
		timestamp = utils::xml::GetString<uint64_t>(node, "creation_date");
		rigblock_asset_id = utils::xml::GetString<uint32_t>(node, "rigblock_asset_id");

		return true;
	}

	void UserPart::WriteSmallXml(pugi::xml_node& node) const {
		if (auto part = node.append_child("part")) {
			utils::xml::Set(part, "id", id);
			utils::xml::Set(part, "user_id", user_id);
			utils::xml::Set(part, "creature_id", equipped_to_creature_id);
			utils::xml::Set(part, "status", status);
			utils::xml::Set(part, "is_flair", flair);
			utils::xml::Set(part, "creation_date", timestamp);
			utils::xml::Set(part, "rigblock_asset_id", rigblock_asset_id);
		}
	}

	void UserPart::WriteXml(pugi::xml_node& node, bool api) const {
		auto partDetails = Repository::Parts::getById(rigblock_asset_id);

		if (auto part = node.append_child("part")) {
			utils::xml::Set(part, "is_flair", flair);
			utils::xml::Set(part, "cost", partDetails->cost);
			utils::xml::Set(part, "creature_id", equipped_to_creature_id);
			utils::xml::Set(part, "level", partDetails->level);
			utils::xml::Set(part, "market_status", partDetails->market_status);
			utils::xml::Set(part, "rarity", partDetails->rarity);
			utils::xml::Set(part, "status", status);
			utils::xml::Set(part, "usage", partDetails->usage);
			utils::xml::Set(part, "creation_date", timestamp);
			if (api) {
				utils::xml::Set(part, "id", id);
				utils::xml::Set(part, "reference_id", id);

				utils::xml::Set(part, "rigblock_asset_id", partDetails->rigblock_asset_hash);
				utils::xml::Set(part, "prefix_asset_id", partDetails->prefix_asset_hash);
				utils::xml::Set(part, "prefix_secondary_asset_id", partDetails->prefix_secondary_asset_hash);
				utils::xml::Set(part, "suffix_asset_id", partDetails->suffix_asset_hash);
			}
			else {
				utils::xml::Set(part, "rigblock_asset_id", rigblock_asset_id);
				utils::xml::Set(part, "prefix_asset_id", partDetails->prefix_asset_id);
				utils::xml::Set(part, "prefix_secondary_asset_id", partDetails->prefix_secondary_asset_id);
				utils::xml::Set(part, "suffix_asset_id", partDetails->suffix_asset_id);
			}
		}
	}

	void UserPart::ReadJson(rapidjson::Value& object) {
		if (!object.IsObject()) return;
		id = utils::json::GetUint16(object, "id");
		equipped_to_creature_id = utils::json::GetUint(object, "creature_id");
		status = utils::json::GetUint8(object, "status");
		timestamp = utils::json::GetUint64(object, "creation_date");
		rigblock_asset_id = utils::json::GetUint16(object, "rigblock_asset_id");
	}

	rapidjson::Value UserPart::WriteJson(rapidjson::Document::AllocatorType& allocator, bool api) const {
		auto part = Repository::Parts::getById(rigblock_asset_id);

		rapidjson::Value object = utils::json::NewObject();
		utils::json::Set(object, "is_flair", flair, allocator);
		utils::json::Set(object, "cost", part->cost, allocator);
		utils::json::Set(object, "creature_id", equipped_to_creature_id, allocator);
		utils::json::Set(object, "level", part->level, allocator);
		utils::json::Set(object, "market_status", part->market_status, allocator);
		utils::json::Set(object, "rarity", part->rarity, allocator);
		utils::json::Set(object, "status", status, allocator);
		utils::json::Set(object, "usage", part->usage, allocator);
		utils::json::Set(object, "creation_date", timestamp, allocator);
		if (api) {
			utils::json::Set(object, "id", id, allocator);
			utils::json::Set(object, "reference_id", id, allocator);

			utils::json::Set(object, "rigblock_asset_id", part->rigblock_asset_hash, allocator);
			utils::json::Set(object, "prefix_asset_id", part->prefix_asset_hash, allocator);
			utils::json::Set(object, "prefix_secondary_asset_id", part->prefix_secondary_asset_hash, allocator);
			utils::json::Set(object, "suffix_asset_id", part->suffix_asset_hash, allocator);
		}
		else {
			utils::json::Set(object, "rigblock_asset_id", rigblock_asset_id, allocator);
			utils::json::Set(object, "prefix_asset_id", part->prefix_asset_id, allocator);
			utils::json::Set(object, "prefix_secondary_asset_id", part->prefix_secondary_asset_id, allocator);
			utils::json::Set(object, "suffix_asset_id", part->suffix_asset_id, allocator);
		}
		return object;
	}

	void UserPart::SetStatus(uint8_t newStatus) {
		status = newStatus;
	}



	// Parts
	UserPart* UserParts::GetPartById(uint32_t id) {
		UserPart* partPtr = nullptr;
		for (auto& part : mItems) {
			if (part.id == id) {
				partPtr = &part;
				break;
			}
		}
		return partPtr;
	}

	void UserParts::ReadXml(const pugi::xml_node& node) {
		auto parts = node.child("parts");
		if (!parts) {
			return;
		}

		for (const auto& partNode : parts) {
			decltype(auto) part = mItems.emplace_back();
			part.ReadXml(partNode);
		}
	}

	void UserParts::WriteSmallXml(pugi::xml_node& node) const {
		if (auto parts = node.append_child("parts")) {
			for (const auto& part : mItems) {
				part.WriteSmallXml(parts);
			}
		}
	}

	void UserParts::WriteXml(pugi::xml_node& node, bool api) const {
		if (auto parts = node.append_child("parts")) {
			for (const auto& part : mItems) {
				part.WriteXml(parts, api);
			}
		}
	}

	void UserParts::ReadJson(rapidjson::Value& object) {
		if (!object.IsArray()) return;
		mItems.clear();
		for (auto& partNode : object.GetArray()) {
			decltype(auto) part = mItems.emplace_back();
			part.ReadJson(partNode);
		}
	}

	rapidjson::Value UserParts::WriteJson(rapidjson::Document::AllocatorType& allocator, bool api) const {
		rapidjson::Value value = utils::json::NewArray();
		for (const auto& part : mItems) {
			rapidjson::Value partNode = part.WriteJson(allocator, api);
			utils::json::Add(value, partNode, allocator);
		}
		return value;
	}

	void UserParts::Add(UserPart part) {
		mItems.emplace_back(part);
	}
}
