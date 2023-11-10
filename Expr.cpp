//
// Created by ryousuke kaga on 2023/11/08.
//

#include "Expr.h"
#include "RuntimeError.h"

std::string Expr::toString() {
    return "";
}

std::shared_ptr<Literal> Expr::evaluate() {
    return nullptr;
}

void Expr::checkNumberOperand(Token *op, std::shared_ptr<Literal> right) {
    if(std::holds_alternative<double>(*right)) return;
    throw RuntimeError(op, "Operand must be a number");
}

void Expr::checkNumberOperands(Token* op, std::shared_ptr<Literal> left, std::shared_ptr<Literal> right) {
    if(std::holds_alternative<double>(*left) && std::holds_alternative<double>(*right)) return;
    throw RuntimeError(op, "Operand must be a number");
}

std::string BinaryExpr::toString() {
    return "(" + op->toString() + " " + left->toString() + " " + right->toString() + ")";
}

std::shared_ptr<Literal> BinaryExpr::evaluate() {
    auto l = left->evaluate();
    auto r = right->evaluate();

    switch(op->type) {
        case MINUS:
            checkNumberOperands(op, l, r);
            return std::make_shared<Literal>(std::get<double>(*l) - std::get<double>(*r));
        case STAR:
            checkNumberOperands(op, l, r);
            return std::make_shared<Literal>(std::get<double>(*l) * std::get<double>(*r));
        case SLASH:
            checkNumberOperand(op, r);
            return std::make_shared<Literal>(std::get<double>(*l) / std::get<double>(*r));
        case PLUS:
        {
            if(std::holds_alternative<double>(*l) && std::holds_alternative<double>(*r))
                return std::make_shared<Literal>(std::get<double>(*l) + std::get<double>(*r));
            if(std::holds_alternative<std::string>(*l) && std::holds_alternative<std::string>(*r))
                return std::make_shared<Literal>(std::get<std::string>(*l) + std::get<std::string>(*r));
            throw RuntimeError(op, "Operands must be two numbers or two Strings");
        }
        case GREAT:
            checkNumberOperands(op, l, r);
            return std::make_shared<Literal>(std::get<double>(*l) > std::get<double>(*r));
        case GREAT_EQUAL:
            checkNumberOperands(op, l, r);
            return std::make_shared<Literal>(std::get<double>(*l) >= std::get<double>(*r));
        case LESS:
            checkNumberOperands(op, l, r);
            return std::make_shared<Literal>(std::get<double>(*l) < std::get<double>(*r));
        case LESS_EQUAL:
            checkNumberOperands(op, l, r);
            return std::make_shared<Literal>(std::get<double>(*l) <= std::get<double>(*r));
        case EQUAL_EQUAL:
            return std::make_shared<Literal>(*l == *r);
        case BANG_EQUAL:
            return std::make_shared<Literal>(*l != *r);
    }
}

std::string UnaryExpr::toString() {
    return "(" + op->toString() + " " +  expr->toString() + ")";
}

std::shared_ptr<Literal> UnaryExpr::evaluate() {
    auto right = expr->evaluate();


    switch(op->type) {
        case MINUS:
            checkNumberOperand(op, right);
            return std::make_shared<Literal>(-1 * std::get<double>(*right));
        case BANG:
        {
            if(std::holds_alternative<bool>(*right)) {
                *right = !std::get<bool>(*right);
                return right;
            }
            break;
        }

        default:
            break;
    }

    return nullptr;
}

std::string GroupingExpr::toString() {
    return "(group " + expr->toString() + ")";
}

std::shared_ptr<Literal> GroupingExpr::evaluate() {
    return expr->evaluate();
}

std::string LiteralExpr::toString() {
    if(std::holds_alternative<std::string>(*literal)) {
        return std::get<std::string>(*literal);
    }

    if(std::holds_alternative<int>(*literal)) {
        return std::to_string(std::get<int>(*literal));
    }

    if(std::holds_alternative<long>(*literal)) {
        return std::to_string(std::get<long>(*literal));
    }

    if(std::holds_alternative<double>(*literal)) {
        return std::to_string(std::get<double>(*literal));
    }

    return "";
}

std::shared_ptr<Literal> LiteralExpr::evaluate() {
    return literal;
}

