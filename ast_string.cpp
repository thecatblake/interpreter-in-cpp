//
// Created by ryousuke kaga on 2023/11/08.
//

#include <iostream>
#include "Expr.h"

int main() {
    Expr* expr = new BinaryExpr(
            new UnaryExpr(
                    new Token(MINUS, "-", nullptr, 1),
                    new LiteralExpr(std::make_shared<Literal>(123))
            ),
            new Token(STAR, "*", nullptr, 1),
            new GroupingExpr(
                    new LiteralExpr(std::make_shared<Literal>(45.67))
                    )
            );
    std::cout << expr->toString() << std::endl;
}