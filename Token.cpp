//
// Created by ryousuke kaga on 2023/11/06.
//

#include "Token.h"

#include <utility>

Token::Token(TokenType type, std::string lexeme, Literal* literal, int line):
        type(type), lexeme(std::move(lexeme)), literal(literal), line(line){
    tokenNameMap[LEFT_PAREN] = "LEFT_PAREN";
    tokenNameMap[RIGHT_PAREN] = "RIGHT_PAREN";
    tokenNameMap[LEFT_BRACE] = "LEFT_BRACE";
    tokenNameMap[RIGHT_BRACE] = "RIGHT_BRACE";
    tokenNameMap[COMMA] = "COMMA";
    tokenNameMap[DOT] = "DOT";
    tokenNameMap[MINUS] = "MINUS";
    tokenNameMap[PLUS] = "PLUS";
    tokenNameMap[SEMICOLON] = "SEMICOLON";
    tokenNameMap[SLASH] = "SLASH";
    tokenNameMap[STAR] = "STAR";
    tokenNameMap[BANG] = "BANG";
    tokenNameMap[BANG_EQUAL] = "BANG_EQUAL";
    tokenNameMap[EQUAL] = "EQUAL";
    tokenNameMap[EQUAL_EQUAL] = "EQUAL_EQUAL";
    tokenNameMap[LESS] = "LESS";
    tokenNameMap[LESS_EQUAL] = "LESS_EQUAL";
    tokenNameMap[GREAT] = "GREAT";
    tokenNameMap[GREAT_EQUAL] = "GREAT_EQUAL";
    tokenNameMap[IDENTIFIER] = "IDENTIFIER";
    tokenNameMap[STRING] = "STRING";
    tokenNameMap[NUMBER] = "NUMBER";
    tokenNameMap[AND] = "AND";
    tokenNameMap[CLASS] = "CLASS";
    tokenNameMap[ELSE] = "ELSE";
    tokenNameMap[FALSE] = "FALSE";
    tokenNameMap[FUN] = "FUN";
    tokenNameMap[FOR] = "FOR";
    tokenNameMap[IF] = "IF";
    tokenNameMap[NIL] = "NIL";
    tokenNameMap[OR] = "OR";
    tokenNameMap[PRINT] = "PRINT";
    tokenNameMap[RETURN] = "RETURN";
    tokenNameMap[SUPER] = "SUPER";
    tokenNameMap[THIS] = "THIS";
    tokenNameMap[TRUE] = "TRUE";
    tokenNameMap[VAR] = "VAR";
    tokenNameMap[WHILE] = "WHILE";
    tokenNameMap[M_EOF] = "EOF";
}

std::string Token::toString() {
    std::string s;
    switch(type) {
        case(STRING):
            s = *literal->s;
            break;
        case(NUMBER):
            s = std::to_string(literal->d);
            break;
        default:
            s = "";
            break;
    }
    return tokenNameMap[type] + " " + lexeme + " " + s;
}

Token::~Token() {
    if(type == STRING) {
        delete literal->s;
    }
    delete literal;
}
