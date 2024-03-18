#include "pass0.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <algorithm>
#include <cstring>

using namespace std;

pass0::pass0() {
    //list of allowed symbols
    language.push_back("+"); keywords.push_back("[0.+]");
    language.push_back("-"); keywords.push_back("[1.-]");
    language.push_back("*"); keywords.push_back("[2.*]");
    language.push_back("/"); keywords.push_back("[3./]");
    // language.push_back("+"); keywords.push_back("[4.+]");
    // language.push_back("-"); keywords.push_back("[5.-]");
    language.push_back("<"); keywords.push_back("[6.<]");
    language.push_back("<="); keywords.push_back("[7.<=]");
    language.push_back(">"); keywords.push_back("[8.>]");
    language.push_back(">="); keywords.push_back("[9.>=]");
    language.push_back("=="); keywords.push_back("[10.==]");
    language.push_back("!="); keywords.push_back("[11.!=]");
    language.push_back("?"); keywords.push_back("[12.?]");
    language.push_back(":"); keywords.push_back("[13.:]");
    language.push_back("="); keywords.push_back("[14.=]");   // must come after "=="
    language.push_back("("); keywords.push_back("[15.(]");
    language.push_back(")"); keywords.push_back("[16.)]");
    langsize = language.size();
}


void pass0::tokenize(string textIn){
    string out = "";
    uint cursor = 0;
    cout << "\nin = " << textIn <<endl;

    int lsize = language.size();
    string next = "";
    string blank = " ";
    int keywordFoundAt = -1;
    while (cursor < textIn.size() ){
        // if (int(s[cursor1]) == 32) {
        if (string() + textIn[cursor] == " "){
            cursor++; continue;
        }
        uint increment = 1;
        for (int i=0; i<lsize; i++){
            string keyword = language[i];
            uint sz = keyword.size();
            if (keyword == textIn.substr(cursor, sz)){      //keyword found
                increment = keyword.size();
                keywordFoundAt = i;
                break;
            }
        }
        if (keywordFoundAt < 0){
            next += textIn[cursor];
            cursor += increment;
        }else{
            if (next.size() > 0) out  += " {" + next + "} ";
            next="";
            out  += keywords[keywordFoundAt];
            keywordFoundAt = -1;
            cursor += increment;
        }
    }
    if (next.size() > 0)
        out  += " {" + next +"} ";
    // match(textIn,  out);

    cout << "\nout= " << out <<endl;
}
