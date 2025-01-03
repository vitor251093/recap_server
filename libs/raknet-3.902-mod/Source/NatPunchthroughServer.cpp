#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_NatPunchthroughServer==1

#include "NatPunchthroughServer.h"
#include "SocketLayer.h"
#include "BitStream.h"
#include "MessageIdentifiers.h"
#include "RakPeerInterface.h"
#include "MTUSize.h"
#include "GetTime.h"
#include "PacketLogger.h"

void NatPunchthroughServerDebugInterface_Printf::OnServerMessage(const char *msg)
{
	printf("%s\n", msg);
}
#if _RAKNET_SUPPORT_PacketLogger==1
void NatPunchthroughServerDebugInterface_PacketLogger::OnServerMessage(const char *msg)
{
	if (pl)
	{
		pl->WriteMiscellaneous("Nat", msg);
	}
}
#endif

void NatPunchthroughServer::User::DeleteConnectionAttempt(NatPunchthroughServer::ConnectionAttempt *ca)
{
	unsigned int index = connectionAttempts.GetIndexOf(ca);
	if ((unsigned int)index!=(unsigned int)-1)
	{
		RakNet::OP_DELETE(ca,__FILE__,__LINE__);
		connectionAttempts.RemoveAtIndex(index);
	}
}
void NatPunchthroughServer::User::DerefConnectionAttempt(NatPunchthroughServer::ConnectionAttempt *ca)
{
	unsigned int index = connectionAttempts.GetIndexOf(ca);
	if ((unsigned int)index!=(unsigned int)-1)
	{
		connectionAttempts.RemoveAtIndex(index);
	}
}
bool NatPunchthroughServer::User::HasConnectionAttemptToUser(User *user)
{
	unsigned int index;
	for (index=0; index < connectionAttempts.Size(); index++)
	{
		if (connectionAttempts[index]->recipient->guid==user->guid ||
			connectionAttempts[index]->sender->guid==user->guid)
			return true;
	}
	return false;
}
void NatPunchthroughServer::User::LogConnectionAttempts(RakNet::RakString &rs)
{
	rs.Clear();
	unsigned int index;
	char guidStr[128], ipStr[128];
	guid.ToString(guidStr);
	systemAddress.ToString(true,ipStr);
	rs=RakNet::RakString("User systemAddress=%s guid=%s\n", ipStr, guidStr);
	rs+=RakNet::RakString("%i attempts in list:\n", connectionAttempts.Size());
	for (index=0; index < connectionAttempts.Size(); index++)
	{
		rs+=RakNet::RakString("%i. SessionID=%i ", index+1, connectionAttempts[index]->sessionId);
		if (connectionAttempts[index]->sender==this)
			rs+="(We are sender) ";
		else
			rs+="(We are recipient) ";
		if (isReady)
			rs+="(READY TO START) ";
		else
			rs+="(NOT READY TO START) ";
		if (connectionAttempts[index]->attemptPhase==NatPunchthroughServer::ConnectionAttempt::NAT_ATTEMPT_PHASE_NOT_STARTED)
			rs+="(NOT_STARTED). ";
		else
			rs+="(GETTING_RECENT_PORTS). ";
		if (connectionAttempts[index]->sender==this)
		{
			connectionAttempts[index]->recipient->guid.ToString(guidStr);
			connectionAttempts[index]->recipient->systemAddress.ToString(true,ipStr);
		}
		else
		{
			connectionAttempts[index]->sender->guid.ToString(guidStr);
			connectionAttempts[index]->sender->systemAddress.ToString(true,ipStr);
		}

		rs+=RakNet::RakString("Target systemAddress=%s, guid=%s.\n", ipStr, guidStr);
	}
}

int NatPunchthroughServer::NatPunchthroughUserComp( const RakNetGUID &key, User * const &data )
{
	if (key < data->guid)
		return -1;
	if (key > data->guid)
		return 1;
	return 0;
}

