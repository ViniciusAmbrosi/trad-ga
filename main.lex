%option noyywrap

%{

#include <stdio.h>
#include <string.h>

#include "common/RulesProcessor.h"

RulesProcessor rulesProcessor;

%}

COMMENT ("//".*)
COMMENT_BLOCK ("/*"[^*/]*"*/")
SPECIAL_CHARACTERS (\(|\)|\{|\}|,|;|#|\[|\])

NUMBERS [0-9]+
FLOAT_NUMBERS [0-9]+[.][0-9]+
STRINGS (\"[^\n"]+\")|""

RELATIONAL_EQUAL_OP (\ )*(==|>=|<=|=|<|>|!==)(\ )*
LOGICAL_OP (\ )*(&&|\|\|)(\ )*

PRIMITIVE_TYPES (int|byte|boolean|char|long|float|double|short|string|void|enum)
ACCESS_LEVEL_KEYWORDS (private|protected|public)
CLASS_KEYWORDS (abstract|class|extends|implements|interface|static|import|package|super|instanceof)
FLOW_CONTROL_KEYWORDS (break|continue|goto|throw|throws|case|return)
VARIABLE_KEYWORDS (const|final|default|new|null|this|transient|volatile|true|false)
METHODS_KEYWORDS (clrscr|scanf|print|printf|catch|do|else|for|finally|if|switch|try|while|getch)

RESERVED_KEYWORD ({PRIMITIVE_TYPES}|{ACCESS_LEVEL_KEYWORDS}|{CLASS_KEYWORDS}|{FLOW_CONTROL_KEYWORDS}|{VARIABLE_KEYWORDS}|{METHODS_KEYWORDS})

%%

{COMMENT}
{COMMENT_BLOCK}
{SPECIAL_CHARACTERS} rulesProcessor.specialCharactersRule();

{NUMBERS} rulesProcessor.numberRule();
{FLOAT_NUMBERS} rulesProcessor.floatNumberRule();
{STRINGS} rulesProcessor.stringsRule();

{RELATIONAL_EQUAL_OP} rulesProcessor.relationalAndEqualOperatorRule();
{LOGICAL_OP} rulesProcessor.logicalOperatorRule();

{RESERVED_KEYWORD} rulesProcessor.reservedKeywordRule();

%%

int main(int argc, char *argv[]){
	yyin = fopen(argv[1], "r");
	yylex();
	fclose(yyin);
	return 0;
}
