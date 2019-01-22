#pragma once

#include <memory>
#include <vector>
#include <mutex>

#include "worker.h"

class Task;

class TaskManager
{
public:
	TaskManager();
	void addTask(std::shared_ptr<Task> task);
	bool isFinished();

private:
	void stopFreeWorkers();

private:
	std::vector<std::unique_ptr<Worker>> workers;
	std::thread thread;
};
