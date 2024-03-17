#ifndef AST_H
#define AST_H
#pragma once
#include <vector>
#include "defs.h"

class ast
{
public:
    ast(std::vector<Token> tokens){};
    std::vector<Token>& toAST();

private:
    std::vector<Token> tokens;
    int cursor = 0;
    Token nextToken(const std::string& from, std::vector<TokenType> expected);

};

#endif // AST_H
// class Pass2
// {
// public:
//     Pass2(std::vector<Token> tokens) : tokens(pTokens){}
//     std::vector<Token>& toRPN();

// private:
//     std::vector<Token> tokens;
//     int cursor = 0;
//     std::vector<Token> tokensout;
//     Token nextToken(const std::string& from, std::vector<TokenType> expected);

//     void expr(Token& tk);
//     void expr0(Token& tk);
//     void expr1(Token& tk);
//     void expr2(Token& tk);
//     void expr3(Token& tk);
//     void expr4(Token& tk);
//     void expr6(Token& tk);
//     void expr7(Token& tk);
//     void expr13(Token& tk);
//     void expr14(Token& tk);
// };
