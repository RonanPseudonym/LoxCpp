#include "token_type.h"

class Token {
	private:
		TokenType   type;
		std::string lexeme;
		char        literal; // Fix this later
		int         line;

	public:
		Token(TokenType type, std::string lexeme, char literal, int line) {
			this->type    = type;
			this->lexeme  = lexeme;
			this->literal = literal;
			this->line    = line;
		}

		void print() {
			printf("%d %s %c", type, lexeme.c_str(), literal);
		}
};