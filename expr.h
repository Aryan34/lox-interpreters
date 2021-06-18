#ifndef LOX_INTERPRETERS_EXPR_H
#define LOX_INTERPRETERS_EXPR_H

#include <memory>
#include <utility>

#include "token.h"

// TODO: Figure out the best way to deal with different return types for visitor pattern functions

class Binary;
class Grouping;
class Literal;
class Unary;

class Visitor {
public:
    virtual std::variant<std::monostate, std::string, double, bool> visitBinaryExpr(Binary& expr) = 0;
    virtual std::variant<std::monostate, std::string, double, bool> visitGroupingExpr(Grouping& expr) = 0;
    virtual std::variant<std::monostate, std::string, double, bool> visitLiteralExpr(Literal& expr) = 0;
    virtual std::variant<std::monostate, std::string, double, bool> visitUnaryExpr(Unary& expr) = 0;
};

class Expr {
public:
    virtual ~Expr() = default;
    virtual std::variant<std::monostate, std::string, double, bool> accept(Visitor& visitor) = 0;
};

class Binary : public Expr {
public:
    std::unique_ptr<Expr> left;
    Token& oper;
    std::unique_ptr<Expr> right;

    Binary(std::unique_ptr<Expr> left, Token& oper, std::unique_ptr<Expr> right) : left(std::move(left)),
                                                                                   oper(oper),
                                                                                   right(std::move(right)) {}

    std::variant<std::monostate, std::string, double, bool> accept(Visitor& visitor) override {
        return visitor.visitBinaryExpr(*this);
    }
};

class Grouping : public Expr {
public:
    std::unique_ptr<Expr> expression;

    explicit Grouping(std::unique_ptr<Expr> expression) : expression(std::move(expression)) {}

    std::variant<std::monostate, std::string, double, bool> accept(Visitor& visitor) override {
        return visitor.visitGroupingExpr(*this);
    }
};

class Literal : public Expr {
public:
    std::variant<std::monostate, std::string, double, bool> value;

    explicit Literal(std::variant<std::monostate, std::string, double, bool> value) : value{ std::move(value) } {}

    std::variant<std::monostate, std::string, double, bool> accept(Visitor& visitor) override {
        return visitor.visitLiteralExpr(*this);
    }
};

class Unary : public Expr {
public:
    Token& oper;
    std::unique_ptr<Expr> right;

    Unary(Token& oper, std::unique_ptr<Expr> right) : oper{ oper }, right(std::move(right)) {}

    std::variant<std::monostate, std::string, double, bool> accept(Visitor& visitor) override {
        return visitor.visitUnaryExpr(*this);
    }
};

#endif //LOX_INTERPRETERS_EXPR_H
