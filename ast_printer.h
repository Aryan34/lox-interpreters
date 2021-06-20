#ifndef LOX_INTERPRETERS_AST_PRINTER_H
#define LOX_INTERPRETERS_AST_PRINTER_H

#include "expr.h"

class AstPrinter : Visitor {
public:
    std::string print(std::unique_ptr<Expr> expr);

    LiteralVariant visitBinaryExpr(Binary& expr) override;
    LiteralVariant visitGroupingExpr(Grouping& expr) override;
    LiteralVariant visitLiteralExpr(Literal& expr) override;
    LiteralVariant visitUnaryExpr(Unary& expr) override;

    std::string parenthesize(const std::string& name, std::initializer_list<Expr*> exprs);

private:
    static std::string toStrVisit(LiteralVariant literal);
};

#endif //LOX_INTERPRETERS_AST_PRINTER_H
