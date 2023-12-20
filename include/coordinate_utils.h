#ifndef COORDINATE_UTILS_H
#define COORDINATE_UTILS_H

#include "string_utils.h"
#include "set_utils.h"
#include <unordered_map>

namespace cpp_utils::coordinate_utils {
	template <typename T>
	class CoordinateCache {
	public:
		CoordinateCache() = default;

		CoordinateCache(CoordinateCache<T>& other) {
			cache = other.get_cache();
		}

		CoordinateCache(std::vector<std::vector<T>> coordinates) {
			insert(coordinates);
		}

		void insert(std::vector<std::vector<T>> coordinates) {
			for (auto coordinate: coordinates) {
				insert(coordinate);
			}
		}

		void insert(std::vector<T> coordinate) {
			std::string coordinate_str = cpp_utils::string_utils::vector_to_string<T>(coordinate);
			cache.insert({coordinate_str, coordinate});
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

		std::unordered_map<std::string, std::vector<T>> get_cache() {
			return cache;
		}

		std::vector<std::vector<T>> get_coordinate_vectors() {
			std::vector<std::vector<T>> v;
			for (const auto p: cache) {
				v.push_back(p.second);
			}
			return v;
		}

		void clear() {
			cache.clear();
		}

		bool operator==(CoordinateCache<T>& other) {
			auto c = other.get_cache();
			if (c.size() != cache.size()) {
				return false;
			}
			
			for (const auto& p: cache) {
				if (!c.contains(p.first)) {
					return false;
				}
			}
			return true;
   		}

		bool operator!=(CoordinateCache<T>& other) {
			return !(*this == other);
   		}

		void operator=(CoordinateCache<T>& other) {
			cache = other.get_cache();
		}
	private:
		std::unordered_map<std::string, std::vector<T>> cache;
	};
} // cpp_utils::coordinate_utils

#endif // COORDINATE_UTILS_H
