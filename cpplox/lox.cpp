#include <fstream>

#include "scanner.h"
#include "parser.h"
#include "interpreter.h"
#include "cpplox/ast_printer.h"

bool hadError = false;

void report(int line, const std::string& where, const std::string& message) {
    std::cout << "[Line " << line << "] Error " << where << ": " << message << "\n";
    hadError = true;
}

void error(const Token& token, const std::string& message) {
    if (token.type == TokenType::END_FILE) {
        report(token.line, " at end", message);
    } else {
        report(token.line, " at '" + token.lexeme + "'", message);
    }
}

void error(int line, const std::string& message) {
    report(line, "", message);
}

void run(std::string source) {
    // TODO: call std::move on source argument directly in scanner header
    Scanner scanner { std::move(source) };
    std::vector<std::unique_ptr<Token>>& tokens = scanner.scanTokens();
    Parser parser{ std::move(tokens) };
    std::unique_ptr<Expr> expression = parser.parse();

    if (hadError) { return; }
    Interpreter interpreter{};
    interpreter.interpret(std::move(expression));
//    AstPrinter printer{};
//    std::cout << printer.print(std::move(expression));
}

void runFile(const std::string& path) {
    std::ifstream ifs{ path };
    std::string source{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
    run(source);
    if (hadError) { exit(1); }
}

void runPrompt() {
    std::string line;
    while (true) {
        std::getline(std::cin, line);
        if (line.length() == 0 or line=="exit()") { break; }
        run(line);
        hadError = false;
    }
}

int main(int argc, char** argv) {
    if (argc > 2) {
        std::cout << "Usage: cpplox [script]";
        exit(1);
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        runPrompt();
    }
    return 0;
}
