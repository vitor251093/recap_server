
#ifndef _BLAZE_COMPONENT_UTIL_HEADER
#define _BLAZE_COMPONENT_UTIL_HEADER

// Include
#include "blaze/component.h"

// Blaze
namespace Blaze {
	// UtilComponent
	class UtilComponent : public Component {
		public:
			enum : uint16_t { Id = 0x09 };

			uint16_t GetId() const override;

			std::string_view GetName() const override;
			std::string_view GetReplyPacketName(uint16_t command) const override;

			bool ParsePacket(Request& request) override;

		private:
			// Response
			static void WritePostAuth(TDF::Packet& packet, const PssConfig& pss, const TelemetryServer& telemetry, const TickerServer& tick, const UserOptions& options);
			static void WriteGetTickerServer(TDF::Packet& packet, const TickerServer& tick);
			static void WriteUserOptions(TDF::Packet& packet, const UserOptions& options);

			// Requests
			static void FetchClientConfig(Request& request);
			static void Ping(Request& request);
			static void GetTelemetryServer(Request& request);
			static void PreAuth(Request& request);
			static void PostAuth(Request& request);
			static void UserSettingsSave(Request& request);
			static void UserSettingsLoadAll(Request& request);
			static void SetClientMetrics(Request& request);
	};
}

#endif
