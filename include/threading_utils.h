#ifndef THREADING_UTILS_H
#define THREADING_UTILS_H

#include <thread>
#include <vector>
#include <condition_variable>
#include <queue>
#include <functional>
#include <iostream>

namespace cpp_utils::threading_utils {
	class ThreadPool {
	public:
		std::mutex m;
		ThreadPool() {
			thread_count = std::thread::hardware_concurrency();
			initThreads();
		}

		ThreadPool(uint8_t thread_count) {
			this->thread_count = thread_count;
			initThreads();
		}

		template <class F, class... Args>
		void enqueue(F&& func, Args&&... args) {
			{
				std::unique_lock<std::mutex> lock(m);

				if (stop) {
					return;
				}

				q.emplace(std::bind(func, args...));
			}

			newTask.notify_one();
		}

		void wait() {
			std::unique_lock<std::mutex> lock(m);
			allWaiting.wait(lock, [&]{return running_task_count == 0 && q.empty();});
		}

		~ThreadPool() {
			{
				std::unique_lock<std::mutex> lock(m);
				stop = true;
			}

			newTask.notify_all();

			for (std::thread& thread : threads) {
				thread.join();
			}
		}
	private:
		std::vector<std::thread> threads;
		std::condition_variable newTask;
		std::condition_variable allWaiting;
		std::queue<std::function<void()>> q;
		uint16_t running_task_count = 0;
		bool stop = false;
		uint16_t thread_count;

		void initThreads() {
			for (int i=0; i<thread_count; i++) {
				threads.emplace_back([this] {worker();});
			}
		}

		void worker() {
			bool first_run = true;
			while (true) {
				std::function<void()> job;
				{
					std::unique_lock<std::mutex> lock(m);

					if (!first_run) {
						running_task_count--;
						if (running_task_count == 0 && q.empty()) {
							allWaiting.notify_all();
						}
					}

					newTask.wait(lock, [&]{return stop || !q.empty(); });

					if (stop) {
						return;
					}

					job = std::move(q.front());
					q.pop();
					running_task_count++;
					if (!first_run && !q.empty() && running_task_count < thread_count) {
						newTask.notify_one();
					}
					else {
						first_run = false;
					}
				}

				job();
			}
		}
	};
} // cpp_utils::threading_utils

#endif // THREADING_UTILS_H
