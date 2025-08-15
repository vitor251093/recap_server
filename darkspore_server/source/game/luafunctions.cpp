
// Include
#include "lua.h"

#include "instance.h"
#include "objectmanager.h"
#include "serverevent.h"

#include "utils/functions.h"
#include "utils/log.h"

#include <glm/gtx/norm.hpp>
#include <glm/gtx/compatibility.hpp>

#include <algorithm>
#include <filesystem>

// Helpers
namespace {
	auto& LuaGetGame(sol::this_state L) {
		Game::Instance& game = sol::state_view(L)["Game"]["Instance"];
		return game;
	}

	auto LuaGetAbility(sol::this_state L) {
		Game::Ability* ability = sol::state_view(L)["_ABILITY"];
		return ability;
	}

	auto LuaGetPlayer(const Game::Instance& instance, sol::object& value) {
		Game::PlayerPtr result;
		if (value.valid()) {
			result = value.as<Game::PlayerPtr>();
			if (!result) {
				result = instance.GetPlayerByIndex(value.as<uint8_t>());
			}
		}
		return result;
	}

	auto LuaGetObject(const Game::ObjectManager& objectManager, sol::object& value) {
		Game::ObjectPtr result;
		if (value.valid()) {
			result = value.as<Game::ObjectPtr>();
			if (!result) {
				result = objectManager.Get(value.as<uint32_t>());
			}
		}
		return result;
	}

	auto LuaGetTrigger(const Game::ObjectManager& objectManager, sol::object& value) {
		Game::TriggerVolumePtr result;
		if (value.valid()) {
			result = value.as<Game::TriggerVolumePtr>();
			if (!result) {
				result = objectManager.GetTrigger(value.as<uint32_t>());
			}
		}
		return result;
	}

	auto LuaGetServerEvent(const Game::ObjectManager& objectManager, const sol::table& value) {
		Game::ServerEvent serverEvent;
		serverEvent.mServerEventDef = value.get_or<uint32_t>("asset", 0);
		serverEvent.mObjectId = value.get_or<uint32_t>("objectId", 0);
		serverEvent.mSimpleSwarmEffectId = value.get_or<uint32_t>("simpleSwarmEffectId", 0);

		if (sol::object eventData = value["position"]; eventData.is<glm::vec3>()) { serverEvent.mPosition = eventData.as<glm::vec3>(); }
		if (sol::object eventData = value["facing"]; eventData.is<glm::vec3>()) { serverEvent.mFacing = eventData.as<glm::vec3>(); }
		if (sol::object eventData = value["targetPoint"]; eventData.is<glm::vec3>()) { serverEvent.mTargetPoint = eventData.as<glm::vec3>(); }

		const auto& object = objectManager.Get(serverEvent.mObjectId);
		if (object) {
			serverEvent.mEffectIndex = object->AddEffect(serverEvent.mServerEventDef);
			if (serverEvent.mEffectIndex != 0xFF) {
				serverEvent.mSecondaryObjectId = value.get_or<uint32_t>("secondaryObjectId", 0);
				serverEvent.mAttackerId = value.get_or<uint32_t>("attackerId", 0);

				serverEvent.mRemove = value.get_or<bool>("remove", 0);
				serverEvent.mHardStop = value.get_or<bool>("hardStop", 0);
				serverEvent.mForceAttach = value.get_or<bool>("forceAttach", 0);
				serverEvent.mCritical = value.get_or<bool>("critical", 0);
			}
		} else {
			serverEvent.mObjectId = 0;
		}

		return serverEvent;
	}

	auto LuaGetProjectileParameters(const sol::table& value) {
		Game::ProjectileParameters parameters;

		if (sol::object eventData = value["direction"]; eventData.is<glm::vec3>()) { parameters.mDirection = eventData.as<glm::vec3>(); }

		parameters.mJinkInfo = value.get_or<uint32_t>("jinkInfo", 0);

		parameters.mSpeed = value.get_or<float>("speed", 0);
		parameters.mAcceleration = value.get_or<float>("acceleration", 0);
		parameters.mRange = value.get_or<float>("range", 0);
		parameters.mSpinRate = value.get_or<float>("spinRate", 0);
		parameters.mHomingDelay = value.get_or<float>("homingDelay", 0);
		parameters.mTurnRate = value.get_or<float>("turnRate", 0);
		parameters.mTurnAcceleration = value.get_or<float>("turnAcceleration", 0);
		parameters.mEccentricity = value.get_or<float>("eccentricity", 0);
		parameters.mCombatantSweepHeight = value.get_or<float>("combatantSweepHeight", 0);

		parameters.mProjectileFlags = value.get_or<uint8_t>("projectileFlags", 0);

		parameters.mPiercing = value.get_or<bool>("piercing", 0);
		parameters.mIgnoreGroundCollide = value.get_or<bool>("ignoreGroundCollide", 0);
		parameters.mIgnoreCreatureCollide = value.get_or<bool>("ignoreCreatureCollide", 0);

		return parameters;
	}
}

// LuaFunction
namespace LuaFunction {
	// nMathUtil
	namespace nMathUtil {
		auto TransformVector(const glm::vec3& v, const glm::quat& q) {
			return v * glm::eulerAngles(q);
		}

		auto RotateVectorByAxisAngle(const glm::vec3& v, const glm::vec3& axis, float angle) {
			return v * glm::angleAxis(angle, axis);
		}

		auto CircleIntersectsArc(const glm::vec3& position, float radius, float arcX, float arcY, float arcFacingX, float arcFacingY, float arcLength, float arcAngle) {
			const auto somefunc = [](const glm::vec2& position, const glm::vec2& arc_position, glm::vec2 other) {
				auto delta = other - arc_position;
				auto something = (position - arc_position) * delta;

				auto var = something.x + something.y;
				auto var2 = glm::length2(something);
				if (var >= 0 && var2 >= var) {
					var /= var2;
					other = delta * var + arc_position;
				}

				return glm::length(position - other);
			};

			auto arcPosition = glm::vec2(arcX, arcY);
			auto delta = glm::vec2(position) - arcPosition;
			auto value = glm::length(delta);
			if (value < (arcLength + radius)) {

				delta = (1.f / value) * delta;
				delta.x *= arcFacingX;
				delta.y *= arcFacingY;

				arcAngle *= 0.5f;
				if (arcAngle <= glm::acos(delta.x + delta.y)) {
					glm::vec2 facingLength = glm::vec2(arcFacingX, arcFacingY) * arcLength;

					float arcCos = glm::cos(arcAngle);
					float arcSin = glm::sin(arcAngle);
					if (position.z <= somefunc(position, arcPosition, {
						(arcCos * facingLength.x) - (arcSin * facingLength.y) + arcX,
						(arcCos * facingLength.y) + (arcSin * facingLength.x) + arcY
					})) {
						float arcCosNeg = glm::cos(-arcAngle);
						float arcSinNeg = glm::sin(-arcAngle);
						if (position.z <= somefunc(position, arcPosition, {
							(arcCosNeg * facingLength.x) - (arcSinNeg * facingLength.y) + arcX,
							(arcCosNeg * facingLength.y) + (arcSinNeg * facingLength.x) + arcY
						})) {
							return false;
						}
					}
				}
				return true;

			}
			return false;
		}
	}

	// nObjectManager
	auto nObjectManager_GetObject(sol::this_state L, uint32_t id) {
		auto& game = LuaGetGame(L);
		return game.GetObjectManager().Get(id);
	}

	auto nObjectManager_CreateObject(sol::this_state L, uint32_t noun, glm::vec3 position) {
		auto& game = LuaGetGame(L);

		auto object = game.GetObjectManager().Create(noun);
		if (object) {
			game.SendObjectUpdate(object); // create and update the object
			object->SetPosition(position);
		}

		return object;
	}

	auto nObjectManager_GetTrigger(sol::this_state L, uint32_t id) {
		auto& game = LuaGetGame(L);
		return game.GetObjectManager().GetTrigger(id);
	}

	auto nObjectManager_CreateTriggerVolume(sol::this_state L, glm::vec3 position, float radius) {
		auto& game = LuaGetGame(L);
		return game.GetObjectManager().CreateTrigger(position, radius);
	}

	auto nObjectManager_GetObjectsInRadius(sol::this_state L, glm::vec3 position, float radius, sol::table objectTypes) {
		auto& game = LuaGetGame(L);

		std::vector<Game::NounType> types;
		for (const auto& entry : objectTypes) {
			types.push_back(static_cast<Game::NounType>(entry.second.as<uint32_t>()));
		}

		auto objects = game.GetObjectManager().GetObjectsInRadius(Game::BoundingSphere(position, radius), types);
		auto objectCount = static_cast<int>(objects.size());

		auto result = sol::state_view(L).create_table(objectCount, 0);
		for (int i = 0; i < objectCount; ++i) {
			result[i + 1] = objects[i];
		}

		return result;
	}

	auto nObjectManager_GetObjectsInRadius_SortedByDistance(sol::this_state L, glm::vec3 position, float radius, sol::table objectTypes) {
		auto& game = LuaGetGame(L);

		std::vector<Game::NounType> types;
		for (const auto& entry : objectTypes) {
			types.push_back(static_cast<Game::NounType>(entry.second.as<uint32_t>()));
		}

		auto objects = game.GetObjectManager().GetObjectsInRadius(Game::BoundingSphere(position, radius), types);
		auto objectCount = static_cast<int>(objects.size());
		std::sort(objects.begin(), objects.end(), [&position](const auto& lhs, const auto& rhs) {
			return glm::distance(position, lhs->GetPosition()) < glm::distance(position, rhs->GetPosition());
		});

		auto result = sol::state_view(L).create_table(objectCount, 0);
		for (int i = 0; i < objectCount; ++i) {
			result[i + 1] = objects[i];
		}

		return result;
	}

