
// Include
#include "octree.h"
#include "objectmanager.h"

#include "utils/log.h"

// TODO: just change this octree to focus on triggers

// Game
namespace Game {
	// OctTree
	OctTree::OctTree() : mRegion(glm::vec3(-2500), glm::vec3(2500)) {}
	OctTree::OctTree(const BoundingBox& boundingBox) : mRegion(boundingBox) {}

	void OctTree::Update() {
		if (!mReady) {
			if (!mBuilt) {
				for (const auto& object : mQueue) {
					mObjects.push_back(object);
				}
				mQueue.clear();

				BuildTree();
				mBuilt = true;
			} else {
				for (const auto& object : mQueue) {
					Insert(object);
				}
				mQueue.clear();
			}
			mReady = true;
		}

		if (mObjects.empty()) {
			if (mActiveNodes == 0) {
				if (mLifespan == -1) {
					mLifespan = mMaxLifespan;
				} else if (mLifespan > 0) {
					mLifespan--;
				}
			}
		} else {
			if (mLifespan != -1) {
				if (mMaxLifespan <= 64) {
					mMaxLifespan *= 2;
				}
				mLifespan = -1;
			}
		}

		// Remove object marked to be deleted
		for (int32_t index = static_cast<int32_t>(mObjects.size()) - 1; index >= 0; --index) {
			const auto& object = mObjects[index];
			if (object->IsMarkedForDeletion()) {
				mObjects.erase(std::next(mObjects.begin(), index));
			}
		}

		// Get objects that have moved
		decltype(mObjects) movedObjects;
		movedObjects.reserve(mObjects.size());

		for (const auto& object : mObjects) {
			if (object->IsDirty()) {
				object->SetDirty(false);
				movedObjects.push_back(object);
			}
		}

		for (uint32_t flags = mActiveNodes, index = 0; flags > 0; flags >>= 1, ++index) {
			auto& childNode = mChildNode[index];
			if ((flags & 1) && childNode->mLifespan == 0) {
				if (childNode->mObjects.empty()) {
					mActiveNodes ^= (1 << index);
					delete childNode;
					childNode = nullptr;
				} else {
					childNode->mLifespan = -1;
				}
			}
		}

		for (uint32_t flags = mActiveNodes, index = 0; flags > 0; flags >>= 1, ++index) {
			if (flags & 1) {
				mChildNode[index]->Update();
			}
		}

		for (const auto& movedObject : movedObjects) {
			auto current = this;

			const auto& bBox = movedObject->GetBoundingBox();
			if (!bBox.IsPoint()) {
				while (!current->mRegion.Contains(bBox)) {
					if (!current->mParentNode) {
						break;
					}
					current = current->mParentNode;
				}
			}
			/*
			const auto& position = movedObject->GetPosition();
			while (!current->mRegion.Contains(position)) {
				if (!current->mParentNode) {
					break;
				}
				current = current->mParentNode;
			}
			*/
			/*
			else {
				const auto& bSphere = movedObject->GetBoundingSphere();
				while (!current->mRegion.Contains(bSphere)) {
					if (!current->mParentNode) {
						break;
					}
					current = current->mParentNode;
				}
			}
			*/

			mObjects.erase(std::find(mObjects.begin(), mObjects.end(), movedObject));
			current->Insert(movedObject);
		}

		if (!mParentNode) {
			std::vector<std::tuple<TriggerVolumePtr, ObjectPtr>> collisions;
			GetTriggerInteractions(collisions, {});

			for (const auto& [trigger, object] : collisions) {
				trigger->AddObject(object);
			}
		}
	}

