#pragma once
#ifndef PASS0_H
#define PASS0_H


#include <string>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include <map>;
#include <array>;

#include "defs.h"

using namespace std;

// using Token0 = array<int, 3>;

class pass0
{
public:
    pass0();

    Token0List tokenize(string textIn);

    using KeyPairType = pair<string, Token0>;
    using MapType = map<string, Token0>;

    MapType keywords;
    // MapType::iterator mapIter;

    void defineKeywords();
    KeyPairType findKeyword(const std::map<string, Token0>& language, const string& s);

    void printMap();
};

#endif // PASS0_H
