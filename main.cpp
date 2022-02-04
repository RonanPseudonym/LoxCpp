#include <iostream>
#include <fstream>
#include <vector>

#include "scanner.h"

static bool had_error = false;

void run(std::string data) {
	Scanner scanner = Scanner(data);
	std::vector<Token> tokens = scanner.scan_tokens();

	// for (int i = 0; i < tokens.size(); i ++) {
	// 	std::cout << tokens[i] << "\n";
	// }
}

void run_prompt() {
	std::string line;

	for (;;) {
		std::cout << "> ";
		std::cin >> line;

		if (line.empty())
			break;

		run(line);
		line = "";

		if (had_error) {
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

void report(int line, std::string where, std::string message) {
	std::cout << "[line " << line << "] Error" << where << ": " << message;
}

void error(int line, std::string message) {
	report(line, "", message);
	had_error = true;
}

int main(int argc, char *argv[]) {
	if (argc > 2) {
		throw std::invalid_argument("Too many arguments specified");
	} else if (argc == 2) {
		run_file((std::string)argv[1]);
	} else {
		run_prompt();
	}
}