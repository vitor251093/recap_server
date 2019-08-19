
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
		if (!object.IsObject()) return;
		name     = utils::json::GetString(object, "name");
		category = utils::json::GetString(object, "category");
		id       = utils::json::GetUint(object, "id");
		slot     = utils::json::GetUint(object, "slot");
		locked   = utils::json::GetBool(object, "locked");
	}

	rapidjson::Value Squad::WriteJson(rapidjson::Document::AllocatorType& allocator) const { 
		rapidjson::Value object = utils::json::NewObject();
		utils::json::Set(object, "name",     name,     allocator);
		utils::json::Set(object, "category", category, allocator);
		utils::json::Set(object, "id",       id,       allocator);
		utils::json::Set(object, "slot",     slot,     allocator);
		utils::json::Set(object, "locked",   locked,   allocator);
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
		if (!object.IsArray()) return;
		mSquads.clear();
		for (auto& squadNode : object.GetArray()) {
			decltype(auto) squad = mSquads.emplace_back();
			squad.ReadJson(squadNode);
		}
	}

	rapidjson::Value Squads::WriteJson(rapidjson::Document::AllocatorType& allocator) const { 
		rapidjson::Value value = utils::json::NewArray();
		for (const auto& squad : mSquads) {
			rapidjson::Value squadNode = squad.WriteJson(allocator);
			utils::json::Add(value, squadNode, allocator);
		}
		return value;
	}
}
