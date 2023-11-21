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

int main() {
	thread_pool th1(func1);
	//thread_pool th2(func2);
	thread_pool th3;
	//th.submit(func1);
	return 0;
}
