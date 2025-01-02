
// Include
#include "api.h"
#include "config.h"

#include "http/session.h"
#include "http/router.h"
#include "http/uri.h"
#include "http/multipart.h"

#include "sporenet/instance.h"
#include "sporenet/user.h"
#include "sporenet/creature.h"
#include "sporenet/vendor.h"

#include "utils/functions.h"

#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <boost/beast/version.hpp>

#include <base64.h>
#include <lodepng.h>

#include <iostream>
#include <iomanip>
#include <filesystem>
#include <chrono>

/*
	A bunch of stuff used in the client

		#define BUDDYAPI_MEMID          ('budd')
		#define CLUBAPI_MEMID           ('club')
		#define HLBUDAPI_MEMID          ('hbud')
		#define XBFRIENDS_MEMID         ('xbfr')
		#define XNFRIENDS_MEMID         ('xnfr')

		#define PCISP_MEMID             ('pcip')

		#define COMMSER_MEMID           ('cser')
		#define COMMSRP_MEMID           ('csrp')
		#define COMMTCP_MEMID           ('ctcp')
		#define COMMUDP_MEMID           ('cudp')

		#define DIRTYLSP_MEMID          ('dlsp')
		#define DIRTYSESSMGR_MEMID      ('dsmg')
		#define SOCKET_MEMID            ('dsoc')
		#define RPC_MEMID               ('drpc')
		#define NETCONN_MEMID           ('ncon')

		#define CONNAPI_MEMID           ('conn')
		#define NETGAMEDIST_MEMID       ('ngdt')
		#define NETGAMEDISTSERV_MEMID   ('ngds')
		#define NETGAMELINK_MEMID       ('nglk')
		#define NETGAMEUTIL_MEMID       ('ngut')

		#define DIRTYGRAPH_MEMID        ('dgph')
		#define DIRTYJPG_MEMID          ('djpg')
		#define DIRTYPNG_MEMID          ('dpng')

		#define FAVORITES_MEMID         ('favr')
		#define GAMECONFIGAPI_MEMID     ('gcfg')
		#define GAMEMANAGER_MEMID       ('gmgr')
		#define USERSETMANAGER_MEMID    ('umgr')
		#define LEAGAPI_MEMID           ('leag')
		#define NEW_TOURNEY_MEMID       ('ntou')
		#define ONLINE_LEAGAPI_MEMID    ('lolg')
		#define LOBBYAPI_MEMID          ('lapi')
		#define LOBBYAPIASYNC_MEMID     ('lasc')
		#define LOBBYAPILIST_MEMID      ('llst')
		#define LOBBYCHAL_MEMID         ('lchl')
		#define LOBBYFINDUSER_MEMID     ('lfus')
		#define LOBBYGLUE_MEMID         ('lglu')
		#define BUDDYTICKERGLUE_MEMID   ('btgl')
		#define LOBBYLOCALIZE_MEMID     ('lloc')
		#define LOBBYLOGGER_MEMID       ('llgr')
		#define LOBBYLOGIN_MEMID        ('llgn')
		#define MSGLOG_MEMID            ('lmlg')
		#define LOBBYRANK_MEMID         ('lrnk')
		#define LOBBYREG_MEMID          ('lreg')
		#define LOBBYSETTING_MEMID      ('lset')
		#define LOBBYSTATBOOK_MEMID     ('lsta')
		#define BLAZESTATS_MEMID        ('bzst')
		#define LOBBYROOMLIST_MEMID     ('lrml')
		#define TOURNEYAPI_MEMID        ('tour')
		#define LOBBYAPIPLAT_MEMID      ('lapp')

		#define LOBBYLAN_MEMID          ('llan')
		#define PORTTESTER_MEMID        ('ptst')
		#define TELEMETRYAPI_MEMID      ('telm')
		#define TICKERAPI_MEMID         ('tick')

		#define PROTOADVT_MEMID         ('padv')
		#define PROTOARIES_MEMID        ('pari')
		#define PROTOHTTP_MEMID         ('phtp')
		#define HTTPMGR_MEMID           ('hmgr')
		#define PROTOMANGLE_MEMID       ('pmgl')
		#define PROTONAME_MEMID         ('pnam')
		#define PROTOPING_MEMID         ('ppng')
		#define PINGMGR_MEMID           ('lpmg')
		#define PROTOSSL_MEMID          ('pssl')
		#define PROTOSTREAM_MEMID       ('pstr')
		#define PROTOTUNNEL_MEMID       ('ptun')
		#define PROTOUDP_MEMID          ('pudp')
		#define PROTOUPNP_MEMID         ('pupp')
		#define PROTOFILTER_MEMID       ('pflt')

		#define DISPLIST_MEMID          ('ldsp')
		#define HASHER_MEMID            ('lhsh')
		#define LOBBYSORT_MEMID         ('lsor')

		#define QOSAPI_MEMID            ('dqos')

		#define VOIP_MEMID              ('voip')

		#define VOIPTUNNEL_MEMID        ('vtun')

		#define DIGOBJAPI_MEMID         ('dobj')
		#define LOCKERAPI_MEMID         ('lckr')
		#define NETRSRC_MEMID           ('nrsc')
		#define WEBLOG_MEMID            ('wlog')
		#define WEBOFFER_MEMID          ('webo')

		#define XMLLIST_MEMID           ('xmll')

		#define NINSOC_MEMID            ('nsoc')
		#define NINDWC_MEMID            ('ndwc')
*/

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

// temporary
const std::string currentTheme = "classic";

// XML, TODO: XMLResponse class?
auto create_xml_response() {
	std::pair<pugi::xml_document, pugi::xml_node> data;

	auto declaration = data.first.append_child(pugi::node_declaration);
	declaration.append_attribute("version").set_value("1.0");
	declaration.append_attribute("encoding").set_value("UTF-8");

	data.second = data.first.append_child("response");
	return data;
}

struct xml_string_writer : pugi::xml_writer {
	std::string result;

	void write(const void* data, size_t size) override {
		result.append(static_cast<const char*>(data), size);
	}
};

auto parse_cookies(HTTP::Request& request) {
	std::map<std::string, std::string> data;

	auto cookies = request.data[boost::beast::http::field::cookie];
	if (cookies.empty()) {
		return data;
	}

	auto cookieList = utils::explode_string(';' + cookies.to_string(), ';');
	for (const auto& cookie : cookieList) {
		auto cookieData = utils::explode_string(cookie, '=', 1);
		if (cookieData.size() == 2) {
			data.emplace(cookieData[0], cookieData[1]);
		}
	}

	return data;
}

// Game
namespace Game {
	constexpr std::string_view skipLauncherScript = R"(
<!DOCTYPE html PUBLIC "-//IETF//DTD HTML 2.0//EN">
<html>
	<head>
		<script type="text/javascript">
			window.onload = function() {
				// Client.install(2);
				Client.playCurrentApp();
			}
		</script>
	</head>
	<body>
	</body>
</html>
)";

	constexpr std::string_view recapClientScript = R"(
<script>
	var ReCapClient = {};
	ReCapClient.getRequest = function(url, callback) {
		var xmlHttp = new XMLHttpRequest(); 
		xmlHttp.onload = function() {
			callback(xmlHttp.responseText);
		}
		xmlHttp.open("GET", url, true);
		xmlHttp.send(null);
	};
	ReCapClient.request = function(name, params, callback) {
		ReCapClient.getRequest("http://{{host}}/recap/api?method=" + name + (params === undefined ? "" : ("&" + params)), callback);
	};
