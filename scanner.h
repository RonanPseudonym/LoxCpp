#include "token.h"
#include <map>

class Scanner {
	private:
		std::string source;
		std::vector<Token> tokens;

		int start = 0;
		int current = 0;
		int line = 1;

		std::map<std::string, TokenType> keywords;

		bool is_at_end() {
			return current >= source.size();
		}

		char advance() {
			return source[current ++];
		}

		void add_token_raw(TokenType type, Object literal) { // Fix char literal later
			std::string text = source.substr(start, current - start);
			tokens.push_back(Token(type, text, literal, line));
		}

		void add_token(TokenType type) {
			add_token_raw(type, Object());
		}

		char peek() {
			if (is_at_end()) return '\0';
			return source[current];
		}

		bool match(char expected) {
			if (is_at_end()) return false;
			if (source[current] != expected) return false;

			current ++;
			return true;
		}

		void string() {
			while (peek() != '"' && !is_at_end()) {
				if (peek() == '\n') line ++;
				advance();
			}

			if (is_at_end()) {
				// Error unterminated string
				return;
			}

			advance();

			std::string value = source.substr(start + 1, (current - 1) - (start + 1)); // Could be the cause of potential issues
			add_token_raw(TokenType::STRING, Object(value));
		}

		char peek_next() {
			if (current + 1 >= source.size()) return '\0';
			return source[current + 1];
		}

		void number() {
			while (isdigit((unsigned char)peek())) advance();

			if (peek() == '.' && isdigit(peek_next())) {
				advance();

				while (isdigit((unsigned char)peek())) advance();
			}

			add_token_raw(TokenType::NUMBER, Object(stod(source.substr(start, current - start)))); // Might also cause problems, idk
		}

		bool is_alpha(char c) {
			return (c >= 'a' && c <= 'z') ||
				(c >= 'A' && c <= 'Z') ||
				c == '_';
		}

		bool is_alphanum(char c) {
			return is_alpha(c) || isdigit((unsigned char)c);
		}

		void identifier() {
			while (is_alphanum(peek())) advance();

			std::string text = source.substr(start, current - start);
			TokenType type;
			
			if (keywords.count(text))
				type = keywords.at(text); // fix in a sec
			else
				type = TokenType::IDENTIFIER;

			add_token(type);
		}

		void scan_token() {
			char c = advance();

			switch (c) {
				case '(': add_token(TokenType::LEFT_PAREN); break;
				case ')': add_token(TokenType::RIGHT_PAREN); break;
				case '{': add_token(TokenType::LEFT_BRACE); break;
				case '}': add_token(TokenType::RIGHT_BRACE); break;
				case ',': add_token(TokenType::COMMA); break;
				case '.': add_token(TokenType::DOT); break;
				case '-': add_token(TokenType::MINUS); break;
				case '+': add_token(TokenType::PLUS); break;
				case ';': add_token(TokenType::SEMICOLON); break;
				case '*': add_token(TokenType::STAR); break;
				case '!':
					add_token(match('=') ? BANG_EQUAL : BANG);
					break;
				case '=':
					add_token(match('=') ? EQUAL_EQUAL : EQUAL);
					break;
				case '<':
					add_token(match('=') ? LESS_EQUAL : LESS);
					break;
				case '>':
					add_token(match('=') ? GREATER_EQUAL : GREATER);
					break;
				case '/':
					if (match('/'))
						while (peek() != '\n' && !is_at_end()) 
							advance();
					else
						add_token(TokenType::SLASH);
					break;

				case '\r': 
				case '\t':
				case ' ':
					break;

				case '\n':
					line ++;
					break;

				case '"':
					string();
					break;

				default:
					if (isdigit((unsigned char)c))
						number();
					else if (is_alpha(c))
						identifier();
					else
						// Error unexpected character

					break;
			}
		}
	public:
		Scanner(std::string s) {
			source = s;

			keywords["and"]    = TokenType::AND;
			keywords["class"]  = TokenType::CLASS;
			keywords["else"]   = TokenType::ELSE;
			keywords["false"]  = TokenType::_FALSE;
			keywords["for"]    = TokenType::FOR;
			keywords["fun"]    = TokenType::FUN;
			keywords["if"]     = TokenType::IF;
			keywords["nil"]    = TokenType::NIL;
			keywords["or"]     = TokenType::OR;
			keywords["print"]  = TokenType::PRINT;
			keywords["return"] = TokenType::RETURN;
			keywords["super"]  = TokenType::SUPER;
			keywords["this"]   = TokenType::THIS;
			keywords["true"]   = TokenType::_TRUE;
			keywords["var"]    = TokenType::VAR;
			keywords["while"]  = TokenType::WHILE;
		}

		std::vector<Token> scan_tokens() {
			while (!is_at_end()) {
				start = current;
				scan_token();
			}

			tokens.push_back(Token(TokenType::_EOF, "", Object(), line));
			return tokens;
		}
};