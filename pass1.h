#ifndef PASS1_H
#define PASS1_H
#include <defs.h>

Token symIn = {NONE, 0, "",0};
bool isFirstSymbol=true;
int cursor = 0;
string textIn= "";

vector<Token> symList;
bool errorsPresent = false;
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
    int tup = kartyp[int(c)];
               symIn.content = KarPP[int(c)];                       // pretty print
    switch (tup) {
               case LETT: case DIGIT: case DOT:                        //c is a KAR, so we're building a string
                s = "";
                while (isaC(c, {LETT, DIGIT, DOT})) {
                    s += c;
                    cursor++;
                    c = textIn[cursor];
                };
                symIn.type = VARI;
                symIn.content = s;
                cursor--;
                break;
               case EXCLA: case ETX: case LF: case CR: case OTHER:
                symIn.type = EOT;
                return symIn;
                break;
               case PAR_L:
                                    symIn.type = BEXPS;                      //the special character becomes the typ
                break;
               case PAR_R:
                                    symIn.type = BEXPE;                        //the special character becomes the typ
                break;
               case TIMES: case DIV: case GT: case LT: case EQ:
                if (! (isFirstSymbol)) {                      //we have a separator
                    symIn.type = TimesDiv;                  //the special character becomes the typ
                }
                break;
            case QUEST:
                symIn.type = ELV_Q;                  //the special character becomes the typ
                break;
            case COLON:
                symIn.type = ELV_C;                  //the special character becomes the typ
                break;
            case PLUS: case MINUS:
                if (isFirstSymbol) {
                    symIn.type = CHS;
                } else if (isaC(textIn[cursor - 1], {TIMES, DIV, PLUS, MINUS, PAR_L, QUEST})) {
                    // we are not adding to the previous, this is a unary operator
                    symIn.type = CHS;
                } else symIn.type = PlusMin;
                break;
            case TEST:                            //c is a KAR, so we're building a string
//                var s = "";
//                s += c;
//                cursor++
//                    c = textIn[cursor]
//                    while (isaC(c, LETT, DIGIT)) {
//                    s += c;
//                    cursor++
//                        c = textIn[cursor]
//                }
//                symIn.typ = VARI;
//                symIn.content = s
                break;
            default:
                symIn.type = NONE;                      //the special character becomes the typ
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

void clear() {
            cursor = 0;
            errorsPresent = false;
            textIn = "";
            symList.clear();
}

vector<Token> parse(string s){
            clear();
            textIn = s;
            cursor = 0;
            errorsPresent = false;
            reportln("textIn =  $textIn", 0);
                do {
                symIn = makeSymbol({});
                if (isa(symIn, {ELV_C})) {                                       // substitute '?(' for '?'
                    symList.push_back({BEXPE, 17, "PAR_R", cursor});     //todo pretty print
                    };
                symList.push_back({symIn.type, 17, symIn.content, cursor});
                    if (isa(symIn, {ELV_Q})) {                                       // substitute '?(' for '?'
                    symList.push_back({BEXPS, 17, "PAR_L", cursor});        //todo
                    };
                } while (symIn.type != EOT);

                reportln(symList, 1, 7);
                cout << "\n";
                return symList;
}


#endif // PASS1_H
