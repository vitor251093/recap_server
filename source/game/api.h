
#ifndef _GAME_API_HEADER
#define _GAME_API_HEADER

// Include
#include <rapidjson/document.h>
#include <pugixml.hpp>

// HTTP
namespace HTTP {
	class Session;
	class URI;
	class Response;
}

// Game
namespace Game {
	// API
	class API {
		public:
			API();

			void setup();

			// default
			void empty_xml_response(HTTP::Session& session, HTTP::Response& response);
			void empty_json_response(HTTP::Response& response);

			// recap
			void recap_launcher_setTheme(HTTP::Session& session, HTTP::Response& response);
			void recap_launcher_listThemes(HTTP::Session& session, HTTP::Response& response);

			void recap_game_registration(HTTP::Session& session, HTTP::Response& response);
			void recap_game_log(HTTP::Session& session, HTTP::Response& response);

			void recap_panel_listUsers(HTTP::Session& session, HTTP::Response& response);
			void recap_panel_getUserInfo(HTTP::Session& session, HTTP::Response& response);
			void recap_panel_setUserInfo(HTTP::Session& session, HTTP::Response& response);

			// bootstrap
			void bootstrap_config_getConfig(HTTP::Session& session, HTTP::Response& response);

			// game
			void game_status_getStatus(HTTP::Session& session, HTTP::Response& response);
			void game_status_getBroadcastList(HTTP::Session& session, HTTP::Response& response);

			void game_inventory_getPartList(HTTP::Session& session, HTTP::Response& response);
			void game_inventory_getPartOfferList(HTTP::Session& session, HTTP::Response& response);
			void game_inventory_vendorParts(HTTP::Session& session, HTTP::Response& response);
			void game_inventory_updatePartStatus(HTTP::Session& session, HTTP::Response& response);

			void game_leaderboard_getLeaderboard(HTTP::Session& session, HTTP::Response& response);

			void game_account_auth(HTTP::Session& session, HTTP::Response& response);
			void game_account_getAccount(HTTP::Session& session, HTTP::Response& response);
			void game_account_logout(HTTP::Session& session, HTTP::Response& response);
			void game_account_unlock(HTTP::Session& session, HTTP::Response& response);
			void game_account_setSettings(HTTP::Session& session, HTTP::Response& response);

			void game_deck_updateDecks(HTTP::Session& session, HTTP::Response& response);

			void game_game_getGame(HTTP::Session& session, HTTP::Response& response);
			void game_game_exitGame(HTTP::Session& session, HTTP::Response& response);

			void game_creature_getCreature(HTTP::Session& session, HTTP::Response& response);
			void game_creature_getTemplate(HTTP::Session& session, HTTP::Response& response);
			void game_creature_resetCreature(HTTP::Session& session, HTTP::Response& response);
			void game_creature_updateCreature(HTTP::Session& session, HTTP::Response& response);
			void game_creature_unlockCreature(HTTP::Session& session, HTTP::Response& response);
			
			// survey
			void survey_survey_getSurveyList(HTTP::Session& session, HTTP::Response& response);

		private:
			void responseWithFileInStorage(HTTP::Session& session, HTTP::Response& response);
			void responseWithFileInStorage(HTTP::Session& session, HTTP::Response& response, std::string path);
			void responseWithFileInStorageAtPath(HTTP::Session& session, HTTP::Response& response, std::string path);
			void responseWithHtmlContents(HTTP::Response& response, std::string_view file_data);
			void alertsResponse(HTTP::Session& session, HTTP::Response& response);

			void add_broadcasts(pugi::xml_node& node);

			void add_common_keys(pugi::xml_node& node, const std::string& darksporeVersion);
		
		private:
			std::string mActiveTheme = "darkui";

			uint32_t mPacketId = 0;
	};
}

#endif
