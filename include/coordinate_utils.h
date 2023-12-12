#ifndef COORDINATE_UTILS_H
#define COORDINATE_UTILS_H

#include "string_utils.h"
#include <unordered_set>

namespace cpp_utils::coordinate_utils {
	template <typename T>
	class CoordinateCache {
	public:
		CoordinateCache() = default;

		void insert(std::vector<T> coordinate) {
			std::string coordinate_str = cpp_utils::string_utils::vector_to_string<T>(coordinate);
			cache.insert(coordinate_str);
		}

		bool contains(std::vector<T> coordinate) {
			std::string coordinate_str = cpp_utils::string_utils::vector_to_string<T>(coordinate);
			return cache.contains(coordinate_str);
		}

		void erase(std::vector<T> coordinate) {
			std::string coordinate_str = cpp_utils::string_utils::vector_to_string<T>(coordinate);
			cache.erase(coordinate_str);	
		}

		size_t size() {
			return cache.size();
		}

		std::unordered_set<std::string> get_cache() {
			return cache;
		}

		void clear() {
			cache.clear();
		}
	private:
		std::unordered_set<std::string> cache;
	};
} // cpp_utils::coordinate_utils

#endif // COORDINATE_UTILS_H
