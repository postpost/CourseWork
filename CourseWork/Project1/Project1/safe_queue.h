#pragma once
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <functional>

template <typename T>
class safe_queue
{
private:
	std::mutex m; //для реализации блокировки
	std::queue<T> data_queue; //для хранения задач
	std::condition_variable data_cond;//для уведомлений
public:
	safe_queue(){};
	safe_queue(const safe_queue& other) {
		std::lock_guard lk(other.m);
		data_queue = other.data_queue;
	};
	//запрет оператора присваивания
	safe_queue& operator=(const safe_queue&) = delete;
	
	// push записывает в начало очереди новую задачу. 
	void push(T new_task) {
		std::lock_guard lk(m);
		data_queue.push(new_task);
		data_cond.notify_all();
	}
	
	//находится в ожидании, пока не придёт уведомление на условную переменную. 
	void pop(T& task) {
		while (true) {
			std::unique_lock lk(m);
			data_cond.wait(lk, []() {
				return !data_queue.empty();
				});
		}
		task = data_queue.front();
		data_queue.pop();
	}

	bool try_pop(T& task) {
		std::lock_guard lk(m);
		if (data_queue.empty())
			return false;
		task = data_queue.front();
		data_queue.pop();
		return true;
	}
};

