
#ifndef _SPORENET_USER_HEADER
#define _SPORENET_USER_HEADER

// Include
#include "predefined.h"

#include "part.h"
#include "squad.h"
#include "room.h"

#include "game/instance.h"

#include "blaze/functions.h"

#include <cstdint>
#include <string>
#include <map>
#include <pugixml.hpp>

// SporeNet
namespace SporeNet {
	// FeedMessageType
	enum class FeedMessageType : uint32_t {
		Friend = 1,
		Creature = 2,
		Upgrade = 3
	};

	// Account
	struct Account {
		bool tutorialCompleted = false;
		bool grantAllAccess = false;
		bool grantOnlineAccess = false;

		int64_t id = 1;

		uint32_t chainProgression = 0;
		uint32_t creatureRewards = 0;

		uint32_t currentGameId = 1;
		uint32_t currentPlaygroupId = 1;

		uint32_t defaultDeckPveId = 1;
		uint32_t defaultDeckPvpId = 1;

		uint32_t level = 1;
		uint32_t xp = 0;
		uint32_t dna = 0;
		uint32_t avatarId = 0;

		uint32_t newPlayerInventory = 0;
		uint32_t newPlayerProgress = 0;

		uint32_t cashoutBonusTime = 0;
		uint32_t starLevel = 0;

		uint32_t unlockCatalysts = 0;
		uint32_t unlockDiagonalCatalysts = 0;
		uint32_t unlockInventory = 0;
		uint32_t unlockFuelTanks = 0;
		uint32_t unlockPveDecks = 0;
		uint32_t unlockPvpDecks = 0;
		uint32_t unlockStats = 0;
		uint32_t unlockInventoryIdentify = 0;
		uint32_t unlockEditorFlairSlots = 0;

		uint32_t upsell = 0;

		uint32_t capLevel = 0;
		uint32_t capProgression = 0;

		void Read(const pugi::xml_node& node);
		void Write(pugi::xml_node& node) const;
	};

	// FeedItem
	struct FeedItem {
		std::string metadata;
		std::string name;

		uint64_t timestamp; // time in seconds?

		uint32_t accountId;
		uint32_t id;

		FeedMessageType messageId;
	};

	// Feed
	class Feed {
		public:
			decltype(auto) begin() { return mItems.begin(); }
			decltype(auto) begin() const { return mItems.begin(); }
			decltype(auto) end() { return mItems.end(); }
			decltype(auto) end() const { return mItems.end(); }

			auto& data() { return mItems; }
			const auto& data() const { return mItems; }

			void Read(const pugi::xml_node& node);
			void Write(pugi::xml_node& node) const;

			void Add(FeedItem&& item);

		private:
			std::vector<FeedItem> mItems;
	};

	// User
	class User {
		public:
			User(const std::string& username);
			~User();

			//
			auto& get_account() { return mAccount; }
			const auto& get_account() const { return mAccount; }

			auto& get_creatures() { return mCreatures; }
			const auto& get_creatures() const { return mCreatures; }

			auto& get_squads() { return mSquads; }
			const auto& get_squads() const { return mSquads; }

			auto& get_feed() { return mFeed; }
			const auto& get_feed() const { return mFeed; }

			auto& get_parts() { return mParts; }
			const auto& get_parts() const { return mParts; }

			const std::string& get_auth_token() const { return mAuthToken; }
			void set_auth_token(const std::string& authToken) { mAuthToken = authToken; }

			const Game::InstancePtr& get_game() const { return mGame; }
			void set_game(const Game::InstancePtr& game) { mGame = game; }

			auto get_id() const { return mAccount.id; }

			const auto& get_username() const { return mUsername; }
			const auto& get_password() const { return mPassword; }
			const auto& get_name() const { return mName; }

			bool UpdateState(uint32_t newState);

			// Blaze
			auto& get_extended_data() { return mExtendedData; }
			const auto& get_extended_data() const { return mExtendedData; }

			// Creature
			CreaturePtr GetCreatureById(uint32_t id) const;

			uint32_t UnlockCreature(uint32_t templateId);

			// Squads
			const std::vector<SquadPtr>& GetSquads() const;

			SquadPtr GetSquadById(uint32_t id) const;

			void UpdateSquad(uint32_t slot, const std::string& creatureStringList, bool pvp);

			// Upgrades
			bool UnlockUpgrade(uint32_t unlockId);

			// Auth
			void Logout();

			// Rooms
			const RoomPtr& GetRoom() const;
			void SetRoom(const RoomPtr& room);

			// Storage
			bool Load();
			bool Save();

			// AssociationLists
			bool IsFriend(const User& user) const;
			void AddFriendUser(const User& user);
			void RemoveFriendUser(const User& user);

			bool IsIgnored(const User& user) const;
			void AddIgnoredUser(const User& user);
			void RemoveIgnoredUser(const User& user);

			// WebAPI
			void WriteAccountAPI(pugi::xml_node& node) const;
			void WriteCreaturesAPI(pugi::xml_node& node) const;
			void WriteSquadsAPI(pugi::xml_node& node) const;

		private:
			Account mAccount;

			std::map<uint32_t, Blaze::ListMembers> mAssociationLists;
			std::vector<SquadPtr> mSquads;

			Creatures mCreatures;
			Feed mFeed;
			Parts mParts;

			std::string mUsername;
			std::string mPassword;
			std::string mName;
			std::string mAuthToken;

			Game::InstancePtr mGame;

			RoomPtr mRoom;

			uint32_t mId = 0;
			uint32_t mState = 0;

			// Blaze server data
			Blaze::UserSessionExtendedData mExtendedData;
	};

	// UserManager
	class UserManager {
		public:
			std::tuple<UserPtr, bool, bool> Login(const std::string& username, const std::string& password);

			std::vector<UserPtr> GetUsers() const;

			UserPtr GetUserById(int64_t id) const;
			UserPtr GetUserByEmail(const std::string& username) const;
			UserPtr GetUserByAuthToken(const std::string& authToken) const;

		private:
			void RemoveUser(const std::string& username);

		private:
			std::map<std::string, UserPtr> sUsersByEmail;

			friend class User;
	};
}

#endif
