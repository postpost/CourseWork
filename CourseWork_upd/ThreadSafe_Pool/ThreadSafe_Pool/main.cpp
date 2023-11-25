#include <iostream>
#include <queue>
#include <vector>
#include <mutex>
#include "thread_pool.h"

using namespace std::chrono_literals;

void func1() {
	std::cout << "Working " << __FUNCTION__ << "...\n";
}
void func2() {
	std::cout << "Working " << __FUNCTION__ << "...\n";
}

int main() {

	int cores = std::thread::hardware_concurrency() - 1;
	thread_pool th1;
	for (int i = 0; i < cores; ++i) {
		th1.submit(func1);
		//std::this_thread::sleep_for(1000ms);
		th1.submit(func2);
	}
	return 0;
}
