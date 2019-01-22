#pragma once

#include <thread>
#include <vector>
#include <memory>

#include "blockingQueue.h"

class Task;

class Worker
{
public:
	Worker(const std::string name, const size_t max);
	bool tryAddTask(std::shared_ptr<Task> task);
	void stop();
	bool isStopped();
	bool isFree();

private:
	void execute();

private:
	std::thread thread;
	const std::string name;
	const size_t max;
	bool stopped;
	BlockingQueue<std::shared_ptr<Task>> tasks;
};
