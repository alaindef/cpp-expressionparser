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
        return makeSymbol({});                              //makesymbol advances the cursor
               }
    int intc = int(c);

    symIn.content = KarPP[int(c)];                       // pretty print
    symIn.opcode  = -1;
    KarType karTypeIn = kartyp[int(c)];
    switch (karTypeIn) {
        case LETT: case DIGIT: case DOT:                        //c is a KAR, so we're building a string
            s = "";
            while (isaC(c, {LETT, DIGIT, DOT})) {
                s += c;
                cursor++;
                c = textIn[cursor];
            };
            if (karTypeIn == DIGIT ) symIn.type = NUM; else symIn.type = LIT;
            symIn.content = s;
            cursor--;
            break;
        case TIMES:
            symIn.type = TimesDiv; symIn.opcode = 0; symIn.arity = 2;  //oMUL;                       //we have a separator
            break;
        case DIV:
            symIn.type = TimesDiv; symIn.opcode = 1; symIn.arity = 2;  //oDIV;                      //we have a separator
            break;
        case PLUS:
            if (isFirstSymbol) {symIn.type = CHS; symIn.opcode = 0;} //oCHS;}
            else if (isaC(textIn[cursor - 1], {TIMES, DIV, PLUS, MINUS, PAR_L, QUEST})) {
                // we are not adding to the previous, this is a unary operator
                symIn.type = CHS; symIn.opcode = 0; //oCHS;
            } else {symIn.type = PlusMin; symIn.opcode = 2;} //oSUM;}
            break;
        case MINUS:
            if (isFirstSymbol) {symIn.type = CHS; symIn.opcode = 0; symIn.arity = 1; } //oCHS;}
            else if (isaC(textIn[cursor - 1], {TIMES, DIV, PLUS, MINUS, PAR_L, QUEST})) {
                // we are not adding to the previous, this is a unary operator
                symIn.type = CHS; symIn.opcode = 0;  symIn.arity = 1;  //oCHS;
            } else {symIn.type = PlusMin; symIn.opcode = 3;} //oMIN;}
            break;
        case LT:
            symIn.type = COMPARE; symIn.opcode = 4; symIn.arity = 2; //oLT;
            break;
        case EQ:
            symIn.type = COMPARE; symIn.opcode = 5; symIn.arity = 2;  //oEQ;
            break;
        case GT:
            symIn.type = COMPARE; symIn.opcode = 6; symIn.arity = 2;  //oGT;
            break;
        case QUEST:
            symIn.type = ELV_Q; symIn.opcode = 0;   //oQUE;
            break;
        case COLON:
            symIn.type = ELV_C; symIn.opcode = -1; symIn.arity = 13;
            break;
        default:
            symIn.type = tokenType[kartyp[int(c)]];
            symIn.opcode = -1;
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
        if (isa(symIn, {ELV_C})) {                                       // substitute '?(' for '?'
            symList.push_back({BEXPE, ")", oCOL, -1, cursor});
            };
        symList.push_back(symIn);
//            symList.push_back({symIn.type, symIn.content, oNONE, -1, cursor});
            if (isa(symIn, {ELV_Q})) {                                       // substitute '?(' for '?'
                symList.push_back({BEXPS, "(", oQUE, -1, cursor});        //
            };
        } while (symIn.type != EOT);
    return symList;
}


#endif // PASS1_H
