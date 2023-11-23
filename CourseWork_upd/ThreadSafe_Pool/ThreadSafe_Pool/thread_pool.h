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
	//������� �������� �������� ������� ���������� �����������: � ���� done, � ������� 
	//worker_queue ������ ���� ��������� �� ������� ������� threads,
	// ��� ����� ����� ������������� �������� 
	//����������� � ���������� ������� : � �������, ���������� ��������� �������
	//�������, ���� �� ����� ����������� ��� ������.
	std::atomic_bool done;
	std::mutex m;
	safe_queue <std::function<void(void)>> work_queue; //���������������� ������� �����
	std::vector <std::thread> threads; //������ ������� �������
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
	// work() �������� �� ������� ��������� ������ � ��������� �. 
	// ���� ����� ��������� ������������ ������� ��� ����������;
	void work();
	//submit() �������� � ������� ������. 
	template <typename T>
	void submit(T func) {
		work_queue.push(std::function<void()>(func));
	}
};



