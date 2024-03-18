
#include <string>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>

#include <defs.h>          // global definitions
#include <utils.h>         // utilities

using namespace std;

#include "pass0.h"
#include <Tokenizer.h>
#include <rpnizer.h>
#include <interpreter.h>

int main(int argc, char *argv[])
{
    (void)(argc);(void)(argv);


    initOperators();

    string text = "";

    vector<string> inputs = {"","type it yourself",
                             "0?222:3",
                             "4/5",
                             "2<3",
                             "2>3",
                             "2==2",
                             "2==3",
                             "a=3",
                             "a=14+3",
                             "a=14==14*2",
                             "1*2+3/4",
                             "3*(2+9)",
                             "(1*2)+(3/4-(5-6))",
                             "(2+3)*(1<(-2)) + (6/2)",
                             "1+-2",
                             "6*2*4/5",
                             "(6)",
                             "5*(-1 + (6-2)*2)",
                             "2*3+5<1?777:((1<2 + (6/2))+17/4)",
                             "(1<2 + (6/2))+17/4",
                             "2*-5+17*2-(45<2)"};


    uint32_t choice = 0;
    string ch = "";

    int a = 1;              //test 0 ==> pass0 else calc

    while (true) {
        cout << "press ENTER to continue";

        cin.ignore();
        cout << "\nchoose:         -- choose 0 to exit\n"
                "\n1. enter expression";
        for (uint32_t i = 2; i<inputs.size(); i++) cout << "\n" << i << ". " << inputs[i] ;
        cout << "\n\nchoice ==> ";
        //    cin  >> choice;  //because cin stops at spaces, we use getline now. do not mix cin and getline!
        getline(cin, ch);
        if (ch!="")
            if (isNumeric(ch) ){
                choice = stoi(ch);
                if (choice < inputs.size()){
                    if (choice == 0) return 0;
                    if (choice == 1) {
                        getline(cin, text);
                        if (text == "") continue;
                    }

                    else text = inputs[choice];
                    cout << "\ntext in: " << text << endl;

                    if (a == 0){
                        pass0 p0;
                        p0.tokenize(text);
                    }

                    else{
                        cout << "\nPASS 1 gives the tokenized input :\n";

                        Tokenizer tokenizer;
                        std::vector<Token> tokens = tokenizer.tokenize(text);
                        printPass(tokens, 5);

                        RPNizer pass2(tokens);
                        cout << "\n\nPASS 2 gives the RPN form of the expression:\n";

                        RPNTokenList tokensRPN = pass2.toRPN();
                        printRPN(tokensRPN, 5);
                        calcandprint(tokensRPN);
                    }

                } else cout << "choice not allowed" << endl;
            } else
                cout << "no  number. retry" << endl;
    };

    return 0;
}
