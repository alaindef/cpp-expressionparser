#include "Tokenizer.h"
#include <iostream>
#include <algorithm>
#include "utils.h"

using namespace std;

Tokenizer::Tokenizer()
{
    for (int j= 1; j<256; j++) {kartyp[j] = t_OTHER; KarPP[j] = "OTHER";};
    for (int j= 48; j<58; j++) {kartyp[j] = t_DIGIT; KarPP[j] = "D";};
    for (int j= 65; j<91; j++) {kartyp[j] = t_LETT ; KarPP[j] = "L";};
    for (int j= 97; j<123; j++) {kartyp[j] = t_LETT; KarPP[j] = "L";};

    kartyp[95] = t_LETT; KarPP[95] = "L";
    kartyp[0]  = t_ETX; KarPP[0] = "ETX";
    kartyp[10] = t_LF; KarPP[10] = "LF";
    kartyp[11] = t_TAB; KarPP[11] = "TAB";
    kartyp[13] = t_CR; KarPP[13] = "CR";
    kartyp[32] = t_BLANK; KarPP[32] = "BLANK";
    kartyp[33] = t_EXCLA; KarPP[33] = "!END!";
    kartyp[35] = t_HASHT; KarPP[35] = "HASHT";
    kartyp[40] = t_PAR_L; KarPP[40] = "(";
    kartyp[41] = t_PAR_R; KarPP[41] = ")";
    kartyp[42] = t_TIMES; KarPP[42] = "*";
    kartyp[43] = t_PLUS; KarPP[43] = "+";
    kartyp[45] = t_MINUS; KarPP[45] = "-";
    kartyp[46] = t_DOT; KarPP[46] = ".";
    kartyp[47] = t_DIV; KarPP[47] = "/";
    kartyp[58] = t_COLON; KarPP[58] = ":";
    kartyp[60] = t_LT; KarPP[60] = "<";
    kartyp[61] = t_EQ; KarPP[61] = "=";
    kartyp[62] = t_GT; KarPP[62] = ">";
    kartyp[63] = t_QUEST; KarPP[63] = "?";
}

std::vector<Token> Tokenizer::tokenize(string textIn)
{
    std::vector<Token> tokens;
    uint32_t cursor = 0;
    errorsPresent = false;
    Token tk;
    do {
        tk = makeToken(textIn, cursor, {});
        if (errorsPresent){
            cout<<"ERROR at cursor " << cursor;// << " : "<<errors<<"\n\n";
            break;
        }
        tokens.push_back(tk);
    } while (tk.type != t_ETX);
    return tokens;
}


Token Tokenizer::makeToken(const string& textIn, uint32_t& cursor, std::vector<TokenType> expected){
    string s = "";
    while (cursor < textIn.length() && std::isspace(textIn[cursor])) cursor++;
    if (cursor >= textIn.length()) return Token{t_ETX,"",-1,-1,-1};

    // create Token
    Token tk;
    char c;
    c = textIn[cursor];
    tk.type = kartyp[(int)c];
    tk.content = KarPP[(int)c];                                                      // pretty print
    tk.opcode  = -1;
    tk.arity   = -1;
    tk.precedence = -1;
    tk.cursor  = cursor;

    switch (kartyp[(int)c]) {
    case t_LETT: case t_DIGIT: case t_DOT:                                          //c is a KAR, so we're building a string
        s = "";
        while (isaC(c, {t_LETT, t_DIGIT, t_DOT})) {
            s += c;
            cursor++;
            c = textIn[cursor];
        };
        if (isNumeric(s) ) {
            tk.opcode = 0;
            tk.content = s;
        }
        else {
            tk.opcode = 1;
            tk.content = s;
        }
        tk.arity = 0;
        tk.precedence = 0;
        cursor--;                                                                   // reposition before next char.
        break;
    case t_TIMES:
        tk.opcode = 0; tk.arity = 2;  tk.precedence = 3;
        break;
    case t_DIV:
        tk.opcode = 1; tk.arity = 2;  tk.precedence = 3;
        break;
    case t_PLUS:
        if (cursor == 0) {tk.opcode = 0; tk.arity = 1; tk.precedence = 2;}
        else if (isaC(textIn[cursor - 1], {t_TIMES,t_DIV,t_PLUS,t_MINUS,t_LT,t_EQ,t_GT,t_PAR_L,t_QUEST,t_COLON})) {
            // this is a unary operator.
            tk.opcode = 0; tk.arity = 1; tk.precedence = 2;
        } else { tk.opcode = 2; tk.arity = 2; tk.precedence = 4;}
        break;
    case t_MINUS:
        if (cursor == 0) {tk.opcode = 1; tk.arity = 1;  tk.precedence = 2;}
        else if (isaC(textIn[cursor - 1], {t_TIMES,t_DIV,t_PLUS,t_MINUS,t_LT,t_EQ,t_GT,t_PAR_L,t_QUEST,t_COLON})) {
            // this is a unary operator. We change the arity and precedence
            tk.opcode = 1;  tk.arity = 1;  tk.precedence = 2;
        } else {tk.opcode = 3; tk.arity = 2; tk.precedence = 4;}
        break;
    case t_LT:
        tk.opcode = 4; tk.arity = 2; tk.precedence = 6;
        break;
    case t_GT:
        tk.opcode = 5; tk.arity = 2; tk.precedence = 6;
        break;
    case t_EQ:
        //c is "=", so we check on second "="
        if (kartyp[int(textIn[cursor+1])] == t_EQ){
            tk.opcode = 6; tk.arity = 2; tk.precedence = 7;                // "=="
            tk.content = "==";
            cursor++;
        }else {
            tk.opcode = 7; tk.arity = 2; tk.precedence = 14;                   // "="
        }
        break;
    case t_QUEST:
        tk.opcode = 0; tk.arity = 0; tk.precedence = 13;                   // this will be skipped in pass2
        break;
    case t_COLON:
        tk.opcode = 0; tk.arity = 3; tk.precedence = 13;
        break;
    default:
        break;
    }
    cursor++;
    if (expected.empty()) return tk;            //default, we do not complain
    if (count(expected.begin(), expected.end(), tk.type) > 0) return tk;        //check on expected char is ok, no complaints
    errorsPresent = true;
    string errors = "SEPARATOR in line at cursor " + to_string(cursor) ;
    throw invalid_argument(errors
                           //            "SEPARATOR in line at cursor " &
                           //            "$cursor < ${textIn.substring(0, cursor)} > \n" +
                           //            "     char=$c, symbol=${tk.content}   ==> < ${expected.contentToString()} >\n"
                           // adf cpp problem
                           );
    return tk;
}
