
#ifndef _GAME_COLLISION_HEADER
#define _GAME_COLLISION_HEADER

// Include
#include <cstdint>

#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>

// Game
namespace Game {
	// predefined
	struct BoundingSphere;
	struct BoundingCapsule;
	struct BoundingShape;

	// BoundingBox
	struct BoundingBox {
		// members
		glm::vec3 center;
		glm::vec3 extent;

		// functions
		BoundingBox();
		BoundingBox(const glm::vec3& min, const glm::vec3& max);

		bool IsPoint() const;
		bool Contains(const glm::vec3& point) const;
		bool Contains(const BoundingBox& boundingBox) const;
		bool Contains(const BoundingSphere& boundingSphere) const;
		bool Intersects(const BoundingBox& boundingBox) const;
		bool Intersects(const BoundingSphere& boundingSphere) const;
		bool Touches(const BoundingBox& boundingBox) const;
		bool Touches(const BoundingSphere& boundingSphere) const;

		void Transform(const glm::mat4& matrix);

		glm::vec3 GetMin() const;
		glm::vec3 GetMax() const;

		glm::vec3 GetSize() const;
	};

	// BoundingSphere
	struct BoundingSphere {
		// members
		glm::vec3 center;
		float radius;

		// functions
		BoundingSphere();
		BoundingSphere(const glm::vec3& center, float radius);

		bool IsPoint() const;
		bool Contains(const glm::vec3& point) const;
		bool Contains(const BoundingBox& boundingBox) const;
		bool Contains(const BoundingSphere& boundingSphere) const;
		bool Intersects(const BoundingBox& boundingBox) const;
		bool Intersects(const BoundingSphere& boundingSphere) const;
		bool Touches(const BoundingBox& boundingBox) const;
		bool Touches(const BoundingSphere& boundingSphere) const;
	};

	// BoundingCapsule
	struct BoundingCapsule {
		// members
		glm::vec3 center;
		float radius;
		float halfHeight;

		// functions
		BoundingCapsule();
		BoundingCapsule(const glm::vec3& center, float radius, float height);

		bool IsPoint() const;
		bool Contains(const glm::vec3& point) const;
		bool Contains(const BoundingBox& boundingBox) const;
		bool Contains(const BoundingSphere& boundingSphere) const;
		bool Intersects(const BoundingBox& boundingBox) const;
		bool Intersects(const BoundingSphere& boundingSphere) const;
		bool Touches(const BoundingBox& boundingBox) const;
		bool Touches(const BoundingSphere& boundingSphere) const;

		glm::vec3 GetMin() const;
		glm::vec3 GetMax() const;
	};

	// BoundingShape
	struct BoundingShape {
		// members
		union {
			// center / box.center / sphere.center are the same
			// box.extent.x is the same as sphere.radius
			glm::vec3 center;

			BoundingBox box;
			BoundingSphere sphere;
			BoundingCapsule capsule;
		};

		// functions
		BoundingShape();
		BoundingShape(const glm::vec3& min, const glm::vec3& max);
		BoundingShape(const glm::vec3& center, float radius);
		BoundingShape(const glm::vec3& center, float radius, float height);

		bool IsPoint() const;
		bool IsBox() const;
		bool IsSphere() const;
		bool IsCapsule() const;

		bool Contains(const glm::vec3& point) const;
		bool Contains(const BoundingBox& box) const;
		bool Contains(const BoundingSphere& sphere) const;
		bool Intersects(const BoundingBox& box) const;
		bool Intersects(const BoundingSphere& sphere) const;
		bool Touches(const BoundingBox& box) const;
		bool Touches(const BoundingSphere& sphere) const;

		void Transform(const glm::mat4& matrix);
	};

	// CollisionObject
	class CollisionObject {
		public:
			

		private:
			BoundingShape mBoundingShape;

			// collision pairs? etc?
	};
}

#endif
