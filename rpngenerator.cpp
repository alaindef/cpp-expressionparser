#include "rpngenerator.h"
#include "utils.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void RpnGenerator::printRPN(const vector<RPNToken>& RPNTokens, int tab){
    cout << "RPN sequence:\n";
    if (vartab->errorlevel==0) return;
    cout << "opcode : ";
    for (const RPNToken& element : RPNTokens)
        cout << "\t" << ppOC[static_cast<int>(element.opcode)] << " " ;
    cout << endl;
    cout << "opcode: ";
    for (const RPNToken& element : RPNTokens)
        cout << "\t" << static_cast<int>(element.opcode) << " ";
    cout << endl;
    cout << "arity : ";
    for (const RPNToken& element : RPNTokens)
        cout << "\t" << element.arity << " ";
    cout << endl;
    cout << "value : ";
    for (const RPNToken& element : RPNTokens)
        cout << "\t" << element.value << " ";
    cout << endl;
}


bool RpnGenerator::precedenceIs2(TkList tkList){
    // the current operator is "+" or "-".
    // we check if it it a binary operator (arity 2, precedence 1) or a unary op (arity 1, precedence 2)
    // this depends on the previous token
    if ((tkList.cursor == 1) ||
        ( ! isa(tkList.get(-2), {OC::PAR_R, OC::VAR, OC::NUM}))) {
        return true;
    }
    return false;
}

void RpnGenerator::pushToken(Token tk, vector<RPNToken> &out ){
    RPNToken newRPNToken;
    newRPNToken.opcode  = tk.opcode;
    newRPNToken.arity   = tk.arity;
    newRPNToken.value   = tk.value;
    out.push_back(newRPNToken);
}

vector<RpnGenerator::RPNToken> RpnGenerator::makeRPN(vector<Token> tkListIn)
{
    // we will move the input token list into a structure TkList, equipped with member funtions
    TkList tkList;
    tkList.tokens = tkListIn; 
    
    tokensout.clear();
    try {
        Token tk = tkList.pop();
        expr(tk, tkList);
    } catch (const exception& e) {
        cout << "\n\n!!! PARSE ERROR:" << e.what() << endl<< endl;;
    };
    printRPN(tokensout, 5);//teut
    return tokensout;
}

Token RpnGenerator::nextToken(TkList& tkList)
{
    if (tkList.done()) throw invalid_argument("symbols missing!");
    Token next = tkList.pop();
    return next;
}

void RpnGenerator::expr0_val(Token& tk, TkList& tkList){
    if (isa(tk, {OC::VAR, OC::NUM})){
        pushToken(tk, tokensout);
        tk = tkList.pop();
    } else
        expr1_par(tk, tkList);
}

void RpnGenerator::expr1_par(Token& tk, TkList& tkList){
    if (isa(tk, {OC::PAR_L})) {
        tk = tkList.pop();
        expr13_tst(tk, tkList);
        if (tk.opcode != OC::PAR_R)
            throw invalid_argument("received " + static_cast<int>(tk.opcode));
        tk = nextToken(tkList);
    }
}

void RpnGenerator::expr2_plus1(Token& tk, TkList& tkList){
    expr0_val(tk, tkList);
    if (precedenceIs2(tkList)){
        // this means pass or change sign (unary operator)
        tk.arity= 1;
        if (tk.opcode==OC::ADD) tk.opcode = OC::PAS;
        else tk.opcode = OC::CHS;                               //!!! poor coding
        Token save = tk;
        tk = tkList.pop();
        expr0_val(tk, tkList);
        pushToken(save, tokensout);
    }
}

void RpnGenerator::expr3_mul(Token& tk, TkList& tkList){
    expr2_plus1(tk, tkList);
    if (tk.precedence == 3){
        Token save = tk;
        tk = tkList.pop();
        expr3_mul(tk, tkList);
        pushToken(save, tokensout);
    }
}

void RpnGenerator::expr4_plus(Token& tk, TkList& tkList){
    expr3_mul(tk, tkList);
    if (tk.precedence == 4){
        Token save = tk;
        tk = tkList.pop();
        expr4_plus(tk, tkList);
        pushToken(save, tokensout);
    }
}

void RpnGenerator::expr6_less(Token& tk, TkList& tkList){
    expr4_plus(tk, tkList);
    if (tk.precedence == 6){
        Token save = tk;
        tk = tkList.pop();
        expr6_less(tk, tkList);
        pushToken(save, tokensout);
    }
}

void RpnGenerator::expr7_eq(Token& tk, TkList& tkList){                                                                           //TODO !!!
    expr6_less(tk, tkList);
    if (tk.precedence == 7){
        Token save = tk;
        tk = tkList.pop();
        expr7_eq(tk, tkList);
        pushToken(save, tokensout);
    }
}

void RpnGenerator::expr13_tst(Token& tk, TkList& tkList){
    expr7_eq(tk, tkList);
    if (tk.precedence == 13){
        Token save = tk;
        tk = tkList.pop();
        expr7_eq(tk, tkList);                                                                // no need to push "?", ":" is ternary, will take care
        save = tk;
        tk = nextToken(tkList);
        expr7_eq(tk, tkList);
        pushToken(save, tokensout);
    }
}

void RpnGenerator::expr14_assgn(Token& tk, TkList& tkList){
    Token save = tkList.get(0);
    pushToken(tk, tokensout);
        tk = tkList.pop();
        tk = tkList.pop();
    expr13_tst(tk, tkList);
    pushToken(save, tokensout);
}
void RpnGenerator::expr(Token& tk, TkList tkList){
    Token save = tkList.get(0);
    if (isa(tk, {OC::VAR}) &(save.precedence == 14))
        expr14_assgn(tk, tkList);
    else
        expr13_tst(tk, tkList);
}