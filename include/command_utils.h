#ifndef COMMAND_UTILS_H
#define COMMAND_UTILS_H

#include <iostream>

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

namespace cpp_utils::command_utils {
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
} // utils::command_utils


#endif // COMMAND_UTILS_H
