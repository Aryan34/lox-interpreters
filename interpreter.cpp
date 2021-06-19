#include "interpreter.h"

// TODO: implement rigorous runtime error handling
void Interpreter::interpret(std::unique_ptr<Expr> expr) {
    try {
        std::cout << stringify(expr->accept(*this)) << "\n";
    } catch (...) {
        std::cout << "error in interpret";
    }
}

std::string Interpreter::stringify(std::variant<std::monostate, std::string, double, bool> object) {
    switch (object.index()) {
        case 0: return "nil";
        case 1: return std::get<std::string>(object);
        case 2: return std::to_string(std::get<double>(object));
        case 3: return std::get<bool>(object) ? std::string("true") : std::string("false");
    }
    return "error";
}

std::variant<std::monostate, std::string, double, bool> Interpreter::visitBinaryExpr(Binary& expr) {
    std::variant<std::monostate, std::string, double, bool> left = expr.left->accept(*this);
    std::variant<std::monostate, std::string, double, bool> right = expr.right->accept(*this);

    switch (expr.oper.type) {
        case TokenType::GREATER:
            std::variant<std::monostate, std::string, double, bool>{ std::get<double>(left) > std::get<double>(right) };
        case TokenType::GREATER_EQUAL:
            std::variant<std::monostate, std::string, double, bool>{
                    std::get<double>(left) >= std::get<double>(right) };
        case TokenType::LESS:
            std::variant<std::monostate, std::string, double, bool>{ std::get<double>(left) < std::get<double>(right) };
        case TokenType::LESS_EQUAL:
            std::variant<std::monostate, std::string, double, bool>{
                    std::get<double>(left) <= std::get<double>(right) };
        case TokenType::MINUS:
            return std::variant<std::monostate, std::string, double, bool>{
                    std::get<double>(left) - std::get<double>(right) };
        case TokenType::PLUS:
            if (left.index() == 2 && right.index() == 2) {
                return std::variant<std::monostate, std::string, double, bool>{
                        std::get<double>(left) + std::get<double>(right) };
            } else if (left.index() == 1 && right.index() == 1) {
                return std::variant<std::monostate, std::string, double, bool>{
                        std::get<std::string>(left) + std::get<std::string>(right) };
            }
            break;
        case TokenType::SLASH:
            return std::variant<std::monostate, std::string, double, bool>{
                    std::get<double>(left) / std::get<double>(right) };
        case TokenType::STAR:
            return std::variant<std::monostate, std::string, double, bool>{
                    std::get<double>(left) * std::get<double>(right) };
    }
    return std::variant<std::monostate, std::string, double, bool>{};
}

std::variant<std::monostate, std::string, double, bool> Interpreter::visitGroupingExpr(Grouping& expr) {
    return expr.expression->accept(*this);
}

std::variant<std::monostate, std::string, double, bool> Interpreter::visitLiteralExpr(Literal& expr) {
    return expr.value;
}

std::variant<std::monostate, std::string, double, bool> Interpreter::visitUnaryExpr(Unary& expr) {
    std::variant<std::monostate, std::string, double, bool> right = expr.right->accept(*this);

    switch (expr.oper.type) {
        // TODO: error handling for if variant is not correct type
        case TokenType::BANG:
            // TODO: implement truthiness
            return std::variant<std::monostate, std::string, double, bool>{!std::get<bool>(right)};
        case TokenType::MINUS:
            return std::variant<std::monostate, std::string, double, bool>{-std::get<double>(right)};
    }
    return std::variant<std::monostate, std::string, double, bool>{};
}
