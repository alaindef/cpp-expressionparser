#ifndef PASS2_H
#define PASS2_H


string textOut= "";

void push(Token sym) {
    symListOut.push_back(sym);
    textOut += sym.content;
}

Token nextSymbol(string from, vector<TokenType> expected){
    if (symList.empty()) throw invalid_argument("from" + from + ": symbols missing!");
    Token next = symList.back(); symList.pop_back();
    if (expected.empty()) return next;
    if (count(expected.begin(), expected.end(), next.type) > 0) return next;
    errorsPresent = true;
    throw invalid_argument(
        "from " + from + " at cursor=" + to_string(next.cursor) + " symbol=" + next.content + ", " + ppTokenType[next.type] +
        "} NOT IN " + "expected" + "}"                                                      // "expected" should be the list of expected types
        );
    return next;
}
void bExpression();

void factor() {
    //next symbol if success
    switch(symIn.type) {
    case LETT: case DIGIT:
        push(symIn);                                                                        // push???
        symIn = nextSymbol("factor", {TIMES, DIV, LT,EQ,GT, PLUS, MINUS, PAR_L, PAR_R, QUEST, EXCLA});
        break;
    default: bExpression();
        break;
    }
}


void term() {
    if (isa(symIn, {PLUS,MINUS})  & (symIn.arity == 1)) {
        Token save = symIn;
        symIn = nextSymbol("term", {LETT, DIGIT});
        factor();
//        char ch = 177;  I cannot yet displan char 177
        if (save.content == "-"){
            save.opcode = 0;
            save.arity  = 1;
            push(save);
        }

//        push(Token({CHS, "CHS+-" , 0, 1, symIn.cursor}));        // push???

    }
    factor();
    while (isa(symIn, {TIMES, DIV, LT,EQ,GT})) {
        Token save = symIn;
        symIn = nextSymbol("term", {LETT, DIGIT, PAR_L});
        factor();
        push(save);                                                                         // push ???
    }
}

void expression(){
    term();
    while (isa(symIn, {TIMES, DIV, LT,EQ,GT, PLUS, MINUS, QUEST, COLON})) {
        Token save = symIn;
        symIn = nextSymbol("expression", {LETT, DIGIT, PAR_L});
        term();
        if (save.content != "?") push(save);             //do not generate token for "?"
    }
};


void bExpression() {
    if (isa(symIn, {PAR_L})) {
        symIn = nextSymbol("bExpression", {LETT, DIGIT, PAR_L, PLUS, MINUS});
        expression();
        symIn = nextSymbol("bExpression", {LETT, DIGIT, TIMES, DIV, LT, EQ, GT, PLUS, MINUS, PAR_L, PAR_R, QUEST, COLON, EXCLA});
    }
};


void clear2() {
    symListOut.clear();
    cursor = 0;
    errorsPresent = false;
    textOut = "";
}

vector<Token> parse2(){
    reverse(symList.begin(), symList.end());
    clear2();
    cursor = 0;
    errorsPresent = false;
    try {
        symIn = nextSymbol("parse", {});
        expression();
    } catch (const exception& e) {
        cout << "PARSE ERROR:" << e.what() << endl;
    };
    if (!errorsPresent)
//        cout << "expression parser PASS2 ended succesfully\n ";
    cout << endl;
    return symListOut;
};


#endif // PASS2_H
