
#ifndef _GAME_OCTREE_HEADER
#define _GAME_OCTREE_HEADER

// Include
#include "predefined.h"
#include "noun.h"

// Game
namespace Game {
	// OctTree
	class OctTree {
		static constexpr float sSmallestExtent = 1;

		public:
			OctTree();
			OctTree(const BoundingBox& boundingBox);

			void Update();
			void BuildTree();

			void Enqueue(const ObjectPtr& object);
			bool Insert(const ObjectPtr& object);

			std::vector<ObjectPtr> GetObjectsInRegion(const BoundingBox& region, const std::vector<NounType>& types) const;
			std::vector<ObjectPtr> GetObjectsInRadius(const BoundingSphere& region, const std::vector<NounType>& types) const;

		protected:
			void GetObjectsInRegion(std::vector<ObjectPtr>& objects, const BoundingBox& region, const std::vector<NounType>& types) const;
			void GetObjectsInRadius(std::vector<ObjectPtr>& objects, const BoundingSphere& region, const std::vector<NounType>& types) const;
			void GetTriggerInteractions(std::vector<std::tuple<TriggerVolumePtr, ObjectPtr>>& collisions, std::vector<TriggerVolumePtr> parentTriggers) const;

			OctTree* CreateNode(const BoundingBox& region, const std::vector<ObjectPtr>& objectList);
			OctTree* CreateNode(const BoundingBox& region, const ObjectPtr& object);

		protected:
			BoundingBox mRegion;

			std::vector<ObjectPtr> mObjects;
			std::vector<ObjectPtr> mQueue;

			OctTree* mChildNode[8] { nullptr };
			OctTree* mParentNode = nullptr;

			uint8_t mActiveNodes = 0;

			int8_t mMaxLifespan = 8;
			int8_t mLifespan = -1;

			bool mBuilt = false;
			bool mReady = false;

			friend class GameObject;
	};
}

#endif
