#ifndef COORDINATE_UTILS_H
#define COORDINATE_UTILS_H

#include "string_utils.h"
#include "set_utils.h"
#include <unordered_map>

namespace cpp_utils::coordinate_utils {
	namespace two_dimensional {
		enum direction_t {
			NORTH,
			EAST,
			SOUTH,
			WEST,
			NUM_DIRECTIONS
		};

		direction_t flip_direction(direction_t direction, float degrees) {
			int direction_change = round(degrees/(360/static_cast<float>(NUM_DIRECTIONS)));
			direction_change %= NUM_DIRECTIONS;
			if (direction_change < 0) {
				direction_change += static_cast<int>(NUM_DIRECTIONS);
			}

			return static_cast<direction_t>((static_cast<int>(direction) + direction_change) % static_cast<int>(NUM_DIRECTIONS));
		}

		template <typename T = size_t>
		bool in_bounds(std::vector<T> coordinate, T y_max, T x_max, T y_min=0, T x_min=0) {
			return coordinate[0] >= y_min && coordinate[0] < y_max && coordinate[1] >= x_min && coordinate[1] < x_max;
		}

		template <typename T = size_t>
		std::vector<T> move(std::vector<T> coordinate, direction_t direction, T disposition=1) {
			switch(direction) {
			case NORTH:
				coordinate[0] -= disposition;
				break;
			case WEST:
				coordinate[1] -= disposition;
				break;
			case SOUTH:
				coordinate[0] += disposition;
				break;
			case EAST:
				coordinate[1] += disposition;
				break;
			default:
				throw std::runtime_error("Invalid direction");
				break;
			}

			return coordinate;
		}
	};
	template <typename T = size_t>
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
