#ifndef DEFS_H
#define DEFS_H
#include <string>
#include <stdio.h>

using namespace std;
//  PASS 1 will scan the input test and generate a list of symbols
//    we will assign a type to each allowed character  .
//    e.g. character 'h' (ascii 104)  is a t_LETT, character '0' (ascii 48 )is a t_DIGIT. character (40) is t_PAR_L (left parenthesis)
//    the following are the possible character types:
enum TokenType
    {t_ETX,   t_LF, t_TAB,  t_BLANK,  t_HASHT,  t_PAR_L,  t_PAR_R,  t_DOT,   t_TIMES,  t_DIV, t_PLUS,   t_MINUS,  t_LT, t_EQ, t_GT, t_QUEST,  t_COLON,  t_LETT,   t_DIGIT,  t_CR, t_OTHER,  t_EXCLA,  t_TEST};

typedef vector<TokenType> TokenTypeList;

//PASS 2 will scan the output of PASS1 and generate a list of tokens
// precedence is according to   https://en.cppreference.com/w/cpp/language/operator_precedence#cite_note-2
//                          or  https://en.wikipedia.org/wiki/Order_of_operations
// although pass2 needs far less tokentypes than the types from pass1, we will reuse the definition of pass1 and work with that


// prettyPrint of TokenType:
string ppTokenType[32] ={"ETX", "LF", "TAB", "BLANK", "HASHT", "PAR_L", "PAR_R", "DOT", "TIMES", "DIV", "PLUS", "MINUS", "LT", "EQ", "GT", "QUEST", "COLON", "LETT", "DIGIT", "CR", "OTHER", "EXCLA",  "TEST"};

typedef struct {
    TokenType type;
    string content;
    int opcode;
    int arity;
    int precedence;
    uint cursor;
} Token;



typedef vector<Token> TokenList;

//      finally our main data structures:
//  1. the output of PASS1 as a vector of symbols. it is also the input for PASS2.
//      symbols of type Token, the element "content" can be TODO
TokenList symList;
//  2. the output of PASS2 as a vector of tokens
TokenList symListOut;

#endif // DEFS_H
