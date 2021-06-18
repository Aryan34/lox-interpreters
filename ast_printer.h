#ifndef LOX_INTERPRETERS_AST_PRINTER_H
#define LOX_INTERPRETERS_AST_PRINTER_H

#include "expr.h"

class AstPrinter : Visitor {
public:
    std::string print(std::unique_ptr<Expr> expr);

    std::variant<std::monostate, std::string, double, bool> visitBinaryExpr(Binary& expr) override;
    std::variant<std::monostate, std::string, double, bool> visitGroupingExpr(Grouping& expr) override;
    std::variant<std::monostate, std::string, double, bool> visitLiteralExpr(Literal& expr) override;
    std::variant<std::monostate, std::string, double, bool> visitUnaryExpr(Unary& expr) override;

    std::string parenthesize(const std::string& name, std::initializer_list<Expr*> exprs);

private:
    static std::string toStrVisit(std::variant<std::monostate, std::string, double, bool> literal);
};

#endif //LOX_INTERPRETERS_AST_PRINTER_H
