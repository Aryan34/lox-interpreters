cmake_minimum_required(VERSION 3.19)
project(lox_interpreters)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(lox_interpreters
        lox.cpp
        scanner.cpp
        scanner.h
        token.cpp
        token.h
        tokentype.cpp
        tokentype.h
        expr.h
        ast_printer.cpp
        ast_printer.h
        parser.cpp
        parser.h
        interpreter.cpp
        interpreter.h)
