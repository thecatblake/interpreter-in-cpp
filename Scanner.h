//
// Created by ryousuke kaga on 2023/11/06.
//

#ifndef INTERPRETER_IN_CPP_SCANNER_H
#define INTERPRETER_IN_CPP_SCANNER_H

#include <vector>
#include <utility>
#include "Token.h"
#include "Interpreter.h"
#include "Literal.h"

class Scanner {
public:
    Scanner(std::string source);
    void scanToken();
    std::vector<Token> scanTokens();
private:
    bool isAtEnd();
    char advance();
    bool match(char expected);
    char peek();
    char peekNext();
    void addToken(TokenType type, const std::shared_ptr<Literal>& literal);
    void string();
    void number();
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);
    void identifier();
    std::string source;
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;
    std::unordered_map<std::string, TokenType> nameTokenMap;
};


#endif //INTERPRETER_IN_CPP_SCANNER_H
