#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <iomanip>
#include <defs.h>

//int cursor = 0;
Token symIn = {OTHER, "", -1, -1, 0};             // used in both pass1 and pass2
bool errorsPresent = false;

bool isa(Token token, vector<TokenType> allowedTypes){
    //    check if the symbol sym is one of the symbols in the list op
    return(count(allowedTypes.begin(), allowedTypes.end(), token.type) > 0);
}

bool isaC(char Kar, vector<KarType> allowedTypes){
    //    int found = find(allowedTypes.begin(), allowedTypes.end(), int(Kar));
    int cnt = count(allowedTypes.begin(), allowedTypes.end(), kartyp[int(Kar)]);
    return(cnt > 0);
}

// some operator functions
float op_chs(float x){return -x;}
float op_mul(float x, float y){return (x*y);}
float op_div(float x, float y){return (x/y);}
float op_add(float x, float y){return (x+y);}
float op_sub(float x, float y){return (x-y);}
float op_lt(float x, float y){return x<y;}
float op_eq(float x, float y){return x==y;}
float op_gt(float x, float y){return x>y;}
float op_elv(float x, float y, float z) {if (x) return y; else return z;}

//float invoke(float x, float (*func) (float)) {return func(x);}
//float invoke(float x, float y, float (*func) (float, float)) {return func(x,y);}
//float invoke(float x, float y, float z, float (*func) (float, float,float)) {return func(x,y,z);}

vector<function<float(float)>> op1;
vector<function<float(float,float)>> op2;
vector<function<float(float,float,float)>> op3;

void initOperators(){
    op1.push_back(op_chs);
    op2.push_back(op_mul);
    op2.push_back(op_div);
    op2.push_back(op_add);
    op2.push_back(op_sub);
    op2.push_back(op_lt);
    op2.push_back(op_eq);
    op2.push_back(op_gt);
    op3.push_back(op_elv);
}


// some printing stuff
void printPass1(vector<Token> symList, int tab){
    for (Token element : symList)
        cout << setw(tab) << element.content << " ";
    cout << endl;
    for (Token element : symList)
        cout << setw(tab) << ppTokenType[element.type] << " ";
    cout << endl;
}


// some printing stuff
void printPass2(vector<Token> symList, int tab){
    cout << "type  : ";
    for (Token element : symList)
        cout << setw(tab) << ppTokenType[element.type] << " ";
    cout << endl;
    cout << "cont  : ";
    for (Token element : symList)
        cout << setw(tab) << element.content << " ";
    cout << endl;
    cout << "opcode: ";
    for (Token element : symList)
        cout << setw(tab) << element.opcode << " ";
    cout << endl;
    cout << "arity : ";
    for (Token element : symList)
        cout << setw(tab) << element.arity << " ";
    cout << endl;
}

#endif // UTILS_H