	void OctTree::BuildTree() {
		if (mObjects.size() <= 1) {
			if (mObjects.size() == 1 && mRegion.Contains(mObjects.front()->GetBoundingBox())) {
				return;
			}
		}

		if (mRegion.IsPoint()) {
			// TODO: get and update extents.
		}

		glm::vec3 extent = mRegion.extent;
		if (extent.x <= sSmallestExtent && extent.y <= sSmallestExtent && extent.z <= sSmallestExtent) {
			return;
		}

		const glm::vec3& rMin = mRegion.GetMin();
		const glm::vec3& rMax = mRegion.GetMax();
		const glm::vec3& rCenter = rMin + extent;

		std::array<BoundingBox, 8> octant {
			BoundingBox(rMin, rCenter),																	// Bottom left (back)
			BoundingBox(glm::vec3(rCenter.x, rMin.y, rMin.z), glm::vec3(rMax.x, rCenter.y, rCenter.z)),	// Bottom right (back)
			BoundingBox(glm::vec3(rCenter.x, rMin.y, rCenter.z), glm::vec3(rMax.x, rCenter.y, rMax.z)),	// Bottom right (front)
			BoundingBox(glm::vec3(rMin.x, rMin.y, rCenter.z), glm::vec3(rCenter.x, rCenter.y, rMax.z)),	// Bottom left (front)
			BoundingBox(glm::vec3(rMin.x, rCenter.y, rMin.z), glm::vec3(rCenter.x, rMax.y, rCenter.z)),	// Top left (back)
			BoundingBox(glm::vec3(rCenter.x, rCenter.y, rMin.z), glm::vec3(rMax.x, rMax.y, rCenter.z)),	// Top right (back)
			BoundingBox(rCenter, rMax),																	// Top right (front)
			BoundingBox(glm::vec3(rMin.x, rCenter.y, rCenter.z), glm::vec3(rCenter.x, rMax.y, rMax.z))	// Top left (front)
		};

		std::array<decltype(mObjects), 8> objectList;
		std::vector<int32_t> objectRemoveList;

		for (int32_t index = 0, size = static_cast<int32_t>(mObjects.size()); index < size; ++index) {
			const auto& object = mObjects[index];
			const BoundingBox& boundingBox = object->GetBoundingBox();
			if (!boundingBox.IsPoint()) {
				for (uint32_t corner = 0; corner < 8; ++corner) {
					if (octant[corner].Contains(boundingBox)) {
						objectList[corner].push_back(object);
						objectRemoveList.push_back(index);
						break;
					}
				}
			}
			/*
			else if (obj.BoundingSphere.Radius != 0) {
				for (int a = 0; a < 8; a++) {
					if (octant[a].Contains(obj.BoundingSphere) == ContainmentType.Contains) {
						octList[a].Add(obj);
						delist.Add(obj);
						break;
					}
				}
			}
			*/
		}

		for (int32_t index = static_cast<int32_t>(objectRemoveList.size()) - 1; index >= 0; --index) {
			mObjects.erase(std::next(mObjects.begin(), objectRemoveList[index]));
		}

		// Create child nodes where there are items contained in the bounding region
		for (uint32_t corner = 0; corner < 8; ++corner) {
			const auto& objects = objectList[corner];
			if (objects.empty()) {
				continue;
			}

			mActiveNodes |= (1 << corner);
			mChildNode[corner] = CreateNode(octant[corner], objects);
			mChildNode[corner]->BuildTree();
		}
	}

	void OctTree::Enqueue(const ObjectPtr& object) {
		mQueue.push_back(object);
		mReady = false;
	}

