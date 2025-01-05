
// Include
#include "part.h"

#include "utils/functions.h"

#include <map>

// Part names
std::map<uint16_t, std::string_view> partNames{

};

// SporeNet
namespace SporeNet {
	// Part
	std::string_view GetName(uint16_t id) {
		using namespace std::literals;

		return ""sv;
	}

	Part::Part(uint32_t rigblock) {
		SetRigblock(rigblock);
		SetPrefix(0, false);
		SetPrefix(0, true);
		SetSuffix(0);
	}

	Part::Part(const pugi::xml_node& node) {
		if (!Read(node)) {
			SetRigblock(1);
			SetPrefix(0, false);
			SetPrefix(0, true);
			SetSuffix(0);
		}
	}
	Part::Part(rapidjson::Value& object) {
		if (!Read(object)) {
			SetRigblock(1);
			SetPrefix(0, false);
			SetPrefix(0, true);
			SetSuffix(0);
		}
	}

	bool Part::Read(const pugi::xml_node& node) {
		std::string_view nodeName = node.name();
		if (nodeName != "part") {
			return false;
		}

		mIsFlair = utils::xml_get_text_node<bool>(node, "is_flair");
		mCost = utils::xml_get_text_node<uint32_t>(node, "cost");
		mEquippedToCreatureId = utils::xml_get_text_node<uint32_t>(node, "creature_id");
		mLevel = utils::xml_get_text_node<uint16_t>(node, "level");
		mMarketStatus = utils::xml_get_text_node<uint8_t>(node, "market_status");
		mRarity = utils::xml_get_text_node<PartRarity>(node, "rarity");
		mStatus = utils::xml_get_text_node<uint8_t>(node, "status");
		mUsage = utils::xml_get_text_node<uint8_t>(node, "usage");
		mTimestamp = utils::xml_get_text_node<uint64_t>(node, "creation_date");

		SetRigblock(utils::xml_get_text_node<uint32_t>(node, "rigblock_asset_id"));
		SetPrefix(utils::xml_get_text_node<uint32_t>(node, "prefix_asset_id"), false);
		SetPrefix(utils::xml_get_text_node<uint32_t>(node, "prefix_secondary_asset_id"), true);
		SetSuffix(utils::xml_get_text_node<uint32_t>(node, "suffix_asset_id"));

		return true;
	}

	void Part::Write(pugi::xml_node& node) const {
		auto part = node.append_child("part");

		utils::xml_add_text_node(part, "is_flair", mIsFlair);
		utils::xml_add_text_node(part, "cost", mCost);
		utils::xml_add_text_node(part, "creature_id", mEquippedToCreatureId);
		utils::xml_add_text_node(part, "level", mLevel);
		utils::xml_add_text_node(part, "market_status", mMarketStatus);
		utils::xml_add_text_node(part, "rarity", mRarity);
		utils::xml_add_text_node(part, "status", mStatus);
		utils::xml_add_text_node(part, "usage", mUsage);
		utils::xml_add_text_node(part, "creation_date", mTimestamp);
		utils::xml_add_text_node(part, "rigblock_asset_id", mRigblockAssetId);
		utils::xml_add_text_node(part, "prefix_asset_id", mPrefixAssetId);
		utils::xml_add_text_node(part, "prefix_secondary_asset_id", mPrefixSecondaryAssetId);
		utils::xml_add_text_node(part, "suffix_asset_id", mSuffixAssetId);
	}

