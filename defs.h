#ifndef DEFS_H
#define DEFS_H
#include <string>
#include <stdio.h>

using namespace std;
//  PASS 1 will scan the input test and generate a list of symbols (see PASS1)
//    we will assign a type to each allowed character  .
//    e.g. character 'h' (ascii 104)  is a LETT, character '0' (ascii 48 )is a DIGIT. character (40) is PAR_L (left parenthesis)
//    the following are the possible character types:
enum TokenType
    {ETX,   LF, TAB,    BLANK,  HASHT,  PAR_L,  PAR_R,  DOT,   TIMES,  DIV, PLUS,   MINUS,  LT, EQ, GT, QUEST,  COLON,  LETT,   DIGIT,  CR, OTHER,  EXCLA,  TEST};

typedef vector<TokenType> TokenTypeList;

//PASS 2 will scan the output of PASS1 and generate a list of tokens
// precedence is according to   https://en.cppreference.com/w/cpp/language/operator_precedence#cite_note-2
//                          or  https://en.wikipedia.org/wiki/Order_of_operations

// prettyPrint of TokenType:
string ppTokenType[32] ={"ETX", "LF", "TAB", "BLANK", "HASHT", "PAR_L", "PAR_R", "DOT", "TIMES", "DIV", "PLUS", "MINUS", "LT", "EQ", "GT", "QUEST", "COLON", "LETT", "DIGIT", "CR", "OTHER", "EXCLA",  "TEST"};

uint cursor = 0;
typedef struct {
    TokenType type;
    string content;
    int opcode;
    int arity;
    int precedence;
    uint cursor;
} Token;
typedef vector<Token> TokenList;

TokenType kartyp[256];    // type of each character

string KarPP[256];      // string representation of each character

void initDinges(){
    for (int j= 1; j<256; j++) {kartyp[j] = OTHER; KarPP[j] = "OTHER";};
    for (int j= 48; j<58; j++) {kartyp[j] = DIGIT; KarPP[j] = "D";};
    for (int j= 65; j<91; j++) {kartyp[j] = LETT ; KarPP[j] = "L";};
    for (int j= 97; j<123; j++) {kartyp[j] = LETT; KarPP[j] = "L";};

    kartyp[95] = LETT; KarPP[95] = "L";
    kartyp[0]  = ETX; KarPP[0] = "ETX";
    kartyp[10] = LF; KarPP[10] = "LF";
    kartyp[11] = TAB; KarPP[11] = "TAB";
    kartyp[13] = CR; KarPP[13] = "CR";
    kartyp[32] = BLANK; KarPP[32] = "BLANK";
    kartyp[33] = EXCLA; KarPP[33] = "!END!";
    kartyp[35] = HASHT; KarPP[35] = "HASHT";
    kartyp[40] = PAR_L; KarPP[40] = "(";
    kartyp[41] = PAR_R; KarPP[41] = ")";
    kartyp[42] = TIMES; KarPP[42] = "*";
    kartyp[43] = PLUS; KarPP[43] = "+";
    kartyp[45] = MINUS; KarPP[45] = "-";
    kartyp[46] = DOT; KarPP[46] = ".";
    kartyp[47] = DIV; KarPP[47] = "/";
    kartyp[58] = COLON; KarPP[58] = ":";
    kartyp[60] = LT; KarPP[60] = "<";
    kartyp[61] = EQ; KarPP[61] = "=";
    kartyp[62] = GT; KarPP[62] = ">";
    kartyp[63] = QUEST; KarPP[63] = "?";
}

//      finally our main data structures:
//  2. the output of PASS1 as a vector of symbols. it is also the input for PASS2.
//      symbols of type Token, the element "content" can be TODO
TokenList symList;
//  3. the output of PASS2 as a vector of tokens
TokenList symListOut;

#endif // DEFS_H
