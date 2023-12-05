#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#include <vector>

namespace cpp_utils::vector_utils {
	void remove_element(auto& v, auto e) {
		for (auto it=v.begin(); it!=v.end(); it++) {
			if (*it == e) {
				it = v.erase(it);
			}
		}
	}

} // cpp_utils::vector_utils


#endif // VECTOR_UTILS_H
