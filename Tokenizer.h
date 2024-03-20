#pragma once
#include <defs.h>
#include <vector>
#include <string>
//  PASS 1 will scan the input test and generate a list of symbols

#include <algorithm>

using namespace std;
class Tokenizer
{
public:
    Tokenizer();
    TokenList tokenize(std::string textIn);

private:
    TokenType kartyp[256];    // type of each character
    std::string KarPP[256];      // string representation of each character
    bool errorsPresent = false;

    bool isaC(char Kar, std::vector<TokenType> allowedTypes)
    {
        int cnt = std::count(allowedTypes.begin(), allowedTypes.end(), kartyp[int(Kar)]);
        return(cnt > 0);
    }
    Token makeToken(const std::string& textIn, uint32_t& cursor, std::vector<TokenType> expected);

    string getVarAdress(string var, string vars[] );

};
