#ifndef MATH_UTILS_H
#define MATH_UTILS_H

namespace cpp_utils::math_utils {
	template <typename T>
	T Euclid_GCD(T n1, T n2) {
		// a = b * c + r

		T a = std::max(n1, n2);
		T b = std::min(n1, n2);
		T r;

		while (b != 0) {
			r = a % b;
			a = b;
			b = r;
		}

		return a;
	} 

	template <typename T>
	T Euclid_GCD(std::vector<T> v) {
		if (v.empty()) {
			return 0;
		}
		else if (v.size() < 2) {
			return v[0];
		}

		T res = Euclid_GCD<T>(v[0], v[1]);

		for (int i=2; i<v.size(); v++) {
			res = Euclid_GCD<T>(res, v[i]);
		}
		
		return res;
	}

	template <typename T>
	T lcm(std::vector<T> v) {
		if (v.empty()) {
			return 0;
		}
		else if (v.size() < 2) {
			return v[0];
		}

		T res = (v[0] * v[1])/Euclid_GCD(v[0], v[1]);

		for (int i=2; i<v.size(); i++) {
			res = (res * v[i])/Euclid_GCD(res, v[i]);
		}

		return res;
	}

} // cpp_utils::math_utils

#endif // MATH_UTILS_H
