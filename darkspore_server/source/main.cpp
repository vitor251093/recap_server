
// Include
#include "main.h"
#include "scheduler.h"

#include "sporenet/instance.h"

#include "http/uri.h"

#include "game/config.h"
#include "game/noun.h"
#include "game/lua.h"

#include <iostream>

/*

127.0.0.1 321915-prodmydb007.spore.rspc-iad.ea.com
127.0.0.1 beta-sn.darkspore.ea.com

*/

// Application
Application* Application::sApplication = nullptr;

Application::Application() : mIoService(), mSignals(mIoService, SIGINT, SIGTERM) {
	mSignals.async_wait([&](auto, auto) { mIoService.stop(); });
}

Application& Application::InitApp(int argc, char* argv[]) {
	if (!sApplication) {
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

	// Config
	Game::Config::Load("config.xml");

	// Scheduler
	mScheduler = std::make_unique<Scheduler>();

	// SporeNet
	mSporeNet = std::make_unique<SporeNet::Instance>();

	// Game
	mGameAPI = std::make_unique<Game::API>("5.3.0.127");

	// Blaze
	mRedirectorServer = std::make_unique<Blaze::Server>(mIoService, 42127);
	mBlazeServer = std::make_unique<Blaze::Server>(mIoService, 10041);

	mPssServer = std::make_unique<Blaze::Server>(mIoService, 8443);
	mTickServer = std::make_unique<Blaze::Server>(mIoService, 8999);
	mTelemetryServer = std::make_unique<Blaze::Server>(mIoService, 9988);

	// QoS
	mQosServer = std::make_unique<QoS::Server>(mIoService, 3659);

	// HTTP
	mHttpServer = std::make_unique<HTTP::Server>(mIoService, 80);
	mHttpTelemetryServer = std::make_unique<HTTP::Server>(mIoService, 8080);
	mHttpQosServer = std::make_unique<HTTP::Server>(mIoService, 17502);

	const auto& router = mHttpServer->get_router();
	mHttpTelemetryServer->set_router(router);
	mHttpQosServer->set_router(router);

	//
	mGameAPI->setup();

	// Load noun files
	(void)Game::NounDatabase::Instance();

	// Load scripts
	Game::GlobalLua::Instance().Initialize();

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
