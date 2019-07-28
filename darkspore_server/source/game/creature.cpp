
// Include
#include "creature.h"
#include "../utils/functions.h"
#include <algorithm>

// Game
namespace Game {
	// Creature
	void Creature::Read(const pugi::xml_node& node) {
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

	void Creature::Write(pugi::xml_node& node) const {
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

	rapidjson::Value Creature::Write(rapidjson::Document::AllocatorType& allocator) const { 
		rapidjson::Value object(rapidjson::kObjectType);
		utils::json_add_text_to_object(object, "name",           name,         allocator);
		utils::json_add_text_to_object(object, "name_locale_id", nameLocaleId, allocator);
		utils::json_add_text_to_object(object, "type_a",         elementType,  allocator);
		utils::json_add_text_to_object(object, "class",          classType,    allocator);
		utils::json_add_text_to_object(object, "png_large_url",  pngLargeUrl,  allocator);
		utils::json_add_text_to_object(object, "png_thumb_url",  pngThumbUrl,  allocator);
		object.AddMember("gear_score",     rapidjson::Value{}.SetDouble(gearScore),  allocator);
		object.AddMember("item_points",    rapidjson::Value{}.SetDouble(itemPoints), allocator);
		object.AddMember("noun_id",        rapidjson::Value{}.SetUint64(nounId),     allocator);
		object.AddMember("id",             rapidjson::Value{}.SetUint(id),           allocator);
		object.AddMember("version",        rapidjson::Value{}.SetUint(version),      allocator);
		return object;
	}

	// Creatures
	void Creatures::Read(const pugi::xml_node& node) {
		auto creatures = node.child("creatures");
		if (!creatures) {
			return;
		}

		for (const auto& creatureNode : creatures) {
			decltype(auto) creature = mCreatures.emplace_back();
			creature.Read(creatureNode);
		}
	}

	void Creatures::Write(pugi::xml_node& node) const {
		if (auto creatures = node.append_child("creatures")) {
			for (const auto& creature : mCreatures) {
				creature.Write(creatures);
			}
		}
	}

	rapidjson::Value Creatures::Write(rapidjson::Document::AllocatorType& allocator) const { 
		rapidjson::Value value(rapidjson::kArrayType);
		for (const auto& creature : mCreatures) {
			value.PushBack(creature.Write(allocator), allocator);
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