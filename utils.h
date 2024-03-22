#pragma once
#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include "defs.h"
#include "rpnizer.h"

inline bool isa(const Token& token, const std::vector<TokenType>& allowedTypes){
    //    check if the symbol sym is one of the symbols in the list op
    return(std::count(allowedTypes.begin(), allowedTypes.end(), token.type) > 0);
}

// some printing stuff
inline void printPass(const std::vector<Token>& symList, int tab){
    std::cout << "type  : ";
    for (const Token& element : symList)
        std::cout << std::setw(tab) << TokenToString(element.type) << " ";
    std::cout << std::endl;
    std::cout << "cont  : ";
    for (const Token& element : symList)
        std::cout << std::setw(tab) << element.content << " ";
    std::cout << std::endl;
    std::cout << "opcode: ";
    for (const Token& element : symList)
        std::cout << std::setw(tab) << element.opcode << " ";
    std::cout << std::endl;
    std::cout << "arity : ";
    for (const Token& element : symList)
        std::cout << std::setw(tab) << element.arity << " ";
    std::cout << std::endl;
    std::cout << "prcd  : ";
    for (const Token& element : symList)
        std::cout << std::setw(tab) << element.precedence << " ";
    std::cout << std::endl;
    // std::cout << "cursr : ";
    // for (const Token& element : symList)
    //     std::cout << std::setw(tab) << element.cursor<< " ";
    // std::cout << std::endl;
}


inline void printRPN(const RPNTokenList& symList, int tab){
    std::cout << "cont  : ";
    for (const RPNToken& element : symList)
        std::cout << std::setw(tab) << element.content << " ";
    std::cout << std::endl;
    std::cout << "opcode: ";
    for (const RPNToken& element : symList)
        std::cout << std::setw(tab) << element.opcode << " ";
    std::cout << std::endl;
    std::cout << "arity : ";
    for (const RPNToken& element : symList)
        std::cout << std::setw(tab) << element.arity << " ";
    std::cout << std::endl;
}


inline void printPass0(const Token0List& symList, int tab){
    std::cout << "opcode: ";
    for (const Token0& element : symList)
        std::cout << "\t" << element.opcode << " ";
    std::cout << std::endl;
    std::cout << "arity : ";
    for (const Token0& element : symList)
        std::cout << "\t"  << element.arity << " ";
    std::cout << std::endl;
    std::cout << "preced: ";
    for (const Token0& element : symList)
        std::cout << "\t"  << element.precedence << " ";
    std::cout << std::endl;
    std::cout << "value : ";
    for (const Token0& element : symList)
        std::cout << "\t"  << element.value << " ";
    std::cout << std::endl;
}

inline bool isNumeric(const std::string& s)
{
    if (s.length() == 0) return false;
    for (uint32_t i = 0; i < s.length(); ++i)
    {
        if ((s[i] >= '0' && s[i] <= '9')
            || s[i] == ' '
            || s[i] == '.'
            || (s[i] == '-' && i == 0))
            continue;
        return false;
    }
    return true;
}

#endif // UTILS_H
