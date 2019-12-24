
#ifndef _GAME_CREATURE_HEADER
#define _GAME_CREATURE_HEADER

// Include
#include <vector>
#include "template.h"
#include "../utils/functions.h"

// Game
namespace Game {
	
	// Creature
	struct Creature {

		uint32_t id = 0;
		uint64_t nounId = 0;

		//stats
		//stats_ability_keyvalues
		//parts[]
		//   part

		std::string pngLargeUrl;
		std::string pngThumbUrl;

		double itemPoints = 0;
		double gearScore = 0;

		uint32_t version = 0;

		void ReadXml(const pugi::xml_node& node);
		void WriteXml(pugi::xml_node& node) const;

		void ReadJson(rapidjson::Value& object);
		rapidjson::Value WriteJson(rapidjson::Document::AllocatorType& allocator) const;
	};

	// Creatures
	class Creatures {
		public:
			decltype(auto) begin() { return mCreatures.begin(); }
			decltype(auto) begin() const { return mCreatures.begin(); }
			decltype(auto) end() { return mCreatures.end(); }
			decltype(auto) end() const { return mCreatures.end(); }

			auto& data() { return mCreatures; }
			const auto& data() const { return mCreatures; }

			void setData(std::vector<Creature> creatures) { mCreatures = creatures; }

			void ReadXml(const pugi::xml_node& node);
			void WriteXml(pugi::xml_node& node) const;

			void ReadJson(rapidjson::Value& object);
			rapidjson::Value WriteJson(rapidjson::Document::AllocatorType& allocator) const;

			void Add(uint32_t templateId);

		private:
			std::vector<Creature> mCreatures;
	};
}

#endif
