
// Include
#include "player.h"

#include "instance.h"
#include "objectmanager.h"

#include "sporenet/user.h"

#include "utils/functions.h"

#include "raknet/types.h"

// Game
namespace Game {
	// Player
	uint32_t Player::GetXPForLevel(uint32_t level) {
		constexpr std::array<uint32_t, 101> xpTable {
			// 0
			0,

			// 1-20
			100, 200, 3000, 6000, 9000,
			12000, 15000, 18000, 21000, 24500,
			28500, 33000, 38000, 43000, 48000,
			53000, 58000, 63000, 68000, 73000,

			// 21-40
			78000, 83000, 88000, 93500, 99500,
			106000, 113000, 120500, 128500, 137000,
			146000, 155500, 165500, 176000, 187000,
			198500, 210500, 223000, 236000, 249500,

			// 41-60
			263500, 278000, 293000, 308500, 324500,
			341000, 358000, 375500, 393500, 412000,
			431000, 451000, 471500, 492500, 514000,
			536000, 558500, 581500, 605000, 629000,

			// 61-80
			653500, 678500, 704500, 731500, 759500,
			788500, 818500, 849500, 881500, 914500,
			948500, 983500, 1019500, 1056500, 1094500,
			1133500, 1173500, 1214500, 1256500, 1299500,

			// 81-100
			1343500, 1388500, 1434500, 1481500, 1529500,
			1578500, 1628500, 1679500, 1731500, 1784500,
			1839500, 1896500, 1955500, 2016500, 2080500,
			2149500, 2225500, 2310500, 2410500, 2510500
		};

		return (level < xpTable.size() ? xpTable[level] : 0);
	}

	Player::Player(Instance& instance, const SporeNet::UserPtr& user, uint8_t playerIndex) : mInstance(instance), mUser(user) {
		mPlayerIndex = playerIndex;
		mDataBits.set(PlayerDataBits::PlayerIndex);

		mChainProgression = user->get_account().chainProgression;
		mDataBits.set(PlayerDataBits::ChainProgression);

		// Some data bits to clear out data from previous missions
		mDataBits.set(PlayerDataBits::CharacterData);
		mDataBits.set(PlayerDataBits::CrystalData);
		mDataBits.set(PlayerDataBits::CrystalBonuses);

		//
		Setup();
	}

	const SporeNet::UserPtr& Player::GetUser() const {
		return mUser;
	}

	uint64_t Player::GetOnlineId() const {
		return mPlayerOnlineId;
	}

	uint8_t Player::GetId() const {
		return mPlayerIndex;
	}

	uint32_t Player::GetCurrentDeckIndex() const {
		return mCurrentDeckIndex;
	}

	uint32_t Player::GetAbilityId(uint8_t creatureIndex, uint8_t abilityIndex) const {
		// TODO: rewrite creature stuff
		switch (abilityIndex) {
			case 0: case 2: case 3: {
				if (creatureIndex >= 3) {
					creatureIndex = 0;
				}

				const auto& creatureIds = mSquad->GetCreatureIds();
				const auto& creature = mUser->GetCreatureById(creatureIds[creatureIndex]);
				if (!creature) {
					return 0;
				}

				switch (abilityIndex) {
					case 0: return creature->GetAbility(0);
					case 2: return creature->GetAbility(1);
					case 3: return creature->GetAbility(3);
				}

				break;
			}

			case 6: case 7: case 8: {
				const auto& creatureIds = mSquad->GetCreatureIds();
				const auto& creature = mUser->GetCreatureById(creatureIds[abilityIndex - 6]);
				if (creature) {
					return creature->GetAbility(2);
				}
				break;
			}
		}

		return 0;
	}

	uint32_t Player::GetAbilityRank(uint8_t creatureIndex, uint8_t abilityIndex) const {
		if (creatureIndex >= 3) {
			creatureIndex = 0;
		}

		const auto& characterData = mCharacterData[std::clamp<size_t>(creatureIndex, 0, mCharacterData.size() - 1)];
		return characterData.mAbilityRanks[std::clamp<size_t>(abilityIndex, 0, 8)];
	}

	bool Player::IsAbilityLocked(uint8_t abilityIndex) const {
		if (abilityIndex < mLockedAbilityMin) {
			return true;
		} else if (mLockedAbilityMin == 5) {
			return (abilityIndex - 6) == mCurrentDeckIndex;
		}
		return false;
	}

