#pragma once
#include <vector>
#include "defs.h"
//PASS 2 will scan the output of PASS1 and generate a list of tokens
// precedence is according to   https://en.cppreference.com/w/cpp/language/operator_precedence#cite_note-2
//                          or  https://en.wikipedia.org/wiki/Order_of_operations

// although pass2 needs far less tokentypes than the types from pass1, we will reuse the definition of pass1 and work with that
class Pass2
    {
public:
    Pass2(std::vector<Token> pTokens) : tokens(pTokens){}
    std::vector<Token>& parse2();

private:
    std::vector<Token> tokens;
    int tokenidx = 0;
    std::vector<Token> tokensout;
    Token nextToken(const std::string& from, std::vector<TokenType> expected);

    void expr(Token& tk);
    void expr0(Token& tk);
    void expr1(Token& tk);
    void expr2(Token& tk);
    void expr3(Token& tk);
    void expr4(Token& tk);
    void expr6(Token& tk);
    void expr7(Token& tk);
    void expr13(Token& tk);
    void expr14(Token& tk);
};
