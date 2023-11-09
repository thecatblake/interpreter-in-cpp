//
// Created by ryousuke kaga on 2023/11/09.
//

#ifndef INTERPRETER_IN_CPP_PARSER_H
#define INTERPRETER_IN_CPP_PARSER_H

#include "Token.h"
#include "Expr.h"
#include "Interpreter.h"

class ParserError : public std::runtime_error {
    std::string what_message;
public:
    ParserError(const std::string& msg) : runtime_error(msg) {}
    const char* what() const noexcept override
    {
        return what_message.c_str();
    }
};

class Parser {
public:
    Parser(std::vector<Token>& tokens): tokens(tokens) {}
    Expr* parse();
private:
    Expr* expression();
    Expr* equality();
    Expr* comparison();
    Expr* term();
    Expr* factor();
    Expr* unary();
    Expr* primary();
    Token* advance();
    Token* peek();
    Token* previous();
    Token* consume(TokenType type, char* message);
    bool match(std::initializer_list<TokenType> types);
    bool check(TokenType type);
    bool isAtEnd();
    ParserError error(Token* token, const char* message);
    void synchronize();

    std::vector<Token> tokens;
    int current = 0;
};


#endif //INTERPRETER_IN_CPP_PARSER_H
