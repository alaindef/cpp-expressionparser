#pragma once

#include <iostream>
#include "calculator.h"
#include "defs.h"

#include "utils.h"

float vars[10];

Calculator::Calculator() {
    funList0.push_back(Calculator::fun_num);
    funList0.push_back(Calculator::fun_var);

    funList1.push_back(Calculator::fun_pas);
    funList1.push_back(Calculator::fun_chs);

    funList2.push_back(Calculator::fun_mul);
    funList2.push_back(Calculator::fun_div);
    funList2.push_back(Calculator::fun_add);
    funList2.push_back(Calculator::fun_sub);
    funList2.push_back(Calculator::fun_lt);
    funList2.push_back(Calculator::fun_gt);
    funList2.push_back(Calculator::fun_eq);
    funList2.push_back(Calculator::fun_ass);

    funList3.push_back(fun_elv);
};

std::vector<std::string> report={""};

const std::string pp_arity[4] = {"LITTERAL", "UNARY expr", "BINARY expr", "TERNARY expr"};
std::string level = "";
const std::string level_inc = "   ";

float Calculator::fun_ass(float x, float y){        // provisional
    float ass_result = y;
    // Calculator::vars[0] = y;
    return ass_result;}                             // opcode 7 arity 2 precedence 14

float Calculator::calc(RPNTokenList& tokenlist){

    if (tokenlist.size() == 0) return 0.f;
    float v1;
    float v2;
    float v3;

    float res;

    level += level_inc;                                                             // increase indentation

    RPNToken last = tokenlist.back();
    tokenlist.pop_back();
    switch (last.arity){
    case 0:
        res = funList0[last.opcode](last.content);
        break;
        if (isNumeric(last.content)){                               // should be in RPNToken
            // std::cout << "numeric\n";
            res =stof(last.content);
        } else{
            // std::cout << "not numeric\n";
            if (last.content == "a") res = 0; else res = 1;
        }
        break;
    case 1:
        v1 =calc(tokenlist);
        res = funList1[last.opcode](v1);
        break;
    case 2:
        v1 =calc(tokenlist);
        v2 =calc(tokenlist);
        res = funList2[last.opcode](v2,v1);
        break;
    case 3:
        v1 =calc(tokenlist);
        v2 =calc(tokenlist);
        v3 =calc(tokenlist);
        res = Calculator::funList3[last.opcode](v1,v2,v3);
        if (v3 > 0.5) res = v2; else res = v1;
        break;
    }
    report.push_back(level + pp_arity[last.arity] + " op " + last.content + " \n"); // report AST
    level = level.substr(level_inc.size(), level.size());                           // decrease indentation
    return res;
}

float Calculator::calcandprint(RPNTokenList &tokenlist) {
    report={""};
    // std::cout << "\nkind: very kind\n body:\n";
    float result = calc(tokenlist);
    // reverse(report.begin(),report.end());
    // for (std::string el:report) std::cout << el;
    std::cout << "\nEVALUATION RESULT ==> " << ((result > 7.999 && result < 8.001) ? std::string("NEUF!") : std::to_string(result)) << std::endl <<
        "_______________________________________________________________________________" << std::endl;
}


