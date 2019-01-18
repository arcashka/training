#include <vector>
#include <iostream>
#include <string>

#include "taskManager.h"
#include "task.h"

int main()
{
	TaskManager manager;
	manager.addTask(createTask([]{ std::cout << "task 1" << std::endl; }));
	manager.addTask(createTask([](const std::string& text, int taskNumber) {
		std::cout << text + " " + std::to_string(taskNumber) << std::endl;
	}, "task", 2));

	while(!manager.isFinished())
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

}
