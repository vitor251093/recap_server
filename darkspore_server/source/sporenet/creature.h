
#ifndef _SPORENET_CREATURE_HEADER
#define _SPORENET_CREATURE_HEADER

// Include
#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <memory>
#include <pugixml.hpp>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/filereadstream.h>

// SporeNet
namespace SporeNet {
	// Creature template IDs
	enum class CreatureID : uint64_t {
		BlitzAlpha = 1667741389,
		SageAlpha = 749013658,
		WraithAlpha = 3591937345,
		GoliathAlpha = 3376462303,
		ZrinAlpha = 576185321,
		AraknaAlpha = 2128242117,
		VexAlpha = 3618328019,
		ViperAlpha = 1237326306,
		LuminAlpha = 963807461,
		JinxAlpha = 3914325063,
		Srs42Alpha = 3524487169,
		MagnosAlpha = 2954534111,
		ArborusAlpha = 1770764384,
		TitanAlpha = 3068979135,
		MaldriAlpha = 3911756266,
		RevenantAlpha = 38011465583,
		KrelAlpha = 1392397193,
		AndromedaAlpha = 3877795735,
		MeditronAlpha = 1557965449,
		SavageAlpha = 3660811270,
		BlitzBeta = 454054015,
		SageBeta = 1986637994,
		WraithBeta = 4201941707,
		ZrinBeta = 2530835539,
		GoliathBeta = 3948469269,
		ViperBeta = 3600769362,
		SeraphXSDelta = 4234304479,
		SeraphXSGamma = 2464059380,
		SeraphXSAlpha = 820281267,
		SeraphXSBeta = 2726720353,
		VexBeta = 3918493889,
		LuminBeta = 1475341687,
		AraknaBeta = 818452503,
		SRS42Beta = 2445894411,
		MagnosBeta = 3639041301,
		JinxBeta = 1442915581,
		TorkAlpha = 1957997466,
	};

	enum class CreatureType : uint16_t {
		Bio,
		Cyber,
		Plasma,
		Necro,
		Chrono,
		All,
		Unknown
	};

	enum class CreatureClass : uint16_t {
		Ravager,
		Sentinel,
		Tempest,
		All,
		Unknown
	};

	enum class CreatureParts : uint16_t {
		All,
		NoHands,
		NoFeet,
		Unknown
	};

	void from_string(const std::string& src, CreatureType& dst);
	std::string to_string(CreatureType value);

	void from_string(const std::string& src, CreatureClass& dst);
	std::string to_string(CreatureClass value);

	void from_string(const std::string& src, CreatureParts& dst);
	std::string to_string(CreatureParts value);

	/*
		name_locale_id
		text_locale_id

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

		ability_passive
		ability_basic
		ability_random
		ability_special_1
		ability_special_2
		ability
			id

	*/

	struct Stats {
		std::string statName;
		uint32_t maxValue;
		uint32_t currentValue;

		// STR, 14, 0; DEX, 13, 0; MIND, 23, 0; HLTH, 100, 70; MANA, 125, 23; PDEF, 50, 78; EDEF, 150, 138; CRTR, 50, 52
	};

	struct AbilityStat {
		std::string key;
		std::string token;
		std::string value;
	};

	// TemplateCreature
	class TemplateCreature {
		public:
			void Read(const pugi::xml_node& node);
			void WriteApi(pugi::xml_node& node, bool include_abilities) const;

			void ReadJson(rapidjson::Value& object);
			rapidjson::Value WriteJson(rapidjson::Document::AllocatorType& allocator) const;

			const std::string& GetName() const;

			uint32_t GetNoun() const;
			uint32_t GetAbility(uint8_t index) const;

			CreatureType GetType() const;
			CreatureClass GetClass() const;
			CreatureParts GetEquipableParts() const;

		private:
			std::vector<AbilityStat> mAbilityStats;
			std::vector<Stats> mStats;

			std::array<uint32_t, 5> mAbility;

			std::string mNameLocaleId;
			std::string mTextLocaleId;
			std::string mName;

			double mBaseWeaponDamageMin = 1.f;
			double mBaseWeaponDamageMax = 1.f;
			float mGearScore = 0.f;

			uint32_t mNoun;

			CreatureType mType = CreatureType::All;
			CreatureClass mClass = CreatureClass::All;
			CreatureParts mEquipableParts = CreatureParts::All;
	};

	using TemplateCreaturePtr = std::shared_ptr<TemplateCreature>;

	// TemplateDatabase
	class TemplateDatabase {
		public:
			void Load();

			TemplateCreaturePtr Get(const std::string& name) const;
			TemplateCreaturePtr Get(uint32_t noun) const;

		private:
			std::unordered_map<std::string, TemplateCreaturePtr> mTemplateCreatures;
	};

	// Creature
	class Creature {
		public:
			Creature() = default;
			Creature(const TemplateCreaturePtr& templateCreature);

			void Read(const pugi::xml_node& node);
			void Write(pugi::xml_node& node) const;
			void WriteApi(pugi::xml_node& node, bool profile_data, bool include_abilities, bool include_parts) const;

			void Update(float gearScore, float itemPoints, const std::string& parts, const std::string& stats, const std::string& abilityStats);

			std::string GetName() const;

			uint32_t GetNoun() const;
			uint32_t GetAbility(uint8_t index) const;

			CreatureType GetType() const;
			CreatureClass GetClass() const;
			CreatureParts GetEquipableParts() const;

			const std::string& GetLargeImageURL() const;
			const std::string& GetThumbImageURL() const;

			float GetGearScore() const;
			float GetGearScoreFlattened() const;
			float GetItemPoints() const;

			int64_t GetCreatorId() const;

			uint32_t GetId() const;
			void SetId(uint32_t id);

			uint32_t GetVersion() const;
			void SetVersion(uint32_t version);

		private:
			// Parts mEquippedParts;

			std::vector<AbilityStat> mAbilityStats;
			std::vector<Stats> mStats;

			TemplateCreaturePtr mTemplate;

			std::string mPngLargeUrl;
			std::string mPngThumbUrl;

			int64_t mCreatorId = 0;

			float mGearScore = 0;
			float mItemPoints = 300;

			uint32_t mId = 0;
			uint32_t mVersion = 0;
	};

	using CreaturePtr = std::shared_ptr<Creature>;

	// Creatures
	class Creatures {
		public:
			decltype(auto) begin() { return mCreatures.begin(); }
			decltype(auto) begin() const { return mCreatures.begin(); }
			decltype(auto) end() { return mCreatures.end(); }
			decltype(auto) end() const { return mCreatures.end(); }

			auto& data() { return mCreatures; }
			const auto& data() const { return mCreatures; }

			void Read(const pugi::xml_node& node);
			void Write(pugi::xml_node& node) const;
			void WriteApi(pugi::xml_node& node) const;

			uint32_t Add(uint32_t templateId);

			CreaturePtr Get(size_t creatureId) const;

		private:
			std::vector<CreaturePtr> mCreatures;
	};
}

#endif
