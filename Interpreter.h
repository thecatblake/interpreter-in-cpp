//
// Created by ryousuke kaga on 2023/11/06.
//

#ifndef INTERPRETER_IN_CPP_INTERPRETER_H
#define INTERPRETER_IN_CPP_INTERPRETER_H

#include <iostream>
#include <fstream>
#include "Scanner.h"
#include "Expr.h"
#include "RuntimeError.h"

class Interpreter {
public:
    Interpreter(int argc, char** args);
    static bool hadError;
    static bool hadRuntimeError;
    static void error(Token* token, const std::string& message);
    static void report(int line, const std::string& where, const std::string& message);
    static void runtimeError(const RuntimeError& error);
private:
    void runFile(char* path);
    void runPrompt();
    void run(std::string& source);
    void interpret(Expr* expression);
    std::string stringify(Literal& literal);
};


#endif //INTERPRETER_IN_CPP_INTERPRETER_H
