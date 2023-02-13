
#ifndef _BLAZE_COMPONENT_HEADER
#define _BLAZE_COMPONENT_HEADER

// Include
#include "blaze/functions.h"
#include <string_view>

// Blaze
namespace Blaze {
	class Request;

	// Component
	class Component {
		public:
			virtual uint16_t GetId() const;

			virtual std::string_view GetName() const;
			virtual std::string_view GetReplyPacketName(uint16_t command) const;
			virtual std::string_view GetNotificationPacketName(uint16_t command) const;

			virtual bool ParsePacket(Request& request) = 0;
	};

	// ComponentManager
	class ComponentManager {
		public:
			static Component* Get(uint16_t id);
	};
}

#endif
