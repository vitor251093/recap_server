
// Include
#include "roomscomponent.h"

#include "sporenet/instance.h"
#include "sporenet/room.h"

#include "blaze/client.h"
#include "utils/functions.h"

#include <iostream>

/*
	"PRESENCESTATE_OFFLINE" : "Offline",
	"PRESENCESTATE_ONLINE_WEB" : "Web",
	"PRESENCESTATE_ONLINE_CLIENT" : "Online - Lobby",
	"PRESENCESTATE_ONLINE_CLIENT_MODE1":"Online - Collection",
	"PRESENCESTATE_ONLINE_CLIENT_MODE2":"Online - Navigation",
	"PRESENCESTATE_ONLINE_CLIENT_MODE3":"Online - Chain",
	"PRESENCESTATE_ONLINE_CLIENT_MODE4":"Online - Arena",
	"PRESENCESTATE_ONLINE_CLIENT_MODE5":"Online - Editor"
*/

/*
	Blaze fields
		RoomReplicationContext
			SEID = 0x38
			UPRE = 0x1C
			USID = 0x34
			VWID = 0x38

		RoomViewData
			DISP = 0x24
			GMET = 0x54
			META = 0x54
			MXRM = 0x38
			NAME = 0x24
			USRM = 0x38
			VWID = 0x38

		RoomCategoryData
			CAPA = 0x38
			CMET = 0x54
			CRIT = 0x54
			CTID = 0x38
			DESC = 0x24
			DISP = 0x24
			DISR = 0x24
			EMAX = 0x38
			EPCT = 0x40
			FLAG = 0x28
			GMET = 0x54
			LOCL = 0x24
			NAME = 0x24
			NEXP = 0x40
			PASS = 0x24
			UCRT = 0x50
			VWID = 0x38

		RoomData
			AREM = 0x50
			ATTR = 0x54
			BLST = 0x58
			CAP = 0x3C
			CNAM = 0x24
			CRET = 0x34
			CRIT = 0x54
			CRTM = 0x38
			CTID = 0x38
			ENUM = 0x38
			HNAM = 0x24
			HOST = 0x34
			NAME = 0x24
			POPU = 0x38
			PSWD = 0x24
			PVAL = 0x24
			RMID = 0x38
			UCRT = 0x50
*/

enum PacketID : uint16_t {
	SelectViewUpdates = 0x0A,
	SelectCategoryUpdates = 0x0B,
	JoinRoom = 0x14,
	LeaveRoom = 0x15,
	KickUser = 0x1F,
	TransferRoomHost = 0x28,
	CreateRoomCategory = 0x64,
	RemoveRoomCategory = 0x65,
	CreateRoom = 0x66,
	RemoveRoom = 0x67,
	ClearBannedUsers = 0x68,
	UnbanUser = 0x69,
	GetViews = 0x6D,
	CreateScheduledCategory = 0x6E,
	DeleteScheduledCategory = 0x6F,
	GetSchedulesCategories = 0x70,
	LookupRoomData = 0x78,
	ListBannedUsers = 0x7A,
	SetRoomAttributes = 0x82,
	CheckEntryCriteria = 0x8C,
	ToggleJoinedRoomNotifications = 0x96,
	SelectPseudoRoomUpdates = 0xA0,

	// Notifications
	NotifyRoomViewUpdated = 0x0A,
	NotifyRoomViewAdded = 0x0B,
	NotifyRoomViewRemoved = 0x0C,
	NotifyRoomCategoryUpdated = 0x14,
	NotifyRoomCategoryAdded = 0x15,
	NotifyRoomCategoryRemoved = 0x16,
	NotifyRoomUpdated = 0x1E,
	NotifyRoomAdded = 0x1F,
	NotifyRoomRemoved = 0x20,
	NotifyRoomPopulationUpdated = 0x28,
	NotifyRoomMemberJoined = 0x32,
	NotifyRoomMemberLeft = 0x33,
	NotifyRoomMemberUpdated = 0x34,
	NotifyRoomKick = 0x3C,
	NotifyRoomHostTransfer = 0x46,
	NotifyRoomAttributesSet = 0x50
};

