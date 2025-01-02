
#ifndef _GAME_CREATURE_HEADER
#define _GAME_CREATURE_HEADER

// Include
#include "object.h"

// Game
namespace Game {
	// Creature
	class Creature {
		public:
			Creature();
			~Creature();

			void OnChangeHealth(int32_t healthChange);
			void OnChangeMana(int32_t manaChange);

		protected:
			ObjectPtr mObject;
	};

	using CreaturePtr = std::shared_ptr<Creature>;
}

#endif
