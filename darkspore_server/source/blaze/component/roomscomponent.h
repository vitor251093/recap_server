
#ifndef _BLAZE_COMPONENT_ROOMS_HEADER
#define _BLAZE_COMPONENT_ROOMS_HEADER

// Include
#include "blaze/component.h"
#include "predefined.h"

// Blaze
namespace Blaze {
	// RoomsComponent
	class RoomsComponent : public Component {
		public:
			enum : uint16_t { Id = 0x15 };

			uint16_t GetId() const override;

			std::string_view GetName() const override;
			std::string_view GetReplyPacketName(uint16_t command) const override;
			std::string_view GetNotificationPacketName(uint16_t command) const override;

			bool ParsePacket(Request& request) override;

		public:
			// Notifications
			static void NotifyRoomViewUpdated(Request& request, uint32_t viewId);
			static void NotifyRoomViewAdded(Request& request, uint32_t viewId);
			static void NotifyRoomViewRemoved(Request& request, uint32_t viewId);
			static void NotifyRoomCategoryUpdated(Request& request, uint32_t categoryId);
			static void NotifyRoomCategoryAdded(Request& request, uint32_t categoryId);
			static void NotifyRoomCategoryRemoved(Request& request, uint32_t categoryId);
			static void NotifyRoomUpdated(Request& request, uint32_t roomId);
			static void NotifyRoomAdded(Request& request, uint32_t roomId);
			static void NotifyRoomRemoved(Request& request, uint32_t roomId);
			static void NotifyRoomPopulationUpdated(Request& request);
			static void NotifyRoomMemberJoined(Request& request, uint32_t roomId, uint32_t memberId);
			static void NotifyRoomMemberLeft(Request& request, uint32_t roomId, uint32_t memberId);
			static void NotifyRoomMemberUpdated(Request& request, uint32_t roomId, uint32_t memberId);
			static void NotifyRoomKick(Request& request, uint32_t roomId, uint32_t memberId);
			static void NotifyRoomHostTransfer(Request& request, uint32_t roomId, uint32_t memberId);
			static void NotifyRoomAttributesSet(Request& request, uint32_t roomId);

		private:
			// Responses
			void WriteSelectCategoryUpdates(TDF::Packet& packet, uint32_t viewId);
			void WriteJoinRoom(TDF::Packet& packet, const SporeNet::RoomPtr& room, int64_t userId);

			// Requests
			void SelectViewUpdates(Request& request);
			void SelectCategoryUpdates(Request& request);
			void JoinRoom(Request& request);
			void SelectPseudoRoomUpdates(Request& request);
	};
}

#endif
