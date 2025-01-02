
// Include
#include "gamemanagercomponent.h"
#include "usersessioncomponent.h"
#include "playgroupscomponent.h"

#include "blaze/client.h"
#include "blaze/functions.h"
#include "game/gamemanager.h"
#include "sporenet/instance.h"
#include "sporenet/user.h"
#include "utils/functions.h"

#include <iostream>

#ifdef GetObject
#	undef GetObject
#endif

/* GOOD:

[11:16:29.242]  |             GID = 2 (0x00000002)
[11:16:29.242]  |             GNAM = "Dalkon's Game"
[11:16:29.243]  |             GPVH = 1 (0x0000000000000001)
[11:16:29.243]  |             GSET = 260 (0x00000104)
[11:16:29.244]  |             GSET = 260 (0x00000104)
[11:16:29.244]  |             GSID = 1 (0x0000000000000001)
[11:16:29.245]  |             GSTA = INITIALIZING (1) (0x00000001)
[11:16:29.245]  |             GTYP = ""
[11:16:29.248]  |                     IP = 3232235632 (0xC0A80070)
[11:16:29.248]  |                     PORT = 3659 (0x0E4B)
[11:16:29.249]  |                   }
[11:16:29.249]  |                     IP = 0 (0x00000000)
[11:16:29.250]  |                     PORT = 3659 (0x0E4B)
[11:16:29.250]  |                   }
[11:16:29.250]  |                 }
[11:16:29.251]  |               }
[11:16:29.251]  |             ]
[11:16:29.251]  |             HSES = 13666 (0x00003562)
[11:16:29.252]  |             IGNO = false
[11:16:29.252]  |             ]
[11:16:29.253]  |             MCAP = 1 (0x0001)
[11:16:29.253]  |               DBPS = 100 (0x00000064)
[11:16:29.254]  |               NATT = NAT_TYPE_OPEN (0) (0x00000000)
[11:16:29.254]  |               UBPS = 100 (0x00000064)
[11:16:29.254]  |             }
[11:16:29.255]  |             NRES = true
[11:16:29.255]  |             NTOP = CLIENT_SERVER_DEDICATED (1) (0x00000001)
[11:16:29.255]  |             PGID = ""
[11:16:29.257]  |             }
[11:16:29.258]  |               HPID = 2 (0x0000000000000002)
[11:16:29.258]  |               HSLT = 1 (0x01)
[11:16:29.259]  |             }
[11:16:29.259]  |             PRES = PRESENCE_MODE_STANDARD (1) (0x00000001)
[11:16:29.260]  |             PSAS = "ams"
[11:16:29.260]  |             QCAP = 0 (0x0000)
[11:16:29.260]  |             SEED = 0 (0x00000000)
[11:16:29.261]  |             TCAP = 0 (0x0000)
[11:16:29.261]  |               HPID = 2 (0x0000000000000002)
[11:16:29.261]  |               HSLT = 0 (0x00)
[11:16:29.262]  |             }
[11:16:29.262]  |               [0] = 0 (0x0000)
[11:16:29.263]  |             ]
[11:16:29.263]  |             UUID = "71bc4bdb-82ec-494d-8d75-ca5123b827ac"
[11:16:29.263]  |             VOIP = VOIP_DISABLED (0) (0x00000000)
[11:16:29.264]  |             VSTR = "5.3.0.127"
[11:16:29.264]  |             }
[11:16:29.265]  |             }
[11:16:29.265]  |           }
[11:16:29.267]  |               }
[11:16:29.268]  |               EXID = 0 (0x0000000000000000)
[11:16:29.268]  |               GID = 2 (0x00000002)
[11:16:29.268]  |               LOC = 1701729619 (0x656E5553)
[11:16:29.269]  |               NAME = "Dalkon"
[11:16:29.269]  |               ]
[11:16:29.270]  |               PID = 2 (0x0000000000000002)
[11:16:29.270]  |                     IP = 0 (0x00000000)
[11:16:29.270]  |                     PORT = 0 (0x0000)
[11:16:29.271]  |                   }
[11:16:29.271]  |                     IP = 0 (0x00000000)
[11:16:29.271]  |                     PORT = 3659 (0x0E4B)
[11:16:29.272]  |                   }
[11:16:29.272]  |                 }
[11:16:29.273]  |               }
[11:16:29.273]  |               SID = 0 (0x00)
[11:16:29.274]  |               SLOT = SLOT_PUBLIC (0) (0x00000000)
[11:16:29.274]  |               STAT = ACTIVE_CONNECTED (4) (0x00000004)
[11:16:29.274]  |               TIDX = 65535 (0xFFFF)
[11:16:29.275]  |               TIME = 1584872189 (0x000000005E773AFD)
[11:16:29.275]  |               UGID = 0/0/0
[11:16:29.275]  |               UID = 2 (0x00000002)
[11:16:29.277]  |             }
[11:16:29.278]  |           ]
[11:16:29.278]  |               DCTX = CREATE_GAME_SETUP_CONTEXT (0) (0x00000000)
[11:16:29.279]  |             }
[11:16:29.279]  |           }

*/

