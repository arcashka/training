#pragma once

#include <type_traits>
#include <memory>
#include <functional>

class Task
{
public:
	Task(std::function<void(void)> lambda)
		: callableFunction(lambda)
	{
	}
	~Task() = default;
	void execute(){ callableFunction(); }

private:
	std::function<void(void)> callableFunction;
};

template<typename T, class... Args>
std::unique_ptr<Task> createTask(const T &lambda, Args... args)
{
	auto func = std::bind(lambda, args...);
	return std::make_unique<Task>(func);
}
