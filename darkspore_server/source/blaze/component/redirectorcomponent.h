
#ifndef _BLAZE_COMPONENT_REDIRECTOR_HEADER
#define _BLAZE_COMPONENT_REDIRECTOR_HEADER

// Include
#include "blaze/component.h"

// Blaze
namespace Blaze {
	// RedirectorComponent
	class RedirectorComponent : public Component {
		public:
			enum : uint16_t { Id = 0x05 };

			uint16_t GetId() const override;

			std::string_view GetName() const override;
			std::string_view GetReplyPacketName(uint16_t command) const override;

			bool ParsePacket(Request& request) override;

		public:
			// Responses
			static void WriteServerInstanceInfo(TDF::Packet& packet, const std::string& host, uint16_t port);
			static void WriteServerAddressInfo(TDF::Packet& packet, const std::string& host, uint16_t port);

		private:
			static void GetServerInstance(Request& request);
	};
}

#endif