/* BAD:

[11:27:58.590]  |             GID = 1 (0x00000001)
[11:27:58.590]  |             GNAM = "Dalkon's Game"
[11:27:58.591]  |             GPVH = 1 (0x0000000000000001)
[11:27:58.591]  |             GSET = 260 (0x00000104)
[11:27:58.591]  |             GSET = 260 (0x00000104)
[11:27:58.592]  |             GSID = 1 (0x0000000000000001)
[11:27:58.592]  |             GSTA = INITIALIZING (1) (0x00000001)
[11:27:58.592]  |             GTYP = ""
[11:27:58.593]  |                     IP = 3232235632 (0xC0A80070)
[11:27:58.593]  |                     PORT = 3659 (0x0E4B)
[11:27:58.594]  |                   }
[11:27:58.595]  |                     IP = 0 (0x00000000)
[11:27:58.596]  |                     PORT = 3659 (0x0E4B)
[11:27:58.596]  |                   }
[11:27:58.597]  |                 }
[11:27:58.597]  |               }
[11:27:58.598]  |             ]
[11:27:58.598]  |             HSES = 13666 (0x00003562)
[11:27:58.598]  |             IGNO = false
[11:27:58.599]  |             ]
[11:27:58.599]  |             MCAP = 1 (0x0001)
[11:27:58.600]  |               DBPS = 100 (0x00000064)
[11:27:58.600]  |               NATT = NAT_TYPE_OPEN (0) (0x00000000)
[11:27:58.600]  |               UBPS = 100 (0x00000064)
[11:27:58.601]  |             }
[11:27:58.601]  |             NRES = true
[11:27:58.601]  |             NTOP = CLIENT_SERVER_DEDICATED (1) (0x00000001)
[11:27:58.602]  |             PGID = ""
[11:27:58.602]  |             }
[11:27:58.603]  |               HPID = 2 (0x0000000000000002)
[11:27:58.603]  |               HSLT = 1 (0x01)
[11:27:58.604]  |             }
[11:27:58.606]  |             PRES = PRESENCE_MODE_STANDARD (1) (0x00000001)
[11:27:58.606]  |             PSAS = "ams"
[11:27:58.607]  |             QCAP = 0 (0x0000)
[11:27:58.607]  |             SEED = 0 (0x00000000)
[11:27:58.607]  |             TCAP = 0 (0x0000)
[11:27:58.608]  |               HPID = 2 (0x0000000000000002)
[11:27:58.608]  |               HSLT = 0 (0x00)
[11:27:58.608]  |             }
[11:27:58.609]  |               [0] = 0 (0x0000)
[11:27:58.609]  |             ]
[11:27:58.610]  |             UUID = "71bc4bdb-82ec-494d-8d75-ca5123b827ac"
[11:27:58.610]  |             VOIP = VOIP_DISABLED (0) (0x00000000)
[11:27:58.610]  |             VSTR = "5.3.0.127"
[11:27:58.611]  |             }
[11:27:58.611]  |             }
[11:27:58.611]  |           }
[11:27:58.612]  |               }
[11:27:58.612]  |               EXID = 0 (0x0000000000000000)
[11:27:58.613]  |               GID = 1 (0x00000001)
[11:27:58.613]  |               LOC = 1701729619 (0x656E5553)
[11:27:58.614]  |               NAME = "Dalkon"
[11:27:58.614]  |               ]
[11:27:58.616]  |               PID = 2 (0x0000000000000002)
[11:27:58.616]  |                     IP = 3232235632 (0xC0A80070)
[11:27:58.617]  |                     PORT = 3659 (0x0E4B)
[11:27:58.617]  |                   }
[11:27:58.618]  |                     IP = 0 (0x00000000)
[11:27:58.618]  |                     PORT = 3659 (0x0E4B)
[11:27:58.618]  |                   }
[11:27:58.619]  |                 }
[11:27:58.619]  |               }
[11:27:58.619]  |               SID = 0 (0x00)
[11:27:58.620]  |               SLOT = SLOT_PUBLIC (0) (0x00000000)
[11:27:58.620]  |               STAT = ACTIVE_CONNECTED (4) (0x00000004)
[11:27:58.621]  |               TIDX = 65535 (0xFFFF)
[11:27:58.621]  |               TIME = 1584872878 (0x000000005E773DAE)
[11:27:58.621]  |               UGID = 0/0/0
[11:27:58.622]  |               UID = 2 (0x00000002)
[11:27:58.622]  |             }
[11:27:58.623]  |           ]
[11:27:58.624]  |               DCTX = CREATE_GAME_SETUP_CONTEXT (0) (0x00000000)
[11:27:58.626]  |             }
[11:27:58.626]  |           }

*/

/*
	STAT
		0 = Boot
		1 = Login
		2 = Moving towards editor (Spaceship any?)
		3 = Squad/Hero screen
		4 = Navigation/Spaceship
		5 = Predungeon
		6 = Unknown (cStateMachine in exe)
		7 = Editor (cStateMachine in exe)
		8 = Cinematic
		9 = Spectator
		10 = Replay
		11 = Chain voting
		12 = Chain cashout
		13 = Game over
		15 = Arena lobby
		16 = Arena round results
		17 = Juggernaut lobby
		18 = Juggernaut results
		19 = Killrace lobby
		20 = Killrace results


	Gamemodes
		Tutorial = 1
		Chain(Matched/Premade) = 2
		Arena = 3
		KillRace = 4
		Juggernaut = 5
		Quickplay = 6
		DirectEntry = 7

	Blaze Fields
		PDAT
			BLOB = 0x20
			EXID = 0x30
			GID = 0x38
			LOC = 0x38
			NAME = 0x24
			PATT = 0x54
			PID = 0x34
			PNET = 0x14
			SID = 0x48
			SLOT = 0x1C
			STAT = 0x1C
			TIDX = 0x40
			TIME = 0x34
			UGID = 0x08
			UID = 0x38

		ReplicatedPlayerData
			BLOB = 0x20
			EXID = 0x30
			GID = 0x38
			LOC = 0x38
			NAME = 0x24
			PATT = 0x54
			PID = 0x34
			PNET = 0x14
			SID = 0x48
			SLOT = 0x1C
			STAT = 0x1C
			TIDX = 0x40
			TIME = 0x34
			UGID = 0x08
			UID = 0x38

		ReplicatedGameData
			ADMN = 0x58
			ATTR = 0x54
			CAP = 0x58
			CRIT = 0x54
			GID = 0x38
			GNAM = 0x24
			GPVH = 0x30
			GSET = 0x28
			GSID = 0x30
			GSTA = 0x1C
			GTYP = 0x24
			HNET = 0x58
			HSES = 0x38
			IGNO = 0x50
			MATR = 0x54
			MCAP = 0x40
			NQOS = 0x18
			NRES = 0x50
			NTOP = 0x1C
			PGID = 0x24
			PGSR = 0x20
			PHST = 0x18
			PRES = 0x1C
			PSAS = 0x24
			QCAP = 0x40
			SEED = 0x38
			TCAP = 0x40
			THST = 0x18
			TIDS = 0x58
			UUID = 0x24
			VOIP = 0x1C
			VSTR = 0x24
			XNNC = 0x20
			XSES = 0x20

		IndirectJoinGameSetupContext
			GRID = 0x08
			RPVC = 0x50

		ResetDedicatedServerSetupContext
			ERR = 0x38

		GameBrowserGameData
			ADMN = 0x58
			ATTR = 0x54
			CAP = 0x58
			CRIT = 0x54
			GID = 0x38
			GNAM = 0x24
			GSET = 0x28
			GSTA = 0x1C
			HNET = 0x58
			HOST = 0x34
			PCNT = 0x58
			PRES = 0x1C
			PSID = 0x24
			QCAP = 0x40
			QCNT = 0x40
			ROST = 0x58
			SID = 0x30
			TCAP = 0x40
			TINF = 0x58
			VOIP = 0x1C
			VSTR = 0x24

	Request Packets
		CreateGame
			ADMN = 0x58
			ATTR = 0x54
			BTPL = 0x08
			CRIT = 0x54
			GCTR = 0x24
			GNAM = 0x24
			GSET = 0x28
			GTYP = 0x24
			GURL = 0x24
			HNET = 0x58
			IGNO = 0x50
			MATR = 0x54
			NRES = 0x50
			NTOP = 0x1C
			PATT = 0x54
			PCAP = 0x58
			PGID = 0x24
			PGSC = 0x20
			PMAX = 0x40
			PRES = 0x1C
			QCAP = 0x40
			RGID = 0x38
			SEAT = 0x58
			SIDL = 0x58
			SLOT = 0x1C
			TCAP = 0x40
			TIDS = 0x58
			TIDX = 0x40
			VOIP = 0x1C
			VSTR = 0x24

		JoinGame
			ATTR = 0x54
			BTPL = 0x08
			GID = 0x38
			GVER = 0x24
			JMET = 0x1C
			PNET = 0x14
			SLID = 0x48
			SLOT = 0x1C
			TIDX = 0x40
			USER = 0x18

		ResetDedicatedServer
			same as CreateGame?

	Response Packets
		CreateGame
			

		DestroyGame
			GID = 0x38

		JoinGame
			GID = 0x38

		StartMatchmaking
			MSID = 0x38

	Notify Packets
		NotifyGameCreated
			GID = 0x38

		NotifyGameRemoved


		NotifyGameSetup
			GAME = 0x18
			PROS = 0x58
			REAS = 0x14

		NotifyHostMigrationCompleted
			GID = 0x38

		NotifyCreateDynamicDedicatedServerGame
			GREQ = 0x18
			MID = 0x24

		NotifyPlatformHostInitialized
			GID = 0x38
			PHST = 0x48

		NotifyGamePlayerStateChange
			GID = 0x38
			PID = 0x34
			STAT = 0x1C

		NotifyPlatformHostInitialized
			GID = 0x38
			PHST = 0x48
*/

