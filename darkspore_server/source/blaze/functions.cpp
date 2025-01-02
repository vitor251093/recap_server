
// Include
#include "functions.h"
#include "utils/functions.h"

#include <array>

// Blaze
namespace Blaze {
	// ClientData
	void ClientData::Read(const rapidjson::Value& value) {
		if (!value.IsObject()) {
			return;
		}

		serviceName = value["SVCN"].GetString();

		lang = value["LANG"].GetUint();
		type = static_cast<ClientType>(value["TYPE"].GetUint());

		iito = value["IITO"].GetUint() != 0;
	}

	void ClientData::Write(TDF::Packet& packet) const {
		packet.put_integer("IITO", iito ? 1 : 0);
		packet.put_integer("LANG", lang);
		packet.put_string("SVCN", serviceName);
		packet.put_integer("TYPE", type);
	}

	// PresenceInfo
	void PresenceInfo::Read(const rapidjson::Value& value) {
		if (!value.IsObject()) {
			return;
		}

		playgroupId = value["GRP"].GetUint();
		level = value["LVL"].GetUint();
		state = static_cast<decltype(state)>(value["STAT"].GetUint());
		extra = value["XTRA"].GetUint();
	}

	void PresenceInfo::Write(TDF::Packet& packet) const {
		packet.put_integer("GRP", playgroupId);
		packet.put_integer("LVL", level);
		packet.put_integer("STAT", state);
		packet.put_integer("XTRA", extra);
	}

	// IpAddress
	void IpAddress::Read(const rapidjson::Value& value) {
		if (value.IsObject()) {
			address = value["IP"].GetUint();
			port = static_cast<uint16_t>(value["PORT"].GetUint());
		}
	}

	void IpAddress::Write(TDF::Packet& packet) const {
		packet.put_integer("IP", address);
		packet.put_integer("PORT", port);
	}

	// HostNameAddress
	void HostNameAddress::Read(const rapidjson::Value& value) {
		if (value.IsObject()) {
			name = value["NAME"].GetString();
			port = static_cast<uint16_t>(value["PORT"].GetUint());
		}
	}

	void HostNameAddress::Write(TDF::Packet& packet) const {
		packet.put_string("NAME", name);
		packet.put_integer("PORT", port);
	}

	// IpPairAddress
	void IpPairAddress::Read(const rapidjson::Value& value) {
		if (value.IsObject()) {
			auto end = value.MemberEnd();
			auto exipIterator = value.FindMember("EXIP");
			if (exipIterator != end) {
				exip.Read(exipIterator->value);
			}

			auto inipIterator = value.FindMember("INIP");
			if (inipIterator != end) {
				inip.Read(inipIterator->value);
			}
		}
	}

	void IpPairAddress::Write(TDF::Packet& packet) const {
		packet.push_struct("EXIP");
		exip.Write(packet);
		packet.pop();

		packet.push_struct("INIP");
		inip.Write(packet);
		packet.pop();
	}

	// UserOptions
	void UserOptions::Write(TDF::Packet& packet) const {
		packet.put_integer("TMOP", value);
	}

	// TickerServer
	void TickerServer::Write(TDF::Packet& packet) const {
		packet.put_string("ADRS", address);
		packet.put_integer("PORT", port);
		packet.put_string("SKEY", key);
	}

	// TelemetryServer
	void TelemetryServer::Write(TDF::Packet& packet) const {
		packet.put_string("ADRS", address);
		packet.put_integer("ANON", anonymous ? 1 : 0);
		packet.put_string("DISA", disable);
		packet.put_string("FILT", filter);
		packet.put_integer("LOC", location);
		packet.put_string("NOOK", noToggleOk);
		packet.put_integer("PORT", port);
		packet.put_integer("SDLY", sendDelay);
		packet.put_string("SESS", session);
		packet.put_string("SKEY", key);
		packet.put_integer("SPCT", sendPercentage);
	}

	// PssConfig
	void PssConfig::Write(TDF::Packet& packet) const {
		packet.put_string("ADRS", address);
		packet.put_blob("CSIG", nullptr, 0);

		packet.push_list("OIDS", TDF::Type::Integer);
		for (const auto& oid : oids) {
			packet.put_string("", oid);
		}
		packet.pop();

		packet.put_string("PJID", pjid);
		packet.put_integer("PORT", port);
		packet.put_integer("RPRT", rprt);
		packet.put_integer("TIID", tiid);
	}

