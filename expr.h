#ifndef LOX_INTERPRETERS_EXPR_H
#define LOX_INTERPRETERS_EXPR_H

#include <memory>

#include "token.h"

// TODO: Determine if its easier to use void functions or create new class to encapsulate returns

class Binary;
class Grouping;
class StrLiteral;
class NumLiteral;
class Unary;

class Visitor {
public:
    virtual void visitBinaryExpr(Binary& expr) = 0;
    virtual void visitGroupingExpr(Grouping& expr) = 0;
    virtual void visitStrLiteralExpr(StrLiteral& expr) = 0;
    virtual void visitNumLiteralExpr(NumLiteral& expr) = 0;
    virtual void visitUnaryExpr(Unary& expr) = 0;
};

class Expr {
public:
    virtual ~Expr() = default;
    virtual void accept(Visitor& visitor) = 0;
};

class Binary : Expr {
public:
    std::unique_ptr<Expr> left;
    Token* oper;
    std::unique_ptr<Expr> right;

    Binary(std::unique_ptr<Expr> left, Token* oper, std::unique_ptr<Expr> right) : left(std::move(left)),
                                                                                   oper(oper),
                                                                                   right(std::move(right)) {}

    void accept(Visitor& visitor) override {
        visitor.visitBinaryExpr(*this);
    }
};

class Grouping : Expr {
public:
    std::unique_ptr<Expr> expression;

    explicit Grouping(std::unique_ptr<Expr> expression) : expression(std::move(expression)) {}

    void accept(Visitor& visitor) override {
        return visitor.visitGroupingExpr(*this);
    }
};

class StrLiteral : Expr {
public:
    std::string value;

    explicit StrLiteral(std::string value) : value(std::move(value)) {}

    void accept(Visitor& visitor) override {
        return visitor.visitStrLiteralExpr(*this);
    }
};

class NumLiteral : Expr {
public:
    double value;

    explicit NumLiteral(double value) : value{ value } {}

    void accept(Visitor& visitor) override {
        return visitor.visitNumLiteralExpr(*this);
    }
};

class Unary : Expr {
public:
    Token oper;
    std::unique_ptr<Expr> right;

    Unary(Token oper, std::unique_ptr<Expr> right) : oper(std::move(oper)), right(std::move(right)) {}

    void accept(Visitor& visitor) override {
        return visitor.visitUnaryExpr(*this);
    }
};

#endif //LOX_INTERPRETERS_EXPR_H
