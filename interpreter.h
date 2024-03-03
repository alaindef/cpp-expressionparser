#ifndef INTERPRETER_H
#define INTERPRETER_H

float calc(vector<Token>& s){
    float v1;
    float v2;
    float v3;
    Token last = s.back(); s.pop_back();
    if (last.content == "?") {last = s.back(); s.pop_back();};
    if (last.type == DIGIT) return stof(last.content);                                  // todo also LIT VARI?
    switch (last.arity){
        case 1: v1 =calc(s); return -v1;
        case 2: v1 =calc(s); v2 =calc(s); return op2[last.opcode](v2,v1);
        case 3:
            v1 =calc(s); v2 =calc(s); v3 =calc(s);
            op3[last.opcode](v1,v2,v3);
            if (v3 > 0.5) return v2; else return v1;
    }
        return -99999;
}


 void calcandprint(vector<Token> s) {
    cout << "RESULT ==> " << float(calc(s)) << endl;
}

#endif // INTERPRETER_H
