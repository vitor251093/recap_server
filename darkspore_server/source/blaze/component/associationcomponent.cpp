
// Include
#include "associationcomponent.h"
#include "playgroupscomponent.h"

#include "blaze/client.h"
#include "blaze/functions.h"
#include "utils/functions.h"

#include <iostream>

/*
	Packet IDs
		0x01 = AddUsersToList
		0x02 = RemoveUsersFromList
		0x03 = ClearLists
		0x04 = SetUsersToList
		0x05 = GetListForUser
		0x06 = GetLists
		0x07 = SubscribeToLists
		0x08 = UnsubscribeFromLists

	Notification Packet IDs
		0x01 = UpdateListMembership

	Blaze fields
		LMAP
			list of ListMember

		ALST
			list of ListInfo

		ListMemberInfoUpdate
			LMID = 0x18
			LUPT = 0x1C (ListUpdateType)

		ListMemberInfo
			LMID = 0x18
			TIME = 0x34

		ListMemberId
			BLID = 0x34
			PNAM = 0x24
			XREF = 0x30
			XTYP = 0x1C

		ListMember
			INFO = 0x18
			MEML = 0x58
			OFRC = 0x38
			TOCT = 0x38

		ListInfo
			BOID = 0x08
			FLGS = 0x28
			LID = 0x18
			LMS = 0x38
			PRID = 0x38

		LID
			LNM = 0x24
			TYPE = 0x38

		BIDL
			list of structs with {
				ListMemberInfoUpdate ()
			}

		PresenceInfo
			GRP = 0x40
			LVL = 0x38
			STAT = 0x1C
			XTRA = 0x40

		UpdateListWithMembersRequest
			BIDL = 0x58
			LID = 0x18

	Request Packets
		GetLists
			ALST = 0x58
			MXRC = 0x38
			OFRC = 0x38
*/

enum PacketID : uint16_t {
	AddUsersToList = 0x01,
	RemoveUsersFromList = 0x02,
	ClearLists = 0x03,
	SetUsersToList = 0x04,
	GetListForUser = 0x05,
	GetLists = 0x06,
	SubscribeToLists = 0x07,
	UnsubscribeFromLists = 0x08,

	// Notifications
	NotifyUpdateListMembership = 0x01,
};

// Blaze
namespace Blaze {
	// AssociationComponent
	uint16_t AssociationComponent::GetId() const {
		return Id;
	}

	std::string_view AssociationComponent::GetName() const {
		return "AssociationLists";
	}

	std::string_view AssociationComponent::GetReplyPacketName(uint16_t command) const {
		switch (static_cast<PacketID>(command)) {
			case PacketID::AddUsersToList: return "addUsersToList";
			case PacketID::RemoveUsersFromList: return "removeUsersFromList";
			case PacketID::ClearLists: return "clearLists";
			case PacketID::SetUsersToList: return "setUsersToList";
			case PacketID::GetListForUser: return "getListForUser";
			case PacketID::GetLists: return "getLists";
			case PacketID::SubscribeToLists: return "subscribeToLists";
			case PacketID::UnsubscribeFromLists: return "unsubscribeFromLists";

			default: return "";
		}
	}

	std::string_view AssociationComponent::GetNotificationPacketName(uint16_t command) const {
		switch (static_cast<PacketID>(command)) {
			case PacketID::NotifyUpdateListMembership: return "NotifyUpdateListMembership";

			default: return "";
		}
	}

	bool AssociationComponent::ParsePacket(Request& request) {
		switch (request.get_command()) {
			case PacketID::AddUsersToList:
				AddUsersToList(request);
				break;

			case PacketID::RemoveUsersFromList:
				RemoveUsersFromList(request);
				break;

			case PacketID::GetLists:
				GetLists(request);
				break;

			default:
				return false;
		}

		return true;
	}

	void AssociationComponent::UpdateListMembersResponse(TDF::Packet& packet, const std::vector<ListMemberInfo>& memberInfoList, const std::vector<ListMemberId>& removeList) {
		if (!memberInfoList.empty()) {
			packet.push_list("LMID", TDF::Type::Struct);
			for (const auto& memberInfo : memberInfoList) {
				packet.push_struct("");
				memberInfo.Write(packet);
				packet.pop();
			}
			packet.pop();
		}

		if (!removeList.empty()) {
			packet.push_list("REM", TDF::Type::Struct);
			for (const auto& memberId : removeList) {
				packet.push_struct("");
				memberId.Write(packet);
				packet.pop();
			}
			packet.pop();
		}
	}

