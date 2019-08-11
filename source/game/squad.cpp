
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

	void Squad::ReadJson(utils::jsonObject& object) {
		name     = object.GetString("name");
		category = object.GetString("category");
		id       = object.GetUint("id");
		slot     = object.GetUint("slot");
		locked   = object.GetBool("locked");
	}

	void Squad::WriteJson(utils::jsonObject& object) const { 
		object.Set("name",     name);
		object.Set("category", category);
		object.Set("id",       id);
		object.Set("slot",     slot);
		object.Set("locked",   locked);
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

	void Squads::ReadJson(utils::jsonArray& object) {
		mSquads.clear();
		for (auto& squadNode : object) {
			decltype(auto) squad = mSquads.emplace_back();
			squad.ReadJson(squadNode.GetObject());
		}
	}

	void Squads::WriteJson(utils::jsonArray& object) const { 
		for (const auto& squad : mSquads) {
			squad.WriteJson(object.NewObject());
		}
	}
}
