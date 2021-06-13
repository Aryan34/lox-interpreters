#ifndef LOX_INTERPRETERS_PARSER_H
#define LOX_INTERPRETERS_PARSER_H

#include <vector>

#include "token.h"
#include "expr.h"

class Parser {
public:
    explicit Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {}

    std::unique_ptr<Expr> parse();

private:
    const std::vector<Token> tokens;
    int current = 0;

    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> comparison();
    std::unique_ptr<Expr> term();
    std::unique_ptr<Expr> factor();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> primary();

    bool match(std::initializer_list<TokenType> types);
    bool check(TokenType type);
    bool isAtEnd();

    Token advance();
    Token peek();
    Token previous();
    Token consume(TokenType type, const std::string& message);

    void synchronize();
};

#endif //LOX_INTERPRETERS_PARSER_H
