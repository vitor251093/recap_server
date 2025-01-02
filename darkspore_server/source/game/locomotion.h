
#ifndef _GAME_LOCOMOTION_HEADER
#define _GAME_LOCOMOTION_HEADER

// Include
#include "predefined.h"

#include <glm/glm.hpp>

#include <cstdint>
#include <vector>
#include <bitset>
#include <memory>

// RakNet
namespace RakNet {
	class BitStream;
}

// Game
namespace Game {
	/*
		Goal flags
			0x001 = move?
			0x002 = used with 0x100 in "TurnToFaceTargetObject" (stand still?)
			0x004 = used with some jump functions and slide
			0x008 = apply external velocity?
			0x020 = stop?
			0x040 = has target object (ignored if flag 0x001 is set)
			0x100 = face object when moving?
			0x400 = something
			0x800 = start rotating towards facing direction?
	*/

	// LocomotionDataBits
	namespace LocomotionDataBits {
		enum : uint8_t {
			LobStartTime = 0,
			LobPreviousSpeedModifier,
			LobParameters,
			ProjectileParameters,
			GoalFlags,
			GoalPosition,
			PartialGoalPosition,
			Facing,
			ExternalLinearVelocity,
			ExternalForce,
			AllowedStopDistance,
			DesiredStopDistance,
			TargetId,
			TargetPosition,
			ExpectedGeoCollision,
			InitialDirection,
			Offset,
			ReflectedLastUpdate,
			Count
		};
	}

	// LocomotionEvent
	enum class LocomotionEvent : uint8_t {
		None = 0,
		NearGoal,

	};

	// GoalFlags
	enum class GoalFlags : uint32_t {

	};

	// LobParameters
	class LobParameters {
		public:
			void WriteTo(RakNet::BitStream& stream) const;
			void WriteReflection(RakNet::BitStream& stream) const;

		public:
			glm::vec3 mUpDirection {};
			glm::vec3 mPlaneDirection {};

			int32_t mBounceNumber = 0;

			float mUpQuadratic = 0;
			float mUpLinear = 0;
			float mPlaneLinear = 0;
			float mBounceRestitution = 0;

			bool mGroundCollisionOnly = false;
			bool mStopBounceOnCreatures = false;

			friend class Locomotion;
	};

	// ProjectileParameters
	class ProjectileParameters {
		public:
			void WriteTo(RakNet::BitStream& stream) const;
			void WriteReflection(RakNet::BitStream& stream) const;

		public:
			glm::vec3 mDirection {};

			uint32_t mJinkInfo = 0;

			float mSpeed = 0;
			float mAcceleration = 0;
			float mRange = 0;
			float mSpinRate = 0;
			float mHomingDelay = 0;
			float mTurnRate = 0;
			float mTurnAcceleration = 0;
			float mEccentricity = 0;
			float mCombatantSweepHeight = 0;

			uint8_t mProjectileFlags = 0;

			bool mPiercing = false;
			bool mIgnoreGroundCollide = false;
			bool mIgnoreCreatureCollide = false;

			friend class Locomotion;
	};

	// Locomotion
	class Locomotion {
		public:
			Locomotion(const ObjectPtr& object);

			//
			const ObjectPtr& GetObject() const;

			// Simulate client positions
			void Update(float deltaTime);

			//
			ProjectileParameters& GetProjectileParameters();
			LobParameters& GetLobParameters();

			int32_t GetReflectedLastUpdate() const;
			void SetReflectedLastUpdate(int32_t lastUpdate);

			const glm::vec3& GetGoalPosition() const;
			const glm::vec3& GetPartialGoalPosition() const;
			const glm::vec3& GetFacing() const;
			const glm::vec3& GetExternalLinearVelocity() const;
			const glm::vec3& GetExternalForce() const;
			const glm::vec3& GetTargetPosition() const;
			const glm::vec3& GetExpectedGeoCollision() const;
			const glm::vec3& GetInitialDirection() const;
			const glm::vec3& GetOffset() const;

			void SetInitialDirection(const glm::vec3& direction);
			void SetTargetPosition(const glm::vec3& position);
			void SetExpectedGeoCollision(const glm::vec3& position);

			bool HasCollidedWithCreature() const;
			void SetHasCollidedWithCreature(bool hasCollided);

			bool HasCollided() const;
			void SetHasCollided(bool hasCollided);

			uint32_t GetGoalFlags() const;
			uint32_t GetTargetId() const;
			void SetTargetId(uint32_t targetId);

			float GetAllowedStopDistance() const;
			float GetDesiredStopDistance() const;

			void SetGoalPosition(const glm::vec3& position);
			void SetGoalPositionWithDistance(const glm::vec3& position, float distance);
			void SetPartialGoalPosition(const glm::vec3& position);
			void SetGoalObject(const ObjectPtr& object, float distance, bool useTargetPosition, bool unk);
			void SetGoalObjectEx(const ObjectPtr& object, float distance, bool useTargetPosition);
			void SetGoalFlags(uint32_t flags);
			void SetFacing(const glm::vec3& facingPosition);
			void Stop();
			void TurnToFaceTargetObject(const ObjectPtr& object);
			void MoveToPointWhileFacingTarget(const glm::vec3& position, const ObjectPtr& object);
			void ApplyExternalVelocity(const glm::vec3& velocity);
			void ClearExternalVelocity();
			void ClearTargetObject();

			void FaceObjectDuringMove(const ObjectPtr& object);

			void SlideToPoint(const glm::vec3& position, float speed);
			void Jump(const glm::vec3& direction, float distance, float speed, const glm::vec3& facing,
				float minJumpHeight, float maxJumpHeight, float rangeToHitMaxJumpHeight, bool param_9);

			void WriteTo(RakNet::BitStream& stream) const;
			void WriteReflection(RakNet::BitStream& stream) const;

		private:
			bool CollideWithCreature(const glm::vec3& position, glm::vec3& collisionPosition);

			void Projectile(float value);
			void OrbitOwner(float value);
			void GroundRoll(float value);
			bool JumpSimulation(float value);


		private:
			ObjectPtr mObject;

			ProjectileParameters mProjectileParameters;

			LobParameters mLobParameters;

			glm::vec3 mGoalPosition {};
			glm::vec3 mPartialGoalPosition {};
			glm::vec3 mFacing {};
			glm::vec3 mExternalLinearVelocity {};
			glm::vec3 mExternalForce {};
			glm::vec3 mTargetPosition {};
			glm::vec3 mExpectedGeoCollision {};
			glm::vec3 mInitialDirection {};
			glm::vec3 mOffset {};

			uint64_t mLobStartTime = 0;

			uint32_t mGoalFlags = 0;
			uint32_t mTargetId = 0;

			int32_t mReflectedCurrentUpdate = -1;
			int32_t mReflectedLastUpdate = 0;

			float mLobPrevSpeedModifier = 0;
			float mAllowedStopDistance = 0;
			float mDesiredStopDistance = 0;

			bool mHasCollidedWithCreature = false;
			bool mHasCollided = false;

			std::bitset<LocomotionDataBits::Count> mDataBits;
	};
}

#endif
