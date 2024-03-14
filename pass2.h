#ifndef PASS2_H
#define PASS2_H


class Pass2
    {
private:
    std::vector<Token> tokens;
    int tokenidx = 0;
    std::vector<Token> tokensout;
public:
    //PASS 2 will scan the output of PASS1 and generate a list of tokens
    // precedence is according to   https://en.cppreference.com/w/cpp/language/operator_precedence#cite_note-2
    //                          or  https://en.wikipedia.org/wiki/Order_of_operations

    // although pass2 needs far less tokentypes than the types from pass1, we will reuse the definition of pass1 and work with that


    /*void push(Token sym) {
        symListOut.push_back(sym);
    }*/
    Pass2(std::vector<Token> pTokens) : tokens(pTokens){}

    std::vector<Token>& parse2(){
        tokensout.clear();
        try {
            tokenidx = 0;
            Token tk = nextToken("parse2", {});
            expr(tk);
        } catch (const exception& e) {
            cout << "\n\n!!! PARSE ERROR:" << e.what() << endl<< endl;;
        };
        return tokensout;
    };

    Token nextToken(const std::string& from, std::vector<TokenType> expected){
        // expected: the list of possible TokenTypes. it is filled in by the calling function
        if (tokenidx >= tokens.size()) throw invalid_argument("symbols missing!");
        Token next = tokens[tokenidx++];
        if (expected.empty()) return next;
        if (count(expected.begin(), expected.end(), next.type) > 0) return next;
        // error:
        string ppexpectedList = "";
        for (TokenType t: expected) ppexpectedList += " " + ppTokenType[t];
        throw invalid_argument(
            "from " + from + " at cursor=" + to_string(next.cursor) + " symbol=" + next.content + ", " + ppTokenType[next.type] +
            " is not one of {" + ppexpectedList + "}"                                                      // "expected" should be the list of expected types
            );
        return next;
    }

    /*void expr0(const Token& tk);
    void expr1(const Token& tk);
    void expr2(const Token& tk);
    void expr3(const Token& tk);
    void expr4(const Token& tk);
    void expr6(const Token& tk);
    void expr7(const Token& tk);
    void expr13(const Token& tk);*/

    void expr0(Token& tk){
        if (isa(tk, {t_LETT, t_DIGIT})){
            tokensout.push_back(tk);
            tk = nextToken("expr0", {t_TIMES, t_DIV, t_LT,t_EQ,t_GT, t_PLUS, t_MINUS, t_PAR_L, t_PAR_R, t_COLON, t_QUEST, t_ETX});
        } else
            expr1(tk);
    }

    void expr1(Token& tk){
        if (isa(tk, {t_PAR_L})) {
            tk = nextToken("expr1", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
            expr13(tk);
            if (tk.content != ")")
                throw invalid_argument("received " + tk.content);
            tk = nextToken("expr1", {});
        }
    }
    void expr2(Token& tk){
        expr0(tk);
            if (tk.precedence == 2){
            Token save = tk;
            tk = nextToken("expr2", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
            expr0(tk);
            tokensout.push_back(save);
        }
    }

    void expr3(Token& tk){
        expr2(tk);
        if (tk.precedence == 3){
            Token save = tk;
            tk = nextToken("expr3", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
            expr3(tk);
            tokensout.push_back(save);
        }
    }

    void expr4(Token& tk){
        expr3(tk);
        if (tk.precedence == 4){
            Token save = tk;
            tk = nextToken("expr4", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
            expr4(tk);
            tokensout.push_back(save);
        }
    }

    void expr6(Token& tk){
        expr4(tk);
        if (tk.precedence == 6){
            Token save = tk;
            tk = nextToken("expr6", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
            expr6(tk);
            tokensout.push_back(save);
        }
    }

    void expr7(Token& tk){                                                                           //TODO !!!
        expr6(tk);
        if (tk.precedence == 7){
            Token save = tk;
            tk = nextToken("expr7", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS,t_EQ});
            expr7(tk);
            tokensout.push_back(save);
        }
    }

    void expr13(Token& tk){
        expr7(tk);
        if (tk.precedence == 13){
            Token save = tk;
            tk = nextToken("expr13", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
            expr7(tk);                                                                // no need to push "?", ":" is ternary, will take care
            save = tk;
            tk = nextToken("expr13", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
            expr7(tk);
            tokensout.push_back(save);
        }
    }

    void expr14(Token& tk){
        Token save = tokens.back();
        if (isa(tk, {t_LETT}) &(save.precedence == 14)){
            tokensout.push_back(tk);
            tk = nextToken("expr14", {t_EQ});
            tk = nextToken("expr14", {t_LETT, t_DIGIT, t_PAR_L, t_PLUS, t_MINUS});
            expr13(tk);
            tokensout.push_back(save);
        } else
            expr13(tk);
    }

    void expr(Token& tk){
        expr14(tk);
    }
};


#endif // PASS2_H
