
// Include
#include "playgroupscomponent.h"

#include "blaze/client.h"
#include "blaze/functions.h"
#include "utils/functions.h"

#include <iostream>

enum PacketID : uint16_t {
	CreatePlaygroup = 0x01,
	DestroyPlaygroup = 0x02,
	JoinPlaygroup = 0x03,
	LeavePlaygroup = 0x04,
	SetPlaygroupAttributes = 0x05,
	SetMemberAttributes = 0x06,
	KickPlaygroupMember = 0x07,
	SetPlaygroupJoinControls = 0x08,
	FinalizePlaygroupCreation = 0x09,
	LookupPlaygroupInfo = 0x0A,
	ResetPlaygroupSession = 0x0B,

	// Notifications
	NotifyDestroyPlaygroup = 0x32,
	NotifyJoinPlaygroup = 0x33,
	NotifyMemberJoinedPlaygroup = 0x34,
	NotifyMemberRemovedFromPlaygroup = 0x35,
	NotifyPlaygroupAttributesSet = 0x36,
	NotifyMemberAttributesSet = 0x45,
	NotifyLeaderChange = 0x4F,
	NotifyMemberPermissionsChange = 0x50,
	NotifyJoinControlsChange = 0x55,
	NotifyXboxSessionInfo = 0x56,
	NotifyXboxSessionChange = 0x57
};

// Blaze
namespace Blaze {
	// PlaygroupsComponent
	uint16_t PlaygroupsComponent::GetId() const {
		return Id;
	}

	std::string_view PlaygroupsComponent::GetName() const {
		return "Playgroups";
	}

	std::string_view PlaygroupsComponent::GetReplyPacketName(uint16_t command) const {
		switch (static_cast<PacketID>(command)) {
			case PacketID::CreatePlaygroup: return "createPlaygroup";
			case PacketID::DestroyPlaygroup: return "destroyPlaygroup";
			case PacketID::JoinPlaygroup: return "joinPlaygroup";
			case PacketID::LeavePlaygroup: return "leavePlaygroup";
			case PacketID::SetPlaygroupAttributes: return "setPlaygroupAttributes";
			case PacketID::SetMemberAttributes: return "setMemberAttributes";
			case PacketID::KickPlaygroupMember: return "kickPlaygroupMember";
			case PacketID::SetPlaygroupJoinControls: return "setPlaygroupJoinControls";
			case PacketID::FinalizePlaygroupCreation: return "finalizePlaygroupCreation";
			case PacketID::LookupPlaygroupInfo: return "lookupPlaygroupInfo";
			case PacketID::ResetPlaygroupSession: return "resetPlaygroupSession";

			default: return "";
		}
	}

	std::string_view PlaygroupsComponent::GetNotificationPacketName(uint16_t command) const {
		switch (static_cast<PacketID>(command)) {
			case PacketID::NotifyDestroyPlaygroup: return "NotifyDestroyPlaygroup";
			case PacketID::NotifyJoinPlaygroup: return "NotifyJoinPlaygroup";
			case PacketID::NotifyMemberJoinedPlaygroup: return "NotifyMemberJoinedPlaygroup";
			case PacketID::NotifyMemberRemovedFromPlaygroup: return "NotifyMemberRemovedFromPlaygroup";
			case PacketID::NotifyPlaygroupAttributesSet: return "NotifyPlaygroupAttributesSet";
			case PacketID::NotifyMemberAttributesSet: return "NotifyMemberAttributesSet";
			case PacketID::NotifyLeaderChange: return "NotifyLeaderChange";
			case PacketID::NotifyMemberPermissionsChange: return "NotifyMemberPermissionsChange";
			case PacketID::NotifyJoinControlsChange: return "NotifyJoinControlsChange";
			case PacketID::NotifyXboxSessionInfo: return "NotifyXboxSessionInfo";
			case PacketID::NotifyXboxSessionChange: return "NotifyXboxSessionChange";

			default: return "";
		}
	}

	bool PlaygroupsComponent::ParsePacket(Request& request) {
		switch (request.get_command()) {
			case PacketID::CreatePlaygroup:
				CreatePlaygroup(request);
				break;

			case PacketID::DestroyPlaygroup:
				DestroyPlaygroup(request);
				break;

			case PacketID::JoinPlaygroup:
				JoinPlaygroup(request);
				break;

			case PacketID::LeavePlaygroup:
				LeavePlaygroup(request);
				break;

			case PacketID::SetPlaygroupAttributes:
				SetPlaygroupAttributes(request);
				break;

			case PacketID::SetMemberAttributes:
				SetMemberAttributes(request);
				break;

			case PacketID::KickPlaygroupMember:
				KickPlaygroupMember(request);
				break;

			case PacketID::SetPlaygroupJoinControls:
				SetPlaygroupJoinControls(request);
				break;

			case PacketID::FinalizePlaygroupCreation:
				FinalizePlaygroupCreation(request);
				break;

			case PacketID::LookupPlaygroupInfo:
				LookupPlaygroupInfo(request);
				break;

			case PacketID::ResetPlaygroupSession:
				ResetPlaygroupSession(request);
				break;

			default:
				return false;
		}

		return true;
	}

	void PlaygroupsComponent::NotifyDestroyPlaygroup(Request& request, uint32_t playgroupId, uint32_t reason) {
		TDF::Packet packet;
		packet.put_integer("PGID", playgroupId);
		packet.put_integer("REAS", reason);

		request.notify(packet, Id, PacketID::NotifyDestroyPlaygroup);
	}

