
// Include
#include "main.h"
#include "scheduler.h"

#include "sporenet/instance.h"

#include "http/uri.h"

#include "game/config.h"
#include "game/noun.h"
#include "game/lua.h"

#include "utils/net.h"

#include "installer.h"

#include <iostream>
#include <cstring>
#include <fstream>
#include <filesystem>
#include <string>
#include <algorithm>
#include <cctype>

/*

127.0.0.1 321915-prodmydb007.spore.rspc-iad.ea.com
127.0.0.1 beta-sn.darkspore.ea.com

*/

// Application
Application* Application::sApplication = nullptr;

bool Application::sVerboseTimestamps = false;

std::string Application::darksporeInstallPath = "../..";
std::string Application::darksporeInstallVersion = "5.3.0.127";

Application::Application() : mIoService(), mSignals(mIoService, SIGINT, SIGTERM) {
	mSignals.async_wait([&](auto, auto) { mIoService.stop(); });
}

Application& Application::InitApp(int argc, char* argv[]) {
	if (!sApplication) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--timestamps") == 0 || 
                strcmp(argv[i], "-ts") == 0) {
                sVerboseTimestamps = true;
            } else if (strcmp(argv[i], "--darkspore-path") == 0) {
        		i++;
        		darksporeInstallPath = std::string(argv[i]);
			} else if (strcmp(argv[i], "--help") == 0 ||
                       strcmp(argv[i], "-h") == 0) {
                std::cout << "Usage: " << argv[0] << " [options]\n";
                std::cout << "Options:\n";
                std::cout << "  --timestamps, -ts    timestamp log\n";
                std::cout << "  --help, -h                   Shows this help\n";
                exit(0);
            }
        }
        
        sApplication = new Application;
#ifdef _WIN32
		/*
		SetConsoleCtrlHandler([](DWORD) -> BOOL {
			// TODO: proper shutdown when closing
			ExitThread(0);
		}, 1);
		*/
#endif
	}
	return *sApplication;
}

Application& Application::GetApp() {
	return *sApplication;
}

bool Application::OnInit() {
	setlocale(LC_ALL, "C");

#ifdef _WIN32
	AllocConsole();
	(void)freopen("CONOUT$", "w", stdout);
	(void)freopen("CONOUT$", "w", stderr);
	SetConsoleOutputCP(CP_UTF8);
#endif

	// Loading Darkspore version and path
	LoadDarksporeVersionAndPath();

	// Config
	Game::Config::Load("config.xml");

	// Scheduler
	mScheduler = std::make_unique<Scheduler>();

	// SporeNet
	mSporeNet = std::make_unique<SporeNet::Instance>();

	// Game
	mGameAPI = std::make_unique<Game::API>(darksporeInstallVersion);

	const auto host = Game::Config::Get(Game::ConfigKey::CONFIG_SERVER_HOST);
	const auto redirector_port = Game::Config::GetU16(Game::ConfigKey::CONFIG_SERVER_REDIRECTOR_PORT);
	const auto blaze_port = Game::Config::GetU16(Game::ConfigKey::CONFIG_SERVER_BLAZE_PORT);
	const auto pss_port = Game::Config::GetU16(Game::ConfigKey::CONFIG_SERVER_PSS_PORT);
	const auto tick_port = Game::Config::GetU16(Game::ConfigKey::CONFIG_SERVER_TICK_PORT);
	const auto telemetry_port = Game::Config::GetU16(Game::ConfigKey::CONFIG_SERVER_TELEMETRY_PORT);
	const auto qos_port = Game::Config::GetU16(Game::ConfigKey::CONFIG_SERVER_QOS_PORT);
	const auto http_port = Game::Config::GetU16(Game::ConfigKey::CONFIG_SERVER_HTTP_PORT);
	const auto http_telemetry_port = Game::Config::GetU16(Game::ConfigKey::CONFIG_SERVER_HTTP_TELEMETRY_PORT);
	const auto http_qos_port = Game::Config::GetU16(Game::ConfigKey::CONFIG_SERVER_HTTP_QOS_PORT);

	const auto ip = utils::net::resolve_ip(host, http_port);

	// Blaze
	mRedirectorServer = std::make_unique<Blaze::Server>(mIoService, ip, redirector_port);
	mBlazeServer = std::make_unique<Blaze::Server>(mIoService, ip, blaze_port);

	mPssServer = std::make_unique<Blaze::Server>(mIoService, ip, pss_port);
	mTickServer = std::make_unique<Blaze::Server>(mIoService, ip, tick_port);
	mTelemetryServer = std::make_unique<Blaze::Server>(mIoService, ip, telemetry_port);

	// QoS
	mQosServer = std::make_unique<QoS::Server>(mIoService, ip, qos_port);

	// HTTP
	mHttpServer = std::make_unique<HTTP::Server>(mIoService, ip, http_port);
	mHttpTelemetryServer = std::make_unique<HTTP::Server>(mIoService, ip, http_telemetry_port);
	mHttpQosServer = std::make_unique<HTTP::Server>(mIoService, ip, http_qos_port);

	const auto& router = mHttpServer->get_router();
	mHttpTelemetryServer->set_router(router);
	mHttpQosServer->set_router(router);

	//
	mGameAPI->setup();

	// Preparing the data folder
	std::thread t([this]() {
		if (!darksporeInstallPath.empty())
		{
			Installer::LoadDarksporeData(darksporeInstallPath, darksporeInstallVersion);
		}

		// Load noun files
		(void)Game::NounDatabase::Instance();

		// Load scripts
		Game::GlobalLua::Instance().Initialize();
	});
	t.detach();

	return true;
}