	void Part::WriteApi(pugi::xml_node& node, uint32_t index, bool offer) const {
		auto part = node.append_child("part");
		if (offer) {
			utils::xml_add_text_node(part, "cost", mCost);
			utils::xml_add_text_node(part, "level", mLevel);
			utils::xml_add_text_node(part, "prefix_asset_id", mPrefixAssetHash);
			utils::xml_add_text_node(part, "prefix_secondary_asset_id", mPrefixSecondaryAssetHash);
			utils::xml_add_text_node(part, "rarity", mRarity);
			utils::xml_add_text_node(part, "reference_id", index);
			utils::xml_add_text_node(part, "rigblock_asset_id", mRigblockAssetHash);
			utils::xml_add_text_node(part, "suffix_asset_id", mSuffixAssetHash);
		} else {
			utils::xml_add_text_node(part, "is_flair", mIsFlair);
			utils::xml_add_text_node(part, "cost", mCost);
			utils::xml_add_text_node(part, "creature_id", mEquippedToCreatureId);
			utils::xml_add_text_node(part, "id", index);
			utils::xml_add_text_node(part, "level", mLevel);
			utils::xml_add_text_node(part, "market_status", mMarketStatus);
			utils::xml_add_text_node(part, "prefix_asset_id", mPrefixAssetHash);
			utils::xml_add_text_node(part, "prefix_secondary_asset_id", mPrefixSecondaryAssetHash);
			utils::xml_add_text_node(part, "rarity", mRarity);
			utils::xml_add_text_node(part, "reference_id", index);
			utils::xml_add_text_node(part, "rigblock_asset_id", mRigblockAssetHash);
			utils::xml_add_text_node(part, "status", mStatus);
			utils::xml_add_text_node(part, "suffix_asset_id", mSuffixAssetHash);
			utils::xml_add_text_node(part, "usage", mUsage);
			utils::xml_add_text_node(part, "creation_date", mTimestamp);
		}
	}

	bool Part::Read(rapidjson::Value& object) {
		if (!object.IsObject()) {
			return false;
		}

		mCost = utils::json::GetUint(object, "cost");
		mLevel = utils::json::GetUint16(object, "level");
		mMarketStatus = utils::json::GetUint8(object, "market_status");
		mRarity = static_cast<SporeNet::PartRarity>(utils::json::GetUint8(object, "rarity"));
		mUsage = utils::json::GetUint8(object, "usage");

		// stats = utils::json::GetString(object, "stats");
		// type_full = utils::json::GetString(object, "type_full");
		// class_types_full = utils::json::GetString(object, "class_types_full");
		// science_types_full = utils::json::GetString(object, "science_types_full");
		// rarity_full = utils::json::GetString(object, "rarity_full");
		// png_key = utils::json::GetString(object, "png_key");
		// weapon_damage_modifier = utils::json::GetString(object, "weapon_damage_modifier");
		// modifiers = utils::json::GetString(object, "modifiers");
		// rand_seed = utils::json::GetString(object, "rand_seed");
		
		SetRigblock(utils::json::GetUint16(object, "rigblock_asset_id"));
		SetPrefix(utils::json::GetUint16(object, "prefix_asset_id"), false);
		SetPrefix(utils::json::GetUint16(object, "prefix_secondary_asset_id"), true);
		SetSuffix(utils::json::GetUint16(object, "suffix_asset_id"));
		return true;
	}

	rapidjson::Value Part::Write(rapidjson::Document::AllocatorType& allocator, uint32_t index, bool api) const {
		rapidjson::Value object = utils::json::NewObject();
		utils::json::Set(object, "cost", mCost, allocator);
		utils::json::Set(object, "level", mLevel, allocator);
		utils::json::Set(object, "market_status", mMarketStatus, allocator);
		utils::json::Set(object, "rarity", static_cast<uint8_t>(mRarity), allocator);
		utils::json::Set(object, "usage", mUsage, allocator);

		if (api) {
			utils::json::Set(object, "id", index, allocator);
			utils::json::Set(object, "reference_id", index, allocator);

			utils::json::Set(object, "rigblock_asset_id", mRigblockAssetHash, allocator);
			utils::json::Set(object, "prefix_asset_id", mPrefixAssetHash, allocator);
			utils::json::Set(object, "prefix_secondary_asset_id", mPrefixSecondaryAssetHash, allocator);
			utils::json::Set(object, "suffix_asset_id", mSuffixAssetHash, allocator);
		}
		else {
			utils::json::Set(object, "rigblock_asset_id", mRigblockAssetId, allocator);
			utils::json::Set(object, "prefix_asset_id", mPrefixAssetId, allocator);
			utils::json::Set(object, "prefix_secondary_asset_id", mPrefixSecondaryAssetId, allocator);
			utils::json::Set(object, "suffix_asset_id", mSuffixAssetId, allocator);
		}

		// utils::json::Set(object, "stats", stats, allocator);
		// utils::json::Set(object, "type_full", type_full, allocator);
		// utils::json::Set(object, "class_types_full", class_types_full, allocator);
		// utils::json::Set(object, "science_types_full", science_types_full, allocator);
		// utils::json::Set(object, "rarity_full", rarity_full, allocator);
		// utils::json::Set(object, "png_key", png_key, allocator);
		// utils::json::Set(object, "weapon_damage_modifier", weapon_damage_modifier, allocator);
		// utils::json::Set(object, "modifiers", modifiers, allocator);
		// utils::json::Set(object, "rand_seed", rand_seed, allocator);

		return object;
	}

