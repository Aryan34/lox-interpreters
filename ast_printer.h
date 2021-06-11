#ifndef LOX_INTERPRETERS_AST_PRINTER_H
#define LOX_INTERPRETERS_AST_PRINTER_H

#include "expr.h"

class AstPrinter : Visitor {
public:
    std::string print(std::unique_ptr<Expr> expr);

    std::string visitBinaryExpr(Binary& expr) override;
    std::string visitGroupingExpr(Grouping& expr) override;
    std::string visitStrLiteralExpr(StrLiteral& expr) override;
    std::string visitNumLiteralExpr(NumLiteral& expr) override;
    std::string visitUnaryExpr(Unary& expr) override;

    std::string parenthesize(const std::string& name, std::initializer_list<Expr*> exprs);
};

#endif //LOX_INTERPRETERS_AST_PRINTER_H
