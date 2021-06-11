#include "token.h"

Token::Token(TokenType t, std::string lex, std::string str, double num, int l)
        : type{ t },
          lexeme{ std::move(lex) },
          str_literal{ std::move(str) },
          num_literal{ num },
          line{ l } {}

std::ostream& operator<<(std::ostream& out, const Token& token) {
    return out << token.line << "; " << token.type << "; " << token.lexeme << "; " << token.str_literal << "; "
               << token.num_literal << "\n";
}
