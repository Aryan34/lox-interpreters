cmake_minimum_required(VERSION 3.16)
project(lox_interpreters)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(lox_interpreters
        cpplox/lox.cpp
        cpplox/scanner.cpp
        cpplox/scanner.h
        cpplox/token.cpp
        cpplox/token.h
        cpplox/tokentype.cpp
        cpplox/tokentype.h
        cpplox/expr.h
        cpplox/ast_printer.cpp
        cpplox/ast_printer.h
        cpplox/parser.cpp
        cpplox/parser.h
        cpplox/interpreter.cpp
        cpplox/interpreter.h
        cpplox/runtime_error.h)
