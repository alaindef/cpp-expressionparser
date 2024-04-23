#pragma once
#ifndef tokengenerator_H
#define tokengenerator_H

#include "vartable.h"
#include <string>
#include <vector>
#include <map>

enum class OC{NUM, VAR, MUL, DIV, ADD, SUB, PAS, CHS, LT, LE, GT, GE, EQ, NE, ASS, QU, COL, PAR_L, PAR_R, NIL};

struct Token {
    OC opcode;
    int arity;
    int precedence;
    float value;} ;

vector<Token> makeTokenList(string textIn,
                            const map<std::string,Token>& keywords,
                            VarTable& vartabel);

#endif // tokengenerator_H
