
// Include
#include "vendor.h"

#include "utils/functions.h"

// SporeNet
namespace SporeNet {
	// Vendor
	Vendor::Vendor() {
		RefreshPartOfferList();
	}

	Vendor::~Vendor() {
		//
	}

	const Parts& Vendor::GetPartOfferList() const {
		return mPartOfferList;
	}

	void Vendor::OnBuy(const UserPtr& user, size_t partIndex) {
		//
	}

	void Vendor::OnSell(const UserPtr& user, size_t partIndex) {
		if (!user) {
			return;
		}

		auto it = mBuybackMap.find(user);
		if (it == mBuybackMap.end()) {
			// No cheating please
			return;
		}

		auto& buybackParts = it->second;
		if (buybackParts.empty() || partIndex >= buybackParts.size()) {
			// Ok
			return;
		}

		// auto& part = buybackParts[partIndex];
	}

	void Vendor::RefreshPartOfferList() {
		auto& parts = mPartOfferList.data();
		parts.clear();

		for (uint16_t id = 100; id < 150; ++id) {
			Part part(id);
			part.SetCreationDate(utils::get_unix_time());
			part.SetIsFlair(false);
			part.SetMarketStatus(0xAB);
			part.SetCost(0x1234);
			part.SetLevel(30);
			part.SetRarity(PartRarity::Rare);
			part.SetStatus(0x62);
			part.SetUsage(0x55);

			part.SetPrefix(1, false);
			part.SetPrefix(2, true);
			part.SetSuffix(3);

			parts.push_back(std::move(part));
		}
	}

	void Vendor::OnBuyWeapon() {
		//
	}

	void Vendor::OnBuyPart() {
		//
	}
}