	bool OctTree::Insert(const ObjectPtr& object) {
		if (mObjects.empty() && mActiveNodes == 0) {
			mObjects.push_back(object);
			return true;
		}

		const glm::vec3& extent = mRegion.extent;
		if (extent.x <= sSmallestExtent && extent.y <= sSmallestExtent && extent.z <= sSmallestExtent) {
			mObjects.push_back(object);
			return true;
		}

		const BoundingBox& boundingBox = object->GetBoundingBox();

		bool isInRegion = mRegion.Contains(boundingBox);
		if (!isInRegion) {
			if (mParentNode) {
				return mParentNode->Insert(object);
			} else {
				std::cout << std::format("Object outside of root region. (x: {}, y: {}, z: {})", mRegion.center.x, mRegion.center.y, mRegion.center.z) << std::endl;
				return false;
			}
		}

		const glm::vec3& rMin = mRegion.GetMin();
		const glm::vec3& rMax = mRegion.GetMax();
		const glm::vec3& rCenter = rMin + extent;

		//Find or create subdivided regions for each octant in the current region
		std::array<BoundingBox, 8> childOctant;
		childOctant[0] = mChildNode[0] ? mChildNode[0]->mRegion : BoundingBox(rMin, rCenter);																	// Bottom left (back)
		childOctant[1] = mChildNode[1] ? mChildNode[1]->mRegion : BoundingBox(glm::vec3(rCenter.x, rMin.y, rMin.z), glm::vec3(rMax.x, rCenter.y, rCenter.z));	// Bottom right (back)
		childOctant[2] = mChildNode[2] ? mChildNode[2]->mRegion : BoundingBox(glm::vec3(rCenter.x, rMin.y, rCenter.z), glm::vec3(rMax.x, rCenter.y, rMax.z));	// Bottom right (front)
		childOctant[3] = mChildNode[3] ? mChildNode[3]->mRegion : BoundingBox(glm::vec3(rMin.x, rMin.y, rCenter.z), glm::vec3(rCenter.x, rCenter.y, rMax.z));	// Bottom left (front)
		childOctant[4] = mChildNode[4] ? mChildNode[4]->mRegion : BoundingBox(glm::vec3(rMin.x, rCenter.y, rMin.z), glm::vec3(rCenter.x, rMax.y, rCenter.z));	// Top left (back)
		childOctant[5] = mChildNode[5] ? mChildNode[5]->mRegion : BoundingBox(glm::vec3(rCenter.x, rCenter.y, rMin.z), glm::vec3(rMax.x, rMax.y, rCenter.z));	// Top right (back)
		childOctant[6] = mChildNode[6] ? mChildNode[6]->mRegion : BoundingBox(rCenter, rMax);																	// Top right (front)
		childOctant[7] = mChildNode[7] ? mChildNode[7]->mRegion : BoundingBox(glm::vec3(rMin.x, rCenter.y, rCenter.z), glm::vec3(rCenter.x, rMax.y, rMax.z));	// Top left (front)

		if (isInRegion) {
			for (uint32_t corner = 0; corner < 8; ++corner) {
				const auto& childRegion = childOctant[corner];
				if (childRegion.Contains(boundingBox)) {
					auto& childNode = mChildNode[corner];
					if (childNode) {
						if (childNode->Insert(object)) {
							return true;
						}
					} else {
						childNode = CreateNode(childRegion, object);
						mActiveNodes |= (1 << corner);
						return true;
					}
				}
			}

			mObjects.push_back(object);
			return true;
		}
		/*
		else if (Item.BoundingSphere.Radius != 0 && m_region.Contains(Item.BoundingSphere) == ContainmentType.Contains) {
			bool found = false;
			//we will try to place the object into a child node. If we can't fit it in a child node, then we insert it into the current node object list.
			for (int a = 0; a < 8; a++) {
				//is the object contained within a child quadrant?
				if (childOctant[a].Contains(Item.BoundingSphere) == ContainmentType.Contains) {
					if (m_childNode[a] != null)
						m_childNode[a].Insert(Item);   //Add the item into that tree and let the child tree figure out what to do with it
					else {
						m_childNode[a] = CreateNode(childOctant[a], Item);   //create a new tree node with the item
						m_activeNodes |= (byte)(1 << a);
					}
					found = true;
				}
			}
			if (!found) m_objects.Add(Item);
		}
		*/
		return false;
	}

	std::vector<ObjectPtr> OctTree::GetObjectsInRegion(const BoundingBox& region, const std::vector<NounType>& types) const {
		std::vector<ObjectPtr> objects;
		GetObjectsInRegion(objects, region, types);
		return objects;
	}

	std::vector<ObjectPtr> OctTree::GetObjectsInRadius(const BoundingSphere& region, const std::vector<NounType>& types) const {
		std::vector<ObjectPtr> objects;
		GetObjectsInRadius(objects, region, types);
		return objects;
	}

	void OctTree::GetObjectsInRegion(std::vector<ObjectPtr>& objects, const BoundingBox& region, const std::vector<NounType>& types) const {
		if (!mBuilt) {
			return;
		}

		for (const auto& object : mObjects) {
			if (types.empty()) {
				if (region.Intersects(object->GetBoundingBox())) {
					objects.push_back(object);
				}
			} else {
				auto type = object->GetType();
				for (auto acceptedType : types) {
					if (type == acceptedType) {
						if (region.Intersects(object->GetBoundingBox())) {
							objects.push_back(object);
						}
						break;
					}
				}
			}
		}

		if (mActiveNodes) {
			for (const auto& childNode : mChildNode) {
				if (childNode && region.Intersects(childNode->mRegion)) {
					childNode->GetObjectsInRegion(objects, region, types);
				}
			}
		}
	}

