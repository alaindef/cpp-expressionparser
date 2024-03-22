#include "pass0.h"
#include "defs.h"
#include "utils.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

vector<string>  varNames ={"y","a","ss","b","dd"};
vector<float>   varValues;

void pass0::defineKeywords(){
    keywords={
        {"*",   {0,  2,  3,  0}},
        {"/",   {1,  2,  3,  0}},
        {"+",   {2,  2,  4,  0}},               //alternative {0, 1, 2}
        {"-",   {3,  2,  4,  0}},               //alternative {1, 1, 2}
        {"<",   {4,  2,  6,  0}},
        {"<=",  {5,  2,  6,  0}},
        {">",   {6,  2,  6,  0}},
        {">=",  {7,  2,  6,  0}},
        {"==",  {8,  2,  7,  0}},
        {"!=",  {9,  2,  7,  0}},
        {"=",   {10, 2,  7,  0}},
        {"?",   {15,-1, 13,  0}},
        {":",   {16, 3, 13,  0}},
        {"(",   {20, 0,  0,  0}},
        {")",   {21, 0,  0,  0}}
    };
    // keywords.insert({"=",   {18, 9, 14}});
}

pass0::pass0() {
    pass0::defineKeywords();
}

void pass0::printMap(){                         // for debugging
    cout << "\nmap is =====> ";
    for (auto entry = keywords.rbegin(); entry != keywords.rend(); ++entry){
        cout << entry->first << " " << entry->second.opcode << " " << entry->second.arity << " " << entry->second.precedence << "\n" ;
    }
    cout << "\n";
}

bool pass0::findKeyword(const map<string, Token0>& keys, const string& s, pass0::KeyPairType& result) {
    // ordered Map stores "==" always after "=", "==" would never be found. so we loop through the map in reverse
    for (auto entry = keys.rbegin(); entry != keys.rend(); ++entry){
        const string& key = entry->first;
        if (s.compare(0, key.size(), key) == 0) {result = {entry->first, entry->second}; return true;}
    }
    return false; // pair if no match is found
}

int pass0::getVarIndex(vector<string>& varnames, string param){
    for (uint i=0; i<varnames.size(); i++)
        if (param == varnames[i])
            return i;
    varnames.push_back(param);
    return varnames.size()-1;
}

void pass0::storeValueOrIndex(string param, Token0& token){
    if (isNumeric(param)){
        token.value     = stof(param);
        token.opcode    = 0;
    }
    else{
        token.value = getVarIndex(varNames, param);
        token.opcode= 1;
    }
};

Token0List pass0::tokenize(string textIn){
    string out = "";
    uint cursor = 0;
    string next = "";
    KeyPairType keyPairFound;
    uint moveCursor;

    Token0List tokens;
    Token0 token;

    while (cursor < textIn.size() ){
        if (textIn[cursor] == ' '){cursor++; continue;}
        if (! findKeyword(keywords, textIn.substr(cursor), keyPairFound)){
            // next is a digit or variable because the text at cursor does not start with a keyword
            next += textIn[cursor];                                         // collect coming chars in next
            moveCursor = 1;
            token.opcode = -1; token.arity = 0; token.precedence =0;
        }else{
            if (next.size() > 0) {                                          // next is a num or var
                storeValueOrIndex(next, token);
                    // if num store it in token, if var reserve an index for it in var array
                tokens.push_back(token);
                out  += "\t{" + next + "}";
            }
            next="";
            token = keyPairFound.second;
            tokens.push_back(token);
            out  += "\t|" + keyPairFound.first + "|";
            moveCursor = keyPairFound.first.size();
        }
        cursor += moveCursor;
    }
    if (next.size() > 0){                                         // next is a num or var
        storeValueOrIndex(next, token);
        tokens.push_back(token);
        out  += "\t{" + next +"} ";
    }
    tokens.push_back({90,0,0});

    // cout << "\nout=\t" << out <<endl;
    cout << "\nout=\t" << out <<endl;
    return tokens;
}
