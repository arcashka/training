#include "worker.h"

#include "task.h"


Worker::Worker(const size_t max)
	: max(max)
	, running(false)
	, stopped(false)
{
	thread = std::thread(&Worker::execute, this);
}

bool Worker::tryAddTask(std::shared_ptr<Task> task) {
	if (tasks.size() >= max)
		return false;
	tasks.add(task);
	return true;
}

void Worker::run() {
	running = true;
	if (stopped)
	{
		stopped = false;
		thread.join();
	}
}

void Worker::stop() {
	stopped = true;
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
		if (running) {
			while (!tasks.empty())
				tasks.pop()->execute();
			running = false;
		}
		else {
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
}


