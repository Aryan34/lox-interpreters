#include <algorithm>

#include "parser.h"
#include "lox.cpp"

std::unique_ptr<Expr> Parser::expression() {
    return equality();
}

std::unique_ptr<Expr> Parser::equality() {
    std::unique_ptr<Expr> expr = comparison();

    while (match(std::initializer_list<TokenType>{ TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL })) {
        Token oper = previous();
        std::unique_ptr<Expr> right = comparison();
        expr = std::make_unique<Binary>(std::move(expr), &oper, std::move(right));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::comparison() {
    std::unique_ptr<Expr> expr = term();

    while (match(std::initializer_list<TokenType>{ TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS,
                                                   TokenType::LESS_EQUAL })) {
        Token oper = previous();
        std::unique_ptr<Expr> right = term();
        expr = std::make_unique<Binary>(std::move(expr), &oper, std::move(right));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::term() {
    std::unique_ptr<Expr> expr = factor();

    while (match(std::initializer_list<TokenType>{ TokenType::MINUS, TokenType::PLUS })) {
        Token oper = previous();
        std::unique_ptr<Expr> right = factor();
        expr = std::make_unique<Binary>(std::move(expr), &oper, std::move(right));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::factor() {
    std::unique_ptr<Expr> expr = unary();

    while (match(std::initializer_list<TokenType>{ TokenType::SLASH, TokenType::STAR })) {
        Token oper = previous();
        std::unique_ptr<Expr> right = unary();
        expr = std::make_unique<Binary>(std::move(expr), &oper, std::move(right));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::unary() {
    if (match(std::initializer_list<TokenType>{ TokenType::BANG, TokenType::MINUS })) {
        Token oper = previous();
        std::unique_ptr<Expr> right = unary();
        return std::make_unique<Unary>(&oper, std::move(right));
    }
    return primary();
}

std::unique_ptr<Expr> Parser::primary() {
    // TODO: Create new Literal classes for booleans and null (or find a better way to deal with them)
    if (match(std::initializer_list<TokenType>{ TokenType::FALSE })) { return std::make_unique<NumLiteral>(0); }
    if (match(std::initializer_list<TokenType>{ TokenType::TRUE })) { return std::make_unique<NumLiteral>(1); }
    if (match(std::initializer_list<TokenType>{ TokenType::NIL })) { return std::make_unique<NumLiteral>(-1); }

    if (match(std::initializer_list<TokenType>{ TokenType::NUMBER })) {
        return std::make_unique<NumLiteral>(previous().num_literal);
    }

    if (match(std::initializer_list<TokenType>{ TokenType::STRING })) {
        return std::make_unique<StrLiteral>(previous().str_literal);
    }

    if (match(std::initializer_list<TokenType>{ TokenType::LEFT_PAREN })) {
        std::unique_ptr<Expr> expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return std::make_unique<Grouping>(std::move(expr));
    }

    error(peek(), "Unrecognized primary expression");
    throw "Parse Error";
}

bool Parser::match(std::initializer_list<TokenType> types) {
    return std::any_of(types.begin(), types.end(), [this](TokenType type) { return check(type); });
}

bool Parser::check(TokenType type) {
    if (isAtEnd() or peek().type != type) { return false; }
    advance();
    return true;
}

bool Parser::isAtEnd() {
    return peek().type == TokenType::END_FILE;
}

Token Parser::advance() {
    if (!isAtEnd()) { ++current; }
    return previous();
}

Token Parser::peek() {
    return tokens.at(current);
}

Token Parser::previous() {
    return tokens.at(current - 1);
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) return advance();
    error(peek(), message);
    throw "Parse Error";
}
