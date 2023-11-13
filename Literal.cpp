//
// Created by ryousuke kaga on 2023/11/13.
//

#include "Literal.h"

std::string stringify(Literal &literal) {
    if(std::holds_alternative<double>(literal))
        return std::to_string(std::get<double>(literal));
    if(std::holds_alternative<std::string>(literal))
        return std::get<std::string>(literal);
    if(std::holds_alternative<bool>(literal))
        return std::to_string(std::get<bool>(literal));
}
