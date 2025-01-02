
// Include
#include "attributes.h"

#include "raknet/server.h"

#include <algorithm>

// Game
namespace Game {
	// Attributes
	float Attributes::GetValue(uint8_t idx) const {
		// test performance some time
		auto end = mData.end();
		auto it = std::find_if(mData.begin(), end, [idx](const auto& data) { return std::get<0>(data) == idx; });
		if (it != end) {
			return std::get<1>(*it);
		}

		return 0;
	}

	float Attributes::GetValue(AttributeType idx) const {
		return GetValue(static_cast<uint8_t>(idx));
	}

	void Attributes::SetValue(uint8_t idx, float value) {
		auto end = mData.end();
		auto it = std::find_if(mData.begin(), end, [idx](const auto& data) { return std::get<0>(data) == idx; });
		if (idx < static_cast<uint8_t>(AttributeType::ClientCount)) {
			if (it != end) {
				if (value == 0) {
					mData.erase(it);
					mErasedData.push_back(idx);
				} else {
					std::get<1>(*it) = value;
				}
			} else if (value != 0) {
				if (mDataBits.test(idx)) {
					mErasedData.erase(std::find(mErasedData.begin(), mErasedData.end(), idx));
				}

				mData.push_back({ idx, value });
				std::sort(mData.begin(), mData.end(), [](const auto& lhs, const auto& rhs) { return std::get<0>(lhs) < std::get<0>(rhs); });
			}
			mDataBits.set(idx);
		}
		/*
		else if (it != end) {
			if (value == 0) {
				mData.erase(it);
			} else {
				std::get<1>(*it) = value;
			}
		} else if (value != 0) {
			mData.push_back({ idx, value });
			std::sort(mData.begin(), mData.end(), [](const auto& lhs, const auto& rhs) { return std::get<0>(lhs) < std::get<0>(rhs); });
		}
		*/
	}

	void Attributes::SetValue(AttributeType idx, float value) {
		SetValue(static_cast<uint8_t>(idx), value);
	}

	std::tuple<float, float> Attributes::GetWeaponDamage() const {
		return std::make_tuple(mMinWeaponDamage, mMaxWeaponDamage);
	}

	void Attributes::SetWeaponDamage(float minDamage, float maxDamage) {
		mMinWeaponDamage = minDamage;
		mMaxWeaponDamage = maxDamage;
	}

	ObjectPtr Attributes::GetOwnerObject() const {
		return mOwnerObject.lock();
	}

	void Attributes::SetOwnerObject(const ObjectPtr& object) {
		mOwnerObject = object;
	}

	void Attributes::WriteTo(RakNet::BitStream& stream) const {
		using RakNet::bytes_to_bits;
		using RakNet::ReallocateStream;

		constexpr auto size = bytes_to_bits(0x634);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x26C));
		for (uint8_t i = 0; i < 0x63; ++i) {
			Write(stream, GetValue(i));
		}

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x400));
		for (uint8_t i = 0x63; i < mData.size(); ++i) {
			Write(stream, GetValue(i));
		}

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x43C));
		Write(stream, mMinWeaponDamage);
		Write(stream, mMaxWeaponDamage);

		stream.SetWriteOffset(writeOffset + size);
	}

	void Attributes::WriteReflection(RakNet::BitStream& stream) const {
		RakNet::reflection_serializer<sClientVisibleAttributeCount> reflector(stream);
		reflector.begin();
		for (const auto& [idx, value] : mData) {
			if (mDataBits.test(idx)) {
				reflector.write(idx, value);
			}
		}

		for (const auto& idx : mErasedData) {
			reflector.write(idx, 0.f);
		}
		reflector.write<111>(mMinWeaponDamage);
		reflector.write<112>(mMaxWeaponDamage);
		reflector.end();
	}

	void Attributes::ResetReflectionBits() {
		mDataBits.reset();
		mErasedData.clear();
	}
}
