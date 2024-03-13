#ifndef PASS2_H
#define PASS2_H


//PASS 2 will scan the output of PASS1 and generate a list of tokens
// precedence is according to   https://en.cppreference.com/w/cpp/language/operator_precedence#cite_note-2
//                          or  https://en.wikipedia.org/wiki/Order_of_operations

// although pass2 needs far less tokentypes than the types from pass1, we will reuse the definition of pass1 and work with that


void push(Token sym) {
    symListOut.push_back(sym);
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

void expr0(){
    if (isa(symIn, {t_LETT, t_DIGIT})){
        push(symIn);
        symIn = nextSymbol("expr0", {t_TIMES, t_DIV, t_LT,t_EQ,t_GT, t_PLUS, t_MINUS, t_PAR_L, t_PAR_R, t_COLON, t_QUEST, t_ETX});
    } else
        expr1();
}

void expr1(){
    if (isa(symIn, {t_PAR_L})) {
        symIn = nextSymbol("expr1", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
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
        symIn = nextSymbol("expr2", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
        expr0();
        push(save);
    }
}

void expr3(){
    expr2();
    if (symIn.precedence == 3){
        Token save = symIn;
        symIn = nextSymbol("expr3", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
        expr3();
        push(save);
    }
}

void expr4(){
    expr3();
    if (symIn.precedence == 4){
        Token save = symIn;
        symIn = nextSymbol("expr4", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
        expr4();
        push(save);
    }
}

void expr6(){
    expr4();
    if (symIn.precedence == 6){
        Token save = symIn;
        symIn = nextSymbol("expr6", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
        expr6();
        push(save);
    }
}

void expr7(){                                                                           //TODO !!!
    expr6();
    if (symIn.precedence == 7){
        Token save = symIn;
        symIn = nextSymbol("expr7", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS,t_EQ});
        expr7();
        push(save);
    }
}

void expr13(){
    expr7();
    if (symIn.precedence == 13){
        Token save = symIn;
        symIn = nextSymbol("expr13", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
        expr7();                                                                // no need to push "?", ":" is ternary, will take care
        save = symIn;
        symIn = nextSymbol("expr13", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
        expr7();
        push(save);
    }
}

void expr14(){
    Token save = symList.back();
    if (isa(symIn, {t_LETT}) &(save.precedence == 14)){
        push(symIn);
        symIn = nextSymbol("expr14", {t_EQ});
        symIn = nextSymbol("expr14", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
        expr13();
        push(save);
    } else
        expr13();
}

void expr(){
    expr14();
}

TokenList parse2(){
    reverse(symList.begin(), symList.end());
    symListOut.clear();
    // cursor = 0;
    try {
        symIn = nextSymbol("parse", {});
        expr();
    } catch (const exception& e) {
        cout << "\n\n!!! PARSE ERROR:" << e.what() << endl<< endl;;
    };
    return symListOut;
};


#endif // PASS2_H