</script>
)";

	// API
	API::API(const std::string& version) : mVersion(version) {
		// Empty
	}

	void API::setup() {
		const auto& router = GetApp().get_http_server()->get_router();

		// Routing
		router->add("/api", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [](HTTP::Session& session, HTTP::Response& response) {
			std::cout << "Got API route." << std::endl;
		});

		// Telemetry
		router->add("/telemetryevent", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [](HTTP::Session& session, HTTP::Response& response) {
			std::cout << "Got telemetry event." << std::endl;
		});

		// ReCap
		router->add("/recap/api", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			const auto& request = session.get_request();

			auto method = request.uri.parameter("method");
			if (method == "api.launcher.setTheme") {
				recap_launcher_setTheme(session, response);
			} else if (method == "api.launcher.listThemes") {
				recap_launcher_listThemes(session, response);
			} else if (method == "api.game.registration") {
				recap_game_registration(session, response);
			} else if (method == "api.game.log") {
				recap_game_log(session, response);
			} else if (method == "api.panel.listUsers") {
				recap_panel_listUsers(session, response);
			} else if (method == "api.panel.getUserInfo") {
				recap_panel_getUserInfo(session, response);
			} else if (method == "api.panel.setUserInfo") {
				recap_panel_setUserInfo(session, response);
			} else {
				response.result() = boost::beast::http::status::internal_server_error;
			}
		});

		// Launcher
		router->add("/bootstrap/api", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			auto& request = session.get_request();

			auto version = request.uri.parameter("version");
			auto build = request.uri.parameter("build");
			auto method = request.uri.parameter("method");

			if (version.empty()) { version = "1"; }
			if (build.empty()) { build = "5.3.0.127"; }
			if (method.empty()) { method = "api.config.getConfigs"; }

			std::cout << method << std::endl;
			if (method.find("api.config.") == 0) {
				if (method == "api.config.getConfigs") {
					bootstrap_config_getConfig(session, response);
				}
			}
		});

		router->add("/bootstrap/launcher/", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			auto& request = session.get_request();

			auto version = request.uri.parameter("version");
			if (Config::GetBool(CONFIG_SKIP_LAUNCHER)) {
				response.set(boost::beast::http::field::content_type, "text/html");
				response.body() = skipLauncherScript;
			} else {
				std::string path = std::format(
					"{}www/{}{}/index.html",
					Config::Get(CONFIG_STORAGE_PATH),
					Config::Get(CONFIG_DARKSPORE_LAUNCHER_THEMES_PATH),
					currentTheme
				);

				std::string client_script(recapClientScript);
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

			std::string path = std::format(
				"{}www/{}{}/images/{}",
				Config::Get(CONFIG_STORAGE_PATH),
				Config::Get(CONFIG_DARKSPORE_LAUNCHER_THEMES_PATH),
				currentTheme,
				resource.substr(resource.rfind('/') + 1)
			);

			response.version() |= 0x1000'0000;
			response.body() = std::move(path);
		});

		router->add("/bootstrap/launcher/notes", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			std::string path = Config::Get(CONFIG_STORAGE_PATH) +
				"www/" +
				Config::Get(CONFIG_DARKSPORE_LAUNCHER_NOTES_PATH);

			std::string file_data = utils::get_file_text(path);
			utils::string_replace(file_data, "{{recap-version}}", "0.1");
			utils::string_replace(file_data, "{{version-lock}}", Config::GetBool(CONFIG_VERSION_LOCKED) ? "5.3.0.127" : "no");
			utils::string_replace(file_data, "{{game-mode}}", Config::GetBool(CONFIG_SINGLEPLAYER_ONLY) ? "singleplayer" : "multiplayer");
			utils::string_replace(file_data, "{{display-latest-version}}", "none");
			utils::string_replace(file_data, "{{latest-version}}", "yes");

			response.set(boost::beast::http::field::content_type, "text/html");
			response.body() = std::move(file_data);
		});

		// Game
		router->add("/game/api", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			// TODO: fix all of these things, its so ugly
			auto& request = session.get_request();

			if (request.data.method() == boost::beast::http::verb::post) {
				// TODO: Fetch boundary later from request.data[boost::beast::http::field::content_type]
				
				HTTP::Multipart multipart;
				multipart.parse(request);

				for (const auto&[name, value] : multipart) {
					request.uri.set_parameter(name, value);
				}
			}

			// TODO: cookie handler
			auto cookies = request.data[boost::beast::http::field::cookie];
			if (!cookies.empty()) {
				auto cookieMap = parse_cookies(request);
				for (const auto& [name, value] : cookieMap) {
					auto it = request.uri.find(name);
					if (it != request.uri.end()) {
						if (it->second == "cookie") {
							it->second = value;
						}
					}
				}
			}

			for (auto& [name, value] : request.uri) {
				std::cout << name << " = " << value << std::endl;
			}
			std::cout << std::endl;

			auto version = request.uri.parameter("version");
			auto build = request.uri.parameter("build");
			auto token = request.uri.parameter("token");

			if (!token.empty()) {
				const auto& user = SporeNet::Get().GetUserManager().GetUserByAuthToken(token);
				if (user) {
					session.set_user(user);
				}
				response.set(boost::beast::http::field::set_cookie, "token=" + token);
			}

			auto method = request.uri.parameter("method");
			if (method.empty()) {
				if (token.empty()) {
					method = "api.account.auth";
				} else {
					method = "api.account.getAccount";
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
			} else if (method == "api.inventory.vendorParts") {
				game_inventory_vendorParts(session, response);
			} else if (method == "api.inventory.updatePartStatus") {
				game_inventory_updatePartStatus(session, response);
			} else if (method == "api.account.auth") {
				game_account_auth(session, response);
			} else if (method == "api.account.getAccount") {
				game_account_getAccount(session, response);
			} else if (method == "api.account.logout") {
				game_account_logout(session, response);
			} else if (method == "api.account.unlock") {
				game_account_unlock(session, response);
			} else if (method == "api.account.setSettings") {
				game_account_setSettings(session, response);
			} else if (method == "api.account.searchAccounts") {
				game_account_searchAccounts(session, response);
			} else if (method == "api.game.getGame") {
				game_game_getGame(session, response);
			} else if (method == "api.game.getRandomGame") {
				game_game_getRandomGame(session, response);
			} else if (method == "api.game.exitGame") {
				game_game_exitGame(session, response);
			} else if (method == "api.creature.resetCreature") {
				game_creature_resetCreature(session, response);
			} else if (method == "api.creature.unlockCreature") {
				game_creature_unlockCreature(session, response);
			} else if (method == "api.creature.getCreature") {
				game_creature_getCreature(session, response);
			} else if (method == "api.creature.getTemplate") {
				game_creature_getTemplate(session, response);
			} else if (method == "api.creature.updateCreature") {
				game_creature_updateCreature(session, response);
			} else if (method == "api.deck.updateDecks") {
				game_deck_updateDecks(session, response);
			} else if (method == "api.leaderboard.getLeaderboard") {
				game_leaderboard_getLeaderboard(session, response);
			} else if (method == "api.game.log") {
				recap_game_log(session, response);
			} else {
				std::cout << "Undefined /game/api method: " << method << std::endl;
				for (const auto& [name, value] : request.uri) {
					std::cout << name << " = " << value << std::endl;
				}
				std::cout << std::endl;
				empty_xml_response(response);
			}
		});

		// Png
		router->add("/template_png/([a-zA-Z0-9_.]+)", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			const auto& request = session.get_request();

			std::string storagePath = Config::Get(CONFIG_STORAGE_PATH);
			std::string path = storagePath + request.uri.resource();
			if (!std::filesystem::exists(path)) {
				path = storagePath + "default.png";
			}

			response.version() |= 0x1000'0000;
			response.body() = std::move(path);
		});

		router->add("/creature_png/([a-zA-Z0-9_.]+)", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			const auto& request = session.get_request();

			std::string storagePath = Config::Get(CONFIG_STORAGE_PATH);
			std::string path = storagePath + request.uri.resource();
			if (!std::filesystem::exists(path)) {
				path = storagePath + "default.png";
			}

			response.version() |= 0x1000'0000;
			response.body() = std::move(path);
		});

		router->add("/game/service/png", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			const auto& request = session.get_request();

			std::string storagePath = Config::Get(CONFIG_STORAGE_PATH);
			std::string path;
			if (auto account_id = request.uri.parameter<int64_t>("account_id"); account_id != 0) {
				/*
				std::string path = std::format(
					"{}www/{}{}/index.html",
					Config::Get(CONFIG_STORAGE_PATH),
					Config::Get(CONFIG_DARKSPORE_LAUNCHER_THEMES_PATH),
					currentTheme
				);
				*/
			} else {
				auto template_id = request.uri.parameter<uint32_t>("template_id");
				auto size = request.uri.parameter("size");

				std::stringstream stream;
				stream << storagePath;
				stream << "template_png/";
				stream << size << "/";
				stream << "0x" << std::setfill('0') << std::setw(8) << std::hex << template_id << std::dec << ".png";

				path = stream.str();
			}

			if (!std::filesystem::exists(path)) {
				path = storagePath + "default.png";
			}

			response.version() |= 0x1000'0000;
			response.body() = std::move(path);
		});

		// Icon
		router->add("/favicon.ico", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			std::string storagePath = Config::Get(CONFIG_STORAGE_PATH);
			std::string path = storagePath + "www/favicon.ico";

			response.version() |= 0x1000'0000;
			response.body() = std::move(path);
		});

		// Survey
		router->add("/survey/api", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			auto& request = session.get_request();

			auto version = request.uri.parameter("version");
			auto method = request.uri.parameter("method");

			if (method == "api.survey.getSurveyList") {
				survey_survey_getSurveyList(session, response);
			} else {
				empty_xml_response(response);
			}
		});

		// Web
		router->add("/web/sporelabsgame/announceen", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			response.set(boost::beast::http::field::content_type, "text/html");
			response.body() = "<html><head><title>x</title></head><body>Announces</body></html>";
		});

		router->add("/web/sporelabsgame/manualen", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			response.set(boost::beast::http::field::content_type, "text/html");
			response.body() = "<html><head><title>Manual test 123</title></head><body>Why won't this game work?</body></html>";
		});

		router->add("/web/sporelabsgame/persona", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			response.set(boost::beast::http::field::content_type, "text/html");
			response.body() = "";
		});

		// QOS
		router->add("/qos/qos", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			/* possible structures
				<qos>
					<numprobes>0</numprobes> // 109Ch
					<probesize>1</probesize> // 1094h
					<qosport>0</qosport> // 11Ch
					<requestid>0</requestid> // 10A8h
					<reqsecret>1</reqsecret> // 10ACh
				</qos>
			*/

			const auto& request = session.get_request();

			auto version = request.uri.parameter<int32_t>("vers");
			auto type = request.uri.parameter<int32_t>("qtyp");
			auto port = request.uri.parameter<uint16_t>("prpt");

			if (type == 1 || type == 2) {
				auto [document, docResponse] = create_xml_response();
				docResponse.set_name("qos");

				utils::xml_add_text_node(docResponse, "numprobes", 2);
				utils::xml_add_text_node(docResponse, "probesize", 8);
				utils::xml_add_text_node(docResponse, "qosport", port);
				utils::xml_add_text_node(docResponse, "requestid", type);
				utils::xml_add_text_node(docResponse, "reqsecret", 0x1337);

				set_response_body(response, document, boost::beast::http::status::ok);

				// Try to connect to port via udp
				{

					// boost::asio::ip::udp::socket s();
				}
			} else {
				response.set(boost::beast::http::field::content_type, "text/plain");
				response.body() = "";
			}
		});

		router->add("/qos/firewall", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			/* possible structures
				<firewall>
					<numinterfaces>number</numinterfaces> // 10B0h

					<ips>
						<ips>127.0.0.1</ips>
					</ips>

					<ports>
						<ports>8080</ports>
					</ports>

					<requestid>0</requestid> // 10C4h
					<reqsecret>1</reqsecret> // 10C8h
				</firewall>
			*/

			const auto& request = session.get_request();

			auto interfaceCount = request.uri.parameter<uint32_t>("nint");

			auto [document, docResponse] = create_xml_response();
			docResponse.set_name("firewall");

			// Number of interfaces
			utils::xml_add_text_node(docResponse, "numinterfaces", interfaceCount);

			// Ips
			auto ipsNode = docResponse.append_child("ips");
			for (uint32_t i = 0; i < interfaceCount; ++i) {
				utils::xml_add_text_node(ipsNode, "ips", boost::asio::ip::address_v4::from_string("127.0.0.1").to_ulong());
			}

			// Ports
			auto portsNode = docResponse.append_child("ports");
			for (uint32_t i = 0; i < interfaceCount; ++i) {
				utils::xml_add_text_node(portsNode, "ports", 3659);
			}

			// Request data
			utils::xml_add_text_node(docResponse, "requestid", 1);
			utils::xml_add_text_node(docResponse, "reqsecret", 0x1337);

			set_response_body(response, document, boost::beast::http::status::ok);
		});

		router->add("/qos/firetype", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			/* possible structures
				<firetype>0</firetype> // 174h
			*/

			const auto& request = session.get_request();

			auto requestId = request.uri.parameter<uint32_t>("rqid");
			auto requestSecret = request.uri.parameter<uint32_t>("rqsc");
			auto inAddress = request.uri.parameter<uint32_t>("inip");
			auto inPort = request.uri.parameter<uint16_t>("inpt");

			std::cout << "Firetype: ";
			std::cout << "ip(" << boost::asio::ip::address_v4(inAddress).to_string() << "); ";
			std::cout << "port(" << inPort << "); ";
			std::cout << "request_id(" << requestId << "); ";
			std::cout << "request_secret(" << requestSecret << "); ";
			std::cout << std::endl;

			auto [document, docResponse] = create_xml_response();
			docResponse.set_name("firetype");

			utils::xml_add_text_node(docResponse, "firetype", static_cast<uint32_t>(Blaze::NatType::Open) + 1);

			set_response_body(response, document, boost::beast::http::status::ok);
		});

		// Ingame Webviews
		router->add("/ingame/([/a-zA-Z0-9\\-_.]*)", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			std::string path = Config::Get(CONFIG_STORAGE_PATH) + "www/" + session.get_request().uri.resource();
			/*
			utils::string_replace(file_data, "{{isDev}}", "true");
			utils::string_replace(file_data, "{{recap-version}}", "0.1");
			utils::string_replace(file_data, "{{host}}", Game::Config::Get(Game::CONFIG_SERVER_HOST));
			utils::string_replace(file_data, "{{game-mode}}", Game::Config::GetBool(Game::CONFIG_SINGLEPLAYER_ONLY) ? "singleplayer" : "multiplayer");
			*/
			response.version() |= 0x1000'0000;
			response.body() = std::move(path);
		});

		router->add("/web/sporelabs/alerts", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			// response.body() = utils::EAWebKit::loadFile("www/ingame/announce.html");
		});

		router->add("/web/sporelabsgame/announceen", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			// response.body() = utils::EAWebKit::loadFile("www/ingame/announce.html");
		});

		router->add("/web/sporelabsgame/register", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			// response.body() = utils::EAWebKit::loadFile("www/ingame/register.html");
		});

		router->add("/web/sporelabsgame/persona", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			// response.body() = utils::EAWebKit::loadFile("www/ingame/persona.html");
		});

		router->add("/web/sporelabs/resetpassword", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			// response.body() = utils::EAWebKit::loadFile("www/ingame/resetpassword.html");
		});

		router->add("/web/sporelabsgame/([/a-zA-Z0-9\\-_.]*)", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			// response.body() = utils::EAWebKit::loadFile("www/ingame" + session.get_request().uri.resource().substr(18));
		});

		router->add("/web/sporelabs/([/a-zA-Z0-9\\-_.]*)", { boost::beast::http::verb::get, boost::beast::http::verb::post }, [this](HTTP::Session& session, HTTP::Response& response) {
			// response.body() = utils::EAWebKit::loadFile("www/ingame" + session.get_request().uri.resource().substr(14));
		});
	}

	void API::empty_xml_response(HTTP::Response& response) {
		auto [document, docResponse] = create_xml_response();
		add_common_keys(docResponse);
		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::empty_json_response(HTTP::Response& response) {
		response.set(boost::beast::http::field::content_type, "application/json");
	}

	void API::recap_launcher_setTheme(HTTP::Session& session, HTTP::Response& response) {
		/*
		theme = requestUtils.get(request, 'theme', str)
		server.setActiveTheme(theme)
		*/
		rapidjson::StringBuffer buffer;
		buffer.Clear();

		rapidjson::Document document;

		// stat
		document.AddMember(rapidjson::Value("stat"), rapidjson::Value("ok"), document.GetAllocator());

		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);

		response.set(boost::beast::http::field::content_type, "application/json");
		response.body() = buffer.GetString();
	}

	void API::recap_launcher_listThemes(HTTP::Session& session, HTTP::Response& response) {
		rapidjson::StringBuffer buffer;
		buffer.Clear();

		rapidjson::Document document;
		rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

		// stat
		document.AddMember(rapidjson::Value("stat"), rapidjson::Value("ok"), allocator);
		
		// themes
		{
			std::string themesFolderPath = Config::Get(CONFIG_STORAGE_PATH) +
				"www/" + Config::Get(CONFIG_DARKSPORE_LAUNCHER_THEMES_PATH);

			rapidjson::Value value(rapidjson::kArrayType);
			for (const auto& entry : std::filesystem::directory_iterator(themesFolderPath)) {
				if (entry.is_directory()) {
					value.PushBack(rapidjson::Value(entry.path().filename().string(), allocator), allocator);
				}
			}

			document.AddMember(rapidjson::Value("themes"), value, allocator);
		}

		// selectedTheme
		document.AddMember(rapidjson::Value("selectedTheme"), rapidjson::Value(currentTheme, allocator), allocator);

		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);

		response.set(boost::beast::http::field::content_type, "application/json");
		response.body() = buffer.GetString();
	}

	void API::recap_game_registration(HTTP::Session& session, HTTP::Response& response) {
		/*
		auto& request = session.get_request();
		auto name = request.uri.parameter("name");
		auto mail = request.uri.parameter("mail");
		auto pass = request.uri.parameter("pass");
		auto avatar = request.uri.parameteri("avatar");

		const auto& user = Repository::Users::CreateUserWithNameMailAndPassword(name, mail, pass);
		rapidjson::Document document = utils::json::NewDocumentObject();
		if (user == NULL) {
			utils::json::Set(document, "stat", "error");
			response.set(boost::beast::http::field::content_type, "application/json");
			response.body() = utils::json::ToString(document);
			return;
		}

		utils::json::Set(document, "stat", "ok");

		auto actualPartsSize = Repository::CreatureParts::ListAll().size();
		auto parts = Repository::Parts::ListAll();
		uint64_t index = 1;
		for (auto& part : parts) {
			Repository::CreatureParts::Add(std::make_shared<Game::CreaturePart>(actualPartsSize + index++, part->rigblock_asset_id, user->get_account().id));
		}
		Repository::CreatureParts::Save();

		// TODO: Unlocking all creatures from start to test; remove that in the future
		std::vector<Repository::CreatureTemplatePtr> templates = Repository::CreatureTemplates::ListAll();
		user->get_account().creatureRewards = templates.size();
		for (auto& templateCreature : templates) {
			user->UnlockCreature(templateCreature->id);
		}

		// TODO: Unlocking everything from start to test; remove that in the future
		SporeNet::Account& account = user->get_account();
		account.tutorialCompleted = false;
		account.chainProgression = 24;
		account.creatureRewards = 100;
		account.currentGameId = 1;
		account.currentPlaygroupId = 1;
		account.defaultDeckPveId = 1;
		account.defaultDeckPvpId = 1;
		account.level = 100;
		account.avatarId = avatar;
		account.dna = 10000000;
		account.newPlayerInventory = 1;
		account.newPlayerProgress = 9500;
		account.cashoutBonusTime = 1;
		account.starLevel = 10;
		account.unlockCatalysts = 1;
		account.unlockDiagonalCatalysts = 1;
		account.unlockFuelTanks = 1;
		account.unlockInventory = 1;
		account.unlockPveDecks = 2;
		account.unlockPvpDecks = 1;
		account.unlockStats = 1;
		account.unlockInventoryIdentify = 2500;
		account.unlockEditorFlairSlots = 1;
		account.upsell = 1;
		account.xp = 10000;
		account.grantAllAccess = true;
		account.grantOnlineAccess = true;

		for (uint16_t squadSlot = 1; squadSlot <= 3; squadSlot++) {
			uint16_t templateId = squadSlot - 1;
			Squad squad1;
			squad1.id = squadSlot;
			squad1.slot = squadSlot;
			squad1.name = "Slot " + std::to_string(squadSlot);
			squad1.locked = false;
			squad1.creatures.Add(templates[templateId]->id);
			user->get_squads().data().push_back(squad1);
		}

		Repository::Users::SaveUser(user);

		response.set(boost::beast::http::field::content_type, "application/json");
		response.body() = utils::json::ToString(document);
		*/
	}

	void API::recap_game_log(HTTP::Session& session, HTTP::Response& response) {
		const auto& request = session.get_request();
		/*
		auto postBody = request.data.body();
		std::cout << "js.console.log: " << postBody << std::endl;
		*/
		std::cout << "js.console.log: " << request.uri.parameter("message") << std::endl;
		// logger::log(postBody);
	}

	void API::recap_panel_listUsers(HTTP::Session& session, HTTP::Response& response) {
		/*
		rapidjson::Document document = utils::json::NewDocumentObject();

		rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

		// stat
		utils::json::Set(document, "stat", "ok");

		const auto users = Repository::Users::GetAllUserNames();
		const auto loggedUsers = Repository::Users::GetLoggedUserNames();
		rapidjson::Value value = utils::json::NewArray();
		for (const auto& entry : users) {
			bool isLogged = std::find(loggedUsers.begin(), loggedUsers.end(), entry) != loggedUsers.end();

			rapidjson::Value object = utils::json::NewObject();
			utils::json::Set(object, "email", entry, allocator);
			utils::json::Set(object, "logged", isLogged, allocator);
			utils::json::Add(value, object, allocator);
		}
		utils::json::Set(document, "users", value);

		response.set(boost::beast::http::field::content_type, "application/json");
		response.body() = utils::json::ToString(document);
		*/
	}

	void API::recap_panel_getUserInfo(HTTP::Session& session, HTTP::Response& response) {
		/*
		auto& request = session.get_request();
		auto mail = request.uri.parameter("mail");

		const auto& user = Repository::Users::GetUserByEmail(mail, false);

		rapidjson::Document document = utils::json::NewDocumentObject();

		rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

		if (user == NULL) {
			// stat
			utils::json::Set(document, "stat", "error");
		} else {
			// stat
			rapidjson::Value users = user->ToJson(allocator);
			utils::json::Set(document, "stat", "ok");
			utils::json::Set(document, "user", users);
		}

		response.set(boost::beast::http::field::content_type, "application/json");
		response.body() = utils::json::ToString(document);
		*/
	}

	void API::recap_panel_setUserInfo(HTTP::Session& session, HTTP::Response& response) {
		/*
		auto& request = session.get_request();
		auto mail = request.uri.parameter("mail");
		auto userJsonString = request.data.body();

		logger::info(userJsonString);
		rapidjson::Document userJson = utils::json::Parse(userJsonString);

		const auto& user = Repository::Users::GetUserByEmail(mail, false);

		rapidjson::Document document = utils::json::NewDocumentObject();

		rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

		if (user == NULL) {
			// stat
			utils::json::Set(document, "stat", "error");
		} else {
			user->FromJson(userJson);
			Repository::Users::SaveUser(user);

			// stat
			utils::json::Set(document, "stat", "ok");
		}

		response.set(boost::beast::http::field::content_type, "application/json");
		response.body() = utils::json::ToString(document);
		*/
	}

	void API::bootstrap_config_getConfig(HTTP::Session& session, HTTP::Response& response) {
		const auto& request = session.get_request();
		const auto& host = Config::Get(CONFIG_SERVER_HOST);

		auto [document, docResponse] = create_xml_response();
		add_common_keys(docResponse);

		if (auto configs = docResponse.append_child("configs")) {
			if (auto config = configs.append_child("config")) {
				utils::xml_add_text_node(config, "blaze_service_name", "darkspore"); // Directly linked to BlazeServiceName
				utils::xml_add_text_node(config, "blaze_secure", "N"); // Directly linked to BlazeSecure
				utils::xml_add_text_node(config, "blaze_env", "prod"); // Directly linked to BlazeEnvironment, can be { prod, beta, cert, test, dev }
				utils::xml_add_text_node(config, "sporenet_cdn_host", host);
				utils::xml_add_text_node(config, "sporenet_db_host", host);
				utils::xml_add_text_node(config, "sporenet_db_name", "darkspore");
				utils::xml_add_text_node(config, "sporenet_host", host);
				utils::xml_add_text_node(config, "http_secure", "N");
				utils::xml_add_text_node(config, "liferay_host", host);
				utils::xml_add_text_node(config, "launcher_action", 2);
				utils::xml_add_text_node(config, "launcher_url", "http://" + host + "/bootstrap/launcher/?version=" + mVersion);
			}
		}

		docResponse.append_child("to_image");
		docResponse.append_child("from_image");

		bool include_settings = request.uri.parameter<bool>("include_settings");
		if (include_settings) {
			if (auto settings = docResponse.append_child("settings")) {
				using namespace std::string_view_literals;
				utils::xml_add_text_node(settings, "open", L"true"sv);
				settings.child("open").append_attribute("test").set_value("true");
				utils::xml_add_text_node(settings, "telemetry-rate", 256);
				utils::xml_add_text_node(settings, "telemetry-setting", 0);
			}
		}

		bool include_patches = request.uri.parameter<bool>("include_patches");
		if (include_patches) {
			add_patches(docResponse);
		}

		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_status_getStatus(HTTP::Session& session, HTTP::Response& response) {
		const auto& request = session.get_request();

		auto [document, docResponse] = create_xml_response();
		add_common_keys(docResponse);

		if (auto status = docResponse.append_child("status")) {
			if (auto api = status.append_child("api")) {
				utils::xml_add_text_node(api, "health", 1); // this+4Ah 1/0
				utils::xml_add_text_node(api, "revision", 1); // this+5Ch integer, setz to this+59h
				utils::xml_add_text_node(api, "version", 1); // this+60h integer
			}

			if (auto blaze = status.append_child("blaze")) {
				utils::xml_add_text_node(blaze, "health", 1); // this+4Bh 1/0
			}

			if (auto gms = status.append_child("gms")) {
				utils::xml_add_text_node(gms, "health", 1); // this+57h 1/0
			}

			if (auto nucleus = status.append_child("nucleus")) {
				utils::xml_add_text_node(nucleus, "health", 1); // this+58h 1/0
			}

			if (auto game = status.append_child("game")) {
				utils::xml_add_text_node(game, "health", 1); // this+4Ch 1/0
				utils::xml_add_text_node(game, "countdown", 90); // this+50h integer
				utils::xml_add_text_node(game, "open", 1); // this+54h 1/0
				utils::xml_add_text_node(game, "throttle", 1); // this+55h 1/0
				utils::xml_add_text_node(game, "vip", 1); // this+56h 1/0
			}
			/*
			if (auto unk = status.append_child("$\x84")) {
				utils::xml_add_text_node(unk, "health", "1");
				utils::xml_add_text_node(unk, "revision", "1");
				utils::xml_add_text_node(unk, "db_version", "1");
			}

			if (auto unk = status.append_child("$\x8B")) {
				utils::xml_add_text_node(unk, "health", "1");
			}
			*/
		}

		bool include_broadcasts = request.uri.parameter<bool>("include_broadcasts");
		if (include_broadcasts) {
			add_broadcasts(docResponse);
		}

		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_status_getBroadcastList(HTTP::Session& session, HTTP::Response& response) {
		auto [document, docResponse] = create_xml_response();

		add_common_keys(docResponse);
		add_broadcasts(docResponse);

		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_inventory_getPartList(HTTP::Session& session, HTTP::Response& response) {

		/*
			market status
				0 = unknown
				1 = full ownership
				2 = unknown
				3 = buyback
		*/

		auto [document, docResponse] = create_xml_response();

		const auto& user = session.get_user();
		add_common_keys(docResponse, user != nullptr);

		if (user) {
			user->get_parts().WriteApi(docResponse, false);
		} else {
			docResponse.append_child("parts");
		}

		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_inventory_getPartOfferList(HTTP::Session& session, HTTP::Response& response) {
		auto [document, docResponse] = create_xml_response();

		const auto& user = session.get_user();
		add_common_keys(docResponse, user != nullptr);

		if (user) {
			auto timestamp = utils::get_unix_time();
			utils::xml_add_text_node(docResponse, "timestamp", timestamp);
			utils::xml_add_text_node(docResponse, "expires", timestamp + (3 * 60 * 60 * 1000));

			const auto& vendor = SporeNet::Get().GetVendor();
			vendor.GetPartOfferList().WriteApi(docResponse, true);
		}

		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_inventory_vendorParts(HTTP::Session& session, HTTP::Response& response) {
		const auto& user = session.get_user();
		if (!user) {
			return;
		}

		SporeNet::Parts parts;

		const auto& request = session.get_request();
		const auto& transactionsString = request.uri.parameter("transactions");
		if (!transactionsString.empty()) {
			for (const auto& transaction : utils::explode_string(transactionsString, ';')) {
				// w = weapon, check for more later
				char type = transaction[0];
				int64_t data = utils::to_number<int64_t>(std::string_view(&transaction[1]));

				SporeNet::Part part(0);
				switch (type) {
					case 'w': {
						// weapon
						part.SetRigblock(static_cast<uint16_t>(data));
						part.SetIsFlair(false);
						part.SetLevel(5);
						part.SetMarketStatus(1);
						part.SetRarity(SporeNet::PartRarity::Rare);
						part.SetStatus(0);
						part.SetUsage(1);
						part.SetCreationDate(utils::get_unix_time());

						break;
					}

					case 'p': {
						// parts
						const auto& vendor = SporeNet::Get().GetVendor();
						part = vendor.GetPartOfferList().GetPart(data);
						break;
					}

					case 'b': {
						// buyback
						break;
					}

					case 's': {
						// sell
						break;
					}

					case 'f': {
						// flair
						break;
					}
				}

				parts.data().push_back(std::move(part));
			}
		}

		// Add part to user inventory
		// Resend all user parts?
		auto [document, docResponse] = create_xml_response();
		add_common_keys(docResponse);

		parts.WriteApi(docResponse, false);
		utils::xml_add_text_node(docResponse, "dna", user->get_account().dna);

		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_inventory_updatePartStatus(HTTP::Session& session, HTTP::Response& response) {
		const auto& user = session.get_user();
		if (!user) {
			// Error
			return;
		}

		const auto& request = session.get_request();

		auto partIds = utils::explode_string(request.uri.parameter("part_id"), ',');
		auto statuses = utils::explode_string(request.uri.parameter("status"), ',');

		size_t len = std::min<size_t>(partIds.size(), statuses.size());
		if (len > 0) {
			auto& parts = user->get_parts();
			for (size_t i = 0; i < len; ++i) {
				auto partIndex = utils::to_number<uint32_t>(partIds[i]);
				auto status = utils::to_number<uint8_t>(statuses[i]);
				parts.data()[partIndex].SetStatus(status);
			}
		}

		empty_xml_response(response);
	}

	void API::game_account_auth(HTTP::Session& session, HTTP::Response& response) {
		const auto& request = session.get_request();

		auto key = request.uri.parameter("key");
		if (!key.empty()) {
			// key = auth_token::0
			auto keyData = utils::explode_string(key, "::");

			const auto& user = SporeNet::Get().GetUserManager().GetUserByAuthToken(keyData.front());
			if (user) {
				session.set_user(user);
			}
		}

		auto [document, docResponse] = create_xml_response();

		const auto& user = session.get_user();
		add_common_keys(docResponse, user != nullptr);

		if (user) {
			auto timestamp = utils::get_unix_time();
			utils::xml_add_text_node(docResponse, "timestamp", timestamp * 1000);

			if (auto docAccount = docResponse.append_child("account")) {
				// Write "account" data
				auto& account = user->get_account();

				auto newPlayerProgress = request.uri.parameter<uint32_t>("new_player_progress");
				if (newPlayerProgress != 0) {
					std::cout << "Old progress: " << account.newPlayerProgress << ", New: " << newPlayerProgress << std::endl;
					account.newPlayerProgress = newPlayerProgress;
				}

				account.Write(docAccount);
			}

			if (request.uri.parameter<bool>("include_creatures")) {
				user->get_creatures().WriteApi(docResponse);
			}

			if (request.uri.parameter<bool>("include_decks")) {
				user->WriteSquadsAPI(docResponse);
			}

			if (request.uri.parameter<bool>("include_feed")) {
				user->get_feed().Write(docResponse);
			}

			if (request.uri.parameter<bool>("include_settings")) {
				if (auto settingsDoc = docResponse.append_child("settings")) {
					// Values can be an integer(long) or "on/off"
					/*
					utils::xml_add_text_node(settingsDoc, "showConfigAlerts", "on");
					utils::xml_add_text_node(settingsDoc, "cheat", "on");
					utils::xml_add_text_node(settingsDoc, "safeMode", "on");
					*/
				}
			}

			if (request.uri.parameter<bool>("include_server_tuning")) {
				if (auto server_tuning = docResponse.append_child("server_tuning")) {
					utils::xml_add_text_node(server_tuning, "itemstore_offer_period", timestamp);
					utils::xml_add_text_node(server_tuning, "itemstore_current_expiration", timestamp + (3 * 60 * 60 * 1000));
					utils::xml_add_text_node(server_tuning, "itemstore_cost_multiplier_basic", 1);
					utils::xml_add_text_node(server_tuning, "itemstore_cost_multiplier_uncommon", 1.1);
					utils::xml_add_text_node(server_tuning, "itemstore_cost_multiplier_rare", 1.2);
					utils::xml_add_text_node(server_tuning, "itemstore_cost_multiplier_epic", 1.3);
					utils::xml_add_text_node(server_tuning, "itemstore_cost_multiplier_unique", 1.4);
					utils::xml_add_text_node(server_tuning, "itemstore_cost_multiplier_rareunique", 1.5);
					utils::xml_add_text_node(server_tuning, "itemstore_cost_multiplier_epicunique", 1.6);
				}
			}

			if (request.uri.parameter<bool>("cookie")) {
				response.set(boost::beast::http::field::set_cookie, "token=" + user->get_auth_token());
			}
		} else {
			std::cout << "User not found" << std::endl;
		}

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
		/*
		pugi::xml_document document;
		if (auto docResponse = document.append_child("response")) {
			utils::xml_add_text_node(docResponse, "timestamp", utils::get_unix_time());
			if (auto docAccount = docResponse.append_child("account")) {
				// Write "account" data
				if (user) {
					auto& account = user->get_account();

					auto newPlayerProgress = request.uri.parameter<uint32_t>("new_player_progress");
					if (newPlayerProgress != 0) {
						std::cout << "Old progress: " << account.newPlayerProgress << ", New: " << newPlayerProgress << std::endl;
						account.newPlayerProgress = newPlayerProgress;
					}

					account.Write(docAccount);
				} else {
					SporeNet::Account account;
					account.Write(docAccount);
				}
			}

			// Other
			if (request.uri.parameter("include_creatures") == "true") {
				if (user) {
					user->get_creatures().WriteApi(docResponse);
				} else {
					docResponse.append_child("creatures");
				}
			}

			if (request.uri.parameter("include_decks") == "true") {
				if (user) {
					user->get_squads().Write(docResponse);
				} else {
					docResponse.append_child("decks");
				}
			}

			if (request.uri.parameter("include_feed") == "true") {
				if (user) {
					user->get_feed().Write(docResponse);
				} else {
					docResponse.append_child("feed");
				}
			}

			if (request.uri.parameter("include_server_tuning") == "true") {
				if (auto server_tuning = docResponse.append_child("server_tuning")) {
					auto timestamp = utils::get_unix_time();
					utils::xml_add_text_node(server_tuning, "itemstore_offer_period", timestamp);
					utils::xml_add_text_node(server_tuning, "itemstore_current_expiration", timestamp + (3 * 60 * 60 * 1000));
					utils::xml_add_text_node(server_tuning, "itemstore_cost_multiplier_basic", 1);
					utils::xml_add_text_node(server_tuning, "itemstore_cost_multiplier_uncommon", 1.1);
					utils::xml_add_text_node(server_tuning, "itemstore_cost_multiplier_rare", 1.2);
					utils::xml_add_text_node(server_tuning, "itemstore_cost_multiplier_epic", 1.3);
					utils::xml_add_text_node(server_tuning, "itemstore_cost_multiplier_unique", 1.4);
					utils::xml_add_text_node(server_tuning, "itemstore_cost_multiplier_rareunique", 1.5);
					utils::xml_add_text_node(server_tuning, "itemstore_cost_multiplier_epicunique", 1.6);
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
		*/

		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_account_getAccount(HTTP::Session& session, HTTP::Response& response) {
		/*
			Accept-Language
			Cookie
			User-Agent
			Host
			Set-Cookie
			Set-Cookie2
			If-Modified-Since
		*/

		const auto& user = session.get_user();
		if (!user) {
			std::cout << "No user in api.account.getAccount" << std::endl;
			// Send some error?
			return;
		}

		const auto& request = session.get_request();
		const auto& account = user->get_account();

		auto [document, docResponse] = create_xml_response();
		add_common_keys(docResponse);

		switch (response.method()) {
			case boost::beast::http::verb::get: {
				if (auto docAccount = docResponse.append_child("account")) {
					account.Write(docAccount);
				}

				user->WriteSquadsAPI(docResponse);

				set_response_body(response, document, boost::beast::http::status::ok);
				break;
			}

			case boost::beast::http::verb::post: {
				bool include_creatures = request.uri.parameter<bool>("include_creatures");
				bool include_decks = request.uri.parameter<bool>("include_decks");
				bool include_feed = request.uri.parameter<bool>("include_feed");
				bool include_stats = request.uri.parameter<bool>("include_stats");

				if (include_creatures || include_decks || include_feed || include_stats) {
					if (auto docAccount = docResponse.append_child("account")) {
						account.Write(docAccount);
					}

					if (include_creatures) {
						user->get_creatures().WriteApi(docResponse);
					}

					if (include_decks) {
						user->WriteSquadsAPI(docResponse);
					}

					if (include_feed) {
						user->get_feed().Write(docResponse);
					}

					if (include_stats) {
						auto stats = docResponse.append_child("stats");
						auto stat = stats.append_child("stat");
						utils::xml_add_text_node(stat, "wins", 0);

						/*
							if(detailstats.childNodes[i].tagName != 'pve_swaps'
							  && detailstats.childNodes[i].tagName != 'pve_overcharges'
							  && detailstats.childNodes[i].tagName != 'pve_dna'
							  && detailstats.childNodes[i].tagName != 'pve_abilitiesUsed'
							  && detailstats.childNodes[i].tagName != 'pve_healthCollected'
							  && detailstats.childNodes[i].tagName != 'pve_powerCollected'
							  && detailstats.childNodes[i].tagName != 'pve_obelisks'
							  && detailstats.childNodes[i].tagName != 'pve_catalysts'
							  && detailstats.childNodes[i].tagName != 'pvp_xp'
							  && detailstats.childNodes[i].tagName != 'pvp_swaps'
							  && detailstats.childNodes[i].tagName != 'pvp_overcharges'
							  && detailstats.childNodes[i].tagName != 'pvp_abilitiesUsed'
							  && detailstats.childNodes[i].tagName != 'pvp_healthCollected'
							  && detailstats.childNodes[i].tagName != 'pvp_powerCollected'
							  && detailstats.childNodes[i].tagName != 'wins'
							  && detailstats.childNodes[i].tagName != 'pvp_glickoSkill'
							  && detailstats.childNodes[i].tagName != 'pvp_glickoRD'
							  && detailstats.childNodes[i].tagName != 'pve_progression'
						*/
					}
				} else {
					utils::xml_add_text_node(docResponse, "blaze_id", account.id);
					utils::xml_add_text_node(docResponse, "name", user->get_name());
					utils::xml_add_text_node(docResponse, "grant_online_access", account.grantOnlineAccess);
					utils::xml_add_text_node(docResponse, "cashout_bonus_time", account.cashoutBonusTime);
				}

				set_response_body(response, document, boost::beast::http::status::created);
				break;
			}
		}
	}

	void API::game_account_logout(HTTP::Session& session, HTTP::Response& response) {
		const auto& user = session.get_user();
		if (user) {
			user->Logout();
		}
	}

	void API::game_account_unlock(HTTP::Session& session, HTTP::Response& response) {
		const auto& request = session.get_request();
		const auto& user = session.get_user();

		bool success = false;

		auto [document, docResponse] = create_xml_response();
		if (user) {
			auto unlockId = request.uri.parameter<uint32_t>("unlock_id");
			success = user->UnlockUpgrade(unlockId);

			user->get_account().Write(docResponse);
		}

		add_common_keys(docResponse, success);
		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_account_setSettings(HTTP::Session& session, HTTP::Response& response) {
		const auto& request = session.get_request();
		const auto& user = session.get_user();

		bool success = false;

		auto [document, docResponse] = create_xml_response();
		if (user) {
			auto settings = request.uri.parameter("settings");
			for (const auto& setting : utils::explode_string(settings, ';')) {
				auto settingData = utils::explode_string(setting, ',');
				if (settingData.size() < 2) {
					continue;
				}

				const auto& key = settingData[0];
				const auto& value = settingData[1];

				// parse/save settings
			}

			success = true;
		}

		add_common_keys(docResponse, success);
		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_account_searchAccounts(HTTP::Session& session, HTTP::Response& response) {
		const auto& request = session.get_request();
		const auto& user = session.get_user();

		bool success = false;

		auto [document, docResponse] = create_xml_response();
		if (user) {
			auto sortBy = request.uri.parameter("sort");
			auto terms = request.uri.parameter("terms");

			auto start = request.uri.parameter<uint32_t>("start");
			auto count = request.uri.parameter<uint32_t>("count");

			/*
				count = 10
				method = api.account.searchAccounts
				sort = name
				start = 0
				terms = Search for Players
			*/

			if (auto docAccounts = docResponse.append_child("accounts")) {
				const auto& users = SporeNet::Get().GetUserManager().GetUsers();
				for (const auto& otherUser : users) {
					auto account = docAccounts.append_child("account");
					utils::xml_add_text_node(account, "blaze_id", otherUser->get_id());
					utils::xml_add_text_node(account, "account_id", otherUser->get_id());
					utils::xml_add_text_node(account, "name", otherUser->get_name());
					utils::xml_add_text_node(account, "presence_level", 1);
				}
			}

			if (sortBy == "name") {

			} else if (sortBy == "presence_level") {

			} else if (sortBy == "presence") {

			} else if (sortBy == "party") {

			} else if (sortBy == "XP") {

			}

			success = true;
		}

		add_common_keys(docResponse, success);
		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_game_getGame(HTTP::Session& session, HTTP::Response& response) {
		auto [document, docResponse] = create_xml_response();
		add_common_keys(docResponse);

		if (auto game = docResponse.append_child("game")) {
			utils::xml_add_text_node(game, "game_id", 1);
			utils::xml_add_text_node(game, "cashed_out", 0);
			utils::xml_add_text_node(game, "finished", 0);
			utils::xml_add_text_node(game, "starting_difficulty", 1);
			utils::xml_add_text_node(game, "start", 1);
			
			utils::xml_add_text_node(game, "rounds", 0);
			utils::xml_add_text_node(game, "chain_id", 0);
			utils::xml_add_text_node(game, "finish", 0);
			utils::xml_add_text_node(game, "planet_id", utils::hash_id("zelems_1.Level"));
			utils::xml_add_text_node(game, "success", 0);
			
			if (auto players = game.append_child("players")) {
				if (auto player = players.append_child("player")) {
					/*
					utils::xml_add_text_node(player, "deaths", 0);
					utils::xml_add_text_node(player, "kills", 0);
					*/
					utils::xml_add_text_node(player, "account_id", 1);
					utils::xml_add_text_node(player, "result", 0);
					utils::xml_add_text_node(player, "creature1_id", 1);
					utils::xml_add_text_node(player, "creature1_version", 1);
					utils::xml_add_text_node(player, "creature2_id", 0);
					utils::xml_add_text_node(player, "creature2_version", 0);
					utils::xml_add_text_node(player, "creature3_id", 0);
					utils::xml_add_text_node(player, "creature3_version", 0);
				}
			}
		}

		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_game_getRandomGame(HTTP::Session& session, HTTP::Response& response) {
		const auto& request = session.get_request();
		const auto& user = session.get_user();

		bool success = false;
		if (user) {
			success = true;
		}

		auto replay_version = request.uri.parameter<int32_t>("replay_version");

		auto [document, docResponse] = create_xml_response();
		add_common_keys(docResponse, success);

		if (auto game = docResponse.append_child("game")) {
			utils::xml_add_text_node(game, "game_id", 1);
			utils::xml_add_text_node(game, "cashed_out", 0);
			utils::xml_add_text_node(game, "finish", "2"); // string (time?)
			utils::xml_add_text_node(game, "starting_difficulty", 1);
			utils::xml_add_text_node(game, "start", "1"); // string (time?)

			if (auto rounds = game.append_child("rounds")) {
				utils::xml_add_text_node(rounds, "chain_id", 1);
				utils::xml_add_text_node(rounds, "finish", "2"); // string (time?)
				utils::xml_add_text_node(rounds, "planet_id", utils::hash_id("zelems_1.Level"));
				utils::xml_add_text_node(rounds, "success", "N");
				utils::xml_add_text_node(rounds, "round_id", 1);
				utils::xml_add_text_node(rounds, "start", "1"); // string (time?)

				if (auto players = rounds.append_child("players")) {
					if (auto player = players.append_child("player")) {
						utils::xml_add_text_node(player, "deaths", 0);
						utils::xml_add_text_node(player, "kills", 0);
						utils::xml_add_text_node(player, "account_id", 100);
						utils::xml_add_text_node(player, "result", "completed");
						utils::xml_add_text_node(player, "creature1_id", 10);
						utils::xml_add_text_node(player, "creature1_version", 1);
						utils::xml_add_text_node(player, "creature2_id", 11);
						utils::xml_add_text_node(player, "creature2_version", 1);
						utils::xml_add_text_node(player, "creature3_id", 12);
						utils::xml_add_text_node(player, "creature3_version", 1);
					}
				}
			}
		}

		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_game_exitGame(HTTP::Session& session, HTTP::Response& response) {
		auto [document, docResponse] = create_xml_response();
		add_common_keys(docResponse);

		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_creature_resetCreature(HTTP::Session& session, HTTP::Response& response) {
		const auto& request = session.get_request();
		const auto& user = session.get_user();

		auto [document, docResponse] = create_xml_response();
		add_common_keys(docResponse);

		if (user) {
			auto creature = user->GetCreatureById(request.uri.parameter<uint32_t>("id"));
			if (creature) {
				if (auto creatureNode = docResponse.append_child("creature")) {
					creature->Write(creatureNode);
				}
			} else {
				// Error, creature not found.
			}
		} else {
			// Error, not logged in.
		}

		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_creature_unlockCreature(HTTP::Session& session, HTTP::Response& response) {
		const auto& request = session.get_request();

		auto [document, docResponse] = create_xml_response();
		add_common_keys(docResponse);

		const auto& user = session.get_user();
		if (user) {
			auto templateId = request.uri.parameter<uint32_t>("template_id");
			auto creatureId = user->UnlockCreature(templateId);

			utils::xml_add_text_node(docResponse, "creature_id", creatureId);
		} else {
			// Send some error
		}

		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_creature_getCreature(HTTP::Session& session, HTTP::Response& response) {
		const auto& request = session.get_request();

		auto [document, docResponse] = create_xml_response();
		add_common_keys(docResponse);

		const auto& user = session.get_user();
		if (user) {
			bool include_abilities = request.uri.parameter<bool>("include_abilities");
			bool include_parts = request.uri.parameter<bool>("include_parts");

			auto creature = user->GetCreatureById(request.uri.parameter<uint32_t>("id"));
			if (creature) {
				creature->WriteApi(docResponse, true, include_abilities, include_parts);
			} else {
				// Unknown creature.
			}
		} else {
			// TODO: Error, no user logged in.
		}

		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_creature_getTemplate(HTTP::Session& session, HTTP::Response& response) {
		const auto& request = session.get_request();
		const auto& user = session.get_user();

		auto [document, docResponse] = create_xml_response();
		add_common_keys(docResponse);

		if (user) {
			bool include_abilities = request.uri.parameter<bool>("include_abilities");

			auto templateCreature = SporeNet::Get().GetTemplateDatabase().Get(request.uri.parameter<uint32_t>("id"));
			if (templateCreature) {
				templateCreature->WriteApi(docResponse, include_abilities);
			} else {
				// Unknown creature.
			}
		} else {
			// TODO: Error, no user logged in.
		}

		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_creature_updateCreature(HTTP::Session& session, HTTP::Response& response) {
		/*
cost = 0
gear = 1.000
id = 10
large = iVBORw0KGgoAAAANSUhEUgAAAQAAAAEACAYAAABccqhmAAAgAElEQVR4nOy9d7Cl533f93nKW06/
large_crc = 2739193539
method = api.creature.updateCreature
parts = 6
points = 313.814
stats = STR,14,3;DEX,23,5;MIND,13,0;HLTH,200,107;MANA,100,13;PDEF,150,168;EDEF,50,78;CRTR,100,112
stats_ability_keyvalues = 868969257!minDamage,4;868969257!maxDamage,12;4022963036!percent,50;1137096183!minDamage,24;1137096183!maxDamage,36;1137096183!stunDuration,3;3492557026!minSecondaryDamage,8;3492557026!maxSecondaryDamage,20;3492557026!minDamage,24;3492557026!maxDamage,40;3492557026!radius,4;2779439490!numOrbs,6;2779439490!minDamage,16;2779439490!maxDamage,40;2779439490!deflectionIncrease,100
thumb = iVBORw0KGgoAAAANSUhEUgAAAIAAAACACAYAAADDPmHLAAAgAElEQVR4nGy9abBtx3kdtlb3Hs5w
thumb_crc = 2819438930
token = 100
version = 1
	*/

		const auto& request = session.get_request();
		const auto& uri = request.uri;

		auto [document, docResponse] = create_xml_response();
		add_common_keys(docResponse);

		const auto& user = session.get_user();
		if (user) {
			auto creature_id = uri.parameter<uint32_t>("id");
			auto creature = user->GetCreatureById(creature_id);
			if (creature) {
				auto version = creature->GetVersion();

				// save large/thumb images
				std::string storagePath = Config::Get(CONFIG_STORAGE_PATH) + "creature_png/";
				std::string creaturePath = std::to_string(creature_id) + "_" + std::to_string(version);

				if (auto largePng = uri.parameter("large"); !largePng.empty()) {
					auto largeCrc = uri.parameter<uint32_t>("large_crc");
					auto data = base64_decode(largePng, true);
					lodepng::save_file(std::vector<uint8_t>(data.begin(), data.end()), storagePath + creaturePath + "_large.png");
				}

				if (auto thumbPng = uri.parameter("thumb"); !thumbPng.empty()) {
					auto thumbCrc = uri.parameter<uint32_t>("thumb_crc");
					auto data = base64_decode(thumbPng, true);
					lodepng::save_file(std::vector<uint8_t>(data.begin(), data.end()), storagePath + creaturePath + "_thumb.png");
				}

				const auto& partsString = uri.parameter("parts");
				// parse parts

				creature->Update(
					uri.parameter<float>("gear"),
					uri.parameter<float>("points"),
					partsString,
					uri.parameter("stats"),
					uri.parameter("stats_ability_keyvalues")
				);

				auto creatureNode = docResponse.append_child("creature");
				utils::xml_add_text_node(docResponse, "version", version);
			}
		} else {
			// TODO: Error, no user logged in.
		}

		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_deck_updateDecks(HTTP::Session& session, HTTP::Response& response) {
		const auto& user = session.get_user();
		if (!user) {
			// TODO: Error, no user logged in.
			return;
		}

		const auto& request = session.get_request();
		user->UpdateSquad(request.uri.parameter<uint32_t>("pve_active_slot"), request.uri.parameter("pve_creatures"), false);
		user->UpdateSquad(request.uri.parameter<uint32_t>("pvp_active_slot"), request.uri.parameter("pvp_creatures"), true);

		auto [document, docResponse] = create_xml_response();
		add_common_keys(docResponse);

		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::game_leaderboard_getLeaderboard(HTTP::Session& session, HTTP::Response& response) {
		// DR:225364700

		constexpr std::string_view pveCategories[] {
			"progression",
			"xp",
			"totalKills",
			"deaths",
			"killDeathRatio",
			"damageMax",
			"healingMax"
		};

		constexpr std::string_view pvpCategories[] {
			"wins",
			"playerKills",
			"damageMax",
			"healingMax"
		};

		const auto& request = session.get_request();
		const auto& user = session.get_user();

		bool success = false;

		auto [document, docResponse] = create_xml_response();
		if (user) {
			auto sortBy = request.uri.parameter("name");
			auto varient = request.uri.parameter("varient");
			auto teamSize = request.uri.parameter<uint32_t>("vs");

			auto start = request.uri.parameter<uint32_t>("start");
			auto count = request.uri.parameter<uint32_t>("count");

			bool pvp = sortBy.find("pvp") != std::string::npos;

			add_common_keys(docResponse, true);
			if (auto statsNode = docResponse.append_child("stats")) {
				// priority order
				if (pvp) {
					for (const auto& category : pvpCategories) {
						utils::xml_add_text_node(statsNode, "stat", category);
					}
				} else {
					for (const auto& category : pveCategories) {
						utils::xml_add_text_node(statsNode, "stat", category);
					}
				}
			}

			if (auto playersNode = docResponse.append_child("players")) {
				const auto& account = user->get_account();

				auto playerNode = playersNode.append_child("player");
				utils::xml_add_text_node(playerNode, "id", account.id);
				utils::xml_add_text_node(playerNode, "name", user->get_name());

				auto playerStatsNode = playerNode.append_child("stats");
				if (pvp) {
					for (const auto& category : pvpCategories) {
						utils::xml_add_text_node(playerStatsNode, "stat", category);
					}
				} else {
					for (const auto& category : pveCategories) {
						utils::xml_add_text_node(playerStatsNode, "stat", category);
					}
				}
			}
		} else {
			add_common_keys(docResponse, false);
		}

		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::survey_survey_getSurveyList(HTTP::Session& session, HTTP::Response& response) {
		auto [document, docResponse] = create_xml_response();
		add_common_keys(docResponse);

		if (auto surveys = docResponse.append_child("surveys")) {
			/*
				<surveys>
					<survey>
						<id>some_id</id>
						<trigger1>some_integer</trigger1>
						<trigger2>some_integer</trigger2>
					</survey>
				</surveys>
			*/
			// Empty
		}

		set_response_body(response, document, boost::beast::http::status::ok);
	}

	void API::add_patches(pugi::xml_node& node) {
		/*
			target, date, from_version, to_version, id, description, application_instructions,
			locale, shipping, file_url, archive_size, uncompressed_size,
			hashes(attributes, Version, Hash, Size, BlockSize)
		*/
		auto patches = node.append_child("patches");
		if (!patches) {
			return;
		}

		// target
		patches.append_attribute("target").set_value("test");

		// date
		patches.append_attribute("date").set_value("test2");

		// from_version
		patches.append_attribute("from_version").set_value("test3");

		// to_version
		patches.append_attribute("to_version").set_value("test4");

		// id
		patches.append_attribute("id").set_value("test5");

		// description
		patches.append_attribute("description").set_value("test6");

		// application_instructions
		patches.append_attribute("application_instructions").set_value("test6");

		// locale
		patches.append_attribute("locale").set_value("en-US");

		// shipping (true or false)
		patches.append_attribute("shipping").set_value("true");

		// file_url
		patches.append_attribute("file_url").set_value("test.zip");

		// archive_size
		patches.append_attribute("archive_size").set_value("1000");

		// uncompressed_size
		patches.append_attribute("uncompressed_size").set_value("2000");

		// hashes
		patches.append_attribute("hashes").set_value("0123456789abcdef");

		// length 16 hashes u128
		/*
		if (auto hashes = patches.append_child("hashes")) {
			std::vector<std::string> test = { "a", "b" };
			for (const auto& t : test) {
				auto attributes = hashes.append_child("attributes");
				utils::xml_add_text_node(attributes, "Version", "1");
				utils::xml_add_text_node(attributes, "Hash", "2");
				utils::xml_add_text_node(attributes, "Size", "3");

				// required field
				utils::xml_add_text_node(attributes, "BlockSize", "4");
			}
		}
		*/
	}

	void API::add_broadcasts(pugi::xml_node& node) {
		if (auto broadcasts = node.append_child("broadcasts")) {
			
			if (auto broadcast = broadcasts.append_child("broadcast")) {
				utils::xml_add_text_node(broadcast, "id", 0x10);
				utils::xml_add_text_node(broadcast, "end", 0x11);
				utils::xml_add_text_node(broadcast, "start", 0x12);
				utils::xml_add_text_node(broadcast, "type", 0x13);
				utils::xml_add_text_node(broadcast, "message", "Bananas for sale! Come get your bananas for only 50 bucks each!");
				utils::xml_add_text_node(broadcast, "tokens", "12345678");
				/*
				if (auto tokens = broadcast.append_child("tokens")) {
					utils::xml_add_text_node(broadcast, "token", "12345");
				}
				*/
			}
			
		}
	}

	void API::add_common_keys(pugi::xml_node& node, bool success, uint32_t successStatus) {
		if (success) {
			utils::xml_add_text_node(node, "stat", "ok");
			utils::xml_add_text_node(node, "code", successStatus);
			utils::xml_add_text_node(node, "result", 1);
		} else {
			utils::xml_add_text_node(node, "stat", "error");
			utils::xml_add_text_node(node, "code", boost::beast::http::status::internal_server_error);
			utils::xml_add_text_node(node, "result", 0);
		}

		// utils::xml_add_text_node(node, "version", 1); // mVersion
		// utils::xml_add_text_node(node, "timestamp", utils::get_unix_time());
		// utils::xml_add_text_node(node, "exectime", ++mPacketId);
	}

	void API::add_common_keys(rapidjson::Document& document) {
		/*
		obj["stat"] = 'ok'
		obj["version"] = self.server.gameVersion
		obj["timestamp"] = self.timestamp()
		obj["exectime"] = self.exectime()
		*/
	}

	void API::set_response_body(HTTP::Response& response, pugi::xml_document& xmlDocument, boost::beast::http::status result) const {
		xml_string_writer writer;
		xmlDocument.save(writer, "\t", pugi::format_default | pugi::format_write_bom, pugi::encoding_latin1);

		response.set(boost::beast::http::field::host, "127.0.0.1");
		// "%s/%s (Pollinator; %s)" (name, version, os_version)
		// response.set(boost::beast::http::field::user_agent, "Darkspore/5.3.0.127 (Pollinator; 6.2.9200)");
		// response.set(boost::beast::http::field::date, utils::get_utc_date_string());
		// response.set(boost::beast::http::field::user_agent, "EA/2.0 (compatible)");
		response.set(boost::beast::http::field::content_language, "en-us");
		response.set(boost::beast::http::field::content_type, "text/xml");
		// response.set(boost::beast::http::field::content_type, "text/xml; charset=utf-8");

		if (result == boost::beast::http::status::created) {
			response.set(boost::beast::http::field::location, "http://127.0.0.1/api");
		}

		response.result() = result;
		response.body() = std::move(writer.result);
	}
}
