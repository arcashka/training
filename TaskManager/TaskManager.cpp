#include "TaskManager.h"
#include "Task.h"

void TaskManager::addTask(std::shared_ptr<Task> task)
{
	tasks.push_back(task);
}

void TaskManager::execute()
{
	for (auto & a : tasks)
		a->execute();
}