// Blaze
namespace Blaze {
	// RoomsComponent
	uint16_t RoomsComponent::GetId() const {
		return Id;
	}

	std::string_view RoomsComponent::GetName() const {
		return "Rooms";
	}

	std::string_view RoomsComponent::GetReplyPacketName(uint16_t command) const {
		switch (static_cast<PacketID>(command)) {
			case PacketID::SelectViewUpdates: return "selectViewUpdates";
			case PacketID::SelectCategoryUpdates: return "selectCategoryUpdates";
			case PacketID::JoinRoom: return "joinRoom";
			case PacketID::LeaveRoom: return "leaveRoom";
			case PacketID::KickUser: return "kickUser";
			case PacketID::TransferRoomHost: return "transferRoomHost";
			case PacketID::CreateRoomCategory: return "createRoomCategory";
			case PacketID::RemoveRoomCategory: return "removeRoomCategory";
			case PacketID::CreateRoom: return "createRoom";
			case PacketID::RemoveRoom: return "removeRoom";
			case PacketID::ClearBannedUsers: return "clearBannedUsers";
			case PacketID::UnbanUser: return "unbanUser";
			case PacketID::GetViews: return "getViews";
			case PacketID::CreateScheduledCategory: return "createScheduledCategory";
			case PacketID::DeleteScheduledCategory: return "deleteScheduledCategory";
			case PacketID::GetSchedulesCategories: return "getSchedulesCategories";
			case PacketID::LookupRoomData: return "lookupRoomData";
			case PacketID::ListBannedUsers: return "listBannedUsers";
			case PacketID::SetRoomAttributes: return "setRoomAttributes";
			case PacketID::CheckEntryCriteria: return "checkEntryCriteria";
			case PacketID::ToggleJoinedRoomNotifications: return "toggleJoinedRoomNotifications";
			case PacketID::SelectPseudoRoomUpdates: return "selectPseudoRoomUpdates";

			default: return "";
		}
	}

	std::string_view RoomsComponent::GetNotificationPacketName(uint16_t command) const {
		switch (static_cast<PacketID>(command)) {
			case PacketID::NotifyRoomViewUpdated: return "NotifyRoomViewUpdated";
			case PacketID::NotifyRoomViewAdded: return "NotifyRoomViewAdded";
			case PacketID::NotifyRoomViewRemoved: return "NotifyRoomViewRemoved";
			case PacketID::NotifyRoomCategoryUpdated: return "NotifyRoomCategoryUpdated";
			case PacketID::NotifyRoomCategoryAdded: return "NotifyRoomCategoryAdded";
			case PacketID::NotifyRoomCategoryRemoved: return "NotifyRoomCategoryRemoved";
			case PacketID::NotifyRoomUpdated: return "NotifyRoomUpdated";
			case PacketID::NotifyRoomAdded: return "NotifyRoomAdded";
			case PacketID::NotifyRoomRemoved: return "NotifyRoomRemoved";
			case PacketID::NotifyRoomPopulationUpdated: return "NotifyRoomPopulationUpdated";
			case PacketID::NotifyRoomMemberJoined: return "NotifyRoomMemberJoined";
			case PacketID::NotifyRoomMemberLeft: return "NotifyRoomMemberLeft";
			case PacketID::NotifyRoomMemberUpdated: return "NotifyRoomMemberUpdated";
			case PacketID::NotifyRoomKick: return "NotifyRoomKick";
			case PacketID::NotifyRoomHostTransfer: return "NotifyRoomHostTransfer";
			case PacketID::NotifyRoomAttributesSet: return "NotifyRoomAttributesSet";

			default: return "";
		}
	}

