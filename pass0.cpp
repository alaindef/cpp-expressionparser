#include "pass0.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include "defs.h"
#include <vector>

using namespace std;

void pass0::defineKeywords(){


    keywords={
        {"*",   {0,  2,  3}},
        {"/",   {1,  2,  3}},
        {"+",   {2,  2,  4}},               //alternative {0, 1, 2}
        {"-",   {3,  2,  4}},               //alternative {1, 1, 2}
        {"<",   {4,  2,  6}},
        {"<=",  {5,  2,  6}},
        {">",   {6,  2,  6}},
        {">=",  {7,  2,  6}},
        {"==",  {8,  2,  7}},
        {"!=",  {9,  2,  7}},
        {"?",   {15, 0, 13}},
        {":",   {16, 3, 13}},
        {"(",   {20, 0,  0}},
        {")",   {21, 0,  0}}
    };
    // keywords.insert({"=",   {18, 9, 14}});
}

pass0::pass0() {
    pass0::defineKeywords();
}

void pass0::printMap(){                         // for debugging
    cout << "\nmap is =====> ";
    for (auto entry = pass0::keywords.rbegin(); entry != pass0::keywords.rend(); ++entry){
        cout << entry->first << " " << entry->second.opcode << " " << entry->second.arity << " " << entry->second.precedence << "\n" ;
    }
    cout << "\n";
}

pass0::KeyPairType pass0::findKeyword(const map<string, Token0>& keys, const string& s) {
    // ordered Map stores "==" always after "=", "==" would never be found. so we loop through the map in reverse
    for (auto entry = keys.rbegin(); entry != keys.rend(); ++entry){
        const string& key = entry->first;
        if (s.compare(0, key.size(), key) == 0) return {entry->first, entry->second};
    }
    return {"", {-1, -1, -1}}; // pair if no match is found
}

Token0List pass0::tokenize(string textIn){
    string out = "";
    uint cursor = 0;
    string next = "";
    pass0::KeyPairType keyPairFound;
    uint moveCursor;

    Token0List tokens;
    Token0 token;

    while (cursor < textIn.size() ){
        // if (int(s[cursor1]) == 32) {
        if (string() + textIn[cursor] == " "){                              // skip blanks
            cursor++; continue;
        }
        keyPairFound = findKeyword(pass0::keywords,textIn.substr(cursor));
        if (keyPairFound.first == ""){                                      // a digit or variable
            next += textIn[cursor];
            moveCursor = 1;
            token.opcode = 80; token.arity = 0; token.precedence =0;
        }else{
            if (next.size() > 0) out  += " {" + next + "}";                 // a keyword
            next="";
            token = keyPairFound.second;
            out  += " |" + keyPairFound.first + "|";
            // out  += " " + keyPairFound->second.opcode;
            moveCursor = keyPairFound.first.size();
        }
        cursor += moveCursor;
        tokens.push_back(token);
    }
    if (next.size() > 0)
        out  += " {" + next +"} ";
    tokens.push_back({90,0,0});

    cout << "\nout= " << out <<endl;
    return tokens;
}
