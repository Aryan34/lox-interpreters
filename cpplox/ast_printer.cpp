#include "ast_printer.h"

std::string AstPrinter::print(std::unique_ptr<Expr> expr) {
    return toStrVisit(expr->accept(*this)) + "\n";
}

std::string AstPrinter::toStrVisit(LiteralVariant literal) {
    switch (literal.index()) {
        case 0: return "nil";  // literal is type nil
        case 1: return std::get<std::string>(literal);  // literal is type string
        case 2: return std::to_string(std::get<double>(literal));  // literal is type number
        case 3: return std::get<bool>(literal) ? std::string("true") : std::string("false");  // literal is type bool
        default: return "variant type index error";
    }
}

std::string AstPrinter::parenthesize(const std::string& name, std::initializer_list<Expr*> exprs) {
    std::string astString = "(" + name;
    for (Expr* expr: exprs) {
        // TODO: error handling for variant get
        astString += " " + toStrVisit(expr->accept(*this));
    }
    return astString + ")";
}

LiteralVariant AstPrinter::visitBinaryExpr(Binary& expr) {
    return parenthesize(expr.oper.lexeme, std::initializer_list<Expr*>{ expr.left.get(), expr.right.get() });
}

LiteralVariant AstPrinter::visitGroupingExpr(Grouping& expr) {
    return parenthesize("group", std::initializer_list<Expr*>{ expr.expression.get() });
}

LiteralVariant AstPrinter::visitLiteralExpr(Literal& expr) {
    return expr.value;
}

LiteralVariant AstPrinter::visitUnaryExpr(Unary& expr) {
    return parenthesize(expr.oper.lexeme, std::initializer_list<Expr*>{ expr.right.get() });
}
