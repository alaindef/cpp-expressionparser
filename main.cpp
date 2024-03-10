#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <vector>
#include <ctime>
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>        // count function

#include "defs.h"          // global definitions
#include "utils.h"         // utilities

using namespace std;

#include "pass1.h"
#include "pass2.h"
#include "interpreter.h"

int main(int argc, char *argv[]){
    (void)(argc);
    (void)(argv);
    initDinges();
    initOperators();

    string text = "";

    vector<string> inputs = {"","type it yourself",
                             "1<-2",
                             "1 -2",
                             "(2+3)*(1<(-2)) + (6/2)",
                             "(2+3)*(1<-2) + (6/2)",
                             "1+-2",
                             "6*2*4/5",
                             "(6)",
                             "(6)",
                             "5*(-1 + (6-2)*2)",
                             "2*3+5<1?777:((1<2 + (6/2))+17/4)",
                             "2*-5+17*2-(45<2)",
                             "0?2:3",
                             "-1+(5<4 ?4*5:(17-5)*3)"
                            };

    uint choice = 0;
    string ch = "";

    while (true)
    {
        cout << "\nchoose:         -- choose 0 to exit\n";
             for (uint i = 1; i<inputs.size(); i++) cout << "\n" << i << ". " << inputs[i] ;
        cout << "\n\nchoice ==> ";
//    cin  >> choice;  //because cin stops at spaces, we use getline now. do not mix cin and getline!
        getline(cin, ch);

        choice = stoi(ch);
        if (choice > inputs.size())
        {
            cout << "wrong choice   " << choice << endl;
            continue;
        }
        if (choice == 0) return 0;
        if (choice == 1) getline(cin, text);
//    if (choice == 1) cin >> text;
        else text = inputs[choice];

        // cin.clear();
        // cin.ignore();
        cout << "\ntext in: " << text << endl;
        cout << "\nPASS 1 gives the tokenized input :\n";
        parse1(text);
        printPass(symList, 5);
//        cout << "\n\nPASS 2 gives the RPN form of the expression:\n";
//        parse2();
//        printPass(symListOut, 5);
//        calcandprint(symListOut);
    };

    return 0;

    //end TEST

    return 0;
}
