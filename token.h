#include "token_type.h"
#include <map>

std::map<TokenType, std::string> kwd_names;

void setup_kwd_names() {
	kwd_names[TokenType::AND] = "AND";
	kwd_names[TokenType::CLASS] = "CLASS";
	kwd_names[TokenType::ELSE] = "ELSE";
	kwd_names[TokenType::_FALSE] = "FALSE";
	kwd_names[TokenType::FOR] = "FOR";
	kwd_names[TokenType::FUN] = "FUN";
	kwd_names[TokenType::IF] = "IF";
	kwd_names[TokenType::NIL] = "NIL";
	kwd_names[TokenType::OR] = "OR";
	kwd_names[TokenType::PRINT] = "PRINT";
	kwd_names[TokenType::RETURN] = "RETURN";
	kwd_names[TokenType::SUPER] = "SUPER";
	kwd_names[TokenType::THIS] = "THIS";
	kwd_names[TokenType::_TRUE] = "TRUE";
	kwd_names[TokenType::VAR] = "VAR";
	kwd_names[TokenType::WHILE] = "WHILE";
	kwd_names[TokenType::_EOF] = "EOF";
	kwd_names[TokenType::LEFT_PAREN] = "LEFT_PAREN";
	kwd_names[TokenType::RIGHT_PAREN] = "RIGHT_PAREN";
	kwd_names[TokenType::LEFT_BRACE] = "LEFT_BRACE";
	kwd_names[TokenType::RIGHT_BRACE] = "RIGHT_BRACE";
	kwd_names[TokenType::COMMA] = "COMMA";
	kwd_names[TokenType::DOT] = "DOT";
	kwd_names[TokenType::MINUS] = "MINUS";
	kwd_names[TokenType::PLUS] = "PLUS";
	kwd_names[TokenType::SEMICOLON] = "SEMICOLON";
	kwd_names[TokenType::SLASH] = "SLASH";
	kwd_names[TokenType::STAR] = "STAR";
	kwd_names[TokenType::BANG] = "BANG";
	kwd_names[TokenType::BANG_EQUAL] = "BANG_EQUAL";
	kwd_names[TokenType::EQUAL] = "EQUAL";
	kwd_names[TokenType::EQUAL_EQUAL] = "EQUAL_EQUAL";
	kwd_names[TokenType::GREATER] = "GREATER";
	kwd_names[TokenType::GREATER_EQUAL] = "GREATER_EQUAL";
	kwd_names[TokenType::LESS] = "LESS";
	kwd_names[TokenType::LESS_EQUAL] = "LESS_EQUAL";
	kwd_names[TokenType::IDENTIFIER] = "IDENTIFIER";
	kwd_names[TokenType::STRING] = "STRING";
	kwd_names[TokenType::NUMBER] = "NUMBER";
	kwd_names[TokenType::_EOF] = "EOF";

}

class Object {
	private:
		std::string inside_str;
		double inside_double;
		char type;

	public:
		std::string to_string() {
			if (type == 's')
				return inside_str;
			else if (type == 'd')
				return std::to_string(inside_double);
			else
				return inside_str;
		}

		Object() {};

		Object(double dbl) {
			inside_double = dbl;
			type = 'd';
		}

		Object(std::string str) {
			inside_str = str;
			type = 's';
		}
};

class Token {
	private:
		TokenType   type;
		std::string lexeme;
		Object      literal;
		int         line;

	public:
		Token(TokenType type, std::string lexeme, Object literal, int line) {
			this->type    = type;
			this->lexeme  = lexeme;
			this->literal = literal;
			this->line    = line;
		}

		void print() {
			printf("%s %s %s\n", kwd_names.at(type).c_str(), lexeme.c_str(), literal.to_string().c_str());
		}
};