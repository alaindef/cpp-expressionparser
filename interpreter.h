#ifndef INTERPRETER_H
#define INTERPRETER_H


float calc1(vector<Token>& s){
    int opsign;
    Token last;
    last = s.back(); s.pop_back();
    if (last.type == NUM) return stof(last.content);                                  // todo also LIT VARI?
    else
        opsign = last.opcode;
    float v1 = calc1(s);
    float v2 = calc1(s);
    switch(opsign) {
        case oMUL: return v2 * v1;
        case oDIV: return v2 / v1;
        case oSUM: return v2 + v1;
        case oMIN: return v2 - v1;
        case oLT:  if (v2 < v1)  return 1; else return 0;
        case oEQ:  if (v2 == v1) return 1; else return 0;
        case oGT:  if (v2 > v1)  return 1; else return 0;
                          //                "?" -> return v1
        case oCOL: {
            float v3 = calc1(s);
        if (v3 > 0) return v2; else return v1;
        }
    }
}

float calc(vector<Token>& s){
    int opcode;
    float v1;
    float v2;
    float v3;
    Token last = s.back(); s.pop_back();
    if (last.content == "?") {last = s.back(); s.pop_back();};
    if (last.type == NUM) return stof(last.content);                                  // todo also LIT VARI?
    switch (last.arity){
        case 1: v1 =calc(s); return -v1;
        case 2: v1 =calc(s); v2 =calc(s); return op2[last.opcode](v1,v2);
        case 3:
            v1 =calc(s); v2 =calc(s); v3 =calc(s);
//            op3[last.opcode](v1,v2,v3);
            if (v1 > 0.5) return v2; else return v3;
    }
}


 void calcandprint(vector<Token> s) {
    cout << "RESULT ==> " << float(calc(s)) << endl;
}




#endif // INTERPRETER_H
