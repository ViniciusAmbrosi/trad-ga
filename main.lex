%option noyywrap

%{

#include <stdio.h>
#include <string.h>

#include "common/RulesProcessor.h"

RulesProcessor rulesProcessor;

%}

NUMBERS [0-9]+
FLOAT_NUMBERS [0-9]+[.][0-9]+

%%

{NUMBERS} rulesProcessor.digitRule();
{FLOAT_NUMBERS} rulesProcessor.floatNumRule();

%%

int main(int argc, char *argv[]){
	yyin = fopen(argv[1], "r");
	yylex();
	fclose(yyin);
	return 0;
}
