#pragma once
#include <vector>
#include "defs.h"

/* BACKUS NAUR definition

letter          ::= a | b | c | ....
digit           ::= 1 | 2 | 3 | ...
var             ::= letter | {letter | digit}
num             ::= {digit} | {digit} . {digit}

// the following defines the precedence, according to https://en.wikipedia.org/wiki/Order_of_operations
op2				::= +				| -
op3				::=	*				| /
op4				::=	+				| -
op6				::=	<				| <=		| >			|>=
op7				::=	==				| !=
op13			::=	?				| :
op14			::=	=				|

example:
a = 1 * 2 + 3 < 4 == 5 ? 6 : 7
    <e3->7
    <--e4--->
    <----e6----->
    <-------e7------->
    <----------e13----------->
<-----------e14-------------->


//
expr0 			::= var				| num					| expr1		ex:abc, 13, a2, (...)
expr1			::= ( expr13 )
expr2			::= expr0			| op2 expr0							ex:+abc, -4, 5
expr3			::= expr2			| expr2 op3 expr3					ex:a*4, -2*5, 2*-5, -1*(...)
expr4			::= expr3			| expr3 op4 expr4					ex:a*4 + 3, a*4 + (...)
expr6			::= expr4			| expr4 op6 expr6					ex:a*4 + 3 < 4
expr7			::= expr6			| expr6 op7 expr7					ex:a*4 + 3 < 4 != 7
expr13			::= expr7			| expr7 ? expr7 : exp7
expr14			::= var op14 expr13

expr			::= expr14			| expr13
 */

//PASS 2 will scan the output of PASS1 and generate a list of tokens
// precedence is according to   https://en.cppreference.com/w/cpp/language/operator_precedence#cite_note-2
//                          or  https://en.wikipedia.org/wiki/Order_of_operations

// (for now!) although pass2 needs far less tokentypes than the types from pass1, we will reuse the definition of pass1 and work with that
class RPNizer
{
public:

    RPNizer(TokenList pTokens) : inputTokenList(pTokens){}
    RPNTokenList& toRPN();

private:
    TokenList inputTokenList;
    RPNTokenList tokensout;
    Token nextToken(const std::string& from, std::vector<TokenType> expected);

    void expr(Token& tk);
    void expr0(Token& tk);
    void expr1(Token& tk);
    void expr2(Token& tk);
    void expr3(Token& tk);
    void expr4(Token& tk);
    void expr6(Token& tk);
    void expr7(Token& tk);
    void expr13(Token& tk);
    void expr14(Token& tk);

    uint cursor = 0;
};
