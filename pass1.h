#ifndef PASS1_H
#define PASS1_H
#include <defs.h>


bool isFirstSymbol=true;
char c= '\u0000';                   //???


Token makeSymbol(vector<TokenType> expected){
    string s = "";
    if (cursor >= textIn.length()) return symIn;
    c = textIn[cursor];
    if (isaC(c, {BLANK, TAB})) {
        cursor++;
        return makeSymbol({});                                                          //makesymbol advances the cursor
        }

    symIn.type = kartyp[int(c)];
    symIn.content = KarPP[int(c)];                                                      // pretty print
    symIn.opcode  = -1;
    symIn.arity   = -1;
    symIn.cursor  = cursor;                                                             // not used for now
    KarType karTypeIn = kartyp[int(c)];
    switch (karTypeIn) {
        case LETT: case DIGIT: case DOT:                                                //c is a KAR, so we're building a string
            s = "";
            while (isaC(c, {LETT, DIGIT, DOT})) {
                s += c;
                cursor++;
                c = textIn[cursor];
            };
//            if (karTypeIn == DIGIT ) symIn.type = NUM; else symIn.type = LIT;           // todo add check on eg 12a4 (=error)
            symIn.content = s; symIn.arity = 0;
            cursor--;                                                                   // reposition before next char.
            break;
        case TIMES:
            symIn.opcode = 0; symIn.arity = 2;                                          //oMUL
            break;
        case DIV:
            symIn.opcode = 1; symIn.arity = 2;                                          //oDIV
            break;
        case PLUS:
            if (isFirstSymbol) {symIn.opcode = 0; symIn.arity = 1;}                      //oCHS
            else if (isaC(textIn[cursor - 1], {TIMES, DIV, PLUS, MINUS, PAR_L, QUEST})) {
                // this is a unary operator.
                symIn.opcode = 0; symIn.arity = 1;                                      //////////////// arity?
            } else { symIn.opcode = 2; symIn.arity = 2;}
            break;
        case MINUS:
            if (isFirstSymbol) {symIn.opcode = 1; symIn.arity = 1; } //oCHS;}
            else if (isaC(textIn[cursor - 1], {TIMES, DIV, PLUS, MINUS, PAR_L, QUEST})) {
                // this is a unary operator. We change the type to CHS
                symIn.opcode = 0;  symIn.arity = 1;                                     //oCHS;
            } else {symIn.opcode = 3; symIn.arity = 2;} //oMIN;}
            break;
        case LT:
            symIn.opcode = 4; symIn.arity = 2;                                          //oLT;
            break;
        case EQ:
            symIn.opcode = 5; symIn.arity = 2;                                          //oEQ;
            break;
        case GT:
            symIn.opcode = 6; symIn.arity = 2;                                          //oGT;
            break;
        case QUEST:
            symIn.opcode = 0;                                                           //oQUE;
            break;
        case COLON:
            symIn.opcode = 0; symIn.arity = 3;                                        //oCOL
            break;
        default:
            break;
    }
    isFirstSymbol = false;
    cursor++;
    if (expected.empty()) return symIn;            //default, we do not complain
    if (count(expected.begin(), expected.end(), symIn.type) > 0) return symIn;         //check on expected char is ok, no complaints
    errorsPresent = true;
//        throw IllegalArgumentException(
//            "SEPARATOR in line at cursor " +
//            "$cursor < ${textIn.substring(0, cursor)} > \n" +
//            "     char=$c, symbol=${symIn.content}   ==> < ${expected.contentToString()} >\n"
//            );
    return symIn;
}

void clear1() {
    cursor = 0;
    errorsPresent = false;
    symList.clear();
}

vector<Token> parse1(){
    clear1();
    cursor = 0;
    errorsPresent = false;
        do {
        symIn = makeSymbol({});

// in case of a "? XXX : YYY" construct we insert parentheses around the XXX part. this isolates the expression XXX
        if (isa(symIn, {COLON})) {                                       // substitute '?(' for '?'
            symList.push_back({PAR_L, ")", -1, -1, cursor});
            };
        symList.push_back(symIn);
//            symList.push_back({symIn.type, symIn.content, oNONE, -1, cursor});
            if (isa(symIn, {QUEST})) {                                       // substitute '?(' for '?'
                symList.push_back({PAR_L, "(", -1, -1, cursor});        //
            };
        } while (symIn.type != EXCLA);
    return symList;
}


#endif // PASS1_H
