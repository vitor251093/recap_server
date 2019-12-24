
// Include
#include "template.h"
#include <algorithm>

// Game
namespace Game {
	// Template
	void CreatureTemplate::ReadXml(const pugi::xml_node& node) {
		id = utils::xml::GetString<uint64_t>(node, "id");

		nameLocaleId = utils::xml::GetString(node, "name_locale_id");
		descLocaleId = utils::xml::GetString(node, "text_locale_id");
		name         = utils::xml::GetString(node, "name");
		elementType  = utils::xml::GetString(node, "type_a");
		
		weaponMinDamage = utils::xml::GetString<double>(node, "weapon_min_damage");
		weaponMaxDamage = utils::xml::GetString<double>(node, "weapon_max_damage");
		gearScore       = utils::xml::GetString<double>(node, "gear_score");

		classType = utils::xml::GetString(node, "class");

		//stats_template
		//stats_template_ability
		//stats_template_ability_keyvalues
		//creature_parts

		//ability_passive
		//ability_basic
		//ability_random
		//ability_special_1
		//ability_special_2
		//ability[]
		//   id
	}

	void CreatureTemplate::WriteXml(pugi::xml_node& node) const {
		if (auto creature = node.append_child("template")) {
			utils::xml::Set(creature, "id", id);

			utils::xml::Set(creature, "name_locale_id", nameLocaleId);
			utils::xml::Set(creature, "text_locale_id", descLocaleId);
			utils::xml::Set(creature, "name", name);
			utils::xml::Set(creature, "type_a", elementType);

			utils::xml::Set(creature, "weapon_min_damage", weaponMinDamage);
			utils::xml::Set(creature, "weapon_max_damage", weaponMaxDamage);
			utils::xml::Set(creature, "gear_score", gearScore);

			utils::xml::Set(creature, "class", classType);

			//utils::xml::Set(creature, "stats_template", );
			//utils::xml::Set(creature, "stats_template_ability", );
			//utils::xml::Set(creature, "stats_template_ability_keyvalues", );
			//utils::xml::Set(creature, "creature_parts", );

			//utils::xml::Set(creature, "ability_passive", );
			//utils::xml::Set(creature, "ability_basic", );
			//utils::xml::Set(creature, "ability_random", );
			//utils::xml::Set(creature, "ability_special_1", );
			//utils::xml::Set(creature, "ability_special_2", );
			//utils::xml::Set(creature, "ability", );
		}
	}

	void CreatureTemplate::ReadJson(rapidjson::Value& object) {
		if (!object.IsObject()) return;
		id = utils::json::GetUint64(object, "id");

		nameLocaleId = utils::json::GetString(object, "name_locale_id");
		descLocaleId = utils::json::GetString(object, "text_locale_id");
		name         = utils::json::GetString(object, "name");
		elementType  = utils::json::GetString(object, "type_a");

		weaponMinDamage = utils::json::GetDouble(object, "weapon_min_damage");
		weaponMaxDamage = utils::json::GetDouble(object, "weapon_max_damage");
		gearScore       = utils::json::GetDouble(object, "gear_score");

		classType = utils::json::GetString(object, "class");

		//utils = utils::json::GetString(object, "stats_template");
		//utils = utils::json::GetString(object, "stats_template_ability");
		//utils = utils::json::GetString(object, "stats_template_ability_keyvalues");
		//utils = utils::json::GetString(object, "creature_parts");

		//utils = utils::json::GetString(object, "ability_passive");
		//utils = utils::json::GetString(object, "ability_basic");
		//utils = utils::json::GetString(object, "ability_random");
		//utils = utils::json::GetString(object, "ability_special_1");
		//utils = utils::json::GetString(object, "ability_special_2");
		//utils = utils::json::GetString(object, "ability");
	}

	rapidjson::Value CreatureTemplate::WriteJson(rapidjson::Document::AllocatorType& allocator) const {
		rapidjson::Value object = utils::json::NewObject();
		utils::json::Set(object, "id", id, allocator);
		
		utils::json::Set(object, "name_locale_id", nameLocaleId, allocator);
		utils::json::Set(object, "text_locale_id", descLocaleId, allocator);
		utils::json::Set(object, "name", name, allocator);
		utils::json::Set(object, "type_a", elementType, allocator);
		
		utils::json::Set(object, "weapon_min_damage", weaponMinDamage, allocator);
		utils::json::Set(object, "weapon_max_damage", weaponMaxDamage, allocator);
		utils::json::Set(object, "gear_score", gearScore, allocator);

		utils::json::Set(object, "class", classType, allocator);

		//utils::json::Set(object, "stats_template", , allocator);
		//utils::json::Set(object, "stats_template_ability", , allocator);
		//utils::json::Set(object, "stats_template_ability_keyvalues", , allocator);
		//utils::json::Set(object, "creature_parts", , allocator);

		//utils::json::Set(object, "ability_passive", , allocator);
		//utils::json::Set(object, "ability_basic", , allocator);
		//utils::json::Set(object, "ability_random", , allocator);
		//utils::json::Set(object, "ability_special_1", , allocator);
		//utils::json::Set(object, "ability_special_2", , allocator);
		//utils::json::Set(object, "ability", , allocator);

		return object;
	}
}
