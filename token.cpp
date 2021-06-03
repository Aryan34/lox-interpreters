#include <string>
#include <iostream>
#include "tokentype.cpp"

class Token {
private:
    TokenType type;
    std::string lexeme;
    std::string str_literal;
    double num_literal;
    int line;

    Token(TokenType t, std::string lex, std::string str, double num, int l) : type{ t },
                                                                              lexeme{ std::move(lex) },
                                                                              str_literal{ std::move(str) },
                                                                              num_literal{ num },
                                                                              line{ l }
    {
    }

    friend std::ostream& operator<<(std::ostream& out, const Token& token);
};

std::ostream& operator<<(std::ostream& out, const Token& token) {
    return out << token.type << " " << token.lexeme << " " << token.str_literal << token.num_literal << token.line << "\n";
}