	void PlaygroupsComponent::NotifyJoinPlaygroup(Request& request) {
		const auto& user = request.get_user();
		if (!user) {
			return;
		}

		auto userId = user->get_id();

		PlaygroupInfo info;
		info.enbv = true;
		info.hostSlotId = 0;
		info.state = PlaygroupJoinState::Open;
		info.pres = PresenceMode::Standard;
		info.ownerId = userId;
		info.memberLimit = 1;
		info.ntop = GameNetworkTopology::ClientServerDedicated;
		info.playgroupId = 1;
		info.ukey = "what";
		info.uprs = true;
		info.name = "Test playgroup";
		info.uuid = "71bc4bdb-82ec-494d-8d75-ca5123b827ac";

		TDF::Packet packet;
		packet.push_struct("INFO");
		info.Write(packet);
		packet.pop();

		packet.push_list("MLST", TDF::Type::Struct);
		packet.pop();

		packet.put_integer("USER", userId);

		request.notify(packet, Id, PacketID::NotifyJoinPlaygroup);
	}

	void PlaygroupsComponent::NotifyMemberJoinedPlaygroup(Request& request, uint32_t playgroupId) {
		PlaygroupMemberInfo memberInfo;
		memberInfo.jtim = 0;
		memberInfo.permissions = 0;
		memberInfo.slot = 0;

		UserIdentification& memberUser = memberInfo.user;
		memberUser.id = 0;
		memberUser.localization = 0;
		memberUser.name = "Unknown";

		TDF::Packet packet;
		packet.push_struct("MEMB");
		memberInfo.Write(packet);
		packet.pop();

		packet.put_integer("PGID", playgroupId);

		request.notify(packet, Id, PacketID::NotifyMemberJoinedPlaygroup);
	}

	void PlaygroupsComponent::NotifyMemberRemovedFromPlaygroup(Request& request, uint32_t playgroupId, uint32_t reason) {
		TDF::Packet packet;
		packet.put_integer("MLST", 0);
		packet.put_integer("PGID", playgroupId);
		packet.put_integer("REAS", reason);

		request.notify(packet, Id, PacketID::NotifyMemberRemovedFromPlaygroup);
	}

	void PlaygroupsComponent::NotifyPlaygroupAttributesSet(Request& request, uint32_t playgroupId) {
		TDF::Packet packet;
		packet.push_map("ATTR", TDF::Type::String, TDF::Type::String);
		// playgroup attributes
		packet.pop();

		packet.put_integer("PGID", playgroupId);

		request.notify(packet, Id, PacketID::NotifyPlaygroupAttributesSet);
	}

	void PlaygroupsComponent::NotifyMemberAttributesSet(Request& request, uint32_t playgroupId) {
		TDF::Packet packet;
		packet.push_map("ATTR", TDF::Type::String, TDF::Type::String);
		// member attributes
		packet.pop();

		packet.put_integer("EID", 0); // member id?
		packet.put_integer("PGID", playgroupId);

		request.notify(packet, Id, PacketID::NotifyMemberAttributesSet);
	}

	void PlaygroupsComponent::NotifyLeaderChange(Request& request, uint32_t playgroupId) {
		TDF::Packet packet;
		packet.put_integer("HSID", 0); // new host(leader) slot id?
		packet.put_integer("LID", 0); // Leader ID?
		packet.put_integer("PGID", playgroupId);

		request.notify(packet, Id, PacketID::NotifyLeaderChange);
	}

	void PlaygroupsComponent::NotifyMemberPermissionsChange(Request& request, uint32_t playgroupId) {
		TDF::Packet packet;
		packet.put_integer("LID", 0);
		packet.put_integer("PERM", 0);
		packet.put_integer("PGID", playgroupId);

		request.notify(packet, Id, PacketID::NotifyMemberPermissionsChange);
	}

	void PlaygroupsComponent::NotifyJoinControlsChange(Request& request, uint32_t playgroupId) {
		TDF::Packet packet;
		packet.put_integer("OPEN", PlaygroupJoinState::Open);
		packet.put_integer("PGID", playgroupId);

		request.notify(packet, Id, PacketID::NotifyJoinControlsChange);
	}

	void PlaygroupsComponent::NotifyXboxSessionInfo(Request& request, uint32_t playgroupId) {
		TDF::Packet packet;
		packet.put_integer("PGID", playgroupId);
		packet.put_integer("PRES", PresenceMode::Standard);
		packet.put_blob("XNNC", nullptr, 0);
		packet.put_blob("XSES", nullptr, 0);

		request.notify(packet, Id, PacketID::NotifyXboxSessionInfo);
	}

	void PlaygroupsComponent::NotifyXboxSessionChange(Request& request, uint32_t playgroupId) {
		NotifyXboxSessionInfo(request, playgroupId);
	}

	void PlaygroupsComponent::CreatePlaygroup(Request& request) {
		// Read "PlaygroupInfo" struct
	}

	void PlaygroupsComponent::DestroyPlaygroup(Request& request) {
		//
	}

	void PlaygroupsComponent::JoinPlaygroup(Request& request) {
		//
	}

	void PlaygroupsComponent::LeavePlaygroup(Request& request) {
		//
	}

	void PlaygroupsComponent::SetPlaygroupAttributes(Request& request) {
		//
	}

	void PlaygroupsComponent::SetMemberAttributes(Request& request) {
		//
	}

	void PlaygroupsComponent::KickPlaygroupMember(Request& request) {
		//
	}

	void PlaygroupsComponent::SetPlaygroupJoinControls(Request& request) {
		//
	}

	void PlaygroupsComponent::FinalizePlaygroupCreation(Request& request) {
		//
	}

	void PlaygroupsComponent::LookupPlaygroupInfo(Request& request) {
		//
	}

	void PlaygroupsComponent::ResetPlaygroupSession(Request& request) {
		//
	}
}
