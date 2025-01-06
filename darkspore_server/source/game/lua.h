
#ifndef _GAME_LUA_HEADER
#define _GAME_LUA_HEADER

// Include
#include "attributes.h"

#include <glm/glm.hpp>

#define SOL_SAFE_FUNCTION_OBJECTS 1
#define SOL_PRINT_ERRORS 1
#include <sol/sol.hpp>

#include <unordered_map>
#include <unordered_set>
#include <functional>

// Game
namespace Game {
	// Predefined
	class Instance;
	class LuaBase;
	class Lua;
	class Ability;

	using AbilityPtr = std::shared_ptr<Ability>;

	// LuaThread
	class LuaThread {
		public:
			using ResumeCondition = std::function<bool(lua_State*, sol::variadic_results&)>;

		public:
			LuaThread(Lua& lua);

			decltype(auto) lua_state() const { return mThread.thread_state(); }
			decltype(auto) status() const { return mThread.status(); }

			sol::object get_value(const std::string& key) const;
			void set_value(const std::string& key, sol::object&& value);

			bool resume();
			void stop();

			void set_resume_condition(const ResumeCondition& condition);
			void set_resume_condition(ResumeCondition&& condition);

			template<typename Result, typename... Args>
			decltype(auto) call(const sol::function& func, Args&&... args) {
				create(func);

				sol::protected_function_result result = mCoroutine(std::forward<Args>(args)...);
				if (result.valid()) {
					post_call();
				} else {
					sol::error err = result;
					std::cout << "LuaThread::call()" << std::endl;
					std::cout << err.what() << std::endl;
					std::cout << std::to_underlying(mCoroutine.status()) << std::endl;
				}

				if constexpr (!std::is_void_v<Result>) {
					return static_cast<Result>(result);
				}
			}

			template<typename Result, typename... Args>
			auto call(const sol::environment& env, const sol::function& func, Args&&... args) {
				env.set_on(mThread);
				return call<Result>(func, std::forward<Args>(args)...);
			}

		private:
			void create(const sol::function& func);
			void post_call();
		
		private:
			Lua& mLua;
			
			std::unordered_map<std::string, sol::object> mValues;

			ResumeCondition mResumeCondition;

			sol::thread mThread;
			sol::coroutine mCoroutine;
			sol::environment mEnvironment;

			friend class Lua;
	};

	// LuaBase
	class LuaBase {
		public:
			LuaBase() = default;
			virtual ~LuaBase();

			virtual void Initialize();
			virtual void Reload();

			static sol::protected_function_result ReportError(lua_State* L, sol::protected_function_result pfr);
			static const char* GetStackTrace(lua_State* L, const char* error);

			sol::protected_function_result LoadFile(const std::string& path);
			sol::protected_function_result LoadBuffer(const std::string& buffer);

			lua_State* GetState() const;

			void CollectGarbage();

		protected:
			void LogError(lua_State* L, std::string_view function, const std::string& message) const;

		private:
			// luafunctions.cpp
			void RegisterFunctions();

			void RegisterMath();
			void RegisterUtil();
			void RegisterClient();
			void RegisterAbility();
			void RegisterPhysics();
			void RegisterGameObject();
			void RegisterAbilityAnimationSelection();
			void RegisterDebug();
			void RegisterNPCType();
			void RegisterTuning();
			void RegisterPlayer();
			void RegisterLocomotion();

		protected:
			sol::state mState;

		private:
			std::vector<std::string> mDefaultPackages;
	};

	// GlobalLua
	class GlobalLua : public LuaBase {
		public:
			~GlobalLua();

			static GlobalLua& Instance();

			void Initialize() override;
			void Reload() override;

			const sol::bytecode& GetAbility(const std::string& abilityName) const;
			const sol::bytecode& GetAbility(uint32_t abilityId) const;

		private:
			void LoadAbilities();

		private:
			static GlobalLua sInstance;

			std::unordered_map<uint32_t, sol::bytecode> mLoadedAbilities;
	};

	// Lua
	class Lua : public LuaBase {
		public:
			Lua(Instance& game);
			~Lua();

			void Initialize() override;
			void Reload() override;

			void Update();
			void PreloadAbilities();

			Instance& GetGame();
			const Instance& GetGame() const;

			AbilityPtr GetAbility(const std::string& abilityName);
			AbilityPtr GetAbility(uint32_t abilityId);

			sol::table GetPrivateTable(uint32_t id) const;
			sol::table CreatePrivateTable(uint32_t id);
			void RemovePrivateTable(uint32_t id);

