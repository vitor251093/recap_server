
// Include
#include "userpart.h"
#include <algorithm>
#include "../game/config.h"
#include "../utils/logger.h"

// Repository
namespace Repository {

	void UserParts::Add(Game::UserPartPtr part) {
		mPartsById.emplace(part->id, part);
	}
	void UserParts::Remove(Game::UserPartPtr part) {
		mPartsById.erase(part->id);
	}
	void UserParts::Remove(uint64_t id) {
		mPartsById.erase(id);
	}

	Game::UserPartPtr UserParts::getById(uint64_t id) {
		Load();

		Game::UserPartPtr part;

		auto it = mPartsById.find(id);
		if (it != mPartsById.end()) {
			part = it->second;
		}

		return part;
	}

	void UserParts::Load() {
		if (!mPartsById.empty()) return;

		std::string filepath = Game::Config::Get(Game::CONFIG_STORAGE_PATH) + "user_parts.xml";

		pugi::xml_document document;
		if (!document.load_file(filepath.c_str())) {
			pugi::xml_document document;
			document.append_child("parts");
			document.save_file(filepath.c_str(), "\t", 1U, pugi::encoding_latin1);
			return;
		}

		auto parts = document.child("parts");
		if (!parts) {
			parts = document.append_child("parts");
		}

		for (const auto& partNode : parts) {
			Add(std::make_shared<Game::UserPart>(partNode));
		}
	}

	bool UserParts::Save() {
		pugi::xml_document document;

		auto allParts = Repository::UserParts::ListAll();
		if (auto parts = document.append_child("parts")) {
			uint32_t index = 0;
			for (const auto& part : allParts) {
				part->WriteSmallXml(parts);
			}
		}

		std::string filepath = Game::Config::Get(Game::CONFIG_STORAGE_PATH) + "user_parts.xml";
		return document.save_file(filepath.c_str(), "\t", 1U, pugi::encoding_latin1);
	}

	std::map<uint64_t, Game::UserPartPtr> UserParts::mPartsById;

	std::vector<Game::UserPartPtr> UserParts::ListAll() {
		Load();

		std::vector<Game::UserPartPtr> l;
		for (const auto& t : mPartsById)
			l.push_back(t.second);

		return l;
	}
}
