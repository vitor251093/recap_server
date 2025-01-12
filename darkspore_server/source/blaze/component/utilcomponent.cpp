
// Include
#include "utilcomponent.h"
#include "associationcomponent.h"
#include "authcomponent.h"
#include "gamemanagercomponent.h"
#include "messagingcomponent.h"
#include "playgroupscomponent.h"
#include "redirectorcomponent.h"
#include "roomscomponent.h"
#include "usersessioncomponent.h"

#include "main.h"

#include "blaze/client.h"
#include "utils/functions.h"

#include <iostream>

/*
	Values in EXE for label parsing
		0x41 = Address?
*/

enum PacketID : uint16_t {
	FetchClientConfig = 0x01,
	Ping = 0x02,
	SetClientData = 0x03,
	LocalizeStrings = 0x04,
	GetTelemetryServer = 0x05,
	GetTickerServer = 0x06,
	PreAuth = 0x07,
	PostAuth = 0x08,
	UserSettingsLoad = 0x0A,
	UserSettingsSave = 0x0B,
	UserSettingsLoadAll = 0x0C,
	FilterForProfanity = 0x14,
	FetchQosConfig = 0x15,
	SetClientMetrics = 0x16,
	SetConnectionState = 0x17,
	GetPssConfig = 0x18,
	GetUserOptions = 0x19,
	SetUserOptions = 0x1A
};

// Blaze
namespace Blaze {
	// UtilComponent
	uint16_t UtilComponent::GetId() const {
		return Id;
	}

	std::string_view UtilComponent::GetName() const {
		return "Util";
	}

	std::string_view UtilComponent::GetReplyPacketName(uint16_t command) const {
		switch (static_cast<PacketID>(command)) {
			case PacketID::FetchClientConfig: return "fetchClientConfig";
			case PacketID::Ping: return "ping";
			case PacketID::SetClientData: return "setClientData";
			case PacketID::LocalizeStrings: return "localizeStrings";
			case PacketID::GetTelemetryServer: return "getTelemetryServer";
			case PacketID::GetTickerServer: return "getTickerServer";
			case PacketID::PreAuth: return "preAuth";
			case PacketID::PostAuth: return "postAuth";
			case PacketID::UserSettingsLoad: return "userSettingsLoad";
			case PacketID::UserSettingsSave: return "userSettingsSave";
			case PacketID::UserSettingsLoadAll: return "userSettingsLoadAll";
			case PacketID::FilterForProfanity: return "filterForProfanity";
			case PacketID::FetchQosConfig: return "fetchQosConfig";
			case PacketID::SetClientMetrics: return "setClientMetrics";
			case PacketID::SetConnectionState: return "setConnectionState";
			case PacketID::GetPssConfig: return "getPssConfig";
			case PacketID::GetUserOptions: return "getUserOptions";
			case PacketID::SetUserOptions: return "setUserOptions";

			default: return "";
		}
	}

	bool UtilComponent::ParsePacket(Request& request) {
		switch (request.get_command()) {
			case PacketID::FetchClientConfig:
				FetchClientConfig(request);
				break;

			case PacketID::Ping:
				Ping(request);
				break;

			case PacketID::GetTelemetryServer:
				GetTelemetryServer(request);
				break;

			case PacketID::PreAuth:
				PreAuth(request);
				break;

			case PacketID::PostAuth:
				PostAuth(request);
				break;

			case PacketID::UserSettingsSave:
				UserSettingsSave(request);
				break;

			case PacketID::UserSettingsLoadAll:
				UserSettingsLoadAll(request);
				break;

			case PacketID::SetClientMetrics:
				SetClientMetrics(request);
				break;

			default:
				return false;
		}

		return true;
	}

	void UtilComponent::WritePostAuth(TDF::Packet& packet, const PssConfig& pss, const TelemetryServer& telemetry, const TickerServer& tick, const UserOptions& options) {
		packet.push_struct("PSS");
		pss.Write(packet);
		packet.pop();

		packet.push_struct("TELE");
		telemetry.Write(packet);
		packet.pop();

		packet.push_struct("TICK");
		tick.Write(packet);
		packet.pop();

		packet.push_struct("UROP");
		options.Write(packet);
		packet.pop();
	}

	void UtilComponent::WriteGetTickerServer(TDF::Packet& packet, const TickerServer& tick) {
		tick.Write(packet);
	}

	void UtilComponent::WriteUserOptions(TDF::Packet& packet, const UserOptions& options) {
		options.Write(packet);
	}

	void UtilComponent::FetchClientConfig(Request& request) {
		std::cout << "Client " << 0 << " requested client configuration" << std::endl;
	}

