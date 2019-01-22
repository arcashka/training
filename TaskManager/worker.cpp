#include "worker.h"

#include "task.h"
#include <iostream>
#include <string>


Worker::Worker(const std::string name, const size_t max)
	: name(name)
	, max(max)
	, stopped(false)
{
	thread = std::thread(&Worker::execute, this);
}

bool Worker::tryAddTask(std::shared_ptr<Task> task) {
	if (tasks.size() >= max)
		return false;
	tasks.add(task);
	if (stopped) {
		stopped = false;
		thread = std::thread(&Worker::execute, this);
	}
	return true;
}

void Worker::stop() {
	stopped = true;
	thread.join();
}

bool Worker::isStopped()
{
	return stopped;
}

bool Worker::isFree()
{
	return tasks.empty();
}

void Worker::execute() {
	while (true)
	{
		if (stopped)
			return;

		while (!tasks.empty())
		{
			std::cout << "Running task on " + name + " worker" << std::endl;
			tasks.pop()->execute();
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}


