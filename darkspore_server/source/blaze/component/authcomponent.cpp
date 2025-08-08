
// Include
#include "authcomponent.h"
#include "usersessioncomponent.h"

#include "sporenet/instance.h"
#include "sporenet/user.h"

#include "blaze/client.h"
#include "blaze/functions.h"
#include "utils/functions.h"

#include <iostream>

/*
	Union types (0-4 means the value when creating the union)
		ADDR

		PNET
			0 = XboxClientAddress
			1 = XboxServerAddress
			2 = IpPairAddress or (IpAddress + IpAddress)?
			3 = IpAddress
			4 = HostNameAddress

		REAS
			0 = DatalessContextSetup
			1 = ResetDedicatedServerSetupContext
			2 = IndirectJoinGameSetupContext
			3 = MatchmakingSetupContext
			4 = IndirectMatchmakingSetupContext

	Blaze types
		0x04 = Integer (Time, U64)
		0x08 = ObjectId
		0x0C = ObjectType
		0x10 = Integer List
		0x14 = Union
		0x18 = Struct
		0x1C = Enum (calls 0x3C internally, so its a int32_t)
		0x20 = Blob
		0x24 = String
		0x28 = Enum (Callback?)
		0x2C = Float
		0x30 = Integer (uint64_t)
		0x34 = Integer (int64_t)
		0x38 = Integer (uint32_t)
		0x3C = Integer (int32_t)
		0x40 = Integer (uint16_t)
		0x44 = Integer (int16_t)
		0x48 = Integer (uint8_t)
		0x4C = Integer (int8_t)
		0x50 = Boolean (integer where true != 0)
		0x54 = Map
		0x58 = Array

	BlazeValues
		DatalessContextSetup
			DCTX = 0x1C

		ResetDedicatedServerSetupContext
			ERR = 0x38

		IndirectJoinGameSetupContext
			GRID = 0x08
			RPVC = 0x50

		MatchmakingSetupContext
			FIT = 0x38
			MAXF = 0x38
			MSID = 0x38
			RSLT = 0x1C
			USID = 0x38

		IndirectMatchmakingSetupContext
			FIT = 0x38
			GRID = 0x08
			MAXF = 0x38
			MSID = 0x38
			RPVC = 0x50
			RSLT = 0x1C
			USID = 0x38

		XboxClientAddress
			XDDR = 0x20
			XUID = 0x30

		XboxServerAddress
			PORT = 0x40
			SITE = 0x24
			SVID = 0x38

		IpPairAddress
			EXIP = 0x18
			INIP = 0x18

		IpAddress
			IP = 0x38
			PORT = 0x40

		HostNameAddress
			NAME = 0x24
			PORT = 0x40

		CDAT
			IITO = 0x50
			LANG = 0x38
			SVCN = 0x24
			TYPE = 0x1C

		PLST
			List of PDTL

		PDTL
			DSNM = 0x24
			LAST = 0x38
			PID = 0x34
			STAS = 0x1C
			XREF = 0x30
			XTYP = 0x1C

		PINF
			List of personas

		SESS
			BUID = 0x34
			FRST = 0x50
			KEY = 0x24
			LLOG = 0x34
			MAIL = 0x24
			PDTL = 0x18
			UID = 0x34

		(User details)
			MAIL
			PLST

		(User profile details)
			CITY
			CTRY
			GNDR
			STAT
			STRT
			ZIP

		(Account defails)
			ASRC
			CO
			DOB
			DTCR
			GOPT
			LATH
			LN
			MAIL
			PML
			RC
			STAS
			STAT
			TOSV
			TPOT
			UID

	Request Packets
		ConsumeCode
			CDKY
			DEID
			GNAM
			KEY
			PID
			PNID

		Login | Yes this is actually what the client sends, completely static
			53 8B 5C 24 10 8B 53 20  55 8B 6C 24 10 56 57 8B
			7C 24 14 8B 07 6A 00 6A  00 8B F1 8B 4B 24 51 52
			8B 50 30 8D 4E 20 51 68  00 64 6A 93 56 55 8B CF
			FF D2 8B 07 8B 40 24 68  01 01 00 00 68 A4 D5 FC
			00 8D 4B 08 51 8D 56 08  52 68 00 6C

		ExpressLogin
			MAIL
			PASS
			PNAM

		LoginPersona
			PNAM

		UpdateAccount
			CPWD = 0x24
			CTRY = 0x24
			DOB = 0x24
			LANG = 0x24
			MAIL = 0x24
			OPTQ = 0x4C
			OPTS = 0x4C
			PASS = 0x24
			PRNT = 0x24
			UID = 0x34

	Response Packets
		ConsumeCode
			EXRF
			KEY
			MCNT
			MFLG
			MLMT
			PRID
			PRMN
			STAT
			UID

		Login
			NTOS = 0x50
			PCTK = 0x24
			PLST = 0x58
			PRIV = 0x24
			SKEY = 0x24
			SPAM = 0x50
			THST = 0x24
			TURI = 0x24
			UID = 0x34

		FullLogin
			AGUP = 0x50
			NTOS = 0x50
			PCTK = 0x24
			PRIV = 0x24
			SESS = 0x18
			SPAM = 0x50
			THST = 0x24
			TURI = 0x24

		ConsoleLogin
			AGUP = 0x50
			NTOS = 0x50
			PRIV = 0x24
			SESS = 0x18
			SPAM = 0x50
			THST = 0x24
			TURI = 0x24

		GetTOSInfo
			EAMC = 0x38
			PMC = 0x38
			PRIV = 0x24
			THST = 0x24
			TURI = 0x24

		GetTermsAndConditions
			LDVC = 0x24
			TCOL = 0x38
			TCOT = 0x24
*/

