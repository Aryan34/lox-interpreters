#ifndef LOX_INTERPRETERS_INTERPRETER_H
#define LOX_INTERPRETERS_INTERPRETER_H

#include "expr.h"

class Interpreter : Visitor {
public:
    void interpret(std::unique_ptr<Expr> expr);

private:
    static std::string stringify(LiteralVariant literal);

    static bool isTruthy(LiteralVariant literal);
    static bool isEqual(LiteralVariant a, LiteralVariant b);

    static void checkNumberOperand(Token& oper, const LiteralVariant& operand);
    static void checkNumberOperands(Token& oper, const LiteralVariant& left, const LiteralVariant& right);

    LiteralVariant visitBinaryExpr(Binary& expr) override;
    LiteralVariant visitGroupingExpr(Grouping& expr) override;
    LiteralVariant visitLiteralExpr(Literal& expr) override;
    LiteralVariant visitUnaryExpr(Unary& expr) override;
};

#endif //LOX_INTERPRETERS_INTERPRETER_H
