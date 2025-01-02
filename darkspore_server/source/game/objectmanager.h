
#ifndef _GAME_OBJECT_MANAGER_HEADER
#define _GAME_OBJECT_MANAGER_HEADER

// Include
#include "object.h"
#include "octree.h"
#include "lua.h"
#include "level.h"

#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>

// Game
namespace Game {
	// TriggerVolume
	class TriggerVolume : public Object {
		public:
			TriggerVolume(ObjectManager& manager, uint32_t id, const glm::vec3& position, float radius);

			bool IsTrigger() const override { return true; }

			void OnActivate() override;
			void OnDeactivate() override;
			void OnTick(float deltaTime) override;

			const ObjectPtr& GetOwnerObject() const;

			void Attach(const ObjectPtr& object);
			void Detach(const ObjectPtr& object);

			void AddObject(const ObjectPtr& object);

			void SetOnEnterCallback(sol::protected_function callback);
			void SetOnExitCallback(sol::protected_function callback);
			void SetOnStayCallback(sol::protected_function callback);

		private:
			void OnEnter(ObjectPtr object) const;
			void OnExit(ObjectPtr object) const;
			void OnStay(ObjectPtr object) const;

		private:
			std::map<ObjectPtr, uint8_t> mObjectStates;

			ObjectPtr mOwnerObject = nullptr;

			sol::environment mEnvironment;
			sol::protected_function mOnEnter;
			sol::protected_function mOnExit;
			sol::protected_function mOnStay;
	};

	using TriggerVolumePtr = std::shared_ptr<TriggerVolume>;

	// ObjectManager
	class ObjectManager {
		public:
			ObjectManager(Instance& game);

			Instance& GetGame();
			const Instance& GetGame() const;

			const std::unordered_set<ObjectPtr>& GetActiveObjects() const;

			ObjectPtr Get(uint32_t id) const;
			ObjectPtr Create(uint32_t noun);
			ObjectPtr Create(const MarkerPtr& marker);

			TriggerVolumePtr GetTrigger(uint32_t id) const;
			TriggerVolumePtr CreateTrigger(const glm::vec3& position, float radius);

			std::vector<ObjectPtr> GetObjectsInRegion(const BoundingBox& region, const std::vector<NounType>& types) const;
			std::vector<ObjectPtr> GetObjectsInRadius(const BoundingSphere& region, const std::vector<NounType>& types) const;

			bool IsInLineOfSight(const ObjectPtr& object, const ObjectPtr& target, const glm::vec3& targetPosition) const;

			void Update(float deltaTime);

		private:
			void MarkForDeletion(const ObjectPtr& object);
			uint32_t GetNextObjectId();

		private:
			Instance& mGame;

			std::unique_ptr<OctTree> mOctTree;

			std::unordered_map<uint32_t, ObjectPtr> mObjects;
			std::unordered_set<ObjectPtr> mActiveObjects;

			std::vector<ObjectPtr> mMarkedObjects;
			std::vector<uint32_t> mOpenObjectIds;

			friend class Object;
	};
}

#endif
