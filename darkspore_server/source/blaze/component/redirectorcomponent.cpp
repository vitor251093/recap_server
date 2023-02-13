
// Include
#include "redirectorcomponent.h"

#include "main.h"
#include "blaze/client.h"
#include "game/config.h"

#include <iostream>

/*
	BlazeValues meanings
		PDTL = PersonaDetails
		SESS = SessionInfo
		NTOS = Need Terms Of Service
		PID = Persona ID
		MAIL = Client Email
		UID = Unique ID
		PCTK = Packet Key

	BlazeValues
		AMAP
			DPRT = 0x40
			MASK = 0x38
			SID = 0x38
			SIP = 0x38
			SPRT = 0x40

		NMAP
			DPRT = 0x40
			SID = 0x38
			SIP = 0x24
			SITE = 0x24
			SPRT = 0x40

		ADDR
			HOST = 0x24
			IP = 0x38
			PORT = 0x40

		(Xbox Server Address)
			PORT
			SID
			SITE

		(Xbox Id)
			GTAG
			XUID

		(Server Endpoint Info)
			ADRS
			CCON
			CHAN
			DEC
			ENC
			MCON
			PROT

		(Server Address Info)
			ADDR = 0x14
			TYPE = 0x1C

		(Server Instance)
			CWD
			ENDP
			ID
			LOAD
			NAME
			SVC

		(Server Info Data)
			AMAP
			BTGT
			BTIM
			CVER
			DEPO
			INST
			IVER
			LOCN
			MSTR
			NAME
			NASP
			NMAP
			PLAT
			SNMS
			SVID
			VERS
			XDNS
			XMST
			XSLV

		(Server Instance Error)
			MSGS

		(Xbox Client Address)
			XDDR
			XUID
*/

enum PacketID : uint16_t {
	GetServerInstance = 0x01
};

// Blaze
namespace Blaze {
	// RedirectorComponent
	uint16_t RedirectorComponent::GetId() const {
		return Id;
	}

	std::string_view RedirectorComponent::GetName() const {
		return "Redirector";
	}

	std::string_view RedirectorComponent::GetReplyPacketName(uint16_t command) const {
		switch (static_cast<PacketID>(command)) {
			case PacketID::GetServerInstance: return "getServerInstance";

			default: return "";
		}
	}

	bool RedirectorComponent::ParsePacket(Request& request) {
		switch (request.get_command()) {
			case PacketID::GetServerInstance:
				GetServerInstance(request);
				break;

			default:
				return false;
		}

		return true;
	}

	void RedirectorComponent::WriteServerInstanceInfo(TDF::Packet& packet, const std::string& host, uint16_t port) {
		packet.push_union("ADDR", NetworkAddressMember::XboxClientAddress);

		// Redirector::IpAddress (not the same as other ones)
		packet.push_struct("VALU");
		packet.put_string("HOST", host);
		packet.put_integer("IP", 0);
		packet.put_integer("PORT", port);
		packet.pop();

		packet.pop();
		/*
		packet.push_list("AMAP", TDF::Type::Struct);
		{
			packet.push_struct("");
			packet.put_integer("DPRT", 10000);
			packet.put_integer("MASK", 0);
			packet.put_integer("SID", 0);
			packet.put_integer("SIP", boost::asio::ip::address_v4::from_string(host).to_ulong());
			packet.put_integer("SPRT", 10000);
			packet.pop();
		}
		packet.pop();

		packet.push_list("MSGS", TDF::Type::String);
		packet.put_string("", "What goes here?");
		packet.pop();

		packet.push_list("NMAP", TDF::Type::Struct);
		{
			packet.push_struct("");
			packet.put_integer("DPRT", 10000);
			packet.put_integer("SID", 0);
			packet.put_string("SIP", host);
			packet.put_string("SITE", "");
			packet.pop();
		}
		packet.pop();
		*/
		packet.put_integer("SECU", 1);
		packet.put_integer("XDNS", 0);
	}

	void RedirectorComponent::WriteServerAddressInfo(TDF::Packet& packet, const std::string& host, uint16_t port) {
		packet.push_union("ADDR", NetworkAddressMember::XboxClientAddress);

		// Redirector::IpAddress (not the same as other ones)
		packet.push_struct("VALU");
		packet.put_string("HOST", host);
		packet.put_integer("IP", 0);
		packet.put_integer("PORT", port);
		packet.pop();

		packet.pop();

		packet.put_integer("TYPE", AddressInfoType::ExternalIp);
	}

	void RedirectorComponent::GetServerInstance(Request& request) {
		auto blazeServer = GetApp().get_blaze_server();

		TDF::Packet packet;
		WriteServerInstanceInfo(packet, Game::Config::Get(Game::CONFIG_SERVER_HOST), blazeServer->get_port());
		
		request.reply(packet);
	}
}
