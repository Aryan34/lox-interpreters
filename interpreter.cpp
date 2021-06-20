#include "interpreter.h"

// TODO: implement rigorous runtime error handling
void Interpreter::interpret(std::unique_ptr<Expr> expr) {
    try {
        std::cout << stringify(expr->accept(*this)) << "\n";
    } catch (...) {
        std::cout << "error in interpreter";
    }
}

std::string Interpreter::stringify(LiteralVariant object) {
    switch (object.index()) {
        case 0: return "nil";
        case 1: return std::get<std::string>(object);
        case 2: return std::to_string(std::get<double>(object));
        case 3: return std::get<bool>(object) ? std::string("true") : std::string("false");
    }
    return "error";
}

LiteralVariant Interpreter::visitBinaryExpr(Binary& expr) {
    LiteralVariant left = expr.left->accept(*this);
    LiteralVariant right = expr.right->accept(*this);

    switch (expr.oper.type) {
        case TokenType::GREATER:
            LiteralVariant{ std::get<double>(left) > std::get<double>(right) };
        case TokenType::GREATER_EQUAL:
            LiteralVariant{
                    std::get<double>(left) >= std::get<double>(right) };
        case TokenType::LESS:
            LiteralVariant{ std::get<double>(left) < std::get<double>(right) };
        case TokenType::LESS_EQUAL:
            LiteralVariant{
                    std::get<double>(left) <= std::get<double>(right) };
        case TokenType::MINUS:
            return LiteralVariant{
                    std::get<double>(left) - std::get<double>(right) };
        case TokenType::PLUS:
            if (left.index() == 2 && right.index() == 2) {
                return LiteralVariant{
                        std::get<double>(left) + std::get<double>(right) };
            } else if (left.index() == 1 && right.index() == 1) {
                return LiteralVariant{
                        std::get<std::string>(left) + std::get<std::string>(right) };
            }
            break;
        case TokenType::SLASH:
            return LiteralVariant{
                    std::get<double>(left) / std::get<double>(right) };
        case TokenType::STAR:
            return LiteralVariant{
                    std::get<double>(left) * std::get<double>(right) };
    }
    return LiteralVariant{};
}

LiteralVariant Interpreter::visitGroupingExpr(Grouping& expr) {
    return expr.expression->accept(*this);
}

LiteralVariant Interpreter::visitLiteralExpr(Literal& expr) {
    return expr.value;
}

LiteralVariant Interpreter::visitUnaryExpr(Unary& expr) {
    LiteralVariant right = expr.right->accept(*this);

    switch (expr.oper.type) {
        // TODO: error handling for if variant is not correct type
        case TokenType::BANG:
            // TODO: implement truthiness
            return LiteralVariant{!std::get<bool>(right)};
        case TokenType::MINUS:
            return LiteralVariant{-std::get<double>(right)};
    }
    return LiteralVariant{};
}
