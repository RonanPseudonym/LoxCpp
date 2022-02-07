#include <iostream>

static bool error = false;

class Error {
	public:
		Error(std::string text, int line) {
			std::cout << "[line " << line << "] Error" << ": " << text;
			error = true;
		}
};