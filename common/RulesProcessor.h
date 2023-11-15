#ifndef RULESPROCESSOR_H
#define RULESPROCESSOR_H

#include <string.h>
#include <string>

#include <iostream>
#include <algorithm>  // for std::remove_if
#include <cctype>     // for std::isspace
#include <cstring>    // for strcmp
#include <map>        // for map

using namespace std;

class RulesProcessor
{
    private:
        map<string, string> specialCharacters = 
            {
                {"[", "l_bracket"},
                {"]", "r_bracket"},
                {"(", "l_paren"},
                {")", "r_paren"},
                {"{", "l_curly_bracket"},
                {"}", "r_curly_bracket"},
                {",", "comma"},
                {";", "semicolon"},
                {"&", "ampersand"},
                {"#", "hashtag"}
            };

        void trim(const char* s)
        {
            string srtingWord(s);
            trimString(srtingWord);
        }

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

        void relationalAndEqualOperatorRule()
        {
            string word(yytext);
            trimString(word);
            if(!word.compare("="))
            {
                print("equal_op", yytext);
            }
            else
            {
                print("relational_op", yytext);
            }
        }

        void logicalOperatorRule()
        {
            print("logic_op", yytext);
        }

        void reservedKeywordRule()
        {
            print("reserved_word", yytext);
        }

        void specialCharactersRule()
        {
            string character(yytext);
            trimString(character);

            string identifiedSpecialCharacter = specialCharacters[character];
            print(&identifiedSpecialCharacter[0], yytext);
        }
};
#endif