	void UtilComponent::Ping(Request& request) {
		TDF::Packet packet;
		packet.put_integer("STIM", utils::get_unix_time());

		request.reply(packet);
	}

	void UtilComponent::GetTelemetryServer(Request& request) {
		decltype(auto) application = GetApp();

		auto telemetryServer = application.get_telemetry_server();

		TelemetryServer telemetry;
		telemetry.address = telemetryServer->get_address().to_string();
		telemetry.anonymous = true;
		telemetry.disable = "AD,AF,AG,AI,AL,AM,AN,AO,AQ,AR,AS,AW,AX,AZ,BA,BB,BD,BF,BH,BI,BJ,BM,BN,BO,BR,BS,BT,BV,BW,BY,BZ,CC,CD,CF,CG,CI,CK,CL,CM,CN,CO,CR,CU,CV,CX,DJ,DM,DO,DZ,EC,EG,EH,ER,ET,FJ,FK,FM,FO,GA,GD,GE,GF,GG,GH,GI,GL,GM,GN,GP,GQ,GS,GT,GU,GW,GY,HM,HN,HT,ID,IL,IM,IN,IO,IQ,IR,IS,JE,JM,JO,KE,KG,KH,KI,KM,KN,KP,KR,KW,KY,KZ,LA,LB,LC,LI,LK,LR,LS,LY,MA,MC,MD,ME,MG,MH,ML,MM,MN,MO,MP,MQ,MR,MS,MU,MV,MW,MY,MZ,NA,NC,NE,NF,NG,NI,NP,NR,NU,OM,PA,PE,PF,PG,PH,PK,PM,PN,PS,PW,PY,QA,RE,RS,RW,SA,SB,SC,SD,SG,SH,SJ,SL,SM,SN,SO,SR,ST,SV,SY,SZ,TC,TD,TF,TG,TH,TJ,TK,TL,TM,TN,TO,TT,TV,TZ,UA,UG,UM,UY,UZ,VA,VC,VE,VG,VN,VU,WF,WS,YE,YT,ZM,ZW,ZZ";
		telemetry.filter = "";
		telemetry.location = request.get_client().data().lang;
		telemetry.noToggleOk = "US,CA,MX";
		telemetry.port = telemetryServer->get_port();
		telemetry.sendDelay = 15000;
		telemetry.session = "telemetry_session";
		telemetry.key = "telemetry_key";
		telemetry.sendPercentage = 75;

		TDF::Packet packet;
		telemetry.Write(packet);

		request.reply(packet);
	}

	void UtilComponent::PreAuth(Request& request) {
		constexpr uint16_t componentIds[] = {
			AssociationComponent::Id,
			AuthComponent::Id,
			GameManagerComponent::Id,
			MessagingComponent::Id,
			PlaygroupsComponent::Id,
			RedirectorComponent::Id,
			RoomsComponent::Id,
			UserSessionComponent::Id,
			UtilComponent::Id
		};

		decltype(auto) application = GetApp();
		const auto httpQosServer = application.get_http_qos_server();

		const auto& clientInfo = request["CINF"];

		auto& data = request.get_client().data();
		data.Read(request["CDAT"]);

		TDF::Packet packet;
		packet.put_string("ASRC", "321915");

		packet.push_list("CIDS", TDF::Type::Integer);
		for (uint16_t componentId : componentIds) {
			packet.put_integer("", componentId);
		}
		packet.pop();

		packet.push_struct("CONF");
		{
			packet.push_map("CONF", TDF::Type::String, TDF::Type::String);
			packet.put_string("pingPeriod", "20000");
			packet.pop();
		}
		packet.pop();

		packet.put_string("INST", data.serviceName);
		packet.put_string("NASP", "cem_ea_id");
		packet.put_string("PILD", "");
		packet.put_string("PLAT", clientInfo["PLAT"].GetString());
		
		packet.push_struct("QOSS");
		{
			// if client qos port == 0, use 7673 (but the client seems to set it to 3659 internally either way)

			QosConfigInfo qosConfig;
			qosConfig.latencyProbes = 1;
			qosConfig.serviceId = 1161889797;
			
			QosPingSiteInfo& qosPingSiteInfo = qosConfig.pingSiteInfoByAlias.try_emplace("ams").first->second;
			qosPingSiteInfo.address = httpQosServer->get_address().to_string();
			qosPingSiteInfo.port = httpQosServer->get_port();
			qosPingSiteInfo.name = "ams";

			qosConfig.Write(packet);
		}
		packet.pop();

		packet.put_string("RSRC", "321915");
		packet.put_string("SVER", "Blaze 3.9.3.1");

		request.reply(packet);
	}

