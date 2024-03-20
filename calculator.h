#pragma once
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <functional>
#include "defs.h"

class Calculator
{
public:
    static uint vars[9];                            //ik krijg dit niet aan de praat

    Calculator();
    float calcandprint(RPNTokenList &tokenlist);
    float calc(RPNTokenList &tokenlist);

// private:
    RPNTokenList inputRPNTokenList;

    // some operator functions
    static float fun_num(std::string content){return stof(content);}
    static float fun_var(std::string content){return stof(content);}

    static float fun_pas(float x){return +x;}                  // opcode 0 arity 1 precedence 2
    static float fun_chs(float x){return -x;}                  // opcode 1 arity 1 precedence 2

    static float fun_mul(float x, float y){return (x*y);}      // opcode 0 arity 2 precedence 3
    static float fun_div(float x, float y){
        float res = ((float)x/(float)y);
        return res;
    }      // opcode 1 arity 2 precedence 3
    static float fun_add(float x, float y){return (x+y);}       // opcode 2 arity 2 precedence 4
    static float fun_sub(float x, float y){return (x-y);}       // opcode 3 arity 2 precedence 4
    static float fun_lt(float x, float y){return x<y;}          // opcode 4 arity 2 precedence 6
    static float fun_gt(float x, float y){return x>y;}          // opcode 5 arity 2 precedence 6
    static float fun_eq(float x, float y){return x==y;}         // opcode 6 arity 2 precedence 7
    static float fun_ass(float x, float y);                     // opcode 7 arity 2 precedence 14

    static float fun_elv(float x, float y, float z){
        if (x>0.5) return y; else return z;}                // opcode 0 arity 3 precedence 13

    std::vector<std::function<float(std::string)>> funList0;                   // arity 0 => digit or variable
    std::vector<std::function<float(float)>> funList1;              // arity 1
    std::vector<std::function<float(float,float)>> funList2;        // arity 2
    std::vector<std::function<float(float,float,float)>> funList3;  // arity 3
};

#endif // CALCULATOR_H
