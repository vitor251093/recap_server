
// Include
#include "creature.h"
#include "instance.h"

#include "game/config.h"
#include "utils/functions.h"
#include "utils/json.h"

#include <algorithm>
#include <filesystem>
#include <iostream>

// SporeNet
namespace SporeNet {
	// CreatureType
	void from_string(const std::string& src, CreatureType& dst) {
		using namespace std::literals;

		std::string_view srcView = src;
		if (utils::string_iequals(srcView, "bio"sv)) {
			dst = CreatureType::Bio;
		} else if (utils::string_iequals(srcView, "cyber"sv)) {
			dst = CreatureType::Cyber;
		} else if (utils::string_iequals(srcView, "plasma"sv)) {
			dst = CreatureType::Plasma;
		} else if (utils::string_iequals(srcView, "necro"sv)) {
			dst = CreatureType::Necro;
		} else if (utils::string_iequals(srcView, "chrono"sv)) {
			dst = CreatureType::Chrono;
		} else if (utils::string_iequals(srcView, "all"sv)) {
			dst = CreatureType::All;
		} else {
			dst = CreatureType::Unknown;
		}
	}

	std::string to_string(CreatureType value) {
		switch (value) {
			case CreatureType::Bio:
				return "bio";

			case CreatureType::Cyber:
				return "cyber";

			case CreatureType::Plasma:
				return "plasma";

			case CreatureType::Necro:
				return "necro";

			case CreatureType::Chrono:
				return "chrono";

			case CreatureType::All:
				return "all";

			default:
				return "unknown";
		}
	}

	// CreatureClass
	void from_string(const std::string& src, CreatureClass& dst) {
		using namespace std::literals;

		std::string_view srcView = src;
		if (utils::string_iequals(srcView, "ravager"sv)) {
			dst = CreatureClass::Ravager;
		} else if (utils::string_iequals(srcView, "sentinel"sv)) {
			dst = CreatureClass::Sentinel;
		} else if (utils::string_iequals(srcView, "tempest"sv)) {
			dst = CreatureClass::Tempest;
		} else if (utils::string_iequals(srcView, "all"sv)) {
			dst = CreatureClass::All;
		} else {
			dst = CreatureClass::Unknown;
		}
	}

	std::string to_string(CreatureClass value) {
		switch (value) {
			case CreatureClass::Ravager:
				return "ravager";

			case CreatureClass::Sentinel:
				return "sentinel";

			case CreatureClass::Tempest:
				return "tempest";

			case CreatureClass::All:
				return "all";

			default:
				return "unknown";
		}
	}

	// CreatureParts
	void from_string(const std::string& src, CreatureParts& dst) {
		using namespace std::literals;

		std::string_view srcView = src;
		if (utils::string_iequals(srcView, "no_feet"sv)) {
			dst = CreatureParts::NoFeet;
		} else if (utils::string_iequals(srcView, "no_hands"sv)) {
			dst = CreatureParts::NoHands;
		} else if (utils::string_iequals(srcView, "all"sv)) {
			dst = CreatureParts::All;
		} else {
			dst = CreatureParts::Unknown;
		}
	}

	std::string to_string(CreatureParts value) {
		switch (value) {
			case CreatureParts::NoFeet:
				return "no_feet";

			case CreatureParts::NoHands:
				return "no_hands";

			case CreatureParts::All:
				return "all";

			default:
				return "unknown";
		}
	}

	/*
		name_locale_id
		text_locale_id

		if not template {
			creator_id
		}

		stats_template_ability
			example {
				full_string = item0;item1;itemN
				item = a!b,value
			}

		if not template {
			stats
			stats_template_ability_keyvalues
			stats_ability_keyvalues
		} else {
			stats_template
			stats_template_ability_keyvalues
		}

		if not template {
			parts
				part
		}

		if not template {
			png_large_url
			png_thumb_url
		}
	*/

