#include <iostream>

enum TokenType {
    // single character tokens
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // one or two character tokens
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // literals
    IDENTIFIER, STRING, NUMBER,

    // keywords
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    EF
};

std::ostream& operator<<(std::ostream& out, const TokenType type) {
    switch (type) {
        case LEFT_PAREN:    out << "LEFT_PAREN"; break;
        case RIGHT_PAREN:   out << "RIGHT_PAREN"; break;
        case LEFT_BRACE:    out << "LEFT_BRACE"; break;
        case RIGHT_BRACE:   out << "RIGHT_BRACE"; break;
        case COMMA:         out << "COMMA"; break;
        case DOT:           out << "DOT"; break;
        case MINUS:         out << "MINUS"; break;
        case PLUS:          out << "PLUS"; break;
        case SEMICOLON:     out << "SEMICOLON"; break;
        case SLASH:         out << "SLASH"; break;
        case STAR:          out << "STAR"; break;
        case BANG:          out << "BANG"; break;
        case BANG_EQUAL:    out << "BANG_EQUAL"; break;
        case EQUAL:         out << "EQUAL"; break;
        case EQUAL_EQUAL:   out << "EQUAL_EQUAL"; break;
        case GREATER:       out << "GREATER"; break;
        case GREATER_EQUAL: out << "GREATER_EQUAL"; break;
        case LESS:          out << "LESS"; break;
        case LESS_EQUAL:    out << "LESS_EQUAL"; break;
        case IDENTIFIER:    out << "IDENTIFIER"; break;
        case STRING:        out << "STRING"; break;
        case NUMBER:        out << "NUMBER"; break;
        case AND:           out << "AND"; break;
        case CLASS:         out << "CLASS"; break;
        case ELSE:          out << "ELSE"; break;
        case FALSE:         out << "FALSE"; break;
        case FUN:           out << "FUN"; break;
        case FOR:           out << "FOR"; break;
        case IF:            out << "IF"; break;
        case NIL:           out << "NIL"; break;
        case OR:            out << "OR"; break;
        case PRINT:         out << "PRINT"; break;
        case RETURN:        out << "RETURN"; break;
        case SUPER:         out << "SUPER"; break;
        case THIS:          out << "THIS"; break;
        case TRUE:          out << "TRUE"; break;
        case VAR:           out << "VAR"; break;
        case WHILE:         out << "WHILE"; break;
        case EF:            out << "EF"; break;
    }
    return out;
}