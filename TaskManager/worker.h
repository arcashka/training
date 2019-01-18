#pragma once

#include <thread>
#include <vector>
#include <memory>

#include "blockingQueue.h"

class Task;

class Worker
{
public:
	Worker(const size_t max);
	bool tryAddTask(std::shared_ptr<Task> task);
	void run();
	void stop();
	bool isFree();

private:
	void execute();

private:
	std::thread thread;
	const size_t max;
	bool running;
	bool stopped;
	BlockingQueue<std::shared_ptr<Task>> tasks;
};
