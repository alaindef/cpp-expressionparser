#ifndef UTILS_H
#define UTILS_H

int cursor = 0;
Token symIn = {NONE, 0, "", 0};             // used in both pass1 and pass2
bool errorsPresent = false;

bool isa(Token token, vector<TokenType> allowedTypes){
    //    check if the symbol sym is one of the symbols in the list op
    return(count(allowedTypes.begin(), allowedTypes.end(), token.type) > 0);
};

bool isaC(char Kar, vector<KarType> allowedTypes){
    //    int found = find(allowedTypes.begin(), allowedTypes.end(), int(Kar));
    int cnt = count(allowedTypes.begin(), allowedTypes.end(), kartyp[int(Kar)]);
    return(cnt > 0);
};

// some operator functions
float add(float x, float y){return (x+y);}
float invoke    (float x, float y, float (*function) (float, float)){return function(x,y);}
// TODO to be completed for the interpreter


// some printing stuff
void printVector(vector<Token> symList){
    for (Token element : symList)
        cout << element.content << " ";
    cout << endl;
//    for (Token element : symList)
//        cout << element.type << " ";
//    cout << endl;
}

void reportln(vector<Token> list, int level, int padding){};
void reportln(string s, int level){};

#endif // UTILS_H
