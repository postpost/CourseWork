#include <vector>
#include <thread>
#include <queue>
#include <future>
#include <functional>
#include "thread_pool.h"

thread_pool::thread_pool(int cores) : done(false) {
	//int cores = std::thread::hardware_concurrency() - 1;
	try {
		for (int i = 0; i < cores; ++i) {
			threads.push_back(std::thread(&thread_pool::work, std::move(this)));
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
		std::function<void(void)> task; //���� ����� ��������������� �������
		if (work_queue.try_pop(task)) { //���� ������ ����, ��������� ������
			task();						//��������� ������
		}
		else {
			std::this_thread::yield(); //���� ����� ���, ����� �������
		}
		if (work_queue.get_size() == 0) {
			done = true;
			return;
		}
			
	}
}