	// NetworkQosData
	void NetworkQosData::Write(TDF::Packet& packet) const {
		packet.put_integer("DBPS", dbps);
		packet.put_integer("NATT", type);
		packet.put_integer("UBPS", ubps);
	}

	// QosPingSiteInfo
	void QosPingSiteInfo::Write(TDF::Packet& packet) const {
		packet.put_string("PSA", address);
		packet.put_integer("PSP", port);
		packet.put_string("SNA", name);
	}

	// QosConfigInfo
	void QosConfigInfo::Write(TDF::Packet& packet) const {
		packet.push_struct("BWPS"); // something something Ping Site
		if (!bandwidthPingSiteInfo.empty()) {
			bandwidthPingSiteInfo.begin()->Write(packet);
		}
		packet.pop();

		packet.put_integer("LNP", latencyProbes);

		packet.push_map("LTPS", TDF::Type::String, TDF::Type::Struct);
		for (const auto& [name, siteInfo] : pingSiteInfoByAlias) {
			packet.push_struct(name);
			siteInfo.Write(packet);
			packet.pop();
		}
		packet.pop();

		packet.put_integer("SVID", serviceId);
	}

	// UserSessionExtendedData
	void UserSessionExtendedData::Read(const rapidjson::Value& value) {
		if (!value.IsObject()) {
			return;
		}

		// TODO:
	}

	void UserSessionExtendedData::Write(TDF::Packet& packet) const {
		/*
			switch (bps) {
				case iad = room category 2
				case gva = room category 3
				case nrt = room category 4
				default: room category = 1
			}
		*/
		constexpr std::array<const char*, 4> bpsValues { "iad", "gva", "nrt", "" };
		
		size_t bpsIndex = 1;
		if (bpsIndex >= bpsValues.size()) {
			bpsIndex = bpsValues.size() - 1;
		}

		if (ip.exip.address == 0 && ip.inip.address == 0) {
			packet.push_union("ADDR", NetworkAddressMember::Unset);
			packet.pop();
		} else {
			packet.push_union("ADDR", NetworkAddressMember::IpPairAddress);
			packet.push_struct("VALU");
			ip.Write(packet);
			packet.pop();
			packet.pop();
		}

		packet.put_string("BPS", bpsValues[bpsIndex]);

		packet.push_map("CMAP", TDF::Type::Integer, TDF::Type::Integer); // map<uint32_t, int32_t>
		for (auto [key, value] : clientAttributes) {
			packet.put_integer(std::to_string(key), value);
		}
		packet.pop();

		packet.put_string("CTY", country);

		packet.push_integer_list("CVAR"); // off_106BAB4
		packet.pop();

		packet.push_map("DMAP", TDF::Type::Integer, TDF::Type::Integer); // map<uint32_t, int64_t>
		for (auto [key, value] : dataMap) {
			packet.put_integer(std::to_string(key), value);
		}
		// packet.put_integer("0x70001", 55);
		// packet.put_integer("0x70002", 707);
		packet.pop();

		packet.put_integer("HWFG", hardwareFlags); // maybe?

		packet.push_list("PSLM", TDF::Type::Integer); // vector<int32_t>
		for (auto value : latencyList) {
			packet.put_integer("", value);
		}
		packet.pop();

		packet.push_struct("QDAT");
		qos.Write(packet);
		packet.pop();

		packet.put_integer("UATT", userAttributes); // maybe?

		packet.push_list("ULST", TDF::Type::ObjectId); // vector<vec3>
		for (const auto& value : blazeObjectIdList) {
			packet.put_object_id("", value);
		}
		packet.pop();
	}

	// HostInfo
	void HostInfo::Write(TDF::Packet& packet) const {
		packet.put_integer("HPID", id);
		packet.put_integer("HSLT", slot);
	}

	// PersonaDetails
	void PersonaDetails::Read(const rapidjson::Value& value) {
		if (!value.IsObject()) {
			return;
		}

		name = value["DSNM"].GetString();
		last = value["LAST"].GetUint();
		id = value["PID"].GetInt64();
		status = static_cast<PersonaStatus>(value["STAS"].GetUint());

		externalReference = value["XREF"].GetUint64();
		externalReferenceType = static_cast<ExternalRefType>(value["XTYP"].GetUint());
	}

