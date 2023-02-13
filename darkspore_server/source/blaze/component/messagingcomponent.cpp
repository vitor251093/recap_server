
// Include
#include "messagingcomponent.h"
#include "gamemanagercomponent.h"
#include "usersessioncomponent.h"

#include "sporenet/instance.h"
#include "sporenet/user.h"

#include "game/gamemanager.h"
#include "game/lua.h"

#include "raknet/server.h"

#include "blaze/client.h"
#include "blaze/functions.h"
#include "utils/functions.h"

#include <iostream>

/*
	Message types
		0-2 = user message types
		2 = playgroup, lobby & game message types

		static var kMessageType_Tell = 0;
		static var kMessageType_Party = 7;
		static var kMessageType_Game = 8;
		static var kMessageType_Lobby = 9;
		static var kMessageType_System = 14;
		static var kMessageType_Warning = 15;
		static var kMessageType_SporeNetBroadcast = 16;
*/

#ifdef SendMessage
#	undef SendMessage
#endif

enum PacketID : uint16_t {
	SendMessage = 0x01,
	FetchMessages = 0x02,
	PurgeMessages = 0x03,
	TouchMessages = 0x04,
	GetMessages = 0x05,

	// Notifications
	NotifyMessage = 0x01
};

// Blaze
namespace Blaze {
	// MessagingComponent
	uint16_t MessagingComponent::GetId() const {
		return Id;
	}

	std::string_view MessagingComponent::GetName() const {
		return "Messaging";
	}

	std::string_view MessagingComponent::GetReplyPacketName(uint16_t command) const {
		switch (static_cast<PacketID>(command)) {
			case PacketID::SendMessage: return "sendMessage";
			case PacketID::FetchMessages: return "fetchMessages";
			case PacketID::PurgeMessages: return "purgeMessages";
			case PacketID::TouchMessages: return "touchMessages";
			case PacketID::GetMessages: return "getMessages";

			default: return "";
		}
	}

	std::string_view MessagingComponent::GetNotificationPacketName(uint16_t command) const {
		switch (static_cast<PacketID>(command)) {
			case PacketID::NotifyMessage: return "NotifyMessage";

			default: return "";
		}
	}

	bool MessagingComponent::ParsePacket(Request& request) {
		switch (request.get_command()) {
			case PacketID::SendMessage:
				OnSendMessage(request);
				break;

			case PacketID::FetchMessages:
				OnFetchMessages(request);
				break;

			case PacketID::PurgeMessages:
				OnPurgeMessages(request);
				break;

			case PacketID::TouchMessages:
				OnTouchMessages(request);
				break;

			case PacketID::GetMessages:
				OnGetMessages(request);
				break;

			default:
				return false;
		}

		return true;
	}

	void MessagingComponent::OnSendMessageResponse(Request& request) {
		ClientMessage message;
		message.Read(request.get_request());

		uint32_t id;
		if (!message.attributes.empty()) {
			id = message.attributes.begin()->first;
		} else {
			id = 0;
		}

		TDF::Packet packet;
		packet.put_integer("MGID", id);
		packet.push_list("MIDS", TDF::Type::Integer); // vector<uint32_t>
		for (const auto& [id, _] : message.attributes) {
			packet.put_integer("", id);
		}
		packet.pop();

		request.reply(packet);

		// Notifications
		NotifyMessage(request, message);
	}

	void MessagingComponent::NotifyMessage(Request& request, const ClientMessage& clientMessage) {
		ServerMessage serverMessage;
		serverMessage.flags = 0;
		serverMessage.messageId = 1;
		serverMessage.time = static_cast<uint32_t>(utils::get_unix_time());
		serverMessage.message = clientMessage;

		auto componentId = std::get<0>(clientMessage.target);
		auto localId = std::get<2>(clientMessage.target);
		switch (componentId) {
			case GameManagerComponent::Id: {
				const auto& game = Game::GameManager::GetGame(static_cast<uint32_t>(localId));
				if (!game) {
					break;
				}

				const auto& player = game->GetPlayerByIndex(0);
				if (!player) {
					break;
				}

				const auto& user = player->GetUser();
				if (user) {
					serverMessage.name = user->get_name();
				}

				// Commands - Move this somewhere else when scripting is added
				auto& messageText = serverMessage.message.attributes[0xFF02];
				if (messageText.starts_with("!") && messageText.length() >= 2) {
					std::string_view messageTextView = &messageText[1];
					if (messageTextView.starts_with("packet ")) {
						// !packet id extra_data
						if (messageTextView.length() < 8) {
							break;
						}

						messageTextView = &messageText[8];
						if (messageTextView.starts_with("reload")) {
							game->AddClientTask(0, RakNet::PacketID::ReloadLevel);
							messageText = "<reloaded level>";
						} else if (messageTextView.starts_with("deploycharacter")) {
							game->AddClientTask(0, RakNet::PacketID::PlayerCharacterDeploy);
							messageText = "<tried to deploy character>";
						} else {
							auto packetId = utils::to_number<RakNet::PacketID>(messageTextView, 0);
							game->AddClientTask(0, packetId);

							std::string valueStr(messageTextView);
							messageText = "<sent packet " + valueStr + ">";
						}
					} else if (messageTextView.starts_with("lua ")) {
						// !lua script
						if (messageTextView.length() < 5) {
							break;
						}

						messageTextView = &messageText[5];
						if (messageTextView.starts_with("reload")) {
							game->AddServerTask([game] { game->GetLua().Reload(); });
							messageText = "<reload lua scripts>";
						} else {
							game->AddServerTask([game, buffer = std::string(messageTextView)] {
								game->GetLua().LoadBuffer(buffer);
							});
							messageText = "<load lua buffer>";
						}
					} else if (messageTextView.starts_with("debug")) {
						game->AddClientTask(0, RakNet::PacketID::PhysicsChanged);
					}
				}

				break;
			}

			case UserSessionComponent::Id: {
				const auto& user = SporeNet::Get().GetUserManager().GetUserByAuthToken(std::to_string(localId));
				if (user) {
					serverMessage.name = user->get_name();
				}

				break;
			}
		}

		if (!serverMessage.name.empty()) {
			TDF::Packet packet;
			serverMessage.Write(packet);

			request.notify(packet, Id, PacketID::NotifyMessage);
		}
	}

	void MessagingComponent::OnSendMessage(Request& request) {
		std::cout << "OnSendMessage" << std::endl;
		OnSendMessageResponse(request);
	}

	void MessagingComponent::OnFetchMessages(Request& request) {
		std::cout << "OnFetchMessages" << std::endl;
	}

	void MessagingComponent::OnPurgeMessages(Request& request) {
		std::cout << "OnPurgeMessages" << std::endl;
	}

	void MessagingComponent::OnTouchMessages(Request& request) {
		std::cout << "OnTouchMessages" << std::endl;
	}

	void MessagingComponent::OnGetMessages(Request& request) {
		std::cout << "OnGetMessages" << std::endl;
	}
}
