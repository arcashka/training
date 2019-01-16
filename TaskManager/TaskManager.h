#pragma once

#include <memory>
#include <vector>

class Task;

class TaskManager
{
public:
	TaskManager() {}
	void addTask(std::shared_ptr<Task> task);
	void execute();

private:
	std::vector<std::shared_ptr<Task>> tasks;
};
