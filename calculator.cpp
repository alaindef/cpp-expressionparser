#include <iostream>
#include "calculator.h"

Calculator::Calculator() {}

float Calculator::calc(std::vector<RpnGenerator::RPNToken>& tokenlist){
    if (tokenlist.size() == 0) return 0.f;

    float res = 0;
    float v1 = 0;
    float v2 = 0;

    // RpnGenerator::RPNToken last = tokenlist.back();
    // tokenlist.pop_back();

    cursor--;
    if (cursor<0) cout << "\n\n !!! ERROR cursor !!!\n";
    RpnGenerator::RPNToken last = tokenlist[cursor];

    //remember that operands will be eaten in reverse order
    switch (last.opcode) {
    case OC::NUM:   res = last.value;                                   break;
    case OC::VAR:   res = vartab->getValue((int)last.value);            break;
    case OC::MUL:   res = calc(tokenlist) * calc(tokenlist);            break;
    case OC::DIV:   v1  = calc(tokenlist);  res = calc(tokenlist)/v1;   break;
    case OC::ADD:   res = calc(tokenlist) + calc(tokenlist);            break;
    case OC::SUB:   v1  = calc(tokenlist);  res = calc(tokenlist) - v1; break;
    case OC::PAS:   res = calc(tokenlist);                              break;
    case OC::CHS:   res = -calc(tokenlist);                             break;
    case OC::LT:    res = calc(tokenlist)   >  calc(tokenlist);         break;
    case OC::LE:    res = calc(tokenlist)   >= calc(tokenlist);         break;
    case OC::GT:    res = calc(tokenlist)   <  calc(tokenlist);         break;
    case OC::GE:    res = calc(tokenlist)   <= calc(tokenlist);         break;
    case OC::EQ:    res = calc(tokenlist)   == calc(tokenlist);         break;
    case OC::NE:    res = calc(tokenlist)   != calc(tokenlist);         break;
    case OC::ASS:   res = calc(tokenlist);
        vartab->setVar(tokenlist[cursor-1].value, res); cursor--;                       break;
    case OC::COL:   v1  = calc(tokenlist);  v2=calc(tokenlist);
        res = calc(tokenlist)?v2:v1;                                                    break;
    default:                                                                            break;
    }
    return res;
}

void Calculator::calcandprint(std::vector<RpnGenerator::RPNToken> &tokenlist, bool prt) {
    cursor = tokenlist.size();
    float result = calc(tokenlist);
    if (prt){
        std::cout << "EVALUATION RESULT ==> " << std::to_string(result) << std::endl;
        vartab->printVarTable();
        cout << "_______________________________________________________________________________" << std::endl;
    }
}


