
// Include
#include "scheduler.h"

// Scheduler
Scheduler::Scheduler() {
	mThread = std::thread([this] {
		std::unique_lock<std::mutex> eventLockUnique(mLock, std::defer_lock);
		while (mState.load(std::memory_order_relaxed) == 0) {
			std::cv_status ret = std::cv_status::no_timeout;

			eventLockUnique.lock();
			if (mTasks.empty()) {
				mSignal.wait(eventLockUnique);
			} else {
				ret = mSignal.wait_until(eventLockUnique, mTasks.top()->GetExecutionPoint());
			}

			if (ret != std::cv_status::timeout) {
				eventLockUnique.unlock();
				continue;
			}

			auto task = mTasks.top();
			mTasks.pop();

			auto it = mTaskIds.find(task->GetId());
			if (it == mTaskIds.end()) {
				eventLockUnique.unlock();
				delete task;
				continue;
			}

			mTaskIds.erase(it);
			eventLockUnique.unlock();

			(*task)();
			delete task;
		}
	});
}

uint32_t Scheduler::AddTask(uint32_t delay, const std::function<void(uint32_t)>& f) {
	static thread_local uint32_t taskId = 0;

	bool notify = false;
	mLock.lock();
	if (mState.load(std::memory_order_relaxed) != 0) {
		mLock.unlock();
		return 0;
	}

	if (++taskId == 0) {
		taskId = 1;
	}

	auto task = new Task(delay, f);
	task->SetId(taskId);

	mTaskIds.insert(task->GetId());
	mTasks.push(task);

	notify = task == mTasks.top();
	mLock.unlock();
	if (notify) {
		mSignal.notify_one();
	}

	return task->GetId();
}

void Scheduler::CancelTask(uint32_t id) {
	if (id == 0) {
		return;
	}

	std::lock_guard<std::mutex> lockGuard(mLock);
	if (auto it = mTaskIds.find(id); it != mTaskIds.end()) {
		mTaskIds.erase(it);
	}
}

void Scheduler::Shutdown() {
	mState.store(1, std::memory_order_relaxed);
	mLock.lock();

	while (!mTasks.empty()) {
		delete mTasks.top();
		mTasks.pop();
	}

	mTaskIds.clear();
	mLock.unlock();
	mSignal.notify_one();

	if (mThread.joinable()) {
		mThread.join();
	}
}
