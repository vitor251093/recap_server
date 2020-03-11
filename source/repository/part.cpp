
// Include
#include "part.h"
#include <algorithm>
#include "../game/config.h"

// Repository
namespace Repository {

	PartPtr Parts::getById(uint16_t id) {
		Load();

		PartPtr part;

		auto it = mParts.find(id);
		if (it != mParts.end()) {
			part = it->second;
		}

		return part;
	}

	void Parts::Load() {
		if (!mParts.empty()) return;

		std::string jsonFilePath = Game::Config::Get(Game::CONFIG_STORAGE_PATH) + "/parts.json";
		auto templatesList = utils::json::FromFile(jsonFilePath);

		for (auto& creatureNode : templatesList.GetArray()) {
			PartPtr creature = std::make_shared<Game::Part>();
			creature->ReadJson(creatureNode);
			mParts.emplace(creature->rigblock_asset_id, creature);
		}
	}

	std::map<uint32_t, PartPtr> Parts::mParts;

	std::vector<PartPtr> Parts::ListAll() {
		Load();

		std::vector<PartPtr> l;
		for (const auto& t : mParts)
			l.push_back(t.second);

		return l;
	}
}
