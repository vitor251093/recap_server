
// Include
#include "collision.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/norm.hpp>

/*
	Axis direction in darkspore
		X = left right
		Y = up down
		Z = in out
*/

// Game
namespace Game {
	// BoundingBox
	BoundingBox::BoundingBox() {
		center = glm::zero<glm::vec3>();
		extent = glm::zero<glm::vec3>();
	}

	BoundingBox::BoundingBox(const glm::vec3& min, const glm::vec3& max) {
		constexpr auto half = glm::vec3(0.5f);
		center = (max + min) * half;
		extent = (max - min) * half;
	}

	bool BoundingBox::IsPoint() const {
		return extent.x == 0 || extent.y == 0 || extent.z == 0;
	}

	bool BoundingBox::Contains(const glm::vec3& point) const {
		auto distance = glm::abs(center - point);
		return glm::all(glm::lessThan(distance, extent));
	}

	bool BoundingBox::Contains(const BoundingBox& boundingBox) const {
		auto distance = glm::abs(center - boundingBox.center);
		auto distanceRequired = extent - boundingBox.extent;
		return glm::all(glm::lessThanEqual(distance, distanceRequired));
	}

	bool BoundingBox::Contains(const BoundingSphere& boundingSphere) const {
		auto delta = extent - boundingSphere.radius;
		return !glm::any(glm::lessThan(delta, glm::zero<glm::vec3>())) && Contains(boundingSphere.center);
	}

	bool BoundingBox::Intersects(const BoundingBox& boundingBox) const {
		auto distance = glm::abs(center - boundingBox.center);
		auto distanceRequired = extent + boundingBox.extent;
		return glm::all(glm::lessThanEqual(distance, distanceRequired));
	}

	bool BoundingBox::Intersects(const BoundingSphere& boundingSphere) const {
		return boundingSphere.Intersects(*this);
	}

	bool BoundingBox::Touches(const BoundingBox& boundingBox) const {
		auto distance = glm::abs(center - boundingBox.center);
		auto distanceRequired = extent + boundingBox.extent;

		auto results = glm::equal(distance, distanceRequired);
		return (results.x + results.y + results.z) >= 2;
	}

	bool BoundingBox::Touches(const BoundingSphere& boundingSphere) const {
		return boundingSphere.Touches(*this);
	}

	void BoundingBox::Transform(const glm::mat4& matrix) {
		glm::vec3 min = GetMin();
		glm::vec3 max = GetMax();

		glm::vec3 xa = glm::vec3(matrix[0] * min.x);
		glm::vec3 xb = glm::vec3(matrix[0] * max.x);
		glm::vec3 xMin = glm::min(xa, xb);
		glm::vec3 xMax = glm::max(xa, xb);

		glm::vec3 ya = glm::vec3(matrix[1] * min.y);
		glm::vec3 yb = glm::vec3(matrix[1] * max.y);
		glm::vec3 yMin = glm::min(ya, yb);
		glm::vec3 yMax = glm::max(ya, yb);

		glm::vec3 za = glm::vec3(matrix[2] * min.z);
		glm::vec3 zb = glm::vec3(matrix[2] * max.z);
		glm::vec3 zMin = glm::min(za, zb);
		glm::vec3 zMax = glm::max(za, zb);

		glm::vec3 newMin = xMin + yMin + zMin + glm::vec3(matrix[3]);
		glm::vec3 newMax = xMax + yMax + zMax + glm::vec3(matrix[3]);

		*this = BoundingBox(newMin, newMax);
	}

	glm::vec3 BoundingBox::GetMin() const {
		return center - extent;
	}

	glm::vec3 BoundingBox::GetMax() const {
		return center + extent;
	}

	glm::vec3 BoundingBox::GetSize() const {
		return extent * 2.0f;
	}

	// BoundingSphere
	BoundingSphere::BoundingSphere() : center(glm::zero<glm::vec3>()), radius(0) {}
	BoundingSphere::BoundingSphere(const glm::vec3& center, float radius) : center(center), radius(radius) {}

	bool BoundingSphere::IsPoint() const {
		return radius == 0;
	}

	bool BoundingSphere::Contains(const glm::vec3& point) const {
		return glm::length(center - point) < radius;
	}

	bool BoundingSphere::Contains(const BoundingBox& boundingBox) const {
		auto closestPoint = glm::clamp(center, boundingBox.GetMin(), boundingBox.GetMax());
		return glm::length(closestPoint - center) < radius;
	}

	bool BoundingSphere::Contains(const BoundingSphere& boundingSphere) const {
		auto fullRadius = radius + boundingSphere.radius;
		return glm::length2(center - boundingSphere.center) < glm::dot(fullRadius, fullRadius);
	}

	bool BoundingSphere::Intersects(const BoundingBox& boundingBox) const {
		auto closestPoint = glm::clamp(center, boundingBox.GetMin(), boundingBox.GetMax());
		return glm::length(closestPoint - center) <= radius;
	}

	bool BoundingSphere::Intersects(const BoundingSphere& boundingSphere) const {
		auto fullRadius = radius + boundingSphere.radius;
		return glm::length2(center - boundingSphere.center) <= glm::dot(fullRadius, fullRadius);
	}

