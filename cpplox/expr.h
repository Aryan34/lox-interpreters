#ifndef LOX_INTERPRETERS_EXPR_H
#define LOX_INTERPRETERS_EXPR_H

#include <memory>
#include <utility>

#include "token.h"

class Binary;
class Grouping;
class Literal;
class Unary;

class Visitor {
public:
    virtual LiteralVariant visitBinaryExpr(Binary& expr) = 0;
    virtual LiteralVariant visitGroupingExpr(Grouping& expr) = 0;
    virtual LiteralVariant visitLiteralExpr(Literal& expr) = 0;
    virtual LiteralVariant visitUnaryExpr(Unary& expr) = 0;
};

class Expr {
public:
    virtual ~Expr() = default;
    virtual LiteralVariant accept(Visitor& visitor) = 0;
};

class Binary : public Expr {
public:
    std::unique_ptr<Expr> left;
    Token& oper;
    std::unique_ptr<Expr> right;

    Binary(std::unique_ptr<Expr> left, Token& oper, std::unique_ptr<Expr> right) : left(std::move(left)),
                                                                                   oper(oper),
                                                                                   right(std::move(right)) {}

    LiteralVariant accept(Visitor& visitor) override {
        return visitor.visitBinaryExpr(*this);
    }
};

class Grouping : public Expr {
public:
    std::unique_ptr<Expr> expression;

    explicit Grouping(std::unique_ptr<Expr> expression) : expression(std::move(expression)) {}

    LiteralVariant accept(Visitor& visitor) override {
        return visitor.visitGroupingExpr(*this);
    }
};

class Literal : public Expr {
public:
    LiteralVariant value;

    explicit Literal(LiteralVariant value) : value{ std::move(value) } {}

    LiteralVariant accept(Visitor& visitor) override {
        return visitor.visitLiteralExpr(*this);
    }
};

class Unary : public Expr {
public:
    Token& oper;
    std::unique_ptr<Expr> right;

    Unary(Token& oper, std::unique_ptr<Expr> right) : oper{ oper }, right(std::move(right)) {}

    LiteralVariant accept(Visitor& visitor) override {
        return visitor.visitUnaryExpr(*this);
    }
};

#endif //LOX_INTERPRETERS_EXPR_H
