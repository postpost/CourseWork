#include <vector>
#include <thread>
#include <queue>
#include <future>
#include <functional>
#include "thread_pool.h"

thread_pool::thread_pool(): done(false) {
	int cores = std::thread::hardware_concurrency();
	try {
		for (int i = 0; i < cores; ++i) { 
			threads.push_back(std::thread(&thread_pool::work, this));
		}
	}
	catch (...) {
		done = true;
		throw "Incorrect work...\n";
	}
}

//destructor
thread_pool::~thread_pool() {
	for (auto& el : threads) {
		//if (el.joinable())
			el.join();
	}
	done = true;
}

void thread_pool::work() {
	while (!done) {
		//
		std::function<void(void)> task; //сюда можно инкапсулировать функцию
		if (work_queue.try_pop(task)) { //если задача есть, извлекаем задачу
			task();						//выполняем задачу
		}
		else {
			std::this_thread::yield(); //если задач нет, берем перерыв
		}
	}
}