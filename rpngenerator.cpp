#include "rpngenerator.h"
#include "utils.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void expr(Token &tk, TkList tkList, vector<RPNToken> &tokensout);
void expr1_par(Token &tk, TkList &tkList, vector<RPNToken> &tokensout);
void expr0_val(Token &tk, TkList &tkList, vector<RPNToken> &tokensout);
void expr2_plus1(Token &tk, TkList &tkList, vector<RPNToken> &tokensout);
void expr3_mul(Token &tk, TkList &tkList, vector<RPNToken> &tokensout);
void expr4_plus(Token &tk, TkList &tkList, vector<RPNToken> &tokensout);
void expr6_less(Token &tk, TkList &tkList, vector<RPNToken> &tokensout);
void expr7_eq(Token &tk, TkList &tkList, vector<RPNToken> &tokensout);
void expr13_tst(Token &tk, TkList &tkList, vector<RPNToken> &tokensout);

void printRPN(const vector<RPNToken> &RPNTokens, int tab, int report)
{
    if (!report)
        return;
    cout << "******************** RPN sequence ********************\n";
    // if (vartab->errorlevel==0) return;
    cout << "opcode : ";
    for (const RPNToken &element : RPNTokens)
        cout << "\t" << ppOC[static_cast<int>(element.opcode)] << " ";
    cout << endl;
    cout << "opcode: ";
    for (const RPNToken &element : RPNTokens)
        cout << "\t" << static_cast<int>(element.opcode) << " ";
    cout << endl;
    cout << "arity : ";
    for (const RPNToken &element : RPNTokens)
        cout << "\t" << element.arity << " ";
    cout << endl;
    cout << "value : ";
    for (const RPNToken &element : RPNTokens)
        cout << "\t" << element.value << " ";
    cout << endl;
}

bool isa(const Token &token, const vector<OC> &allowedTypes)
{
    //    check if the symbol sym is one of the symbols in the list op
    return (count(allowedTypes.begin(), allowedTypes.end(), token.opcode) > 0);
    return true;
}

bool precedenceIs2(TkList tkList)
{
    // the current operator is "+" or "-".
    // we check if it is a binary operator (arity 2, precedence 1) or a unary op (arity 1, precedence 2)
    // this depends on the previous token
    Token t = tkList.get(-2);
    if (isa(t, {OC::NIL}))
        return true; // expression starts with + or -
    if (isa(t, {OC::PAR_R, OC::VAR, OC::NUM}))
        return false;
    return true;
}

void pushToken(Token tk, vector<RPNToken> &out)
{
    RPNToken newRPNToken;
    newRPNToken.opcode = tk.opcode;
    newRPNToken.arity = tk.arity;
    newRPNToken.value = tk.value;
    out.push_back(newRPNToken);
}

vector<RPNToken> makeRPN(vector<Token> tkListIn, int report)
{
    // we will move the input token list into a structure TkList, equipped with member funtions
    TkList tkList;
    tkList.tokens = tkListIn;
    vector<RPNToken> tokensout;

    tokensout.clear();
    Token tk = tkList.pop();
    try
    {
        Token tk = tkList.pop();
        expr(tk, tkList, tokensout);
    }
    catch (const exception &e)
    {
        cout << "\n\n!!! PARSE ERROR:" << e.what() << endl
             << endl;
        ;
    };
    printRPN(tokensout, 5, report);
    return tokensout;
}

vector<RPNToken> makeRPN(string textIn,
                         const map<std::string, Token> &keywords,
                         VarTable &vartabel, int report)
{
    vector<Token> tokens = makeTokenList(textIn, keywords, vartabel, report);
    return makeRPN(tokens, report);
}

Token nextToken(TkList &tkList)
{
    if (tkList.done())
        throw invalid_argument("symbols missing!");
    Token next = tkList.pop();
    return next;
}

void expr0_val(Token &tk, TkList &tkList, vector<RPNToken> &tokensout)
{
    if (isa(tk, {OC::VAR, OC::NUM}))
    {
        pushToken(tk, tokensout);
        tk = tkList.pop();
    }
    else
        expr1_par(tk, tkList, tokensout);
}

void expr1_par(Token &tk, TkList &tkList, vector<RPNToken> &tokensout)
{
    if (isa(tk, {OC::PAR_L}))
    {
        tk = tkList.pop();
        expr13_tst(tk, tkList, tokensout);
        if (tk.opcode != OC::PAR_R)
            throw invalid_argument("received " + static_cast<int>(tk.opcode));
        tk = nextToken(tkList);
    }
}

void expr2_plus1(Token &tk, TkList &tkList, vector<RPNToken> &tokensout)
{
    expr0_val(tk, tkList, tokensout);
    if (precedenceIs2(tkList))
    {
        // this means pass or change sign (unary operator)
        tk.arity = 1;
        if (tk.opcode == OC::ADD)
            tk.opcode = OC::PAS;
        else
            tk.opcode = OC::CHS; //!!! poor coding
        Token save = tk;
        tk = tkList.pop();
        expr0_val(tk, tkList, tokensout);
        pushToken(save, tokensout);
    }
}

void expr3_mul(Token &tk, TkList &tkList, vector<RPNToken> &tokensout)
{
    expr2_plus1(tk, tkList, tokensout);
    if (tk.precedence == 3)
    {
        Token save = tk;
        tk = tkList.pop();
        expr3_mul(tk, tkList, tokensout);
        pushToken(save, tokensout);
    }
}

void expr4_plus(Token &tk, TkList &tkList, vector<RPNToken> &tokensout)
{
    expr3_mul(tk, tkList, tokensout);
    if (tk.precedence == 4)
    {
        Token save = tk;
        tk = tkList.pop();
        expr4_plus(tk, tkList, tokensout);
        pushToken(save, tokensout);
    }
}

void expr6_less(Token &tk, TkList &tkList, vector<RPNToken> &tokensout)
{
    expr4_plus(tk, tkList, tokensout);
    if (tk.precedence == 6)
    {
        Token save = tk;
        tk = tkList.pop();
        expr6_less(tk, tkList, tokensout);
        pushToken(save, tokensout);
    }
}

void expr7_eq(Token &tk, TkList &tkList, vector<RPNToken> &tokensout)
{ // TODO !!!
    expr6_less(tk, tkList, tokensout);
    if (tk.precedence == 7)
    {
        Token save = tk;
        tk = tkList.pop();
        expr7_eq(tk, tkList, tokensout);
        pushToken(save, tokensout);
    }
}

void expr13_tst(Token &tk, TkList &tkList, vector<RPNToken> &tokensout)
{
    expr7_eq(tk, tkList, tokensout);
    if (tk.precedence == 13)
    {
        Token save = tk;
        tk = tkList.pop();
        expr7_eq(tk, tkList, tokensout); // no need to push "?", ":" is ternary, will take care
        save = tk;
        tk = nextToken(tkList);
        expr7_eq(tk, tkList, tokensout);
        pushToken(save, tokensout);
    }
}

void expr14_assgn(Token &tk, TkList &tkList, vector<RPNToken> &tokensout)
{
    Token save = tkList.get(0);
    pushToken(tk, tokensout);
    tk = tkList.pop();
    tk = tkList.pop();
    expr13_tst(tk, tkList, tokensout);
    pushToken(save, tokensout);
}

void expr(Token &tk, TkList tkList, vector<RPNToken> &tokensout)
{
    Token save = tkList.get(0);
    if (isa(tk, {OC::VAR}) & (save.precedence == 14))
        expr14_assgn(tk, tkList, tokensout);
    else
        expr13_tst(tk, tkList, tokensout);
}