	bool RoomsComponent::ParsePacket(Request& request) {
		switch (request.get_command()) {
			case PacketID::SelectViewUpdates:
				SelectViewUpdates(request);
				break;

			case PacketID::SelectCategoryUpdates:
				SelectCategoryUpdates(request);
				break;

			case PacketID::JoinRoom:
				JoinRoom(request);
				break;

			case PacketID::SelectPseudoRoomUpdates:
				SelectPseudoRoomUpdates(request);
				break;

			default:
				return false;
		}

		return true;
	}

	// Blaze functions
	void RoomsComponent::NotifyRoomViewUpdated(Request& request, uint32_t viewId) {
		const auto& roomView = SporeNet::Get().GetRoomManager().GetRoomView(viewId);
		if (roomView) {
			TDF::Packet packet;
			roomView->WriteTo(packet);

			request.notify(packet, Id, PacketID::NotifyRoomViewUpdated);
		}
	}
	
	void RoomsComponent::NotifyRoomViewAdded(Request& request, uint32_t viewId) {
		const auto& roomView = SporeNet::Get().GetRoomManager().GetRoomView(viewId);
		if (roomView) {
			TDF::Packet packet;
			roomView->WriteTo(packet);

			request.notify(packet, Id, PacketID::NotifyRoomViewAdded);
		}
	}

	void RoomsComponent::NotifyRoomViewRemoved(Request& request, uint32_t viewId) {
		TDF::Packet packet;
		packet.put_integer("VWID", viewId);

		request.notify(packet, Id, PacketID::NotifyRoomViewRemoved);
	}

	void RoomsComponent::NotifyRoomCategoryUpdated(Request& request, uint32_t categoryId) {
		const auto& roomCategory = SporeNet::Get().GetRoomManager().GetRoomCategory(categoryId);
		if (roomCategory) {
			TDF::Packet packet;
			roomCategory->WriteTo(packet);

			request.notify(packet, Id, PacketID::NotifyRoomCategoryUpdated);
		}
	}

	void RoomsComponent::NotifyRoomCategoryAdded(Request& request, uint32_t categoryId) {
		const auto& roomCategory = SporeNet::Get().GetRoomManager().GetRoomCategory(categoryId);
		if (roomCategory) {
			TDF::Packet packet;
			roomCategory->WriteTo(packet);

			request.notify(packet, Id, PacketID::NotifyRoomCategoryAdded);
		}
	}

	void RoomsComponent::NotifyRoomCategoryRemoved(Request& request, uint32_t categoryId) {
		TDF::Packet packet;
		packet.put_integer("CTID", categoryId);

		request.notify(packet, Id, PacketID::NotifyRoomCategoryRemoved);
	}

	void RoomsComponent::NotifyRoomUpdated(Request& request, uint32_t roomId) {
		const auto& room = SporeNet::Get().GetRoomManager().GetRoom(roomId);
		if (room) {
			TDF::Packet packet;
			room->WriteTo(packet);

			request.notify(packet, Id, PacketID::NotifyRoomUpdated);
		}
	}

	void RoomsComponent::NotifyRoomAdded(Request& request, uint32_t roomId) {
		const auto& room = SporeNet::Get().GetRoomManager().GetRoom(roomId);
		if (room) {
			TDF::Packet packet;
			room->WriteTo(packet);

			request.notify(packet, Id, PacketID::NotifyRoomAdded);
		}
	}

	void RoomsComponent::NotifyRoomRemoved(Request& request, uint32_t roomId) {
		TDF::Packet packet;
		packet.put_integer("RMID", roomId);

		request.notify(packet, Id, PacketID::NotifyRoomRemoved);
	}

	void RoomsComponent::NotifyRoomPopulationUpdated(Request& request) {
		TDF::Packet packet;

		packet.push_map("POPA", TDF::Type::String, TDF::Type::String);
		// administrator population?
		packet.pop();

		packet.push_map("POPM", TDF::Type::String, TDF::Type::String);
		// member population?
		packet.pop();

		request.notify(packet, Id, PacketID::NotifyRoomPopulationUpdated);
	}

