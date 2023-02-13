
#ifndef _BLAZE_COMPONENT_ASSOCIATION_HEADER
#define _BLAZE_COMPONENT_ASSOCIATION_HEADER

// Include
#include "blaze/component.h"
#include "blaze/functions.h"

// Blaze
namespace Blaze {
	// AssociationListId
	enum AssociationListId {
		Ignore = 4,
		Friend = 5
	};

	// AssociationComponent
	class AssociationComponent : public Component {
		public:
			enum : uint16_t { Id = 0x19 };

			uint16_t GetId() const override;

			std::string_view GetName() const override;
			std::string_view GetReplyPacketName(uint16_t command) const override;
			std::string_view GetNotificationPacketName(uint16_t command) const override;

			bool ParsePacket(Request& request) override;

		public:
			// Responses
			static void UpdateListMembersResponse(TDF::Packet& packet, const std::vector<ListMemberInfo>& memberInfoList, const std::vector<ListMemberId>& removeList);
			static void WriteLists(TDF::Packet& packet, const std::vector<ListMembers>& listMembersData);

			// Notifications
			static void NotifyUpdateListMembership(Request& request, const std::vector<ListMemberInfoUpdate>& listMemberInfoUpdate, const ListIdentification& listId);

		private:
			static void AddUsersToList(Request& request);
			static void RemoveUsersFromList(Request& request);
			static void GetLists(Request& request);
	};
}

#endif
