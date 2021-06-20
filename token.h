#ifndef LOX_INTERPRETERS_TOKEN_H
#define LOX_INTERPRETERS_TOKEN_H

#include <string>
#include <variant>

#include "tokentype.h"

using LiteralVariant = std::variant<std::monostate, std::string, double, bool>;

class Token {
public:
    TokenType type;
    std::string lexeme;
    LiteralVariant literal;
    int line;

    Token(TokenType type, std::string lexeme, LiteralVariant literal, int line);

    friend std::ostream& operator<<(std::ostream& out, const Token& token);
};

#endif //LOX_INTERPRETERS_TOKEN_H
