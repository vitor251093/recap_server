
#ifndef _GAME_SQUAD_HEADER
#define _GAME_SQUAD_HEADER

// Include
#include "creature.h"

// Game
namespace Game {
	// Squad
	struct Squad {
		Creatures creatures;

		std::string name;
		std::string category;

		uint32_t id = 0;
		uint32_t slot = 0;

		bool locked = true;

		void ReadXml(const pugi::xml_node& node);
		void WriteXml(pugi::xml_node& node) const;

		void ReadJson(utils::jsonObject& object);
		void WriteJson(utils::jsonObject& object) const;
	};

	// Squads
	class Squads {
		public:
			decltype(auto) begin() { return mSquads.begin(); }
			decltype(auto) begin() const { return mSquads.begin(); }
			decltype(auto) end() { return mSquads.end(); }
			decltype(auto) end() const { return mSquads.end(); }

			auto& data() { return mSquads; }
			const auto& data() const { return mSquads; }

			void ReadXml(const pugi::xml_node& node);
			void WriteXml(pugi::xml_node& node) const;

			void ReadJson(utils::jsonArray& object);
			void WriteJson(utils::jsonArray& object) const;

		private:
			std::vector<Squad> mSquads;
	};
}

#endif
