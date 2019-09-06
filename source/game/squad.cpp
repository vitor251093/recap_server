
// Include
#include "squad.h"
#include <algorithm>

// Game
namespace Game {
	// Squad
	void Squad::ReadXml(const pugi::xml_node& node) {
		std::string_view nodeName = node.name();
		if (nodeName != "deck") {
			return;
		}

		name = utils::xml_get_text_node(node, "name");
		category = utils::xml_get_text_node(node, "category");

		id = utils::xml_get_text_node<uint32_t>(node, "id");
		slot = utils::xml_get_text_node<uint32_t>(node, "slot");

		locked = utils::xml_get_text_node<uint32_t>(node, "locked");

		creatures.ReadXml(node);
	}

	void Squad::WriteXml(pugi::xml_node& node) const {
		if (auto deck = node.append_child("deck")) {
			utils::xml_add_text_node(deck, "name", name);
			utils::xml_add_text_node(deck, "id", id);
			utils::xml_add_text_node(deck, "category", category);
			utils::xml_add_text_node(deck, "slot", slot);
			utils::xml_add_text_node(deck, "locked", locked ? 1 : 0);
			creatures.WriteXml(deck);
		}
	}

	void Squad::ReadJson(rapidjson::Value& object) {
		name     = object.GetObject()["name"    ].GetString();
		category = object.GetObject()["category"].GetString();
		id       = object.GetObject()["id"      ].GetUint();
		slot     = object.GetObject()["slot"    ].GetUint();
		locked   = object.GetObject()["locked"  ].GetBool();
	}

	rapidjson::Value Squad::WriteJson(rapidjson::Document::AllocatorType& allocator) const { 
		rapidjson::Value object(rapidjson::kObjectType);
		utils::json::SetString(object, "name",     name,     allocator);
		utils::json::SetString(object, "category", category, allocator);
		object.AddMember("id",     rapidjson::Value{}.SetUint(id),     allocator);
		object.AddMember("slot",   rapidjson::Value{}.SetUint(slot),   allocator);
		object.AddMember("locked", rapidjson::Value{}.SetBool(locked), allocator);
		return object;
	}

	// Squads
	void Squads::ReadXml(const pugi::xml_node& node) {
		auto decks = node.child("decks");
		if (!decks) {
			return;
		}

		for (const auto& deckNode : decks) {
			decltype(auto) squad = mSquads.emplace_back();
			squad.ReadXml(deckNode);
		}
	}

	void Squads::WriteXml(pugi::xml_node& node) const {
		if (auto decks = node.append_child("decks")) {
			for (const auto& squad : mSquads) {
				squad.WriteXml(decks);
			}
		}
	}

	void Squads::ReadJson(rapidjson::Value& object) {
		mSquads.clear();
		for (auto& squadNode : object.GetArray()) {
			decltype(auto) squad = mSquads.emplace_back();
			squad.ReadJson(squadNode);
		}
	}

	rapidjson::Value Squads::WriteJson(rapidjson::Document::AllocatorType& allocator) const { 
		rapidjson::Value value(rapidjson::kArrayType);
		for (const auto& squad : mSquads) {
			value.PushBack(squad.WriteJson(allocator), allocator);
		}
		return value;
	}
}
