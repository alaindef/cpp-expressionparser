#pragma once
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <functional>
#include "rpngenerator.h"

class Calculator
{
public:;;

    Calculator();
    Calculator(VarTable *vt) : vartab(vt){}
    void calcandprint(std::vector<RpnGenerator::RPNToken> &tokenlist, bool prt);
    float calc(std::vector<RpnGenerator::RPNToken> &tokenlist);

private:
    VarTable * vartab;

    std::vector<RpnGenerator::RPNToken> inputRPNTokenList;
    static float fun_elv(float x, float y, float z){
        if (x>0.5) return y; else return z;}
    int cursor;

};



#endif // CALCULATOR_H
