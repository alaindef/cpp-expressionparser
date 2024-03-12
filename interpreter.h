#ifndef INTERPRETER_H
#define INTERPRETER_H

float calc(TokenList& s){
    if (s.size() == 0) return 0.f;
    float v1;
    float v2;
    float v3;
    Token last = s.back();
    s.pop_back();
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


 void calcandprint(TokenList s) {
    float result = calc(s);
    cout << "\nEVALUATION RESULT ==> " << ((result > 7.999 && result < 8.001) ? std::string("NEUF!") : std::to_string(result)) << endl <<
        "_______________________________________________________________________________" << endl;
}

#endif // INTERPRETER_H
