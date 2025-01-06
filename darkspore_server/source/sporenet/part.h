
#ifndef _SPORENET_PART_HEADER
#define _SPORENET_PART_HEADER

// Include
#include <cstdint>
#include <string_view>
#include <vector>
#include <pugixml.hpp>
#include "utils/json.h"

// SporeNet
namespace SporeNet {
	// PartUsage
	enum class PartUsage : uint8_t {

	};

	// PartRarity
	enum class PartRarity : uint8_t {
		Basic = 0,
		Uncommon,
		Rare,
		Epic,
		Unique,
		RareUnique,
		EpicUnique
	};

	// Part
	class Part {
		public:
			static std::string_view GetName(uint16_t id);

			Part(uint32_t rigblock);
			Part(const pugi::xml_node& node);
			Part(rapidjson::Value& object);

			bool Read(const pugi::xml_node& node);
			void Write(pugi::xml_node& node) const;
			void WriteApi(pugi::xml_node& node, uint32_t index, bool offer) const;

			bool Read(rapidjson::Value& object);
			rapidjson::Value Write(rapidjson::Document::AllocatorType& allocator, uint32_t index, bool api = false) const;

			std::string_view GetName() const;

			uint64_t GetTimestamp() const;

			uint32_t GetRigblockAssetHash() const;
			uint32_t GetPrefixAssetHash() const;
			uint32_t GetPrefixSecondaryAssetHash() const;
			uint32_t GetSuffixAssetHash() const;

			uint16_t GetLevel() const;
			PartRarity GetRarity() const;

			void SetRigblock(uint16_t rigblock);
			void SetPrefix(uint16_t prefix, bool secondary = false);
			void SetSuffix(uint16_t suffix);

			void SetCreationDate(uint64_t timestamp);
			void SetCost(uint32_t cost);
			void SetLevel(uint16_t level);
			void SetRarity(PartRarity rarity);
			void SetMarketStatus(uint8_t marketStatus);
			void SetStatus(uint8_t status);
			void SetUsage(uint8_t usage);
			void SetIsFlair(bool flair);

		private:
			uint64_t mTimestamp = 0;

			uint32_t mRigblockAssetHash = 0;
			uint32_t mPrefixAssetHash = 0;
			uint32_t mPrefixSecondaryAssetHash = 0;
			uint32_t mSuffixAssetHash = 0;
			uint32_t mCost = 0;
			uint32_t mEquippedToCreatureId = 0;

			uint16_t mRigblockAssetId = 0;
			uint16_t mPrefixAssetId = 0;
			uint16_t mPrefixSecondaryAssetId = 0;
			uint16_t mSuffixAssetId = 0;
			uint16_t mLevel = 0;

			PartRarity mRarity = PartRarity::Basic;
			uint8_t mMarketStatus = 0;
			uint8_t mStatus = 0;
			uint8_t mUsage = 0;

			bool mIsFlair = false;

			friend class Parts;
	};

	// Parts
	class Parts {
		public:
			decltype(auto) begin() { return mItems.begin(); }
			decltype(auto) begin() const { return mItems.begin(); }
			decltype(auto) end() { return mItems.end(); }
			decltype(auto) end() const { return mItems.end(); }

			auto& data() { return mItems; }
			const auto& data() const { return mItems; }

			size_t size() const { return mItems.size(); }
			bool empty() const { return mItems.empty(); }

			Part& GetPart(size_t index);
			const Part& GetPart(size_t index) const;

			void AddPart(Part part);

			void Read(const pugi::xml_node& node);
			void Write(pugi::xml_node& node) const;
			void WriteApi(pugi::xml_node& node, bool offer) const;

		private:
			std::vector<Part> mItems;
	};
}

#endif