	// TemplateCreature
	void TemplateCreature::Read(const pugi::xml_node& node) {
		mNoun = utils::hash_id(node.attribute("noun").as_string());

		mNameLocaleId = utils::xml_get_text_node(node, "name_locale_id");
		mTextLocaleId = utils::xml_get_text_node(node, "text_locale_id");

		mName = utils::xml_get_text_node(node, "name");
		from_string(utils::xml_get_text_node(node, "type_a"), mType);
		mBaseWeaponDamageMin = utils::xml_get_text_node<double>(node, "weapon_min_damage");
		mBaseWeaponDamageMax = utils::xml_get_text_node<double>(node, "weapon_max_damage");
		mGearScore = utils::xml_get_text_node<float>(node, "gear_score");
		from_string(utils::xml_get_text_node(node, "class"), mClass);
		from_string(utils::xml_get_text_node(node, "creature_parts"), mEquipableParts);

		mAbility[0] = utils::hash_id(utils::xml_get_text_node(node, "ability_basic"));
		mAbility[1] = utils::hash_id(utils::xml_get_text_node(node, "ability_special_1"));
		mAbility[2] = utils::hash_id(utils::xml_get_text_node(node, "ability_special_2"));
		mAbility[3] = utils::hash_id(utils::xml_get_text_node(node, "ability_random"));
		mAbility[4] = utils::hash_id(utils::xml_get_text_node(node, "ability_passive"));

		// parse stats
		const auto& statsString = utils::xml_get_text_node(node, "stats_template");

		mStats.clear();
		for (const auto& statString : utils::explode_string(statsString, ';')) {
			if (statString.empty()) {
				continue;
			}

			const auto& statData = utils::explode_string(statString, ',');

			decltype(auto) stat = mStats.emplace_back();
			stat.statName = statData[0];
			stat.maxValue = utils::to_number<uint32_t>(statData[1]);
			stat.currentValue = utils::to_number<uint32_t>(statData[2]);
		}
	}

	void TemplateCreature::WriteApi(pugi::xml_node& node, bool include_abilities) const {
		utils::xml_add_text_node(node, "name_locale_id", mNameLocaleId);
		utils::xml_add_text_node(node, "text_locale_id", mTextLocaleId);

		utils::xml_add_text_node(node, "name", mName);
		utils::xml_add_text_node(node, "type_a", to_string(mType));
		utils::xml_add_text_node(node, "weapon_min_damage", mBaseWeaponDamageMin);
		utils::xml_add_text_node(node, "weapon_max_damage", mBaseWeaponDamageMax);
		utils::xml_add_text_node(node, "gear_score", mGearScore);
		utils::xml_add_text_node(node, "class", to_string(mClass));
		utils::xml_add_text_node(node, "creature_parts", to_string(mEquipableParts));

		{
			std::string statsString;
			for (const auto& stat : mStats) {
				statsString += stat.statName + ',' + std::to_string(stat.maxValue) + ',' + std::to_string(stat.currentValue) + ';';
			}
			utils::xml_add_text_node(node, "stats_template", statsString);
		}
		// stats_template
		// stats_template_ability_keyvalues

		if (include_abilities) {
			utils::xml_add_text_node(node, "ability_basic", mAbility[0]);
			utils::xml_add_text_node(node, "ability_special_1", mAbility[1]);
			utils::xml_add_text_node(node, "ability_special_2", mAbility[2]);
			utils::xml_add_text_node(node, "ability_random", mAbility[3]);
			utils::xml_add_text_node(node, "ability_passive", mAbility[4]);

			if (auto abilityNode = node.append_child("ability")) {
				for (const auto value : mAbility) {
					utils::xml_add_text_node(abilityNode, "id", value);
				}
			}
		}
	}

	void TemplateCreature::ReadJson(rapidjson::Value& object) {
		if (!object.IsObject()) return;
		mNoun = utils::json::GetUint(object, "id");

		mNameLocaleId = utils::json::GetString(object, "nameLocaleId");
		mTextLocaleId = utils::json::GetString(object, "descLocaleId");

		mName = utils::json::GetString(object, "name");
		from_string(utils::json::GetString(object, "elementType"), mType);

		mBaseWeaponDamageMin = utils::json::GetDouble(object, "weaponMinDamage");
		mBaseWeaponDamageMax = utils::json::GetDouble(object, "weaponMaxDamage");
		mGearScore = utils::json::GetDouble(object, "gearScore");

		from_string(utils::json::GetString(object, "classType"), mClass);
		from_string(utils::json::GetString(object, "classType"), mEquipableParts); // TODO: Should be a separate property?

		//statsTemplateAbility = utils::json::GetString(object, "statsTemplateAbility");
		//statsTemplateAbilityKeyvalues = utils::json::GetString(object, "statsTemplateAbilityKeyvalues");

		// hasFeet  = utils::json::GetBool(object, "hasFeet");
		// hasHands = utils::json::GetBool(object, "hasHands");

		mAbility[0] = utils::json::GetUint64(object, "abilityBasic");
		mAbility[1] = utils::json::GetUint64(object, "abilitySpecial1");
		mAbility[2] = utils::json::GetUint64(object, "abilitySpecial2");
		mAbility[3] = utils::json::GetUint64(object, "abilityRandom");
		mAbility[4] = utils::json::GetUint64(object, "abilityPassive");

		// parse stats
		const auto& statsString = utils::json::GetString(object, "statsTemplate");

		mStats.clear();
		for (const auto& statString : utils::explode_string(statsString, ';')) {
			if (statString.empty()) {
				continue;
			}

			const auto& statData = utils::explode_string(statString, ',');

			decltype(auto) stat = mStats.emplace_back();
			stat.statName = statData[0];
			stat.maxValue = utils::to_number<uint32_t>(statData[1]);
			stat.currentValue = utils::to_number<uint32_t>(statData[2]);
		}
	}