	uint64_t Part::GetTimestamp() const {
		return mTimestamp;
	}

	uint32_t Part::GetRigblockAssetHash() const {
		return mRigblockAssetHash;
	}

	uint32_t Part::GetPrefixAssetHash() const {
		return mPrefixAssetHash;
	}

	uint32_t Part::GetPrefixSecondaryAssetHash() const {
		return mPrefixSecondaryAssetHash;
	}

	uint32_t Part::GetSuffixAssetHash() const {
		return mSuffixAssetHash;
	}

	uint16_t Part::GetLevel() const {
		return mLevel;
	}

	PartRarity Part::GetRarity() const {
		return mRarity;
	}

	void Part::SetRigblock(uint16_t rigblock) {
		if (!(rigblock >= 1 && rigblock <= 1573) && !(rigblock >= 10001 && rigblock <= 10835)) {
			rigblock = 1;
		}

		const std::string& rigblock_string = "_Generated/LootRigblock" + std::to_string(rigblock) + ".LootRigblock";
		mRigblockAssetId = rigblock;
		mRigblockAssetHash = utils::hash_id(rigblock_string);
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
			mPrefixSecondaryAssetId = prefix;
			mPrefixSecondaryAssetHash = utils::hash_id(prefix_string);
		} else {
			mPrefixAssetId = prefix;
			mPrefixAssetHash = utils::hash_id(prefix_string);
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

		mSuffixAssetId = suffix;
		mSuffixAssetHash = utils::hash_id(suffix_string);
	}

	void Part::SetCreationDate(uint64_t timestamp) {
		mTimestamp = timestamp;
	}

	void Part::SetCost(uint32_t cost) {
		mCost = cost;
	}

	void Part::SetLevel(uint16_t level) {
		mLevel = level;
	}

	void Part::SetRarity(PartRarity rarity) {
		mRarity = rarity;
	}

	void Part::SetMarketStatus(uint8_t marketStatus) {
		mMarketStatus = marketStatus;
	}

	void Part::SetStatus(uint8_t status) {
		mStatus = status;
	}

	void Part::SetUsage(uint8_t usage) {
		mUsage = usage;
	}

	void Part::SetIsFlair(bool flair) {
		mIsFlair = flair;
	}

	// Parts
	Part& Parts::GetPart(size_t index) {
		return mItems[index];
	}

	const Part& Parts::GetPart(size_t index) const {
		return mItems[index];
	}

	void Parts::Read(const pugi::xml_node& node) {
		for (const auto& part : node.child("parts")) {
			mItems.emplace_back(part);
		}
	}

	void Parts::Write(pugi::xml_node& node) const {
		if (auto parts = node.append_child("parts")) {
			for (const auto& part : mItems) {
				part.Write(parts);
			}
		}
	}

	void Parts::WriteApi(pugi::xml_node& node, bool offer) const {
		if (auto parts = node.append_child("parts")) {
			uint32_t index = 0;
			for (const auto& part : mItems) {
				part.WriteApi(parts, ++index, offer);
			}
		}
	}
}
