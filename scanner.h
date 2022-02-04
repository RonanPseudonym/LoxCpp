#include "token.h"

class Scanner {
	private:
		std::string source;
	public:
		Scanner(std::string s) {
			source = s;
		}
		std::vector<Token> scan_tokens() {
			return std::vector<Token>();
		}
};