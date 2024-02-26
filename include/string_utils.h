#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <vector>
#include <sstream>
#include <string>
#include <iomanip>

namespace cpp_utils::string_utils {
	std::vector<std::string> split_by_string(std::string str, std::string delimeter) {
		std::vector<std::string> tokens;
		int start_index = str.find(delimeter);
		if (start_index == std::string::npos) {
			tokens.push_back(str);
		}
		else {
			while (start_index != -1) {
				tokens.push_back(str.substr(0, start_index));
				str = str.substr(start_index + delimeter.length());
				start_index = str.find(delimeter);
			}
			tokens.push_back(str);
		}
		return tokens;
	}

	std::vector<std::string> split(std::string str, char delimeter) {
		std::vector<std::string> tokens;
		std::stringstream ss(str);
		std::string token;
		while (getline(ss, token, delimeter)) {
			if (!token.empty())
				tokens.push_back(token);
		}
		return tokens;
	}

	std::string replace_substring(std::string str, std::string old_substring, std::string new_substring) {
		for (int i = 0; i < str.length(); i++) {
			if (str.substr(i, old_substring.length()) == old_substring) {
				str = str.substr(0, i) + new_substring + str.substr(i + old_substring.length());
				i--;
				i += new_substring.length();
			}
		}
		return str;
	}

	std::string flip(std::string str) {
		for (int i = 0; i < str.length() / 2; i++) {
			char temp = str[i];
			str[i] = str[str.length() - i - 1];
			str[str.length() - i - 1] = temp;
		}
		return str;
	}

	/*
	* @param str string to be converted into template type
	*/
	template <typename T>
	T convert_string(std::string str) 
	{
		T val;
		std::istringstream(str) >> val;
		return val;
	}

	template <typename T>
	T convert_hexadecimal(std::string str) {
		T val;
		std::istringstream(str) >> std::hex >> val;
		return val;
	}

	template <typename T>
	std::vector<T> convert_string_vector(std::vector<std::string> v) {
		std::vector<T> ret(v.size());
		for (int i = 0; i < ret.size(); i++) {
			ret[i] = convert_string<T>(v[i]);
		}
		return ret;
	}

	bool isLower(std::string s) {
		for (const auto& c: s) {
			if (!std::islower(c)) {
				return false;
			}
		}
		return true;
	}

	template <typename T>
	std::vector<T> string_to_vector(std::string str) {
		return convert_string_vector<T>(split_by_string(str, ","));
	}

	template <typename T>
	std::string vector_to_string(std::vector<T> v) {
		std::string str;
		for (int i=0; i<v.size(); i++) {
			str += std::to_string(v[i]);
			if (i != v.size()-1) {
				str += ",";
			}
		}

		return str;
	}

	std::string vector_to_string(std::vector<std::string> v) {
		std::string str;
		for (int i=0; i<v.size(); i++) {
			str += v[i];
			if (i != v.size()-1) {
				str += ",";
			}
		}

		return str;
	}

	template <typename T>
	std::string pad(T val, unsigned int zeros) {
		std::ostringstream oss;
		oss << std::setw(zeros) << std::setfill('0') << val;
		return oss.str();
	}
} // cpp_utils::string_utils

#endif // STRING_UTILS_H
