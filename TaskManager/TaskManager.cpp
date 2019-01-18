#include "taskManager.h"
#include "task.h"

TaskManager::TaskManager() {
	for (int i = 0; i < 4; ++i)
		workers.emplace_back(std::make_unique<Worker>(3));
	workers.front()->run();
	thread = std::thread(&TaskManager::execute, this);
//	thread.join();
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
			std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void TaskManager::finish()
{
	finished = true;
}

void TaskManager::run()
{
	finished = false;
	thread.join();
}

bool TaskManager::isFinished()
{
	bool allDone = false;
	for (const auto& worker : workers)
		allDone &= worker->isFree();
	return allDone;
}

void TaskManager::execute()
{
	while (true) {
		for (auto & worker : workers) {
			if (worker->isFree())
				worker->stop();
			else
				worker->run();
		}
		if (finished)
			return;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