	// Locomotion
	namespace Locomotion {
		auto On(sol::this_state L, sol::object objectValue, sol::variadic_args args) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object && object->HasLocomotionData()) {

			}
		}

		auto TeleportAndFace(sol::this_state L, sol::object objectValue, glm::vec3 position, glm::vec3 facingPosition) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object && object->HasLocomotionData()) {
				object->SetInputSyncStamp(object->GetInputSyncStamp() + 1);

				const auto& locomotion = object->GetLocomotionData();
				locomotion->Stop();

				locomotion->SetGoalPosition(position);
				locomotion->SetFacing(facingPosition);
				locomotion->SetGoalFlags(locomotion->GetGoalFlags() | 0x020);

				game.MoveObject(object, *locomotion);
			}
		}

		auto TeleportObject(sol::this_state L, sol::object objectValue, glm::vec3 position, sol::optional<bool> keepFacing) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object && object->HasLocomotionData()) {
				object->SetInputSyncStamp(object->GetInputSyncStamp() + 1);

				const auto& locomotion = object->GetLocomotionData();
				locomotion->Stop();

				const auto& direction = position - object->GetPosition();
				object->SetPosition(position);

				if (keepFacing.value_or(false)) {
					locomotion->SetFacing(direction + object->GetPosition());
				}
			}
		}

		auto JumpInDirection(sol::this_state L, sol::object objectValue, glm::vec3 position, sol::optional<bool> keepFacing) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object && object->HasLocomotionData()) {
				object->SetInputSyncStamp(object->GetInputSyncStamp() + 1);

				const auto& locomotion = object->GetLocomotionData();
				locomotion->Stop();

				const auto& direction = position - object->GetPosition();
				object->SetPosition(position);

				if (keepFacing.value_or(false)) {
					locomotion->SetFacing(direction + object->GetPosition());
				}
			}
		}

		auto SlideToPoint(sol::this_state L, sol::object objectValue, glm::vec3 position, float speed) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object && object->HasLocomotionData()) {
				const auto& locomotion = object->GetLocomotionData();
				locomotion->SlideToPoint(position, speed);

				game.MoveObject(object, *locomotion);
			}
		}

		auto MoveToPointExact(sol::this_state L, sol::object objectValue, glm::vec3 position, sol::optional<bool> setSomeFlag) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object && object->HasLocomotionData()) {
				const auto& locomotion = object->GetLocomotionData();
				locomotion->SetGoalPosition(position);

				if (setSomeFlag.value_or(false)) {
					locomotion->SetGoalFlags(locomotion->GetGoalFlags() | 0x800);
				}

				game.MoveObject(object, *locomotion);
			}
		}

		auto MoveToCircleEdge(sol::this_state L, sol::object objectValue, glm::vec3 position, float distance, sol::optional<bool> setSomeFlag) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object && object->HasLocomotionData()) {
				const auto& locomotion = object->GetLocomotionData();
				locomotion->SetGoalPositionWithDistance(position, distance);

				if (setSomeFlag.value_or(false)) {
					locomotion->SetGoalFlags(locomotion->GetGoalFlags() | 0x800);
				}

				game.MoveObject(object, *locomotion);
			}
		}

		auto MoveToPointWithinRange(sol::this_state L, sol::object objectValue, glm::vec3 position, float distance, sol::optional<bool> setSomeFlag) {
			auto& game = LuaGetGame(L);
			auto& lua = game.GetLua();

			auto thread = lua.GetThread(L);
			if (!thread) {
				return;
			}

			auto& objectManager = game.GetObjectManager();
			auto object = LuaGetObject(objectManager, objectValue);
			if (object && object->HasLocomotionData()) {
				const auto& locomotion = object->GetLocomotionData();
				locomotion->SetGoalPositionWithDistance(position, distance);

				if (setSomeFlag.value_or(false)) {
					locomotion->SetGoalFlags(locomotion->GetGoalFlags() | 0x800);
				}

				game.MoveObject(object, *locomotion);

				thread->set_resume_condition([&objectManager, objectId = object->GetId(), position, distance](lua_State* L, sol::variadic_results& results) {
					auto object = objectManager.Get(objectId);
					if (!object) {
						return true;
					}

					auto delta = object->GetPosition() - position;
					if ((object->GetFootprintRadius() + distance) <= glm::length(delta)) {
						return false;
					}

					return true;
				});

				lua.YieldThread(thread);
			}
		}

		auto MoveToObject(sol::this_state L, sol::object objectValue, sol::object targetValue, sol::optional<float> distance, sol::optional<bool> setSomeFlag) {
			auto& game = LuaGetGame(L);
			auto& objectManager = game.GetObjectManager();

			auto object = LuaGetObject(objectManager, objectValue);
			if (object && object->HasLocomotionData()) {
				auto target = LuaGetObject(objectManager, targetValue);
				if (!target) {
					return;
				}

				const auto& locomotion = object->GetLocomotionData();
				locomotion->SetGoalObject(target, distance.value_or(0.f) + target->GetFootprintRadius(), false, false);

				if (setSomeFlag.value_or(false)) {
					locomotion->SetGoalFlags(locomotion->GetGoalFlags() | 0x800);
				}

				game.MoveObject(object, *locomotion);
			}
		}

		auto FollowAsPet(sol::this_state L, sol::object objectValue, sol::object targetValue, sol::optional<float> distance) {
			auto& game = LuaGetGame(L);
			auto& objectManager = game.GetObjectManager();

			auto object = LuaGetObject(objectManager, objectValue);
			if (object && object->HasLocomotionData()) {
				auto target = LuaGetObject(objectManager, targetValue);
				if (!target) {
					return;
				}

				const auto& locomotion = object->GetLocomotionData();
				locomotion->SetGoalObjectEx(target, distance.value_or(0.f) + target->GetFootprintRadius(), false);

				game.MoveObject(object, *locomotion);
			}
		}

		auto ApplyExternalVelocity(sol::this_state L, sol::object objectValue, glm::vec3 velocity) {
			auto& game = LuaGetGame(L);
			auto& objectManager = game.GetObjectManager();

			auto object = LuaGetObject(objectManager, objectValue);
			if (object && object->HasLocomotionData()) {
				const auto& locomotion = object->GetLocomotionData();
				locomotion->ApplyExternalVelocity(velocity);

				game.MoveObject(object, *locomotion);
			}
		}

		auto ClearExternalVelocity(sol::this_state L, sol::object objectValue) {
			auto& game = LuaGetGame(L);
			auto& objectManager = game.GetObjectManager();

			auto object = LuaGetObject(objectManager, objectValue);
			if (object && object->HasLocomotionData()) {
				const auto& locomotion = object->GetLocomotionData();
				locomotion->ClearExternalVelocity();

				game.MoveObject(object, *locomotion);
			}
		}

		auto ClearTargetObject(sol::this_state L, sol::object objectValue) {
			auto& game = LuaGetGame(L);
			auto& objectManager = game.GetObjectManager();

			auto object = LuaGetObject(objectManager, objectValue);
			if (object && object->HasLocomotionData()) {
				const auto& locomotion = object->GetLocomotionData();
				locomotion->ClearTargetObject();

				game.MoveObject(object, *locomotion);
			}
		}

		auto FaceObjectDuringMove(sol::this_state L, sol::object objectValue, sol::object targetValue) {
			auto& game = LuaGetGame(L);
			auto& objectManager = game.GetObjectManager();

			auto object = LuaGetObject(objectManager, objectValue);
			if (object && object->HasLocomotionData()) {
				auto target = LuaGetObject(objectManager, targetValue);
				if (!target) {
					return;
				}

				const auto& locomotion = object->GetLocomotionData();
				locomotion->FaceObjectDuringMove(target);

				game.MoveObject(object, *locomotion);
			}
		}

		auto TurnToFace(sol::this_state L, sol::object objectValue, glm::vec3 position, sol::optional<bool> setSomeFlag) {
			auto& game = LuaGetGame(L);
			auto& objectManager = game.GetObjectManager();

			auto object = LuaGetObject(objectManager, objectValue);
			if (object && object->HasLocomotionData()) {
				const auto& locomotion = object->GetLocomotionData();
				locomotion->SetFacing(position);

				if (setSomeFlag.value_or(false)) {
					locomotion->SetGoalFlags(locomotion->GetGoalFlags() | 0x800);
				}
			}
		}

		auto TurnToFaceTargetObject(sol::this_state L, sol::object objectValue, sol::object targetValue) {
			auto& game = LuaGetGame(L);
			auto& objectManager = game.GetObjectManager();

			auto object = LuaGetObject(objectManager, objectValue);
			if (object && object->HasLocomotionData()) {
				auto target = LuaGetObject(objectManager, targetValue);
				if (!target) {
					return;
				}

				const auto& locomotion = object->GetLocomotionData();
				locomotion->TurnToFaceTargetObject(target);
			}
		}

		auto MoveToPointWhileFacingTarget(sol::this_state L, sol::object objectValue, glm::vec3 position, sol::object targetValue) {
			auto& game = LuaGetGame(L);
			auto& objectManager = game.GetObjectManager();

			auto object = LuaGetObject(objectManager, objectValue);
			if (object && object->HasLocomotionData()) {
				auto target = LuaGetObject(objectManager, targetValue);
				if (!target) {
					return;
				}

				const auto& locomotion = object->GetLocomotionData();
				locomotion->MoveToPointWhileFacingTarget(position, target);

				game.MoveObject(object, *locomotion);
			}
		}

		auto Stop(sol::this_state L, sol::object objectValue) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object && object->HasLocomotionData()) {
				const auto& locomotion = object->GetLocomotionData();
				locomotion->Stop();

				game.MoveObject(object, *locomotion);
			}
		}

		auto GetClosestPosition(sol::this_state L, glm::vec3 position) {
			// TODO: add Locomotion::GetClosestPosition (not sure how the fuck I'm gonna do that without getting navmesh data)
			return position;
		}

		auto GetClosestPositionFromPoint(sol::this_state L, glm::vec3 position) {
			// TODO: add Locomotion::GetClosestPositionFromPoint (not sure how the fuck I'm gonna do that without getting navmesh data)
			return position;
		}

		auto GetTargetPosition(sol::this_state L, sol::object objectValue) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object && object->HasLocomotionData()) {
				const auto& locomotion = object->GetLocomotionData();
				return locomotion->GetTargetPosition();
			}

			return glm::zero<glm::vec3>();
		}

		auto SetTargetPosition(sol::this_state L, sol::object objectValue, glm::vec3 position) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object && object->HasLocomotionData()) {
				const auto& locomotion = object->GetLocomotionData();
				locomotion->SetTargetPosition(position);
			}
		}
	}

	// Object
	namespace Object {
		auto IsValid(sol::this_state L, sol::object objectValue) {
			// object:IsValid() could be useful later.
			if (objectValue.is<Game::ObjectPtr>()) {
				return objectValue.as<Game::ObjectPtr>() != nullptr;
			}
			return false;
		}

		auto GetName(sol::this_state L, sol::object objectValue) {
			std::string result;

			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object) {
				const auto& noun = object->GetNoun();
				if (noun) {
					result = noun->GetName();
				}
			}

			return result;
		}

		auto GetPrivateTable(sol::this_state L, sol::object objectValue) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object) {
				return game.GetLua().CreatePrivateTable(object->GetId());
			}
			return sol::table(sol::nil);
		}

		auto GetFacing(sol::this_state L, sol::object objectValue) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object && object->HasLocomotionData()) {
				return object->GetLocomotionData()->GetFacing();
			}
			return glm::zero<glm::vec3>();
		}

		auto GetFootprintRadius(sol::this_state L, sol::object objectValue) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object) {
				return object->GetFootprintRadius();
			}
			return 0.f;
		}

		auto Move(sol::this_state L, sol::object objectValue, glm::vec3 position, bool teleport) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object && object->HasLocomotionData()) {
				const auto& locomotionData = object->GetLocomotionData();
				locomotionData->SetGoalPosition(position);
				if (teleport) {
					locomotionData->SetGoalFlags(locomotionData->GetGoalFlags() | 0x020);
				}
				game.MoveObject(object, *locomotionData);
			}
		}

		auto SetAnimationState(sol::this_state L, sol::object objectValue, uint32_t animationState, sol::optional<bool> overlay, sol::optional<float> scale) {
			if (animationState == 0) {
				return;
			}

			auto& game = LuaGetGame(L);
			game.SendAnimationState(LuaGetObject(game.GetObjectManager(), objectValue), animationState, overlay.value_or(false), scale.value_or(1.f));
		}

		auto SetAnimationStateToDeath(sol::this_state L, sol::object objectValue) {
			// TODO: 
		}

		auto SetAnimationStateToAggro(sol::this_state L, sol::object objectValue, sol::optional<bool> subsequent) {
			float duration = 0;

			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (!object) {
				return duration;
			}

			const auto& noun = object->GetNoun();
			if (!noun) {
				return duration;
			}

			const auto& animations = noun->GetCharacterAnimation();
			if (!animations) {
				return duration;
			}

			uint32_t state;
			if (subsequent.value_or(false)) {
				std::tie(state, duration) = animations->GetAnimationData(Game::CharacterAnimationType::SubsequentAggro);
			} else {
				std::tie(state, duration) = animations->GetAnimationData(Game::CharacterAnimationType::Aggro);
			}

			game.SendAnimationState(object, state);
			return duration;
		}

		auto SetGraphicsState(sol::this_state L, sol::object objectValue, uint32_t graphicsState) {
			if (graphicsState == 0) {
				return;
			}

			auto& game = LuaGetGame(L);
			game.SendObjectGfxState(LuaGetObject(game.GetObjectManager(), objectValue), graphicsState);
		}

		auto GetAttributeSnapshot(sol::this_state L, sol::object objectValue) {
			const auto& game = LuaGetGame(L);
			const auto& object = LuaGetObject(game.GetObjectManager(), objectValue);

			Game::AttributesPtr attributes;
			if (object && object->HasAttributeData()) {
				attributes = std::make_shared<Game::Attributes>(*object->GetAttributeData());
				attributes->SetOwnerObject(object);
			}

			return attributes;
		}

		auto SetAttributeSnapshot(sol::this_state L, sol::object objectValue, sol::object attributeSnapshotValue) {
			auto& game = LuaGetGame(L);

			const auto& object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object) {
				// attributes = std::make_shared<Game::Attributes>(*object->GetAttributeData());
				// attributes->SetOwnerObject(object);
			}
		}

		auto GetWeaponDamage(sol::this_state L, sol::object objectValue) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);

			sol::table damageRange = sol::state_view(L).create_table(2);
			if (object && object->HasAttributeData()) {
				const auto& weaponDamage = object->GetAttributeData()->GetWeaponDamage();
				damageRange[1] = std::get<0>(weaponDamage);
				damageRange[2] = std::get<1>(weaponDamage);
			}

			return damageRange;
		}

		auto IsCombatant(sol::this_state L, sol::object objectValue) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object) {
				return object->HasCombatantData();
			}
			return false;
		}

		auto AddCooldown(sol::this_state L, sol::object objectValue, uint32_t abilityId, uint32_t milliseconds) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object) {
				const auto& [end, duration] = object->AddCooldown(abilityId, milliseconds);
				game.SendCooldownUpdate(object, abilityId, end - duration, duration);
			}
		}

		auto RemoveCooldown(sol::this_state L, sol::object objectValue, uint32_t abilityId, uint32_t milliseconds) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object) {
				const auto& [end, duration] = object->RemoveCooldown(abilityId, milliseconds);
				game.SendCooldownUpdate(object, abilityId, end - duration, duration);
			}
		}

		auto ScaleCooldown(sol::this_state L, sol::object objectValue, uint32_t abilityId, float scale) {
			//
		}

		auto TakeDamage(sol::this_state L,
			sol::object objectValue,
			sol::object attackerValue,
			sol::object attributeSnapshotValue,
			sol::table damageRange,
			Game::DamageType damageType,
			Game::DamageSource damageSource,
			float damageCoefficient,
			Game::Descriptors descriptors,
			sol::optional<float> damageMultiplier,
			sol::optional<glm::vec3> direction
		) {
			auto& game = LuaGetGame(L);
			const auto& objectManager = game.GetObjectManager();

			auto object = LuaGetObject(objectManager, objectValue);
			if (object) {
				auto attacker = LuaGetObject(objectManager, attackerValue);

				Game::AttributesPtr attributes;
				if (attributeSnapshotValue.is<Game::AttributesPtr>()) {
					attributes = attributeSnapshotValue.as<Game::AttributesPtr>();
				}

				Game::CombatEvent combatEvent;
				combatEvent.mTargetId = object->GetId();
				combatEvent.mDirection = direction.value_or(glm::zero<glm::vec3>());

				const auto& result = object->TakeDamage(
					attributes,
					std::make_tuple(damageRange.raw_get_or(1, 0.f), damageRange.raw_get_or(2, 0.f)),
					damageType,
					damageSource,
					damageCoefficient,
					descriptors,
					damageMultiplier.value_or(1.0f),
					combatEvent.mDirection
				);

				combatEvent.mDeltaHealth = std::get<1>(result);
				combatEvent.mIntegerHpChange = static_cast<int32_t>(combatEvent.mDeltaHealth);

				if (std::get<2>(result)) {
					combatEvent.mFlags = Game::CombatEventFlags::Critical;
				}

				game.SendCombatEvent(combatEvent);
				return result;
			}

			return std::make_tuple(false, 0.f, false);
		}

		auto Heal(sol::this_state L,
			sol::object objectValue,
			sol::object attackerValue,
			sol::object attributeSnapshotValue,
			sol::table healRange,
			float healCoefficient,
			sol::optional<Game::Descriptors> descriptors,
			sol::optional<bool> critical,
			sol::optional<bool> canResurrect
		) {
			auto& game = LuaGetGame(L);
			const auto& objectManager = game.GetObjectManager();

			auto object = LuaGetObject(objectManager, objectValue);
			if (object) {
				auto attacker = LuaGetObject(objectManager, attackerValue);

				Game::AttributesPtr attributes;
				if (attributeSnapshotValue.is<Game::AttributesPtr>()) {
					attributes = attributeSnapshotValue.as<Game::AttributesPtr>();
				}

				Game::CombatEvent combatEvent;
				combatEvent.mTargetId = object->GetId();

				const auto& result = object->Heal(
					attributes,
					std::make_tuple(healRange.raw_get_or(1, 0.f), healRange.raw_get_or(2, 0.f)),
					healCoefficient,
					descriptors.value_or(Game::Descriptors::IsBasic),
					critical.value_or(false),
					false
				);

				combatEvent.mDeltaHealth = std::get<0>(result);
				combatEvent.mIntegerHpChange = static_cast<int32_t>(combatEvent.mDeltaHealth);

				if (std::get<1>(result)) {
					combatEvent.mFlags = Game::CombatEventFlags::Critical;
				}

				game.SendCombatEvent(combatEvent);
				return result;
			}

			return std::make_tuple(0.f, false);
		}

		auto AddEffect(sol::this_state L, sol::object objectValue, sol::object serverEventDef, sol::optional<sol::object> secondaryObjectValue, sol::optional<glm::vec3> targetPointValue) {
			auto& game = LuaGetGame(L);
			const auto& objectManager = game.GetObjectManager();

			auto object = LuaGetObject(objectManager, objectValue);
			if (object) {
				uint32_t effect;
				if (serverEventDef.is<uint32_t>()) {
					effect = serverEventDef.as<uint32_t>();
				} else if (serverEventDef.is<std::string>()) {
					effect = utils::hash_id(serverEventDef.as<std::string>());
				} else {
					effect = 0;
				}

				auto index = object->AddEffect(effect);
				if (index == 0) {
					return index;
				}

				Game::ServerEvent serverEvent;
				serverEvent.mServerEventDef = effect;
				serverEvent.mEffectIndex = index;
				serverEvent.mForceAttach = true;
				serverEvent.mObjectId = object->GetId();

				if (targetPointValue.has_value()) {
					serverEvent.mTargetPoint = targetPointValue.value();
				} else {
					serverEvent.mTargetPoint = object->GetPosition();
				}

				// serverEvent.SetIgnoredPlayerBits(ignoredPlayerBits);
				if (secondaryObjectValue) {
					auto secondaryObject = LuaGetObject(objectManager, *secondaryObjectValue);
					if (secondaryObject) {
						serverEvent.mSecondaryObjectId = secondaryObject->GetId();
					}
				}

				game.SendServerEvent(serverEvent);
				return serverEvent.mEffectIndex;
			}

			return static_cast<uint8_t>(0);
		}

		auto RemoveEffect(sol::this_state L, sol::object objectValue, sol::object effectValue, sol::optional<bool> hardStop) {
			uint32_t effect;
			if (effectValue.is<uint32_t>()) {
				effect = effectValue.as<uint32_t>();
			} else if (effectValue.is<std::string>()) {
				effect = utils::hash_id(effectValue.as<std::string>());
			} else {
				return;
			}

			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object) {
				auto index = object->RemoveEffect(effect);
				if (index != 0) {
					Game::ServerEvent serverEvent;
					serverEvent.mObjectId = object->GetId();
					serverEvent.mEffectIndex = index;
					serverEvent.mRemove = true;
					serverEvent.mHardStop = hardStop.value_or(true);
					// serverEvent.SetIgnoredPlayerBits(ignoredPlayerBits);

					game.SendServerEvent(serverEvent);
				}
			}
		}

		auto RemoveEffectIndex(sol::this_state L, sol::object objectValue, uint8_t index, sol::optional<bool> hardStop) {
			if (index == 0) {
				return;
			}

			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object) {
				auto removed = object->RemoveEffectByIndex(index);
				if (removed) {
					Game::ServerEvent serverEvent;
					serverEvent.mObjectId = object->GetId();
					serverEvent.mEffectIndex = index;
					serverEvent.mRemove = true;
					serverEvent.mHardStop = hardStop.value_or(true);
					// serverEvent.SetIgnoredPlayerBits(ignoredPlayerBits);

					game.SendServerEvent(serverEvent);
				}
			}
		}

		auto UseAbility(sol::this_state L, sol::object objectValue, uint32_t abilityId, sol::object targetObjectValue, glm::vec3 targetPosition) {
			auto& game = LuaGetGame(L);

			const auto& ability = game.GetLua().GetAbility(abilityId);
			if (ability) {
				const auto& objectManager = game.GetObjectManager();

				auto object = LuaGetObject(objectManager, objectValue);
				if (object) {
					auto targetObject = LuaGetObject(objectManager, targetObjectValue);
					ability->Tick(object, targetObject, targetPosition, 1);
				}
			}
		}

		auto DropLoot(sol::this_state L, sol::object objectValue, sol::object targetObjectValue, Game::DropType dropType) {
			auto& game = LuaGetGame(L);
			const auto& objectManager = game.GetObjectManager();

			auto object = LuaGetObject(objectManager, objectValue);
			auto targetObject = LuaGetObject(objectManager, targetObjectValue);
			if (object && targetObject) {
				game.DropLoot(object, targetObject, dropType);
			}
		}

		auto GetSharedAbilityOffset(sol::this_state L, sol::object objectValue) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);

			glm::vec3 offset {};
			if (object) {
				const auto& noun = object->GetNoun();
				if (noun) {
					const auto& playerClassData = noun->GetPlayerClassData();
					if (playerClassData) {
						offset = playerClassData->GetSharedAbilityOffset();
					}
				}
			}

			return offset;
		}

		auto IncrementNumTimesUsed(sol::this_state L, sol::object objectValue) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);

			if (object) {
				const auto& interactableData = object->GetInteractableData();
				if (interactableData) {
					interactableData->SetTimesUsed(interactableData->GetTimesUsed() + 1);
				}
			}
		}

		auto GetTeleporterDestination(sol::this_state L, sol::object objectValue) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);

			glm::vec3 destination {};
			if (object) {
				const auto& marker = game.GetMarker(object->GetMarkerId());
				if (marker) {
					const auto& teleporterData = marker->GetTeleporterData();
					if (teleporterData) {
						const auto& destinationMarker = game.GetMarker(teleporterData->GetDestinationId());
						if (destinationMarker) {
							destination = destinationMarker->GetPosition();
						}
					}
				}
			}

			return destination;
		}

		auto IsStealthed(sol::this_state L, sol::object objectValue) {
			auto& game = LuaGetGame(L);
			auto object = LuaGetObject(game.GetObjectManager(), objectValue);
			if (object) {
				return object->GetStealthType() != Game::StealthType::None;
			}
			return false;
		}
	}

	// nPlayer
	auto nPlayerPickupCrystal() {

	}
}

