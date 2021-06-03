#include <cmath>

#include "token.h"

Token::Token(TokenType t, std::string lex, std::string str, double num, int l)
        : type{ t },
          lexeme{ std::move(lex) },
          str_literal{ std::move(str) },
          num_literal{ num },
          line{ l } {}

TokenType Token::getType() const {
    return this->type;
}

std::string Token::getLexeme() const {
    return this->lexeme;
}

std::string Token::getStrLiteral() const {
    return this->str_literal;
}

double Token::getNumLiteral() const {
    return this->num_literal;
}

int Token::getLine() const {
    return this->line;
}

std::ostream& operator<<(std::ostream& out, const Token& token) {
    return out << token.line << "; " << token.type << "; " << token.lexeme << "; " << token.str_literal << "; "
               << token.num_literal << "\n";
}
