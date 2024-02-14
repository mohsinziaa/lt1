%{
#include "myscanner.h"
%}
%option nounput yylineno

%%
"|"					return PIPE;
":-"                return SEPERATOR;
"Name"				return NAME;
"Reg_Number"		return REG_NUMBER;
"Deptt"				return DEPTT;

[a-zA-Z][_a-zA-Z]*	return IDENTIFIER;
[1-9][0-9]*			return INTEGER;
[ \t\n]				;
.					printf("unexpected character\n");

%%

int yywrap(void)
{
	return 1;
}

