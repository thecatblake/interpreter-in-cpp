//
// Created by ryousuke kaga on 2023/11/06.
//

#include "Interpreter.h"

bool Interpreter::hadError = false;

Interpreter::Interpreter(int argc, char **args) {
    if(argc > 2) {
        std::cout << "Usage: itpt [script]" << std::endl;
        exit(64);
    } else if(argc == 2) {
        runFile(args[1]);
    } else {
        runPrompt();
    }
}

void Interpreter::runFile(char *path) {
    std::ifstream file(path);
    std::string source;
    file >> source;
    run(source);

    if(hadError) exit(65);
}

void Interpreter::runPrompt() {

}

void Interpreter::run(std::string& source) {
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();
    for(auto & token : tokens) {
        std::cout << token.toString() << std::endl;
    }
}

void Interpreter::error(int line, const std::string &message) {
    std::string where;
    report(line, where, message);
}

void Interpreter::report(int line, std::string &where, const std::string &message) {
    std::cout << "[line " << line << "] Error" << where << ": " << message << std::endl;
    hadError = true;
}
