#pragma once
#include "tokengenerator.h"

#include <vector>
#include <algorithm>
#include <iostream>

/* BACKUS NAUR definition

letter          ::= a | b | c | ....
digit           ::= 1 | 2 | 3 | ...
var             ::= letter | {letter | digit}
num             ::= {digit} | {digit} . {digit}

// the following defines the precedence, according to https://en.wikipedia.org/wiki/Order_of_operations
op2-plus1		::= +				| -
op3-mul			::=	*				| /
op4-plus2		::=	+				| -
op6-less		::=	<				| <=		| >			|>=
op7-eq			::=	==				| !=
op13-tst		::=	?				| :
op14-assgn		::=	=				|

example:
a = 1 * 2 + 3 < 4 == 5 ? 6 : 7
    <e3->7
    <--e4--->
    <----e6----->
    <-------e7------->
    <----------e13----------->
<-----------e14-------------->

//
expr0_val		::= var				| num					| expr1		ex:abc, 13, a2, (...)
expr1_par		::= ( expr13 )
expr2_plus1		::= expr0			| op2 expr0							ex:+abc, -4, 5
expr3_mul		::= expr2			| expr2 op3 expr3					ex:a*4, -2*5, 2*-5, -1*(...)
expr4_plus		::= expr3			| expr3 op4 expr4					ex:a*4 + 3, a*4 + (...)
expr6_less		::= expr4			| expr4 op6 expr6					ex:a*4 + 3 < 4
expr7_eq		::= expr6			| expr6 op7 expr7					ex:a*4 + 3 < 4 != 7
expr13_tst		::= expr7			| expr7 ? expr7 : exp7
expr14_assgn	::= var op14 expr13

expr			::= expr14			| expr13
 */

//PASS 2 will scan the output of PASS1 and generate a list of tokens
// precedence is according to   https://en.cppreference.com/w/cpp/language/operator_precedence#cite_note-2
//                          or  https://en.wikipedia.org/wiki/Order_of_operations


struct TkList{
    vector<Token> tokens;
    int cursor = 0;
    Token pop(){
        if (cursor >= tokens.size()) throw invalid_argument("symbols missing!");
        return tokens[cursor++];
    };
    Token get(int shift){
        int newCursor = cursor + shift;
        if ((newCursor < 0) || (newCursor > tokens.size())) throw invalid_argument("out of reach");
        return tokens[newCursor];
    }
    bool done(){
        return (cursor > tokens.size());
    }
};

    // RPNToken is used in the OUTPUT of RPNizer, en input for the Interpreter
    struct RPNToken{
        OC opcode;
        int arity;
        float value;
    } ;

    vector<RPNToken> makeRPN(vector<Token> tkListIn);


