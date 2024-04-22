#pragma once
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <functional>
#include "rpngenerator.h"

    void calcandprint(std::vector<RPNToken> &tokenlist, VarTable * vartabel, bool prt);
    float calc(std::vector<RPNToken> &tokenlist, VarTable * vartabel);

    static float fun_elv(float x, float y, float z){
        if (x>0.5) return y; else return z;}
    static int cursor;


#endif // CALCULATOR_H
