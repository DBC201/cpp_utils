#ifndef TIMER_UTILS_H
#define TIMER_UTILS_H

#include <chrono>

namespace cpp_utils::timer_utils {
	class Timer{
	public:
		Timer() = default;
	
		void start() {
			start_time = std::chrono::high_resolution_clock::now();
		}

		void stop() {
			end_time = std::chrono::high_resolution_clock::now();
		}

		uint64_t get_nanoseconds() {
			return std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
		}

		uint64_t get_miliseconds() {
			return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
		}
	private:
		std::chrono::steady_clock::time_point start_time;
		std::chrono::steady_clock::time_point end_time;
	};
} // cpp_utils::timer_utils

#endif TIMER_UTILS_H
