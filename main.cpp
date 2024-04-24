#include <string>
#include <iostream>
#include <vector>
#include <sys/stat.h>

#include "utils.h"
#include "vartable.h"
#include "tokengenerator.h"
#include "rpngenerator.h"
#include "calculator.h"
#ifdef WIN32
#include <windows.h>
#endif

using namespace std;
void sleep(unsigned msec)
{
    struct timespec sleepTime;
    sleepTime.tv_sec = msec / 1000;
    sleepTime.tv_nsec = (msec % 1000) * 1000000;
    nanosleep(&sleepTime, NULL);
}

int main(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);
    string text = "";

    int reportLevel = 0; // provisional - controls reporting

    const map<std::string, Token> keywords = {
        {"NUM", {OC::NUM, 0, 0, 0}}, // {opcode, arity, precedence, value}
        {"VAR", {OC::VAR, 0, 0, 0}},
        {"*", {OC::MUL, 2, 3, 0}},
        {"/", {OC::DIV, 2, 3, 0}},
        {"+", {OC::ADD, 2, 4, 0}},
        {"-", {OC::SUB, 2, 4, 0}},
        {"<", {OC::LT, 2, 6, 0}},
        {"<=", {OC::LE, 2, 6, 0}},
        {">", {OC::GT, 2, 6, 0}},
        {">=", {OC::GE, 2, 6, 0}},
        {"==", {OC::EQ, 2, 7, 0}},
        {"!=", {OC::NE, 2, 7, 0}},
        {"?", {OC::QU, -1, 13, 0}},
        {":", {OC::COL, 3, 13, 0}},
        {"=", {OC::ASS, 2, 14, 0}},
        {"(", {OC::PAR_L, 0, 0, 0}},
        {")", {OC::PAR_R, 0, 0, 0}},
        {"NIL", {OC::NIL, 0, 0, 0}}};

    VarTable vvv;

    // Calculator calc(&variables);
    vector<Token> tokenList;
    // vector<RpnGenerator::RPNToken> tokensRPN;

    // SPEEDTEST

    if (1 == 2)
    { // 1==1 if you want it!
        text = "b=a*a*a/100000000";
        tokenList = makeTokenList(text, keywords, vvv, 0);
        // tokensRPN = p3.makeRPN(tokenList);
        int n = 0;
        while (n < 500000)
        {
            std::cout << "\033[H\033[2J\033[3J";
            vvv.setVar(0, n);
            // calc.calcandprint(tokensRPN, false);
            n++;
        }
        sleep(100); // without sleep, cout gets in trouble in this final phase
        // calc.calcandprint(tokensRPN, true);
        return 0;
    }
    // SPEEDTEST END

    vector<string> inputs = {"", "type it yourself",
                             "4/5",
                             "2<3",
                             "2>3",
                             "b=17",
                             "c=30",
                             "kees = c?b:88",
                             "kees = (c?b:88)",
                             "a=b?111:222",
                             "a=2*b+c",
                             "drum = a + 2 * (keeskop=c?b:88)",
                             "a=14==14*2",
                             "1*2+3/4",
                             "3*(2+9)",
                             "(1*2)+(3/4-(5-6))",
                             "(2+28)*(1<(-23)) + (6/2)",
                             "1+-2",
                             "6*2*4/5",
                             "(6)",
                             "5*(-1 + (6-2)*2)",
                             "0?222:3",
                             "2*3+5<1?777:((1<2 + (6/2))+17/4)",
                             "(1<2 + (6/2))+17/4",
                             "2*-5+17*2-(45<b)"};

    vector<RPNToken> tokensRPN;
    string ch = "";
    long unsigned int choice = 0;

    cout << "\nchoose: (0 to exit)\n"
            "\n1. enter expression";

    for (long unsigned int i = 2; i < inputs.size(); i++)
        cout << "\n"
             << i << ". " << inputs[i];
    cout << endl;
    cout << "\nvartable at start:";
    vvv.printVarTable();
    while (true)
    {
        cout << "\nchoice (0 to exit, 1 to enter expression manually, r to toggle reporting level) ==> ";
        cin >> ch;
        cin.ignore();
        if (ch != "")
        {
            if (isNumeric(ch))
            {
                choice = stoi(ch);
                if (choice < inputs.size())
                {
                    if (choice == 0)
                        return 0;
                    if (choice == 1)
                    {
                        getline(cin, text);
                        tokensRPN = makeRPN(text, keywords, vvv, reportLevel);
                        int cursor = 17;
                        calc(tokensRPN, vvv);
                        if (text == "")
                            continue;
                    }
                    else
                        text = inputs[choice];
                    cout << "\ntext in:\t\t" << text << "\t\t";

                    // directly from expression to RPN:
                    tokensRPN = makeRPN(text, keywords, vvv, reportLevel);

                    // separate calls:
                    // vector<Token> tokenList = makeTokenList(text, keywords, vvv, reportLevel);
                    // vector<RPNToken> tokensRPN = makeRPN(tokenList);

                    calcandprint(tokensRPN, vvv, true);
                }
                else
                    cout << "choice not allowed" << endl;
            }
            else if (ch == "r")
                reportLevel = 1 - reportLevel;
            else
                cout << "no  number. retry" << endl;
        }
    };

    return 0;
}