enum PacketID : uint16_t {
	CreateGame = 0x01,
	DestroyGame = 0x02,
	AdvanceGameState = 0x03,
	SetGameSettings = 0x04,
	SetPlayerCapacity = 0x05,
	SetGameAttributes = 0x07,
	SetPlayerAttributes = 0x08,
	JoinGame = 0x09,
	RemovePlayer = 0x0B,
	StartMatchmaking = 0x0D,
	CancelMatchmaking = 0x0E,
	FinalizeGameCreation = 0x0F,
	ListGames = 0x11,
	SetPlayerCustomData = 0x12,
	ReplayGame = 0x13,
	ReturnDedicatedServerToPool = 0x14,
	JoinGameByGroup = 0x15,
	LeaveGameByGroup = 0x16,
	MigrateGame = 0x17,
	UpdateGameHostMigrationStatus = 0x18,
	ResetDedicatedServer = 0x19,
	UpdateGameSession = 0x1A,
	BanPlayer = 0x1B,
	UpdateMeshConnection = 0x1D,
	RemovePlayerFromBannedList = 0x1F,
	ClearBannedList = 0x20,
	GetBannedList = 0x21,
	AddQueuedPlayerToGame = 0x26,
	UpdateGameName = 0x27,
	GetGameListSnapshot = 0x64,
	GetGameListSubscription = 0x65,
	DestroyGameList = 0x66,
	GetFullGameData = 0x67,
	GetMatchmakingConfig = 0x68,
	GetGameDataFromId = 0x69,
	AddAdminPlayer = 0x6A,
	RemoveAdminPlayer = 0x6B,
	SetPlayerTeam = 0x6C,
	ChangePlayerTeam = 0x6D,
	MigrateAdminPlayer = 0x6E,
	GetUserSetGameListSubscription = 0x6F,
	RegisterDynamicDedicatedServerCreator = 0x96,
	UnregisterDynamicDedicatedServerCreator = 0x97,

	// Notifications
	NotifyMatchmakingFailed = 0x0A,
	NotifyMatchmakingAsyncStatus = 0x0C,
	NotifyGameCreated = 0x0F,
	NotifyGameRemoved = 0x10,
	NotifyGameSetup = 0x14,
	NotifyPlayerJoining = 0x15,
	NotifyPlayerJoinCompleted = 0x1E,
	NotifyPlayerRemoved = 0x28,
	NotifyHostMigrationCompleted = 0x3C,
	NotifyHostMigrationStart = 0x46,
	NotifyPlatformHostInitialized = 0x47,
	NotifyGameAttribChange = 0x50,
	NotifyPlayerAttribChange = 0x5A,
	NotifyPlayerCustomDataChange = 0x5F,
	NotifyGameStateChange = 0x64,
	NotifyGameSettingsChange = 0x6E,
	NotifyGameCapacityChange = 0x6F,
	NotifyGameReset = 0x70,
	NotifyGameReportingIdChange = 0x71,
	NotifyGameSessionUpdated = 0x73,
	NotifyGamePlayerStateChange = 0x74,
	NotifyGamePlayerTeamChange = 0x75,
	NotifyGameTeamIdChange = 0x76,
	NotifyProcessQueue = 0x77,
	NotifyGameListUpdate = 0xC9,
	NotifyAdminListChange = 0xCA,
	NotifyCreateDynamicDedicatedServerGame = 0xDC,
	NotifyGameNameChange = 0xE6
};

// Blaze
namespace Blaze {
	// GameManagerComponent
	uint16_t GameManagerComponent::GetId() const {
		return Id;
	}

	std::string_view GameManagerComponent::GetName() const {
		return "GameManager";
	}

