#ifndef PASS1_H
#define PASS1_H
#include <defs.h>

//  PASS 1 will scan the input test and generate a list of symbols

TokenType kartyp[256];    // type of each character

uint cursor = 0;
string KarPP[256];      // string representation of each character

void initDinges(){
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


bool isaC(char Kar, TokenTypeList allowedTypes){
    int cnt = count(allowedTypes.begin(), allowedTypes.end(), kartyp[int(Kar)]);
    return(cnt > 0);
}

Token makeSymbol(string textIn, TokenTypeList expected){
    string s = "";
    char c;
    if (cursor >= textIn.length()) return Token{t_ETX,"",-1,-1,-1};
    c = textIn[cursor];
    if (isaC(c, {t_BLANK, t_TAB})) {
        cursor++;
        return makeSymbol(textIn, {});                                                          //makesymbol advances the cursor
    }

    symIn.type = kartyp[int(c)];
    symIn.content = KarPP[int(c)];                                                      // pretty print
    symIn.opcode  = -1;
    symIn.arity   = -1;
    symIn.precedence = -1;
    symIn.cursor  = cursor;                                                             // not used for now
    TokenType karTypeIn = kartyp[int(c)];
    switch (karTypeIn) {
    case t_LETT: case t_DIGIT: case t_DOT:                                                //c is a KAR, so we're building a string
        s = "";
        while (isaC(c, {t_LETT, t_DIGIT, t_DOT})) {
            s += c;
            cursor++;
            c = textIn[cursor];
        };
        //            if (karTypeIn == DIGIT ) symIn.type = NUM; else symIn.type = LIT;           // todo add check on eg 12a4 (=error)
        symIn.content = s; symIn.arity = 0; symIn.precedence = 0;
        cursor--;                                                                   // reposition before next char.
        break;
    case t_TIMES:
        symIn.opcode = 0; symIn.arity = 2;  symIn.precedence = 3;                   //oMUL
        break;
    case t_DIV:
        symIn.opcode = 1; symIn.arity = 2;  symIn.precedence = 3;                    //oDIV
        break;
    case t_PLUS:
        if (cursor == 0) {symIn.opcode = 0; symIn.arity = 1; symIn.precedence = 2;}//oCHS
        else if (isaC(textIn[cursor - 1], {t_TIMES,t_DIV,t_PLUS,t_MINUS,t_LT,t_EQ,t_GT,t_PAR_L,t_QUEST,t_COLON})) {
            // this is a unary operator.
            symIn.opcode = 0; symIn.arity = 1; symIn.precedence = 2;
        } else { symIn.opcode = 2; symIn.arity = 2; symIn.precedence = 4;}
        break;
    case t_MINUS:
        if (cursor == 0) {symIn.opcode = 1; symIn.arity = 1;  symIn.precedence = 2;} //oCHS;}
        else if (isaC(textIn[cursor - 1], {t_TIMES,t_DIV,t_PLUS,t_MINUS,t_LT,t_EQ,t_GT,t_PAR_L,t_QUEST,t_COLON})) {
            // this is a unary operator. We change the arity and precedence
            symIn.opcode = 1;  symIn.arity = 1;  symIn.precedence = 2;                                     //oCHS;
        } else {symIn.opcode = 3; symIn.arity = 2; symIn.precedence = 4;}           //oMIN;}
        break;
    case t_LT:
        symIn.opcode = 4; symIn.arity = 2; symIn.precedence = 6;                    //oLT;
        break;
    case t_EQ:
        //c is "=", so we check on second "="
        if (kartyp[int(textIn[cursor+1])] == t_EQ){
            symIn.opcode = 5; symIn.arity = 2; symIn.precedence = 7;                // "=="
            symIn.content = "==";
            cursor++;
        }else {
        symIn.opcode = 7; symIn.arity = 2; symIn.precedence = 14;                    // "="
        }
        break;
    case t_GT:
        symIn.opcode = 6; symIn.arity = 2; symIn.precedence = 6;                    //oGT;
        break;
    case t_QUEST:
        symIn.opcode = 0; symIn.arity = 0; symIn.precedence = 13;                                                           //oQUE;
        break;
    case t_COLON:
        symIn.opcode = 0; symIn.arity = 3; symIn.precedence = 13;                                        //oCOL
        break;
    default:
        break;
    }
    cursor++;
    if (expected.empty()) return symIn;            //default, we do not complain
    if (count(expected.begin(), expected.end(), symIn.type) > 0) return symIn;        //check on expected char is ok, no complaints
    errorsPresent = true;
    string errors = "SEPARATOR in line at cursor " + to_string(cursor) ;
    throw invalid_argument(errors
                           //            "SEPARATOR in line at cursor " &
                           //            "$cursor < ${textIn.substring(0, cursor)} > \n" +
                           //            "     char=$c, symbol=${symIn.content}   ==> < ${expected.contentToString()} >\n"
                           // adf cpp problem
                           );
    return symIn;
}

void clear() {
    cursor = 0;
    errorsPresent = false;
    symList.clear();
}

TokenList parse1(string textIn){
    clear();
    cursor = 0;
    errorsPresent = false;
    do {
        symIn = makeSymbol(textIn, {});
        symList.push_back(symIn);
    } while (symIn.type != t_ETX);
    return symList;
}

#endif // PASS1_H