	void RoomsComponent::NotifyRoomMemberJoined(Request& request, uint32_t roomId, uint32_t memberId) {
		TDF::Packet packet;
		packet.put_integer("BZID", memberId);
		packet.put_integer("RMID", roomId);

		request.notify(packet, Id, PacketID::NotifyRoomMemberJoined);
	}

	void RoomsComponent::NotifyRoomMemberLeft(Request& request, uint32_t roomId, uint32_t memberId) {
		TDF::Packet packet;
		packet.put_integer("MBID", memberId);
		packet.put_integer("RMID", roomId);

		request.notify(packet, Id, PacketID::NotifyRoomMemberLeft);
	}

	void RoomsComponent::NotifyRoomMemberUpdated(Request& request, uint32_t roomId, uint32_t memberId) {
		TDF::Packet packet;
		packet.put_integer("BZID", memberId);
		packet.put_integer("RMID", roomId);

		request.notify(packet, Id, PacketID::NotifyRoomMemberUpdated);
	}

	void RoomsComponent::NotifyRoomKick(Request& request, uint32_t roomId, uint32_t memberId) {
		TDF::Packet packet;
		packet.put_integer("MBID", memberId);
		packet.put_integer("RMID", roomId);

		request.notify(packet, Id, PacketID::NotifyRoomKick);
	}

	void RoomsComponent::NotifyRoomHostTransfer(Request& request, uint32_t roomId, uint32_t memberId) {
		TDF::Packet packet;
		packet.put_integer("MBID", memberId);
		packet.put_integer("RMID", roomId);

		request.notify(packet, Id, PacketID::NotifyRoomHostTransfer);
	}

	void RoomsComponent::NotifyRoomAttributesSet(Request& request, uint32_t roomId) {
		// TODO: add a map<string, string> for attributes
		TDF::Packet packet;

		packet.push_map("ATTR", TDF::Type::String, TDF::Type::String);
		// attributes
		packet.pop();

		packet.put_integer("RMID", roomId);

		request.notify(packet, Id, PacketID::NotifyRoomAttributesSet);
	}

	void RoomsComponent::WriteSelectCategoryUpdates(TDF::Packet& packet, uint32_t viewId) {
		packet.put_integer("VWID", viewId);
	}

	void RoomsComponent::WriteJoinRoom(TDF::Packet& packet, const SporeNet::RoomPtr& room, int64_t userId) {
		if (!room) {
			// No.
			return;
		}

		Rooms::RoomMemberData memberData {};
		memberData.memberId = userId;
		memberData.roomId = room->GetId();

		const auto& category = room->GetCategory();
		const auto& view = category->GetView();

		packet.put_string("CRIT", "");
		packet.put_integer("VERS", 1);

		// Category data
		packet.push_struct("CDAT");
		category->WriteTo(packet);
		packet.pop();

		// Room data
		packet.push_struct("RDAT");
		room->WriteTo(packet);
		packet.pop();

		// View data
		packet.push_struct("VDAT");
		view->WriteTo(packet);
		packet.pop();

		// Member data
		packet.push_struct("MDAT");
		memberData.Write(packet);
		packet.pop();
	}

