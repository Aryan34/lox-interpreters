#include <fstream>

#include "scanner.h"

bool hadError = false;

void report(int line, const std::string& where, const std::string& message) {
    std::cout << "[Line " << line << "] Error " << where << ": " << message << "\n";
}

void error(int line, const std::string& message) {
    report(line, "", message);
}

void run(std::string source) {
    Scanner scanner { std::move(source) };
    std::vector<Token> tokens = scanner.scanTokens();

    for (const Token& token : tokens) {
        std::cout << token;
    }
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
}
