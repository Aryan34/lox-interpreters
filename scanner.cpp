#include <cmath>

#include "scanner.h"

Scanner::Scanner(std::string source)
        : line{ 0 },
          start{ 0 },
          current{ 0 },
          source{ std::move(source) },
          tokens{ },
          keywords{
                  { "and",    TokenType::AND },
                  { "class",  TokenType::CLASS },
                  { "else",   TokenType::ELSE },
                  { "false",  TokenType::FALSE },
                  { "for",    TokenType::FOR },
                  { "fun",    TokenType::FUN },
                  { "if",     TokenType::IF },
                  { "nil",    TokenType::NIL },
                  { "or",     TokenType::OR },
                  { "print",  TokenType::PRINT },
                  { "return", TokenType::RETURN },
                  { "super",  TokenType::SUPER },
                  { "this",   TokenType::THIS },
                  { "true",   TokenType::TRUE },
                  { "var",    TokenType::VAR },
                  { "while",  TokenType::WHILE },
          } {}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

bool Scanner::match(char expected) {
    if (isAtEnd() or source.at(current) != expected) { return false; }
    ++current;
    return true;
}

char Scanner::peek() {
    if (isAtEnd()) { return '\0'; }
    return source.at(current);
}

char Scanner::peekNext() {
    if (current + 1 >= source.length()) { return '\0'; }
    return source.at(current + 1);
}

char Scanner::advance() {
    return source.at(current++);
}

void Scanner::addToken(TokenType type) {
    std::string text = source.substr(start, current - start);
    tokens.push_back(
            std::make_unique<Token>(type, text, LiteralVariant{}, line));
}

void Scanner::addToken(TokenType type, const LiteralVariant& literal) {
    std::string text = source.substr(start, current - start);
    tokens.push_back(std::make_unique<Token>(type, text, literal, line));
}

void Scanner::str() {
    while (peek() != '"' and not isAtEnd()) {
        if (peek() == '\n') {
            ++line;
        }
        advance();
    }

    if (isAtEnd()) {
//        error(line, "Unterminated string.");
        return;
    }

    advance();
    std::string value = source.substr(start + 1, current - start - 2);
    addToken(TokenType::STRING, LiteralVariant{value});
}

void Scanner::number() {
    while (isdigit(peek())) {
        advance();
    }

    if (peek() == '.' and isdigit(peekNext())) {
        advance();
        while (isdigit(peek())) {
            advance();
        }
    }

    double value = stod(source.substr(start, current - start));
    addToken(TokenType::NUMBER, LiteralVariant{value});
}

void Scanner::identifier() {
    while (isalpha(peek()) or isdigit(peek())) {
        advance();
    }

    std::string text = source.substr(start, current - start);
    if (text == "true") {
        addToken(TokenType::TRUE, LiteralVariant{true});
    } else if (text == "false") {
        addToken(TokenType::FALSE, LiteralVariant{false});
    } else if (text == "nil") {
        addToken(TokenType::NIL, LiteralVariant{});
    } else {
        addToken(keywords.find(text) != keywords.end() ? keywords[text] : TokenType::IDENTIFIER);
    }
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        // single character tokens
        case '(':
            addToken(TokenType::LEFT_PAREN);
            break;
        case ')':
            addToken(TokenType::RIGHT_PAREN);
            break;
        case '{':
            addToken(TokenType::LEFT_BRACE);
            break;
        case '}':
            addToken(TokenType::RIGHT_BRACE);
            break;
        case ',':
            addToken(TokenType::COMMA);
            break;
        case '.':
            addToken(TokenType::DOT);
            break;
        case '-':
            addToken(TokenType::MINUS);
            break;
        case '+':
            addToken(TokenType::PLUS);
            break;
        case ';':
            addToken(TokenType::SEMICOLON);
            break;
        case '*':
            addToken(TokenType::STAR);
            break;

        // one or two character tokens
        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        case '/':
            if (match('/')) {
                while (peek() != '\n' and not isAtEnd()) {
                    advance();
                }
            } else {
                addToken(TokenType::SLASH);
            }
            break;

        // strings
        case '"':
            str();
            break;

        // whitespace
        case ' ':
        case '\r':
        case '\t':
            break;

        // new lines
        case '\n':
            ++line;
            break;

        // numbers, keywords & identifiers, illegal chars
        default:
            if (isdigit(c)) {
                number();
            } else if (isalpha(c)) {
                identifier();
            } else {
//                error(line, "Unexpected character");
            }
            break;
    }
}

std::vector<std::unique_ptr<Token>>& Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    tokens.push_back(
            std::make_unique<Token>(TokenType::END_FILE, "", LiteralVariant{},
                                    line));
    return tokens;
}