	rapidjson::Value TemplateCreature::WriteJson(rapidjson::Document::AllocatorType& allocator) const {
		rapidjson::Value object = utils::json::NewObject();
		utils::json::Set(object, "id", mNoun, allocator);
		
		utils::json::Set(object, "nameLocaleId", mNameLocaleId, allocator);
		utils::json::Set(object, "descLocaleId", mTextLocaleId, allocator);

		utils::json::Set(object, "name", mName, allocator);
		utils::json::Set(object, "elementType", to_string(mType), allocator);
		
		utils::json::Set(object, "weaponMinDamage", mBaseWeaponDamageMin, allocator);
		utils::json::Set(object, "weaponMaxDamage", mBaseWeaponDamageMax, allocator);
		utils::json::Set(object, "gearScore", mGearScore, allocator);

		utils::json::Set(object, "classType", to_string(mClass), allocator);
		// utils::json::Set(object, "classType", to_string(mEquipableParts), allocator); // TODO: Should be a separate property?

		{
			std::string statsString;
			for (const auto& stat : mStats) {
				statsString += stat.statName + ',' + std::to_string(stat.maxValue) + ',' + std::to_string(stat.currentValue) + ';';
			}
			utils::json::Set(object, "statsTemplate", statsString, allocator);
		}
		
		//utils::json::Set(object, "statsTemplateAbility", statsTemplateAbility, allocator);
		//utils::json::Set(object, "statsTemplateAbilityKeyvalues", statsTemplateAbilityKeyvalues, allocator);

		// utils::json::Set(object, "hasFeet",  hasFeet,  allocator);
		// utils::json::Set(object, "hasHands", hasHands, allocator);

		utils::json::Set(object, "abilityBasic",    mAbility[0], allocator);
		utils::json::Set(object, "abilitySpecial1", mAbility[1], allocator);
		utils::json::Set(object, "abilitySpecial2", mAbility[2], allocator);
		utils::json::Set(object, "abilityRandom",   mAbility[3], allocator);
		utils::json::Set(object, "abilityPassive",  mAbility[4], allocator);

		return object;
	}

	const std::string& TemplateCreature::GetName() const {
		return mName;
	}

	uint32_t TemplateCreature::GetNoun() const {
		return mNoun;
	}

	uint32_t TemplateCreature::GetAbility(uint8_t index) const {
		return index < mAbility.size() ? mAbility[index] : 0;
	}

	CreatureType TemplateCreature::GetType() const {
		return mType;
	}

	CreatureClass TemplateCreature::GetClass() const {
		return mClass;
	}

	CreatureParts TemplateCreature::GetEquipableParts() const {
		return mEquipableParts;
	}

	// TemplateDatabase
	void TemplateDatabase::Load() {
		const auto& templateCreaturePath = Game::Config::Get(Game::ConfigValue::CONFIG_TEMPLATE_CREATURE_PATH);
		if (!std::filesystem::exists(templateCreaturePath)) {
			std::cout << "File not found: " << templateCreaturePath << std::endl;
			return;
		}

		auto templatesList = utils::json::FromFile(templateCreaturePath);
		for (auto& templateNode : templatesList.GetArray()) {
			TemplateCreaturePtr templateCreature = std::make_shared<TemplateCreature>();
			templateCreature->ReadJson(templateNode);
			mTemplateCreatures.try_emplace(templateCreature->GetName(), templateCreature);
		}
	}

