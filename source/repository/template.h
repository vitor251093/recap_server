
#ifndef _GAME_REPO_TEMPLATE_HEADER
#define _GAME_REPO_TEMPLATE_HEADER

// Include
#include <string>
#include <map>
#include <vector>
#include "../utils/functions.h"
#include "../game/template.h"

// Game
namespace Repository {

	using CreatureTemplatePtr = std::shared_ptr<Game::CreatureTemplate>;

	class CreatureTemplates {
		public:
			static CreatureTemplatePtr getById(uint32_t id);
			static void Load();
			static std::vector<CreatureTemplatePtr> ListAll();

		private:
			static std::map<uint32_t, CreatureTemplatePtr> mTemplates;
			friend class Game::CreatureTemplate;
	};
}

#endif
