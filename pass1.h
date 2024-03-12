#ifndef PASS1_H
#define PASS1_H
#include <defs.h>

TokenType kartyp[256];    // type of each character

uint cursor = 0;
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


bool isaC(char Kar, TokenTypeList allowedTypes){
    int cnt = count(allowedTypes.begin(), allowedTypes.end(), kartyp[int(Kar)]);
    return(cnt > 0);
}

Token makeSymbol(string textIn, TokenTypeList expected){
    string s = "";
    char c;
    if (cursor >= textIn.length()) return Token{ETX,"",-1,-1,-1};
    c = textIn[cursor];
    if (isaC(c, {BLANK, TAB})) {
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
        case LETT: case DIGIT: case DOT:                                                //c is a KAR, so we're building a string
            s = "";
            while (isaC(c, {LETT, DIGIT, DOT})) {
                s += c;
                cursor++;
                c = textIn[cursor];
            };
//            if (karTypeIn == DIGIT ) symIn.type = NUM; else symIn.type = LIT;           // todo add check on eg 12a4 (=error)
            symIn.content = s; symIn.arity = 0; symIn.precedence = 0;
            cursor--;                                                                   // reposition before next char.
            break;
        case TIMES:
            symIn.opcode = 0; symIn.arity = 2;  symIn.precedence = 3;                   //oMUL
            break;
        case DIV:
            symIn.opcode = 1; symIn.arity = 2;  symIn.precedence = 3;                    //oDIV
            break;
        case PLUS:
            if (cursor == 0) {symIn.opcode = 0; symIn.arity = 1; symIn.precedence = 2;}//oCHS
            else if (isaC(textIn[cursor - 1], {TIMES,DIV,PLUS,MINUS,LT,EQ,GT,PAR_L,QUEST,COLON})) {
                // this is a unary operator.
                symIn.opcode = 0; symIn.arity = 1; symIn.precedence = 2;
            } else { symIn.opcode = 2; symIn.arity = 2; symIn.precedence = 4;}
            break;
        case MINUS:
            if (cursor == 0) {symIn.opcode = 1; symIn.arity = 1;  symIn.precedence = 2;} //oCHS;}
            else if (isaC(textIn[cursor - 1], {TIMES,DIV,PLUS,MINUS,LT,EQ,GT,PAR_L,QUEST,COLON})) {
                // this is a unary operator. We change the arity and precedence
                symIn.opcode = 1;  symIn.arity = 1;  symIn.precedence = 2;                                     //oCHS;
            } else {symIn.opcode = 3; symIn.arity = 2; symIn.precedence = 4;}           //oMIN;}
            break;
        case LT:
            symIn.opcode = 4; symIn.arity = 2; symIn.precedence = 6;                    //oLT;
            break;
        case EQ:
            symIn.opcode = 5; symIn.arity = 2; symIn.precedence = 6;                     //oEQ;
            break;
        case GT:
            symIn.opcode = 6; symIn.arity = 2; symIn.precedence = 6;                    //oGT;
            break;
        case QUEST:
            symIn.opcode = 0; symIn.arity = 0; symIn.precedence = 13;                                                           //oQUE;
            break;
        case COLON:
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
        } while (symIn.type != ETX);
    return symList;
}

#endif // PASS1_H
