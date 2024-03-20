#pragma once
#ifndef PASS0_H
#define PASS0_H


#include <string>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include <map>;

// #include "defs.h"


using namespace std;


class pass0
{
public:
    pass0();

    void tokenize(string textIn);
    vector<string> keywords;

    // private:
    //     typedef struct {
    //         string type;
    //         string content;
    //         int opcode;
    //         int arity;
    //         int precedence;
    //         uint cursor;
    //     } Token;
    vector<string> language;
    uint langsize;
    // vector<Token>  tokens;
    void match(string s, string &out);

    // typedef std::map<std::string, string> kvPair;
    // typedef std::map<std::string, string> MapType;


    typedef map<std::string, string> MapType;
    MapType languageMap;
    MapType::iterator mapIter;
    void defineLanguage();
    std::pair<string, string>  findKeyword(const std::map<std::string, string>& language, const string& s);
};

#endif // PASS0_H
