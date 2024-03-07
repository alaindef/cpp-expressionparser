#ifndef PASS2_H
#define PASS2_H

string textOut= "";

void push(Token sym) {
    symListOut.push_back(sym);
    textOut += sym.content;
}

Token nextSymbol(string from, TokenTypeList expected){
    //  param from: the cpp function from where nextsymbol is called. used for error reporting
    // expected: the list of possible TokenTypes. it is filled in by the calling function
    string ppexpectedList = "";
    for (TokenType t: expected) ppexpectedList += " " + ppTokenType[t];
    if (symList.empty()) throw invalid_argument("from " + from + ": symbols missing!");
    Token next = symList.back(); symList.pop_back();
    if (expected.empty()) return next;
    if (count(expected.begin(), expected.end(), next.type) > 0) return next;
    throw invalid_argument(
        "from " + from + " at cursor=" + to_string(next.cursor) + " symbol=" + next.content + ", " + ppTokenType[next.type] +
        " is not one of {" + ppexpectedList + "}"                                                      // "expected" should be the list of expected types
        );
    return next;
}

void expr0();
void expr1();
void expr2();
void expr3();
void expr4();
void expr6();
void expr7();
void expr13();

void expr(){
    expr13();
}

void expr0(){
    if (isa(symIn, {LETT, DIGIT})){
        push(symIn);
        symIn = nextSymbol("expr0", {TIMES, DIV, LT,EQ,GT, PLUS, MINUS, PAR_L, PAR_R, COLON, QUEST, ETX});
    } else
        expr1();
}

void expr1(){
    if (isa(symIn, {PAR_L})) {
        symIn = nextSymbol("expr1", {LETT, DIGIT, PAR_L, PLUS, MINUS});
        expr13();
        if (symIn.content != ")")
            throw invalid_argument("received " + symIn.content);
        symIn = nextSymbol("expr1", {});
    }
}
void expr2(){
    expr0();
        if (symIn.precedence == 2){
        Token save = symIn;
        symIn = nextSymbol("expr2", {LETT, DIGIT, PAR_L, PLUS, MINUS});
        expr0();
        push(save);
    }
}

void expr3(){
    expr2();
    if (symIn.precedence == 3){
        Token save = symIn;
        symIn = nextSymbol("expr3", {LETT, DIGIT, PAR_L, PLUS, MINUS});
        expr3();
        push(save);
    }
}

void expr4(){
    expr3();
    if (symIn.precedence == 4){
        Token save = symIn;
        symIn = nextSymbol("expr4", {LETT, DIGIT, PAR_L, PLUS, MINUS});
        expr4();
        push(save);
    }
}

void expr6(){
    expr4();
    if (symIn.precedence == 6){
        Token save = symIn;
        symIn = nextSymbol("expr6", {LETT, DIGIT, PAR_L, PLUS, MINUS});
        expr6();
        push(save);
    }
}

void expr7(){                                                                           //TODO !!!
    expr6();
}

void expr13(){
    expr7();
    if (symIn.precedence == 13){
        Token save = symIn;
        symIn = nextSymbol("expr13", {LETT, DIGIT, PAR_L, PLUS, MINUS});
        expr7();
//        push(save);                                                                   // no need, ":" is ternary, will take care
        save = symIn;
        symIn = nextSymbol("expr13", {LETT, DIGIT, PAR_L, PLUS, MINUS});
        expr7();
        push(save);                                                                                                                                      // for now, should be silenced
    }
}

void clear2() {
    symListOut.clear();
    cursor = 0;
    textOut = "";
}

TokenList parse2(){
    reverse(symList.begin(), symList.end());
    clear2();
    cursor = 0;
    try {
        symIn = nextSymbol("parse", {});
        expr();
    } catch (const exception& e) {
        cout << "\n\n!!! PARSE ERROR:" << e.what() << endl<< endl;;
    };
    return symListOut;
};


#endif // PASS2_H