	std::string_view GameManagerComponent::GetReplyPacketName(uint16_t command) const {
		switch (static_cast<PacketID>(command)) {
			case PacketID::CreateGame: return "createGame";
			case PacketID::DestroyGame: return "destroyGame";
			case PacketID::AdvanceGameState: return "advanceGameState";
			case PacketID::SetGameSettings: return "setGameSettings";
			case PacketID::SetPlayerCapacity: return "setPlayerCapacity";
			case PacketID::SetGameAttributes: return "setGameAttributes";
			case PacketID::SetPlayerAttributes: return "setPlayerAttributes";
			case PacketID::JoinGame: return "joinGame";
			case PacketID::RemovePlayer: return "removePlayer";
			case PacketID::StartMatchmaking: return "startMatchmaking";
			case PacketID::CancelMatchmaking: return "cancelMatchmaking";
			case PacketID::FinalizeGameCreation: return "finalizeGameCreation";
			case PacketID::ListGames: return "listGames";
			case PacketID::SetPlayerCustomData: return "setPlayerCustomData";
			case PacketID::ReplayGame: return "replayGame";
			case PacketID::ReturnDedicatedServerToPool: return "returnDedicatedServerToPool";
			case PacketID::JoinGameByGroup: return "joinGameByGroup";
			case PacketID::LeaveGameByGroup: return "leaveGameByGroup";
			case PacketID::MigrateGame: return "migrateGame";
			case PacketID::UpdateGameHostMigrationStatus: return "updateGameHostMigrationStatus";
			case PacketID::ResetDedicatedServer: return "resetDedicatedServer";
			case PacketID::UpdateGameSession: return "updateGameSession";
			case PacketID::BanPlayer: return "banPlayer";
			case PacketID::UpdateMeshConnection: return "updateMeshConnection";
			case PacketID::RemovePlayerFromBannedList: return "removePlayerFromBannedList";
			case PacketID::ClearBannedList: return "clearBannedList";
			case PacketID::GetBannedList: return "getBannedList";
			case PacketID::AddQueuedPlayerToGame: return "addQueuedPlayerToGame";
			case PacketID::UpdateGameName: return "updateGameName";
			case PacketID::GetGameListSnapshot: return "getGameListSnapshot";
			case PacketID::GetGameListSubscription: return "getGameListSubscription";
			case PacketID::DestroyGameList: return "destroyGameList";
			case PacketID::GetFullGameData: return "getFullGameData";
			case PacketID::GetMatchmakingConfig: return "getMatchmakingConfig";
			case PacketID::GetGameDataFromId: return "getGameDataFromId";
			case PacketID::AddAdminPlayer: return "addAdminPlayer";
			case PacketID::RemoveAdminPlayer: return "removeAdminPlayer";
			case PacketID::SetPlayerTeam: return "setPlayerTeam";
			case PacketID::ChangePlayerTeam: return "changePlayerTeam";
			case PacketID::MigrateAdminPlayer: return "migrateAdminPlayer";
			case PacketID::GetUserSetGameListSubscription: return "getUserSetGameListSubscription";
			case PacketID::RegisterDynamicDedicatedServerCreator: return "registerDynamicDedicatedServerCreator";
			case PacketID::UnregisterDynamicDedicatedServerCreator: return "unregisterDynamicDedicatedServerCreator";

			default: return "";
		}
	}

	std::string_view GameManagerComponent::GetNotificationPacketName(uint16_t command) const {
		switch (static_cast<PacketID>(command)) {
			case PacketID::NotifyMatchmakingFailed: return "NotifyMatchmakingFailed";
			case PacketID::NotifyMatchmakingAsyncStatus: return "NotifyMatchmakingAsyncStatus";
			case PacketID::NotifyGameCreated: return "NotifyGameCreated";
			case PacketID::NotifyGameRemoved: return "NotifyGameRemoved";
			case PacketID::NotifyGameSetup: return "NotifyGameSetup";
			case PacketID::NotifyPlayerJoining: return "NotifyPlayerJoining";
			case PacketID::NotifyPlayerJoinCompleted: return "NotifyPlayerJoinCompleted";
			case PacketID::NotifyPlayerRemoved: return "NotifyPlayerRemoved";
			case PacketID::NotifyHostMigrationCompleted: return "NotifyHostMigrationCompleted";
			case PacketID::NotifyHostMigrationStart: return "NotifyHostMigrationStart";
			case PacketID::NotifyPlatformHostInitialized: return "NotifyPlatformHostInitialized";
			case PacketID::NotifyGameAttribChange: return "NotifyGameAttribChange";
			case PacketID::NotifyPlayerAttribChange: return "NotifyPlayerAttribChange";
			case PacketID::NotifyPlayerCustomDataChange: return "NotifyPlayerCustomDataChange";
			case PacketID::NotifyGameStateChange: return "NotifyGameStateChange";
			case PacketID::NotifyGameSettingsChange: return "NotifyGameSettingsChange";
			case PacketID::NotifyGameCapacityChange: return "NotifyGameCapacityChange";
			case PacketID::NotifyGameReset: return "NotifyGameReset";
			case PacketID::NotifyGameReportingIdChange: return "NotifyGameReportingIdChange";
			case PacketID::NotifyGameSessionUpdated: return "NotifyGameSessionUpdated";
			case PacketID::NotifyGamePlayerStateChange: return "NotifyGamePlayerStateChange";
			case PacketID::NotifyGamePlayerTeamChange: return "NotifyGamePlayerTeamChange";
			case PacketID::NotifyGameTeamIdChange: return "NotifyGameTeamIdChange";
			case PacketID::NotifyProcessQueue: return "NotifyProcessQueue";
			case PacketID::NotifyGameListUpdate: return "NotifyGameListUpdate";
			case PacketID::NotifyAdminListChange: return "NotifyAdminListChange";
			case PacketID::NotifyCreateDynamicDedicatedServerGame: return "NotifyCreateDynamicDedicatedServerGame";
			case PacketID::NotifyGameNameChange: return "NotifyGameNameChange";

			default: return "";
		}
	}

	bool GameManagerComponent::ParsePacket(Request& request) {
		switch (request.get_command()) {
			case PacketID::CreateGame:
				CreateGame(request);
				break;

			case PacketID::DestroyGame:
				DestroyGame(request);
				break;

			case PacketID::SetPlayerAttributes:
				SetPlayerAttributes(request);
				break;

			case PacketID::JoinGame:
				JoinGame(request);
				break;
			
			case PacketID::RemovePlayer:
				RemovePlayer(request);
				break;

			case PacketID::StartMatchmaking:
				StartMatchmaking(request);
				break;

			case PacketID::CancelMatchmaking:
				CancelMatchmaking(request);
				break;

			case PacketID::FinalizeGameCreation:
				FinalizeGameCreation(request);
				break;

			case PacketID::ResetDedicatedServer:
				ResetDedicatedServer(request);
				break;

			case PacketID::UpdateMeshConnection:
				UpdateMeshConnection(request);
				break;

			default:
				return false;
		}

		return true;
	}

