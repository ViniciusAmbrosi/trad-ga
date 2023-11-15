#ifndef RULESPROCESSOR_H
#define RULESPROCESSOR_H

using namespace std;

class RulesProcessor
{
    public:

    void digitRule()
    {
        printf("[%s, %s]", "num", yytext);
    }

    void floatNumRule()
    {
        printf("[%s, %s]", "float_num", yytext);
    }
};
#endif
