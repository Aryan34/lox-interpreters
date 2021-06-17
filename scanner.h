#ifndef LOX_INTERPRETERS_SCANNER_H
#define LOX_INTERPRETERS_SCANNER_H

#include <vector>
#include <memory>
#include <unordered_map>

#include "token.h"

class Scanner {
public:
    explicit Scanner(std::string source);

    std::vector<std::unique_ptr<Token>>& scanTokens();

private:
    int line;
    int start;
    int current;
    std::string source;
    std::vector<std::unique_ptr<Token>> tokens;
    std::unordered_map<std::string, TokenType> keywords;

    bool isAtEnd();
    bool match(char expected);

    char peek();
    char peekNext();
    char advance();

    void addToken(TokenType type);
    void addToken(TokenType type, const std::variant<std::monostate, std::string, double>& literal);
    void str();
    void number();
    void identifier();

    void scanToken();
};

#endif //LOX_INTERPRETERS_SCANNER_H
