
#ifndef _BLAZE_COMPONENT_PLAYGROUPS_HEADER
#define _BLAZE_COMPONENT_PLAYGROUPS_HEADER

// Include
#include "blaze/component.h"

// Blaze
namespace Blaze {
	// PlaygroupsComponent
	class PlaygroupsComponent : public Component {
		public:
			enum : uint16_t { Id = 0x06 };

			uint16_t GetId() const override;

			std::string_view GetName() const override;
			std::string_view GetReplyPacketName(uint16_t command) const override;
			std::string_view GetNotificationPacketName(uint16_t command) const override;

			bool ParsePacket(Request& request) override;

		public:
			// Responses
			// static void SendSelectCategoryUpdates(Request& request, uint32_t viewId);

			// Notifications
			static void NotifyDestroyPlaygroup(Request& request, uint32_t playgroupId, uint32_t reason);
			static void NotifyJoinPlaygroup(Request& request);
			static void NotifyMemberJoinedPlaygroup(Request& request, uint32_t playgroupId);
			static void NotifyMemberRemovedFromPlaygroup(Request& request, uint32_t playgroupId, uint32_t reason);
			static void NotifyPlaygroupAttributesSet(Request& request, uint32_t playgroupId);
			static void NotifyMemberAttributesSet(Request& request, uint32_t playgroupId);
			static void NotifyLeaderChange(Request& request, uint32_t playgroupId);
			static void NotifyMemberPermissionsChange(Request& request, uint32_t playgroupId);
			static void NotifyJoinControlsChange(Request& request, uint32_t playgroupId);
			static void NotifyXboxSessionInfo(Request& request, uint32_t playgroupId);
			static void NotifyXboxSessionChange(Request& request, uint32_t playgroupId);

		private:
			static void CreatePlaygroup(Request& request);
			static void DestroyPlaygroup(Request& request);
			static void JoinPlaygroup(Request& request);
			static void LeavePlaygroup(Request& request);
			static void SetPlaygroupAttributes(Request& request);
			static void SetMemberAttributes(Request& request);
			static void KickPlaygroupMember(Request& request);
			static void SetPlaygroupJoinControls(Request& request);
			static void FinalizePlaygroupCreation(Request& request);
			static void LookupPlaygroupInfo(Request& request);
			static void ResetPlaygroupSession(Request& request);
	};
}

#endif