// Game
namespace Game {
	// LuaBase
	void LuaBase::RegisterFunctions() {
		// os
		auto osTable = mState.create_named_table("os");
		osTable["mtime"] = &utils::get_milliseconds;

		// glm
		{
			mState.new_usertype<glm::vec3>("vec3",
				sol::constructors<glm::vec3(), glm::vec3(float, float, float)>(),

				sol::meta_function::to_string, [](const glm::vec3& v) { return std::format("vec3<{}, {}, {}>", v.x, v.y, v.z); },
				sol::meta_function::addition, [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 + v2; },
				sol::meta_function::subtraction, [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 - v2; },
				sol::meta_function::multiplication, sol::overload(
					[](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 * v2; },
					[](const glm::vec3& v1, float f) -> glm::vec3 { return v1 * f; },
					[](float f, const glm::vec3& v1) -> glm::vec3 { return f * v1; }
				),
				sol::meta_function::division, sol::overload(
					[](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 / v2; },
					[](const glm::vec3& v1, float f) -> glm::vec3 { return v1 / f; },
					[](float f, const glm::vec3& v1) -> glm::vec3 { return f / v1; }
				),
				
				"x", &glm::vec3::x,
				"y", &glm::vec3::y,
				"z", &glm::vec3::z,
					
				"dot", [](const glm::vec3& v1, const glm::vec3& v2) -> float { return glm::dot(v1, v2); },
				"len", [](const glm::vec3& v) -> float { return glm::length(v); },
				"sqrlen", [](const glm::vec3& v) -> float { return glm::length2(v); },
				"distance", [](const glm::vec3& v1, const glm::vec3& v2) -> float { return glm::distance(v1, v2); },
				"distance2", [](const glm::vec3& v1, const glm::vec3& v2) -> float { return glm::distance2(v1, v2); },
				"normalize", [](const glm::vec3& v) -> glm::vec3 { return glm::normalize(v); },
				"cross", [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return glm::cross(v1, v2); },
				"direction", [](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return glm::normalize(v1 - v2); },
				"lerp", [](const glm::vec3& v1, const glm::vec3& v2, float a) -> glm::vec3 { return glm::lerp(v1, v2, a); },
				"scale", [](const glm::vec3& v, float scale) -> glm::vec3 { return v * scale; }
			);

			mState.new_usertype<glm::quat>("quat",
				sol::constructors<glm::quat(), glm::quat(float, float, float, float)>(),

				sol::meta_function::to_string, [](const glm::quat& q) { return std::format("quat<{}, {}, {}, {}>", q.x, q.y, q.z, q.w); },

				"x", &glm::quat::x,
				"y", &glm::quat::y,
				"z", &glm::quat::z,
				"w", &glm::quat::w
			);
		}

		RegisterMath();
		RegisterUtil();
		RegisterClient();
		RegisterAbility();
		RegisterPhysics();
		RegisterGameObject();
		RegisterAbilityAnimationSelection();
		RegisterDebug();
		RegisterNPCType();
		RegisterTuning();
		RegisterPlayer();
		RegisterLocomotion();
	}