	void UtilComponent::PostAuth(Request& request) {
		decltype(auto) application = GetApp();

		auto pssServer = application.get_pss_server();
		auto telemetryServer = application.get_telemetry_server();
		auto tickServer = application.get_tick_server();

		PssConfig pss;
		pss.address = pssServer->get_address().to_string();
		pss.pjid = "123071"; // Random numbers (means nothing)
		pss.port = pssServer->get_port();
		pss.rprt = 9;
		pss.tiid = 0;

		TelemetryServer telemetry;
		telemetry.address = telemetryServer->get_address().to_string();
		telemetry.anonymous = false;
		telemetry.disable = "AD,AF,AG,AI,AL,AM,AN,AO,AQ,AR,AS,AW,AX,AZ,BA,BB,BD,BF,BH,BI,BJ,BM,BN,BO,BR,BS,BT,BV,BW,BY,BZ,CC,CD,CF,CG,CI,CK,CL,CM,CN,CO,CR,CU,CV,CX,DJ,DM,DO,DZ,EC,EG,EH,ER,ET,FJ,FK,FM,FO,GA,GD,GE,GF,GG,GH,GI,GL,GM,GN,GP,GQ,GS,GT,GU,GW,GY,HM,HN,HT,ID,IL,IM,IN,IO,IQ,IR,IS,JE,JM,JO,KE,KG,KH,KI,KM,KN,KP,KR,KW,KY,KZ,LA,LB,LC,LI,LK,LR,LS,LY,MA,MC,MD,ME,MG,MH,ML,MM,MN,MO,MP,MQ,MR,MS,MU,MV,MW,MY,MZ,NA,NC,NE,NF,NG,NI,NP,NR,NU,OM,PA,PE,PF,PG,PH,PK,PM,PN,PS,PW,PY,QA,RE,RS,RW,SA,SB,SC,SD,SG,SH,SJ,SL,SM,SN,SO,SR,ST,SV,SY,SZ,TC,TD,TF,TG,TH,TJ,TK,TL,TM,TN,TO,TT,TV,TZ,UA,UG,UM,UY,UZ,VA,VC,VE,VG,VN,VU,WF,WS,YE,YT,ZM,ZW,ZZ";
		telemetry.filter = "";
		telemetry.location = request.get_client().data().lang;
		telemetry.noToggleOk = "US,CA,MX";
		telemetry.port = telemetryServer->get_port();
		telemetry.sendDelay = 15000;
		telemetry.session = "telemetry_session";
		telemetry.key = "telemetry_key";
		telemetry.sendPercentage = 75;

		TickerServer tick;
		tick.address = tickServer->get_address().to_string();
		tick.port = tickServer->get_port();
		tick.key = std::format("0,%s:%hu,darkspore-pc,10,50,50,50,50,0,0", tick.address, tick.port);

		UserOptions options;
		options.value = TelemetryOpt::OptIn;

		TDF::Packet packet;
		WritePostAuth(packet, pss, telemetry, tick, options);

		request.reply(packet);
	}

	void UtilComponent::UserSettingsSave(Request& request) {
		/*
		Log.Info(string.Format("Client {0} saving user settings for user {1}", request.Client.ID, request.Client.User.ID));

		var data = (TdfString)request.Data["DATA"];

		Directory.CreateDirectory(string.Format(".\\data\\{0}", request.Client.User.ID));

		if (File.Exists(string.Format(".\\data\\{0}\\user_settings", request.Client.User.ID)))
		{
			File.Delete(string.Format(".\\data\\{0}\\user_settings", request.Client.User.ID));
		}

		File.WriteAllBytes(string.Format(".\\data\\{0}\\user_settings", request.Client.User.ID), Encoding.ASCII.GetBytes(data.Value));

		request.Reply();
		*/
	}

	void UtilComponent::UserSettingsLoadAll(Request& request) {
		/*
		Log.Info(string.Format("Client {0} loading all user settings for user {1}", request.Client.ID, request.Client.User.ID));

        if (File.Exists(string.Format(".\\data\\{0}\\user_settings", request.Client.User.ID)))
        {
            var userSettings = File.ReadAllBytes(string.Format(".\\data\\{0}\\user_settings", request.Client.User.ID));

            var data = new List<Tdf>
            {
                new TdfMap("SMAP", TdfBaseType.String, TdfBaseType.String, new Dictionary<object, object>
                {
                    { "cust", userSettings.ToString() }
                })
            };

            request.Reply(0, data);
        }
        else
        {
            request.Reply();
        }
		*/
	}

	void UtilComponent::SetClientMetrics(Request& request) {
		// UDEV = router info?
		// USTA = upnp on or off

		request.reply();
	}
}
