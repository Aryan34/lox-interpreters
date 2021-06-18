#ifndef LOX_INTERPRETERS_AST_PRINTER_H
#define LOX_INTERPRETERS_AST_PRINTER_H

#include "expr.h"

class AstPrinter : Visitor {
public:
    std::string print(std::unique_ptr<Expr> expr);

    std::variant<std::monostate, std::string, double> visitBinaryExpr(Binary& expr) override;
    std::variant<std::monostate, std::string, double> visitGroupingExpr(Grouping& expr) override;
    std::variant<std::monostate, std::string, double> visitStrLiteralExpr(StrLiteral& expr) override;
    std::variant<std::monostate, std::string, double> visitNumLiteralExpr(NumLiteral& expr) override;
    std::variant<std::monostate, std::string, double> visitUnaryExpr(Unary& expr) override;

    std::string parenthesize(const std::string& name, std::initializer_list<Expr*> exprs);
};

#endif //LOX_INTERPRETERS_AST_PRINTER_H