	void LuaBase::RegisterMath() {
		auto mathUtil = mState.create_named_table("nMathUtil");
		mathUtil["TransformVector"] = &LuaFunction::nMathUtil::TransformVector;
		mathUtil["RotateVectorByAxisAngle"] = &LuaFunction::nMathUtil::RotateVectorByAxisAngle;
		mathUtil["CircleIntersectsArc"] = &LuaFunction::nMathUtil::CircleIntersectsArc;
	}

	void LuaBase::RegisterUtil() {
		auto util = mState.create_named_table("nUtil");

		util["SPID"] = [](std::string value) {
			return utils::hash_id(value);
		};

		util["ToGUID"] = [](std::string value) {
			return utils::to_number<uint64_t>(value, 0);
		};

		util["GetAsset"] = [this](std::string value) {
			return mAssets[value];
		};
	}

	void LuaBase::RegisterClient() {
		auto client = mState.create_named_table("nClient");
		
	}

	void LuaBase::RegisterAbility() {
		auto ability = mState.create_named_table("nAbility");
		
	}

	void LuaBase::RegisterPhysics() {
		auto physics = mState.create_named_table("nPhysics");
		
	}

	void LuaBase::RegisterGameObject() {
		auto gameObject = mState.create_named_table("nGameObject");
		
	}

	void LuaBase::RegisterAbilityAnimationSelection() {
		auto abilityAnimationSelection = mState.create_named_table("nAbilityAnimationSelection");
		
	}

	void LuaBase::RegisterDebug() {
		auto debug = mState.create_named_table("nDebug");
		
	}

	void LuaBase::RegisterNPCType() {
		auto npcType = mState.create_named_table("nNPCType");
		
	}

	void LuaBase::RegisterTuning() {
		auto tuning = mState.create_named_table("nTuning");
		
	}

	void LuaBase::RegisterPlayer() {
		auto player = mState.create_named_table("nPlayer");
		
	}

	void LuaBase::RegisterLocomotion() {
		auto locomotion = mState.create_named_table("nLocomotion");
		
	}

	void LuaBase::LoadAssetsCatalog() {
		std::string filepath = "data/assets_catalog.xml";

		pugi::xml_document document;
		if (!document.load_file(filepath.c_str())) {
			return;
		}

		if (auto catalog = document.child("catalog")) {
			for (const auto& entry : catalog.child("entry")) {
				auto asset = utils::xml_get_text_node(entry, "asset");
				auto sourceFilePath = utils::xml_get_text_node(entry, "source_file");
				std::vector<std::string> sourceFilePathComps = utils::explode_string(sourceFilePath, ".");

				if (sourceFilePathComps.size() == 2) {
					std::string folderName = utils::string_tolower(sourceFilePathComps[1]);
					std::string sourceFileFullPath = "data/serverdata/" + folderName + "/" + sourceFilePath + ".xml";
					if (std::filesystem::exists(sourceFileFullPath)) {
						std::string sourceFile = utils::get_file_text(sourceFileFullPath);
						mAssets.insert(std::make_pair(asset, sourceFile));
					}
					else
					{
						std::cout << "Asset " << sourceFilePath << " not found inside serverdata folder" << std::endl;
					}
				}
			}
		}
	}

