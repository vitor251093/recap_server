
#ifndef _GAME_LEVEL_HEADER
#define _GAME_LEVEL_HEADER

// Include
#include "noun.h"

#include <unordered_map>
#include <memory>

// Game
namespace Game {
	// TriggerVolumeShape
	enum class TriggerVolumeShape : uint32_t {
		Sphere = 0,
		Box,
		Capsule
	};

	// TriggerVolumeActivationType
	enum class TriggerVolumeActivationType : uint32_t {
		EachObject = 0,
		EachPlayer,
		AnyObject,
		AllPlayers
	};

	// TriggerVolumeEvents
	class TriggerVolumeEvents {
		public:
			void Read(pugi::xml_node node);

		private:
			std::string mOnEnter;
			std::string mOnExit;
	};

	// TriggerVolumeData
	class TriggerVolumeData {
		public:
			void Read(pugi::xml_node node);

			const BoundingBox& GetBoundingBox() const;

			const glm::vec3& GetOffset() const;

			TriggerVolumeShape GetShape() const;
			TriggerVolumeActivationType GetActivationType() const;

			float GetTimeToActivate() const;

		private:
			BoundingBox mBoundingBox;

			TriggerVolumeEvents mEvents;

			glm::vec3 mOffset {};

			std::string mOnEnter;
			std::string mOnExit;
			std::string mOnStay;
			std::string mLuaCallbackOnEnter;
			std::string mLuaCallbackOnExit;
			std::string mLuaCallbackOnStay;

			TriggerVolumeShape mShape = TriggerVolumeShape::Sphere;
			TriggerVolumeActivationType mActivationType = TriggerVolumeActivationType::EachObject;

			float mTimeToActivate = 0;

			bool mUseObjectDimensions = false;
			bool mIsKinematic = false;
			bool mPersistentTimer = false;
			bool mTriggerOnceOnly = false;
			bool mTriggerIfNotBeaten = false;
	};

	// TeleporterData
	class TeleporterData {
		public:
			void Read(pugi::xml_node node);

			const std::unique_ptr<TriggerVolumeData>& GetTriggerVolumeData() const;

			uint32_t GetDestinationId() const;

			bool DeferTriggerCreation() const;

		private:
			std::unique_ptr<TriggerVolumeData> mTriggerVolumeData;

			uint32_t mDestinationMarkerId = 0;

			bool mDeferTriggerCreation = false;
	};

	// MarkerInteractableData
	class MarkerInteractableData {
		public:
			void Read(pugi::xml_node node);

			const std::string& GetAbility() const;
			const std::string& GetStartInteractEvent() const;
			const std::string& GetEndInteractEvent() const;
			const std::string& GetOptionalInteractEvent() const;

			int32_t GetUsesAllowed() const;
			int32_t GetChallengeValue() const;

		private:
			std::string mAbility;
			std::string mStartInteractEvent;
			std::string mEndInteractEvent;
			std::string mOptionalInteractEvent;

			int32_t mUsesAllowed = 0;
			int32_t mChallengeValue = 0;
	};

	// Marker
	class Marker {
		public:
			void Read(pugi::xml_node node);

			const std::unique_ptr<TeleporterData>& GetTeleporterData() const;
			const std::unique_ptr<MarkerInteractableData>& GetInteractableData() const;

			const glm::vec3& GetPosition() const;
			const glm::vec3& GetRotation() const;

			const std::string& GetNounName() const;

			uint64_t GetOverrideAssetId() const;

			uint32_t GetId() const;
			uint32_t GetNoun() const;
			uint32_t GetTargetId() const;

			float GetScale() const;

		private:
			std::unique_ptr<TeleporterData> mTeleporterData;
			std::unique_ptr<MarkerInteractableData> mInteractableData;

			glm::vec3 mPosition;
			glm::vec3 mRotation;

			std::string mName;
			std::string mNounName;

			uint64_t mOverrideAssetId = 0;

			uint32_t mId = 0;
			uint32_t mNoun = 0;
			uint32_t mTargetId = 0;

			float mScale = 0;

			bool mVisible = false;
			bool mHasCollision = false;

			friend class Markerset;
	};

	using MarkerPtr = std::shared_ptr<Marker>;

	// Markerset
	class Markerset {
		public:
			bool Load(const std::string& difficultyName, const std::string& markersetAsset);

			void Read(pugi::xml_node node);

			const std::vector<MarkerPtr>& GetMarkers() const;
			std::vector<MarkerPtr> GetMarkersByType(uint32_t noun) const;

		private:
			std::unordered_map<uint32_t, std::vector<MarkerPtr>> mMarkersByNoun;
			std::vector<MarkerPtr> mMarkers;

			std::string mName;

			friend class Level;
	};

	// DirectorClass
	class DirectorClass {
		public:
			void Read(pugi::xml_node node);

			const std::string& GetNounName() const;

			int32_t GetMinLevel() const;
			int32_t GetMaxLevel() const;

			bool IsHordeLegal() const;

		private:
			std::string mNounName;

			int32_t mMinLevel = 0;
			int32_t mMaxLevel = 100;

			bool mHordeLegal = true;
	};

	// LevelConfig
	class LevelConfig {
		public:
			void Read(pugi::xml_node node);

			DirectorClass GetMinion(size_t idx) const;
			DirectorClass GetSpecial(size_t idx) const;
			DirectorClass GetBoss(size_t idx) const;
			DirectorClass GetAgent(size_t idx) const;
			DirectorClass GetCaptain(size_t idx) const;

		private:
			std::vector<DirectorClass> mMinions;
			std::vector<DirectorClass> mSpecial;
			std::vector<DirectorClass> mBoss;
			std::vector<DirectorClass> mAgent;
			std::vector<DirectorClass> mCaptain;
	};

	// Level
	class Level {
		public:
			Level();
			~Level();

			bool Load(const std::string& difficultyName, const std::string& levelName);

			bool GetMarkerset(const std::string& name, Markerset& markerset) const;

			const LevelConfig& GetConfig() const;
			const LevelConfig& GetFirstTimeConfig() const;
			const LevelConfig& GetPlanetConfig() const;

		private:
			std::unordered_map<uint32_t, Markerset> mMarkersets;

			LevelConfig mConfig;
			LevelConfig mFirstTimeConfig;
			LevelConfig mPlanetConfig;
	};
}

#endif
