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

	bool vector_equal(auto& a, auto& b) {
		if (a.size() != b.size()) {
			return false;
		}

		for (int i=0; i<a.size(); i++) {
			if (a[i] != b[i]) {
				return false;
			}
		}
		return true;
	}

} // cpp_utils::vector_utils


#endif // VECTOR_UTILS_H
