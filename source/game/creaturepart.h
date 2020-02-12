
#ifndef _GAME_CREATUREPART_HEADER
#define _GAME_CREATUREPART_HEADER

// Include
#include "game.h"

#include <map>
#include "../utils/functions.h"

// Game
namespace Game {
	// Part
	class CreaturePart {
	public:
		uint64_t id;
		uint16_t rigblock_asset_id;
		
		uint64_t timestamp;
		uint32_t equipped_to_creature_id;

		uint8_t status;

		CreaturePart();
		CreaturePart(uint32_t rigblock);
		CreaturePart(const pugi::xml_node& node);

		bool ReadXml(const pugi::xml_node& node);
		
		void WriteSmallXml(pugi::xml_node& node) const;
		void WriteXml(pugi::xml_node& node, uint32_t index, bool api = false) const;

		void ReadJson(rapidjson::Value& object);
		rapidjson::Value WriteJson(rapidjson::Document::AllocatorType& allocator, uint32_t index, bool api = false) const;

		void SetStatus(uint8_t newStatus);

	private:
		friend class CreatureParts;
	};

	// Parts
	class CreatureParts {
	public:
		decltype(auto) begin() { return mItems.begin(); }
		decltype(auto) begin() const { return mItems.begin(); }
		decltype(auto) end() { return mItems.end(); }
		decltype(auto) end() const { return mItems.end(); }

		auto& data() { return mItems; }
		const auto& data() const { return mItems; }

		CreaturePart* GetPartById(uint32_t id);

		void ReadXml(const pugi::xml_node& node);

		void WriteSmallXml(pugi::xml_node& node) const;
		void WriteXml(pugi::xml_node& node, bool api = false) const;

		void ReadJson(rapidjson::Value& object);
		rapidjson::Value WriteJson(rapidjson::Document::AllocatorType& allocator, bool api = false) const;

		void Add(CreaturePart part);

	private:
		std::vector<CreaturePart> mItems;
	};
}

#endif