	void GameManagerComponent::WriteCreateGame(TDF::Packet& packet, uint32_t gameId) {
		// TODO: check if this packet even uses any data.
		packet.put_integer("GID", gameId);
	}

	void GameManagerComponent::WriteJoinGame(TDF::Packet& packet, uint32_t gameId) {
		packet.put_integer("GID", gameId);
	}

	void GameManagerComponent::WriteStartMatchmaking(TDF::Packet& packet, uint32_t id) {
		packet.put_integer("MSID", id);
	}

	void GameManagerComponent::WriteCancelMatchmaking(TDF::Packet& packet, uint32_t id) {
		packet.put_integer("MSID", id);
	}

	void GameManagerComponent::NotifyMatchmakingFailed(Request& request, uint32_t id, MatchmakingResult result) {
		const auto& user = request.get_user();
		if (!user) {
			// No user, ignore.
			return;
		}

		TDF::Packet packet;
		packet.put_integer("MAXF", 0);
		packet.put_integer("MSID", id);
		packet.put_integer("RSLT", result);
		packet.put_integer("USID", user->get_id());

		request.notify(packet, Id, PacketID::NotifyMatchmakingFailed);
	}

	void GameManagerComponent::NotifyMatchmakingAsyncStatus(Request& request, uint32_t id) {
		const auto& user = request.get_user();
		if (!user) {
			// No user, ignore.
			return;
		}

		TDF::Packet packet;
		packet.push_list("ASIL", TDF::Type::String);
		// some user list? ill check later.
		packet.pop();

		packet.put_integer("MSID", id);
		packet.put_integer("USID", user->get_id());

		request.notify(packet, Id, PacketID::NotifyMatchmakingAsyncStatus);
	}

	void GameManagerComponent::NotifyGameCreated(Request& request, uint32_t gameId) {
		TDF::Packet packet;
		packet.put_integer("GID", gameId);

		request.notify(packet, Id, PacketID::NotifyGameCreated);
	}

	void GameManagerComponent::NotifyGameRemoved(Request& request, uint32_t gameId, DestroyGameReason reason) {
		TDF::Packet packet;
		packet.put_integer("GID", gameId);
		packet.put_integer("REAS", reason);

		request.notify(packet, Id, PacketID::NotifyGameRemoved);
	}

