
// Include
#include "api.h"
#include "config.h"

#include "../main.h"

#include "../http/session.h"
#include "../http/router.h"
#include "../http/uri.h"
#include "../http/multipart.h"
#include "../utils/functions.h"

#include <boost/beast/version.hpp>

#include <iostream>
#include <filesystem>

/*
	api.account.auth
		response
			timestamp
				{TIMESTAMP}

			account
				tutorial_completed
				chain_progression
				creature_rewards
				current_game_id
				current_playgroup_id
				default_deck_pve_id
				default_deck_pvp_id
				level
				avatar_id
				id
				new_player_inventory
				new_player_progress
				cashout_bonus_time
				star_level
				unlock_catalysts
				unlock_diagonal_catalysts
				unlock_fuel_tanks
				unlock_inventory
				unlock_pve_decks
				unlock_pvp_decks
				unlock_stats
				unlock_inventory_identify
				unlock_editor_flair_slots
				upsell
				xp
				grant_all_access
				cap_level
				cap_progression

			creatures
				id
				name
				png_thumb_url
				noun_id
				version
				gear_score
				item_points

			decks
				name
				category
				id
				slot
				locked
				creatures
					{SAME_AS_CREATURES_BEFORE}

			feed
				items

			settings

			server_tuning
				itemstore_offer_period
				itemstore_current_expiration
				itemstore_cost_multiplier_basic
				itemstore_cost_multiplier_uncommon
				itemstore_cost_multiplier_rare
				itemstore_cost_multiplier_epic
				itemstore_cost_multiplier_unique
				itemstore_cost_multiplier_rareunique
				itemstore_cost_multiplier_epicunique

*/

// Game
namespace Game {
	constexpr std::string_view skipLauncherScript = R"(
<!DOCTYPE html PUBLIC "-//IETF//DTD HTML 2.0//EN">
<html>
	<head>
		<script type="text/javascript">
			window.onload = function() {
				Client.playCurrentApp();
			}
		</script>
	</head>
	<body>
	</body>
</html>
)";

	constexpr std::string_view dlsClientScript = R"(
<script>
	var DLSClient = {};
	DLSClient.getRequest = function(url, callback, errorCallback) {
		var xmlHttp = new XMLHttpRequest(); 
		xmlHttp.onload = function() {
			if (callback !== undefined) callback(xmlHttp.responseText);
		}
		xmlHttp.onerror = function(e) {
			if (errorCallback !== undefined) errorCallback(e);
		};
		xmlHttp.open("GET", url, true);
		xmlHttp.send(null);
	};
	DLSClient.request = function(name, params, callback, errorCallback) {
		if (params !== undefined && typeof params === 'object') {
			var str = [];
			for (var p in params)
				if (params.hasOwnProperty(p)) {
					str.push(encodeURIComponent(p) + "=" + encodeURIComponent(params[p]));
				}
			params = str.join("&");
		}
		DLSClient.getRequest("http://{{host}}/dls/api?method=" + name + (params === undefined ? "" : ("&" + params)), callback, errorCallback);
	};
