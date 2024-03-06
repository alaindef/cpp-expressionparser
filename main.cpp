
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


#include <defs.h>          // global definitions
#include <utils.h>         // utilities

using namespace std;

bool elaps = true;
clock_t pTime, cTime = clock();
void reportElapsedTime(string msg){
    if (elaps){
        cTime = clock();
        std::cout << "time passed: " << (cTime - pTime)/1000000.0 << " in " << msg << endl;
        pTime = cTime;
    }
}

#include <pass1.h>
#include <pass2.h>
#include <interpreter.h>

int main(int argc, char *argv[])
{
    (void)(argc);(void)(argv);
    initDinges();
    initOperators();

    //tests
    cout << "testing ... \n" << int(c) << endl;
//    cout << "invoke: " << op2[1](2,3) << endl;

// test cases: uncomment 1 of them to try

//    textIn = "1<-2!";
//    textIn = "(2+3)*(1<(-2)) + (6/2)!";
//    textIn = "(2+3)*(1<-2) + (6/2)!";          //CALC CRASH
//    textIn = "1+-2!";
//    textIn = "6*2*4/5!";
//    textIn = "(6)!";
//        textIn = "(6)";
//    textIn = "5*(-1 + (6-2)*2)!";
    textIn = "2*3+5<1?777:((1<2 + (6/2))+17/4)";
//    textIn = "2*-5+17*2-(45<2)!";
//    textIn = "0?2:3!";
//    textIn = "-1+(5<4 ?4*5:(17-5)*3)!";


    cout << "textIn is: " << textIn << endl;
    cout << "\nPASS 1 gives the tokenized input :\n"; parse1();
    printPass(symList, 5);
    cout << "\n\nPASS 2 gives the RPN form of the expression"; parse2();
    printPass(symListOut, 5);

    calcandprint(symListOut);

    cout << "\n\nthe end"<< endl;

    return 0;

    //end TEST

    // the following is not used yet
    int choice = 0;
    cout << "choose:\n1. create the 4 world part files\n2. create srtmfiles\n3. create both\n4. reduce files to Res400\n5. create both and reduce files to Res400\n";
    while ((choice==0) | (choice>3)) {
        cin  >> choice;
        switch (choice) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            cout << "wrong choice " << choice << endl;
            break;
        };
        cin.clear();
        cin.ignore();
    };
    cout << "optionChosen final = " << choice << endl;

    return 0;
}
