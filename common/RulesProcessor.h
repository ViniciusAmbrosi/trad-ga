#ifndef RULESPROCESSOR_H
#define RULESPROCESSOR_H

#include <string.h>
#include <string>

#include <iostream>
#include <algorithm>  // for std::remove_if
#include <cctype>     // for std::isspace


using namespace std;

class RulesProcessor
{
    private:
        void trimString(string &s)
        {
            s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
        }

        void print(const char* keyword, const char* word)
        {
            string srtingWord(word);
            trimString(srtingWord);
            printf("[%s, %s]", keyword, srtingWord.c_str());
        }

    public:

        void digitRule()
        {
            print("num", yytext);
        }

        void floatNumRule()
        {
            print("float_num", yytext);
        }

        void relationalOperatorRule()
        {
            print("Relational_Op", yytext);
        }
};
#endif
