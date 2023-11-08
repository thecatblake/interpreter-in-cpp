//
// Created by ryousuke kaga on 2023/11/08.
//

#include "Expr.h"

std::string Expr::toString() {
    return "";
}

std::string BinaryExpr::toString() {
    return "(" + op->toString() + " " + left->toString() + " " + right->toString() + ")";
}

std::string UnaryExpr::toString() {
    return "(" + op->toString() + " " +  expr->toString() + ")";
}

std::string GroupingExpr::toString() {
    return "(group " + expr->toString() + ")";
}

std::string LiteralExpr::toString() {
    if(std::holds_alternative<std::string*>(*literal)) {
        return *std::get<std::string*>(*literal);
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

