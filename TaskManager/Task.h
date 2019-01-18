#pragma once

#include <memory>
#include <functional>

class Task
{
public:
	Task(const std::function<void(void)>& lambda)
		: callableFunction(lambda)
	{
	}
	~Task() = default;
	void execute() const { callableFunction(); }

private:
	const std::function<void(void)> callableFunction;
};

template<typename T, class... Args>
std::unique_ptr<Task> createTask(const T &lambda, Args... args)
{
	const auto func = std::bind(lambda, args...);
	return std::make_unique<Task>(func);
}
