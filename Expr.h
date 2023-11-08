//
// Created by ryousuke kaga on 2023/11/08.
//

#ifndef INTERPRETER_IN_CPP_EXPR_H
#define INTERPRETER_IN_CPP_EXPR_H


#include "Token.h"

class Expr {
public:
    virtual std::string toString();
};

class BinaryExpr : public Expr {
public:
    BinaryExpr(Expr* left, Token* op, Expr* right): left(left), op(op), right(right) {}
    std::string toString() override;
    Expr* left;
    Token* op;
    Expr* right;
};

class UnaryExpr : public Expr {
public:
    UnaryExpr(Token* op, Expr* expr): op(op), expr(expr) {}
    std::string toString() override;
    Token* op;
    Expr* expr;
};

class GroupingExpr : public Expr {
public:
    GroupingExpr(Expr* expr): expr(expr) {}
    std::string toString() override;
    Expr* expr;
};

class LiteralExpr : public Expr {
public:
    LiteralExpr(std::shared_ptr<Literal> literal): literal(literal) {}
    std::string toString() override;
    std::shared_ptr<Literal> literal;
};


#endif //INTERPRETER_IN_CPP_EXPR_H
