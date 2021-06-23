#ifndef LOX_INTERPRETERS_RUNTIME_ERROR_H
#define LOX_INTERPRETERS_RUNTIME_ERROR_H

#include <stdexcept>

#include "token.h"

class RuntimeError : public std::runtime_error {
public:
    Token& token;

    RuntimeError(Token& token, std::string message) : std::runtime_error(message), token{ token } {}
};

#endif //LOX_INTERPRETERS_RUNTIME_ERROR_H
