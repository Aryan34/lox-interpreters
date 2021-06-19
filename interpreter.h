#ifndef LOX_INTERPRETERS_INTERPRETER_H
#define LOX_INTERPRETERS_INTERPRETER_H

#include "expr.h"

class Interpreter : Visitor {
public:
    void interpret(std::unique_ptr<Expr> expr);

private:
    static std::string stringify(std::variant<std::monostate, std::string, double, bool> object);
    std::variant<std::monostate, std::string, double, bool> visitBinaryExpr(Binary& expr) override;
    std::variant<std::monostate, std::string, double, bool> visitGroupingExpr(Grouping& expr) override;
    std::variant<std::monostate, std::string, double, bool> visitLiteralExpr(Literal& expr) override;
    std::variant<std::monostate, std::string, double, bool> visitUnaryExpr(Unary& expr) override;
};

#endif //LOX_INTERPRETERS_INTERPRETER_H