enum class LoginTokenType : uint8_t {
	Unknown = 0,
	AuthToken,
	PcLoginToken,
	HandoffToken
};

enum PacketID : uint16_t {
	CreateAccount = 0x0A,
	UpdateAccount = 0x14,
	UpdateParentalEmail = 0x1C,
	ListUserEntitlements2 = 0x1D,
	GetAccount = 0x1E,
	GrantEntitlement = 0x1F,
	ListEntitlements = 0x20,
	HasEntitlement = 0x21,
	GetUseCount = 0x22,
	DecrementUseCount = 0x23,
	GetAuthToken = 0x24,
	GetHandoffToken = 0x25,
	GetPasswordRules = 0x26,
	GrantEntitlement2 = 0x27,
	Login = 0x28,
	AcceptTOS = 0x29,
	GetTOSInfo = 0x2A,
	ModifyEntitlements2 = 0x2B,
	ConsumeCode = 0x2C,
	ForgottenPassword = 0x2D,
	GetTermsAndConditions = 0x2E,
	GetPrivacyPolicy = 0x2F,
	ListPersonaEntitlements2 = 0x30,
	SilentLogin = 0x32,
	CheckAgeRequirement = 0x33,
	ExpressLogin = 0x3C,
	Logout = 0x46,
	CreatePersona = 0x50,
	GetPersona = 0x5A,
	ListPersonas = 0x64,
	LoginPersona = 0x6E,
	LogoutPersona = 0x78,
	DeletePersona = 0x8C,
	DisablePersona = 0x8D,
	ListDeviceAccounts = 0x8F,
	XboxCreateAccount = 0x96,
	XboxAssociateAccount = 0xA0,
	XboxLogin = 0xAA,
	PS3CreateAccount = 0xB4,
	PS3AssociateAccount = 0xBE,
	PS3Login = 0xC8,
	ValidateSessionKey = 0xD2,
	WalUserSession = 0xE6,
	DeviceLoginGuest = 0x12C //(What?)
};

// Blaze
namespace Blaze {
	// AuthComponent
	uint16_t AuthComponent::GetId() const {
		return Id;
	}

	std::string_view AuthComponent::GetName() const {
		return "Authentication";
	}

