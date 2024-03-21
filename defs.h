#pragma once
#include <string>
#include <vector>



using namespace std;

// PASS0 should replace PASS1


struct Token0 {int opcode; int arity; int precedence;} ;
using Token0List = vector<Token0>;


//  PASS 1 will scan the input test and generate a list of symbols
//    we will assign a type to each allowed character  .
//    e.g. character 'h' (ascii 104)  is a t_LETT, character '0' (ascii 48 )is a t_DIGIT. character (40) is t_PAR_L (left parenthesis)
//    the following are the possible character types:
enum TokenType
{t_ETX,   t_LF, t_TAB,  t_BLANK,  t_HASHT,  t_PAR_L,  t_PAR_R,  t_DOT,   t_TIMES,  t_DIV, t_PLUS,   t_MINUS,  t_LT, t_EQ, t_GT, t_QUEST,  t_COLON,  t_LETT,   t_DIGIT,  t_CR, t_OTHER,  t_EXCLA,  t_TEST};

//typedef std::vector<TokenType> TokenTypeList;

typedef struct {
    TokenType type;
    std::string content;
    int opcode;
    int arity;
    int precedence;
    uint32_t cursor;
} Token;

typedef std::vector<Token> TokenList;



//PASS 2 will scan the output of PASS1 and generate a list of tokens
// precedence is according to   https://en.cppreference.com/w/cpp/language/operator_precedence#cite_note-2
//                          or  https://en.wikipedia.org/wiki/Order_of_operations
// although pass2 needs far less tokentypes than the types from pass1, we will reuse the definition of pass1 and work with that

// RPNToken is used in the OUTPUT of RPNizer, en input for the Interpreter
typedef struct {
    int opcode;
    int arity;
    std::string content;
    uint32_t cursor;
} RPNToken;

typedef std::vector<RPNToken>   RPNTokenList;

// prettyPrint of TokenType:
inline std::string& TokenToString(TokenType tt)
{
    static std::string ppTokenType[32] ={"ETX", "LF", "TAB", "BLANK", "HASHT", "PAR_L", "PAR_R", "DOT", "TIMES", "DIV", "PLUS", "MINUS", "LT", "EQ", "GT", "QUEST", "COLON", "LETT", "DIGIT", "CR", "OTHER", "EXCLA",  "TEST"};
    return ppTokenType[int(tt)];
}
