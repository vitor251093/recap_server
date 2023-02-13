
#ifndef _BLAZE_COMPONENT_USERSESSION_HEADER
#define _BLAZE_COMPONENT_USERSESSION_HEADER

// Include
#include "predefined.h"

#include "blaze/component.h"
#include "blaze/functions.h"

// Blaze
namespace Blaze {
	// UserSessionComponent
	class UserSessionComponent : public Component {
		public:
			enum : uint16_t { Id = 0x7802 };

			uint16_t GetId() const override;

			std::string_view GetName() const override;
			std::string_view GetReplyPacketName(uint16_t command) const override;
			std::string_view GetNotificationPacketName(uint16_t command) const override;

			bool ParsePacket(Request& request) override;

		public:
			static void NotifyUserSessionExtendedDataUpdate(Request& request, int64_t userId, const UserSessionExtendedData& extendedData);
			static void NotifyUserAdded(Request& request, const SporeNet::UserPtr& user);
			static void NotifyUserUpdated(Request& request, const SporeNet::UserPtr& user, SessionState state);

		private:
			static void LookupUser(Request& request);

			static void UpdateNetworkInfo(Request& request);
			static void UpdateUserSessionClientData(Request& request);
	};
}

#endif