	std::string_view AuthComponent::GetReplyPacketName(uint16_t command) const {
		switch (static_cast<PacketID>(command)) {
			case PacketID::CreateAccount: return "createAccount";
			case PacketID::UpdateAccount: return "updateAccount";
			case PacketID::UpdateParentalEmail: return "updateParentalEmail";
			case PacketID::ListUserEntitlements2: return "listUserEntitlements2";
			case PacketID::GetAccount: return "getAccount";
			case PacketID::GrantEntitlement: return "grantEntitlements";
			case PacketID::ListEntitlements: return "listEntitlements";
			case PacketID::HasEntitlement: return "hasEntitlement";
			case PacketID::GetUseCount: return "getUseCount";
			case PacketID::DecrementUseCount: return "decrementUseCount";
			case PacketID::GetAuthToken: return "getAuthToken";
			case PacketID::GetHandoffToken: return "getHandoffToken";
			case PacketID::GetPasswordRules: return "getPasswordRules";
			case PacketID::GrantEntitlement2: return "grantEntitlements2";
			case PacketID::Login: return "login";
			case PacketID::AcceptTOS: return "acceptTos";
			case PacketID::GetTOSInfo: return "getTosInfo";
			case PacketID::ModifyEntitlements2: return "modiftEntitlements2";
			case PacketID::ConsumeCode: return "consumeCode";
			case PacketID::ForgottenPassword: return "forgottenPassword";
			case PacketID::GetTermsAndConditions: return "getTermsAndConditions";
			case PacketID::GetPrivacyPolicy: return "getPrivacyPolicy";
			case PacketID::ListPersonaEntitlements2: return "listPersonaEntitlements2";
			case PacketID::SilentLogin: return "silentLogin";
			case PacketID::CheckAgeRequirement: return "checkAgeRequirement";
			case PacketID::ExpressLogin: return "expressLogin";
			case PacketID::Logout: return "logout";
			case PacketID::CreatePersona: return "createPersona";
			case PacketID::GetPersona: return "getPersona";
			case PacketID::ListPersonas: return "listPersonas";
			case PacketID::LoginPersona: return "loginPersona";
			case PacketID::LogoutPersona: return "logoutPersona";
			case PacketID::DeletePersona: return "deletePersona";
			case PacketID::DisablePersona: return "disablePersona";
			case PacketID::ListDeviceAccounts: return "listDeviceAccounts";

			// Ignore the xbox & ps3 packets
			case PacketID::XboxCreateAccount: return "xboxCreateAccount";
			case PacketID::XboxAssociateAccount: return "xboxAssociateAccount";
			case PacketID::XboxLogin: return "xboxLogin";
			case PacketID::PS3CreateAccount: return "ps3CreateAccount";
			case PacketID::PS3AssociateAccount: return "ps3AssociateAccount";
			case PacketID::PS3Login: return "ps3Login";

			case PacketID::ValidateSessionKey: return "validateSessionKey";
			case PacketID::WalUserSession: return "createWalUserSession";
			case PacketID::DeviceLoginGuest: return "deviceLoginGuest";

			default: return "";
		}
	}

	std::string_view AuthComponent::GetNotificationPacketName(uint16_t command) const {
		return "";
	}

	bool AuthComponent::ParsePacket(Request& request) {
		switch (request.get_command()) {
			case PacketID::GetAuthToken:
				GetAuthToken(request);
				break;

			case PacketID::Login:
				Login(request);
				break;

			case PacketID::AcceptTOS:
				AcceptTOS(request);
				break;

			case PacketID::GetTOSInfo:
				GetTOSInfo(request);
				break;

			case PacketID::GetTermsAndConditions:
				GetTermsAndConditions(request);
				break;

			case PacketID::GetPrivacyPolicy:
				GetPrivacyPolicy(request);
				break;

			case PacketID::SilentLogin:
				SilentLogin(request);
				break;

			case PacketID::ExpressLogin:
				ExpressLogin(request);
				break;

			case PacketID::Logout:
				Logout(request);
				break;

			case PacketID::LoginPersona:
				LoginPersona(request);
				break;

			default:
				return false;
		}

		return true;
	}

	void AuthComponent::WriteAuthToken(TDF::Packet& packet, const std::string& token) {
		packet.put_string("AUTH", token);
	}

