#pragma once
#ifndef PASS0_H
#define PASS0_H

#include "defs.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include <map>;
#include <array>;


using namespace std;



class pass0
{
public:
    pass0();

    Token0List tokenize(string textIn);

    using KeyPairType = pair<string, Token0>;
    using MapType = map<string, Token0>;

    MapType keywords;
    // MapType::iterator mapIter;


private:

    void defineKeywords();
    bool findKeyword(const std::map<string, Token0>& language, const string& s, KeyPairType& result);
    int getVarIndex(vector<string> &varnames, string param);
    void storeValueOrIndex(string param, Token0& token);
    void printMap();
};

#endif // PASS0_H
