#ifndef LOX_INTERPRETERS_TOKEN_H
#define LOX_INTERPRETERS_TOKEN_H

#include <string>

#include "tokentype.h"

class Token {
public:
    TokenType type;
    std::string lexeme;
    std::string str_literal;
    double num_literal;
    int line;

    Token(TokenType t, std::string lex, std::string str, double num, int l);

    friend std::ostream& operator<<(std::ostream& out, const Token& token);
};

#endif //LOX_INTERPRETERS_TOKEN_H