NatPunchthroughServer::NatPunchthroughServer()
{
	lastUpdate=0;
	sessionId=0;
	natPunchthroughServerDebugInterface=0;
}
NatPunchthroughServer::~NatPunchthroughServer()
{
	User *user, *otherUser;
	ConnectionAttempt *connectionAttempt;
	unsigned int j;
	while(users.Size())
	{
		user = users[0];
		for (j=0; j < user->connectionAttempts.Size(); j++)
		{
			connectionAttempt=user->connectionAttempts[j];
			if (connectionAttempt->sender==user)
				otherUser=connectionAttempt->recipient;
			else
				otherUser=connectionAttempt->sender;
			otherUser->DeleteConnectionAttempt(connectionAttempt);
		}
		RakNet::OP_DELETE(user,__FILE__,__LINE__);
		users[0]=users[users.Size()-1];
		users.RemoveAtIndex(users.Size()-1);
	}
}
void NatPunchthroughServer::SetDebugInterface(NatPunchthroughServerDebugInterface *i)
{
	natPunchthroughServerDebugInterface=i;
}
void NatPunchthroughServer::Update(void)
{
	ConnectionAttempt *connectionAttempt;
	User *user, *recipient;
	unsigned int i,j;
	RakNetTime time = RakNet::GetTime();
	if (time > lastUpdate+250)
	{
		lastUpdate=time;

		for (i=0; i < users.Size(); i++)
		{
			user=users[i];
			for (j=0; j < user->connectionAttempts.Size(); j++)
			{
				connectionAttempt=user->connectionAttempts[j];
				if (connectionAttempt->sender==user)
				{
					if (connectionAttempt->attemptPhase!=ConnectionAttempt::NAT_ATTEMPT_PHASE_NOT_STARTED &&
						time > connectionAttempt->startTime &&
						time > 10000 + connectionAttempt->startTime ) // Formerly 5000, but sometimes false positives
					{
						RakNet::BitStream outgoingBs;
						
						// that other system might not be running the plugin
						outgoingBs.Write((MessageID)ID_NAT_TARGET_UNRESPONSIVE);
						outgoingBs.Write(connectionAttempt->recipient->guid);
						outgoingBs.Write(connectionAttempt->sessionId);
						rakPeerInterface->Send(&outgoingBs,HIGH_PRIORITY,RELIABLE_ORDERED,0,connectionAttempt->sender->systemAddress,false);

						// 05/28/09 Previously only told sender about ID_NAT_CONNECTION_TO_TARGET_LOST
						// However, recipient may be expecting it due to external code
						// In that case, recipient would never get any response if the sender dropped
						outgoingBs.Reset();
						outgoingBs.Write((MessageID)ID_NAT_TARGET_UNRESPONSIVE);
						outgoingBs.Write(connectionAttempt->sender->guid);
						outgoingBs.Write(connectionAttempt->sessionId);
						rakPeerInterface->Send(&outgoingBs,HIGH_PRIORITY,RELIABLE_ORDERED,0,connectionAttempt->recipient->systemAddress,false);

						connectionAttempt->sender->isReady=true;
						connectionAttempt->recipient->isReady=true;
						recipient=connectionAttempt->recipient;


						if (natPunchthroughServerDebugInterface)
						{
							char str[1024];
							char addr1[128], addr2[128];
							// 8/01/09 Fixed bug where this was after DeleteConnectionAttempt()
							connectionAttempt->sender->systemAddress.ToString(true,addr1);
							connectionAttempt->recipient->systemAddress.ToString(true,addr2);
							sprintf(str, "Sending ID_NAT_TARGET_UNRESPONSIVE to sender %s and recipient %s.", addr1, addr2);
							natPunchthroughServerDebugInterface->OnServerMessage(str);
							RakNet::RakString log;
							connectionAttempt->sender->LogConnectionAttempts(log);
							connectionAttempt->recipient->LogConnectionAttempts(log);
						}


						connectionAttempt->sender->DerefConnectionAttempt(connectionAttempt);
						connectionAttempt->recipient->DeleteConnectionAttempt(connectionAttempt);

						StartPunchthroughForUser(user);
						StartPunchthroughForUser(recipient);

						break;
					}
				}
			}
		}
	}
}
PluginReceiveResult NatPunchthroughServer::OnReceive(Packet *packet)
{
	switch (packet->data[0])
	{
	case ID_NAT_PUNCHTHROUGH_REQUEST:
		OnNATPunchthroughRequest(packet);
		return RR_STOP_PROCESSING_AND_DEALLOCATE;
	case ID_NAT_GET_MOST_RECENT_PORT:
		OnGetMostRecentPort(packet);
		return RR_STOP_PROCESSING_AND_DEALLOCATE;
	case ID_NAT_CLIENT_READY:
		OnClientReady(packet);
		return RR_STOP_PROCESSING_AND_DEALLOCATE;
	}
	return RR_CONTINUE_PROCESSING;
}
void NatPunchthroughServer::OnClosedConnection(SystemAddress systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason )
{
	(void) lostConnectionReason;
	(void) systemAddress;

	unsigned int i=0;
	bool objectExists;
	i = users.GetIndexFromKey(rakNetGUID, &objectExists);
	if (objectExists)
	{
		RakNet::BitStream outgoingBs;
		DataStructures::List<User *> freedUpInProgressUsers;
		User *user = users[i];
		User *otherUser;
		unsigned int connectionAttemptIndex;
		ConnectionAttempt *connectionAttempt;
		for (connectionAttemptIndex=0; connectionAttemptIndex < user->connectionAttempts.Size(); connectionAttemptIndex++)
		{
			connectionAttempt=user->connectionAttempts[connectionAttemptIndex];
			outgoingBs.Reset();
			if (connectionAttempt->recipient==user)
			{
				otherUser=connectionAttempt->sender;
			}
			else
			{
				otherUser=connectionAttempt->recipient;
			}

			// 05/28/09 Previously only told sender about ID_NAT_CONNECTION_TO_TARGET_LOST
			// However, recipient may be expecting it due to external code
			// In that case, recipient would never get any response if the sender dropped
			outgoingBs.Write((MessageID)ID_NAT_CONNECTION_TO_TARGET_LOST);
			outgoingBs.Write(rakNetGUID);
			outgoingBs.Write(connectionAttempt->sessionId);
			rakPeerInterface->Send(&outgoingBs,HIGH_PRIORITY,RELIABLE_ORDERED,0,otherUser->systemAddress,false);

			// 4/22/09 - Bug: was checking inProgress, legacy variable not used elsewhere
			if (connectionAttempt->attemptPhase==ConnectionAttempt::NAT_ATTEMPT_PHASE_GETTING_RECENT_PORTS)
			{
				otherUser->isReady=true;
				freedUpInProgressUsers.Insert(otherUser, __FILE__, __LINE__ );
			}

			otherUser->DeleteConnectionAttempt(connectionAttempt);
		}

		RakNet::OP_DELETE(users[i], __FILE__, __LINE__);
		users.RemoveAtIndex(i);

		for (i=0; i < freedUpInProgressUsers.Size(); i++)
		{
			StartPunchthroughForUser(freedUpInProgressUsers[i]);
		}
	}
}

