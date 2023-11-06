//
// Created by ryousuke kaga on 2023/11/06.
//

#ifndef INTERPRETER_IN_CPP_INTERPRETER_H
#define INTERPRETER_IN_CPP_INTERPRETER_H

#include <iostream>
#include <fstream>
#include "Scanner.h"

class Interpreter {
public:
    Interpreter(int argc, char** args);
    static bool hadError;
    static void error(int line, const std::string& message);
    static void report(int line, std::string& where, const std::string& message);
private:
    void runFile(char* path);
    void runPrompt();
    void run(std::string& source);
};


#endif //INTERPRETER_IN_CPP_INTERPRETER_H