	void GameManagerComponent::NotifyGameSetup(Request& request, ReplicatedGameData& gameData, std::vector<ReplicatedGamePlayer>& gamePlayers) {
		const auto& user = request.get_user();
		if (!user) {
			return;
		}

		const auto& game = user->get_game();
		if (!game) {
			return;
		}

		TDF::Packet packet;
		
		// Game data
#if 1
		packet.push_struct("GAME");
		gameData.Write(packet);
		packet.pop();

		packet.push_list("PROS", TDF::Type::Struct);
		for (const auto& player : gamePlayers) {
			packet.push_struct("");
			player.Write(packet);
			packet.pop();
		}
		packet.pop();

		packet.push_union("REAS", NetworkAddressMember::XboxClientAddress);
		{
			packet.push_struct("VALU");
			packet.put_integer("DCTX", DatalessSetup::CreateGame);
			// packet.put_integer("ERR", 0);
			packet.pop();
		}
		packet.pop();
#else
		{
			auto& gameStruct = packet.CreateStruct(nullptr, "GAME");
			{
				auto& admnList = packet.CreateList(&gameStruct, "ADMN", TDF::Type::Integer);
				packet.PutInteger(&admnList, "", clientId);
			} {
				auto& attrMap = packet.CreateMap(&gameStruct, "ATTR", TDF::Type::String, TDF::Type::String);
				for (const auto& [key, value] : gameInfo.attributes) {
					packet.PutString(&attrMap, key, value);
				}
			} {
				auto& capList = packet.CreateList(&gameStruct, "CAP", TDF::Type::Integer); // u16 list?
				for (auto value : gameInfo.capacity) {
					packet.PutInteger(&capList, "", value);
				}
			}
			packet.PutInteger(&gameStruct, "GID", gameInfo.id);
			packet.PutString(&gameStruct, "GNAM", gameInfo.name);
			packet.PutInteger(&gameStruct, "GPVH", 1);
			packet.PutInteger(&gameStruct, "GSET", gameInfo.settings);
			packet.PutInteger(&gameStruct, "GSID", 1);
			packet.PutInteger(&gameStruct, "GSTA", gameInfo.state);
			packet.PutString(&gameStruct, "GTYP", gameInfo.type);
			{
				auto& hnetList = packet.CreateList(&gameStruct, "HNET", TDF::Type::Struct, true);
				{
#if 1
					auto& valuStruct = packet.CreateStruct(&hnetList, "");
					{
						auto& exipStruct = packet.CreateStruct(&valuStruct, "EXIP");
						packet.PutInteger(&exipStruct, "IP", gameInfo.hostNetwork.exip.address);
						packet.PutInteger(&exipStruct, "PORT", gameInfo.hostNetwork.exip.port);
					} {
						auto& inipStruct = packet.CreateStruct(&valuStruct, "INIP");
						packet.PutInteger(&inipStruct, "IP", gameInfo.hostNetwork.inip.address);
						packet.PutInteger(&inipStruct, "PORT", gameInfo.hostNetwork.inip.port);
					}
#else
					auto& hnetMemberUnion = packet.CreateUnion(&hnetList, "", NetworkAddressMember::IpPairAddress);
					auto& valuStruct = packet.CreateStruct(&hnetMemberUnion, "VALU");
					{
						auto& exipStruct = packet.CreateStruct(&valuStruct, "EXIP");
						packet.PutInteger(&exipStruct, "IP", gameInfo.hostNetwork.exip.address);
						packet.PutInteger(&exipStruct, "PORT", gameInfo.hostNetwork.exip.port);
					} {
						auto& inipStruct = packet.CreateStruct(&valuStruct, "INIP");
						packet.PutInteger(&inipStruct, "IP", gameInfo.hostNetwork.inip.address);
						packet.PutInteger(&inipStruct, "PORT", gameInfo.hostNetwork.inip.port);
					}
#endif
				}
			}
			packet.PutInteger(&gameStruct, "HSES", 13666);
			packet.PutInteger(&gameStruct, "IGNO", gameInfo.ignore ? 1 : 0);
			packet.PutInteger(&gameStruct, "MCAP", gameInfo.maxPlayers);
			{
				auto& nqosStruct = packet.CreateStruct(&gameStruct, "NQOS");
				packet.PutInteger(&nqosStruct, "DBPS", 100);
				packet.PutInteger(&nqosStruct, "NATT", NatType::Open);
				packet.PutInteger(&nqosStruct, "UBPS", 100);
			}
			packet.PutInteger(&gameStruct, "NRES", gameInfo.resetable ? 0 : 1);
			packet.PutInteger(&gameStruct, "NTOP", gameInfo.networkTopology);
			packet.PutString(&gameStruct, "PGID", gameInfo.playgroupId); // b6852db1-ba37-4b40-aea3-0bd16efba4f9
			packet.PutBlob(&gameStruct, "PGSR", nullptr, 0);
			{
				auto& phstStruct = packet.CreateStruct(&gameStruct, "PHST");
				packet.PutInteger(&phstStruct, "HPID", user->get_id()); // host player id?
				packet.PutInteger(&phstStruct, "HSLT", 1);
			}
			packet.PutInteger(&gameStruct, "PRES", gameInfo.presence);
			packet.PutString(&gameStruct, "PSAS", "ams");
			packet.PutInteger(&gameStruct, "QCAP", gameInfo.queueCapacity);
			packet.PutInteger(&gameStruct, "SEED", 0);
			packet.PutInteger(&gameStruct, "TCAP", gameInfo.tcap);
			{
				auto& thstStruct = packet.CreateStruct(&gameStruct, "THST");
				packet.PutInteger(&thstStruct, "HPID", gameInfo.id);
				packet.PutInteger(&thstStruct, "HSLT", 0);
			} {
				auto& tidsList = packet.CreateList(&gameStruct, "TIDS", TDF::Type::Integer); // u16 list?
				packet.PutInteger(&tidsList, "", 0);
			}
			packet.PutString(&gameStruct, "UUID", "71bc4bdb-82ec-494d-8d75-ca5123b827ac"); // 714b05dc-93bc-49ac-961c-cb38b574f30a
			packet.PutInteger(&gameStruct, "VOIP", VoipTopology::Disabled);
			packet.PutString(&gameStruct, "VSTR", gameInfo.version);
			packet.PutBlob(&gameStruct, "XNNC", nullptr, 0);
			packet.PutBlob(&gameStruct, "XSES", nullptr, 0);
		}
		{
			auto& prosList = packet.CreateList(nullptr, "PROS", TDF::Type::Struct);
			{
				auto& playerStruct = packet.CreateStruct(&prosList, "");
				packet.PutBlob(&playerStruct, "BLOB", nullptr, 0);
				packet.PutInteger(&playerStruct, "EXID", 0);
				packet.PutInteger(&playerStruct, "GID", game->GetId());
				packet.PutInteger(&playerStruct, "LOC", client->data().lang);
				packet.PutString(&playerStruct, "NAME", user->get_name());
				{
					// PATT
				}
				packet.PutInteger(&playerStruct, "PID", user->get_id());
				{
					auto& pnetUnion = packet.CreateUnion(&playerStruct, "PNET", NetworkAddressMember::IpPairAddress);
					auto& valuStruct = packet.CreateStruct(&pnetUnion, "VALU");
					{
						auto& exipStruct = packet.CreateStruct(&valuStruct, "INIP");
						packet.PutInteger(&exipStruct, "IP", gameInfo.hostNetwork.inip.address);
						packet.PutInteger(&exipStruct, "PORT", gameInfo.hostNetwork.inip.port);
					} {
						auto& inipStruct = packet.CreateStruct(&valuStruct, "EXIP");
						packet.PutInteger(&inipStruct, "IP", gameInfo.hostNetwork.exip.address);
						packet.PutInteger(&inipStruct, "PORT", gameInfo.hostNetwork.exip.port);
					}
				}
				packet.PutInteger(&playerStruct, "SID", 0);
				packet.PutInteger(&playerStruct, "SLOT", 0);
				packet.PutInteger(&playerStruct, "STAT", PlayerState::Connected);
				packet.PutInteger(&playerStruct, "TIDX", 0xFFFF);
				packet.PutInteger(&playerStruct, "TIME", utils::get_unix_time());
				packet.PutObjectId(&playerStruct, "UGID", 0, 0, 0);
				packet.PutInteger(&playerStruct, "UID", client->get_id());
			}
		} {
			auto& reasUnion = packet.CreateUnion(nullptr, "REAS", NetworkAddressMember::XboxClientAddress);
			auto& valuStruct = packet.CreateStruct(&reasUnion, "VALU");
			packet.PutInteger(&valuStruct, "DCTX", DatalessSetup::CreateGame);
			// packet.PutInteger(&valuStruct, "ERR", 0);
		}
#endif
		request.notify(packet, Id, PacketID::NotifyGameSetup);
	}

	void GameManagerComponent::NotifyPlayerJoining(Request& request, const ReplicatedGamePlayer& gamePlayer) {
		const auto& user = request.get_user();
		if (!user) {
			return;
		}

		TDF::Packet packet;
		packet.put_integer("GID", gamePlayer.gameId);

		packet.push_struct("PDAT");
		gamePlayer.Write(packet);
		packet.pop();

		request.notify(packet, Id, PacketID::NotifyPlayerJoining);
	}

	void GameManagerComponent::NotifyPlayerJoinCompleted(Request& request, uint32_t gameId, uint32_t personaId) {
		TDF::Packet packet;
		packet.put_integer("GID", gameId);
		packet.put_integer("PID", personaId);

		request.notify(packet, Id, PacketID::NotifyPlayerJoinCompleted);
	}

	void GameManagerComponent::NotifyPlayerRemoved(Request& request, uint32_t gameId, uint32_t personaId, PlayerRemovedReason reason) {
		TDF::Packet packet;
		packet.put_integer("CNTX", 0);
		packet.put_integer("GID", gameId);
		packet.put_integer("PID", personaId);
		packet.put_integer("REAS", reason);

		request.notify(packet, Id, PacketID::NotifyPlayerRemoved);
	}