	void PersonaDetails::Write(TDF::Packet& packet) const {
		packet.put_string("DSNM", name);
		packet.put_integer("LAST", last);
		packet.put_integer("PID", id);
		packet.put_integer("STAS", status);
		packet.put_integer("XREF", externalReference);
		packet.put_integer("XTYP", externalReferenceType);
	}

	// SessionInfo
	void SessionInfo::Write(TDF::Packet& packet) const {
		packet.put_integer("BUID", blazeId);
		packet.put_integer("FRST", firstLogin ? 1 : 0);
		packet.put_string("KEY", key);
		packet.put_integer("LLOG", lastLogin);
		packet.put_string("MAIL", email);

		packet.push_struct("PDTL");
		personaDetails.Write(packet);
		packet.pop();

		packet.put_integer("UID", uid);
	}

	// ListIdentification
	void ListIdentification::Read(const rapidjson::Value& value) {
		if (!value.IsObject()) {
			return;
		}

		name = value["LNM"].GetString();
		type = value["TYPE"].GetUint();
	}

	void ListIdentification::Write(TDF::Packet& packet) const {
		packet.put_string("LNM", name);
		packet.put_integer("TYPE", type);
	}

	// ListInfo
	void ListInfo::Read(const rapidjson::Value& value) {
		if (!value.IsObject()) {
			return;
		}

		const auto& listIdData = value["LID"];
		identification.Read(listIdData);

		const auto& objectId = value["BOID"];
		std::get<0>(blazeObjectId) = objectId["_X"].GetUint();
		std::get<1>(blazeObjectId) = objectId["_Y"].GetUint();
		std::get<2>(blazeObjectId) = objectId["_Z"].GetUint64();

		flags = value["FLGS"].GetUint();
		lms = value["LMS"].GetUint();
		prid = value["PRID"].GetUint();
	}

	void ListInfo::Write(TDF::Packet& packet) const {
		packet.put_object_id("BOID", blazeObjectId);
		packet.put_integer("FLGS", flags);

		packet.push_struct("LID");
		identification.Write(packet);
		packet.pop();

		packet.put_integer("LMS", lms);
		packet.put_integer("PRID", prid);
	}

	// ListMemberId
	void ListMemberId::Read(const rapidjson::Value& value) {
		if (!value.IsObject()) {
			return;
		}

		id = value["BLID"].GetInt64();
		name = value["PNAM"].GetString();
		externalReference = value["XREF"].GetUint64();
		externalReferenceType = static_cast<decltype(externalReferenceType)>(value["XTYP"].GetUint());
	}

	void ListMemberId::Write(TDF::Packet& packet) const {
		packet.put_integer("BLID", id);
		packet.put_string("PNAM", name);
		packet.put_integer("XREF", externalReference);
		packet.put_integer("XTYP", externalReferenceType);
	}

	// ListMemberInfo
	void ListMemberInfo::Write(TDF::Packet& packet) const {
		packet.push_struct("LMID");
		id.Write(packet);
		packet.pop();

		packet.put_integer("TIME", time);
	}

	// ListMemberInfoUpdate
	void ListMemberInfoUpdate::Write(TDF::Packet& packet) const {
		packet.push_struct("LMID");
		info.Write(packet);
		packet.pop();

		packet.put_integer("LUPT", type);
	}

	// ListMembers
	void ListMembers::Write(TDF::Packet& packet) const {
		packet.push_struct("INFO");
		info.Write(packet);
		packet.pop();

		packet.push_list("MEML", TDF::Type::Struct);
		for (const auto& memberInfo : memberList) {
			packet.push_struct("");
			memberInfo.Write(packet);
			packet.pop();
		}
		packet.pop();

		packet.put_integer("OFRC", ofrc);
		packet.put_integer("TOCT", toct);
	}

	// ClientMessage
	void ClientMessage::Read(const rapidjson::Value& value) {
		if (!value.IsObject()) {
			return;
		}

		const auto& attrIterator = value.FindMember("ATTR");
		if (attrIterator != value.MemberEnd()) {
			for (const auto& attribute : attrIterator->value["_Content"].GetObject()) {
				std::string_view nameView = attribute.name.GetString();
				std::string_view valueView = attribute.value.GetString();
				attributes.emplace(utils::to_number<uint32_t>(nameView, 0), valueView);
			}
		}

		const auto& targetData = value["TARG"];
		std::get<0>(target) = targetData["_X"].GetUint(); // component id
		std::get<1>(target) = targetData["_Y"].GetUint(); // unknown so far
		std::get<2>(target) = targetData["_Z"].GetUint64(); // some id used in component

		flags = value["FLAG"].GetUint();
		stat = value["STAT"].GetUint();
		tag = value["TAG"].GetUint();
		type = value["TYPE"].GetUint();
	}

