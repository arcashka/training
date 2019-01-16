#include <vector>
#include <iostream>
#include <string>

#include "TaskManager.h"
#include "Task.h"

int main()
{
	TaskManager manager;
	manager.addTask(createTask([]{ std::cout << "task 1" << std::endl; }));
	manager.addTask(createTask([](const std::string& text, int taskNumber) {
		std::cout << text + " " + std::to_string(taskNumber) << std::endl;
	}, "task", 2));
	manager.execute();
}
