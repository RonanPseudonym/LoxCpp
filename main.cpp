#include <iostream>
#include <fstream>
#include <vector>

#include "scanner.h"

void run(std::string data) {
	Scanner scanner = Scanner(data);
	std::vector<Token> tokens = scanner.scan_tokens();

	for (int i = 0; i < tokens.size(); i ++) {
		tokens[i].print();
	}
}

void run_prompt() {
	std::string line;

	for (;;) {
		std::cout << "> ";
		std::getline(std::cin, line);

		if (line.empty())
			break;

		run(line);
		line = "";

		if (error) {
			return;
		}
	}
}

void run_file(std::string file_name) {
	std::ifstream stream (file_name, std::ios::in);
	std::istreambuf_iterator<char> eos;
	std::string data(std::istreambuf_iterator<char>(stream), eos);

   	run(data);
}

// void report(int line, std::string where, std::string message) {
// 	std::cout << "[line " << line << "] Error" << where << ": " << message;
// }

// void error(int line, std::string message) {
// 	report(line, "", message);
// 	had_error = true;
// }

int main(int argc, char *argv[]) {
	setup_kwd_names();

	if (argc > 2) {
		throw std::invalid_argument("Too many arguments specified");
	} else if (argc == 2) {
		run_file((std::string)argv[1]);
	} else {
		run_prompt();
	}
}