//
// Created by ryousuke kaga on 2023/11/06.
//

#include "Scanner.h"

Scanner::Scanner(std::string source): source(std::move(source)) {
    nameTokenMap["and"] = AND;
    nameTokenMap["class"] = CLASS;
    nameTokenMap["else"] = ELSE;
    nameTokenMap["false"] = FALSE;
    nameTokenMap["for"] = FOR;
    nameTokenMap["fun"] = FUN;
    nameTokenMap["if"] = IF;
    nameTokenMap["nil"] = NIL;
    nameTokenMap["or"] = OR;
    nameTokenMap["print"] = PRINT;
    nameTokenMap["return"] = RETURN;
    nameTokenMap["super"] = SUPER;
    nameTokenMap["this"] = THIS;
    nameTokenMap["true"] = TRUE;
    nameTokenMap["var"] = VAR;
    nameTokenMap["while"] = WHILE;
}

std::vector<Token> Scanner::scanTokens() {
    while(!isAtEnd()) {
        start = current;
        scanToken();
    }

    tokens.emplace_back(M_EOF, "", nullptr, line);

    return tokens;
}

void Scanner::scanToken() {
    char c = advance();
    switch(c) {
        case('('): addToken(LEFT_PAREN, nullptr); break;
        case(')'): addToken(RIGHT_PAREN, nullptr); break;
        case('{'): addToken(LEFT_BRACE, nullptr); break;
        case('}'): addToken(RIGHT_BRACE, nullptr); break;
        case(','): addToken(COMMA, nullptr); break;
        case('.'): addToken(DOT, nullptr); break;
        case('-'): addToken(MINUS, nullptr); break;
        case('+'): addToken(PLUS, nullptr); break;
        case(';'): addToken(SEMICOLON, nullptr); break;
        case('*'): addToken(STAR, nullptr); break;
        case('!'): addToken(match('=') ? BANG_EQUAL : BANG, nullptr); break;
        case('='): addToken(match('=') ? EQUAL_EQUAL: EQUAL, nullptr); break;
        case('<'): addToken(match('=') ? LESS_EQUAL: LESS, nullptr); break;
        case('>'): addToken(match('=') ? GREAT_EQUAL: GREAT, nullptr); break;
        case('/'):
            if(match('/')) {
                while(peek() != '\n' && !isAtEnd()) advance();
            } else {
                addToken(SLASH, nullptr);
            }
            break;
        case(' '):
        case('\r'):
        case('\t'):
            break;
        case('\n'):
            line++;
            break;
        case('"'): string(); break;
        case('o'):
            if(match('r'))
                addToken(OR, nullptr);
            break;
        default:
            if(isdigit(c)) {
                number();
            } else {
                Interpreter::error(nullptr, "Unexpected character");
            }
            break;
    }
}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

char Scanner::advance() {
    return source[current++];
}

void Scanner::addToken(TokenType type, const std::shared_ptr<Literal>& literal) {
    std::string text = source.substr(start, current - start);
    tokens.emplace_back(type, text, literal, line);
}

bool Scanner::match(char expected) {
    if(isAtEnd()) return false;
    if(source[current] != expected) return false;

    current++;
    return true;
}

char Scanner::peek() {
    if(isAtEnd()) return '\0';
    return source[current];
}

char Scanner::peekNext() {
    if(current + 1 >= source.length()) return '\0';
    return source[current + 1];
}

void Scanner::string() {
    while(peek() != '"' && !isAtEnd()) {
        if(peek() == '\n') line++;
        advance();
    }

    if(isAtEnd()) {
        Interpreter::error(nullptr, "Unterminated string.");
        return;
    }

    advance();

    auto literal = std::make_shared<Literal>(new std::string(source.substr(start + 1, current - start - 2)));
    addToken(STRING, literal);
}

void Scanner::number() {
    while(isdigit(peek())) advance();

    if(peek() == '.' && isdigit(peekNext())) {
        advance();

        while(isdigit(peek())) advance();
    }

    auto literal = std::make_shared<Literal>(std::stod(source.substr(start, current)));
    addToken(NUMBER, literal);
}

void Scanner::identifier() {
    while(isAlphaNumeric(peek())) advance();

    std::string text = source.substr(start, current);
    TokenType type;
    auto it = nameTokenMap.find(text);
    if(it == nameTokenMap.end())
        type = IDENTIFIER;
    else
        type = it->second;

    addToken(type, nullptr);
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            c == '_';
}

bool Scanner::isAlphaNumeric(char c) {
    return isAlpha(c) || isdigit(c);
}