</script>
)";

	// API
	API::API(const std::string& version) : mVersion(version) {
		// Empty
	}

	void API::responseWithFileInStorage(HTTP::Session& session, HTTP::Response& response) {
		responseWithFileInStorage(session, response, "");
	}

	void API::responseWithFileInStorage(HTTP::Session& session, HTTP::Response& response, std::string path) {
		auto& request = session.get_request();
		std::string name = request.uri.resource();
		if (name.ends_with("/")) name = name + "index.html";
		responseWithFileInStorageAtPath(session, response, path + name);
	}

	void API::responseWithFileInStorageAtPath(HTTP::Session& session, HTTP::Response& response, std::string path) {
		std::string wholePath = Config::Get(CONFIG_STORAGE_PATH) + path;

		response.version() |= 0x1000'0000;
		response.body() = std::move(wholePath);
	}

	void API::setup() {
		const auto& router = Application::GetApp().get_http_server()->get_router();

		// Routing
		router->add("/api", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [](HTTP::Session& session, HTTP::Response& response) {
			std::cout << "Got API route." << std::endl;
		});

		// DLS
		router->add("/dls/api", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			auto& request = session.get_request();

			auto method = request.uri.parameter("method");
			if (method == "api.launcher.setTheme") {
				dls_launcher_setTheme(session, response);
			} else if (method == "api.launcher.listThemes") {
				dls_launcher_listThemes(session, response);
			} else if (method == "api.game.registration") {
				dls_game_registration(session, response);
			} else if (method == "api.game.log") {
				dls_game_log(session, response);
			} else if (method == "api.panel.listUsers") {
				dls_panel_listUsers(session, response);
			} else if (method == "api.panel.getUserInfo") {
				dls_panel_getUserInfo(session, response);
			} else if (method == "api.panel.setUserInfo") {
				dls_panel_setUserInfo(session, response);
			} else {
				std::cout << "Undefined /dls/api method: " << method << std::endl;
				response.result() = boost::beast::http::status::internal_server_error;
			}
		});

		// Launcher
		router->add("/bootstrap/api", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			auto& request = session.get_request();

			auto method = request.uri.parameter("method");
			if (method == "api.config.getConfigs") {
				bootstrap_config_getConfig(session, response);
				return;
			}

			std::cout << "Undefined /bootstrap/api method: " << method << std::endl;
			response.result() = boost::beast::http::status::internal_server_error;
		});

		router->add("/bootstrap/launcher/", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			auto& request = session.get_request();

			auto version = request.uri.parameter("version");
			if (Config::GetBool(CONFIG_SKIP_LAUNCHER)) {
				response.set(boost::beast::http::field::content_type, "text/html");
				response.body() = skipLauncherScript;
			} else {
				std::string path = Config::Get(CONFIG_STORAGE_PATH) +
					"www/" +
					Config::Get(CONFIG_DARKSPORE_LAUNCHER_THEMES_PATH) +
					mActiveTheme + "/index.html";

				std::string client_script(dlsClientScript);
				utils::string_replace(client_script, "{{host}}", Config::Get(CONFIG_SERVER_HOST));

				std::string file_data = utils::get_file_text(path);
				utils::string_replace(file_data, "</head>", client_script + "</head>");

				response.set(boost::beast::http::field::content_type, "text/html");
				response.body() = std::move(file_data);
			}
		});

		router->add("/bootstrap/launcher/images/([a-zA-Z0-9_.]+)", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			auto& request = session.get_request();

			const std::string& resource = request.uri.resource();

			std::string path = Config::Get(CONFIG_STORAGE_PATH) +
				"www/" +
				Config::Get(CONFIG_DARKSPORE_LAUNCHER_THEMES_PATH) +
				mActiveTheme + "/images/" +
				resource.substr(resource.rfind('/') + 1);

			response.version() |= 0x1000'0000;
			response.body() = std::move(path);
		});

		router->add("/bootstrap/launcher/notes", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			std::string path = Config::Get(CONFIG_STORAGE_PATH) +
				"www/" +
				Config::Get(CONFIG_DARKSPORE_LAUNCHER_NOTES_PATH);

			std::string file_data = utils::get_file_text(path);
			utils::string_replace(file_data, "{{dls-version}}", Config::dlsVersion());
			utils::string_replace(file_data, "{{version-lock}}", Config::GetBool(CONFIG_VERSION_LOCKED) ? mVersion : "no");
			utils::string_replace(file_data, "{{game-mode}}", Config::GetBool(CONFIG_SINGLEPLAYER_ONLY) ? "singleplayer" : "multiplayer");
			utils::string_replace(file_data, "{{display-latest-version}}", "none");
			utils::string_replace(file_data, "{{latest-version}}", "yes");

			response.set(boost::beast::http::field::content_type, "text/html");
			response.body() = std::move(file_data);
		});

		// Game
		router->add("/game/api", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			auto& request = session.get_request();

			if (request.data.method() == boost::beast::http::verb::post) {
				// Fetch boundary later from request.data[boost::beast::http::field::content_type]
				
				HTTP::Multipart multipart(request.data.body(), "EA_HTTP_REQUEST_SIMPLE_BOUNDARY");
				for (const auto&[name, value] : multipart) {
					request.uri.set_parameter(name, value);
				}
			}

			auto cookies = request.data[boost::beast::http::field::cookie];
			if (!cookies.empty()) {
				auto cookieList = boost::beast::http::param_list(";" + cookies.to_string());
				for (auto& [name, value] : request.uri) {
					if (value == "cookie") {
						for (const auto& param : cookieList) {
							if (std::strncmp(param.first.data(), name.c_str(), name.length()) == 0) {
								value = param.second.to_string();
								break;
							}
						}
					}
					std::cout << name << " = " << value << std::endl;
				}
				std::cout << std::endl;
			}

			auto version = request.uri.parameter("version");
			auto build = request.uri.parameter("build");

			auto method = request.uri.parameter("method");
			if (method.empty()) {
				if (request.uri.parameter("token") == "cookie") {
					method = "api.account.auth";
				} else {
					method = "api.account.getAccount";
				}
			}

			auto token = request.uri.parameter("token");
			if (!token.empty()) {
				const auto& user = Game::UserManager::GetUserByAuthToken(token);
				if (user) {
					session.set_user(user);
				}
			}

			if (method == "api.account.setNewPlayerStats") {
				method = "api.account.auth";
			}

			       if (method == "api.status.getStatus") {
				game_status_getStatus(session, response);
			} else if (method == "api.status.getBroadcastList") {
				game_status_getBroadcastList(session, response);
			} else if (method == "api.inventory.getPartList") {
				game_inventory_getPartList(session, response);
			} else if (method == "api.inventory.getPartOfferList") {
				game_inventory_getPartOfferList(session, response);
			} else if (method == "api.inventory.updatePartStatus") {
				game_inventory_updatePartStatus(session, response);
			} else if (method == "api.inventory.vendorParts") {
				game_inventory_vendorParts(session, response);
			} else if (method == "api.account.auth") {
				game_account_auth(session, response);
			} else if (method == "api.account.getAccount") {
				game_account_getAccount(session, response);
			} else if (method == "api.account.logout") {
				game_account_logout(session, response);
			} else if (method == "api.account.unlock") {
				game_account_unlock(session, response);
			} else if (method == "api.game.getGame" || method == "api.game.getRandomGame") {
				game_game_getGame(session, response);
			} else if (method == "api.game.exitGame") {
				game_game_exitGame(session, response);
			} else if (method == "api.creature.resetCreature") {
				game_creature_resetCreature(session, response);
			} else if (method == "api.creature.unlockCreature") {
				game_creature_unlockCreature(session, response);
			} else {
				std::cout << "Undefined /game/api method: " << method << std::endl;
				for (const auto& [name, value] : request.uri) {
					std::cout << name << " = " << value << std::endl;
				}
				std::cout << std::endl;
				empty_xml_response(response);
			}
		});

		/*
Undefined /game/api method: api.deck.updateDecks
method = api.deck.updateDecks
pve_active_slot = 1
pve_creatures = 10,11,3948469269,0,0,0,0,0,0
pvp_active_slot = 28614456
pvp_creatures = 0,0,0,0,0,0,0,0,0
token = ABCDEFGHIJKLMNOPQRSTUVWXYZ
version = 1
		*/



		// Png
		router->add("/template_png/([a-zA-Z0-9_.]+)", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			responseWithFileInStorage(session, response);
		});

		router->add("/creature_png/([a-zA-Z0-9_.]+)", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			responseWithFileInStorage(session, response);
		});


		// Browser launcher
		router->add("/favicon.ico", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			responseWithFileInStorage(session, response, "/www");
		});

		router->add("/panel/([/a-zA-Z0-9\\-_.]*)", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			responseWithFileInStorage(session, response, "/www");
		});


		// Survey
		router->add("/survey/api", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			auto& request = session.get_request();

			auto version = request.uri.parameter("version");
			auto method = request.uri.parameter("method");

			if (method == "api.survey.getSurveyList") {
				survey_survey_getSurveyList(session, response);
			} else {
				std::cout << "Undefined /survey/api method: " << method << std::endl;
				empty_xml_response(response);
			}
		});

		// Web
		router->add("/web/sporelabsgame/announceen", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			std::string contentsFolder = Config::Get(CONFIG_STORAGE_PATH) + "www/ingame/";
			std::string path = contentsFolder + "announce.html";
			
			std::string file_data = utils::get_html_file_for_darkspore_webkit(path, contentsFolder);

			utils::string_replace(file_data, "{{host}}", Config::Get(CONFIG_SERVER_HOST));
			utils::string_replace(file_data, "{{isDev}}", "true");

			response.set(boost::beast::http::field::content_type, "text/html");
			response.body() = std::move(file_data);
		});

		router->add("/web/sporelabsgame/register", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			std::string contentsFolder = Config::Get(CONFIG_STORAGE_PATH) + "www/ingame/";
			std::string path = contentsFolder + Config::Get(CONFIG_DARKSPORE_REGISTER_PAGE_PATH);
			
			std::string file_data = utils::get_html_file_for_darkspore_webkit(path, contentsFolder);

			utils::string_replace(file_data, "{{host}}", Config::Get(CONFIG_SERVER_HOST));
			utils::string_replace(file_data, "{{isDev}}", "true");

			response.set(boost::beast::http::field::content_type, "text/html");
			response.body() = std::move(file_data);
		});

		router->add("/web/sporelabsgame/resetpassword", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			// That one is launched in the system browser
			response.set(boost::beast::http::field::content_type, "text/html");
			response.body() = "";
		});

		router->add("/web/sporelabsgame/persona", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			response.set(boost::beast::http::field::content_type, "text/html");
			response.body() = "";
		});

		// QOS
		router->add("/qos/qos", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			auto& request = session.get_request();

			auto version = request.uri.parameteri("vers");
			auto type = request.uri.parameteri("qtyp");
			auto port = request.uri.parameteri("prpt");

			if (type == 1 && port == 3659) {
				pugi::xml_document document;

				auto docResponse = document.append_child("response");
				utils::xml::Set(docResponse, "result", "1,0,1");
				add_common_keys(docResponse);

				response.set(boost::beast::http::field::content_type, "text/xml");
				response.body() = utils::xml::ToString(document);
			} else {
				response.set(boost::beast::http::field::content_type, "text/plain");
				response.body() = "";
			}
		});
	}

	void API::empty_xml_response(HTTP::Response& response) {
		pugi::xml_document document;

		auto docResponse = document.append_child("response");
		add_common_keys(docResponse);

		response.set(boost::beast::http::field::content_type, "text/xml");
		response.body() = utils::xml::ToString(document);
	}

	void API::empty_json_response(HTTP::Response& response) {
		response.set(boost::beast::http::field::content_type, "application/json");
	}

	void API::dls_launcher_setTheme(HTTP::Session& session, HTTP::Response& response) {
		auto& request = session.get_request();
		auto themeName = request.uri.parameter("theme");

		mActiveTheme = themeName;
		
		rapidjson::Document document = utils::json::NewDocumentObject();
		
		// stat
		utils::json::Set(document, "stat", "ok");

		response.set(boost::beast::http::field::content_type, "application/json");
		response.body() = utils::json::ToString(document);
	}

	void API::dls_launcher_listThemes(HTTP::Session& session, HTTP::Response& response) {
		rapidjson::Document document = utils::json::NewDocumentObject();

		rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

		// stat
		utils::json::Set(document, "stat", "ok");
		
		// themes
		{
			std::string themesFolderPath = Config::Get(CONFIG_STORAGE_PATH) +
					"www/" + Config::Get(CONFIG_DARKSPORE_LAUNCHER_THEMES_PATH);
			rapidjson::Value value = utils::json::NewArray();
			for (const auto & entry : std::filesystem::directory_iterator(themesFolderPath)) {
				if (entry.is_directory()) {
					utils::json::Add(value, entry.path().filename().string(), allocator);
				}
			}
			utils::json::Set(document, "themes", value);
		}

		// selectedTheme
		utils::json::Set(document, "selectedTheme", mActiveTheme);

		response.set(boost::beast::http::field::content_type, "application/json");
		response.body() = utils::json::ToString(document);
	}

	void API::dls_game_registration(HTTP::Session& session, HTTP::Response& response) {
		auto& request = session.get_request();
		auto name = request.uri.parameter("name");
		auto mail = request.uri.parameter("mail");
		auto pass = request.uri.parameter("pass");

		const auto& user = Game::UserManager::CreateUserWithNameMailAndPassword(name, mail, pass);

		rapidjson::Document document = utils::json::NewDocumentObject();
		if (user == NULL) {
			utils::json::Set(document, "stat", "error");
		} else {
			utils::json::Set(document, "stat", "ok");
		}
		response.set(boost::beast::http::field::content_type, "application/json");
		response.body() = utils::json::ToString(document);
	}

	void API::dls_game_log(HTTP::Session& session, HTTP::Response& response) {
		auto& request = session.get_request();
		auto postBody = request.data.body();
		std::cout << postBody << std::endl;
	}

	void API::dls_panel_listUsers(HTTP::Session& session, HTTP::Response& response) {
		rapidjson::Document document = utils::json::NewDocumentObject();

		rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

		// stat
		utils::json::Set(document, "stat", "ok");
		
		const auto users = Game::UserManager::GetAllUserNames();
		const auto loggedUsers = Game::UserManager::GetLoggedUserNames();
		rapidjson::Value value = utils::json::NewArray();
		for (const auto & entry : users) {
			bool isLogged = std::find(loggedUsers.begin(), loggedUsers.end(), entry) != loggedUsers.end();
			
			rapidjson::Value object = utils::json::NewObject();
			utils::json::Set(object, "email", entry, allocator);
			utils::json::Set(object, "logged", isLogged, allocator);
			utils::json::Add(value, object, allocator);
		}
		utils::json::Set(document, "users", value);
		
		response.set(boost::beast::http::field::content_type, "application/json");
		response.body() = utils::json::ToString(document);
	}

	void API::dls_panel_getUserInfo(HTTP::Session& session, HTTP::Response& response) {
		auto& request = session.get_request();
		auto mail = request.uri.parameter("mail");

		const auto& user = Game::UserManager::GetUserByEmail(mail, false);

		rapidjson::Document document = utils::json::NewDocumentObject();

		rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

		if (user == NULL) {
			// stat
			utils::json::Set(document, "stat", "error");
		}
		else {
			// stat
			rapidjson::Value users = user->ToJson(allocator);
			utils::json::Set(document, "stat", "ok");
			utils::json::Set(document, "user", users);
		}

		response.set(boost::beast::http::field::content_type, "application/json");
		response.body() = utils::json::ToString(document);
	}

	void API::dls_panel_setUserInfo(HTTP::Session& session, HTTP::Response& response) {
		auto& request = session.get_request();
		auto mail = request.uri.parameter("mail");
		auto userJsonString = request.data.body();
		
		std::cout << userJsonString << std::endl;
		rapidjson::Document userJson = utils::json::Parse(userJsonString);

		const auto& user = Game::UserManager::GetUserByEmail(mail, false);
		
		rapidjson::Document document = utils::json::NewDocumentObject();

		rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

		if (user == NULL) {
			// stat
			utils::json::Set(document, "stat", "error");
		}
		else {
			user->FromJson(userJson);
			user->Save();
			
			// stat
			utils::json::Set(document, "stat", "ok");
		}

		response.set(boost::beast::http::field::content_type, "application/json");
		response.body() = utils::json::ToString(document);
	}

	void API::bootstrap_config_getConfig(HTTP::Session& session, HTTP::Response& response) {
		auto& request = session.get_request();

		pugi::xml_document document;

		const auto& host = Config::Get(CONFIG_SERVER_HOST);

		auto docResponse = document.append_child("response");
		if (auto configs = docResponse.append_child("configs")) {
			if (auto config = configs.append_child("config")) {
				utils::xml::Set(config, "blaze_service_name", "darkspore");
				utils::xml::Set(config, "blaze_secure", "Y");
				utils::xml::Set(config, "blaze_env", "production");
				utils::xml::Set(config, "sporenet_cdn_host", host);
				utils::xml::Set(config, "sporenet_cdn_port", "80");
				utils::xml::Set(config, "sporenet_db_host", host);
				utils::xml::Set(config, "sporenet_db_port", "80");
				utils::xml::Set(config, "sporenet_db_name", "darkspore");
				utils::xml::Set(config, "sporenet_host", host);
				utils::xml::Set(config, "sporenet_port", "80");
				utils::xml::Set(config, "http_secure", "N");
				utils::xml::Set(config, "liferay_host", host);
				utils::xml::Set(config, "liferay_port", "80");
				utils::xml::Set(config, "launcher_action", "2");
				utils::xml::Set(config, "launcher_url", "http://" + host + "/bootstrap/launcher/?version=" + mVersion);
			}
		}

		docResponse.append_child("to_image");
		docResponse.append_child("from_image");

		if (request.uri.parameterb("include_settings")) {
			if (auto settings = docResponse.append_child("settings")) {
				utils::xml::Set(settings, "open", "true");
				utils::xml::Set(settings, "telemetry-rate", "256");
				utils::xml::Set(settings, "telemetry-setting", "0");
			}
		}

		if (request.uri.parameterb("include_patches")) {
			docResponse.append_child("patches");
			/*
			target, date, from_version, to_version, id, description, application_instructions,
			locale, shipping, file_url, archive_size, uncompressed_size,
			hashes(attributes, Version, Hash, Size, BlockSize)
			*/
		}

		add_common_keys(docResponse);

		//utils::xml::Set(node, "version", mVersion);

		response.set(boost::beast::http::field::content_type, "text/xml");
		response.body() = utils::xml::ToString(document);
	}

	void API::game_status_getStatus(HTTP::Session& session, HTTP::Response& response) {
		auto& request = session.get_request();

		pugi::xml_document document;

		auto docResponse = document.append_child("response");
		if (auto status = docResponse.append_child("status")) {
			utils::xml::Set(status, "health", "1");

			if (auto api = status.append_child("api")) {
				utils::xml::Set(api, "health", "1");
				utils::xml::Set(api, "revision", "1");
				utils::xml::Set(api, "version", "1");
			}

			if (auto blaze = status.append_child("blaze")) {
				utils::xml::Set(blaze, "health", "1");
			}

			if (auto gms = status.append_child("gms")) {
				utils::xml::Set(gms, "health", "1");
			}

			if (auto nucleus = status.append_child("nucleus")) {
				utils::xml::Set(nucleus, "health", "1");
			}

			if (auto game = status.append_child("game")) {
				utils::xml::Set(game, "health", "1");
				utils::xml::Set(game, "countdown", "0");
				utils::xml::Set(game, "open", "1");
				utils::xml::Set(game, "throttle", "0");
				utils::xml::Set(game, "vip", "0");
			}
			/*
			if (auto unk = status.append_child("$\x84")) {
				utils::xml::Set(unk, "health", "1");
				utils::xml::Set(unk, "revision", "1");
				utils::xml::Set(unk, "db_version", "1");
			}

			if (auto unk = status.append_child("$\x8B")) {
				utils::xml::Set(unk, "health", "1");
			}
			*/
		}

		if (request.uri.parameterb("include_broadcasts")) {
			add_broadcasts(docResponse);
		}

		add_common_keys(docResponse);

		response.set(boost::beast::http::field::content_type, "text/xml");
		response.body() = utils::xml::ToString(document);
	}

	void API::game_status_getBroadcastList(HTTP::Session& session, HTTP::Response& response) {
		pugi::xml_document document;

		auto docResponse = document.append_child("response");
		add_broadcasts(docResponse);
		add_common_keys(docResponse);

		response.set(boost::beast::http::field::content_type, "text/xml");
		response.body() = utils::xml::ToString(document);
	}

	void API::game_inventory_getPartList(HTTP::Session& session, HTTP::Response& response) {
		pugi::xml_document document;

		if (auto docResponse = document.append_child("response")) {
			const auto& user = session.get_user();
			if (user) {
				user->get_parts().WriteXml(docResponse, true);
			} else {
				docResponse.append_child("parts");
			}
			add_common_keys(docResponse);
		}

		response.set(boost::beast::http::field::content_type, "text/xml");
		response.body() = utils::xml::ToString(document);
	}

	void API::game_inventory_getPartOfferList(HTTP::Session& session, HTTP::Response& response) {
		pugi::xml_document document;

		if (auto docResponse = document.append_child("response")) {
			auto timestamp = utils::get_unix_time();

			utils::xml::Set(docResponse, "expires", timestamp + (3 * 60 * 60 * 1000));
			if (auto parts = docResponse.append_child("parts")) {
				/*
				if (auto part = parts.append_child("part")) {
					utils::xml::Set(part, "is_flair", "0");
					utils::xml::Set(part, "cost", "100");
					utils::xml::Set(part, "creature_id", static_cast<uint64_t>(CreatureID::BlitzAlpha));
					utils::xml::Set(part, "id", "1");
					utils::xml::Set(part, "level", "1");
					utils::xml::Set(part, "market_status", "1");
					utils::xml::Set(part, "prefix_asset_id", 0x010C);
					utils::xml::Set(part, "prefix_secondary_asset_id", "0");
					utils::xml::Set(part, "rarity", "1");
					utils::xml::Set(part, "reference_id", 1);
					utils::xml::Set(part, "rigblock_asset_id", 0x27A1); // 0xA14538E5
					utils::xml::Set(part, "status", "1");
					utils::xml::Set(part, "suffix_asset_id", 0x0005);
					utils::xml::Set(part, "usage", "1");
					utils::xml::Set(part, "creation_date", timestamp);
				}
				*/
				if (auto part = parts.append_child("part")) {
					utils::xml::Set(part, "is_flair", "0");
					utils::xml::Set(part, "cost", "100");
					utils::xml::Set(part, "creature_id", static_cast<uint64_t>(CreatureID::BlitzAlpha));
					utils::xml::Set(part, "id", "1");
					utils::xml::Set(part, "level", "1");
					utils::xml::Set(part, "market_status", "1");
					utils::xml::Set(part, "prefix_asset_id", utils::hash_id("_Generated/lootprefix1.lootprefix"));
					utils::xml::Set(part, "prefix_secondary_asset_id", utils::hash_id("_Generated/lootprefix2.lootprefix"));
					utils::xml::Set(part, "rarity", "1");
					utils::xml::Set(part, "reference_id", 1);
					utils::xml::Set(part, "rigblock_asset_id", utils::hash_id("_Generated/lootrigblock1.lootrigblock"));
					utils::xml::Set(part, "status", "1");
					utils::xml::Set(part, "suffix_asset_id", utils::hash_id("_Generated/lootsuffix1.lootsuffix"));
					utils::xml::Set(part, "usage", "1");
					utils::xml::Set(part, "creation_date", timestamp);
				}
			}
			
			add_common_keys(docResponse);
		}

		response.set(boost::beast::http::field::content_type, "text/xml");
		response.body() = utils::xml::ToString(document);
	}

	void API::game_inventory_vendorParts(HTTP::Session& session, HTTP::Response& response) {
		pugi::xml_document document;

		auto& request = session.get_request();

		const auto& transactionsString = request.uri.parameter("transactions");
		if (!transactionsString.empty()) {
			for (const auto& transaction : utils::explode_string(transactionsString, ';')) {
				// w = weapon, check for more later
				char type = transaction[0];
				std::cout << "Transaction: " << transaction << std::endl;

				int64_t index = utils::to_number<int64_t>(&transaction[1]);
				// Stuff
			}
		}

		if (auto docResponse = document.append_child("response")) {
			auto timestamp = utils::get_unix_time();
			if (auto parts = docResponse.append_child("parts")) {
				if (auto part = parts.append_child("part")) {
					utils::xml::Set(part, "is_flair", "0");
					utils::xml::Set(part, "cost", "100");
					utils::xml::Set(part, "creature_id", static_cast<uint64_t>(CreatureID::BlitzAlpha));
					utils::xml::Set(part, "id", "1");
					utils::xml::Set(part, "level", "1");
					utils::xml::Set(part, "market_status", "1");
					utils::xml::Set(part, "prefix_asset_id", utils::hash_id("_Generated/lootprefix1.lootprefix"));
					utils::xml::Set(part, "prefix_secondary_asset_id", utils::hash_id("_Generated/lootprefix2.lootprefix"));
					utils::xml::Set(part, "rarity", "1");
					utils::xml::Set(part, "reference_id", 1);
					utils::xml::Set(part, "rigblock_asset_id", utils::hash_id("_Generated/lootrigblock10001.lootrigblock"));
					utils::xml::Set(part, "status", "1");
					utils::xml::Set(part, "suffix_asset_id", utils::hash_id("_Generated/lootsuffix1.lootsuffix"));
					utils::xml::Set(part, "usage", "1");
					utils::xml::Set(part, "creation_date", timestamp);
				}
			}

			add_common_keys(docResponse);
		}

		response.set(boost::beast::http::field::content_type, "text/xml");
		response.body() = utils::xml::ToString(document);
	}

	void API::game_inventory_updatePartStatus(HTTP::Session& session, HTTP::Response& response) {
		auto& request = session.get_request();

		auto partIds = utils::explode_string(request.uri.parameter("part_id"), ',');
		auto statuses = utils::explode_string(request.uri.parameter("status"), ',');

		size_t len = std::min<size_t>(partIds.size(), statuses.size());
		if (len > 0) {
			const auto& user = session.get_user();

			auto& parts = user->get_parts();
			for (size_t i = 0; i < len; ++i) {
				uint32_t partIndex = utils::to_number<uint32_t>(partIds[i]);
				uint8_t  status    = utils::to_number<uint8_t>(statuses[i]);
				parts.data()[partIndex].SetStatus(status);
			}
		}

		pugi::xml_document document;
		if (auto docResponse = document.append_child("response")) {
			add_common_keys(docResponse);
		}

		response.set(boost::beast::http::field::content_type, "text/xml");
		response.body() = utils::xml::ToString(document);
	}

	void API::game_account_auth(HTTP::Session& session, HTTP::Response& response) {
		auto& request = session.get_request();

		auto key = request.uri.parameter("key");
		if (!key.empty()) {
			// key = auth_token::0
			auto keyData = utils::explode_string(key, "::");

			const auto& user = Game::UserManager::GetUserByAuthToken(keyData.front());
			if (user) {
				session.set_user(user);
			}
		}

		const auto& user = session.get_user();

		/*
			timestamp
				{TIMESTAMP}

			account
				tutorial_completed
				chain_progression
				creature_rewards
				current_game_id
				current_playgroup_id
				default_deck_pve_id
				default_deck_pvp_id
				level
				avatar_id
				id
				new_player_inventory
				new_player_progress
				cashout_bonus_time
				star_level
				unlock_catalysts
				unlock_diagonal_catalysts
				unlock_fuel_tanks
				unlock_inventory
				unlock_pve_decks
				unlock_pvp_decks
				unlock_stats
				unlock_inventory_identify
				unlock_editor_flair_slots
				upsell
				xp
				grant_all_access
				cap_level
				cap_progression

			creatures
				id
				name
				png_thumb_url
				noun_id
				version
				gear_score
				item_points

			decks
				name
				category
				id
				slot
				locked
				creatures
					{SAME_AS_CREATURES_BEFORE}

			feed
				items

			settings

			server_tuning
				itemstore_offer_period
				itemstore_current_expiration
				itemstore_cost_multiplier_basic
				itemstore_cost_multiplier_uncommon
				itemstore_cost_multiplier_rare
				itemstore_cost_multiplier_epic
				itemstore_cost_multiplier_unique
				itemstore_cost_multiplier_rareunique
				itemstore_cost_multiplier_epicunique
		*/

		pugi::xml_document document;
		if (auto docResponse = document.append_child("response")) {
			// Write "account" data
			if (user) {
				auto& account = user->get_account();

				auto newPlayerProgress = request.uri.parameteru("new_player_progress");
				if (newPlayerProgress != std::numeric_limits<uint64_t>::max()) {
					account.newPlayerProgress = newPlayerProgress;
				}

				account.WriteXml(docResponse);
			} else {
				Game::Account account;
				account.WriteXml(docResponse);
			}

			// Other
			pugi::xml_node creatures;
			if (request.uri.parameter("include_creatures") == "true") {
				if (user) {
					user->get_creatures().WriteXml(docResponse);
				} else {
					docResponse.append_child("creatures");
				}
			}

			if (request.uri.parameter("include_decks") == "true") {
				if (user) {
					user->get_squads().WriteXml(docResponse);
				} else {
					docResponse.append_child("decks");
				}
			}

			if (request.uri.parameter("include_feed") == "true") {
				if (user) {
					user->get_feed().WriteXml(docResponse);
				} else {
					docResponse.append_child("feed");
				}
			}

			if (request.uri.parameter("include_server_tuning") == "true") {
				if (auto server_tuning = docResponse.append_child("server_tuning")) {
					auto timestamp = utils::get_unix_time();
					utils::xml::Set(server_tuning, "itemstore_offer_period", timestamp);
					utils::xml::Set(server_tuning, "itemstore_current_expiration", timestamp + (3 * 60 * 60 * 1000));
					utils::xml::Set(server_tuning, "itemstore_cost_multiplier_basic", 1);
					utils::xml::Set(server_tuning, "itemstore_cost_multiplier_uncommon", 1.1);
					utils::xml::Set(server_tuning, "itemstore_cost_multiplier_rare", 1.2);
					utils::xml::Set(server_tuning, "itemstore_cost_multiplier_epic", 1.3);
					utils::xml::Set(server_tuning, "itemstore_cost_multiplier_unique", 1.4);
					utils::xml::Set(server_tuning, "itemstore_cost_multiplier_rareunique", 1.5);
					utils::xml::Set(server_tuning, "itemstore_cost_multiplier_epicunique", 1.6);
				}
			}

			if (request.uri.parameter("include_settings") == "true") {
				docResponse.append_child("settings");
			}

			if (request.uri.parameter("cookie") == "true") {
				std::string cookie;
				if (user) {
					cookie = user->get_auth_token();
				} else {
					cookie = "TESTING";
				}
				response.set(boost::beast::http::field::set_cookie, "token=" + cookie);
			}

			add_common_keys(docResponse);
		}

		response.set(boost::beast::http::field::content_type, "text/xml");
		response.body() = utils::xml::ToString(document);
	}

	void API::game_account_getAccount(HTTP::Session& session, HTTP::Response& response) {
		auto& request = session.get_request();

		const auto& user = session.get_user();

		pugi::xml_document document;
		if (auto docResponse = document.append_child("response")) {
			bool include_creatures = request.uri.parameter("include_creatures") == "true";
			bool include_decks     = request.uri.parameter("include_decks")     == "true";
			bool include_feed      = request.uri.parameter("include_feed")      == "true";
			bool include_stats     = request.uri.parameter("include_stats")     == "true";
			if (user) {
				user->get_account().WriteXml(docResponse);

				if (include_creatures) { user->get_creatures().WriteXml(docResponse); }
				if (include_decks)     { user->get_squads().WriteXml(docResponse);    }
				if (include_feed)      { user->get_feed().WriteXml(docResponse);      }
				if (include_stats) {
					auto stats = docResponse.append_child("stats");
					auto stat = stats.append_child("stat");
					utils::xml::Set(stat, "wins", 0);
				}
			} else {
				Game::Account account;
				account.WriteXml(docResponse);

				if (include_creatures) { docResponse.append_child("creatures"); }
				if (include_decks)     { docResponse.append_child("decks"); }
				if (include_feed)      { docResponse.append_child("feed"); }
				if (include_stats)     { docResponse.append_child("stats"); }
			}

			add_common_keys(docResponse);
		}

		response.set(boost::beast::http::field::content_type, "text/xml");
		response.body() = utils::xml::ToString(document);
	}

	void API::game_account_logout(HTTP::Session& session, HTTP::Response& response) {
		const auto& user = session.get_user();
		if (user) {
			user->Logout();
		}
	}

	void API::game_account_unlock(HTTP::Session& session, HTTP::Response& response) {
		auto& request = session.get_request();

		const auto& user = session.get_user();
		if (user) {
			uint32_t unlockId = request.uri.parameteru("unlock_id");
			user->UnlockUpgrade(unlockId);
		}

		game_account_getAccount(session, response);
	}

	void API::game_game_getGame(HTTP::Session& session, HTTP::Response& response) {
		pugi::xml_document document;

		auto docResponse = document.append_child("response");
		if (auto game = docResponse.append_child("game")) {
			utils::xml::Set(game, "game_id", "1");
			utils::xml::Set(game, "cashed_out", "0");
			utils::xml::Set(game, "finished", "0");
			utils::xml::Set(game, "starting_difficulty", "1");
			utils::xml::Set(game, "start", "1");
			/*
			utils::xml::Set(game, "rounds", "0");
			utils::xml::Set(game, "chain_id", "0");
			utils::xml::Set(game, "finish", "0");
			utils::xml::Set(game, "planet_id", "0");
			utils::xml::Set(game, "success", "0");
			*/
			if (auto players = game.append_child("players")) {
				if (auto player = players.append_child("player")) {
					/*
					utils::xml::Set(player, "deaths", "0");
					utils::xml::Set(player, "kills", "0");
					*/
					utils::xml::Set(player, "account_id", "1");
					utils::xml::Set(player, "result", "0");
					utils::xml::Set(player, "creature1_id", "1");
					utils::xml::Set(player, "creature1_version", "1");
					utils::xml::Set(player, "creature2_id", "0");
					utils::xml::Set(player, "creature2_version", "0");
					utils::xml::Set(player, "creature3_id", "0");
					utils::xml::Set(player, "creature3_version", "0");
				}
			}
		}

		add_common_keys(docResponse);

		response.set(boost::beast::http::field::content_type, "text/xml");
		response.body() = utils::xml::ToString(document);
	}

	void API::game_game_exitGame(HTTP::Session& session, HTTP::Response& response) {
		pugi::xml_document document;

		auto docResponse = document.append_child("response");
		add_common_keys(docResponse);

		response.set(boost::beast::http::field::content_type, "text/xml");
		response.body() = utils::xml::ToString(document);
	}

	void API::game_creature_resetCreature(HTTP::Session& session, HTTP::Response& response) {
		auto& request = session.get_request();

		pugi::xml_document document;

		auto docResponse = document.append_child("response");

		const auto& user = session.get_user();
		if (user) {
			Creature* creature = user->GetCreatureById(request.uri.parameteru("id"));
			if (creature) {
				creature->WriteXml(docResponse);
			} else {
				docResponse.append_child("creature");
			}
		} else {
			docResponse.append_child("creature");
		}

		add_common_keys(docResponse);

		response.set(boost::beast::http::field::content_type, "text/xml");
		response.body() = utils::xml::ToString(document);
	}

	void API::game_creature_unlockCreature(HTTP::Session& session, HTTP::Response& response) {
		auto& request = session.get_request();

		uint32_t templateId = request.uri.parameteru("template_id");

		const auto& user = session.get_user();
		if (user) {
			user->UnlockCreature(templateId);
		}

		pugi::xml_document document;

		auto docResponse = document.append_child("response");
		utils::xml::Set(docResponse, "creature_id", templateId);

		add_common_keys(docResponse);

		response.set(boost::beast::http::field::content_type, "text/xml");
		response.body() = utils::xml::ToString(document);
	}

	void API::game_creature_getCreature(HTTP::Session& session, HTTP::Response& response) {
		/*
			name_locale_id
			text_locale_id
			name
			type_a

			if not template {
				creator_id
			}

			weapon_min_damage
			weapon_max_damage
			gear_score (default: 0)
			class
			stats_template_ability
				example {
					full_string = item0;item1;itemN
					item = a!b,value
				}

			if not template {
				stats
				stats_template_ability_keyvalues
				stats_ability_keyvalues
			} else {
				stats_template
				stats_template_ability_keyvalues
			}

			if not template {
				parts
					part
			}

			creature_parts
			ability_passive
			ability_basic
			ability_random
			ability_special_1
			ability_special_2
			ability
				id

			if not template {
				png_large_url
				png_thumb_url
			}
		*/
		/*
		auto& request = session.get_request();

		uint32_t templateId = request.uri.parameteru("template_id");

		const auto& user = session.get_user();
		if (user) {
			user->UnlockCreature(templateId);
		}

		pugi::xml_document document;

		auto docResponse = document.append_child("response");
		utils::xml::Set(docResponse, "creature_id", templateId);

		add_common_keys(docResponse);

		response.set(boost::beast::http::field::content_type, "text/xml");
		response.body() = utils::xml::ToString(document);
		*/
	}

	/*
/game/api?version=1&token=cookie
cost = 0
gear = 0.000
id = 749013658
large = iVBORw0KGgoAAAANSUhEUgAAAQAAAAEACAYAAABccqhmAAAgAElEQVR4nOy9Z7Bl13WY+e1wwk0v
large_crc = 692908162
method = api.creature.updateCreature
parts = 117957934
points = 300.000
stats = STR,14,0;DEX,13,0;MIND,23,0;HLTH,100,70;MANA,125,23;PDEF,50,78;EDEF,150,138;CRTR,50,52
stats_ability_keyvalues = 885660025!minDamage,5;885660025!maxDamage,8;885660025!percentToHeal,20;1152331895!duration,20;1152331895!spawnMax,2;424126604!radius,8;424126604!healing,5;424126604!duration,6;424126604!minHealing,21;424126604!maxHealing,32;1577880566!Enrage.damage,9;1577880566!Enrage.duration,30;1577880566!Enrage.healing,35;1829107826!diameter,12;1829107826!damage,6;1829107826!duration,10;1829107826!speedDebuff,75
thumb = iVBORw0KGgoAAAANSUhEUgAAAIAAAACACAYAAADDPmHLAAAgAElEQVR4nGy8adRm11kduJ9zh3f6
thumb_crc = 1921048798
token = ABCDEFGHIJKLMNOPQRSTUVWXYZ
version = 1
	*/

	void API::survey_survey_getSurveyList(HTTP::Session& session, HTTP::Response& response) {
		pugi::xml_document document;

		auto docResponse = document.append_child("response");
		if (auto surveys = docResponse.append_child("surveys")) {
			// Empty
		}

		add_common_keys(docResponse);

		response.set(boost::beast::http::field::content_type, "text/xml");
		response.body() = utils::xml::ToString(document);
	}

	void API::add_broadcasts(pugi::xml_node& node) {
		if (auto broadcasts = node.append_child("broadcasts")) {
			/*
			if (auto broadcast = broadcasts.append_child("broadcast")) {
				utils::xml::Set(broadcast, "id", "0");
				utils::xml::Set(broadcast, "start", "0");
				utils::xml::Set(broadcast, "type", "0");
				utils::xml::Set(broadcast, "message", "Hello World!");
				if (auto tokens = broadcast.append_child("tokens")) {
				}
			}
			*/
		}
	}

	void API::add_common_keys(pugi::xml_node& node) {
		utils::xml::Set(node, "stat", "ok");
		utils::xml::Set(node, "version", mVersion);
		utils::xml::Set(node, "timestamp", std::to_string(utils::get_unix_time()));
		utils::xml::Set(node, "exectime", std::to_string(++mPacketId));
	}

	void API::add_common_keys(rapidjson::Document& document) {
		/*
		obj["stat"] = 'ok'
		obj["version"] = self.server.gameVersion
		obj["timestamp"] = self.timestamp()
		obj["exectime"] = self.exectime()
		*/
	}
}
