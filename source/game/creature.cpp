
// Include
#include "creature.h"
#include <algorithm>

// Game
namespace Game {
	// Creature
	void Creature::ReadXml(const pugi::xml_node& node) {
		std::string_view nodeName = node.name();
		if (nodeName != "creature") {
			return;
		}

		name = utils::xml_get_text_node(node, "name");
		nameLocaleId = utils::xml_get_text_node(node, "name_locale_id");
		elementType = utils::xml_get_text_node(node, "type_a");
		classType = utils::xml_get_text_node(node, "class");
		pngLargeUrl = utils::xml_get_text_node(node, "png_large_url");
		pngThumbUrl = utils::xml_get_text_node(node, "png_thumb_url");

		gearScore = utils::xml_get_text_node<double>(node, "gear_score");
		itemPoints = utils::xml_get_text_node<double>(node, "item_points");

		id = utils::xml_get_text_node<uint32_t>(node, "id");
		nounId = utils::xml_get_text_node<uint64_t>(node, "noun_id");
		version = utils::xml_get_text_node<uint32_t>(node, "version");
	}

	void Creature::WriteXml(pugi::xml_node& node) const {
		if (auto creature = node.append_child("creature")) {
			utils::xml_add_text_node(creature, "id", id);
			utils::xml_add_text_node(creature, "name", name);
			utils::xml_add_text_node(creature, "name_locale_id", nameLocaleId);
			utils::xml_add_text_node(creature, "type_a", elementType);
			utils::xml_add_text_node(creature, "class", classType);
			utils::xml_add_text_node(creature, "png_large_url", pngLargeUrl);
			utils::xml_add_text_node(creature, "png_thumb_url", pngThumbUrl);
			utils::xml_add_text_node(creature, "noun_id", nounId);
			utils::xml_add_text_node(creature, "version", version);
			utils::xml_add_text_node(creature, "gear_score", gearScore);
			utils::xml_add_text_node(creature, "item_points", itemPoints);
		}
	}

	void Creature::ReadJson(rapidjson::Value& object) {
		name         = utils::json::GetString(object, "name");
		nameLocaleId = utils::json::GetString(object, "name_locale_id");
		elementType  = utils::json::GetString(object, "type_a");
		classType    = utils::json::GetString(object, "class");
		pngLargeUrl  = utils::json::GetString(object, "png_large_url");
		pngThumbUrl  = utils::json::GetString(object, "png_thumb_url");

		gearScore    = utils::json::GetDouble(object, "gear_score");
		itemPoints   = utils::json::GetDouble(object, "item_points");

		id      = utils::json::GetUint(object, "id");
		nounId  = utils::json::GetUint64(object, "noun_id");
		version = utils::json::GetUint(object, "version");
	}

	rapidjson::Value Creature::WriteJson(rapidjson::Document::AllocatorType& allocator) const { 
		rapidjson::Value object = utils::json::NewObject();
		utils::json::Set(object, "name",           name,         allocator);
		utils::json::Set(object, "name_locale_id", nameLocaleId, allocator);
		utils::json::Set(object, "type_a",         elementType,  allocator);
		utils::json::Set(object, "class",          classType,    allocator);
		utils::json::Set(object, "png_large_url",  pngLargeUrl,  allocator);
		utils::json::Set(object, "png_thumb_url",  pngThumbUrl,  allocator);
		utils::json::Set(object, "gear_score",     gearScore,    allocator);
		utils::json::Set(object, "item_points",    itemPoints,   allocator);
		utils::json::Set(object, "noun_id",        nounId,       allocator);
		utils::json::Set(object, "id",             id,           allocator);
		utils::json::Set(object, "version",        version,      allocator);
		return object;
	}



	// Creatures
	void Creatures::ReadXml(const pugi::xml_node& node) {
		auto creatures = node.child("creatures");
		if (!creatures) {
			return;
		}

		for (const auto& creatureNode : creatures) {
			decltype(auto) creature = mCreatures.emplace_back();
			creature.ReadXml(creatureNode);
		}
	}

	void Creatures::WriteXml(pugi::xml_node& node) const {
		if (auto creatures = node.append_child("creatures")) {
			for (const auto& creature : mCreatures) {
				creature.WriteXml(creatures);
			}
		}
	}

	void Creatures::ReadJson(rapidjson::Value& object) {
		mCreatures.clear();
		for (auto& creatureNode : object.GetArray()) {
			decltype(auto) creature = mCreatures.emplace_back();
			creature.ReadJson(creatureNode);
		}
	}

	rapidjson::Value Creatures::WriteJson(rapidjson::Document::AllocatorType& allocator) const { 
		rapidjson::Value value = utils::json::NewArray();
		for (const auto& creature : mCreatures) {
			rapidjson::Value creatureNode = creature.WriteJson(allocator);
			utils::json::Add(value, creatureNode, allocator);
		}
		return value;
	}

	void Creatures::Add(uint32_t templateId) {
		for (const auto& creature : mCreatures) {
			if (creature.nounId == templateId) {
				return;
			}
		}

		decltype(auto) creature = mCreatures.emplace_back();
		creature.id = 1;
		creature.nounId = templateId;
	}
}