	TemplateCreaturePtr TemplateDatabase::Get(const std::string& name) const {
		auto it = mTemplateCreatures.find(name);
		return it != mTemplateCreatures.end() ? it->second : nullptr;
	}

	TemplateCreaturePtr TemplateDatabase::Get(uint32_t noun) const {
		for (const auto& [_, templateCreature] : mTemplateCreatures) {
			if (templateCreature->GetNoun() == noun) {
				return templateCreature;
			}
		}
		return nullptr;
	}
	std::vector<TemplateCreaturePtr> TemplateDatabase::List() const {
		std::vector<TemplateCreaturePtr> list;
		for (const auto& [key, value] : mTemplateCreatures) {
			list.push_back(value);
		}
		return list;
	}

	// Creature
	Creature::Creature(const TemplateCreaturePtr& templateCreature)
		: mTemplate(templateCreature) {}

	void Creature::Read(const pugi::xml_node& node) {
		auto templateName = node.attribute("template").as_string();
		mTemplate = SporeNet::Get().GetTemplateDatabase().Get(templateName);

		mId = utils::xml_get_text_node<uint32_t>(node, "id");
		mVersion = utils::xml_get_text_node<uint32_t>(node, "version");

		mGearScore = utils::xml_get_text_node<float>(node, "gear_score"); // Shows up as "level" ingame
		mItemPoints = utils::xml_get_text_node<float>(node, "item_points");

		mPngLargeUrl = utils::xml_get_text_node(node, "png_large_url");
		mPngThumbUrl = utils::xml_get_text_node(node, "png_thumb_url");
	}

	void Creature::Write(pugi::xml_node& node) const {
		node.append_attribute("template").set_value(mTemplate->GetName().c_str());

		utils::xml_add_text_node(node, "id", mId);
		utils::xml_add_text_node(node, "version", mVersion);
		utils::xml_add_text_node(node, "gear_score", mGearScore);
		utils::xml_add_text_node(node, "item_points", mItemPoints);
		utils::xml_add_text_node(node, "png_large_url", mPngLargeUrl);
		utils::xml_add_text_node(node, "png_thumb_url", mPngThumbUrl);
	}

	void Creature::WriteApi(pugi::xml_node& node, bool profile_data, bool include_abilities, bool include_parts) const {
		if (!mTemplate) {
			// Invalid creature object
			return;
		}

		if (profile_data) {
			mTemplate->WriteApi(node, include_abilities);
			node.remove_child("stats_template");

			utils::xml_add_text_node(node, "creator_id", mCreatorId);
			utils::xml_add_text_node(node, "stats", "TODO");

			// stats_ability_keyvalues (uses template by default if this doesnt exist)
		} else {
			utils::xml_add_text_node(node, "id", mId);
			utils::xml_add_text_node(node, "name", mTemplate->GetName());
			utils::xml_add_text_node(node, "png_large_url", mPngLargeUrl);
			utils::xml_add_text_node(node, "png_thumb_url", mPngThumbUrl);
			utils::xml_add_text_node(node, "noun_id", mTemplate->GetNoun());
			utils::xml_add_text_node(node, "version", mVersion);
			utils::xml_add_text_node(node, "gear_score", mGearScore);
			utils::xml_add_text_node(node, "item_points", mItemPoints);
		}

		if (include_parts) {
			if (auto partsNode = node.append_child("parts")) {
				// add parts
			}
		}
	}

	void Creature::Update(float gearScore, float itemPoints, const std::string& parts, const std::string& stats, const std::string& abilityStats) {
		mGearScore = gearScore;
		mItemPoints = itemPoints;

		mStats.clear();
		for (const auto& statString : utils::explode_string(stats, ';')) {
			if (statString.empty()) {
				continue;
			}

			const auto& statData = utils::explode_string(statString, ',');
			if (statData.size() < 3) {
				continue;
			}

			decltype(auto) stat = mStats.emplace_back();
			stat.statName = statData[0];
			stat.maxValue = utils::to_number<uint32_t>(statData[1]);
			stat.currentValue = utils::to_number<uint32_t>(statData[2]);
		}

		mAbilityStats.clear();
		for (const auto& abilityString : utils::explode_string(abilityStats, ';')) {
			if (abilityString.empty()) {
				continue;
			}

			const auto& abilityData = utils::explode_string(abilityString, '!');
			if (abilityData.size() < 2) {
				continue;
			}

			decltype(auto) ability = mAbilityStats.emplace_back();
			ability.token = abilityData[0];
			ability.value = abilityData[1];
		}

		/*
stats_ability_keyvalues = 868969257!minDamage,4;868969257!maxDamage,12;4022963036!percent,50;1137096183!minDamage,24;1137096183!maxDamage,36;1137096183!stunDuration,3;3492557026!minSecondaryDamage,8;3492557026!maxSecondaryDamage,20;3492557026!minDamage,24;3492557026!maxDamage,40;3492557026!radius,4;2779439490!numOrbs,6;2779439490!minDamage,16;2779439490!maxDamage,40;2779439490!deflectionIncrease,100
		*/
	}