	// Lua
	void Lua::RegisterEnums() {
		// Attribute
		mState.new_enum<AttributeType>("Attribute", {
			{ "Strength", AttributeType::Strength },
			{ "Dexterity", AttributeType::Dexterity },
			{ "Mind", AttributeType::Mind },
			{ "MaxHealthIncrease", AttributeType::MaxHealthIncrease },
			{ "MaxHealth", AttributeType::MaxHealth },
			{ "MaxMana", AttributeType::MaxMana },
			{ "DamageReduction", AttributeType::DamageReduction },
			{ "PhysicalDefense", AttributeType::PhysicalDefense },
			{ "PhysicalDamageReduction", AttributeType::PhysicalDamageReduction },
			{ "EnergyDefense", AttributeType::EnergyDefense },
			{ "CriticalRating", AttributeType::CriticalRating },
			{ "NonCombatSpeed", AttributeType::NonCombatSpeed },
			{ "CombatSpeed", AttributeType::CombatSpeed },
			{ "DamageBuff", AttributeType::DamageBuff },
			{ "Silence", AttributeType::Silence },
			{ "Immobilized", AttributeType::Immobilized },
			{ "DefenseBoostBasicDamage", AttributeType::DefenseBoostBasicDamage },
			{ "PhysicalDamageIncrease", AttributeType::PhysicalDamageIncrease },
			{ "PhysicalDamageIncreaseFlat", AttributeType::PhysicalDamageIncreaseFlat },
			{ "AutoCrit", AttributeType::AutoCrit },
			{ "BehindDirectDamageIncrease", AttributeType::BehindDirectDamageIncrease },
			{ "BehindOrSideDirectDamageIncrease", AttributeType::BehindOrSideDirectDamageIncrease },
			{ "CriticalDamageIncrease", AttributeType::CriticalDamageIncrease },
			{ "AttackSpeedScale", AttributeType::AttackSpeedScale },
			{ "CooldownScale", AttributeType::CooldownScale },
			{ "Frozen", AttributeType::Frozen },
			{ "ProjectileSpeedIncrease", AttributeType::ProjectileSpeedIncrease },
			{ "AoEResistance", AttributeType::AoEResistance },
			{ "EnergyDamageBuff", AttributeType::EnergyDamageBuff },
			{ "Intangible", AttributeType::Intangible },
			{ "HealingReduction", AttributeType::HealingReduction },
			{ "EnergyDamageIncrease", AttributeType::EnergyDamageIncrease },
			{ "EnergyDamageIncreaseFlat", AttributeType::EnergyDamageIncreaseFlat },
			{ "Immune", AttributeType::Immune },
			{ "StealthDetection", AttributeType::StealthDetection },
			{ "LifeSteal", AttributeType::LifeSteal },
			{ "RejectModifier", AttributeType::RejectModifier },
			{ "AoEDamage", AttributeType::AoEDamage },
			{ "TechnologyTypeDamage", AttributeType::TechnologyTypeDamage },
			{ "SpacetimeTypeDamage", AttributeType::SpacetimeTypeDamage },
			{ "LifeTypeDamage", AttributeType::LifeTypeDamage },
			{ "ElementsTypeDamage", AttributeType::ElementsTypeDamage },
			{ "SupernaturalTypeDamage", AttributeType::SupernaturalTypeDamage },
			{ "TechnologyTypeResistance", AttributeType::TechnologyTypeResistance },
			{ "SpacetimeTypeResistance", AttributeType::SpacetimeTypeResistance },
			{ "LifeTypeResistance", AttributeType::LifeTypeResistance },
			{ "ElementsTypeResistance", AttributeType::ElementsTypeResistance },
			{ "SupernaturalTypeResistance", AttributeType::SupernaturalTypeResistance },
			{ "MovementSpeedBuff", AttributeType::MovementSpeedBuff },
			{ "ImmuneToDebuffs", AttributeType::ImmuneToDebuffs },
			{ "BuffDuration", AttributeType::BuffDuration },
			{ "DebuffDuration", AttributeType::DebuffDuration },
			{ "ManaSteal", AttributeType::ManaSteal },
			{ "DebuffDurationIncrease", AttributeType::DebuffDurationIncrease },
			{ "EnergyDamageReduction", AttributeType::EnergyDamageReduction },
			{ "Incorporeal", AttributeType::Incorporeal },
			{ "DoTDamageIncrease", AttributeType::DoTDamageIncrease },
			{ "MindControlled", AttributeType::MindControlled },
			{ "SwapDisabled", AttributeType::SwapDisabled },
			{ "ImmuneToRandomTeleport", AttributeType::ImmuneToRandomTeleport },
			{ "ImmuneToBanish", AttributeType::ImmuneToBanish },
			{ "ImmuneToKnockback", AttributeType::ImmuneToKnockback },
			{ "AoeRadius", AttributeType::AoeRadius },
			{ "PetDamage", AttributeType::PetDamage },
			{ "PetHealth", AttributeType::PetHealth },
			{ "CrystalFind", AttributeType::CrystalFind },
			{ "DNADropped", AttributeType::DNADropped },
			{ "RangeIncrease", AttributeType::RangeIncrease },
			{ "OrbEffectiveness", AttributeType::OrbEffectiveness },
			{ "OverdriveBuildup", AttributeType::OverdriveBuildup },
			{ "OverdriveDuration", AttributeType::OverdriveDuration },
			{ "LootFind", AttributeType::LootFind },
			{ "Surefooted", AttributeType::Surefooted },
			{ "ImmuneToStunned", AttributeType::ImmuneToStunned },
			{ "ImmuneToSleep", AttributeType::ImmuneToSleep },
			{ "ImmuneToTerrified", AttributeType::ImmuneToTerrified },
			{ "ImmuneToSilence", AttributeType::ImmuneToSilence },
			{ "ImmuneToCursed", AttributeType::ImmuneToCursed },
			{ "ImmuneToPoisonOrDisease", AttributeType::ImmuneToPoisonOrDisease },
			{ "ImmuneToBurning", AttributeType::ImmuneToBurning },
			{ "ImmuneToRooted", AttributeType::ImmuneToRooted },
			{ "ImmuneToSlow", AttributeType::ImmuneToSlow },
			{ "ImmuneToPull", AttributeType::ImmuneToPull },
			{ "DoTDamageDoneIncrease", AttributeType::DoTDamageDoneIncrease },
			{ "AggroIncrease", AttributeType::AggroIncrease },
			{ "AggroDecrease", AttributeType::AggroDecrease },
			{ "PhysicalDamageDoneIncrease", AttributeType::PhysicalDamageDoneIncrease },
			{ "PhysicalDamageDoneByAbilityIncrease", AttributeType::PhysicalDamageDoneByAbilityIncrease },
			{ "EnergyDamageDoneIncrease", AttributeType::EnergyDamageDoneIncrease },
			{ "EnergyDamageDoneByAbilityIncrease", AttributeType::EnergyDamageDoneByAbilityIncrease },
			{ "ChannelTimeDecrease", AttributeType::ChannelTimeDecrease },
			{ "CrowdControlDurationDecrease", AttributeType::CrowdControlDurationDecrease },
			{ "DoTDurationDecrease", AttributeType::DoTDurationDecrease },
			{ "AoEDurationIncrease", AttributeType::AoEDurationIncrease },
			{ "HealIncrease", AttributeType::HealIncrease },
			{ "OnLockdown", AttributeType::OnLockdown },
			{ "HoTDoneIncrease", AttributeType::HoTDoneIncrease },
			{ "ProjectileDamageIncrease", AttributeType::ProjectileDamageIncrease },
			{ "DeployBonusInvincibilityTime", AttributeType::DeployBonusInvincibilityTime },
			{ "PhysicalDamageDecreaseFlat", AttributeType::PhysicalDamageDecreaseFlat },
			{ "EnergyDamageDecreaseFlat", AttributeType::EnergyDamageDecreaseFlat },
			{ "MinWeaponDamage", AttributeType::MinWeaponDamage },
			{ "MaxWeaponDamage", AttributeType::MaxWeaponDamage },
			{ "MinWeaponDamagePercent", AttributeType::MinWeaponDamagePercent },
			{ "MaxWeaponDamagePercent", AttributeType::MaxWeaponDamagePercent },
			{ "DirectAttackDamage", AttributeType::DirectAttackDamage },
			{ "DirectAttackDamagePercent", AttributeType::DirectAttackDamagePercent },
			{ "GetHitAnimDisabled", AttributeType::GetHitAnimDisabled },
			{ "XPBoost", AttributeType::XPBoost },
			{ "InvisibleToSecurityTeleporters", AttributeType::InvisibleToSecurityTeleporters },
			{ "BodyScale", AttributeType::BodyScale }
		});

		// NounType
		mState.new_enum<NounType>("NounType", {
			{ "None", NounType::None },
			{ "Creature", NounType::Creature },
			{ "Vehicle", NounType::Vehicle },
			{ "Obstacle", NounType::Obstacle },
			{ "SpawnPoint", NounType::SpawnPoint },
			{ "PathPoint", NounType::PathPoint },
			{ "Trigger", NounType::Trigger },
			{ "PointLight", NounType::PointLight },
			{ "SpotLight", NounType::SpotLight },
			{ "LineLight", NounType::LineLight },
			{ "ParallelLight", NounType::ParallelLight },
			{ "HemisphereLight", NounType::HemisphereLight },
			{ "Animator", NounType::Animator },
			{ "Animated", NounType::Animated },
			{ "GraphicsControl", NounType::GraphicsControl },
			{ "Material", NounType::Material },
			{ "Flora", NounType::Flora },
			{ "LevelshopObject", NounType::LevelshopObject },
			{ "Terrain", NounType::Terrain },
			{ "Weapon", NounType::Weapon },
			{ "Building", NounType::Building },
			{ "Handle", NounType::Handle },
			{ "HealthOrb", NounType::HealthOrb },
			{ "ManaOrb", NounType::ManaOrb },
			{ "ResurrectOrb", NounType::ResurrectOrb },
			{ "Movie", NounType::Movie },
			{ "Loot", NounType::Loot },
			{ "PlacableEffect", NounType::PlacableEffect },
			{ "LuaJob", NounType::LuaJob },
			{ "AbilityObject", NounType::AbilityObject },
			{ "LevelExitPoint", NounType::LevelExitPoint },
			{ "Decal", NounType::Decal },
			{ "Water", NounType::Water },
			{ "Grass", NounType::Grass },
			{ "Door", NounType::Door },
			{ "Crystal", NounType::Crystal },
			{ "Interactable", NounType::Interactable },
			{ "Projectile", NounType::Projectile },
			{ "DestructibleOrnament", NounType::DestructibleOrnament },
			{ "MapCamera", NounType::MapCamera },
			{ "Occluder", NounType::Occluder },
			{ "SplineCamera", NounType::SplineCamera },
			{ "SplineCameraNode", NounType::SplineCameraNode },
			{ "BossPortal", NounType::BossPortal }
		});

		// ClientEventID
		mState.new_enum<ClientEventID>("ClientEventID", {
			{ "AbilityRequiresTarget", ClientEventID::AbilityRequiresTarget },
			{ "AbilityNotReady", ClientEventID::AbilityNotReady },
			{ "SquadAbilityUnavailable", ClientEventID::SquadAbilityUnavailable },
			{ "OverdriveNotCharged", ClientEventID::OverdriveNotCharged },
			{ "OverdriveReady", ClientEventID::OverdriveReady },
			{ "PlayerReady", ClientEventID::PlayerReady },
			{ "PlayerCashOut", ClientEventID::PlayerCashOut },
			{ "PlayerDeath", ClientEventID::PlayerDeath },
			{ "PlayerFreed", ClientEventID::PlayerFreed },
			{ "PlayerLeftGame", ClientEventID::PlayerLeftGame },
			{ "PlayerTrapped", ClientEventID::PlayerTrapped },
			{ "PlayerUnlockedSecondCreature", ClientEventID::PlayerUnlockedSecondCreature },
			{ "PlayerEnteredTunnel", ClientEventID::PlayerEnteredTunnel },
			{ "PlayerExitedTunnel", ClientEventID::PlayerExitedTunnel },
			{ "GameOver", ClientEventID::GameOver },
			{ "LootRoll", ClientEventID::LootRoll },
			{ "LootPickup", ClientEventID::LootPickup },
			{ "LootPlayerDrop", ClientEventID::LootPlayerDrop },
			{ "CatalystPickup", ClientEventID::CatalystPickup },
			{ "TeleportersDeactivated", ClientEventID::TeleportersDeactivated },
			{ "SwitchUnavailable", ClientEventID::SwitchUnavailable },
			{ "InvalidTargetArea", ClientEventID::InvalidTargetArea },
			{ "CannotSwitchHeroPerished", ClientEventID::CannotSwitchHeroPerished },
			{ "WarningFinalHero", ClientEventID::WarningFinalHero },
			{ "SwitchOnCooldown", ClientEventID::SwitchOnCooldown },
			{ "AllyReconnected", ClientEventID::AllyReconnected },
			{ "AllyDisconnected", ClientEventID::AllyDisconnected },
			{ "NotEnoughMana", ClientEventID::NotEnoughMana },
			{ "HealthLow", ClientEventID::HealthLow },
			{ "ManaLow", ClientEventID::ManaLow },
			{ "HordeIncoming", ClientEventID::HordeIncoming },
			{ "HordeDefeated", ClientEventID::HordeDefeated }
		});

		// StealthType
		mState.new_enum<StealthType>("StealthType", {
			{ "None", StealthType::None },
			{ "Technology", StealthType::Technology },
			{ "Supernatural", StealthType::Supernatural },
			{ "FullyInvisible", StealthType::FullyInvisible }
		});

		// DamageSource
		mState.new_enum<DamageSource>("DamageSource", {
			{ "Physical", DamageSource::Physical },
			{ "Energy", DamageSource::Energy }
		});

		// DamageType
		mState.new_enum<DamageType>("DamageType", {
			{ "Technology", DamageType::Technology },
			{ "Spacetime", DamageType::Spacetime },
			{ "Life", DamageType::Life },
			{ "Elements", DamageType::Elements },
			{ "Supernatural", DamageType::Supernatural },
			{ "Generic", DamageType::Generic }
		});

		// Descriptor
		mState.new_enum<Descriptors>("Descriptors", {
			{ "IsMelee", Descriptors::IsMelee },
			{ "IsBasic", Descriptors::IsBasic },
			{ "IsDoT", Descriptors::IsDoT },
			{ "IsAoE", Descriptors::IsAoE },
			{ "IsBuff", Descriptors::IsBuff },
			{ "IsDebuff", Descriptors::IsDebuff },
			{ "IsPhysicalDamage", Descriptors::IsPhysicalDamage },
			{ "IsEnergyDamage", Descriptors::IsEnergyDamage },
			{ "IsCosmetic", Descriptors::IsCosmetic },
			{ "IsHaste", Descriptors::IsHaste },
			{ "IsChannel", Descriptors::IsChannel },
			{ "HitReactNone", Descriptors::HitReactNone },
			{ "IsHoT", Descriptors::IsHoT },
			{ "IsProjectile", Descriptors::IsProjectile },
			{ "IgnorePlayerCount", Descriptors::IgnorePlayerCount },
			{ "IgnoreDifficulty", Descriptors::IgnoreDifficulty },
			{ "IsSelfResurrect", Descriptors::IsSelfResurrect },
			{ "IsInteract", Descriptors::IsInteract },
			{ "IsThorns", Descriptors::IsThorns }
		});

		// NpcType
		mState.new_enum<NpcType>("NpcType", {
			{ "Invalid", NpcType::Invalid },
			{ "Minion", NpcType::Minion },
			{ "Special", NpcType::Special },
			{ "Boss", NpcType::Boss },
			{ "Destructible", NpcType::Destructible },
			{ "Interactable", NpcType::Interactable },
			{ "Agent", NpcType::Agent },
			{ "Victim", NpcType::Victim },
			{ "Captain", NpcType::Captain }
		});

		// DropType
		mState.new_enum<DropType>("DropType", {
			{ "None", DropType::None },
			{ "Orbs", DropType::Orbs },
			{ "Catalysts", DropType::Catalysts },
			{ "Loot", DropType::Loot },
			{ "DNA", DropType::DNA }
		});
	}