	void OctTree::GetObjectsInRadius(std::vector<ObjectPtr>& objects, const BoundingSphere& region, const std::vector<NounType>& types) const {
		if (!mBuilt) {
			return;
		}

		for (const auto& object : mObjects) {
			if (types.empty()) {
				if (region.Intersects(object->GetBoundingBox())) {
					objects.push_back(object);
				}
			} else {
				auto type = object->GetType();
				for (auto acceptedType : types) {
					if (type == acceptedType) {
						if (region.Intersects(object->GetBoundingBox())) {
							objects.push_back(object);
						}
						break;
					}
				}
			}
		}

		if (mActiveNodes) {
			for (const auto& childNode : mChildNode) {
				if (childNode && region.Intersects(childNode->mRegion)) {
					childNode->GetObjectsInRadius(objects, region, types);
				}
			}
		}
	}

	void OctTree::GetTriggerInteractions(std::vector<std::tuple<TriggerVolumePtr, ObjectPtr>>& collisions, std::vector<TriggerVolumePtr> parentTriggers) const {
		// TODO: just store triggers in a seperate vector as to not fetch them each time?
		if (!mObjects.empty()) {
			decltype(parentTriggers) localTriggers;
			if (parentTriggers.empty()) {
				for (const auto& object : mObjects) {
					if (object->IsTrigger() && !object->GetBoundingBox().IsPoint()) {
						localTriggers.push_back(std::static_pointer_cast<TriggerVolume>(object));
					}
				}
			} else {
				for (const auto& trigger : parentTriggers) {
					const auto& triggerBox = trigger->GetBoundingBox();
					for (const auto& object : mObjects) {
						const auto& objectBox = object->GetBoundingBox();
						if (object->IsTrigger()) {
							if (!objectBox.IsPoint()) {
								localTriggers.push_back(std::static_pointer_cast<TriggerVolume>(object));
							}
							continue;
						}

						if (object != trigger->GetOwnerObject() && triggerBox.Intersects(objectBox)) {
							collisions.push_back(std::make_tuple(trigger, object));
						}
					}
				}
			}

			if (!localTriggers.empty()) {
#if 1
				auto node = this;
				while (node) {
					if (!node->mParentNode) {
						break;
					}
					node = node->mParentNode;
				}

				for (const auto& trigger : localTriggers) {
					std::vector<ObjectPtr> foundObjects;
					node->GetObjectsInRegion(foundObjects, trigger->GetBoundingBox(), {});

					for (const auto& object : foundObjects) {
						if (object->IsTrigger() || object == trigger->GetOwnerObject()) {
							continue;
						}
						collisions.push_back(std::make_tuple(trigger, object));
					}
			}
#else
				auto current = this;
				while (current) {
					for (const auto& trigger : localTriggers) {
						const auto& triggerBox = trigger->GetBoundingBox();
						for (const auto& object : current->mObjects) {
							if (object->IsTrigger()) {
								continue;
							}

							if (object != trigger->GetOwnerObject() && triggerBox.Intersects(object->GetBoundingBox())) {
								collisions.push_back(std::make_tuple(trigger, object));
							}
						}
					}
					current = current->mParentNode;
				}
#endif
			}

			parentTriggers.insert(parentTriggers.end(), localTriggers.begin(), localTriggers.end());
		}

		if (mActiveNodes) {
			for (const auto& childNode : mChildNode) {
				if (childNode) {
					childNode->GetTriggerInteractions(collisions, parentTriggers);
				}
			}
		}
	}

	OctTree* OctTree::CreateNode(const BoundingBox& region, const std::vector<ObjectPtr>& objectList) {
		if (objectList.empty()) {
			return nullptr;
		}

		auto tree = new OctTree(region);
		tree->mParentNode = this;
		tree->mObjects = objectList;

		return tree;
	}

	OctTree* OctTree::CreateNode(const BoundingBox& region, const ObjectPtr& object) {
		if (!object) {
			return nullptr;
		}

		auto tree = new OctTree(region);
		tree->mParentNode = this;
		tree->mObjects.push_back(object);

		return tree;
	}
}
