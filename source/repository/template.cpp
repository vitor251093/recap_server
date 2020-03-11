
// Include
#include "template.h"
#include <algorithm>
#include "../game/config.h"

// Repository
namespace Repository {
	
	CreatureTemplatePtr CreatureTemplates::getById(uint32_t id) {
		Load();
		
		CreatureTemplatePtr creatureTemplate;

		auto it = mTemplates.find(id);
		if (it != mTemplates.end()) {
			creatureTemplate = it->second;
		}

		return creatureTemplate;
	}

	void CreatureTemplates::Load() {
		if (!mTemplates.empty()) return;

		std::string jsonFilePath = Game::Config::Get(Game::CONFIG_STORAGE_PATH) + "/templates.json";
		auto templatesList = utils::json::FromFile(jsonFilePath);

		for (auto& creatureNode : templatesList.GetArray()) {
			CreatureTemplatePtr creature = std::make_shared<Game::CreatureTemplate>();
			creature->ReadJson(creatureNode);
			mTemplates.emplace(creature->id, creature);
		}
	}

	std::map<uint32_t, CreatureTemplatePtr> CreatureTemplates::mTemplates;

	std::vector<CreatureTemplatePtr> CreatureTemplates::ListAll() {
		Load();

		std::vector<CreatureTemplatePtr> l;

		for (const auto& t : mTemplates)
			l.push_back(t.second);
		
		return l;
	}
}