int Application::OnExit() {
	mGameAPI.reset();
	mRedirectorServer.reset();
	mBlazeServer.reset();
	mHttpServer.reset();
	mQosServer.reset();
	mSporeNet.reset();

	mScheduler->Shutdown();
	mScheduler.reset();
	return 0;
}

void Application::Run() {
	try {
		mIoService.run();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

void Application::LoadDarksporeVersionAndPath()
{
	darksporeInstallPath = std::filesystem::absolute(darksporeInstallPath).string();
	std::string newDarksporeInstallVersion = LoadVersionFromDarksporeInstall();
	if (!newDarksporeInstallVersion.empty()) {
		darksporeInstallVersion = newDarksporeInstallVersion;
	} else {
		darksporeInstallPath = "";
	}

	std::cout << "Darkspore version: " << darksporeInstallVersion << std::endl;
	if (!darksporeInstallPath.empty()) {
		std::cout << "Darkspore install path: " << darksporeInstallPath << std::endl;
	}
}

std::string Application::LoadVersionFromDarksporeInstall()
{
	std::filesystem::path darksporeInstall(darksporeInstallPath);
	std::filesystem::path appended = darksporeInstall / "DarksporeBin" / "version_bin.txt";
	std::ifstream file(appended.string(), std::ios::in | std::ios::binary);
	if (!file) return "";
	std::string version = std::string(std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>());
	trim(version);
	return version;
}

void Application::trim(std::string& s) {
	// Trim leading spaces and newlines
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return ch != ' ' && ch != '\n';
	}));

	// Trim trailing spaces and newlines
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return ch != ' ' && ch != '\n';
	}).base(), s.end());
}

boost::asio::io_context& Application::get_io_service() {
	return mIoService;
}

Scheduler& Application::GetScheduler() const {
	return *mScheduler;
}

SporeNet::Instance& Application::GetSporeNet() const {
	return *mSporeNet;
}

Game::API* Application::get_game_api() const {
	return mGameAPI.get();
}

Blaze::Server* Application::get_redirector_server() const {
	return mRedirectorServer.get();
}

Blaze::Server* Application::get_blaze_server() const {
	return mBlazeServer.get();
}

Blaze::Server* Application::get_pss_server() const {
	return mPssServer.get();
}

Blaze::Server* Application::get_tick_server() const {
	return mTickServer.get();
}

Blaze::Server* Application::get_telemetry_server() const {
	return mTelemetryServer.get();
}

HTTP::Server* Application::get_http_server() const {
	return mHttpServer.get();
}

HTTP::Server* Application::get_http_qos_server() const {
	return mHttpQosServer.get();
}

QoS::Server* Application::get_qos_server() const {
	return mQosServer.get();
}

// main
int main(int argc, char* argv[]) {
	Application& app = Application::InitApp(argc, argv);
	if (!app.OnInit()) {
		app.OnExit();
		return 1;
	}

	app.Run();
	return app.OnExit();
}