	void AssociationComponent::WriteLists(TDF::Packet& packet, const std::vector<ListMembers>& listMembersData) {
		/*
		4 = ignore list
		5 = friend list
		*/
		packet.push_list("LMAP", TDF::Type::Struct);
		for (const auto& listMembers : listMembersData) {
			packet.push_struct("");
			listMembers.Write(packet);
			packet.pop();
		}
		packet.pop();
	}

	void AssociationComponent::NotifyUpdateListMembership(Request& request, const std::vector<ListMemberInfoUpdate>& listMemberInfoUpdate, const ListIdentification& listId) {
		if (listMemberInfoUpdate.empty()) {
			return;
		}

		const auto& user = request.get_user();
		if (!user) {
			return;
		}

		TDF::Packet packet;
		packet.push_list("BIDL", TDF::Type::Struct);
		for (const auto& memberInfoUpdate : listMemberInfoUpdate) {
			packet.push_struct("");
			memberInfoUpdate.Write(packet);
			packet.pop();
		}
		packet.pop();

		packet.push_struct("LID");
		listId.Write(packet);
		packet.pop();

		request.notify(packet, Id, PacketID::NotifyUpdateListMembership);
	}

	void AssociationComponent::AddUsersToList(Request& request) {
		// Read request data
		std::vector<ListMemberInfoUpdate> updateList;
		std::vector<ListMemberInfo> memberInfoList;
		if (auto it = request.find("BIDL"); it != request.end()) {
			auto timestamp = utils::get_unix_time();
			for (const auto& child : it->value["_Content"].GetArray()) {
				decltype(auto) memberInfo = memberInfoList.emplace_back();
				memberInfo.id.Read(child);
				memberInfo.time = timestamp;

				decltype(auto) memberInfoUpdate = updateList.emplace_back();
				memberInfoUpdate.info = memberInfo;
				memberInfoUpdate.type = ListUpdateType::Add;
			}
		}

		ListIdentification listId;
		listId.Read(request["LID"]);

		// Send reply
		TDF::Packet packet;
		UpdateListMembersResponse(packet, memberInfoList, {});

		request.reply(packet);

		// Send update notification
		NotifyUpdateListMembership(request, updateList, listId);
	}

	void AssociationComponent::RemoveUsersFromList(Request& request) {
		// Read request data
		std::vector<ListMemberInfoUpdate> updateList;
		std::vector<ListMemberId> removeList;
		if (auto it = request.find("BIDL"); it != request.end()) {
			auto timestamp = utils::get_unix_time();
			for (const auto& child : it->value["_Content"].GetArray()) {
				decltype(auto) memberId = removeList.emplace_back();
				memberId.Read(child);

				decltype(auto) memberInfoUpdate = updateList.emplace_back();
				memberInfoUpdate.info.id = memberId;
				memberInfoUpdate.info.time = timestamp;
				memberInfoUpdate.type = ListUpdateType::Remove;
			}
		}

		ListIdentification listId;
		listId.Read(request["LID"]);

		// Send reply
		TDF::Packet packet;
		UpdateListMembersResponse(packet, {}, removeList);

		request.reply(packet);

		// Send update notification
		NotifyUpdateListMembership(request, updateList, listId);
	}

	void AssociationComponent::GetLists(Request& request) {
		const auto& user = request.get_user();
		if (!user) {
			return;
		}

		uint32_t mxrc = request["MXRC"].GetUint();
		uint32_t ofrc = request["OFRC"].GetUint();

		std::vector<ListMembers> listMembersData;
		if (auto it = request.find("ALST"); it != request.end()) {
			for (const auto& child : it->value["_Content"].GetArray()) {
				decltype(auto) listMembers = listMembersData.emplace_back();
				listMembers.info.Read(child);
				listMembers.ofrc = ofrc;
				listMembers.toct = 0; // unknown so far, some sort of id?

				auto type = listMembers.info.identification.type;
				if (type == 4) {
					// Ignore list
					decltype(auto) member = listMembers.memberList.emplace_back();
					member.id.id = user->get_id();
					member.id.name = user->get_name();
					member.time = 0;
				} else if (type == 5) {
					// Friend list
					{
						decltype(auto) member = listMembers.memberList.emplace_back();
						member.id.id = 100;
						member.id.name = "Dalkon";
						member.time = 0;
					}
					{
						decltype(auto) member = listMembers.memberList.emplace_back();
						member.id.id = 102;
						member.id.name = "test";
						member.time = 0;
					}
				}
			}
		}

		TDF::Packet packet;
		WriteLists(packet, listMembersData);

		request.reply(packet);

		// PlaygroupsComponent::NotifyJoinPlaygroup(client);
		// NotifyUpdateListMembership(client);
	}
}
