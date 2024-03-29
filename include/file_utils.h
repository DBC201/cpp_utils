#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <fstream>
#include <vector>
#include <iostream>
#include <string>

/*
	std::fstream::in read
	std::fstream::out write
	std::fstream::app append
	std::fstream::trunc truncate, force clear
	std::fstream::in | std::fstream::app
*/

namespace cpp_utils::file_utils {
	enum FileMode {
		READ = std::fstream::in,
		WRITE = std::fstream::out,
		APPEND = std::fstream::app,
		TRUNC = std::fstream::trunc
	};

	class FileUtils {
	public:
		FileUtils() = default;

		FileUtils(std::string file_path) {
			file.open(file_path, std::fstream::in);

			if (!file.is_open()) {
				throw std::runtime_error("Unable to open " + file_path);
			}
 		}

		FileUtils(std::string file_path, FileMode mode) {
			file.open(file_path, mode);
			if (!file.is_open()) {
				throw std::runtime_error("Unable to open " + file_path);
			}
		}

		std::string get_line() {
			std::string line;
			std::getline(file, line);
			return line;
		}

		bool is_open() {
			return file.is_open();
		}

		void open(std::string file_path) {
			file.open(file_path, std::fstream::in);
		}

		void open(std::string file_path, FileMode mode) {
			file.open(file_path, mode);
		}

		void process_lines(auto lambda) {
			std::string line;
			while (std::getline(file, line)) {
				lambda(line);
			}
		}

		void write(std::string str) {
			file << str;
		}

		void write(const std::vector<uint8_t>& data) {
			file.write(reinterpret_cast<const char*>(data.data()), data.size());
		}

		void close() {
			file.close();
		}

		~FileUtils() {
			close();
		}
	private:
		std::fstream file;
	};

	/**
	* @param file_path path to file to be read
	* @param container the container data type to contain parsed lines
	* @param lambda a lambda function that takes two arguments, line as string and container (container is taken as reference)
	*/
	void process_lines(std::string file_path, auto& container, auto lambda) {
		std::string line;
		std::fstream file;
		file.open(file_path, std::fstream::in);
		if (!file.is_open()) {
			// throw std::runtime_error("Unable to open " + file_path);
			std::cerr << "Unable to open " + file_path << std::endl;
			exit(EXIT_FAILURE);
		}
		while (std::getline(file, line)) {
			lambda(line, container);
		}
		file.close();
	}

	/**
	* @param file_path path to file to be read
	* @param lambda 
	*/
	void process_lines(std::string file_path, auto lambda) {
		std::string line;
		std::fstream file;
		file.open(file_path, std::fstream::in);
		if (!file.is_open()) {
			// throw std::runtime_error("Unable to open " + file_path);
			std::cerr << "Unable to open " + file_path << std::endl;
			exit(EXIT_FAILURE);
		}
		while (std::getline(file, line)) {
			lambda(line);
		}
		file.close();
	}

	/**
	* @param file_path path to file to be read
	* @param lambda takes line and returns parsed data to be added to final vector
	* @returns vector of given template type
	*/
	template <typename token>
	std::vector<token> get_lines(std::string file_path, auto lambda) {
		std::vector<token> return_val;
		std::string line;
		std::fstream file;
		file.open(file_path, std::fstream::in);
		if (!file.is_open()) {
			// throw std::runtime_error("Unable to open " + file_path);
			std::cerr << "Unable to open " + file_path << std::endl;
			exit(EXIT_FAILURE);
		}
		while (std::getline(file, line)) {
			return_val.push_back(lambda(line));
		}
		file.close();
		return return_val;
	}
} // cpp_utils::file_utils

#endif // FILE_UTILS_H