	void ClientMessage::Write(TDF::Packet& packet) const {
		packet.push_map("ATTR", TDF::Type::Integer, TDF::Type::String);
		for (const auto& [id, message] : attributes) {
			packet.put_string(std::to_string(id), message);
		}
		packet.pop();

		packet.put_integer("FLAG", flags);
		packet.put_integer("STAT", stat);
		packet.put_integer("TAG", tag);
		packet.put_object_id("TARG", target);
		packet.put_integer("TYPE", type);
	}

	// ServerMessage
	void ServerMessage::Write(TDF::Packet& packet) const {
		packet.put_integer("FLAG", flags);
		packet.put_integer("MGID", messageId);
		packet.put_string("NAME", name);

		packet.push_struct("PYLD");
		message.Write(packet);
		packet.pop();

		packet.put_object_id("SRCE", source);
		packet.put_integer("TIME", time);
	}

	// UserIdentification
	void UserIdentification::Read(const rapidjson::Value& value) {
		if (!value.IsObject()) {
			return;
		}

		localization = value["ALOC"].GetUint();
		id = value["ID"].GetInt64();
		name = value["NAME"].GetString();
	}

	void UserIdentification::Write(TDF::Packet& packet) const {
		packet.put_integer("AID", id);
		packet.put_integer("ALOC", localization);
		packet.put_blob("EXBB", nullptr, 0); // blob, unused?
		packet.put_integer("EXID", 0); // uint64_t, unused?
		packet.put_integer("ID", id);
		packet.put_string("NAME", name);
	}

	// UserData
	void UserData::Read(const rapidjson::Value& value) {
		if (!value.IsObject()) {
			return;
		}

		const auto& endIterator = value.MemberEnd();
		const auto& extendedDataIterator = value.FindMember("EDAT");
		if (extendedDataIterator != endIterator) {
			extendedData.Read(extendedDataIterator->value["_Content"]);
		}

		const auto& userIterator = value.FindMember("USER");
		if (userIterator != endIterator) {
			user.Read(userIterator->value["_Content"]);
		}

		statusFlags = value["FLGS"].GetUint();
	}

	void UserData::Write(TDF::Packet& packet) const {
		packet.push_struct("EDAT");
		extendedData.Write(packet);
		packet.pop();

		packet.put_integer("FLGS", statusFlags);

		packet.push_struct("USER");
		user.Write(packet);
		packet.pop();
	}

	// PlaygroupInfo
	void PlaygroupInfo::Write(TDF::Packet& packet) const {
		packet.push_map("ATTR", TDF::Type::Integer, TDF::Type::String);
		for (const auto& [key, value] : attributes) {
			packet.put_string(key, value);
		}
		packet.pop();

		packet.put_integer("ENBV", enbv ? 1 : 0);

		packet.push_union("HNET", NetworkAddressMember::Unset);
		// TODO: check if this is neccesary
		packet.pop();

		packet.put_integer("HSID", hostSlotId);
		packet.put_integer("JOIN", state);
		packet.put_integer("MLIM", memberLimit);
		packet.put_string("NAME", name);
		packet.put_integer("NTOP", ntop);
		packet.put_integer("OWNR", ownerId);
		packet.put_integer("PGID", playgroupId);
		packet.put_integer("PRES", pres);
		packet.put_string("UKEY", ukey);
		packet.put_integer("UPRS", uprs ? 1 : 0);
		packet.put_string("UUID", uuid);
		packet.put_integer("VOIP", VoipTopology::Disabled);
		packet.put_blob("XNNC", nullptr, 0);
		packet.put_blob("XSES", nullptr, 0);
	}

	// PlaygroupMemberInfo
	void PlaygroupMemberInfo::Write(TDF::Packet& packet) const {
		packet.push_map("ATTR", TDF::Type::Integer, TDF::Type::String);
		for (const auto& [key, value] : attributes) {
			packet.put_string(key, value);
		}
		packet.pop();

		packet.put_integer("JTIM", jtim);
		packet.put_integer("PERM", permissions);

		packet.push_union("PNET", NetworkAddressMember::Unset);
		// TODO: check if this is neccesary
		packet.pop();

		packet.put_integer("SID", slot);

		packet.push_struct("USER");
		user.Write(packet);
		packet.pop();
	}
	
