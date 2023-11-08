cmake_minimum_required(VERSION 3.26)
project(interpreter_in_cpp)

set(CMAKE_CXX_STANDARD 17)

add_library(interpreter
        Interpreter.cpp
        Interpreter.h
        Token.cpp
        Token.h
        Scanner.cpp
        Scanner.h
        Expr.cpp
        Expr.h
)

add_executable(itpt run.cpp)
target_link_libraries(itpt interpreter)
add_executable(ast_string ast_string.cpp)
target_link_libraries(ast_string interpreter)