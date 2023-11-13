//
// Created by ryousuke kaga on 2023/11/13.
//

#include "Stmt.h"

void Stmt::execute() {
}

void ExprStmt::execute() {
    expression->evaluate();
}

void PrintStmt::execute() {
    auto value = expression->evaluate();
    std::cout << stringify(*value) << std::endl;
}
