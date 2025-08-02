
#ifndef _MAIN_HEADER
#define _MAIN_HEADER

// Include
#include "predefined.h"

#include "blaze/server.h"
#include "http/server.h"
#include "qos/server.h"
#include "game/api.h"

#include <filesystem>

// Application
class Application {
	private:
		Application();
		static bool sVerboseTimestamps;
		static std::string darksporeInstallPath;
		static std::string darksporeInstallVersion;
		
	public:
		static Application& InitApp(int argc, char* argv[]);
		static Application& GetApp();
		static bool IsVerboseTimestamps() { return sVerboseTimestamps; }
		static std::string GetDarksporeInstallPath() { return darksporeInstallPath; }

		bool OnInit();
		int OnExit();

		void Run();

		boost::asio::io_context& get_io_service();

		Scheduler& GetScheduler() const;

		SporeNet::Instance& GetSporeNet() const;

		Game::API* get_game_api() const;
		Blaze::Server* get_redirector_server() const;
		Blaze::Server* get_blaze_server() const;
		Blaze::Server* get_pss_server() const;
		Blaze::Server* get_telemetry_server() const;
		Blaze::Server* get_tick_server() const;
		HTTP::Server* get_http_server() const;
		HTTP::Server* get_http_qos_server() const;
		QoS::Server* get_qos_server() const;

	private:
		static Application* sApplication;

		boost::asio::io_context mIoService;
		boost::asio::signal_set mSignals;

		std::unique_ptr<Scheduler> mScheduler;

		std::unique_ptr<SporeNet::Instance> mSporeNet;

		std::unique_ptr<Game::API> mGameAPI;

		std::unique_ptr<Blaze::Server> mRedirectorServer;
		std::unique_ptr<Blaze::Server> mBlazeServer;
		std::unique_ptr<Blaze::Server> mPssServer;
		std::unique_ptr<Blaze::Server> mTelemetryServer;
		std::unique_ptr<Blaze::Server> mTickServer;

		std::unique_ptr<HTTP::Server> mHttpServer;
		std::unique_ptr<HTTP::Server> mHttpTelemetryServer;
		std::unique_ptr<HTTP::Server> mHttpQosServer;

		std::unique_ptr<QoS::Server> mQosServer;

		void LoadDarksporeVersionAndPath();
		void LoadDarksporeData();
		void RunCommand(const std::string& cmd);
		void MergeDirectories(const std::filesystem::path& source, const std::filesystem::path& destination);
		std::string LoadVersionFromDarksporeInstall();
};

static Application& GetApp() {
	return Application::GetApp();
}

#endif