	bool BoundingSphere::Touches(const BoundingBox& boundingBox) const {
		/*
		auto distance = glm::abs(mCenter - boundingBox.mCenter);
		auto distanceRequired = mExtent + boundingBox.mExtent;

		auto results = glm::equal(distance, distanceRequired);
		return (results.x + results.y + results.z) >= 2;
		*/
		return false;
	}

	bool BoundingSphere::Touches(const BoundingSphere& boundingSphere) const {
		return false;
	}

	// BoundingCapsule
	BoundingCapsule::BoundingCapsule() : center(glm::zero<glm::vec3>()), radius(0), halfHeight(0) {}
	BoundingCapsule::BoundingCapsule(const glm::vec3& center, float radius, float height) : center(center), radius(radius), halfHeight(height * 0.5f) {}

	bool BoundingCapsule::IsPoint() const {
		return radius == 0;
	}

	bool BoundingCapsule::Contains(const glm::vec3& point) const {
		return glm::length(center - point) < radius;
	}

	bool BoundingCapsule::Contains(const BoundingBox& boundingBox) const {
		// find top bottom or center(cylinder)
		auto closestPoint = glm::clamp(center, boundingBox.GetMin(), boundingBox.GetMax());
		return glm::length(closestPoint - center) < radius;
	}

	bool BoundingCapsule::Contains(const BoundingSphere& boundingSphere) const {
		auto fullRadius = radius + boundingSphere.radius;
		return glm::length2(center - boundingSphere.center) < glm::dot(fullRadius, fullRadius);
	}

	bool BoundingCapsule::Intersects(const BoundingBox& boundingBox) const {
		auto min = GetMin();
		auto max = GetMax();

		auto sphereTopCenter = max;
		sphereTopCenter.y -= radius;

		auto sphereBottomCenter = min;
		sphereBottomCenter.y += radius;

		auto closestPoint = glm::clamp(center, boundingBox.GetMin(), boundingBox.GetMax());
		return glm::length(closestPoint - center) <= radius;
	}

	bool BoundingCapsule::Intersects(const BoundingSphere& boundingSphere) const {
		auto fullRadius = radius + boundingSphere.radius;
		return glm::length2(center - boundingSphere.center) <= glm::dot(fullRadius, fullRadius);
	}

	bool BoundingCapsule::Touches(const BoundingBox& boundingBox) const {
		/*
		auto distance = glm::abs(mCenter - boundingBox.mCenter);
		auto distanceRequired = mExtent + boundingBox.mExtent;

		auto results = glm::equal(distance, distanceRequired);
		return (results.x + results.y + results.z) >= 2;
		*/
		return false;
	}

	bool BoundingCapsule::Touches(const BoundingSphere& boundingSphere) const {
		return false;
	}

	glm::vec3 BoundingCapsule::GetMin() const {
		auto value = center;
		value.y -= halfHeight;
		return std::move(value);
	}

	glm::vec3 BoundingCapsule::GetMax() const {
		auto value = center;
		value.y += halfHeight;
		return std::move(value);
	}

	// BoundingShape
	BoundingShape::BoundingShape() : box() {}
	BoundingShape::BoundingShape(const glm::vec3& min, const glm::vec3& max) : box(min, max) {}
	BoundingShape::BoundingShape(const glm::vec3& center, float radius) : sphere(center, radius) { box.extent.y = NAN; }
	BoundingShape::BoundingShape(const glm::vec3& center, float radius, float height) : capsule(center, radius, height) { box.extent.z = NAN; }

	bool BoundingShape::IsPoint() const {
		// also true for sphere.radius == 0
		return box.extent.x == 0;
	}

	bool BoundingShape::IsBox() const {
		return !IsSphere();
	}

	bool BoundingShape::IsSphere() const {
		return glm::isnan(box.extent.y);
	}

	bool BoundingShape::IsCapsule() const {
		return glm::isnan(box.extent.z);
	}

	bool BoundingShape::Contains(const glm::vec3& point) const {
		if (IsSphere()) { return sphere.Contains(point); }
		return box.Contains(point);
	}

	bool BoundingShape::Contains(const BoundingBox& box) const {
		if (IsSphere()) { return sphere.Contains(box); }
		return box.Contains(box);
	}

	bool BoundingShape::Contains(const BoundingSphere& sphere) const {
		if (IsSphere()) { return sphere.Contains(box); }
		return box.Contains(box);
	}

	bool BoundingShape::Intersects(const BoundingBox& box) const {
		if (IsSphere()) { return sphere.Intersects(box); }
		return box.Intersects(box);
	}

	bool BoundingShape::Intersects(const BoundingSphere& sphere) const {
		if (IsSphere()) { return sphere.Intersects(sphere); }
		return box.Intersects(sphere);
	}

	bool BoundingShape::Touches(const BoundingBox& box) const {
		if (IsSphere()) { return sphere.Touches(box); }
		return box.Touches(box);
	}

	bool BoundingShape::Touches(const BoundingSphere& sphere) const {
		if (IsSphere()) { return sphere.Touches(sphere); }
		return box.Touches(sphere);
	}

	void BoundingShape::Transform(const glm::mat4& matrix) {
		if (IsBox()) { return box.Transform(matrix); }
	}

	// CollisionObject

}
