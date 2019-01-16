#include <iostream>
#include <vector>
#include <cstdint>
#include <chrono>
#include <thread>
#include <algorithm>
#include <iterator>
#include <future>
#include <numeric>

namespace {
const int THREAD_COUNT = 4;
const uint64_t SIZE = 6 * (2 << 20);
}

template <typename T>
void PrintVector(const std::vector<T> & vec)
{
	for (const auto & elem : vec)
		std::cout << elem << " ";
	std::cout << std::endl;
}

void GenerateVector(std::vector<int> & input, uint64_t size, int seed = 13)
{
	std::srand(seed);

	input.reserve(size);
	for (uint64_t idx = 0; idx < size; ++idx)
		input.push_back(std::rand() % 10);
}

uint64_t Sum(const std::vector<int>::const_iterator & begin, const std::vector<int>::const_iterator & end)
{
	return std::accumulate(begin, end, static_cast<uint64_t>(0));
}

void ThreadFunc(const std::vector<int>::const_iterator begin, const std::vector<int>::const_iterator end, uint64_t & result)
{
	result = Sum(begin, end);
}

uint64_t ThreadSum(const std::vector<int> & input)
{
	std::vector <std::thread> threadPool;
	std::vector <uint64_t> sums(THREAD_COUNT);

	auto piece = std::distance(input.begin(), input.end()) / THREAD_COUNT;
	
	for (int i = 0; i < THREAD_COUNT; ++i)
		threadPool.push_back(std::thread(ThreadFunc, input.cbegin() + piece * i, input.cbegin() + piece * (i + 1), std::ref(sums[i])));

	for (auto & thread : threadPool)
		thread.join();

	uint64_t result = 0;
	for (const auto & elem : sums)
		result += elem;

	return result;
}

int main()
{
	std::vector<int> numbers;
	GenerateVector(numbers, SIZE);
	// PrintVector(randomNumbers);

	auto start = std::chrono::high_resolution_clock::now();
	const auto seqResult = Sum(numbers.cbegin(), numbers.cend());
	auto end = std::chrono::high_resolution_clock::now();

	std::cout << "Sequential sum: " 
				<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
				<< " milliseconds" << std::endl
				<< "result :" << seqResult << std::endl;

	start = std::chrono::high_resolution_clock::now();
	const auto threadResult = ThreadSum(numbers);
	end = std::chrono::high_resolution_clock::now();

	std::cout << "Parallel sum: " 
				<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
				<< " milliseconds" << std::endl
				<< "result :" << threadResult << std::endl;

	return 0;
}
