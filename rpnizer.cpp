#include "rpnizer.h"
#include "defs.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "utils.h"
using namespace std;

void pushToken(Token tk, RPNTokenList& out ){
    RPNToken newRPNToken;
    newRPNToken.content = tk.content;
    newRPNToken.opcode  = tk.opcode;
    newRPNToken.arity   = tk.arity;
    newRPNToken.cursor  = tk.cursor;

    out.push_back(newRPNToken);
};

std::vector<RPNToken>& RPNizer::RPNizer::toRPN()
{
    tokensout.clear();
    try {
        cursor = 0;
        Token tk = nextToken("toRPN", {});
        expr(tk);
    } catch (const exception& e) {
        cout << "\n\n!!! PARSE ERROR:" << e.what() << endl<< endl;;
    };
    return tokensout;
}

Token RPNizer::nextToken(const std::string &from, std::vector<TokenType> expected)
{
    // expected: the list of possible TokenTypes. it is filled in by the calling function
    if (cursor >= tokens.size()) throw invalid_argument("symbols missing!");
    Token next = tokens[cursor++];
    if (expected.empty()) return next;
    if (count(expected.begin(), expected.end(), next.type) > 0) return next;
    // error:
    string ppexpectedList = "";
    for (TokenType t: expected) ppexpectedList += " " + TokenToString(t);
    throw invalid_argument(
        "from " + from + " at cursor=" + to_string(next.cursor) + " symbol=" + next.content + ", " + TokenToString(next.type) +
        " is not one of {" + ppexpectedList + "}"                                                      // "expected" should be the list of expected types
        );
    return next;
}

void RPNizer::expr0(Token& tk){
    if (isa(tk, {t_LETT, t_DIGIT})){
        pushToken(tk, tokensout);
        tk = nextToken("expr0", {t_TIMES, t_DIV, t_LT,t_EQ,t_GT, t_PLUS, t_MINUS, t_PAR_L, t_PAR_R, t_COLON, t_QUEST, t_ETX});
    } else
        expr1(tk);
}

void RPNizer::expr1(Token& tk){
    if (isa(tk, {t_PAR_L})) {
        tk = nextToken("expr1", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
        expr13(tk);
        if (tk.content != ")")
            throw invalid_argument("received " + tk.content);
        tk = nextToken("expr1", {});
    }
}
void RPNizer::expr2(Token& tk){
    expr0(tk);
    if (tk.precedence == 2){
        Token save = tk;
        tk = nextToken("expr2", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
        expr0(tk);
        pushToken(save, tokensout);
    }
}

void RPNizer::expr3(Token& tk){
    expr2(tk);
    if (tk.precedence == 3){
        Token save = tk;
        tk = nextToken("expr3", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
        expr3(tk);
        pushToken(save, tokensout);
    }
}

void RPNizer::expr4(Token& tk){
    expr3(tk);
    if (tk.precedence == 4){
        Token save = tk;
        tk = nextToken("expr4", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
        expr4(tk);
        pushToken(save, tokensout);
    }
}

void RPNizer::expr6(Token& tk){
    expr4(tk);
    if (tk.precedence == 6){
        Token save = tk;
        tk = nextToken("expr6", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
        expr6(tk);
        pushToken(save, tokensout);
    }
}

void RPNizer::expr7(Token& tk){                                                                           //TODO !!!
    expr6(tk);
    if (tk.precedence == 7){
        Token save = tk;
        tk = nextToken("expr7", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS,t_EQ});
        expr7(tk);
        pushToken(save, tokensout);
    }
}

void RPNizer::expr13(Token& tk){
    expr7(tk);
    if (tk.precedence == 13){
        Token save = tk;
        tk = nextToken("expr13", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
        expr7(tk);                                                                // no need to push "?", ":" is ternary, will take care
        save = tk;
        tk = nextToken("expr13", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
        expr7(tk);
        pushToken(save, tokensout);
    }
}

void RPNizer::expr14(Token& tk){
    // Token save = tokens.back();
    Token save = tokens[cursor];
    if (isa(tk, {t_LETT}) &(save.precedence == 14)){
        pushToken(tk, tokensout);
        tk = nextToken("expr14", {t_EQ});
        tk = nextToken("expr14", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
        expr13(tk);
        pushToken(save, tokensout);
    } else
        expr13(tk);
}

void RPNizer::expr(Token& tk){
    expr14(tk);
}
