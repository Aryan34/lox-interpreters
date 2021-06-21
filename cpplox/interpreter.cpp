#include "interpreter.h"

// TODO: implement rigorous runtime error handling
void Interpreter::interpret(std::unique_ptr<Expr> expr) {
    try {
        std::cout << stringify(expr->accept(*this)) << "\n";
    } catch (...) {
        std::cout << "error in interpreter";
    }
}

std::string Interpreter::stringify(LiteralVariant literal) {
    switch (literal.index()) {
        case 0: return "nil";  // literal is type nil
        case 1: return std::get<std::string>(literal);  // literal is type string
        case 2: return std::to_string(std::get<double>(literal));  // literal is type number
        case 3: return std::get<bool>(literal) ? std::string("true") : std::string("false");  // literal is type bool
    }
    return "error";
}

bool Interpreter::isTruthy(LiteralVariant literal) {
    switch (literal.index()) {
        case 0: return false;
        case 3: return std::get<bool>(literal);
        default: return true;
    }
}

bool Interpreter::isEqual(LiteralVariant a, LiteralVariant b) {
    if (a.index() != b.index()) { return false; }

    switch(a.index()) {
        case 0: return true;
        case 1: return std::get<std::string>(a) == std::get<std::string>(b);
        case 2: return std::get<double>(a) == std::get<double>(b);
        case 3: return std::get<bool>(a) == std::get<bool>(b);
        default: return false;
    }
}

LiteralVariant Interpreter::visitBinaryExpr(Binary& expr) {
    LiteralVariant left = expr.left->accept(*this);
    LiteralVariant right = expr.right->accept(*this);

    switch (expr.oper.type) {
        case TokenType::BANG_EQUAL:
            return LiteralVariant{ !isEqual(left, right) };
        case TokenType::EQUAL_EQUAL:
            return LiteralVariant{ isEqual(left, right) };
        case TokenType::GREATER:
            return LiteralVariant{ std::get<double>(left) > std::get<double>(right) };
        case TokenType::GREATER_EQUAL:
            return LiteralVariant{ std::get<double>(left) >= std::get<double>(right) };
        case TokenType::LESS:
            return LiteralVariant{ std::get<double>(left) < std::get<double>(right) };
        case TokenType::LESS_EQUAL:
            return LiteralVariant{ std::get<double>(left) <= std::get<double>(right) };
        case TokenType::MINUS:
            return LiteralVariant{ std::get<double>(left) - std::get<double>(right) };
        case TokenType::PLUS:
            if (left.index() == 2 && right.index() == 2) {
                return LiteralVariant{ std::get<double>(left) + std::get<double>(right) };
            } else if (left.index() == 1 && right.index() == 1) {
                return LiteralVariant{ std::get<std::string>(left) + std::get<std::string>(right) };
            }
            break;
        case TokenType::SLASH:
            return LiteralVariant{ std::get<double>(left) / std::get<double>(right) };
        case TokenType::STAR:
            return LiteralVariant{ std::get<double>(left) * std::get<double>(right) };
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
            return LiteralVariant{!isTruthy(std::get<bool>(right))};
        case TokenType::MINUS:
            return LiteralVariant{-std::get<double>(right)};
    }
    return LiteralVariant{};
}