	// PlayerConnectionStatus
	void PlayerConnectionStatus::Read(const rapidjson::Value& value) {
		if (value.IsObject()) {
			flags = value["FLGS"].GetUint();
			id = value["PID"].GetInt64();
			status = static_cast<ConnectionStatus>(value["STAT"].GetUint());
		}
	}

	void PlayerConnectionStatus::Write(TDF::Packet& packet) const {
		packet.put_integer("FLGS", flags);
		packet.put_integer("PID", id);
		packet.put_integer("STAT", status);
	}

	// ReplicatedGamePlayer
	void ReplicatedGamePlayer::Write(TDF::Packet& packet) const {
		packet.put_blob("BLOB", nullptr, 0);
		packet.put_integer("EXID", 0); // u64
		packet.put_integer("GID", gameId);
		packet.put_integer("LOC", localization);
		packet.put_string("NAME", name);

		packet.push_map("PATT", TDF::Type::String, TDF::Type::String);
		// player attributes
		packet.pop();

		packet.put_integer("PID", id);
#if 0
		packet.push_struct("PNET");
		hostNetwork.Write(packet);
		packet.pop();
#else
		packet.push_union("PNET", NetworkAddressMember::IpPairAddress);
		{
			packet.push_struct("VALU");
			hostNetwork.Write(packet);
			packet.pop();
		}
		packet.pop();
#endif
		packet.put_integer("SID", slot);
		packet.put_integer("SLOT", slotType);
		packet.put_integer("STAT", state);
		packet.put_integer("TIDX", tIndex);
		packet.put_integer("TIME", time);
		packet.put_object_id("UGID", ugid);
		packet.put_integer("UID", uid);
	}

	// ReplicatedGameData
	void ReplicatedGameData::Write(TDF::Packet& packet) const {
		packet.push_list("ADMN", TDF::Type::Integer);
		for (const auto value : administrators) {
			packet.put_integer("", value);
		}
		packet.pop();

		packet.push_map("ATTR", TDF::Type::String, TDF::Type::String);
		for (const auto& [key, value] : attributes) {
			packet.put_string(key, value);
		}
		packet.pop();

		packet.push_list("CAP", TDF::Type::Integer);
		for (const auto value : capacity) {
			packet.put_integer("", value);
		}
		packet.pop();

		packet.push_map("CRIT", TDF::Type::String, TDF::Type::String);
		for (const auto& [key, value] : criteria) {
			packet.put_string(key, value);
		}
		packet.pop();

		packet.put_integer("GID", id);
		packet.put_string("GNAM", name);
		packet.put_integer("GPVH", gpvh);
		packet.put_integer("GSET", settings);
		packet.put_integer("GSID", gsid);
		packet.put_integer("GSTA", state);
		packet.put_string("GTYP", type);

		packet.push_list("HNET", TDF::Type::Struct, true);
		{
#if 1
			packet.push_struct("");
			hostNetwork.Write(packet);
			packet.pop();
#else
			packet.push_union("", NetworkAddressMember::IpPairAddress);
			{
				packet.push_struct("VALU");
				hostNetwork.Write(packet);
				packet.pop();
			}
			packet.pop();
#endif
		}
		packet.pop();

		packet.put_integer("HSES", hses);
		packet.put_integer("IGNO", ignore ? 1 : 0);
		/*
		packet.push_map("MATR", TDF::Type::Integer, TDF::Type::Integer);
		std::map<std::string, std::string>();
		packet.pop();
		*/
		packet.put_integer("MCAP", maxPlayers);

		packet.push_struct("NQOS");
		networkQos.Write(packet);
		packet.pop();

		packet.put_integer("NRES", resetable ? 0 : 1);
		packet.put_integer("NTOP", networkTopology);
		packet.put_string("PGID", playgroupId);
		packet.put_blob("PGSR", nullptr, 0); // ?

		packet.push_struct("PHST");
		pHost.Write(packet);
		packet.pop();

		packet.put_integer("PRES", presence);
		packet.put_string("PSAS", psas);
		packet.put_integer("QCAP", queueCapacity);
		packet.put_integer("SEED", seed);
		packet.put_integer("TCAP", tcap);

		packet.push_struct("THST");
		tHost.Write(packet);
		packet.pop();

		packet.push_list("TIDS", TDF::Type::Integer);
		for (const auto value : tids) {
			packet.put_integer("", value);
		}
		packet.pop();

		packet.put_string("UUID", uuid);
		packet.put_integer("VOIP", VoipTopology::Disabled);
		packet.put_string("VSTR", version);
		packet.put_blob("XNNC", nullptr, 0);
		packet.put_blob("XSES", nullptr, 0);
	}