	bool Player::IsOverdriveCharged() const {
		return mbIsCharged;
	}

	void Player::Setup() {
		SetStatus(0, 0.f);

		mbDataSetup = false;
		mTeam = 1;
		mPlayerOnlineId = mUser->get_id();
		mLockCamera = false;
		mLockedAbilityMin = 0xFF; // num abilities shown in hud (including squad abilities)
		mLockedDeckIndexMin = 0xFF; // num creatures shown in squad
		// mbIsCharged = true;

		const auto& accountData = mUser->get_account();
		mAvatarLevel = accountData.level;
		mDNA = accountData.dna;

		auto prevXP = GetXPForLevel(accountData.level);
		auto nextXP = GetXPForLevel(accountData.level + 1);
		mAvatarXP = (accountData.xp - prevXP) / static_cast<float>(std::max<uint32_t>(1, nextXP - prevXP));

		mDataBits.set(PlayerDataBits::DataSetup);
		mDataBits.set(PlayerDataBits::Team);
		mDataBits.set(PlayerDataBits::PlayerOnlineId);
		mDataBits.set(PlayerDataBits::LockCamera);
		mDataBits.set(PlayerDataBits::LockAbilityMin);
		mDataBits.set(PlayerDataBits::LockDeckIndexMin);
		mDataBits.set(PlayerDataBits::Level);
		mDataBits.set(PlayerDataBits::DNA);
		mDataBits.set(PlayerDataBits::Experience);
	}

	void Player::GetStatus(uint32_t& status, float& progress) const {
		status = mStatus;
		progress = mStatusProgress;
	}

	void Player::SetStatus(uint32_t status, float progress) {
		mStatus = status;
		mStatusProgress = progress;

		mDataBits.set(PlayerDataBits::Status);
		mDataBits.set(PlayerDataBits::StatusProgress);

		SetUpdateBits(PlayerUpdateBits::PlayerBits);
	}

	ObjectPtr Player::GetCharacterObject(uint32_t index) const {
		if (index >= mCharacterObjects.size()) {
			return nullptr;
		}
		return mCharacterObjects[index];
	}

	ObjectPtr Player::GetDeployedCharacterObject() const {
		return GetCharacterObject(GetCurrentDeckIndex());
	}

	bool Player::SwapCharacter(uint32_t index) {
		// TODO: cooldown checks, etc etc
		mCurrentDeckIndex = index;
		mDataBits.set(PlayerDataBits::CurrentDeckIndex);

		SetUpdateBits(PlayerUpdateBits::PlayerBits);
		return true;
	}

	bool Player::SyncCharacterData() {
		const auto& characterObject = GetDeployedCharacterObject();
		if (!characterObject) {
			return false;
		}

		auto characterIndex = GetCurrentDeckIndex();
		auto& characterData = mCharacterData[characterIndex];
		characterData.SetHealth(characterObject->GetHealth());
		characterData.SetMaxHealth(characterObject->GetMaxHealth());
		characterData.SetMana(characterObject->GetMana());
		characterData.SetMaxMana(characterObject->GetMaxMana());

		// TODO: update attributes
		// characterData.mPartAttributes

		SetUpdateBits(PlayerUpdateBits::CharacterBits << characterIndex);
		return true;
	}

	SporeNet::SquadPtr Player::GetSquad() const {
		return mSquad;
	}

	void Player::SetSquad(const SporeNet::SquadPtr& squad) {
		mSquad = squad;

		mCurrentDeckIndex = 0;
		mQueuedDeckIndex = 0;

		if (mSquad) {
			// mDeckScore = mSquad->GetScore();

			uint32_t creatureIndex = 0;
			for (uint32_t creatureId : mSquad->GetCreatureIds()) {
				Character character;

				// TODO: save/calculate health and "power"
				character.SetMaxHealth(200.0f);
				character.SetHealth(character.GetMaxHealth());
				character.SetMaxMana(200.0f);
				character.SetMana(character.GetMaxMana());

				const auto& creature = mUser->GetCreatureById(creatureId);
				if (creature) {
					character.SetNoun(creature->GetNoun());
					character.SetVersion(creature->GetVersion());
					character.SetCreatureType(static_cast<uint32_t>(creature->GetType()));
					character.SetGearScore(creature->GetGearScore());
					character.SetGearScoreFlattened(creature->GetGearScoreFlattened());
				} else {
					character.SetNoun(0);
					character.SetVersion(0);
					character.SetCreatureType(static_cast<uint32_t>(SporeNet::CreatureType::Unknown));
					character.SetGearScore(0.f);
					character.SetGearScoreFlattened(0.f);
				}

				SetCharacter(std::move(character), creatureIndex);
				creatureIndex++;
			}
		} else {
			mDeckScore = 0;
		}

		mDataBits.set(PlayerDataBits::CurrentDeckIndex);
		mDataBits.set(PlayerDataBits::QueuedDeckIndex);
		mDataBits.set(PlayerDataBits::DeckScore);

		SetUpdateBits(PlayerUpdateBits::PlayerBits);
	}

