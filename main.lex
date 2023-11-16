%option noyywrap

%{

#include <stdio.h>
#include <string.h>

#include "common/RulesProcessor.h"

RulesProcessor rulesProcessor;

%}

IDENTATION ([ \t\n\r])
COMMENT ("//".*)
COMMENT_BLOCK ("/*"[^*/]*"*/")
SPECIAL_CHARACTERS (\(|\)|\{|\}|,|;|#|\[|\])

NUMBERS [0-9]+
FLOAT_NUMBERS [0-9]+[.][0-9]+
STRINGS (\"[^\n"]+\")|""
HEADER_NAME ([a-zA-Z]+\.h)

ALPHANUMERIC_WORD [a-zA-Z0-9]*

RELATIONAL_EQUAL_OP (\ )*(==|>=|<=|=|<|>|!==)(\ )*
LOGICAL_OP (\ )*(&&|\|\|)(\ )*
ARITHMETIC_OP [+]|[-]|[*]|[/]

PRIMITIVE_TYPES (int|byte|boolean|char|long|float|double|short|string|void|enum)
ACCESS_LEVEL_KEYWORDS (private|protected|public)
CLASS_KEYWORDS (abstract|class|extends|implements|interface|static|import|package|super|instanceof)
FLOW_CONTROL_KEYWORDS (break|continue|goto|throw|throws|case|return)
VARIABLE_KEYWORDS (const|final|default|new|null|this|transient|volatile|true|false)
METHODS_KEYWORDS (clrscr|scanf|print|printf|catch|do|else|for|finally|if|switch|try|while|getch|include)

RESERVED_KEYWORD ({PRIMITIVE_TYPES}|{ACCESS_LEVEL_KEYWORDS}|{CLASS_KEYWORDS}|{FLOW_CONTROL_KEYWORDS}|{VARIABLE_KEYWORDS}|{METHODS_KEYWORDS})

SINGLE_SPACE (\ )+

VARIABLE ({PRIMITIVE_TYPES}(\*)?{SINGLE_SPACE}(\*)?(\ )*{ALPHANUMERIC_WORD}(,(\ )*(\*)?(\ )*{ALPHANUMERIC_WORD})*(\ )*;)|{PRIMITIVE_TYPES}(\*)?{SINGLE_SPACE}(\*)?(\ )*{ALPHANUMERIC_WORD}
METHOD {PRIMITIVE_TYPES}(\*)?{SINGLE_SPACE}(\*)?(\ )*{ALPHANUMERIC_WORD}(\ )*(\()

%%

{COMMENT}
{COMMENT_BLOCK}
{SPECIAL_CHARACTERS} rulesProcessor.specialCharactersRule();

{NUMBERS} rulesProcessor.numberRule();
{FLOAT_NUMBERS} rulesProcessor.floatNumberRule();
{STRINGS} rulesProcessor.stringsRule();
{HEADER_NAME} rulesProcessor.stringsRule();

{RELATIONAL_EQUAL_OP} rulesProcessor.relationalAndEqualOperatorRule();
{LOGICAL_OP} rulesProcessor.logicalOperatorRule();
{ARITHMETIC_OP} rulesProcessor.arithmeticOperatorRule();

{RESERVED_KEYWORD} rulesProcessor.reservedKeywordRule();

{VARIABLE} rulesProcessor.variableDeclarationRule();
{METHOD} rulesProcessor.methodDeclarationRule();

#{IDENTATION}

%%

int main(int argc, char *argv[]){
	yyin = fopen(argv[1], "r");
	yylex();
	fclose(yyin);
	return 0;
}
