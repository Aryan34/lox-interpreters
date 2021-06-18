#ifndef LOX_INTERPRETERS_EXPR_H
#define LOX_INTERPRETERS_EXPR_H

#include <memory>

#include "token.h"

// TODO: Figure out the best way to deal with different return types for visitor pattern functions

class Binary;
class Grouping;
class StrLiteral;
class NumLiteral;
class Unary;

class Visitor {
public:
    virtual std::variant<std::monostate, std::string, double> visitBinaryExpr(Binary& expr) = 0;
    virtual std::variant<std::monostate, std::string, double> visitGroupingExpr(Grouping& expr) = 0;
    virtual std::variant<std::monostate, std::string, double> visitStrLiteralExpr(StrLiteral& expr) = 0;
    virtual std::variant<std::monostate, std::string, double> visitNumLiteralExpr(NumLiteral& expr) = 0;
    virtual std::variant<std::monostate, std::string, double> visitUnaryExpr(Unary& expr) = 0;
};

class Expr {
public:
    virtual ~Expr() = default;
    virtual std::variant<std::monostate, std::string, double> accept(Visitor& visitor) = 0;
};

class Binary : public Expr {
public:
    std::unique_ptr<Expr> left;
    Token& oper;
    std::unique_ptr<Expr> right;

    Binary(std::unique_ptr<Expr> left, Token& oper, std::unique_ptr<Expr> right) : left(std::move(left)),
                                                                                   oper(oper),
                                                                                   right(std::move(right)) {}

    std::variant<std::monostate, std::string, double> accept(Visitor& visitor) override {
        return visitor.visitBinaryExpr(*this);
    }
};

class Grouping : public Expr {
public:
    std::unique_ptr<Expr> expression;

    explicit Grouping(std::unique_ptr<Expr> expression) : expression(std::move(expression)) {}

    std::variant<std::monostate, std::string, double> accept(Visitor& visitor) override {
        return visitor.visitGroupingExpr(*this);
    }
};

class StrLiteral : public Expr {
public:
    std::string value;

    explicit StrLiteral(std::string value) : value(std::move(value)) {}

    std::variant<std::monostate, std::string, double> accept(Visitor& visitor) override {
        return visitor.visitStrLiteralExpr(*this);
    }
};

class NumLiteral : public Expr {
public:
    double value;

    explicit NumLiteral(double value) : value{ value } {}

    std::variant<std::monostate, std::string, double> accept(Visitor& visitor) override {
        return visitor.visitNumLiteralExpr(*this);
    }
};

class Unary : public Expr {
public:
    Token& oper;
    std::unique_ptr<Expr> right;

    Unary(Token& oper, std::unique_ptr<Expr> right) : oper{ oper }, right(std::move(right)) {}

    std::variant<std::monostate, std::string, double> accept(Visitor& visitor) override {
        return visitor.visitUnaryExpr(*this);
    }
};

#endif //LOX_INTERPRETERS_EXPR_H