	void RoomsComponent::SelectViewUpdates(Request& request) {
		const auto& user = request.get_user();
		if (!user) {
			return;
		}

		uint32_t roomId = 0;
		uint32_t roomCategoryId = 0;
		uint32_t roomViewId = 0;

		bool add = false;
		bool update = request["UPDT"].GetUint() != 0;
		if (update) {
			roomViewId = 1;
			add = true;
		}

		TDF::Packet packet;
		packet.put_integer("SEID", 1);
		packet.put_integer("UPRE", RoomViewUpdate::UserRoomCreated);
		packet.put_integer("USID", user->get_id());
		packet.put_integer("VWID", roomViewId);

		request.reply(packet);

		// Notifications
		if (add) {
			NotifyRoomViewAdded(request, roomViewId);
			// NotifyRoomCategoryAdded(request, roomCategoryId);
			// NotifyRoomAdded(request, roomId);
		}

		if (update) {
			NotifyRoomViewUpdated(request, roomViewId);
			// NotifyRoomCategoryUpdated(request, roomCategoryId);
			// NotifyRoomUpdated(request, roomId);
		}
	}

	void RoomsComponent::SelectCategoryUpdates(Request& request) {
		uint32_t viewId = request["VWID"].GetUint();

		// Notifications
		if (viewId == 0) {
			// pseudo room categories?
		} else {
			decltype(auto) roomManager = SporeNet::Get().GetRoomManager();
			for (uint32_t i = 0; i < 4; ++i) {
				uint32_t categoryId = i + 1;
				NotifyRoomCategoryAdded(request, categoryId);
				NotifyRoomCategoryUpdated(request, categoryId);
			}
		}

		// Response
		TDF::Packet packet;
		WriteSelectCategoryUpdates(packet, viewId);

		request.reply(packet);
		/*
		if (add) {
			NotifyRoomViewAdded(request, roomViewId);
			// NotifyRoomCategoryAdded(request, roomCategoryId);
			// NotifyRoomAdded(request, roomId);
		}

		if (update) {
			NotifyRoomViewUpdated(request, roomViewId);
			// NotifyRoomCategoryUpdated(request, roomCategoryId);
			// NotifyRoomUpdated(request, roomId);
		}
		*/
	}

	void RoomsComponent::JoinRoom(Request& request) {
		const auto& user = request.get_user();
		if (!user) {
			// No.
			return;
		}

		std::string password = request["PASS"].GetString();
		std::string pval = request["PVAL"].GetString();

		uint64_t inviterId = request["INID"].GetUint64();
		bool invited = request["INVT"].GetUint() != 0;

		uint32_t categoryId = request["CTID"].GetUint();
		uint32_t roomId = request["RMID"].GetUint();

		// Get room data
		bool newRoom = false;
		bool newCategory = false;

		decltype(auto) roomManager = SporeNet::Get().GetRoomManager();

		SporeNet::RoomPtr room;
		if (roomId == 0) {
			room = roomManager.CreateRoom();
			roomId = room->GetId();
			newRoom = true;
		} else {
			room = roomManager.GetRoom(roomId);
		}

		if (!room) {
			request.reply(ErrorCode::ROOMS_ERR_NOT_FOUND);
			return;
		}

		SporeNet::RoomCategoryPtr roomCategory;
		if (categoryId == 0) {
			roomCategory = roomManager.CreateRoomCategory();
			categoryId = roomCategory->GetId();
			newCategory = true;
		} else {
			roomCategory = roomManager.GetRoomCategory(categoryId);
		}

		if (!roomCategory) {
			request.reply(ErrorCode::ROOMS_ERR_CREATE_UNKNOWN_CATEGORY);
			return;
		}

		if (!roomCategory->GetView()) {
			roomCategory->SetView(roomManager.CreateRoomView());
		}

		auto userId = user->get_id();

		// TODO: proper room handling
		room->SetCategory(roomCategory);
		room->AddUser(user);

		if (newRoom) {
			NotifyRoomAdded(request, roomId);
			NotifyRoomUpdated(request, roomId);
		}

		// Write packet
		TDF::Packet packet;
		WriteJoinRoom(packet, room, userId);

		request.reply(packet);

		// Notifications
		NotifyRoomMemberJoined(request, roomId, userId);
	}

	void RoomsComponent::SelectPseudoRoomUpdates(Request& request) {
		// Empty reply?
		request.reply();
	}
}
