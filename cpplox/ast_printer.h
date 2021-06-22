#ifndef LOX_INTERPRETERS_AST_PRINTER_H
#define LOX_INTERPRETERS_AST_PRINTER_H

#include "expr.h"

class AstPrinter : Visitor {
public:
    std::string print(std::unique_ptr<Expr> expr);

private:
    static std::string toStrVisit(LiteralVariant literal);
    std::string parenthesize(const std::string& name, std::initializer_list<Expr*> exprs);

    LiteralVariant visitBinaryExpr(Binary& expr) override;
    LiteralVariant visitGroupingExpr(Grouping& expr) override;
    LiteralVariant visitLiteralExpr(Literal& expr) override;
    LiteralVariant visitUnaryExpr(Unary& expr) override;
};

#endif //LOX_INTERPRETERS_AST_PRINTER_H
