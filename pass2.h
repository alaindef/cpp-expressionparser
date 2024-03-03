#ifndef PASS2_H
#define PASS2_H


string textOut= "";

void push(Token sym) {
    symListOut.push_back(sym);
    textOut += sym.content;
}

Token nextSymbol(string from, vector<TokenType> expected){
    if (symList.empty()) throw invalid_argument("from <$from>: symbols missing!");
    Token next = symList.back(); symList.pop_back();
    if (expected.empty()) return next;
    if (count(expected.begin(), expected.end(), next.type) > 0) return next;
    errorsPresent = true;
    throw invalid_argument(
                  "from <$from> at cursor=${next.cursor} symbol={${next.content}, ${next.typ}} NOT IN ${expected.contentToString()}"
        );
    return next;
}
void bExpression();

void factor() {
    //next symbol if success
    switch(symIn.type) {
    case VARI: case LIT: case NUM:
        push(symIn);                                                                        // push???
        symIn = nextSymbol("factor", {TimesDiv, COMPARE, PlusMin, BEXPE, ELV_Q, EOT});
        break;
    default: bExpression();
        break;
    }
}


void term() {
    if (isa(symIn, {CHS})) {
        Token save = symIn;
        symIn = nextSymbol("term", {VARI,LIT,NUM});
        factor();
        char ch = 177;
        if (save.content == "-") push(Token({CHS, "CHS" , oCHS, 1, symIn.cursor}));        // push???

    }
    factor();
    while (isa(symIn, {TimesDiv, COMPARE})) {
        Token save = symIn;
        symIn = nextSymbol("term", {VARI,LIT,NUM, BEXPS});
        factor();
        push(save);                                                                         // push ???
    }
}

void expression(){
    term();
    while (isa(symIn, {PlusMin, ELV_Q, ELV_C})) {
        Token save = symIn;
        symIn = nextSymbol("expression", {VARI,LIT,NUM, BEXPS});
        term();
        push(save);             //???
    }
};


void bExpression() {
    if (isa(symIn, {BEXPS})) {
        symIn = nextSymbol("bExpression", {VARI,LIT,NUM, BEXPS, CHS});
        expression();
        symIn = nextSymbol("bExpression", {VARI,LIT,NUM, TimesDiv, COMPARE, PlusMin, BEXPS, BEXPE, ELV_Q, ELV_C, EOT});
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
    } catch (invalid_argument) {
        cout << "PARSE ERROR: ${e.message}" << endl;
    };
    if (!errorsPresent)
        cout << "expression parser PASS2 ended succesfully\n ";
    cout << endl;
    return symListOut;
};



#endif // PASS2_H
