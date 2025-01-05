
#ifndef _SPORENET_SQUAD_HEADER
#define _SPORENET_SQUAD_HEADER

// Include
#include "creature.h"

// SporeNet
namespace SporeNet {
	// Squad
	class Squad {
		public:
			Squad() = default;
			Squad(uint32_t id, uint32_t slot);
			Squad(uint32_t id, uint32_t slot, std::string name, bool locked);

			bool Read(const pugi::xml_node& node);
			void Write(pugi::xml_node& node) const;

			const std::array<uint32_t, 3>& GetCreatureIds() const;
			void SetCreatureId(uint8_t index, uint32_t id);

			const std::string GetName() const;
			const std::string GetCategory() const;

			uint32_t GetId() const;
			uint32_t GetSlot() const;

			bool IsLocked() const;

			void Update(const std::string& creatureStringList, bool pvp);

		private:
			std::array<uint32_t, 3> mCreatureIds;

			std::string mName;
			std::string mCategory;

			uint32_t mId = 0;
			uint32_t mSlot = 0;

			bool mLocked = true;
	};

	// Squads
	class Squads {
		public:
			decltype(auto) begin() { return mSquads.begin(); }
			decltype(auto) begin() const { return mSquads.begin(); }
			decltype(auto) end() { return mSquads.end(); }
			decltype(auto) end() const { return mSquads.end(); }

			auto& data() { return mSquads; }
			const auto& data() const { return mSquads; }

			void Read(const pugi::xml_node& node);
			void Write(pugi::xml_node& node) const;

			Squad* Create();
			void Remove(size_t index);

			Squad* Get(size_t index);
			uint32_t Size() const { return static_cast<uint32_t>(mSquads.size()); }

		private:
			std::vector<Squad> mSquads;
	};

	using SquadPtr = std::shared_ptr<Squad>;
}

#endif