	void GameManagerComponent::NotifyPlatformHostInitialized(Request& request, uint64_t gameId) {
		TDF::Packet packet;
		packet.put_integer("GID", gameId);
		packet.put_integer("PHST", 1); // host id (host persona id)?

		request.notify(packet, Id, PacketID::NotifyPlatformHostInitialized);
	}

	void GameManagerComponent::NotifyGameStateChange(Request& request, uint64_t gameId, GameState gameState) {
		TDF::Packet packet;
		packet.put_integer("GID", gameId);
		packet.put_integer("GSTA", gameState);

		request.notify(packet, Id, PacketID::NotifyGameStateChange);
	}

	void GameManagerComponent::NotifyGameReset(Request& request, ReplicatedGameData& gameData) {
		const auto& user = request.get_user();
		if (!user) {
			return;
		}

		TDF::Packet packet;
		packet.push_struct("DATA");
		gameData.Write(packet);
		packet.pop();

		request.notify(packet, Id, PacketID::NotifyGameReset);
	}

	void GameManagerComponent::NotifyGameSessionUpdated(Request& request, uint32_t gameId) {
		TDF::Packet packet;
		packet.put_integer("GID", gameId);
		packet.put_blob("XNNC", nullptr, 0);
		packet.put_blob("XSES", nullptr, 0);

		request.notify(packet, Id, PacketID::NotifyGameSessionUpdated);
	}

	void GameManagerComponent::NotifyGamePlayerStateChange(Request& request, uint32_t gameId, uint32_t personaId, PlayerState playerState) {
		TDF::Packet packet;
		packet.put_integer("GID", gameId);
		packet.put_integer("PID", personaId);
		packet.put_integer("STAT", playerState);

		request.notify(packet, Id, PacketID::NotifyGamePlayerStateChange);
	}

	void GameManagerComponent::NotifyCreateDynamicDedicatedServerGame(Request& request, GameManager::CreateGameRequest& gameData) {
		// Sending this should make the client send back a CreateGameRequest or ResetDedicatedServer
		const auto& user = request.get_user();
		if (!user) {
			return;
		}

		const auto& game = user->get_game();
		if (!game) {
			return;
		}

		const auto& gameInfo = game->GetInfo();

		TDF::Packet packet;
		packet.push_struct("GREQ");
		gameData.Write(packet);
		packet.pop();

		packet.put_string("MID", "1");

		request.notify(packet, Id, PacketID::NotifyCreateDynamicDedicatedServerGame);
	}

	void GameManagerComponent::CreateGame(Request& request) {
		GameManager::CreateGameRequest data;
		data.Read(request.get_request());

		TDF::Packet packet;
		WriteCreateGame(packet, 1);

		request.reply(packet);

		// Notifications
		NotifyGameStateChange(request, 1, GameState::Initializing);
		// NotifyGameSetup(request);
	}

	void GameManagerComponent::DestroyGame(Request& request) {
		auto gameId = request["GID"].GetUint();
		auto reason = static_cast<DestroyGameReason>(request["REAS"].GetUint());

		TDF::Packet packet;
		packet.put_integer("GID", gameId);

		request.reply(packet);

		// Notifications
		NotifyGameRemoved(request, gameId, reason);
	}

	void GameManagerComponent::SetPlayerAttributes(Request& request) {
		// get new attribs?
		request.reply();
	}

	void GameManagerComponent::JoinGame(Request& request) {
		const auto& user = request.get_user();
		if (!user) {
			return;
		}

		uint32_t gameId = request["GID"].GetUint();

		const auto& game = Game::GameManager::GetGame(gameId);
		if (!game) {
			return;
		}

		user->set_game(game);

		const auto& gameInfo = game->GetInfo();
		const auto& client = request.get_client();

		ReplicatedGamePlayer player;
		player.gameId = gameId;
		player.localization = client.data().lang;
		player.name = user->get_name();
		player.id = user->get_id();
		player.hostNetwork = gameInfo.hostNetwork;
		player.slot = 1;
		player.slotType = Slot::Public;
		player.state = PlayerState::Connected;
		player.tIndex = 0xFFFF;
		player.time = utils::get_unix_time();
		player.uid = client.get_id();

		TDF::Packet packet;
		WriteJoinGame(packet, gameId);

		request.reply(packet);

		// Notifications
		// PlaygroupsComponent::NotifyJoinPlaygroup(request);

		NotifyPlayerJoining(request, player);
	}

	void GameManagerComponent::RemovePlayer(Request& request) {
		uint32_t gameId = request["GID"].GetUint();
		int64_t personaId = request["PID"].GetInt64();
		PlayerRemovedReason reason = static_cast<PlayerRemovedReason>(request["REAS"].GetUint());

		const auto& game = Game::GameManager::GetGame(gameId);
		if (game) {
			game->RemovePlayer(personaId);
		}

		const auto& user = SporeNet::Get().GetUserManager().GetUserById(personaId);
		if (user) {
			user->set_game(nullptr);
		}

		//
		request.reply();

		// Notifications
		NotifyPlayerRemoved(request, gameId, personaId, reason);
	}

	void GameManagerComponent::StartMatchmaking(Request& request) {
		// TODO: read game data etc when I bother adding multiplayer

		TDF::Packet packet;
		WriteStartMatchmaking(packet, 1);

		request.reply(packet);
	}

	void GameManagerComponent::CancelMatchmaking(Request& request) {
		auto matchmakingSessionId = request["MSID"].GetUint();

		TDF::Packet packet;
		WriteCancelMatchmaking(packet, matchmakingSessionId);

		request.reply(packet);

		// Notifications
		NotifyMatchmakingFailed(request, matchmakingSessionId, MatchmakingResult::Cancelled);
	}

	void GameManagerComponent::FinalizeGameCreation(Request& request) {
		// Game ID = request["GID"].GetUint();
		const auto& user = request.get_user();
		if (!user) {
			return;
		}

		const auto& game = user->get_game();
		if (!game) {
			// Send an error after I bother adding error types
			request.reply();
			return;
		}

		uint32_t gameId = game->GetId();
		Game::GameManager::StartGame(gameId);

		TDF::Packet packet;
		WriteJoinGame(packet, gameId);

		request.reply(packet);

		// Notifications
		NotifyGameStateChange(request, gameId, GameState::InGame);
		NotifyGamePlayerStateChange(request, gameId, user->get_id(), PlayerState::Connected);
		NotifyPlayerJoinCompleted(request, gameId, user->get_id());
	}

