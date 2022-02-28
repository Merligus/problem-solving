#include <iostream>
#include <vector>

#include <atomic>
#include <mutex>
#include <thread>

#include <ctime>

class CustomObject
{
public:
	std::atomic<unsigned long long int > variable;
	int index;

	CustomObject(int index, unsigned long long int  variable);

};

CustomObject::CustomObject(int index, unsigned long long int  variable)
{
	this->variable = variable;
	this->index = index;
}

std::mutex mtx;

void increase_reference(CustomObject& variable, unsigned long long int n)
{
	// mtx.lock();
	for (int i = 0; i < n; ++i)
		++variable.variable;
	// mtx.unlock();
}

int main_Thread()
{
	time_t timer1, timer2;

	std::vector<std::thread> threads;

	CustomObject foo(0, 0);
	time(&timer1);
	for (int i = 1; i <= 4; ++i)
		threads.push_back(std::thread(increase_reference, std::ref(foo), 100000000));

	for (auto& th : threads)
		th.join();
	time(&timer2);

	std::cout << foo.variable << ' ' << difftime(timer2, timer1) << "\n";

	return 0;
}