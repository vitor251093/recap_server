
#ifndef _BLAZE_COMPONENT_MESSAGING_HEADER
#define _BLAZE_COMPONENT_MESSAGING_HEADER

// Include
#include "blaze/component.h"
#include "blaze/functions.h"

// Blaze
namespace Blaze {
	// MessagingComponent
	class MessagingComponent : public Component {
		public:
			enum : uint16_t { Id = 0x0F };

			uint16_t GetId() const override;

			std::string_view GetName() const override;
			std::string_view GetReplyPacketName(uint16_t command) const override;
			std::string_view GetNotificationPacketName(uint16_t command) const override;

			bool ParsePacket(Request& request) override;

		public:
			// Responses
			static void OnSendMessageResponse(Request& request);

			// Notifications
			static void NotifyMessage(Request& request, const ClientMessage& clientMessage);

		private:
			static void OnSendMessage(Request& request);
			static void OnFetchMessages(Request& request);
			static void OnPurgeMessages(Request& request);
			static void OnTouchMessages(Request& request);
			static void OnGetMessages(Request& request);
	};
}

#endif