	void Lua::RegisterFunctions() {
		// global functions
		mState["AddEvent"] = [this](sol::this_state L, sol::protected_function callback, uint32_t delay, sol::variadic_args args) {
			if (delay > 0) {
				auto& game = mGame;
				return game.AddTask(delay, [&game, callback = std::move(callback), args = std::vector<sol::object>(args.begin(), args.end())](uint32_t id) mutable {
					game.AddServerTask([&game, id, callback = std::move(callback), args = std::move(args)]() mutable {
						game.CancelTask(id);
						callback.call<void>(sol::as_args(args));
					});
				});
			} else {
				callback.call<void>(args);
				return static_cast<uint32_t>(0);
			}
		};

		mState["StopEvent"] = [this](sol::this_state L, uint32_t id) {
			mGame.CancelTask(id);
		};

		RegisterThread();
		RegisterGame();
		RegisterObjectManager();
		RegisterLocomotion();
		RegisterPlayer();
		RegisterAttributes();
		RegisterObject();
		RegisterAbility();
		RegisterObjective();
		RegisterTriggerVolume();
	}

	void Lua::RegisterThread() {
		auto thread = mState.create_named_table("nThread");

		// nThread.Create(owner, callback, ...)
		thread["Create"] = [this](sol::this_state L, sol::object objectValue, sol::protected_function callback, sol::variadic_args args) {
			LuaThread* thread;

			auto& objectManager = mGame.GetObjectManager();
			auto object = LuaGetObject(objectManager, objectValue);
			if (object) {
				thread = object->GetLuaThread();
				if (thread && thread->status() != sol::thread_status::dead) {
					return;
				} else {
					thread = SpawnThread();
					object->SetLuaThread(thread);
				}
			} else {
				thread = SpawnThread();
			}

			thread->call<void>(callback, args);
		};

		thread["GetValue"] = [this](sol::this_state L, std::string key) {
			auto thread = GetThread(L);
			return (thread != nullptr) ? thread->get_value(key) : sol::make_object(L, sol::lua_nil);
		};

		thread["SetValue"] = [this](sol::this_state L, std::string key, sol::object value) {
			auto thread = GetThread(L);
			if (thread) {
				thread->set_value(key, std::move(value));
			}
		};

		thread["Sleep"] = sol::yielding([this](sol::this_state L, int32_t milliseconds) {
			auto thread = GetThread(L);
			if (!thread) {
				return;
			}

			if (milliseconds > 0) {
				uint64_t time = utils::get_milliseconds() + milliseconds;
				thread->set_resume_condition([time](lua_State* L, sol::variadic_results& results) { return utils::get_milliseconds() >= time; });
			}

			YieldThread(thread);
		});

		thread["WaitForCallback"] = sol::yielding([this](sol::this_state L, sol::function callback) {
			auto thread = GetThread(L);
			if (!thread) {
				return;
			}

			thread->set_resume_condition([callback](lua_State* L, sol::variadic_results& results) {
				return callback.call<bool>();
			});

			YieldThread(thread);
		});

		thread["WaitForHitpointsAbove"] = sol::yielding([this](sol::this_state L, sol::object objectValue, float value, float deathTimer) {
			auto thread = GetThread(L);
			if (!thread) {
				return;
			}

			auto& objectManager = mGame.GetObjectManager();
			auto object = LuaGetObject(objectManager, objectValue);
			if (object) {
				thread->set_resume_condition([&objectManager, objectId = object->GetId(), value](lua_State* L, sol::variadic_results& results) {
					auto object = objectManager.Get(objectId);
					if (!object) {
						return true;
					}

					// Check death timer thingy
					//

					return object->GetHealth() > value;
				});
			}

			YieldThread(thread);
		});

		thread["WaitForXSeconds"] = sol::yielding([this](sol::this_state L, double seconds, sol::object attributesSnapshotValue, sol::optional<bool> channeling) {
			auto thread = GetThread(L);
			if (!thread) {
				return;
			}

			if (seconds > 0) {
				auto ability = LuaGetAbility(L);
				if (ability && attributesSnapshotValue.is<Game::AttributesPtr>()) {
					const auto descriptors = ability->GetDescriptors();
					const auto& attributes = attributesSnapshotValue.as<Game::AttributesPtr>();

					if (utils::enum_helper<Game::Descriptors>::test(descriptors, Game::Descriptors::IsBasic)) {
						seconds /= std::max(-0.9f, attributes->GetValue(Game::AttributeType::AttackSpeedScale)) + 1;
					}

					if (utils::enum_helper<Game::Descriptors>::test(descriptors, Game::Descriptors::IsChannel) && channeling.value_or(false)) {
						seconds *= 1.f - attributes->GetValue(Game::AttributeType::ChannelTimeDecrease);
						seconds = std::max(0.05, seconds);
					}
				}
			}

			if (seconds > 0) {
				uint64_t time = utils::get_milliseconds() + static_cast<uint64_t>(seconds * 1000);
				thread->set_resume_condition([time](lua_State* L, sol::variadic_results& results) { return utils::get_milliseconds() >= time; });
			}

			YieldThread(thread);
		});

		thread["WaitUntilTime"] = sol::yielding([this](sol::this_state L, double seconds, sol::object attributesSnapshotValue, sol::optional<bool> channeling) {
			auto thread = GetThread(L);
			if (!thread) {
				return;
			}

			if (seconds > 0) {
				auto ability = LuaGetAbility(L);
				if (ability && attributesSnapshotValue.is<Game::AttributesPtr>()) {
					const auto descriptors = ability->GetDescriptors();
					const auto& attributes = attributesSnapshotValue.as<Game::AttributesPtr>();

					if (utils::enum_helper<Game::Descriptors>::test(descriptors, Game::Descriptors::IsBasic)) {
						seconds /= std::max(-0.9f, attributes->GetValue(Game::AttributeType::AttackSpeedScale)) + 1;
					}

					if (utils::enum_helper<Game::Descriptors>::test(descriptors, Game::Descriptors::IsChannel) && channeling.value_or(false)) {
						seconds *= 1.f - attributes->GetValue(Game::AttributeType::ChannelTimeDecrease);
						seconds = std::max(0.05, seconds);
					}
				}
			}

			if (seconds > 0) {
				uint64_t time = utils::get_milliseconds() + static_cast<uint64_t>(seconds * 1000);
				thread->set_resume_condition([time](lua_State* L, sol::variadic_results& results) { return utils::get_milliseconds() >= time; });
			}

			YieldThread(thread);
		});

		thread["WaitForProjectile"] = sol::yielding([this](sol::this_state L,
			sol::object projectileObjectValue,
			sol::table projectileParametersTable,
			sol::optional<sol::object> targetValue,
			sol::optional<sol::protected_function> callbackValue
		) {
			const auto CalculateExpectedGeoCollision = [=](const auto& locomotion, const auto& parameters) {
				locomotion->SetHasCollidedWithCreature(false);
				locomotion->SetHasCollided(false);
				locomotion->SetReflectedLastUpdate(1000);

				// *(undefined*)&object->locomotion->field_0x10 = 0;
				// *(undefined4*)&object->locomotion->field_0x14 = 0;

				auto something = parameters.mDirection * parameters.mRange;
				/*
				pLVar1 = object->locomotion;
				local_28.z = (pLVar1->projectile_parameters).range;
				local_28.x = local_28.z * (pLVar1->projectile_parameters).direction.x;
				local_28.y = (pLVar1->projectile_parameters).direction.y * local_28.z;
				local_28.z = (pLVar1->projectile_parameters).direction.z * local_28.z;
				bVar2 = FUN_00a33800(&local_1c, object, &local_28);
				*/
				const auto& object = locomotion->GetObject();
				if (object->IsColliding()) {
					locomotion->SetExpectedGeoCollision(object->GetPosition());
				}
			};

			const auto ProjectileFlagsOne = [=](const Game::ObjectPtr& projectile, const Game::ObjectPtr& target) {
				const auto& projectileLocomotion = projectile->GetLocomotionData();
				if (!projectileLocomotion) {
					return;
				}

				projectileLocomotion->SetHasCollidedWithCreature(false);
				projectileLocomotion->SetHasCollided(false);
				projectileLocomotion->SetReflectedLastUpdate(1000);

				uint32_t targetId;
				if (target) {
					targetId = target->GetId();
				} else {
					targetId = 0;
				}

				projectileLocomotion->SetTargetId(targetId);
				projectile->SetMovementType(Game::MovementType::HomingProjectile);

				auto& parameters = projectileLocomotion->GetProjectileParameters();
				if (parameters.mEccentricity > 0) {
					parameters.mJinkInfo = utils::random::get<uint8_t>(0, 0xFF) | std::clamp<uint8_t>(static_cast<uint8_t>(parameters.mEccentricity * 255.f), 0, 0xFF);
				}

				projectileLocomotion->SetInitialDirection(parameters.mDirection);
				if (target) {
					const auto& projectileCenter = projectile->GetCenterPoint();
					const auto& targetCenter = target->GetCenterPoint();

					auto delta = projectileCenter - targetCenter;
					auto deltaLength = glm::length(delta);

					projectile->SetLinearVelocity(glm::normalize(delta) * parameters.mSpeed);

					// What?
					float jinkValue = deltaLength * 0.75f;
					if (2.f < (deltaLength - jinkValue)) {
						jinkValue = deltaLength - 2.f;
					}

					parameters.mJinkInfo |= (static_cast<uint32_t>(jinkValue * 10.f) << 16);
				} else {
					auto newDirection = glm::normalize(glm::vec3(parameters.mDirection.x, parameters.mDirection.y, 0));
					parameters.mDirection = newDirection;

					projectile->SetLinearVelocity(newDirection * parameters.mSpeed);

					CalculateExpectedGeoCollision(projectileLocomotion, parameters);
					// *(undefined4*)&object->locomotion->field_0xd0 = 0x7f7fffff;
				}

				/*
				pLVar5 = object->locomotion;
				bVar4 = *(byte *)((int)&(pLVar5->projectile_parameters).jink_info + 2);
				uVar3 = *(undefined *)((int)&(pLVar5->projectile_parameters).jink_info + 1);
				*(undefined *)&pLVar5->field_0xc5 = *(undefined *)&(pLVar5->projectile_parameters).jink_info;
				*(undefined *)&pLVar5->field_0xc6 = uVar3;
				*(float *)&pLVar5->field_0xd0 = (float)(uint)bVar4 * 0.1;
				*/
			};

			auto thread = GetThread(L);
			if (!thread) {
				return;
			}

			auto& objectManager = mGame.GetObjectManager();
			auto projectile = LuaGetObject(objectManager, projectileObjectValue);
			if (projectile && projectile->HasLocomotionData()) {
				const auto& locomotion = projectile->GetLocomotionData();

				auto& parameters = locomotion->GetProjectileParameters();
				parameters = LuaGetProjectileParameters(projectileParametersTable);

				const auto& owner = projectile->GetOwnerObject();
				if (owner) {
					parameters.mRange *= 1.f + owner->GetAttributeValue(Game::AttributeType::RangeIncrease);
					/*
					owner->GetAttributeValue(Game::AttributeType::ProjectileSpeedIncrease)
					projectile->GetAttributeValue(Game::AttributeType::MovementSpeedBuff)
					*/
				}

				projectile->SetLinearVelocity(parameters.mDirection * parameters.mSpeed);
				projectile->SetAngularVelocity(parameters.mDirection * parameters.mSpinRate);

				auto dot = glm::dot(parameters.mDirection, parameters.mDirection);
				if (dot < 0) {
					parameters.mDirection = projectile->GetLocomotionData()->GetFacing();
					dot = glm::length(parameters.mDirection);
				}

				/* dunno what this does
				if (dot > 0) {
					piVar7 = (int*)FUN_009c1050();
					pvVar6 = (vec3*)(**(code**)(*piVar7 + 0x10))(&local_1c, &projectile->position);
					pqVar8 = FUN_007b69f0(&qStack16, pvVar1, pvVar6);
					(projectile->orientation).x = pqVar8->x;
					(projectile->orientation).y = pqVar8->y;
					(projectile->orientation).z = pqVar8->z;
					(projectile->orientation).w = pqVar8->w;
				}
				*/

				if (parameters.mProjectileFlags & 1) {
					Game::ObjectPtr target;
					if (targetValue.has_value()) {
						target = LuaGetObject(objectManager, *targetValue);
					}
					ProjectileFlagsOne(projectile, target);
				} else {
					CalculateExpectedGeoCollision(locomotion, parameters);
				}

				thread->set_resume_condition([&objectManager, id = projectile->GetId(), position = projectile->GetPosition(), range = parameters.mRange](lua_State* L, sol::variadic_results& results) {
					const Game::ObjectPtr& object = objectManager.Get(id);
					if (!object) {
						results.push_back({ L, sol::in_place, Game::ObjectPtr() });
						results.push_back({ L, sol::in_place, true });
						results.push_back({ L, sol::in_place, true });
						results.push_back({ L, sol::in_place, glm::zero<glm::vec3>() });
						results.push_back({ L, sol::in_place, 0 });
						return true;
					}

					auto delta = position - object->GetPosition();
					auto distance = range - glm::length(delta);
					if (distance > 0) {
						const auto& locomotionData = object->GetLocomotionData();

						bool hasCollidedWithCreature = locomotionData->HasCollidedWithCreature();
						bool hasCollided = locomotionData->HasCollided();
						if (!hasCollidedWithCreature && !hasCollided) {
							return false;
						}

						results.push_back({ L, sol::in_place, Game::ObjectPtr() });
						results.push_back({ L, sol::in_place, hasCollidedWithCreature });
						results.push_back({ L, sol::in_place, hasCollided });
					} else {
						results.push_back({ L, sol::in_place, Game::ObjectPtr() });
						results.push_back({ L, sol::in_place, false });
						results.push_back({ L, sol::in_place, false });
					}

					results.push_back({ L, sol::in_place, object->GetPosition() });
					results.push_back({ L, sol::in_place, distance });
					return true;
				});
			}

			YieldThread(thread);
		});
	}

