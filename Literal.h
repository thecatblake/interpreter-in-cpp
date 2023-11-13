//
// Created by ryousuke kaga on 2023/11/13.
//

#ifndef INTERPRETER_IN_CPP_LITERAL_H
#define INTERPRETER_IN_CPP_LITERAL_H

#include <string>

typedef std::variant<std::string, int, long, float, double, bool> Literal;

std::string stringify(Literal& literal);

#endif //INTERPRETER_IN_CPP_LITERAL_H