	namespace Authentication {
		// UserDetails
		void UserDetails::Read(const rapidjson::Value& value) {
			if (!value.IsObject()) {
				return;
			}

			const auto end = value.MemberEnd();
			auto mailIterator = value.FindMember("MAIL");
			if (mailIterator != end) {
				mail = mailIterator->value.GetString();
			}

			auto plstIterator = value.FindMember("PLST");
			if (plstIterator != end) {
				for (const auto& child : plstIterator->value["_Content"].GetArray()) {
					PersonaDetails& details = personaDetailsList.emplace_back();
					details.Read(child);
				}
			}
		}

		void UserDetails::Write(TDF::Packet& packet) const {
			packet.put_string("MAIL", mail);
			packet.push_list("PLST", TDF::Type::Struct);
			for (const auto& value : personaDetailsList) {
				packet.push_struct("");
				value.Write(packet);
				packet.pop();
			}
			packet.pop();
		};

		// PasswordRulesInfo
		void PasswordRulesInfo::Read(const rapidjson::Value& value) {
			if (!value.IsObject()) {
				return;
			}

			maxS = value["MAXS"].GetUint();
			minS = value["MINS"].GetUint();
			vdch = value["VDCH"].GetString();
		}

		void PasswordRulesInfo::Write(TDF::Packet& packet) const {
			packet.put_integer("MAXS", maxS);
			packet.put_integer("MINS", minS);
			packet.put_string("VDCH", vdch);
		};
	}

	namespace Rooms {
		void RoomMemberData::Read(const rapidjson::Value& value) {
			if (!value.IsObject()) {
				return;
			}

			memberId = value["BZID"].GetInt64();
			roomId = value["RMID"].GetUint();
		}

		void RoomMemberData::Write(TDF::Packet& packet) const {
			packet.put_integer("BZID", memberId);
			packet.put_integer("RMID", roomId);
		}
	}

	namespace GameManager {
		// CreateGameRequest
		void CreateGameRequest::Read(const rapidjson::Value& value) {
			if (!value.IsObject()) {
				return;
			}

			const auto end = value.MemberEnd();

			auto iterator = value.FindMember("ADMN");
			if (iterator != end) {
				for (const auto& child : iterator->value["_Content"].GetArray()) {
					administrators.push_back(child.GetInt64());
				}
			}

			for (const auto& child : value["ATTR"]["_Content"].GetObject()) {
				attributes.emplace(child.name.GetString(), child.value.GetString());
			}

			const auto& inBtpl = value["BTPL"];
			std::get<0>(btpl) = inBtpl["_X"].GetUint();
			std::get<1>(btpl) = inBtpl["_Y"].GetUint();
			std::get<2>(btpl) = inBtpl["_Z"].GetUint64();

			iterator = value.FindMember("CRIT");
			if (iterator != end) {
				for (const auto& child : iterator->value["_Content"].GetObject()) {
					criteria.emplace(child.name.GetString(), child.value.GetString());
				}
			}

			ctr = value["GCTR"].GetString();
			name = value["GNAM"].GetString();
			settings = value["GSET"].GetUint();
			type = value["GTYP"].GetString();
			url = value["GURL"].GetString();

			const auto& hnetData = value["HNET"]["_Content"];
			hostNetwork.inip.Read(hnetData[0]);
			hostNetwork.exip.Read(hnetData[1]);

			ignore = value["IGNO"].GetUint() != 0;

			iterator = value.FindMember("MATR");
			if (iterator != end) {
				for (const auto& child : iterator->value["_Content"].GetObject()) {
					matr.emplace(child.name.GetString(), child.value.GetString());
				}
			}

			resetable = value["NRES"].GetUint() != 0;
			networkTopology = static_cast<GameNetworkTopology>(value["NTOP"].GetUint());

			iterator = value.FindMember("PATT");
			if (iterator != end) {
				for (const auto& child : iterator->value["_Content"].GetObject()) {
					playerAttributes.emplace(child.name.GetString(), child.value.GetString());
				}
			}

			for (const auto& child : value["PCAP"]["_Content"].GetArray()) {
				capacity.push_back(child.GetUint());
			}

			playgroupId = value["PGID"].GetString();
			playgroupSc = value["PGSC"].GetString();
			maxPlayers = value["PMAX"].GetUint();
			presence = static_cast<PresenceMode>(value["PRES"].GetUint());
			queueCapacity = value["QCAP"].GetUint();
			rgid = value["RGID"].GetUint();

			iterator = value.FindMember("SEAT");
			if (iterator != end) {
				for (const auto& child : iterator->value["_Content"].GetArray()) {
					seat.push_back(child.GetInt64());
				}
			}

			iterator = value.FindMember("SIDL");
			if (iterator != end) {
				for (const auto& child : iterator->value["_Content"].GetArray()) {
					sidl.push_back(child.GetUint());
				}
			}

			slot = value["SLOT"].GetUint();
			tcap = value["TCAP"].GetUint();

			iterator = value.FindMember("TIDS");
			if (iterator != end) {
				for (const auto& child : iterator->value["_Content"].GetArray()) {
					tids.push_back(child.GetUint());
				}
			}

			tIndex = value["TIDX"].GetUint();
			// Ignore VOIP
			version = value["VSTR"].GetString();
		}

