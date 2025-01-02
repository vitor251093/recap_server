
// Include
#include "component.h"

#include "component/associationcomponent.h"
#include "component/authcomponent.h"
#include "component/gamemanagercomponent.h"
#include "component/messagingcomponent.h"
#include "component/playgroupscomponent.h"
#include "component/redirectorcomponent.h"
#include "component/roomscomponent.h"
#include "component/usersessioncomponent.h"
#include "component/utilcomponent.h"

// unused components
enum ComponentType : uint16_t {
	Stats = 0x07,
	CensusData = 0x0A,
	Clubs = 0x0B,
	GameReporting = 0x1C,
	RSP = 0x801,
	Teams = 0x816,
};

// Blaze
namespace Blaze {
	// Component
	uint16_t Component::GetId() const {
		return 0;
	}

	std::string_view Component::GetName() const {
		return "UnknownComponent";
	}

	std::string_view Component::GetReplyPacketName(uint16_t command) const {
		return "";
	}

	std::string_view Component::GetNotificationPacketName(uint16_t command) const {
		return "";
	}

	// ComponentManager
	Component* ComponentManager::Get(uint16_t id) {
		switch (id) {
			case AuthComponent::Id: {
				static AuthComponent component;
				return &component;
			}

			case GameManagerComponent::Id: {
				static GameManagerComponent component;
				return &component;
			}

			case RedirectorComponent::Id: {
				static RedirectorComponent component;
				return &component;
			}

			case PlaygroupsComponent::Id: {
				static PlaygroupsComponent component;
				return &component;
			}

			case UtilComponent::Id: {
				static UtilComponent component;
				return &component;
			}

			case MessagingComponent::Id: {
				static MessagingComponent component;
				return &component;
			}

			case RoomsComponent::Id: {
				static RoomsComponent component;
				return &component;
			}

			case AssociationComponent::Id: {
				static AssociationComponent component;
				return &component;
			}

			case UserSessionComponent::Id: {
				static UserSessionComponent component;
				return &component;
			}
		}

		return nullptr;
	}
}
