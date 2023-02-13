
#ifndef _SPORENET_INSTANCE_HEADER
#define _SPORENET_INSTANCE_HEADER

// Include
#include "predefined.h"
#include "main.h"

// SporeNet
namespace SporeNet {
	// Instance
	class Instance {
		public:
			Instance();
			~Instance();

			TemplateDatabase& GetTemplateDatabase() const;
			UserManager& GetUserManager() const;
			RoomManager& GetRoomManager() const;
			Vendor& GetVendor() const;

		private:
			std::unique_ptr<TemplateDatabase> mTemplateDatabase;
			std::unique_ptr<UserManager> mUserManager;
			std::unique_ptr<RoomManager> mRoomManager;
			std::unique_ptr<Vendor> mVendor;
	};

	static Instance& Get() {
		return GetApp().GetSporeNet();
	}
}

#endif