	const Character& Player::GetCharacter(uint32_t index) const {
		return mCharacterData[index];
	}

	void Player::SetCharacter(Character&& character, uint32_t index) {
		if (index >= mCharacterData.size()) {
			return;
		}

		auto& characterRef = mCharacterData[index];
		characterRef = std::move(character);

		auto& characterObject = mCharacterObjects[index];
		if (characterRef.mNounId != 0) {
			characterObject = mInstance.GetObjectManager().Create(characterRef.mNounId);
		} else {
			characterObject = nullptr;
		}

		if (characterObject) {
			// characterRef.mAssetId = characterObject->GetId();
			characterRef.mAssetId = characterObject->GetAssetId();
			characterRef.mAbilityPoints = 10;
			characterRef.mAbilityRanks.fill(1);

			characterObject->SetAttributeValue(AttributeType::MaxHealth, characterRef.GetMaxHealth());
			characterObject->SetAttributeValue(AttributeType::MaxMana, characterRef.GetMaxMana());
			characterObject->SetHealth(characterRef.GetHealth());
			characterObject->SetMana(characterRef.GetMana());

			characterObject->SetTeam(mTeam);
			characterObject->SetHasCollision(true);
			characterObject->SetPlayerIndex(mPlayerIndex);
		} else {
			characterRef.mAssetId = 0;
		}

		mDataBits.set(PlayerDataBits::CharacterData);
		SetUpdateBits(PlayerUpdateBits::CharacterBits << index);
	}

	uint32_t Player::GetOpenCatalystSlot() const {
		for (uint32_t i = 0; i < mCatalysts.size(); ++i) {
			if (mCatalysts[i].GetNounId() == 0) {
				return i;
			}
		}
		return 0xFFFFFFFF;
	}

	Catalyst Player::GetCatalyst(uint32_t index) const {
		if (mCatalysts.size() < index) {
			return Catalyst();
		}
		return mCatalysts[index];
	}

	void Player::SetCatalyst(const Catalyst& catalyst, uint32_t index) {
		if (index < mCatalysts.size()) {
			mCatalysts[index] = catalyst;
			SetUpdateBits(PlayerUpdateBits::CrystalBits << index);

			// This crashes the client, probably because it updates raw data and not reflection dataa
			// mDataBits.set(PlayerDataBits::CrystalData);

			UpdateCatalystBonuses();
		}
	}

	uint16_t Player::GetUpdateBits() const {
		return mUpdateBits;
	}

	void Player::SetUpdateBits(uint16_t bits) {
		mUpdateBits |= bits;
	}

	void Player::ResetUpdateBits() {
		mUpdateBits = 0;
		mDataBits.reset();
		for (auto& character : mCharacterData) {
			character.ResetUpdateBits();
		}
	}

