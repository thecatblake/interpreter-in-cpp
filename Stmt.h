//
// Created by ryousuke kaga on 2023/11/13.
//

#ifndef INTERPRETER_IN_CPP_STMT_H
#define INTERPRETER_IN_CPP_STMT_H


#include "Expr.h"
#include "Literal.h"

class Stmt {
public:
    virtual void execute();
};

class ExprStmt : public Stmt {
public:
    ExprStmt(Expr* expression): expression(expression) {}
    void execute() override;
    Expr* expression;
};

class PrintStmt : public Stmt {
public:
    PrintStmt(Expr* expression): expression(expression) {}
    void execute() override;
    Expr* expression;
};


#endif //INTERPRETER_IN_CPP_STMT_H