			LuaThread* SpawnThread();
			LuaThread* GetThread(lua_State* L) const;
			void YieldThread(LuaThread* thread);

			template<typename Result, typename... Args>
			auto CallCoroutine(std::nullptr_t, const sol::function& func, Args&&... args) {
				return SpawnThread()->call<Result>(func, std::forward<Args>(args)...);
			}

			template<typename Result, typename... Args>
			auto CallCoroutine(const sol::environment& env, const sol::function& func, Args&&... args) {
				return SpawnThread()->call<Result>(env, func, std::forward<Args>(args)...);
			}

			void ReturnThreadToPool(LuaThread* thread);

		private:
			// luafunctions.cpp
			void RegisterEnums();
			void RegisterFunctions();

			void RegisterThread();
			void RegisterGame();
			void RegisterObjectManager();
			void RegisterLocomotion();
			void RegisterPlayer();
			void RegisterAttributes();
			void RegisterObject();
			void RegisterAbility();
			void RegisterObjective();
			void RegisterTriggerVolume();

		private:
			Instance& mGame;

			std::unordered_map<lua_State*, LuaThread*> mThreads;
			std::unordered_map<uint32_t, AbilityPtr> mAbilities;
			std::unordered_map<uint32_t, sol::table> mPrivateTables;

			std::unordered_set<LuaThread*> mYieldedThreads;

			std::vector<LuaThread*> mThreadPool;
	};

	// Coroutine
	class Coroutine {
		public:
			Coroutine(Lua& lua, sol::table&& self);
			virtual ~Coroutine() = default;

			void Reload();

		protected:
			template<typename Result, typename... Args>
			auto Call(sol::function fn, Args&&... args) const {
				if (fn) {
					return mLua.CallCoroutine<Result>(mEnvironment, fn, mSelf, std::forward<Args>(args)...);
				}

				if constexpr (!std::is_void_v<Result>) {
					return Result {};
				}
			}

		protected:
			Lua& mLua;

			sol::table mSelf;
			sol::environment mEnvironment;
	};

	// Ability
	class Ability : public Coroutine {
		public:
			Ability(Lua& lua, sol::table&& self, const std::string& name, uint32_t id);

			// properties
			const std::string& GetName() const;

			Descriptors GetDescriptors() const;
			AttributeType GetScalingAttribute() const;
			InterfaceType GetInterface() const;

			uint32_t GetId() const;

			bool RequiresAgent() const;
			bool HasGlobalCooldown() const;
			bool ShouldPursue() const;

			// methods
			float GetManaCost(const ObjectPtr& object, int32_t rank, float value) const;

			bool IsInRange(const ObjectPtr& object, const ObjectPtr& target, const glm::vec3& targetPosition, int32_t rank) const;
			bool IsAbleToHit(const ObjectPtr& object, const ObjectPtr& target, const glm::vec3& targetPosition, int32_t rank) const;

			// events
			template<typename... Args>
			auto Activate(Args&&... args) const {
				return Call<void>(mActivateFn, std::forward<Args>(args)...);
			}

			template<typename... Args>
			auto Deactivate(Args&&... args) const {
				return Call<void>(mDeactivateFn, std::forward<Args>(args)...);
			}

			bool Tick(ObjectPtr object, ObjectPtr target, glm::vec3 cursorPosition, int32_t rank) const;

		private:
			std::string mName {};

			Descriptors mDescriptors;
			AttributeType mScalingAttribute;
			InterfaceType mInterface;

			uint32_t mId { 0 };

			bool mRequiresAgent { false };
			bool mHasGlobalCooldown { false };
			bool mShouldPursue { false };

			sol::function mActivateFn;
			sol::function mDeactivateFn;
			sol::function mTickFn;
	};

	// Objective
	class Objective : public Coroutine {
		public:
			Objective(Lua& lua, sol::table&& self);

			template<typename... Args>
			auto Init(Args&&... args) const {
				return Call<void>(mInitFn, std::forward<Args>(args)...);
			}

			template<typename... Args>
			auto HandleEvent(Args&&... args) const {
				return Call<void>(mHandleEventFn, std::forward<Args>(args)...);
			}

			template<typename... Args>
			auto Status(Args&&... args) const {
				return Call<uint32_t>(mStatusFn, std::forward<Args>(args)...);
			}

		private:
			sol::function mInitFn;
			sol::function mHandleEventFn;
			sol::function mStatusFn;
	};
}

#endif