	void AuthComponent::WriteLogin(TDF::Packet& packet, const SporeNet::UserPtr& user) {
		/*
			Internal packet offsets
				NTOS = 0x71
				PCTK = 0x10 (max len: 0x400)
				PLST = 0x1C
				PRIV = 0x4C (max len: 0x80)
				SKEY = 0x64 (max len: 0x40)
				SPAM = 0x70
				THST = 0x58 (max len: 0x80)
				TURI = 0x40 (max len: 0x80)
				UID = 0x08
		*/
		if (!user) {
			return;
		}

		uint64_t currentTime = utils::get_unix_time();

		PersonaDetails personaDetails;
		personaDetails.name = user->get_name();
		personaDetails.last = static_cast<uint32_t>(currentTime);
		personaDetails.id = user->get_id();
		personaDetails.status = PersonaStatus::Active;

		// Write packet
		packet.put_integer("NTOS", 0);
		packet.put_string("PCTK", "unknown_data");

		packet.push_list("PLST", TDF::Type::Struct);
			packet.push_struct("");
			personaDetails.Write(packet);
			packet.pop();
		packet.pop();

		packet.put_string("PRIV", "");
		packet.put_string("SKEY", "telemetry_key");
		packet.put_integer("SPAM", 0);
		packet.put_string("THST", "");
		packet.put_string("TURI", "");
		packet.put_integer("UID", personaDetails.id);
		// packet.put_integer("UID", request.get_client().get_id());
	}

	void AuthComponent::WriteFullLogin(TDF::Packet& packet, const SporeNet::UserPtr& user) {
		if (!user) {
			return;
		}

		uint64_t currentTime = utils::get_unix_time();
		int64_t userId = user->get_id();

		SessionInfo sessionInfo;
		sessionInfo.blazeId = userId;
		sessionInfo.firstLogin = false;
		sessionInfo.key = "telemetry_key";
		sessionInfo.lastLogin = currentTime;
		sessionInfo.uid = userId;

		PersonaDetails& personaDetails = sessionInfo.personaDetails;
		personaDetails.name = user->get_name();
		personaDetails.last = static_cast<uint32_t>(currentTime);
		personaDetails.id = userId;
		personaDetails.status = PersonaStatus::Active;

		packet.put_integer("AGUP", 0);
		packet.put_integer("NTOS", 0);
		packet.put_string("PCTK", "");
		packet.put_string("PRIV", "");

		packet.push_struct("SESS");
		sessionInfo.Write(packet);
		packet.pop();

		packet.put_integer("SPAM", 0);
		packet.put_string("THST", "");
		packet.put_string("TURI", "");
	}

	void AuthComponent::WriteTOSInfo(TDF::Packet& packet) {
		packet.put_integer("EAMC", 0);
		packet.put_integer("PMC", 0);
		packet.put_string("PRIV", "");
		packet.put_string("THST", "");
		packet.put_string("TURI", "");
	}

	void AuthComponent::WriteTermsAndConditions(TDF::Packet& packet) {
		std::string testConditions = "Hello this is something";

		packet.put_string("LDVC", "Something");
		packet.put_integer("TCOL", testConditions.length());
		packet.put_string("TCOT", testConditions);
	}

	void AuthComponent::WritePrivacyPolicy(TDF::Packet& packet) {
		std::string testConditions = "Hello this is stuff about privacy";

		packet.put_string("LDVC", "Something2");
		packet.put_integer("TCOL", testConditions.length());
		packet.put_string("TCOT", testConditions);
	}

	void AuthComponent::GetAuthToken(Request& request) {
		const auto& user = request.get_user();
		if (!user) {
			return;
		}

		user->set_auth_token(std::to_string(user->get_id()));

		TDF::Packet packet;
		WriteAuthToken(packet, user->get_auth_token());

		request.reply(packet);

		// Notifications
		UserSessionComponent::NotifyUserUpdated(request, user, SessionState::Authenticated);
	}

