//
// Created by ryousuke kaga on 2023/11/09.
//

#include "Parser.h"

Expr* Parser::expression() {
    return equality();
}

Expr* Parser::equality() {
    Expr* expr = comparison();

    while(match({BANG_EQUAL, EQUAL_EQUAL})) {
        Token* op = previous();
        Expr* right = comparison();
        expr = new BinaryExpr(expr, op, right);
    }

    return expr;
}

bool Parser::match(std::initializer_list<TokenType> types) {
    for(auto & type : types) {
        if(check(type)) {
            advance();
            return true;
        }
    }

    return false;
}

bool Parser::check(TokenType type) {
    if(isAtEnd()) return false;
    return peek()->type == type;
}

Token *Parser::advance() {
    if(!isAtEnd()) current++;
    return previous();
}

bool Parser::isAtEnd() {
    return peek()->type == M_EOF;
}

Token *Parser::peek() {
    return &tokens[current];
}

Token *Parser::previous() {
    return &tokens[current - 1];
}

Expr *Parser::comparison() {
    Expr* expr = term();

    while(match({GREAT, GREAT_EQUAL, LESS, LESS_EQUAL})) {
        Token* op = previous();
        Expr* right = factor();
        expr = new BinaryExpr(expr, op, right);
    }

    return expr;
}

Expr *Parser::term() {
    Expr* expr = factor();

    while(match({MINUS, PLUS})) {
        Token* op = previous();
        Expr* right = factor();
        expr = new BinaryExpr(expr, op, right);
    }

    return expr;
}

Expr *Parser::factor() {
    Expr* expr = unary();

    while(match({SLASH, STRING})) {
        Token* op = previous();
        Expr* right = unary();
        expr = new BinaryExpr(expr, op, right);
    }

    return expr;
}

Expr *Parser::unary() {
    if(match({BANG, MINUS})) {
        Token* op = previous();
        Expr* right = unary();
        return new UnaryExpr(op, right);
    }

    return primary();
}

Expr *Parser::primary() {
    if(match({FALSE})) return new LiteralExpr(std::make_shared<Literal>(false));
    if(match({TRUE})) return new LiteralExpr(std::make_shared<Literal>(true));
    if(match({NIL})) return new LiteralExpr(std::make_shared<Literal>(nullptr));
    if(match({NUMBER, STRING})) return new LiteralExpr(previous()->literal);

    if(match({LEFT_PAREN})) {
        Expr* expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return new GroupingExpr(expr);
    }

    throw error(peek(), "Expect expression.");
}

Token *Parser::consume(TokenType type, char *message) {
    if(check(type)) return advance();
    throw error(peek(), message);
}

ParserError Parser::error(Token *token, const char *message) {
    Interpreter::error(token, message);
    return {"f"};
}

void Parser::synchronize() {
    advance();

    while(!isAtEnd()) {
        if(previous()->type == SEMICOLON) return;

        switch (peek()->type) {
            case CLASS:
            case FUN:
            case VAR:
            case FOR:
            case IF:
            case WHILE:
            case PRINT:
            case RETURN:
                return;
            default:
                break;
        }

        advance();
    }
}

std::vector<std::unique_ptr<Stmt>> Parser::parse() {
    std::vector<std::unique_ptr<Stmt>> statements;
    while(!isAtEnd()) {
        statements.push_back(statement());
    }

    return statements;
}

std::unique_ptr<Stmt> Parser::statement() {
    if(match({PRINT})) return printStatement();

    return expressionStatement();
}

std::unique_ptr<Stmt> Parser::printStatement() {
    Expr* value = expression();
    consume(SEMICOLON, "Expect ';' after value.");
    return std::make_unique<PrintStmt>(value);
}

std::unique_ptr<Stmt> Parser::expressionStatement() {
    Expr* expr = expression();
    consume(SEMICOLON, "Expect ';' after value.");
    return std::make_unique<ExprStmt>(expr);
}

