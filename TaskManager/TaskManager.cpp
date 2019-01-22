#include "taskManager.h"
#include "task.h"

#include <string>

TaskManager::TaskManager() {
	for (int i = 0; i < 4; ++i)
		workers.emplace_back(std::make_unique<Worker>("Worker " + std::to_string(i), 1));
}

void TaskManager::addTask(std::shared_ptr<Task> task) {
	bool added = false;
	while (!added) {
		for (auto & worker : workers) {
			added = worker->tryAddTask(task);
			if (added)
				break;
		}
		if (!added)
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

bool TaskManager::isFinished() {
	stopFreeWorkers();

	bool allDone = true;
	for (const auto& worker : workers)
		allDone &= worker->isStopped();

	return allDone;
}

void TaskManager::stopFreeWorkers() {
	for (const auto& worker : workers)
		if (!worker->isStopped() && worker->isFree())
			worker->stop();
}