	std::string Creature::GetName() const {
		return mTemplate != nullptr ? mTemplate->GetName() : std::string();
	}

	uint32_t Creature::GetNoun() const {
		return mTemplate != nullptr ? mTemplate->GetNoun() : 0;
	}

	uint32_t Creature::GetAbility(uint8_t index) const {
		return mTemplate != nullptr ? mTemplate->GetAbility(index) : 0;
	}

	CreatureType Creature::GetType() const {
		return mTemplate != nullptr ? mTemplate->GetType() : CreatureType::Unknown;
	}

	CreatureClass Creature::GetClass() const {
		return mTemplate != nullptr ? mTemplate->GetClass() : CreatureClass::Unknown;
	}

	CreatureParts Creature::GetEquipableParts() const {
		return mTemplate != nullptr ? mTemplate->GetEquipableParts() : CreatureParts::Unknown;
	}

	const std::string& Creature::GetLargeImageURL() const {
		return mPngLargeUrl;
	}

	const std::string& Creature::GetThumbImageURL() const {
		return mPngThumbUrl;
	}

	float Creature::GetGearScore() const {
		return mGearScore;
	}

	float Creature::GetGearScoreFlattened() const {
		return std::floor(mGearScore);
	}

	float Creature::GetItemPoints() const {
		return mItemPoints;
	}

	int64_t Creature::GetCreatorId() const {
		return mCreatorId;
	}

	uint32_t Creature::GetId() const {
		return mId;
	}

	void Creature::SetId(uint32_t id) {
		mId = id;
	}

	uint32_t Creature::GetVersion() const {
		return mVersion;
	}

	void Creature::SetVersion(uint32_t version) {
		mVersion = version;
	}

	// Creatures
	void Creatures::Read(const pugi::xml_node& node) {
		auto creatures = node.child("creatures");
		if (!creatures) {
			return;
		}

		for (const auto& creatureNode : creatures) {
			std::string_view nodeName = creatureNode.name();
			if (nodeName == "creature") {
				auto creature = std::make_shared<Creature>();
				creature->Read(creatureNode);
				mCreatures.push_back(std::move(creature));
			}
		}
	}

	void Creatures::Write(pugi::xml_node& node) const {
		if (auto creaturesNode = node.append_child("creatures")) {
			for (const auto& creature : mCreatures) {
				if (auto creatureNode = creaturesNode.append_child("creature")) {
					creature->Write(creatureNode);
				}
			}
		}
	}

	void Creatures::WriteApi(pugi::xml_node& node) const {
		if (auto creaturesNode = node.append_child("creatures")) {
			for (const auto& creature : mCreatures) {
				if (auto creatureNode = creaturesNode.append_child("creature")) {
					creature->WriteApi(creatureNode, false, false, false);
				}
			}
		}
	}

	uint32_t Creatures::Add(uint32_t templateId) {
		// TODO: create unique ids for all creatures
		auto templateCreature = SporeNet::Get().GetTemplateDatabase().Get(templateId);
		if (templateCreature) {
			// TODO: global ids (need a database first)
			auto creature = std::make_shared<Creature>(templateCreature);
			creature->SetVersion(1);
			if (mCreatures.empty()) {
				creature->SetId(1);
			} else {
				creature->SetId(mCreatures.back()->GetId() + 1);
			}

			mCreatures.push_back(std::move(creature));
			return mCreatures.back()->GetId();
		}
		return 0;
	}

	CreaturePtr Creatures::Get(size_t creatureId) const {
		for (const auto& creature : mCreatures) {
			if (creature->GetId() == creatureId) {
				return creature;
			}
		}
		return nullptr;
	}
}
