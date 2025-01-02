
#ifndef _SPORENET_VENDOR_HEADER
#define _SPORENET_VENDOR_HEADER

// Include
#include "predefined.h"
#include "part.h"

#include <map>
#include <unordered_map>

// SporeNet
namespace SporeNet {
	// Vendor
	class Vendor {
		public:
			Vendor();
			~Vendor();

			const Parts& GetPartOfferList() const;

			void OnBuy(const UserPtr& user, size_t partIndex);
			void OnSell(const UserPtr& user, size_t partIndex);

			void RefreshPartOfferList();

		private:
			void OnBuyWeapon();
			void OnBuyPart();

		private:
			std::unordered_map<UserPtr, Parts> mBuybackMap;

			Parts mPartOfferList;
	};
}

#endif
