#ifndef INTERPRETER_H
#define INTERPRETER_H



int ass_result = 0;

// some operator functions
float op_chs(float x){return -x;}
float op_mul(float x, float y){return (x*y);}
float op_div(float x, float y){return (x/y);}
float op_add(float x, float y){return (x+y);}
float op_sub(float x, float y){return (x-y);}
float op_lt(float x, float y){return x<y;
}
float op_eq(float x, float y){return x==y;}
float op_gt(float x, float y){return x>y;}
float op_ass(float x, float y){
    ass_result = y;
    cout << "assignment result. a = " << ass_result<< endl;
    return ass_result;}
float op_elv(float x, float y, float z) {if (x) return y; else return z;}


vector<function<float(float)>> op1;
vector<function<float(float,float)>> op2;
vector<function<float(float,float,float)>> op3;

void initOperators(){
    op1.push_back(op_chs);          // opcode 0 arity 1
    op2.push_back(op_mul);          // opcode 0 arity 2
    op2.push_back(op_div);          // opcode 1 arity 2
    op2.push_back(op_add);          // opcode 2 arity 2
    op2.push_back(op_sub);          // opcode 3 arity 2
    op2.push_back(op_lt);           // opcode 4 arity 2
    op2.push_back(op_eq);           // opcode 5 arity 2
    op2.push_back(op_gt);           // opcode 6 arity 2
    op2.push_back(op_ass);          // opcode 7 arity 2
    op3.push_back(op_elv);          // opcode 0 arity 3
}

float calc(TokenList& s){
  float v1;
    float v2;
    float v3;

    int res;

    Token last = s.back();
    s.pop_back();
    if (last.type == t_DIGIT) return stof(last.content);                                  // todo also LIT VARI?
    switch (last.arity){
        case 1: v1 =calc(s); return -v1;
        case 2:
            v1 =calc(s);
            v2 =calc(s);
            res = op2[last.opcode](v2,v1);
            return res;
        case 3:
            v1 =calc(s); v2 =calc(s); v3 =calc(s);
            op3[last.opcode](v1,v2,v3);
            if (v3 > 0.5) return v2; else return v1;
    }
        return -99999;
}


 void calcandprint(TokenList s) {
        cout << "\nEVALUATION RESULT ==> " << float(calc(s)) << endl <<
        "_______________________________________________________________________________" << endl;
}

#endif // INTERPRETER_H
