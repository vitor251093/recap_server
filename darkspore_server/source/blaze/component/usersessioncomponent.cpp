
// Include
#include "usersessioncomponent.h"
#include "gamemanagercomponent.h"

#include "blaze/client.h"
#include "utils/functions.h"

#include <iostream>

enum PacketID : uint16_t {
	FetchExtendedData = 0x03,
	UpdateExtendedDataAttribute = 0x05,
	UpdateHardwareFlags = 0x08,
	LookupUser = 0x0C,
	LookupUsers = 0x0D,
	LookupUsersByPrefix = 0x0E,
	UpdateNetworkInfo = 0x14,
	LookupUserGeoIPData = 0x17,
	OverrideUserGeoIPData = 0x18,
	UpdateUserSessionClientData = 0x19,
	SetUserInfoAttribute = 0x1A,
	ResetUserGeoIPData = 0x1B,

	// Notifications
	UserSessionExtendedDataUpdate = 0x01,
	UserAdded = 0x02,
	UserRemoved = 0x03,
	UserSessionDisconnected = 0x04,
	UserUpdated = 0x05
};

// Blaze
namespace Blaze {
	// UserSessionComponent
	uint16_t UserSessionComponent::GetId() const {
		return Id;
	}

	std::string_view UserSessionComponent::GetName() const {
		return "UserSessions";
	}

	std::string_view UserSessionComponent::GetReplyPacketName(uint16_t command) const {
		switch (static_cast<PacketID>(command)) {
			case PacketID::FetchExtendedData: return "fetchExtendedData";
			case PacketID::UpdateExtendedDataAttribute: return "updateExtendedDataAttribute";
			case PacketID::UpdateHardwareFlags: return "updateHardwareFlags";
			case PacketID::LookupUser: return "lookupUser";
			case PacketID::LookupUsers: return "lookupUsers";
			case PacketID::LookupUsersByPrefix: return "lookupUsersByPrefix";
			case PacketID::UpdateNetworkInfo: return "updateNetworkInfo";
			case PacketID::LookupUserGeoIPData: return "lookupUserGeoIPData";
			case PacketID::OverrideUserGeoIPData: return "overrideUserGeoIPData";
			case PacketID::UpdateUserSessionClientData: return "updateUserSessionClientData";
			case PacketID::SetUserInfoAttribute: return "setUserInfoAttribute";
			case PacketID::ResetUserGeoIPData: return "resetUserGeoIPData";

			default: return "";
		}
	}

	std::string_view UserSessionComponent::GetNotificationPacketName(uint16_t command) const {
		switch (static_cast<PacketID>(command)) {
			case PacketID::UserSessionExtendedDataUpdate: return "UserSessionExtendedDataUpdate";
			case PacketID::UserAdded: return "UserAdded";
			case PacketID::UserRemoved: return "UserRemoved";
			case PacketID::UserSessionDisconnected: return "UserSessionDisconnected";
			case PacketID::UserUpdated: return "UserUpdated";

			default: return "";
		}
	}

	bool UserSessionComponent::ParsePacket(Request& request) {
		switch (request.get_command()) {
			case PacketID::LookupUser:
				LookupUser(request);
				break;

			case PacketID::UpdateNetworkInfo:
				UpdateNetworkInfo(request);
				break;

			case PacketID::UpdateUserSessionClientData:
				UpdateUserSessionClientData(request);
				break;

			default:
				return false;
		}

		return true;
	}

	void UserSessionComponent::NotifyUserSessionExtendedDataUpdate(Request& request, int64_t userId, const UserSessionExtendedData& extendedData) {
		TDF::Packet packet;

		packet.push_struct("DATA");
		extendedData.Write(packet);
		packet.pop();

		packet.put_integer("USID", userId);

		request.notify(packet, Id, PacketID::UserSessionExtendedDataUpdate);
	}

	void UserSessionComponent::NotifyUserAdded(Request& request, const SporeNet::UserPtr& user) {
		if (!user) {
			return;
		}

		// Change to get user from userId
		const auto& extendedData = user->get_extended_data();

		UserIdentification userIdentification;
		userIdentification.localization = request.get_client().data().lang;
		userIdentification.id = user->get_id();
		userIdentification.name = user->get_name();

		TDF::Packet packet;
		packet.push_struct("DATA");
		extendedData.Write(packet);
		packet.pop();

		packet.push_struct("USER");
		userIdentification.Write(packet);
		packet.pop();

		request.notify(packet, Id, PacketID::UserAdded);
	}

	void UserSessionComponent::NotifyUserUpdated(Request& request, const SporeNet::UserPtr& user, SessionState state) {
		if (!user) {
			return;
		}

		TDF::Packet packet;
		packet.put_integer("FLGS", state);
		packet.put_integer("ID", user->get_id());

		request.notify(packet, Id, PacketID::UserUpdated);
	}

	void UserSessionComponent::LookupUser(Request& request) {
		const auto& user = request.get_user();
		if (!user) {
			return;
		}

		UserData userData;
		userData.user.Read(request.get_request());

		// Online
		userData.statusFlags |= 1;

		// Offline
		// userData.statusFlags &= 0xFFFFFFFE;

		if (userData.user.name == "test") {
			userData.extendedData = user->get_extended_data();
		}

		TDF::Packet packet;
		userData.Write(packet);

		request.reply(packet);
	}

	void UserSessionComponent::UpdateNetworkInfo(Request& request) {
		// UDEV = router info?
		// USTA = upnp on or off

		const auto& user = request.get_user();
		if (!user) {
			return;
		}

		UserSessionExtendedData& extendedData = user->get_extended_data();
		extendedData.ip.Read(request["ADDR"]["VALU"]);

		request.reply();

		// Notifications
		NotifyUserSessionExtendedDataUpdate(request, user->get_id(), extendedData);
	}

	void UserSessionComponent::UpdateUserSessionClientData(Request& request) {
		// Log(request.get_request());

		PresenceInfo presenceInfo {};
		presenceInfo.Read(request["CVAR"]);

		// auto& data = client->data();

		TDF::Packet packet;
		packet.push_integer_list("CVAR");
		packet.put_integer("", 1);
		packet.pop();

		request.reply(packet);
	}
}
