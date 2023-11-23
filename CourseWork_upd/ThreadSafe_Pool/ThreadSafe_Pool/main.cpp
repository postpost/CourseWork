#include <iostream>
#include <queue>
#include <vector>
#include <mutex>
#include "thread_pool.h"


void func1() {
	std::cout << "Working " << __FUNCTION__ << "...\n";
}
void func2() {
	std::cout << "Working " << __FUNCTION__ << "...\n";
}

void submit(thread_pool& thread, std::function<void(void)> func) {
	thread.submit(func);
}
int main() {

	int cores = std::thread::hardware_concurrency() - 1;
	thread_pool th1(cores);
	th1.submit(func1);
	th1.submit(func2);
	
	return 0;
}
