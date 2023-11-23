#pragma once
#include <vector>
#include <thread>
#include <queue>
#include <future>
#include <functional>
#include "safe_queue.h"

using namespace std::chrono_literals;

class thread_pool {
private:
	//—ледует отметить важность пор€дка объ€влени€ компонентов: и флаг done, и очередь 
	//worker_queue должны быть объ€влены до вектора потоков threads,
	// “ем самым будет гарантировано удаление 
	//компонентов в правильном пор€дке : к примеру, невозможно безопасно удалить
	//очередь, пока не будут остановлены все потоки.
	std::atomic_bool done;
	std::mutex m;
	safe_queue <std::function<void(void)>> work_queue; //потокобезопасна€ очередь задач
	std::vector <std::thread> threads; //вектор рабочих потоков
public:
	//constructor
	thread_pool() {};
	thread_pool(int cores);
	/*template <typename T>
	thread_pool(T func) {
		int cores = std::thread::hardware_concurrency() - 1;
		for (int i = 0; i < cores; ++i) {
			std::this_thread::sleep_for(1000ms);
			std::lock_guard lk(m);
			submit(func);
		}
	};*/
	//destructor
	~thread_pool();
	// work() выбирает из очереди очередную задачу и исполн€ет еЄ. 
	// Ётот метод передаЄтс€ конструктору потоков дл€ исполнени€;
	void work();
	//submit() помещает в очередь задачу. 
	template <typename T>
	void submit(T func) {
		work_queue.push(std::function<void()>(func));
	}
};