	void Player::WriteTo(RakNet::BitStream& stream) const {
		using RakNet::bytes_to_bits;
		using RakNet::ReallocateStream;

		constexpr auto size = bytes_to_bits(0x14B8);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset);
		Write(stream, mbDataSetup);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x0004));
		Write(stream, mStatus);
		Write(stream, mStatusProgress);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x000C));
		Write(stream, mCurrentDeckIndex);
		Write(stream, mQueuedDeckIndex);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x0018));
		for (const auto& character : mCharacterData) {
			character.WriteTo(stream);
		}

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1278));
		Write(stream, mPlayerIndex);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1280));
		Write(stream, mPlayerOnlineId);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x12DC));
		Write(stream, mTeam);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x12E0));
		Write(stream, mCurrentCreatureId);
		Write(stream, mEnergyPoints);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x12EC));
		Write(stream, mbIsCharged);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x12F0));
		Write(stream, mDNA);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x12F8));
		Write(stream, mAvatarXP);
		Write(stream, mAvatarLevel);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1304));
		Write(stream, mChainProgression);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x133C));
		for (const auto& catalyst : mCatalysts) {
			catalyst.WriteTo(stream);
		}

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x13CC));
		for (auto bonus : mCatalystBonuses) {
			Write(stream, bonus);
		}

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1408));
		Write(stream, mLockCamera);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x140C));
		Write(stream, mDeckScore);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1414));
		Write(stream, mbLockedOverdrive);
		Write(stream, mbLockedCrystals);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1418));
		Write(stream, mLockedAbilityMin);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1420));
		Write(stream, mLockedDeckIndexMin);

		stream.SetWriteOffset(writeOffset + size);
	}

	void Player::WriteReflection(RakNet::BitStream& stream) const {
		RakNet::reflection_serializer<24> reflector(stream);
		reflector.begin();
		if (mDataBits.any()) {
			if (mDataBits.test(0)) { reflector.write<0>(mbDataSetup); }
			if (mDataBits.test(1)) { reflector.write<1>(mCurrentDeckIndex); }
			if (mDataBits.test(2)) { reflector.write<2>(mQueuedDeckIndex); }
			if (mDataBits.test(3)) { reflector.write<3>(mCharacterData); }
			if (mDataBits.test(4)) { reflector.write<4>(mPlayerIndex); }
			if (mDataBits.test(5)) { reflector.write<5>(mTeam); }
			if (mDataBits.test(6)) { reflector.write<6>(mPlayerOnlineId); }
			if (mDataBits.test(7)) { reflector.write<7>(mStatus); }
			if (mDataBits.test(8)) { reflector.write<8>(mStatusProgress); }
			if (mDataBits.test(9)) { reflector.write<9>(mCurrentCreatureId); }
			if (mDataBits.test(10)) { reflector.write<10>(mEnergyPoints); }
			if (mDataBits.test(11)) { reflector.write<11>(mbIsCharged); }
			if (mDataBits.test(12)) { reflector.write<12>(mDNA); }
			if (mDataBits.test(13)) { reflector.write<13>(mCatalysts); }
			if (mDataBits.test(14)) { reflector.write<14>(mCatalystBonuses); }
			if (mDataBits.test(15)) { reflector.write<15>(mAvatarLevel); }
			if (mDataBits.test(16)) { reflector.write<16>(mAvatarXP); }
			if (mDataBits.test(17)) { reflector.write<17>(mChainProgression); }
			if (mDataBits.test(18)) { reflector.write<18>(mLockCamera); }
			if (mDataBits.test(19)) { reflector.write<19>(mbLockedOverdrive); }
			if (mDataBits.test(20)) { reflector.write<20>(mbLockedCrystals); }
			if (mDataBits.test(21)) { reflector.write<21>(mLockedAbilityMin); }
			if (mDataBits.test(22)) { reflector.write<22>(mLockedDeckIndexMin); }
			if (mDataBits.test(23)) { reflector.write<23>(mDeckScore); }
		}
		reflector.end();
	}

	bool Player::NeedUpdate() const {
		return (mUpdateBits & PlayerUpdateBits::Mask) || mDataBits.any();
	}

	void Player::UpdateCatalystBonuses() {
		constexpr size_t GRID_SIZE = 3;
		constexpr size_t MIDDLE_SLOT = 4;

		const Catalyst* catalyst;
		for (size_t i = 0; i < GRID_SIZE; ++i) {
			size_t index = i * GRID_SIZE;

			catalyst = &mCatalysts[index];
			mCatalystBonuses[i] = catalyst->MatchingColor(mCatalysts[index + 1]) && catalyst->MatchingColor(mCatalysts[index + 2]);

			catalyst = &mCatalysts[i];
			mCatalystBonuses[i + GRID_SIZE] = catalyst->MatchingColor(mCatalysts[i + (GRID_SIZE * 1)]) && catalyst->MatchingColor(mCatalysts[i + (GRID_SIZE * 2)]);
		}

		// Diagonals
		catalyst = &mCatalysts[MIDDLE_SLOT];
		mCatalystBonuses[6] = catalyst->MatchingColor(mCatalysts[0]) && catalyst->MatchingColor(mCatalysts[8]);
		mCatalystBonuses[7] = catalyst->MatchingColor(mCatalysts[2]) && catalyst->MatchingColor(mCatalysts[6]);

		mDataBits.set(PlayerDataBits::CrystalBonuses);
		SetUpdateBits(PlayerUpdateBits::PlayerBits);
	}
}
