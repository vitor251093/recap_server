
#ifndef _GAME_TEMPLATE_HEADER
#define _GAME_TEMPLATE_HEADER

// Include
#include <vector>
#include "../utils/functions.h"

// Game
namespace Game {

	enum class CreatureTemplateID : uint64_t {
		BlitzAlpha     = 1667741389,
		SageAlpha      = 749013658,
		WraithAlpha    = 3591937345,
		GoliathAlpha   = 3376462303,
		ZrinAlpha      = 576185321,
		AraknaAlpha    = 2128242117,
		VexAlpha       = 3618328019,
		ViperAlpha     = 1237326306,
		LuminAlpha     = 963807461,
		JinxAlpha      = 3914325063,
		Srs42Alpha     = 3524487169,
		MagnosAlpha    = 2954534111,
		ArborusAlpha   = 1770764384,
		TitanAlpha     = 3068979135,
		MaldriAlpha    = 3911756266,
		RevenantAlpha  = 38011465583,
		KrelAlpha      = 1392397193,
		AndromedaAlpha = 3877795735,
		MeditronAlpha  = 1557965449,
		SavageAlpha    = 3660811270,
		BlitzBeta      = 454054015,
		SageBeta       = 1986637994,
		WraithBeta     = 4201941707,
		ZrinBeta       = 2530835539,
		GoliathBeta    = 3948469269,
		ViperBeta      = 3600769362,
		SeraphXSDelta  = 4234304479,
		SeraphXSGamma  = 2464059380,
		SeraphXSAlpha  = 820281267,
		SeraphXSBeta   = 2726720353,
		VexBeta        = 3918493889,
		LuminBeta      = 1475341687,
		AraknaBeta     = 818452503,
		SRS42Beta      = 2445894411,
		MagnosBeta     = 3639041301,
		JinxBeta       = 1442915581,
		TorkAlpha      = 1957997466,
	};

	// Creature
	class CreatureTemplate {
		public:
			uint64_t id = 0;
		
			std::string nameLocaleId;
			std::string descLocaleId;
			std::string name;
			std::string elementType;
		
			double weaponMinDamage = 0;
			double weaponMaxDamage = 0;
			double gearScore = 0;

			std::string classType;

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

			void ReadXml(const pugi::xml_node& node);
			void WriteXml(pugi::xml_node& node) const;

			void ReadJson(rapidjson::Value& object);
			rapidjson::Value WriteJson(rapidjson::Document::AllocatorType& allocator) const;
	};
}

#endif