	void Lua::RegisterGame() {
		auto gameMetatable = mState.create_table_with();

		// variables
		gameMetatable["Instance"] = &mGame;
		gameMetatable["Level"] = mGame.GetChainData().GetLevelIndex();

		// functions
		gameMetatable["GetPlayer"] = [this](sol::this_state L, uint8_t index) {
			return mGame.GetPlayerByIndex(index);
		};

		gameMetatable["Notify"] = [this](sol::this_state L, sol::table serverEventTable) {
			auto serverEvent = LuaGetServerEvent(mGame.GetObjectManager(), serverEventTable);
			mGame.SendServerEvent(serverEvent);
		};

		// meta
		gameMetatable[sol::meta_function::new_index] = [](lua_State* L) { return luaL_error(L, "You may not edit the Game table."); };
		gameMetatable[sol::meta_function::index] = gameMetatable;

		mState.create_named_table("Game")[sol::metatable_key] = gameMetatable;
	}

	void Lua::RegisterObjectManager() {
		auto objectManager = mState.create_named_table("nObjectManager");
		objectManager["GetObject"] = &LuaFunction::nObjectManager_GetObject;
		objectManager["CreateObject"] = &LuaFunction::nObjectManager_CreateObject;

		objectManager["GetTrigger"] = &LuaFunction::nObjectManager_GetTrigger;
		objectManager["CreateTriggerVolume"] = &LuaFunction::nObjectManager_CreateTriggerVolume;

		objectManager["GetObjectsInRadius"] = &LuaFunction::nObjectManager_GetObjectsInRadius;
		objectManager["GetObjectsInRadius_SortedByDistance"] = &LuaFunction::nObjectManager_GetObjectsInRadius_SortedByDistance;
	}

	void Lua::RegisterLocomotion() {
		auto locomotion = mState.create_named_table("Locomotion");

		// event functions
		locomotion["On"] = &LuaFunction::Locomotion::On;

		// object functions (object as arg0)
		locomotion["TeleportAndFace"] = &LuaFunction::Locomotion::TeleportAndFace;
		locomotion["TeleportObject"] = &LuaFunction::Locomotion::TeleportObject;
		locomotion["JumpInDirection"] = &LuaFunction::Locomotion::JumpInDirection;
		locomotion["SlideToPoint"] = &LuaFunction::Locomotion::SlideToPoint;
		locomotion["MoveToPointExact"] = &LuaFunction::Locomotion::MoveToPointExact;
		locomotion["MoveToCircleEdge"] = &LuaFunction::Locomotion::MoveToCircleEdge;
		locomotion["MoveToPointWithinRange"] = &LuaFunction::Locomotion::MoveToPointWithinRange;
		locomotion["MoveToObject"] = &LuaFunction::Locomotion::MoveToObject;
		locomotion["FollowAsPet"] = &LuaFunction::Locomotion::FollowAsPet;

		locomotion["ApplyExternalVelocity"] = &LuaFunction::Locomotion::ApplyExternalVelocity;
		locomotion["ClearExternalVelocity"] = &LuaFunction::Locomotion::ClearExternalVelocity;
		locomotion["ClearTargetObject"] = &LuaFunction::Locomotion::ClearTargetObject;

		locomotion["FaceObjectDuringMove"] = &LuaFunction::Locomotion::FaceObjectDuringMove;
		locomotion["TurnToFace"] = &LuaFunction::Locomotion::TurnToFace;
		locomotion["TurnToFaceTargetObject"] = &LuaFunction::Locomotion::TurnToFaceTargetObject;
		locomotion["MoveToPointWhileFacingTarget"] = &LuaFunction::Locomotion::MoveToPointWhileFacingTarget;

		locomotion["Stop"] = &LuaFunction::Locomotion::Stop;

		// position functions (vec3 as arg0)
		locomotion["GetClosestPosition"] = &LuaFunction::Locomotion::GetClosestPosition;
		locomotion["GetClosestPositionFromPoint"] = &LuaFunction::Locomotion::GetClosestPositionFromPoint;

		locomotion["GetTargetPosition"] = &LuaFunction::Locomotion::GetTargetPosition;
		locomotion["SetTargetPosition"] = &LuaFunction::Locomotion::SetTargetPosition;
	}

	void Lua::RegisterPlayer() {
		auto player = mState.new_usertype<Player>("Player", sol::no_constructor);
		player["GetCharacter"] = &Player::GetCharacterObject;
		player["GetDeployedCharacter"] = &Player::GetDeployedCharacterObject;

		player["Notify"] = [this](sol::this_state L, sol::object playerValue, sol::table serverEventTable) {
			auto player = LuaGetPlayer(mGame, playerValue);
			if (player) {
				auto serverEvent = LuaGetServerEvent(mGame.GetObjectManager(), serverEventTable);
				mGame.SendServerEvent(player, serverEvent);
			}
		};
	}

	void Lua::RegisterAttributes() {
		auto attributes = mState.new_usertype<Game::Attributes>("Attributes", sol::no_constructor);
		attributes["GetValue"] = sol::resolve<float(uint8_t) const>(&Game::Attributes::GetValue);
		attributes["SetValue"] = sol::resolve<void(uint8_t, float)>(&Game::Attributes::SetValue);

		attributes["GetOwnerObject"] = &Game::Attributes::GetOwnerObject;
	}

