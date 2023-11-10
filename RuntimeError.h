//
// Created by ryousuke kaga on 2023/11/10.
//

#ifndef INTERPRETER_IN_CPP_RUNTIMEERROR_H
#define INTERPRETER_IN_CPP_RUNTIMEERROR_H

#include <iostream>
#include "Token.h"

class RuntimeError : public std::runtime_error {
    std::string what_message;
public:
    RuntimeError(Token* token, const std::string& msg) : token(token), runtime_error(msg) {}
    const char* what() const noexcept override
    {
        return what_message.c_str();
    }

    Token* token;
};

#endif //INTERPRETER_IN_CPP_RUNTIMEERROR_H
