#ifndef LOX_INTERPRETERS_AST_PRINTER_H
#define LOX_INTERPRETERS_AST_PRINTER_H

#include <cmath>
#include <vector>

#include "expr.h"

class AstPrinter : Visitor {
    std::string print(Expr expr);

    std::string visitBinaryExpr(Binary expr);
    std::string visitGroupingExpr(Grouping expr);
    std::string visitStrLiteralExpr(StrLiteral expr);
    std::string visitNumLiteralExpr(NumLiteral expr);
    std::string visitUnaryExpr(Unary expr);

    std::string parenthesize(std::string name, std::vector<Expr> exprs);
};

#endif //LOX_INTERPRETERS_AST_PRINTER_H