	void AuthComponent::Login(Request& request) {
		uint64_t dvid = request["DVID"].GetUint64(); // device id?

		std::string username = request["MAIL"].GetString();
		std::string password = request["PASS"].GetString();

		std::string token = request["TOKN"].GetString();
		LoginTokenType tokenType = static_cast<LoginTokenType>(request["TYPE"].GetUint());

		const auto& [user, success, alreadyLoggedIn] = SporeNet::Get().GetUserManager().Login(username, password);
		if (!success && !alreadyLoggedIn) {
			std::cout << "User '" << username << "' not found." << std::endl;

			request.reply(ErrorCode::AUTH_ERR_INVALID_USER);
			return;
		}

		// Setup initial user data (move this)
		UserSessionExtendedData& extendedData = user->get_extended_data();
		extendedData.country = "US";
		extendedData.hardwareFlags = 1;
		extendedData.userAttributes = 3;
		// extendedData.dmap[0x70001] = 55;
		// extendedData.dmap[0x70002] = 707;
		extendedData.blazeObjectIdList.emplace_back(4, 1, 0);
		extendedData.blazeObjectIdList.emplace_back(5, 1, 0);
		for (uint32_t i = 0; i < 5; ++i) {
			// extendedData.latencyList.push_back(0x0FFF0FFF);
			extendedData.latencyList.push_back(1161889797);
		}

		NetworkQosData& qos = extendedData.qos;
		qos.dbps = 128000;
		qos.type = NatType::Open;
		qos.ubps = 2;

		// Assign user to client
		request.set_user(user);

		// Reply
		TDF::Packet packet;
		WriteLogin(packet, user);

		request.reply(packet);
	}

	void AuthComponent::SilentLogin(Request& request) {
		// Used somewhere ingame, don't know how to trigger.
		std::string authToken = request["AUTH"].GetString();
		LoginTokenType tokenType = static_cast<LoginTokenType>(request["TYPE"].GetUint());

		int64_t personaId = request["PID"].GetInt64();

		const auto& user = SporeNet::Get().GetUserManager().GetUserByAuthToken(authToken);
		if (!user) {
			std::cout << "User with auth token '" << authToken << "' not found." << std::endl;

			request.reply(ErrorCode::AUTH_ERR_INVALID_USER);
			return;
		}

		request.set_user(user);

		TDF::Packet packet;
		WriteFullLogin(packet, user);

		request.reply(packet);
	}

	void AuthComponent::ExpressLogin(Request& request) {
		// Used somewhere ingame, don't know how to trigger.
		std::string username = request["MAIL"].GetString();
		std::string password = request["PASS"].GetString();
		std::string personaName = request["PNAM"].GetString();

		const auto& user = SporeNet::Get().GetUserManager().GetUserByEmail(username);
		if (!user) {
			std::cout << "User '" << username << "' not found." << std::endl;

			request.reply(ErrorCode::AUTH_ERR_INVALID_USER);
			return;
		}

		request.set_user(user);

		TDF::Packet packet;
		WriteFullLogin(packet, user);

		request.reply(packet);
	}

	void AuthComponent::LoginPersona(Request& request) {
		const auto& user = request.get_user();
		if (!user) {
			return;
		}

		// LoginPersona does not have its own response function.
		uint64_t currentTime = utils::get_unix_time();
		int64_t userId = user->get_id();

		SessionInfo sessionInfo;
		sessionInfo.blazeId = userId;
		sessionInfo.firstLogin = false;
		sessionInfo.key = "telemetry_key";
		sessionInfo.lastLogin = currentTime;
		sessionInfo.uid = userId;

		PersonaDetails& personaDetails = sessionInfo.personaDetails;
		personaDetails.name = user->get_name();
		personaDetails.last = static_cast<uint32_t>(currentTime);
		personaDetails.id = userId;
		personaDetails.status = PersonaStatus::Active;

		TDF::Packet packet;
		sessionInfo.Write(packet);

		request.reply(packet);

		// Notifications
		UserSessionComponent::NotifyUserAdded(request, user);
		UserSessionComponent::NotifyUserUpdated(request, user, SessionState::Connected);
	}

	void AuthComponent::Logout(Request& request) {
		const auto& user = request.get_user();
		if (user) {
			user->Logout();
		}
	}

	void AuthComponent::AcceptTOS(Request& request) {
		// Empty response
		request.reply();
	}

	void AuthComponent::GetTOSInfo(Request& request) {
		TDF::Packet packet;
		WriteTOSInfo(packet);

		request.reply(packet);
	}

	void AuthComponent::GetTermsAndConditions(Request& request) {
		TDF::Packet packet;
		WriteTermsAndConditions(packet);

		request.reply(packet);
	}

	void AuthComponent::GetPrivacyPolicy(Request& request) {
		TDF::Packet packet;
		WritePrivacyPolicy(packet);

		request.reply(packet);
	}
}
