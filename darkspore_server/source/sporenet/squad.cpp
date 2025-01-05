
// Include
#include "squad.h"
#include "utils/functions.h"
#include <algorithm>

// SporeNet
namespace SporeNet {
	// Squad
	Squad::Squad(uint32_t id, uint32_t slot)
		: mId(id), mSlot(slot) {}

	Squad::Squad(uint32_t id, uint32_t slot, std::string name, bool locked)
		: mId(id), mSlot(slot), mName(name), mLocked(locked) {}

	bool Squad::Read(const pugi::xml_node& node) {
		std::string_view nodeName = node.name();
		if (nodeName != "squad") {
			return false;
		}

		mName = utils::xml_get_text_node(node, "name");
		mCategory = utils::xml_get_text_node(node, "category");

		mId = utils::xml_get_text_node<uint32_t>(node, "id");
		mSlot = utils::xml_get_text_node<uint32_t>(node, "slot");

		mLocked = utils::xml_get_text_node<uint32_t>(node, "locked");

		if (auto creaturesNode = node.child("creatures")) {
			size_t count = 0;
			for (const auto& creatureNode : creaturesNode.children()) {
				mCreatureIds[count++] = creatureNode.attribute("id").as_uint();
				if (count >= mCreatureIds.size()) {
					break;
				}
			}
		}

		return true;
	}

	void Squad::Write(pugi::xml_node& node) const {
		if (auto deckNode = node.append_child("squad")) {
			utils::xml_add_text_node(deckNode, "name", mName);
			utils::xml_add_text_node(deckNode, "id", mId);
			utils::xml_add_text_node(deckNode, "category", mCategory);
			utils::xml_add_text_node(deckNode, "slot", mSlot);
			utils::xml_add_text_node(deckNode, "locked", mLocked ? 1 : 0);
			if (auto creaturesNode = deckNode.append_child("creatures")) {
				for (const auto id : mCreatureIds) {
					auto creatureNode = creaturesNode.append_child("creature");
					creatureNode.append_attribute("id").set_value(id);
				}
			}
		}
	}

	const std::array<uint32_t, 3>& Squad::GetCreatureIds() const {
		return mCreatureIds;
	}

	void Squad::SetCreatureId(uint8_t index, uint32_t id) {
		if (index < mCreatureIds.size()) {
			mCreatureIds[index] = id;
		}
	}

	const std::string Squad::GetName() const {
		return mName;
	}

	const std::string Squad::GetCategory() const {
		return mCategory;
	}

	uint32_t Squad::GetId() const {
		return mId;
	}

	uint32_t Squad::GetSlot() const {
		return mSlot;
	}

	bool Squad::IsLocked() const {
		return mLocked;
	}

	void Squad::Update(const std::string& creatureStringList, bool pvp) {
		auto creatureIds = utils::explode_string(creatureStringList, ',');
		auto length = std::min<size_t>(creatureIds.size(), mCreatureIds.size());
		for (size_t i = 0; i < length; ++i) {
			auto id = utils::to_number<uint32_t>(creatureIds[i]);
			if (id > 0) {
				mCreatureIds[i] = id;
			}
		}

		mCategory = pvp ? "pvp" : "pve";
		/*
		for (const auto& idString : creatureIds) {
			auto id = utils::to_number<uint32_t>(idString);
			if (id == 0) {
				continue;
			}

			auto creature = mCreatures.Get(id);
			if (creature) {
				*it++ = creature;
				if (it == mCreatures.end()) {
					break;
				}
			}
		}
		*/
	}

	// Squads
	void Squads::Read(const pugi::xml_node& node) {
		auto decks = node.child("decks");
		if (!decks) {
			return;
		}

		for (const auto& deckNode : decks) {
			decltype(auto) squad = mSquads.emplace_back();
			squad.Read(deckNode);
		}
	}

	void Squads::Write(pugi::xml_node& node) const {
		if (auto decks = node.append_child("decks")) {
			for (const auto& squad : mSquads) {
				squad.Write(decks);
			}
		}
	}

	Squad* Squads::Create() {
		if (mSquads.size() >= 3) {
			return nullptr;
		}

		auto& squad = mSquads.emplace_back();
		//squad.id = static_cast<uint32_t>(mSquads.size());
		//squad.slot = squad.id;

		return &squad;
	}

	void Squads::Remove(size_t index) {
		if (index < mSquads.size()) {
			mSquads.erase(mSquads.begin() + index);
		}
	}

	Squad* Squads::Get(size_t index) {
		if (index < mSquads.size()) {
			return &mSquads[index];
		}
		return nullptr;
	}
}
