#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "defs.h"

#include <vector>
#include <functional>
#include <iostream>

#include <string>



// some operator functions
float fun_pas(float x){return +x;}                  // opcode 0 arity 1 precedence 2
float fun_chs(float x){return -x;}                  // opcode 1 arity 1 precedence 2

float fun_mul(float x, float y){return (x*y);}      // opcode 0 arity 2 precedence 3
float fun_div(float x, float y){
    float res = ((float)x/(float)y);
    return res;
}      // opcode 1 arity 2 precedence 3
float fun_add(float x, float y){return (x+y);}      // opcode 2 arity 2 precedence 4
float fun_sub(float x, float y){return (x-y);}      // opcode 3 arity 2 precedence 4
float fun_lt(float x, float y){return x<y;}         // opcode 4 arity 2 precedence 6
float fun_gt(float x, float y){return x>y;}         // opcode 5 arity 2 precedence 6
float fun_eq(float x, float y){return x==y;}        // opcode 6 arity 2 precedence 7
float fun_ass(float, float y){
    float ass_result = y;
    std::cout << "assignment result. a = " << ass_result<< std::endl;
    return ass_result;}                             // opcode 7 arity 2 precedence 14

float fun_elv(float x, float y, float z){
    if (x) return y; else return z;}                // opcode 0 arity 3 precedence 13

std::vector<std::function<float(float)>> funList1;                // arity 1
std::vector<std::function<float(float,float)>> funList2;          // arity 2
std::vector<std::function<float(float,float,float)>> funList3;    // arity 3

void initOperators(){
    // functions ar pushed in the order of their opcode
    funList1.push_back(fun_pas);
    funList1.push_back(fun_chs);

    funList2.push_back(fun_mul);
    funList2.push_back(fun_div);
    funList2.push_back(fun_add);
    funList2.push_back(fun_sub);
    funList2.push_back(fun_lt);
    funList2.push_back(fun_gt);
    funList2.push_back(fun_eq);
    funList2.push_back(fun_ass);

    funList3.push_back(fun_elv);
}

vector<string> report={""};
const string pp_arity[4] = {"LITTERAL", "UNARY expr", "BINARY expr", "TERNARY expr"};
string level = "";
const string level_inc = "   ";

float calc(std::vector<Token>& tokenlist){
    if (tokenlist.size() == 0) return 0.f;
    float v1;
    float v2;
    float v3;

    float res;

    level += level_inc;

    Token last = tokenlist.back();
    tokenlist.pop_back();
    switch (last.arity){
    case 0:
        res =stof(last.content);
        break;
    case 1:
        v1 =calc(tokenlist);
        res = -v1;
        break;
    case 2:
        v1 =calc(tokenlist);
        v2 =calc(tokenlist);
        res = funList2[last.opcode](v2,v1);
        break;
    case 3:
        v1 =calc(tokenlist);
        v2 =calc(tokenlist);
        v3 =calc(tokenlist);
        funList3[last.opcode](v1,v2,v3);
        if (v3 > 0.5) res = v2; else res = v1;
        break;
    }
    report.push_back(level + pp_arity[last.arity] + " op " + last.content + " \n");
    level = level.substr(level_inc.size(), level.size());
    return res;
}

void calcandprint(std::vector<Token> s) {
    report={""};
    std::cout << "\nkind: very kind\n body:\n";
    float result = calc(s);
    reverse(report.begin(),report.end());
    for (string el:report) cout << el;
    std::cout << "\nEVALUATION RESULT ==> " << ((result > 7.999 && result < 8.001) ? std::string("NEUF!") : std::to_string(result)) << std::endl <<
        "_______________________________________________________________________________" << std::endl;
}

#endif // INTERPRETER_H
