#ifndef RULESPROCESSOR_H
#define RULESPROCESSOR_H

#include <stdio.h>
#include <string.h>
#include <string>

#include <iostream>
#include <algorithm>  // for std::remove_if
#include <cctype>     // for std::isspace
#include <cstring>    // for strcmp
#include <map>        // for map
#include <sstream>

#include "ScopeProcessor.h"

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
                {"#", "hashtag"},
                {"*", "asterisk"},
            };
        
        ScopeProcessor* globalScopeProcessor = new ScopeProcessor("global");
        ScopeProcessor* currentScopeProcessor = globalScopeProcessor;

        void trimString(string &s)
        {
            s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
        }

        void removeCharacter(string &s, char charToRemove)
        {
            s.erase(std::remove_if(s.begin(), s.end(), [charToRemove](char c) { return c == charToRemove; }), s.end());
        }

        void print(const char* keyword, const char* word, bool shouldTrim = true)
        {
            string srtingWord(word);

            if(shouldTrim)
            {
                trimString(srtingWord);
            }
                
            printf("[%s, %s]", keyword, srtingWord.c_str());
        }

        vector<string> splitString(const char* base, char delimitator, bool log = false)
        {
            vector<string> splittingResult;
            stringstream stream(base);
            string token;

            while (getline(stream, token, delimitator)) 
            {
                splittingResult.push_back(token);
            }

            if(log)
            {
                for(string& word : splittingResult) 
                {
                    print("debug", word.c_str());
                }   
            }

            return splittingResult;
        }

    public:

        void numberRule()
        {
            print("num", yytext);
        }

        void floatNumberRule()
        {
            print("float_num", yytext);
        }

        void stringsRule(){
            string word(yytext);
            removeCharacter(word, '"');
            print("string_literal", word.c_str(), false);
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

        void arithmeticOperatorRule()
        {
            print("arithmetic_operator", yytext);
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
        
        void methodDeclarationRule() {
            string word(yytext);
            vector<string> words = splitString(word.c_str(),' ');
            removeCharacter(words.at(1), '(');

            currentScopeProcessor = new ScopeProcessor(words.at(1).c_str());
            globalScopeProcessor->addMethod(currentScopeProcessor);
            
            print("reserved_word", words.at(0).c_str());
            print("id",to_string(globalScopeProcessor->subIdentifier).c_str());
            print("l_paren","(");
        }

        void variableDeclarationRule() {
            string word(yytext);
            vector<string> words = splitString(word.c_str(),' ');

            print("reserved_word", words.at(0).c_str());

            for(string& word : words) 
            {
                if(!word.compare(words.at(0)))
                {
                    continue;
                }

                trimString(word);
                removeCharacter(word, ',');

                //garante que * e & sejam processados corretamente
                if (word.size() == 1) {
                    string identifiedSpecialCharacter = specialCharacters[word];
                    print(&identifiedSpecialCharacter[0], word.c_str());
                }
                else
                {
                    currentScopeProcessor->addVariable(word);

                    print("id", 
                        (to_string(currentScopeProcessor->scopeIdentifier) + 
                        "." + 
                        to_string(currentScopeProcessor->subIdentifier)).c_str());
                }
            }
        }

        void variableLookupRule(){
            // string word(yytext);
            // int id = globalScope->find(word);
            // if (id >= 0) {
            //     stringcontrol::printKeyword("id", ( to_string(globalScope-> id) + "." +  to_string(id)).c_str());
            // } else {
            //     id = currentScope -> find(word);
            //     if (id >= 0) {
            //         stringcontrol::printKeyword("id", ( to_string(currentScope-> id) + "." +  to_string(id)).c_str());
            //     }else{
            //     printf("%s",yytext);
            //     }
            // }
        }
};
#endif
