//
// Created by ryousuke kaga on 2023/11/06.
//

#include "Interpreter.h"
#include "Parser.h"
#include <sstream>

bool Interpreter::hadError = false;
bool Interpreter::hadRuntimeError = false;

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
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    std::string buffer(size, ' ');
    file.seekg(0);
    file.read(&buffer[0], (int)size);

    run(buffer);

    if(hadError) exit(65);
    if(hadRuntimeError) exit(70);
}

void Interpreter::runPrompt() {

}

void Interpreter::run(std::string& source) {
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();
    Parser parser(tokens);
    auto statements = parser.parse();

    if(hadError) return;

    interpret(statements);
}

void Interpreter::error(Token* token, const std::string &message) {
    if(!token)
        report(0, "", message);
    else if(token->type == M_EOF)
        report(token->line, " at end", message);
    else
        report(token->line, " at '" + token->lexeme + "'", message);
}

void Interpreter::report(int line, const std::string &where, const std::string &message) {
    std::cout << "[line " << line << "] Error" << where << ": " << message << std::endl;
    hadError = true;
}

void Interpreter::interpret(std::vector<std::unique_ptr<Stmt>>& statements) {
    try {
        for (auto & statement : statements) {
            statement->execute();
        }
    } catch(const RuntimeError& err) {
        Interpreter::runtimeError(err);
    }
}

void Interpreter::runtimeError(const RuntimeError &error) {
    std::cout << error.what() << "\n[line " << error.token->line << "]" << std::endl;
    hadRuntimeError = true;
}