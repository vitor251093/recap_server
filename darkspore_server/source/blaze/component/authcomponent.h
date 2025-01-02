
#ifndef _BLAZE_COMPONENT_AUTH_HEADER
#define _BLAZE_COMPONENT_AUTH_HEADER

// Include
#include "blaze/component.h"
#include "predefined.h"

// Blaze
namespace Blaze {
	// AuthComponent
	class AuthComponent : public Component {
		public:
			enum : uint16_t { Id = 0x01 };

			uint16_t GetId() const override;

			std::string_view GetName() const override;
			std::string_view GetReplyPacketName(uint16_t command) const override;
			std::string_view GetNotificationPacketName(uint16_t command) const override;

			bool ParsePacket(Request& request) override;

		private:
			// Responses
			static void WriteAuthToken(TDF::Packet& packet, const std::string& token);
			static void WriteLogin(TDF::Packet& packet, const SporeNet::UserPtr& user);
			static void WriteFullLogin(TDF::Packet& packet, const SporeNet::UserPtr& user);
			static void WriteTOSInfo(TDF::Packet& packet);
			static void WriteTermsAndConditions(TDF::Packet& packet);
			static void WritePrivacyPolicy(TDF::Packet& packet);

			// Requests
			static void GetAuthToken(Request& request);

			// Login
			static void Login(Request& request);
			static void SilentLogin(Request& request);
			static void ExpressLogin(Request& request);
			static void LoginPersona(Request& request);
			static void Logout(Request& request);

			// Terms and such
			static void AcceptTOS(Request& request);
			static void GetTOSInfo(Request& request);
			static void GetTermsAndConditions(Request& request);
			static void GetPrivacyPolicy(Request& request);
	};
}

#endif
