#ifndef COMMAND_UTILS_H
#define COMMAND_UTILS_H

#include <iostream>
#include <filesystem>

#ifdef _WIN32
#include <direct.h>
#define popen _popen
#define pclose _pclose
#else
#include <unistd.h>  // For chdir
#endif

namespace cpp_utils::command_utils {
	bool change_directory(const std::string& path) {
		return chdir(path.c_str()) == 0;
	}

	std::string get_current_directory() {
		std::filesystem::path cwd = std::filesystem::current_path();
		return cwd.string();
	}

	std::string run_command(std::string command) {
		std::string output = "";
		FILE *pipe = popen(command.c_str(), "r");
		if (!pipe) {
			return output;
		}

		char buffer[128];
		
		while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
			output += buffer;
		}

		pclose(pipe);

		return output;
	}
} // cpp_utils::command_utils


#endif // COMMAND_UTILS_H
