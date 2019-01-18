#pragma once

#include <mutex>
#include <memory>
#include <queue>

template <typename T>
class BlockingQueue : public std::queue<T>
{
public:
	T pop() {
		mutex.lock();
		auto temp = std::queue<T>::front();
		std::queue<T>::pop();
		mutex.unlock();
		return temp;
	}

	void add(T value) {
		mutex.lock();
		std::queue<T>::push(value);
		mutex.unlock();
	}

private:
	std::mutex mutex;
};
