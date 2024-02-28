
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

#include <defs.h>;

using namespace std;

typedef int FileNumber;

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

Token tt = {VARI, 0, "haha", 0};        //test
int main(int argc, char *argv[])
{
    (void)(argc);(void)(argv);
    initDinges();

    //tests
    vector<Token> pass1Out;
    char c = '1';
    cout << "code c =" << int(c) << endl;

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
        case 4:
//            cout << invoke(BLANK, 3, &add) << endl;
            cout << "makesymbol " << makeSymbol({VARI, LIT}).type << endl;
            break;
        case 5:
            cout << "token is : " << isa(tt, {CHS, ELV_C }) << endl;
            break;
        case 6:
            pass1Out = parse("1+2!");
            cout << "parser is : " << pass1Out[0].content << " en " << pass1Out[1].content << endl;
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
