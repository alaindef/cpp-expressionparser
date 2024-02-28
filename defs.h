#ifndef DEFS_H
#define DEFS_H
#include <string>

using namespace std;
//  PASS 1 will scan the input test and generate a list of symbols (see PASS1)
//    we will assign a type to each allowed character  .
//    e.g. character 'h' (ascii 104)  is a LETT, character '0' (ascii 48 )is a DIGIT. character (40) is PAR_L (left parenthesis)
//    the following are the possible character types:
enum KarType {ETX,
               LF,
               TAB,
               BLANK,
               HASHT,
               PAR_L,
               PAR_R,
               DOT,
               TIMES,
               DIV,
               PLUS,
               MINUS,
               EQ,
               GT,
               LT,
               COLON,
               QUEST,   // we ignore this operator, becase ':' takes care of ternary, else QUESTION("[?]"),
               LETT,
               DIGIT,
               CR,
               OTHER,
               EXCLA,
               TEST};

//PASS 2 will scan the output of PASS1 and generate a list of symbols
enum TokenType {
    // https://en.cppreference.com/w/cpp/language/operator_precedence#cite_note-2
    // of https://en.wikipedia.org/wiki/Order_of_operations
    COMMENT,
    VARI,
    LIT,                //literal
    CHS,                // CHS "change sign " was OP_3
    TimesDiv,           // * or /, according to precedence order - was OP5
    PlusMin,            // + or -               -  was OP6
    OP_16,              // like elvis
    ELV_Q,
    ELV_C,
    BEXPS,
    BEXPE,
    EOT,
    NONE}  ;

typedef struct {
    TokenType type;
    int arity;
    string content;
    int cursor;
} Token;

KarType kartyp[256];    // type of each character
string KarPP[256];      // string representation of each character

//KarPP[1] = 2;

void initDinges(){
    for (int8_t j= 1; j<256; j++) {kartyp[j] = OTHER; KarPP[j] = "OTHER";};
    for (int8_t j= 48; j<58; j++) {kartyp[j] = DIGIT; KarPP[j] = "D";};
    for (int8_t j= 65; j<91; j++) {kartyp[j] = LETT; KarPP[j] = "L";};
    for (int8_t j= 97; j<123; j++) {kartyp[j] = LETT; KarPP[j] = "L";};

    kartyp[95] = LETT; KarPP[95] = "L";
    kartyp[0]  = ETX; KarPP[0] = "ETX";
    kartyp[10] = LF; KarPP[10] = "LF";
    kartyp[11] = TAB; KarPP[11] = "TAB";
    kartyp[13] = CR; KarPP[13] = "CR";
    kartyp[32] = BLANK; KarPP[32] = "BLANK";
    kartyp[33] = EXCLA; KarPP[33] = "!END!";
    kartyp[35] = HASHT; KarPP[35] = "HASHT";
    kartyp[40] = PAR_L; KarPP[40] = "PAR_L";
    kartyp[41] = PAR_R; KarPP[41] = "PAR_R";
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


bool isa(Token token, vector<TokenType> allowedTypes){
//    check if the symbol sym is one of the symbols in the list op
    return(count(allowedTypes.begin(), allowedTypes.end(), token.type) > 0);
};

    bool isaC(char Kar, vector<KarType> allowedTypes){
    return(count(allowedTypes.begin(), allowedTypes.end(), int(Kar)) > 0);
    };

// some operator functions
float add(float x, float y){return (x+y);}
float invoke    (float x, float y, float (*function) (float, float)){return function(x,y);}




#endif // DEFS_H
