#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <iomanip>
#include <defs.h>

Token symIn = {t_OTHER, "", -1, -1, 0, 0};             // used in both pass1 and pass2
bool errorsPresent = false;

bool isa(Token token, TokenTypeList allowedTypes){
    //    check if the symbol sym is one of the symbols in the list op
    return(count(allowedTypes.begin(), allowedTypes.end(), token.type) > 0);
}

// some printing stuff
void printPass(TokenList symList, int tab){
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
    cout << "prcd  : ";
    for (Token element : symList)
        cout << setw(tab) << element.precedence << " ";
    cout << endl;
    cout << "cursr : ";
    for (Token element : symList)
        cout << setw(tab) << element.cursor<< " ";
    cout << endl;
}

#endif // UTILS_H
