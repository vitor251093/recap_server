
// Include
#include "locomotion.h"
#include "object.h"

#include "raknet/types.h"

#include <algorithm>

// internal floats
constexpr size_t TEST_VALUE = 0x37800000U;

// unknown functions
namespace {
	void Func(Game::Object& object) {}
}

// Game
namespace Game {
	/*
		Goal flag meanings
			0x001 = something (can combine with 0x002, 0x400)
			0x002 = use facing
			0x004 = unknown
			0x008 = use external velocity
			0x020 = used in Stop and ClearExternalVelocity (allows use of flags 0x100, 0x040, 0x004)
			0x040 = use target position / id
			0x080 = unknown (updates partial goal position)
			0x100 = use target id
			0x400 = requires target id (face target?)
			0x800 = used in (
				MoveTowardsObject
				MoveToPointExact
				MoveToCircleEdge
				MoveToPointWithinRange
				TurnToFace
			)
	*/

	// LobParameters
	void LobParameters::WriteTo(RakNet::BitStream& stream) const {
		using RakNet::bytes_to_bits;
		using RakNet::ReallocateStream;

		constexpr auto size = bytes_to_bits(0x54);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x18));
		Write(stream, mUpDirection);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x30));
		Write(stream, mBounceNumber);
		Write(stream, mBounceRestitution);
		Write(stream, mGroundCollisionOnly);
		Write(stream, mStopBounceOnCreatures);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x3C));
		Write(stream, mPlaneDirection);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x48));
		Write(stream, mPlaneLinear);
		Write(stream, mUpLinear);
		Write(stream, mUpQuadratic);

		stream.SetWriteOffset(writeOffset + size);
	}

	void LobParameters::WriteReflection(RakNet::BitStream& stream) const {
		RakNet::reflection_serializer<9> reflector(stream);
		reflector.begin();
		reflector.write<0>(mPlaneLinear);
		reflector.write<1>(mUpLinear);
		reflector.write<2>(mUpQuadratic);
		reflector.write<3>(mUpDirection);
		reflector.write<4>(mPlaneDirection);
		reflector.write<5>(mBounceNumber);
		reflector.write<6>(mBounceRestitution);
		reflector.write<7>(mGroundCollisionOnly);
		reflector.write<8>(mStopBounceOnCreatures);
		reflector.end();
	}

	// ProjectileParameters
	void ProjectileParameters::WriteTo(RakNet::BitStream& stream) const {
		using RakNet::bytes_to_bits;
		using RakNet::ReallocateStream;

		constexpr auto size = bytes_to_bits(0x3C);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset);
		Write(stream, mSpeed);
		Write(stream, mAcceleration);
		Write(stream, mJinkInfo);
		Write(stream, mRange);
		Write(stream, mSpinRate);
		Write(stream, mDirection);
		Write(stream, mProjectileFlags);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x24));
		Write(stream, mHomingDelay);
		Write(stream, mTurnRate);
		Write(stream, mTurnAcceleration);
		Write(stream, mPiercing);
		Write(stream, mIgnoreGroundCollide);
		Write(stream, mIgnoreCreatureCollide);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x34));
		Write(stream, mEccentricity);
		Write(stream, mCombatantSweepHeight);

		stream.SetWriteOffset(writeOffset + size);
	}

	void ProjectileParameters::WriteReflection(RakNet::BitStream& stream) const {
		RakNet::reflection_serializer<15> reflector(stream);
		reflector.begin();
		reflector.write<0>(mSpeed);
		reflector.write<1>(mAcceleration);
		reflector.write<2>(mJinkInfo);
		reflector.write<3>(mRange);
		reflector.write<4>(mSpinRate);
		reflector.write<5>(mDirection);
		reflector.write<6>(mProjectileFlags);
		reflector.write<7>(mHomingDelay);
		reflector.write<8>(mTurnRate);
		reflector.write<9>(mTurnAcceleration);
		reflector.write<10>(mEccentricity);
		reflector.write<11>(mPiercing);
		reflector.write<12>(mIgnoreGroundCollide);
		reflector.write<13>(mIgnoreCreatureCollide);
		reflector.write<14>(mCombatantSweepHeight);
		reflector.end();
	}

	// Locomotion
	Locomotion::Locomotion(const ObjectPtr& object) : mObject(object) {
		Stop();
	}

	const ObjectPtr& Locomotion::GetObject() const {
		return mObject;
	}

	void Locomotion::Update(float deltaTime) {
		switch (mObject->GetMovementType()) {
			case MovementType::Pathfinding: {
				if (false) {
					mObject->SetLinearVelocity(glm::zero<glm::vec3>());
					mObject->SetAngularVelocity(glm::zero<glm::vec3>());
				}
				break;
			}

			case MovementType::Projectile: {
				Projectile(deltaTime);
				break;
			}

			case MovementType::Ballistic: {
				break;
			}

			case MovementType::HomingProjectile: {
				break;
			}

			case MovementType::Lobbed: {
				break;
			}

			case MovementType::OrbitOwner: {
				OrbitOwner(deltaTime);
				break;
			}

			case MovementType::GroundRoll: {
				GroundRoll(deltaTime);
				break;
			}
		}
		/*
		if (mObject.IsPlayerControlled() && utils::enum_helper<GoalFlags>::test(mGoalFlags, 1U << 7)) {
			pvVar16 = FUN_00a18600((int)pvVar3);
			local_f8 = pvVar16->x;
			local_f4 = pvVar16->y;
			local_f0 = pvVar16->z;
			(pLVar10->partial_goal_position).x = local_f8;
			(pLVar10->partial_goal_position).y = local_f4;
			(pLVar10->partial_goal_position).z = local_f0;
		} else {
			pfVar13 = FUN_009ee680(&local_88, pLVar10, pvVar3);
			(pLVar10->partial_goal_position).x = pfVar13->x;
			(pLVar10->partial_goal_position).y = pfVar13->y;
			(pLVar10->partial_goal_position).z = pfVar13->z;
		}
		*/

		if (JumpSimulation(1)) {
			// We are in a jumping state, ignore other movement.
			return;
		}

		if (mGoalFlags & 0x008) {
			if (mExternalLinearVelocity != glm::zero<glm::vec3>()) {

			}
			/*
			if ((((iVar8->external_linear_velocity).x != vec3_0158cc18.x) ||
				((iVar8->external_linear_velocity).y != vec3_0158cc18.y)) ||
				((iVar8->external_linear_velocity).z != vec3_0158cc18.z)) {
				local_f8 = (iVar8->external_linear_velocity).x;
				local_f4 = (iVar8->external_linear_velocity).y;
				local_f0 = (iVar8->external_linear_velocity).z;
				local_eb = 0;
				local_ec = 1;
				local_110 = SQRT(local_f0 * local_f0 + local_f4 * local_f4 + local_f8 * local_f8);
				fVar19 = 1.0 / (local_110 + 1.525879e-05);
				local_f8 = fVar19 * local_f8;
				local_f4 = local_f4 * fVar19;
				local_f0 = local_f0 * fVar19;
				local_e4 = local_f8;
				local_e0 = local_f4;
				local_dc = local_f0;
				FUN_00a17e70(pvVar3, &local_e4, local_110, &local_ec);
				pvVar16 = Object::GetFacing(pOVar2, &local_88);
				local_94 = pvVar16->x;
				local_90 = pvVar16->y;
				local_8c = pvVar16->z;
				FUN_00a18400(pvVar3, &local_94);
			}
			*/
		} else if (mGoalFlags & 0x020) {
			/*
			FUN_009eb420(pOVar2);
			bVar7 = FUN_00a187e0((int)pvVar3);
			if (bVar7 == false) {
				FUN_00a17e20(pvVar3, &local_112);
			}
			*/
		} else if (mTargetId == 0 || (mGoalFlags & 0x100)) {

		}
		/*
		uVar4 = iVar8->goal_flags;

		local_112 = true;
		if ((bVar6 == false) || ((object == pOVar2 && (param_2 == false)))) {
			if ((iVar8->target_id == 0) || ((uVar4 >> 8 & 1) != 0)) {
				if (*(char*)&iVar8->field_0x1a8 == '\0') {
					if ((uVar4 & 1) == 0) {
						if ((uVar4 >> 6 & 1) == 0) {
							pbVar20 = &local_114;
							local_114 = false;
						} else {
							fVar19 = iVar8->timeLocked - timeInSeconds;
							iVar8->timeLocked = fVar19;
							if (0.0 < fVar19) goto LAB_009ef634;
							fVar18 = (float10)FUN_009c18e0();
							pbVar20 = &local_112;
							iVar8->timeLocked = (float)(fVar18 * (float10)0.1 + (float10)0.2);
						}
						FUN_00a17e20(pvVar3, pbVar20);
					} else {
						fVar19 = iVar8->timeLocked - timeInSeconds;
						iVar8->timeLocked = fVar19;
						if (fVar19 <= 0.0) {
							fVar18 = (float10)FUN_009c18e0();
							pvVar16 = &iVar8->facingEx;
							iVar8->timeLocked = (float)(fVar18 * (float10)0.1 + (float10)0.2);
							if ((iVar8->goal_flags >> 1 & 1) == 0) {
								pvVar16 = &vec3_0158cc18;
							}
							local_ac = pvVar16->x;
							fStack168 = pvVar16->y;
							fStack164 = pvVar16->z;
							FUN_009ed610(pvVar3, &iVar8->goal_position);
						}
					}
				}
			} else {
				pOVar11 = GetSporeLabsObject(local_b8, iVar8->target_id);
				if (pOVar11 == (Object*)0x0) {
					local_114 = false;
					FUN_00a17e20(pvVar3, &local_114);
					goto LAB_009ef837;
				}
				pvVar16 = &iVar8->facingEx;
				if ((iVar8->goal_flags >> 1 & 1) == 0) {
					pvVar16 = &vec3_0158cc18;
				}
				local_a0 = pvVar16->x;
				local_9c = pvVar16->y;
				local_98 = pvVar16->z;
				FUN_009ed610(pvVar3, &pOVar11->position);
			}
		} else {
			fVar19 = (iVar8->field_0x160).x - (iVar8->partial_goal_position).x;
			local_b4 = iVar8->desired_stop_distance;
			fVar1 = (iVar8->field_0x160).y - (iVar8->partial_goal_position).y;
			local_c0 = local_b4;
			fVar5 = (iVar8->field_0x160).z - (iVar8->partial_goal_position).z;
			local_b0 = 0.0;
			pfVar15 = &local_110;
			local_110 = local_b4 - SQRT(fVar1 * fVar1 + fVar5 * fVar5 + fVar19 * fVar19);
			if (local_110 <= 0.0) {
				pfVar15 = &local_b0;
			}
			fVar19 = *pfVar15;
			iVar8->desired_stop_distance = fVar19;
			iVar8->allowed_stop_distance = fVar19;
			iVar8->goal_flags = uVar4 | 1;
			FUN_009ed610(pvVar3, &iVar8->partial_goal_position);
			iVar8->desired_stop_distance = local_c0;
			iVar8->allowed_stop_distance = local_c0;
		}
LAB_009ef634:
		FUN_009eb420(pOVar2);
		local_c8 = 1.0;
		if ((((iVar8->external_force).x != vec3_0158cc18.x) ||
			((iVar8->external_force).y != vec3_0158cc18.y)) ||
			((iVar8->external_force).z != vec3_0158cc18.z)) {
			pfVar15 = (float*)FUN_00a19540((int)pvVar3);
			local_d8 = 0.0;
			local_d4 = 0;
			local_d0 = pfVar15[3] * 0.7071068 - *pfVar15 * 0.7071068;
			local_cc = *pfVar15 * 0.7071068 - pfVar15[3] * -0.7071068;
			FUN_00412280(&local_7c);
			FUN_004c6620(&local_7c);
			puVar12 = (undefined4*)FUN_0040f240(local_24, &local_d8);
			local_10c = (iVar8->external_force).x;
			local_108 = (iVar8->external_force).y;
			iVar9 = 9;
			local_104 = (iVar8->external_force).z;
			puVar17 = local_68;
			while (iVar9 != 0) {
				iVar9 += -1;
				*puVar17 = *puVar12;
				puVar12 = puVar12 + 1;
				puVar17 = puVar17 + 1;
			}
			local_7c |= 2;
			local_7a += 1;
			FUN_00cb48f0(&local_7c, &local_10c);
			fVar19 = SQRT(local_10c * local_10c +
				local_108 * local_108 + local_104 * local_104);
			if (0.8 < fVar19) {
				fVar19 = 0.8 / fVar19;
				local_10c = local_10c * fVar19;
				local_108 = local_108 * fVar19;
				local_104 = local_104 * fVar19;
			}
			local_110 = SQRT(1.0 - local_10c * local_10c) + local_108;
			local_c8 = local_110;
			if (local_110 < DAT_0116bc90) {
				local_c8 = DAT_0116bc90;
			}
			if (DAT_0116bc94 < local_c8) {
				local_c8 = DAT_0116bc94;
			}
		}
		FUN_00a184d0(pvVar3, local_c8);
		*/
	}

	ProjectileParameters& Locomotion::GetProjectileParameters() {
		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateLocomotion);
		mDataBits.set(LocomotionDataBits::ProjectileParameters);
		return mProjectileParameters;
	}

	LobParameters& Locomotion::GetLobParameters() {
		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateLocomotion);
		mDataBits.set(LocomotionDataBits::LobParameters);
		return mLobParameters;
	}

	int32_t Locomotion::GetReflectedLastUpdate() const {
		return mReflectedLastUpdate;
	}

	void Locomotion::SetReflectedLastUpdate(int32_t lastUpdate) {
		mReflectedLastUpdate = lastUpdate;
		mDataBits.set(LocomotionDataBits::ReflectedLastUpdate);
	}

	const glm::vec3& Locomotion::GetGoalPosition() const {
		return mGoalPosition;
	}

	const glm::vec3& Locomotion::GetPartialGoalPosition() const {
		return mPartialGoalPosition;
	}

	const glm::vec3& Locomotion::GetFacing() const {
		return mFacing;
	}

	const glm::vec3& Locomotion::GetExternalLinearVelocity() const {
		return mExternalLinearVelocity;
	}

	const glm::vec3& Locomotion::GetExternalForce() const {
		return mExternalForce;
	}

	const glm::vec3& Locomotion::GetTargetPosition() const {
		return mTargetPosition;
	}

	const glm::vec3& Locomotion::GetExpectedGeoCollision() const {
		return mExpectedGeoCollision;
	}

	const glm::vec3& Locomotion::GetInitialDirection() const {
		return mInitialDirection;
	}

	const glm::vec3& Locomotion::GetOffset() const {
		return mOffset;
	}

	void Locomotion::SetInitialDirection(const glm::vec3& direction) {
		mInitialDirection = direction;
		mDataBits.set(LocomotionDataBits::InitialDirection);
	}

	void Locomotion::SetTargetPosition(const glm::vec3& position) {
		mTargetPosition = position;
		mDataBits.set(LocomotionDataBits::TargetPosition);
	}

	void Locomotion::SetExpectedGeoCollision(const glm::vec3& position) {
		mExpectedGeoCollision = position;
		mDataBits.set(LocomotionDataBits::ExpectedGeoCollision);
	}

	bool Locomotion::HasCollidedWithCreature() const {
		return mHasCollidedWithCreature;
	}

	void Locomotion::SetHasCollidedWithCreature(bool hasCollided) {
		mHasCollidedWithCreature = hasCollided;
	}
	
	bool Locomotion::HasCollided() const {
		return mHasCollided;
	}

	void Locomotion::SetHasCollided(bool hasCollided) {
		mHasCollided = hasCollided;
	}

	uint32_t Locomotion::GetGoalFlags() const {
		return mGoalFlags;
	}

	uint32_t Locomotion::GetTargetId() const {
		return mTargetId;
	}

	void Locomotion::SetTargetId(uint32_t targetId) {
		mTargetId = targetId;
		mDataBits.set(LocomotionDataBits::TargetId);
	}

	float Locomotion::GetAllowedStopDistance() const {
		return mAllowedStopDistance;
	}

	float Locomotion::GetDesiredStopDistance() const {
		return mDesiredStopDistance;
	}

	void Locomotion::SetGoalPosition(const glm::vec3& position) {
		// reset data
		mTargetId = 0;
		mFacing = glm::zero<glm::vec3>();
		mTargetPosition = glm::zero<glm::vec3>();
		mExternalLinearVelocity = glm::zero<glm::vec3>();

		// set data
		mGoalFlags = 0x001;
		mGoalPosition = position;
		mAllowedStopDistance = 0;
		mDesiredStopDistance = 0;

		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateLocomotion);
	}

	void Locomotion::SetGoalPositionWithDistance(const glm::vec3& position, float distance) {
		SetGoalPosition(position);

		mAllowedStopDistance = distance;
		mDesiredStopDistance = distance;
	}

	void Locomotion::SetPartialGoalPosition(const glm::vec3& position) {
		mPartialGoalPosition = position;
	}
	
	void Locomotion::SetGoalObject(const ObjectPtr& object, float distance, bool useTargetPosition, bool unk) {
		if (!object) {
			return;
		}

		// distance = GetAllowedStoppingDistance(object) + distance;
		SetGoalPosition(object->GetPosition());

		// Internally these seem like no ops
		// mGoalFlags |= (1 & 0x40);
		// mGoalFlags |= (2 & 0x80);

		mAllowedStopDistance = distance;
		mDesiredStopDistance = distance;

		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateLocomotion);
	}

	void Locomotion::SetGoalObjectEx(const ObjectPtr& object, float distance, bool useTargetPosition) {
		if (!object) {
			return;
		}

		// reset data
		mFacing = glm::zero<glm::vec3>();
		mTargetPosition = glm::zero<glm::vec3>();
		mExternalLinearVelocity = glm::zero<glm::vec3>();

		// set data
		mGoalFlags = 0x400;
		// mGoalFlags = 1 & 0x040;
		mTargetId = object->GetId();
		mGoalPosition = object->GetPosition();
		mAllowedStopDistance = distance;
		mDesiredStopDistance = distance;

		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateLocomotion);
	}

	void Locomotion::SetGoalFlags(uint32_t flags) {
		mGoalFlags = flags;
		mDataBits.set(LocomotionDataBits::GoalFlags);
	}

	void Locomotion::SetFacing(const glm::vec3& facingPosition) {
		// reset data
		mTargetId = 0;
		mAllowedStopDistance = 0;
		mDesiredStopDistance = 0;
		mExternalLinearVelocity = glm::zero<glm::vec3>();

		// set data
		mGoalFlags = 0x002 | 0x040;
		mGoalPosition = mObject->GetPosition();
		mTargetPosition = facingPosition;
		mFacing = glm::normalize(mTargetPosition - mGoalPosition);

		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateLocomotion);
	}
	
	void Locomotion::Stop() {
		// reset data
		mTargetId = 0;
		mExternalLinearVelocity = glm::zero<glm::vec3>();
		mTargetPosition = glm::zero<glm::vec3>();
		mFacing = glm::zero<glm::vec3>();

		// set data
		mGoalFlags = 0x020;

		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateLocomotion);
	}

	void Locomotion::TurnToFaceTargetObject(const ObjectPtr& object) {
		if (!object) {
			return;
		}

		// reset data
		mTargetPosition = glm::zero<glm::vec3>();
		mExternalLinearVelocity = glm::zero<glm::vec3>();

		// set data
		mGoalFlags = 0x100 | 0x002;
		mGoalPosition = mObject->GetPosition();
		mTargetId = object->GetId();
		mFacing = glm::normalize(object->GetPosition() - mGoalPosition);

		auto radius = mObject->GetFootprintRadius();
		mAllowedStopDistance = radius;
		mDesiredStopDistance = radius;
	}
	
	void Locomotion::MoveToPointWhileFacingTarget(const glm::vec3& position, const ObjectPtr& object) {
		if (!object) {
			return;
		}

		// reset data
		mFacing = glm::zero<glm::vec3>();
		mTargetPosition = glm::zero<glm::vec3>();
		mExternalLinearVelocity = glm::zero<glm::vec3>();

		// set data
		mGoalFlags = 0x001 | 0x100;
		mGoalPosition = position;
		mTargetId = object->GetId();

		mAllowedStopDistance = 0;
		mDesiredStopDistance = 0;

		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateLocomotion);
	}
	
	void Locomotion::ApplyExternalVelocity(const glm::vec3& velocity) {
		// reset data
		mTargetId = 0;
		mFacing = glm::zero<glm::vec3>();

		// set data
		mGoalFlags = 0x008;
		mExternalLinearVelocity = velocity;

		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateLocomotion);
	}

	void Locomotion::ClearExternalVelocity() {
		// set data
		mGoalFlags = 0x020;
		mExternalLinearVelocity = glm::zero<glm::vec3>();

		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateLocomotion);
	}

	void Locomotion::ClearTargetObject() {
		// set data
		mGoalFlags &= ~0x040;
		mGoalFlags &= ~0x100;
		mTargetId = 0;

		mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateLocomotion);
	}

	void Locomotion::FaceObjectDuringMove(const ObjectPtr& object) {
		if (!object) {
			return;
		}

		mTargetId = object->GetId();
		mGoalFlags |= 0x100;
	}

	void Locomotion::SlideToPoint(const glm::vec3& position, float speed) {
		auto delta = position - mObject->GetPosition();
		auto distance = glm::sqrt(glm::dot(delta, delta));
		auto direction = delta * (static_cast<float>(1) / distance);
		Jump(direction, distance, speed, direction, 0.f, 0.f, 0.f, false);
	}

	void Locomotion::Jump(
		const glm::vec3& direction, float distance, float speed, const glm::vec3& facing,
		float minJumpHeight, float maxJumpHeight, float rangeToHitMaxJumpHeight, bool param_9
	) {
		// TODO: seems to require a bunch of NavMesh stuff, no clue about this yet.
	}

	void Locomotion::WriteTo(RakNet::BitStream& stream) const {
		using RakNet::bytes_to_bits;
		using RakNet::ReallocateStream;

		constexpr auto size = bytes_to_bits(0x290);

		auto writeOffset = ReallocateStream(stream, size);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x08));
		Write(stream, mReflectedLastUpdate);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x44));
		mProjectileParameters.WriteTo(stream);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x84));
		Write(stream, mExpectedGeoCollision);
		Write(stream, mTargetId);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x9C));
		Write(stream, mInitialDirection);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0xD8));
		Write(stream, mLobStartTime);
		Write(stream, mLobPrevSpeedModifier);
		mLobParameters.WriteTo(stream);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x138));
		Write(stream, mOffset);
		Write(stream, mGoalFlags);
		Write(stream, mGoalPosition);
		Write(stream, mPartialGoalPosition);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x178));
		Write(stream, mFacing);
		Write(stream, mExternalLinearVelocity);
		Write(stream, mExternalForce);
		Write(stream, mAllowedStopDistance);
		Write(stream, mDesiredStopDistance);

		stream.SetWriteOffset(writeOffset + bytes_to_bits(0x1AC));
		Write(stream, mTargetPosition);

		stream.SetWriteOffset(writeOffset + size);
	}

	void Locomotion::WriteReflection(RakNet::BitStream& stream) const {
		RakNet::reflection_serializer<18> reflector(stream);
		reflector.begin();
		if (mDataBits.any()) {
			if (mDataBits.test(0)) { reflector.write<0>(mLobStartTime); }
			if (mDataBits.test(1)) { reflector.write<1>(mLobPrevSpeedModifier); }
			if (mDataBits.test(2)) { reflector.write<2>(mLobParameters); }
			if (mDataBits.test(3)) { reflector.write<3>(mProjectileParameters); }
			if (mDataBits.test(4)) { reflector.write<4>(mGoalFlags); }
			if (mDataBits.test(5)) { reflector.write<5>(mGoalPosition); }
			if (mDataBits.test(6)) { reflector.write<6>(mPartialGoalPosition); }
			if (mDataBits.test(7)) { reflector.write<7>(mFacing); }
			if (mDataBits.test(8)) { reflector.write<8>(mExternalLinearVelocity); }
			if (mDataBits.test(9)) { reflector.write<9>(mExternalForce); }
			if (mDataBits.test(10)) { reflector.write<10>(mAllowedStopDistance); }
			if (mDataBits.test(11)) { reflector.write<11>(mDesiredStopDistance); }
			if (mDataBits.test(12)) { reflector.write<12>(mTargetId); }
			if (mDataBits.test(13)) { reflector.write<13>(mTargetPosition); }
			if (mDataBits.test(14)) { reflector.write<14>(mExpectedGeoCollision); }
			if (mDataBits.test(15)) { reflector.write<15>(mInitialDirection); }
			if (mDataBits.test(16)) { reflector.write<16>(mOffset); }
			if (mDataBits.test(17)) { reflector.write<17>(mReflectedLastUpdate); }
		}
		reflector.end();
	}

	bool Locomotion::CollideWithCreature(const glm::vec3& position, glm::vec3& collisionPosition) {
		const auto TestCollision = [this](const ObjectPtr& collidingObject) {
			if (collidingObject->GetAttributeValue(AttributeType::Incorporeal) <= 0 && collidingObject->GetAttributeValue(AttributeType::Intangible) == 0) {
				const auto collidingId = collidingObject->GetId();
				if (mTargetId == collidingId) {
					return true;
				}

				if (mObject->GetOwnerObject() == collidingObject) {
					return false;
				}

				const auto& noun = mObject->GetNoun();
				if (noun) {
					const auto& projectile = noun->GetProjectileData();
					if (projectile) {
						switch (projectile->GetTargetType()) {
							case TargetType::Enemies: return mObject->GetTeam() != collidingObject->GetTeam();
							case TargetType::Allies: return mObject->GetTeam() == collidingObject->GetTeam();
							case TargetType::Any: return true;
							case TargetType::None: return false;
						}
					}
				}
			}
			return false;
		};

		if (mProjectileParameters.mIgnoreCreatureCollide) {
			return false;
		}

		const auto& noun = mObject->GetNoun();
		if (!noun) {
			return false;
		}

		const auto& projectileData = noun->GetProjectileData();
		if (!projectileData) {
			return false;
		}

		const auto& creatureCollisionVolume = projectileData->GetCreatureCollisionVolume();
		if (!creatureCollisionVolume) {
			return false;
		}

		const auto& collidingObjects = mObject->GetCollidingObjectsWith(*creatureCollisionVolume, { NounType::Creature });
		for (const auto& collidingObject : collidingObjects) {
			if (TestCollision(collidingObject)) {
				return true;
			}
		}

		// Some other tests im not sure about yet.
		return false;
	}

	void Locomotion::Projectile(float value) {
		if (mReflectedCurrentUpdate != mReflectedLastUpdate) {
			SetInitialDirection(glm::normalize(mObject->GetLinearVelocity()));
			mReflectedCurrentUpdate = mReflectedLastUpdate;
		}

		if (mExternalForce != glm::zero<glm::vec3>()) {
			mObject->SetLinearVelocity(mObject->GetLinearVelocity() + mExternalForce * value);
			SetExpectedGeoCollision(glm::zero<glm::vec3>());
		}

		// reverse
		float acceleration = 1.f * value;

		glm::vec3 movementSpeed;
		if (mObject->IsImmobilized()) {
			movementSpeed = glm::zero<glm::vec3>();
		} else {
			movementSpeed = mObject->GetLinearVelocity() * acceleration;
		}

		glm::vec3 collisionPosition;
		if (CollideWithCreature(collisionPosition, collisionPosition)) {
			mHasCollidedWithCreature = true;
			// mCollisionPosition = position;
			if (!mProjectileParameters.mPiercing) {
				mObject->SetPositionSimulated(mExpectedGeoCollision);
				return;
			}
		}

		if (!mProjectileParameters.mIgnoreGroundCollide) {
			if (mExpectedGeoCollision != glm::zero<glm::vec3>()) {
				const auto& delta = mExpectedGeoCollision - movementSpeed;
				if (glm::dot(delta, delta) < glm::dot(movementSpeed, movementSpeed)) {
					mObject->SetPositionSimulated(mExpectedGeoCollision);
					mHasCollided = true;
					return;
				}
			} else {

			}
		}

		mObject->SetPositionSimulated(mObject->GetPosition() + movementSpeed);
		if (mObject->IsDirty()) {
			mObject->SetFlags(mObject->GetFlags() | Object::Flags::UpdateLocomotion);
		}

		const auto& angularVelocity = mObject->GetAngularVelocity();
		if (angularVelocity != glm::zero<glm::vec3>()) {
			// unknown "unaff_retaddr" used here aswell.
			const auto& orientation = mObject->GetOrientation();
			mObject->SetOrientation(glm::normalize(orientation + (orientation * glm::quat(0, angularVelocity * 0.5f))));
		}
	}

	void Locomotion::OrbitOwner(float value) {
		const auto& noun = mObject->GetNoun();
		if (!noun) {
			return;
		}

		const auto& orbitData = noun->GetOrbitData();
		if (!orbitData) {
			return;
		}

		const auto& ownerObject = mObject->GetOwnerObject();
		if (!ownerObject) {
			return;
		}

		if (mOffset != glm::zero<glm::vec3>()) {
			auto delta = mObject->GetPosition() - ownerObject->GetPosition();
			if (glm::dot(delta, delta) <= *reinterpret_cast<float*>(TEST_VALUE)) {
				mOffset = GetFacing();
			} else {
				mOffset = glm::normalize(delta);
			}
		}

		float speedBuff = mObject->GetAttributeValue(AttributeType::MovementSpeedBuff) + 1;
		float speed = orbitData->GetSpeed();
		float radius = std::max<float>(1, orbitData->GetRadius());

		float unk = ((speed * speedBuff * value) / radius) * 0.5f;
		float unkSin = glm::sin(unk);
		float unkCos = glm::cos(unk);

		auto orientationEuler = glm::eulerAngles(ownerObject->GetOrientation());

		glm::quat unkQuat;
		unkQuat.x = orientationEuler.x * unkSin;
		unkQuat.y = orientationEuler.y * unkSin;
		unkQuat.z = orientationEuler.z * unkSin;
		unkQuat.w = unkCos;

		mOffset *= 0;

		// mObject.SetOrientation(glm::quat(u, v));
	}

	void Locomotion::GroundRoll(float value) {
		if (mProjectileParameters.mSpeed == 0 || mReflectedCurrentUpdate != mReflectedLastUpdate) {
			const auto& velocity = mObject->GetLinearVelocity();

			mProjectileParameters.mSpeed = glm::sqrt(glm::dot(velocity, velocity));
			if (mProjectileParameters.mSpeed == 0) {
				mObject->SetLinearVelocity(glm::zero<glm::vec3>());
				mObject->SetAngularVelocity(glm::zero<glm::vec3>());
				mProjectileParameters.mSpeed = 1;
			} else {
				mInitialDirection = velocity * (1.f / mProjectileParameters.mSpeed);
			}

			mReflectedCurrentUpdate = mReflectedLastUpdate;
		}

		if (mExternalForce != glm::zero<glm::vec3>()) {
			mObject->SetLinearVelocity(mObject->GetLinearVelocity() + mExternalForce * value);
			mExpectedGeoCollision = glm::zero<glm::vec3>();
		}

		float speed = mObject->GetAttributeValue(AttributeType::MovementSpeedBuff);
		if (speed != 0) {
			speed = (speed + 1) * mProjectileParameters.mSpeed;
		} else {
			speed = mProjectileParameters.mSpeed;
		}

		// Disassembly too annoying to read from here.
	}

	bool Locomotion::JumpSimulation(float value) {
		return false;
	}
}
