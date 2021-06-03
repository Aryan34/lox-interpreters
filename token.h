#ifndef LOX_INTERPRETERS_TOKEN_H
#define LOX_INTERPRETERS_TOKEN_H

#include <string>

#include "tokentype.h"

class Token {
public:
    Token(TokenType t, std::string lex, std::string str, double num, int l);

    TokenType getType() const;
    std::string getLexeme() const;
    std::string getStrLiteral() const;
    double getNumLiteral() const;
    int getLine() const;

    friend std::ostream& operator<<(std::ostream& out, const Token& token);

private:
    TokenType type;
    std::string lexeme;
    std::string str_literal;
    double num_literal;
    int line;
};

#endif //LOX_INTERPRETERS_TOKEN_H
