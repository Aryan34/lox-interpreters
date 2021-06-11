#include <cmath>

#include "ast_printer.h"

std::string AstPrinter::print(std::unique_ptr<Expr> expr) {
    return expr->accept(*this);
}

std::string AstPrinter::visitBinaryExpr(Binary& expr) {
    return parenthesize(expr.oper->lexeme, std::initializer_list<Expr*>{ expr.left.get(), expr.right.get() });
}

std::string AstPrinter::visitGroupingExpr(Grouping& expr) {
    return parenthesize("group", std::initializer_list<Expr*>{ expr.expression.get() });
}

std::string AstPrinter::visitStrLiteralExpr(StrLiteral& expr) {
    return expr.value;
}

std::string AstPrinter::visitNumLiteralExpr(NumLiteral& expr) {
    return std::to_string(expr.value);
}

std::string AstPrinter::visitUnaryExpr(Unary& expr) {
    return parenthesize(expr.oper->lexeme, std::initializer_list<Expr*>{ expr.right.get() });
}

std::string AstPrinter::parenthesize(const std::string& name, std::initializer_list<Expr*> exprs) {
    std::string astString = "(" + name;
    for (Expr* expr: exprs) {
        astString += " " + expr->accept(*this);
    }
    return astString + ")";
}

//int main() {
//    std::unique_ptr<Expr> literal1 = std::make_unique<NumLiteral>(42.67);
//    std::unique_ptr<Expr> grouping = std::make_unique<Grouping>(std::move(literal1));
//    std::unique_ptr<Expr> literal2 = std::make_unique<NumLiteral>(123);
//    std::unique_ptr<Expr> unary = std::make_unique<Unary>(new Token(TokenType::MINUS, "-", "", NAN, 1),
//                                                          std::move(literal2));
//    std::unique_ptr<Expr> expression = std::make_unique<Binary>(std::move(unary),
//                                                                new Token(TokenType::STAR, "*", "", NAN, 1),
//                                                                std::move(grouping));
//
//    AstPrinter printer{};
//    std::cout << printer.print(std::move(expression));
//}