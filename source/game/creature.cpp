
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

	void Creature::ReadJson(utils::jsonObject& object) {
		name         = object.GetString("name");
		nameLocaleId = object.GetString("name_locale_id");
		elementType  = object.GetString("type_a");
		classType    = object.GetString("class");
		pngLargeUrl  = object.GetString("png_large_url");
		pngThumbUrl  = object.GetString("png_thumb_url");

		gearScore    = object.GetDouble("gear_score");
		itemPoints   = object.GetDouble("item_points");

		id      = object.GetUint("id");
		nounId  = object.GetUint64("noun_id");
		version = object.GetUint("version");
	}

	void Creature::WriteJson(utils::jsonObject& object) const { 
		object.Set("name",           name        );
		object.Set("name_locale_id", nameLocaleId);
		object.Set("type_a",         elementType );
		object.Set("class",          classType   );
		object.Set("png_large_url",  pngLargeUrl );
		object.Set("png_thumb_url",  pngThumbUrl );
		object.Set("gear_score",     gearScore   );
		object.Set("item_points",    itemPoints  );
		object.Set("noun_id",        nounId      );
		object.Set("id",             id          );
		object.Set("version",        version     );
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

	void Creatures::ReadJson(utils::jsonArray& object) {
		mCreatures.clear();
		for (auto& creatureNode : object) {
			decltype(auto) creature = mCreatures.emplace_back();
			creature.ReadJson(creatureNode.GetObject());
		}
	}

	void Creatures::WriteJson(utils::jsonArray& object) const { 
		for (const auto& creature : mCreatures) {
			creature.WriteJson(object.NewObject());
		}
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