	void Lua::RegisterObject() {
		auto object = mState.new_usertype<Object>("Object", sol::no_constructor);
		object["IsValid"] = &LuaFunction::Object::IsValid;

		object["GetId"] = &Object::GetId;
		object["GetName"] = &LuaFunction::Object::GetName;
		object["GetPrivateTable"] = &LuaFunction::Object::GetPrivateTable;

		object["GetPosition"] = &Object::GetPosition;
		object["SetPosition"] = &Object::SetPosition;

		object["GetOrientation"] = &Object::GetOrientation;
		object["SetOrientation"] = &Object::SetOrientation;

		object["GetExtent"] = &Object::GetExtent;
		object["SetExtent"] = &Object::SetExtent;

		object["GetType"] = &Object::GetType;
		object["GetNpcType"] = &Object::GetNpcType;

		object["GetFacing"] = &LuaFunction::Object::GetFacing;
		object["GetFootprintRadius"] = &Object::GetFootprintRadius;
		object["GetCenterPoint"] = &Object::GetCenterPoint;

		object["SetTickOverride"] = sol::resolve<void(sol::protected_function)>(&Object::SetTickOverride);

		object["Move"] = &LuaFunction::Object::Move;

		object["GetHealth"] = &Object::GetHealth;
		object["GetMaxHealth"] = &Object::GetMaxHealth;
		object["SetHealth"] = &Object::SetHealth;

		object["GetMana"] = &Object::GetMana;
		object["GetMaxMana"] = &Object::GetMaxMana;
		object["SetMana"] = &Object::SetMana;

		object["GetOwnerObject"] = &Object::GetOwnerObject;
		object["SetOwnerObject"] = &Object::SetOwnerObject;

		object["PlayAnimationSequence"] = [this](sol::this_state L, sol::object objectValue, sol::table sequenceTable) {
			auto ability = LuaGetAbility(L);
			if (!ability) {
				LogError(L, "Object.PlayAnimationSequence", "You may not call this function outside of an ability");
				return;
			}

			auto object = LuaGetObject(mGame.GetObjectManager(), objectValue);
			if (object) {

			}
		};

		object["SetAnimationState"] = &LuaFunction::Object::SetAnimationState;
		object["SetAnimationStateToDeath"] = &LuaFunction::Object::SetAnimationStateToDeath;
		object["SetAnimationStateToAggro"] = &LuaFunction::Object::SetAnimationStateToAggro;
		object["SetGraphicsState"] = &LuaFunction::Object::SetGraphicsState;

		object["GetAttributeSnapshot"] = &LuaFunction::Object::GetAttributeSnapshot;
		object["SetAttributeSnapshot"] = &LuaFunction::Object::SetAttributeSnapshot;

		object["GetAttributeValue"] = sol::resolve<float(uint8_t) const>(&Object::GetAttributeValue);
		object["SetAttributeValue"] = sol::resolve<void(uint8_t, float)>(&Object::SetAttributeValue);

		object["GetWeaponDamage"] = &LuaFunction::Object::GetWeaponDamage;

		object["GetMarkerId"] = &Object::GetMarkerId;
		object["SetMarkerId"] = &Object::SetMarkerId;

		object["GetScale"] = &Object::GetScale;
		object["SetScale"] = &Object::SetScale;

		object["GetTeam"] = &Object::GetTeam;
		object["SetTeam"] = &Object::SetTeam;

		object["IsPlayerControlled"] = &Object::IsPlayerControlled;
		object["GetPlayerIndex"] = &Object::GetPlayerIndex;

		object["IsVisible"] = &Object::IsVisible;
		object["SetVisible"] = &Object::SetVisible;

		object["IsMarkedForDeletion"] = &Object::IsMarkedForDeletion;
		object["MarkForDeletion"] = &Object::MarkForDeletion;

		object["IsCombatant"] = &LuaFunction::Object::IsCombatant;

		object["AddCooldown"] = &LuaFunction::Object::AddCooldown;
		object["RemoveCooldown"] = &LuaFunction::Object::RemoveCooldown;
		object["ScaleCooldown"] = &LuaFunction::Object::ScaleCooldown;

		object["TakeDamage"] = &LuaFunction::Object::TakeDamage;
		object["Heal"] = &LuaFunction::Object::Heal;
		
		object["RequestAbility"] = [this](sol::this_state L, sol::object objectValue, sol::object attackerValue, uint32_t abilityId, int32_t rank) {
			// darkspore original = object.request_ability(ability, object, target, position, ...)
			const auto& ability = GetAbility(abilityId);
			if (!ability) {
				return;
			}

			const auto& objectManager = mGame.GetObjectManager();

			auto object = LuaGetObject(objectManager, objectValue);
			if (!object) {
				return;
			}
		};

		object["RequestModifier"] = [this](sol::this_state L, sol::object objectValue, sol::object attackerValue, uint32_t abilityId, int32_t rank) {
			//
		};

		object["AddEffect"] = &LuaFunction::Object::AddEffect;
		object["RemoveEffect"] = &LuaFunction::Object::RemoveEffect;
		object["RemoveEffectIndex"] = &LuaFunction::Object::RemoveEffectIndex;

		object["UseAbility"] = &LuaFunction::Object::UseAbility;
		object["DropLoot"] = &LuaFunction::Object::DropLoot;

		object["GetSharedAbilityOffset"] = &LuaFunction::Object::GetSharedAbilityOffset;

		// Interactable data
		object["HasInteractableUsesLeft"] = &Object::HasInteractableUsesLeft;
		object["IncrementNumTimesUsed"] = &LuaFunction::Object::IncrementNumTimesUsed;

		// Agent blackboard
		object["GetTargetId"] = &Object::GetTargetId;
		object["SetTargetId"] = &Object::SetTargetId;

		object["IsStealthed"] = &LuaFunction::Object::IsStealthed;
		object["GetStealthType"] = &Object::GetStealthType;
		object["SetStealthType"] = &Object::SetStealthType;

		object["IsInCombat"] = &Object::IsInCombat;
		object["SetInCombat"] = &Object::SetInCombat;

		object["IsTargetable"] = &Object::IsTargetable;
		object["SetTargetable"] = &Object::SetTargetable;

		// Markers
		object["GetTeleporterDestination"] = &LuaFunction::Object::GetTeleporterDestination;
	}

	void Lua::RegisterAbility() {
		auto ability = mState.create_named_table("Ability");
		ability["Register"] = [this](sol::this_state L, sol::table ability) {
			// TODO: validate ability
			if (ability == sol::nil) {
				LogError(L, "Ability.Register", "ability is nil");
				return;
			}

			const auto& nameOption = ability["name"].get<sol::optional<std::string>>();
			if (!nameOption) {
				LogError(L, "Ability.Register", "ability has no name");
				return;
			}
			
			const auto& name = nameOption.value();
			if (auto [it, inserted] = mAbilities.try_emplace(utils::hash_id(name)); inserted) {
				ability["id"] = it->first;
				it->second = std::make_shared<Ability>(*this, std::move(ability), name, it->first);
			} else {
				LogError(L, "Ability.Register", "trying to register " + name + " when it already exists");
			}
		};

		ability["TargetInRangeAtStart"] = [this](sol::this_state L) -> bool {
			auto ability = LuaGetAbility(L);
			if (!ability) {
				LogError(L, "Ability.TargetInRangeAtStart", "You may not call this function outside of an ability");
				return false;
			}
			return true;
		};
	}

	void Lua::RegisterObjective() {
		auto objective = mState.create_named_table("Objective");
		objective["Register"] = [this](sol::this_state L, sol::table objective) {
			return LogError(L, "Objective.Register", "this function has not been implemented yet");
		};

		/*
		local_a8 = "RegisterObjective";
		local_a4 = &LAB_00a0c340;
		local_a0 = "SetObjectiveIntData";
		local_9c = &LAB_00a009a0;
		local_98 = "SetObjectiveIntDataFromSPID";
		local_94 = &LAB_00a00a90;
		local_90 = "GetObjectiveIntData";
		local_8c = FUN_00a00bc0;
		local_88 = "SetObjectiveFloatData";
		local_84 = FUN_00a00c60;
		local_80 = "SetObjectiveFloatDataFromSPID";
		local_7c = FUN_00a00d40;
		local_78 = "GetObjectiveFloatData";
		local_74 = FUN_00a00e60;
		local_70 = "SetObjectiveGUIDData";
		local_6c = FUN_00a00f10;
		local_68 = "SetObjectiveGUIDDataFromSPID";
		local_64 = &LAB_00a01020;
		local_60 = "GetObjectiveGUIDData";
		local_5c = FUN_00a01170;
		*/

		/*
		local_58 = "CreateObjectiveEvent";
		local_54 = FUN_00a01220;
		local_50 = "SendObjectiveEvent";
		local_4c = FUN_00a01280;
		local_48 = "DestroyObjectiveEvent";
		local_44 = FUN_00a012f0;
		local_40 = "SetObjectiveEventIntData";
		local_3c = FUN_00a01360;
		local_38 = "GetObjectiveEventIntData";
		local_34 = FUN_00a01440;
		local_30 = "SetObjectiveEventFloatData";
		local_2c = FUN_00a01520;
		local_28 = "GetObjectiveEventFloatData";
		local_24 = FUN_00a015e0;
		local_20 = "SetObjectiveEventGUIDData";
		local_1c = FUN_00a016b0;
		local_18 = "GetObjectiveEventGUIDData";
		local_14 = FUN_00a017b0;
		local_8 = "GetRegisteredDestructibles";
		local_4 = &LAB_00a01890;
		*/
	}

	void Lua::RegisterTriggerVolume() {
		auto triggerVolume = mState.new_usertype<TriggerVolume>("TriggerVolume", sol::no_constructor, sol::base_classes, sol::bases<Object>());

		triggerVolume["Attach"] = [this](sol::this_state L, sol::object triggerValue, sol::object objectValue) {
			const auto& objectManager = mGame.GetObjectManager();

			auto trigger = LuaGetTrigger(objectManager, triggerValue);
			auto object = LuaGetObject(objectManager, objectValue);
			if (trigger && object) {
				trigger->Attach(object);
			}
		};

		triggerVolume["Detach"] = [this](sol::this_state L, sol::object triggerValue, sol::object objectValue) {
			const auto& objectManager = mGame.GetObjectManager();

			auto trigger = LuaGetTrigger(objectManager, triggerValue);
			auto object = LuaGetObject(objectManager, objectValue);
			if (trigger && object) {
				trigger->Detach(object);
			}
		};

		triggerVolume["SetOnEnterCallback"] = &TriggerVolume::SetOnEnterCallback;
		triggerVolume["SetOnExitCallback"] = &TriggerVolume::SetOnExitCallback;
		triggerVolume["SetOnStayCallback"] = &TriggerVolume::SetOnStayCallback;
	}
}
