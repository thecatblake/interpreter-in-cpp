//
// Created by ryousuke kaga on 2023/11/06.
//

#ifndef INTERPRETER_IN_CPP_TOKEN_H
#define INTERPRETER_IN_CPP_TOKEN_H

#include <iostream>
#include <unordered_map>
#include "Literal.h"

enum TokenType {
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    LESS, LESS_EQUAL,
    GREAT, GREAT_EQUAL,

    IDENTIFIER, STRING, NUMBER,

    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    M_EOF
};

class Token {
public:
    Token(TokenType type, std::string lexeme, std::shared_ptr<Literal> literal, int line);
    ~Token();
    std::string toString();
    TokenType type;
    std::shared_ptr<Literal> literal;
    std::string lexeme;
    int line;
private:
    std::unordered_map<TokenType, std::string> tokenNameMap;
};


#endif //INTERPRETER_IN_CPP_TOKEN_H
