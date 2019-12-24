
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

		statsTemplate = utils::xml::GetString(node, "stats_template");
		//stats_template_ability
		statsTemplateAbilityKeyvalues = utils::xml::GetString(node, "stats_template_ability_keyvalues");

		auto creatureParts = utils::xml::GetString(node, "creature_parts");
		hasHands = (creatureParts == "no_feet"  || creatureParts == "all");
		hasFeet  = (creatureParts == "no_hands" || creatureParts == "all");

		abilityPassive  = utils::xml::GetString<uint64_t>(node, "ability_passive");
		abilityBasic    = utils::xml::GetString<uint64_t>(node, "ability_basic");
		abilityRandom   = utils::xml::GetString<uint64_t>(node, "ability_random");
		abilitySpecial1 = utils::xml::GetString<uint64_t>(node, "ability_special_1");
		abilitySpecial2 = utils::xml::GetString<uint64_t>(node, "ability_special_2");
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

			utils::xml::Set(creature, "stats_template", statsTemplate);

			// TODO: That's not correct, but it works for testing purposes
			utils::xml::Set(creature, "stats_template_ability", statsTemplateAbilityKeyvalues);
			
			utils::xml::Set(creature, "stats_template_ability_keyvalues", statsTemplateAbilityKeyvalues);

			if (hasFeet && !hasHands) {
				utils::xml::Set(creature, "creature_parts", "no_hands");
			}
			else if (!hasFeet && hasHands) {
				utils::xml::Set(creature, "creature_parts", "no_feet");
			}
			else {
				utils::xml::Set(creature, "creature_parts", "all");
			}

			utils::xml::Set(creature, "ability_passive",   abilityPassive);
			utils::xml::Set(creature, "ability_basic",     abilityBasic);
			utils::xml::Set(creature, "ability_random",    abilityRandom);
			utils::xml::Set(creature, "ability_special_1", abilitySpecial1);
			utils::xml::Set(creature, "ability_special_2", abilitySpecial2);
			if (auto abilities = creature.append_child("ability")) {
				// TODO: 
			}
		}
	}

	void CreatureTemplate::ReadJson(rapidjson::Value& object) {
		if (!object.IsObject()) return;
		id = utils::json::GetUint64(object, "id");

		nameLocaleId = utils::json::GetString(object, "nameLocaleId");
		descLocaleId = utils::json::GetString(object, "textLocaleId");
		name         = utils::json::GetString(object, "name");
		elementType  = utils::json::GetString(object, "elementType");

		weaponMinDamage = utils::json::GetDouble(object, "weaponMinDamage");
		weaponMaxDamage = utils::json::GetDouble(object, "weaponMaxDamage");
		gearScore       = utils::json::GetDouble(object, "gearScore");

		classType = utils::json::GetString(object, "classType");

		statsTemplate = utils::json::GetString(object, "statsTemplate");
		//statsTemplateAbility = utils::json::GetString(object, "statsTemplateAbility");
		statsTemplateAbilityKeyvalues = utils::json::GetString(object, "statsTemplateAbilityKeyvalues");

		hasFeet  = utils::json::GetBool(object, "hasFeet");
		hasHands = utils::json::GetBool(object, "hasHands");

		abilityPassive  = utils::json::GetUint64(object, "abilityPassive");
		abilityBasic    = utils::json::GetUint64(object, "abilityBasic");
		abilityRandom   = utils::json::GetUint64(object, "abilityRandom");
		abilitySpecial1 = utils::json::GetUint64(object, "abilitySpecial1");
		abilitySpecial2 = utils::json::GetUint64(object, "abilitySpecial2");
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

		utils::json::Set(object, "stats_template", statsTemplate, allocator);
		//utils::json::Set(object, "stats_template_ability", statsTemplateAbility, allocator);
		utils::json::Set(object, "stats_template_ability_keyvalues", statsTemplateAbilityKeyvalues, allocator);

		utils::json::Set(object, "has_feet",  hasFeet,  allocator);
		utils::json::Set(object, "has_hands", hasHands, allocator);

		utils::json::Set(object, "ability_passive",   abilityPassive,  allocator);
		utils::json::Set(object, "ability_basic",     abilityBasic,    allocator);
		utils::json::Set(object, "ability_random",    abilityRandom,   allocator);
		utils::json::Set(object, "ability_special_1", abilitySpecial1, allocator);
		utils::json::Set(object, "ability_special_2", abilitySpecial2, allocator);

		return object;
	}
}