void NatPunchthroughServer::OnNewConnection(SystemAddress systemAddress, RakNetGUID rakNetGUID, bool isIncoming)
{
	(void) systemAddress;
	(void) isIncoming;

	User *user = RakNet::OP_NEW<User>(__FILE__,__LINE__);
	user->guid=rakNetGUID;
	user->mostRecentPort=0;
	user->systemAddress=systemAddress;
	user->isReady=true;
	users.Insert(rakNetGUID, user, true, __FILE__,__LINE__);
}
void NatPunchthroughServer::OnNATPunchthroughRequest(Packet *packet)
{
	RakNet::BitStream outgoingBs;
	RakNet::BitStream incomingBs(packet->data, packet->length, false);
	incomingBs.IgnoreBytes(sizeof(MessageID));
	RakNetGUID recipientGuid, senderGuid;
	incomingBs.Read(recipientGuid);
	senderGuid=packet->guid;
	unsigned int i;
	bool objectExists;
	i = users.GetIndexFromKey(senderGuid, &objectExists);
	RakAssert(objectExists);

	ConnectionAttempt *ca = RakNet::OP_NEW<ConnectionAttempt>(__FILE__,__LINE__);
	ca->sender=users[i];
	ca->sessionId=sessionId++;
	i = users.GetIndexFromKey(recipientGuid, &objectExists);
	if (objectExists==false)
	{
		outgoingBs.Write((MessageID)ID_NAT_TARGET_NOT_CONNECTED);
		outgoingBs.Write(recipientGuid);
		rakPeerInterface->Send(&outgoingBs,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);
		RakNet::OP_DELETE(ca,__FILE__,__LINE__);
		return;
	}
	ca->recipient=users[i];
	if (ca->recipient->HasConnectionAttemptToUser(ca->sender))
	{
		outgoingBs.Write((MessageID)ID_NAT_ALREADY_IN_PROGRESS);
		outgoingBs.Write(recipientGuid);
		rakPeerInterface->Send(&outgoingBs,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);
		RakNet::OP_DELETE(ca,__FILE__,__LINE__);
		return;
	}

	ca->sender->connectionAttempts.Insert(ca, __FILE__, __LINE__ );
	ca->recipient->connectionAttempts.Insert(ca, __FILE__, __LINE__ );

	StartPunchthroughForUser(ca->sender);
}
void NatPunchthroughServer::OnClientReady(Packet *packet)
{
	unsigned int i;
	bool objectExists;
	i = users.GetIndexFromKey(packet->guid, &objectExists);
	if (objectExists)
	{
		users[i]->isReady=true;
		StartPunchthroughForUser(users[i]);
	}
}

