
// Include
#include "serverevent.h"
#include "object.h"

#include "sporenet/part.h"

#include "raknet/types.h"

#include "utils/functions.h"

// Game
namespace Game {
	// ServerEvent & others
	/*
	void ServerEvent::WriteTo(BitStream& stream) const {
		constexpr auto size = bytes_to_bits(0x98);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x04));
		Write(stream, simpleSwarmEffectID);
		Write(stream, objectFxIndex);
		Write(stream, bRemove);
		Write(stream, bHardStop);
		Write(stream, bForceAttach);
		Write(stream, bCritical);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x10));
		Write(stream, ServerEventDef);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x18));
		Write(stream, objectId);
		Write(stream, secondaryObjectId);
		Write(stream, attackerId);
		Write(stream, position);
		Write(stream, facing);
		Write(stream, orientation);
		Write(stream, targetPoint);
		Write(stream, textValue);
		Write(stream, clientEventID);
		Write(stream, clientIgnoreFlags);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x68));
		Write(stream, lootReferenceId);
		Write(stream, lootInstanceId);
		Write(stream, lootRigblockId);
		Write(stream, lootSuffixAssetId);
		Write(stream, lootPrefixAssetId1);
		Write(stream, lootPrefixAssetId2);
		Write(stream, lootItemLevel);
		Write(stream, lootRarity);
		Write(stream, lootCreationTime);

		stream.SetWriteOffset(writeOffset + size);
	}
	*/

	// ServerEventBase
	void ServerEventBase::SetIgnoredPlayerBits(uint8_t bits) {
		mIgnoreFlags = 0;
	}

	// ServerEvent
	ServerEvent::operator bool() const {
		return mServerEventDef != 0 || mSimpleSwarmEffectId != 0 || (mRemove != false && mEffectIndex != 0);
	}

	void ServerEvent::WriteReflection(RakNet::BitStream& stream) const {
		RakNet::reflection_serializer<ReflectionLength> reflector(stream);
		reflector.begin();
		reflector.write<0>(mSimpleSwarmEffectId);
		reflector.write<1>(mEffectIndex);
		reflector.write<2>(mRemove);
		reflector.write<3>(mHardStop);
		reflector.write<4>(mForceAttach);
		reflector.write<5>(mCritical);
		reflector.write<6>(mServerEventDef);
		reflector.write<7>(mObjectId);
		reflector.write<8>(mSecondaryObjectId);
		reflector.write<9>(mAttackerId);
		reflector.write<10>(mPosition);
		reflector.write<11>(mFacing);
		reflector.write<12>(mOrientation);
		reflector.write<13>(mTargetPoint);
		// 14-15 (unused)
		reflector.write<16>(mIgnoreFlags);
		// 17-25 (unused)
		reflector.end();
	}

	// ClientEvent
	ClientEvent::operator bool() const {
		return mEventId != ClientEventID::None;
	}

	void ClientEvent::SetEventId(ClientEventID eventId) {
		mEventId = eventId;
	}

	void ClientEvent::SetLootPickup(uint8_t playerId, const SporeNet::Part& part) {
		SetEventId(ClientEventID::LootPickup);
		mTextValue = playerId;
		mLootReferenceId = 0;
		mLootRigblockId = part.GetRigblockAssetHash();
		mLootSuffixAssetId = part.GetSuffixAssetHash();
		mLootPrefixAssetId1 = part.GetPrefixAssetHash();
		mLootPrefixAssetId2 = part.GetPrefixSecondaryAssetHash();
		mLootItemLevel = part.GetLevel();
		mLootRarity = static_cast<int32_t>(part.GetRarity());
		mLootCreationTime = part.GetTimestamp();
	}

	void ClientEvent::SetLootPickup(uint8_t playerId, const LootData& lootData) {
		SetEventId(ClientEventID::LootPickup);
		mTextValue = playerId;
		mLootReferenceId = 0;
		mLootRigblockId = lootData.GetRigblockAsset();
		mLootSuffixAssetId = lootData.GetSuffixAsset();
		mLootPrefixAssetId1 = lootData.GetPrefixAsset();
		mLootPrefixAssetId2 = lootData.GetPrefixSecondaryAsset();
		mLootItemLevel = lootData.GetLevel();
		mLootRarity = lootData.GetRarity();
		mLootCreationTime = utils::get_milliseconds();
	}

	void ClientEvent::SetCatalystPickup(uint8_t playerId) {
		SetEventId(ClientEventID::CatalystPickup);
		mTextValue = playerId;
	}

	void ClientEvent::SetPlayerDropLoot(uint8_t playerId, uint64_t lootInstanceId) {
		SetEventId(ClientEventID::LootPlayerDrop);
		mTextValue = playerId;
		mLootInstanceId = lootInstanceId;
	}

	void ClientEvent::WriteReflection(RakNet::BitStream& stream) const {
		RakNet::reflection_serializer<ReflectionLength> reflector(stream);
		reflector.begin();
		// 0-6 (unused)
		reflector.write<7>(mObjectId);
		// 8-13 (unused)
		reflector.write<14>(mTextValue);
		reflector.write<15>(mEventId);
		reflector.write<16>(mIgnoreFlags);
		reflector.write<17>(mLootReferenceId);
		reflector.write<18>(mLootInstanceId);
		reflector.write<19>(mLootRigblockId);
		reflector.write<20>(mLootSuffixAssetId);
		reflector.write<21>(mLootPrefixAssetId1);
		reflector.write<22>(mLootPrefixAssetId2);
		reflector.write<23>(mLootItemLevel);
		reflector.write<24>(mLootRarity);
		reflector.write<25>(mLootCreationTime);
		reflector.end();
	}

	// CombatEvent
	void CombatEvent::WriteReflection(RakNet::BitStream& stream) const {
		RakNet::reflection_serializer<8> reflector(stream);
		reflector.begin();
		reflector.write<0>(mFlags);
		reflector.write<1>(mDeltaHealth);
		reflector.write<2>(mAbsorbedAmount);
		reflector.write<3>(mTargetId);
		reflector.write<4>(mSourceId);
		reflector.write<5>(mAbilityId);
		reflector.write<6>(mDirection);
		reflector.write<7>(mIntegerHpChange);
		reflector.end();
	}
}