	void GameManagerComponent::ResetDedicatedServer(Request& request) {
		/*
			GSET flags
				1024 = pvp
				256 = unknown (seemingly always used)
				4 = unknown (seemingly always used)
		*/

		/*
# failed to start a level (may be used in other cases) - GMS
0x1e5bc0a4 Unable to start planet. Returning to ship. (THIS IS THE CURRENT PROBLEM)

# Dynamic Ded Serv capcity
#seen when the GMS's are offline or at capacity
0x01320004 Unable to start planet. Returning to ship.

#GAMEMANAGER_ERR_INVALID_GAME_ID
0x00020004 Unable to start planet. Returning to ship.

#GAMEMANAGER_ERR_GAME_FULL
0x00040004 Unable to start planet. Returning to ship.
		*/

		// sub_C2EA10

		const auto& user = request.get_user();
		if (!user) {
			return;
		}

		const auto& game = Game::GameManager::CreateGame();
		if (!game) {
			// Should never happen?
			return;
		}

		user->set_game(game);

		int64_t userId = user->get_id();
		uint8_t userSlot = 0;

		GameManager::CreateGameRequest gameData;
		gameData.Read(request.get_request());

		// Game data
		auto& gameInfo = game->GetInfo();
		gameInfo.attributes = gameData.attributes;
		gameInfo.capacity = gameData.capacity;
		gameInfo.hostNetwork = gameData.hostNetwork;
		gameInfo.name = gameData.name;
		gameInfo.settings = gameData.settings;
		gameInfo.type = gameData.type;
		gameInfo.ignore = gameData.ignore;
		gameInfo.playgroupId = gameData.playgroupId;
		gameInfo.tcap = gameData.tcap;
		gameInfo.version = gameData.version;
		gameInfo.presence = gameData.presence;
		gameInfo.networkTopology = gameData.networkTopology;
		gameInfo.maxPlayers = gameData.maxPlayers;
		gameInfo.queueCapacity = gameData.queueCapacity;
		gameInfo.resetable = gameData.resetable;

		gameInfo.state = GameState::Initializing;
		gameInfo.gpvh = 0xABABABAB;
		gameInfo.gsid = 0xCDCDCDCD;
		gameInfo.hses = 13666;
		gameInfo.psas = "ams";
		gameInfo.seed = 0xFAFAFAFA;
		gameInfo.uuid = "71bc4bdb-82ec-494d-8d75-ca5123b827ac";
		gameInfo.tids.push_back(userSlot);

		NetworkQosData& networkQos = gameInfo.networkQos;
		networkQos.dbps = 128000;
		networkQos.type = NatType::Open;
		networkQos.ubps = 2;

		HostInfo& pHost = gameInfo.pHost; // Party host? no fucking idea about these
		pHost.id = userId;
		pHost.slot = userSlot;

		HostInfo& tHost = gameInfo.tHost; // Team host?
		tHost.id = userId;
		tHost.slot = userSlot;

		// Replace this with party data when that is made
		// Player data
		std::vector<ReplicatedGamePlayer> gamePlayers;
		{
			decltype(auto) player = gamePlayers.emplace_back();
			player.gameId = gameInfo.id;
			player.localization = request.get_client().data().lang;
			player.name = user->get_name();
			player.id = userId;
			player.hostNetwork = gameInfo.hostNetwork;
			player.slot = userSlot;
			player.slotType = Slot::Public;
			player.state = PlayerState::Connecting;
			player.tIndex = gameData.tIndex;
			player.time = utils::get_unix_time();
			player.uid = userId;
		}

		// Game settings etc
		auto levelId = utils::to_number<uint32_t>(gameInfo.attributes["SelectedDifficulty"]);

		auto& chainData = game->GetChainData();
		chainData.SetLevelByIndex(levelId);
		chainData.SetStarLevel(0);
		chainData.SetCompleted(false);

		if (!game->LoadLevel()) {
			// some error, could not load level.
		}

		// Packet
		TDF::Packet packet;
		WriteJoinGame(packet, gameInfo.id);

		request.reply(packet);

		// Notifications
		NotifyGameCreated(request, gameInfo.id);
		// NotifyGameStateChange(request, gameInfo.id, gameInfo.state);
		// NotifyGameReset(request, gameInfo);
		NotifyGameSetup(request, gameInfo, gamePlayers);
		for (const auto& player : gamePlayers) {
			NotifyPlayerJoining(request, player);
		}
		// NotifyPlayerJoinCompleted(request, gameInfo.id, userId);
	}

	void GameManagerComponent::UpdateMeshConnection(Request& request) {
		const auto& targetList = request["TARG"]["_Content"];

		uint32_t gameId = request["GID"].GetUint();
		for (const auto& target : targetList.GetArray()) {
			PlayerConnectionStatus connectionStatus;
			connectionStatus.Read(target);

			std::cout << "ConnectionStatus: " << connectionStatus.flags << ", " << connectionStatus.id << ", " << (int)connectionStatus.status << std::endl;
		}

		uint32_t personaId = targetList[0]["PID"].GetUint();

		PlayerState playerState = static_cast<PlayerState>(targetList[0]["STAT"].GetUint());
		ClientType type = request.get_client().data().type;

		request.reply();

		// Notifications
		if (playerState == PlayerState::Connecting) {
			if (type == ClientType::GameplayUser) {
				const auto& user = request.get_user();
				if (user) {
					NotifyGamePlayerStateChange(request, gameId, user->get_id(), PlayerState::Connected);
					NotifyPlayerJoinCompleted(request, gameId, user->get_id());
				}
			} else if (type == ClientType::DedicatedServer) {
				NotifyGamePlayerStateChange(request, gameId, personaId, PlayerState::Connected);
				NotifyPlayerJoinCompleted(request, gameId, personaId);
			}
		} else if (playerState == PlayerState::Reserved) {
			if (type == ClientType::GameplayUser) {
				// var game = GameManager.Games[gameID.Value];
				// game.Slots.Remove(playerID.Value);

				NotifyPlayerRemoved(request, gameId, personaId, PlayerRemovedReason::PlayerConnLost);
			} else if (type == ClientType::DedicatedServer) {
				// var game = GameManager.Games[gameID.Value];
				// game.Slots.Remove(playerID.Value);

				NotifyPlayerRemoved(request, gameId, personaId, PlayerRemovedReason::PlayerConnLost);
			}
		}
	}
}