void NatPunchthroughServer::OnGetMostRecentPort(Packet *packet)
{
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	uint16_t sessionId;
	unsigned short mostRecentPort;
	bsIn.Read(sessionId);
	bsIn.Read(mostRecentPort);

	unsigned int i,j;
	User *user;
	ConnectionAttempt *connectionAttempt;
	bool objectExists;
	i = users.GetIndexFromKey(packet->guid, &objectExists);

	if (natPunchthroughServerDebugInterface)
	{
		RakNet::RakString log;
		char addr1[128], addr2[128];
		packet->systemAddress.ToString(true,addr1);
		packet->guid.ToString(addr2);
		log=RakNet::RakString("Got ID_NAT_GET_MOST_RECENT_PORT from systemAddress %s guid %s. port=%i. sessionId=%i. userFound=%i.", addr1, addr2, mostRecentPort, sessionId, objectExists);
		natPunchthroughServerDebugInterface->OnServerMessage(log.C_String());
	}

	if (objectExists)
	{
		user=users[i];
		user->mostRecentPort=mostRecentPort;
		RakNetTime time = RakNet::GetTime();

		for (j=0; j < user->connectionAttempts.Size(); j++)
		{
			connectionAttempt=user->connectionAttempts[j];
			if (connectionAttempt->attemptPhase==ConnectionAttempt::NAT_ATTEMPT_PHASE_GETTING_RECENT_PORTS &&
				connectionAttempt->sender->mostRecentPort!=0 &&
				connectionAttempt->recipient->mostRecentPort!=0 &&
				// 04/29/08 add sessionId to prevent processing for other systems
				connectionAttempt->sessionId==sessionId)
			{
				SystemAddress senderSystemAddress = connectionAttempt->sender->systemAddress;
				SystemAddress recipientSystemAddress = connectionAttempt->recipient->systemAddress;
				SystemAddress recipientTargetAddress = recipientSystemAddress;
				SystemAddress senderTargetAddress = senderSystemAddress;
				recipientTargetAddress.port=connectionAttempt->recipient->mostRecentPort;
				senderTargetAddress.port=connectionAttempt->sender->mostRecentPort;

				// Pick a time far enough in the future that both systems will have gotten the message
				int targetPing = rakPeerInterface->GetAveragePing(recipientTargetAddress);
				int senderPing = rakPeerInterface->GetAveragePing(senderSystemAddress);
				RakNetTime simultaneousAttemptTime;
				if (targetPing==-1 || senderPing==-1)
					simultaneousAttemptTime = time + 1500;
				else
				{
					int largerPing = targetPing > senderPing ? targetPing : senderPing;
					if (largerPing * 4 < 100)
						simultaneousAttemptTime = time + 100;
					else
						simultaneousAttemptTime = time + (largerPing * 4);
				}


				if (natPunchthroughServerDebugInterface)
				{
					RakNet::RakString log;
					char addr1[128], addr2[128];
					recipientSystemAddress.ToString(true,addr1);
					connectionAttempt->recipient->guid.ToString(addr2);
					log=RakNet::RakString("Sending ID_NAT_CONNECT_AT_TIME to recipient systemAddress %s guid %s", addr1, addr2);
					natPunchthroughServerDebugInterface->OnServerMessage(log.C_String());
				}

				// Send to recipient timestamped message to connect at time
				RakNet::BitStream bsOut;
				bsOut.Write((MessageID)ID_TIMESTAMP);
				bsOut.Write(simultaneousAttemptTime);
				bsOut.Write((MessageID)ID_NAT_CONNECT_AT_TIME);
				bsOut.Write(connectionAttempt->sessionId);
				bsOut.Write(senderTargetAddress); // Public IP, using most recent port
				for (j=0; j < MAXIMUM_NUMBER_OF_INTERNAL_IDS; j++) // Internal IP
					bsOut.Write(rakPeerInterface->GetInternalID(senderSystemAddress,j));
				bsOut.Write(connectionAttempt->sender->guid);
				bsOut.Write(false);
				rakPeerInterface->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,recipientSystemAddress,false);


				if (natPunchthroughServerDebugInterface)
				{
					RakNet::RakString log;
					char addr1[128], addr2[128];
					senderSystemAddress.ToString(true,addr1);
					connectionAttempt->sender->guid.ToString(addr2);
					log=RakNet::RakString("Sending ID_NAT_CONNECT_AT_TIME to sender systemAddress %s guid %s", addr1, addr2);
					natPunchthroughServerDebugInterface->OnServerMessage(log.C_String());
				}


				// Same for sender
				bsOut.Reset();
				bsOut.Write((MessageID)ID_TIMESTAMP);
				bsOut.Write(simultaneousAttemptTime);
				bsOut.Write((MessageID)ID_NAT_CONNECT_AT_TIME);
				bsOut.Write(connectionAttempt->sessionId);
				bsOut.Write(recipientTargetAddress); // Public IP, using most recent port
				for (j=0; j < MAXIMUM_NUMBER_OF_INTERNAL_IDS; j++) // Internal IP
					bsOut.Write(rakPeerInterface->GetInternalID(recipientSystemAddress,j));						
				bsOut.Write(connectionAttempt->recipient->guid);
				bsOut.Write(true);
				rakPeerInterface->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,senderSystemAddress,false);

				connectionAttempt->recipient->DerefConnectionAttempt(connectionAttempt);
				connectionAttempt->sender->DeleteConnectionAttempt(connectionAttempt);

				// 04/29/08 missing return
				return;
			}
		}
	}
	else
	{

		if (natPunchthroughServerDebugInterface)
		{
			RakNet::RakString log;
			char addr1[128], addr2[128];
			packet->systemAddress.ToString(true,addr1);
			packet->guid.ToString(addr2);
			log=RakNet::RakString("Ignoring ID_NAT_GET_MOST_RECENT_PORT from systemAddress %s guid %s", addr1, addr2);
			natPunchthroughServerDebugInterface->OnServerMessage(log.C_String());
		}

	}
}
void NatPunchthroughServer::StartPunchthroughForUser(User *user)
{
	if (user->isReady==false)
		return;

	ConnectionAttempt *connectionAttempt;
	User *sender,*recipient,*otherUser;
	unsigned int i;
	for (i=0; i < user->connectionAttempts.Size(); i++)
	{
		connectionAttempt=user->connectionAttempts[i];
		if (connectionAttempt->sender==user)
		{
			otherUser=connectionAttempt->recipient;
			sender=user;
			recipient=otherUser;
		}
		else
		{
			otherUser=connectionAttempt->sender;
			recipient=user;
			sender=otherUser;
		}

		if (otherUser->isReady)
		{
			if (natPunchthroughServerDebugInterface)
			{
				char str[1024];
				char addr1[128], addr2[128];
				sender->systemAddress.ToString(true,addr1);
				recipient->systemAddress.ToString(true,addr2);
				sprintf(str, "Sending NAT_ATTEMPT_PHASE_GETTING_RECENT_PORTS to sender %s and recipient %s.", addr1, addr2);
				natPunchthroughServerDebugInterface->OnServerMessage(str);
			}

			sender->isReady=false;
			recipient->isReady=false;
			connectionAttempt->attemptPhase=ConnectionAttempt::NAT_ATTEMPT_PHASE_GETTING_RECENT_PORTS;
			connectionAttempt->startTime=RakNet::GetTime();

			sender->mostRecentPort=0;
			recipient->mostRecentPort=0;

			RakNet::BitStream outgoingBs;
			outgoingBs.Write((MessageID)ID_NAT_GET_MOST_RECENT_PORT);
			// 4/29/09 Write sessionID so we don't use returned port for a system we don't want
			outgoingBs.Write(connectionAttempt->sessionId);
			rakPeerInterface->Send(&outgoingBs,HIGH_PRIORITY,RELIABLE_ORDERED,0,sender->systemAddress,false);
			rakPeerInterface->Send(&outgoingBs,HIGH_PRIORITY,RELIABLE_ORDERED,0,recipient->systemAddress,false);

			// 4/22/09 - BUG: missing break statement here
			break;
		}
	}
}

#endif // _RAKNET_SUPPORT_*