		void CreateGameRequest::Write(TDF::Packet& packet) const {
			packet.push_list("ADMN", TDF::Type::Integer);
			for (const auto value : administrators) {
				packet.put_integer("", value);
			}
			packet.pop();

			packet.push_map("ATTR", TDF::Type::String, TDF::Type::String);
			for (const auto& [key, value] : attributes) {
				packet.put_string(key, value);
			}
			packet.pop();

			packet.put_object_id("BTPL", btpl);

			packet.push_map("CRIT", TDF::Type::String, TDF::Type::String);
			for (const auto& [key, value] : criteria) {
				packet.put_string(key, value);
			}
			packet.pop();

			packet.put_string("GCTR", ctr);
			packet.put_string("GNAM", name);
			packet.put_integer("GSET", settings);
			packet.put_string("GTYP", type);
			packet.put_string("GURL", url);

			packet.push_list("HNET", TDF::Type::Struct, true);
			{
				packet.push_struct("");
				hostNetwork.Write(packet);
				packet.pop();
			}
			packet.pop();

			packet.put_integer("IGNO", ignore ? 1 : 0);
			
			packet.push_map("MATR", TDF::Type::String, TDF::Type::String);
			for (const auto& [key, value] : matr) {
				packet.put_string(key, value);
			}
			packet.pop();

			packet.put_integer("NRES", resetable ? 0 : 1);
			packet.put_integer("NTOP", networkTopology);

			packet.push_map("PATT", TDF::Type::String, TDF::Type::String);
			for (const auto& [key, value] : playerAttributes) {
				packet.put_string(key, value);
			}
			packet.pop();

			packet.push_list("PCAP", TDF::Type::Integer);
			for (const auto value : capacity) {
				packet.put_integer("", value);
			}
			packet.pop();

			packet.put_string("PGID", playgroupId);
			packet.put_blob("PGSR", nullptr, 0); // ?
			packet.put_integer("PMAX", maxPlayers);
			packet.put_integer("PRES", presence);
			packet.put_integer("QCAP", queueCapacity);
			packet.put_integer("RGID", rgid);

			packet.push_list("SEAT", TDF::Type::Integer);
			for (const auto value : seat) {
				packet.put_integer("", value);
			}
			packet.pop();

			packet.push_list("SIDL", TDF::Type::Integer);
			for (const auto value : sidl) {
				packet.put_integer("", value);
			}
			packet.pop();

			packet.put_integer("SLOT", slot);
			packet.put_integer("TCAP", tcap);

			packet.push_list("TIDS", TDF::Type::Integer);
			for (const auto value : tids) {
				packet.put_integer("", value);
			}
			packet.pop();

			packet.put_integer("TIDX", tIndex);
			packet.put_integer("VOIP", VoipTopology::Disabled);
			packet.put_string("VSTR", version);
		}
	}
}
