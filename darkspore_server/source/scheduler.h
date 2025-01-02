
#ifndef _SCHEDULER_HEADER
#define _SCHEDULER_HEADER

// Include
#include <cstdint>
#include <chrono>
#include <functional>
#include <queue>
#include <unordered_set>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>

// Task
class Task {
	public:
		auto operator()() const { mFunction(mId); }
		auto GetExecutionPoint() const { return mExecutionPoint; }

		auto GetId() const { return mId; }
		void SetId(uint32_t id) { mId = id; }

	private:
		Task(uint32_t delay, const std::function<void(uint32_t)>& f) :
			mExecutionPoint(std::chrono::system_clock::now() + std::chrono::milliseconds(delay)), mFunction(f) {}

		Task(uint32_t delay, std::function<void(uint32_t)>&& f) :
			mExecutionPoint(std::chrono::system_clock::now() + std::chrono::milliseconds(delay)), mFunction(std::move(f)) {}

		std::chrono::system_clock::time_point mExecutionPoint;
		std::function<void(uint32_t)> mFunction;

		uint32_t mId = 0;

		friend class Scheduler;
};

struct TaskComparator {
	constexpr auto operator()(const Task* lhs, const Task* rhs) const {
		return lhs->GetExecutionPoint() > rhs->GetExecutionPoint();
	}
};

// Scheduler
class Scheduler {
	public:
		Scheduler();

		uint32_t AddTask(uint32_t delay, const std::function<void(uint32_t)>& f);
		uint32_t AddTask(uint32_t delay, std::function<void(uint32_t)>&& f);
		void CancelTask(uint32_t id);

		void Shutdown();

	private:
		std::priority_queue<Task*, std::deque<Task*>, TaskComparator> mTasks;
		std::unordered_set<uint32_t> mTaskIds;

		std::atomic<uint8_t> mState;
		std::thread mThread;
		std::mutex mLock;
		std::condition_variable mSignal;
};

#endif
