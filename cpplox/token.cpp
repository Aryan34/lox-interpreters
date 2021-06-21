#include "token.h"

#include <utility>

Token::Token(TokenType type, std::string lexeme, LiteralVariant literal, int line)
        : type{ type },
          lexeme{ std::move(lexeme) },
          literal { std::move(literal) },
          line{ line } {}

std::ostream& operator<<(std::ostream& out, const Token& token) {
    // TODO: print variant contents (possibly using visit)
    return out << token.line << "; " << token.type << "; " << token.lexeme << "\n";
}
