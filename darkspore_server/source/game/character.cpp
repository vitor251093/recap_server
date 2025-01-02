
// Include
#include "character.h"

#include "raknet/types.h"

// Game
namespace Game {
	// Character
	Character::Character() {
		mDataBits.set(); // set all the first time
	}

	Character::~Character() {
		// Empty
	}

	uint32_t Character::GetNoun() const {
		return mNounId;
	}

	void Character::SetNoun(uint32_t id) {
		mNounId = id;
		mDataBits.set(CharacterDataBits::NounId);
	}

	uint32_t Character::GetCreatureType() const {
		return mCreatureType;
	}

	void Character::SetCreatureType(uint32_t newCreatureType) {
		mCreatureType = newCreatureType;
		mDataBits.set(CharacterDataBits::CreatureType);
	}

	int32_t Character::GetVersion() const {
		return mVersion;
	}

	void Character::SetVersion(int32_t newVersion) {
		mVersion = newVersion;
		mDataBits.set(CharacterDataBits::Version);
	}

	float Character::GetHealth() const {
		return mHealthPoints;
	}

	void Character::SetHealth(float newHealth) {
		mHealthPoints = newHealth;
		mDataBits.set(CharacterDataBits::Health);
	}

	float Character::GetMaxHealth() const {
		return mMaxHealthPoints;
	}

	void Character::SetMaxHealth(float newMaxHealth) {
		mMaxHealthPoints = newMaxHealth;
		mDataBits.set(CharacterDataBits::MaxHealth);
	}

	float Character::GetMana() const {
		return mManaPoints;
	}

	void Character::SetMana(float newMana) {
		mManaPoints = newMana;
		mDataBits.set(CharacterDataBits::Mana);
	}

	float Character::GetMaxMana() const {
		return mMaxManaPoints;
	}

	void Character::SetMaxMana(float newMaxMana) {
		mMaxManaPoints = newMaxMana;
		mDataBits.set(CharacterDataBits::MaxMana);
	}

	float Character::GetGearScore() const {
		return mGearScore;
	}

	void Character::SetGearScore(float newGearScore) {
		mGearScore = newGearScore;
		mDataBits.set(CharacterDataBits::GearScore);
	}

	float Character::GetGearScoreFlattened() const {
		return mGearScoreFlattened;
	}

	void Character::SetGearScoreFlattened(float newGearScoreFlattened) {
		mGearScoreFlattened = newGearScoreFlattened;
		mDataBits.set(CharacterDataBits::GearScoreFlattened);
	}

	void Character::WriteTo(RakNet::BitStream& stream) const {
		using RakNet::bytes_to_bits;
		using RakNet::ReallocateStream;
		
		constexpr auto size = bytes_to_bits(0x620);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x008));
		Write<uint64_t>(stream, mAssetId);
		Write<int32_t>(stream, mVersion);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x0B4));
		Write<uint32_t>(stream, mNounId);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x0B8));
		for (uint8_t i = 0; i <= 0x49; ++i) {
			Write<float>(stream, mPartAttributes.GetValue(i));
		}

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1E4));
		Write<float>(stream, mPartAttributes.GetValue(AttributeType::ImmuneToSleep));

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1EC));
		for (uint8_t i = 0x4B; i <= 0x61; ++i) {
			Write<float>(stream, mPartAttributes.GetValue(i));
		}

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x24C));
		for (uint8_t i = 0x62; i <= 0x6E; ++i) {
			Write<float>(stream, mPartAttributes.GetValue(i));
		}

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x3B8));
		Write<uint32_t>(stream, mCreatureType);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x3C0));
		Write<uint64_t>(stream, mDeployCooldown);
		Write<uint32_t>(stream, mAbilityPoints);
		for (auto value : mAbilityRanks) {
			Write<uint32_t>(stream, value);
		}

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x3F0));
		Write<float>(stream, mHealthPoints);
		Write<float>(stream, mMaxHealthPoints);
		Write<float>(stream, mManaPoints);
		Write<float>(stream, mMaxManaPoints);
		Write<float>(stream, mGearScore);
		Write<float>(stream, mGearScoreFlattened);

		stream.SetWriteOffset(writeOffset + size);
	}

	void Character::WriteReflection(RakNet::BitStream& stream) const {
		RakNet::reflection_serializer<124> reflector(stream);
		reflector.begin();

		if (mDataBits.any()) {
			if (mDataBits.test(0)) { reflector.write<0>(mVersion); }
			if (mDataBits.test(1)) { reflector.write<1>(mNounId); }
			if (mDataBits.test(2)) { reflector.write<2>(mAssetId); }
			if (mDataBits.test(3)) { reflector.write<3>(mCreatureType); }
			if (mDataBits.test(4)) { reflector.write<4>(mDeployCooldown); }
			if (mDataBits.test(5)) { reflector.write<5>(mAbilityPoints); }
			if (mDataBits.test(6)) { reflector.write<6>(mAbilityRanks); }
			if (mDataBits.test(7)) { reflector.write<7>(mHealthPoints); }
			if (mDataBits.test(8)) { reflector.write<8>(mMaxHealthPoints); }
			if (mDataBits.test(9)) { reflector.write<9>(mManaPoints); }
			if (mDataBits.test(10)) { reflector.write<10>(mMaxManaPoints); }
			if (mDataBits.test(11)) { reflector.write<11>(mGearScore); }
			if (mDataBits.test(12)) { reflector.write<12>(mGearScoreFlattened); }
		}

		constexpr uint8_t attributeFieldOffset = 13;
		const auto& attrData = mPartAttributes.GetData();
		if (!attrData.empty()) {
			const auto& attrDataBits = mPartAttributes.GetDataBits();
			for (const auto& [idx, value] : attrData) {
				if (attrDataBits.test(idx)) {
					reflector.write(attributeFieldOffset + idx, value);
				}
			}
		}

		for (const auto& idx : mPartAttributes.GetErasedData()) {
			reflector.write(attributeFieldOffset + idx, 0.f);
		}

		reflector.end();
	}

	void Character::ResetUpdateBits() {
		mDataBits.reset();
	}
}
