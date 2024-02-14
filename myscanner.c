#include <stdio.h>
#include <string.h>
#include "myscanner.h"

extern int yylex();
extern int yylineno;
extern char *yytext;
int validString = 0;

char *names[] = {NULL, "Name", "Reg_Number", "Deptt"};

int checkForPipe(int inputText)
{
	if (inputText != PIPE)
	{
		fprintf(stderr, "Error: Missing pipe\n");
		validString = 1;
		return 1;
	}
}

int checkForSeperator(int inputText)
{
	if (inputText != SEPERATOR)
	{
		fprintf(stderr, "Error: Missing Seperator ':-'\n");
		validString = 1;
		return 1;
	}
}

int main(void)
{

	int ntoken, vtoken;

	ntoken = yylex();
	checkForPipe(ntoken);
	ntoken = yylex();

	if (ntoken == NAME)
	{
		ntoken = yylex();
		checkForSeperator(ntoken);
		vtoken = yylex();
		if (vtoken != IDENTIFIER)
		{
			printf("Syntax error in line %d, Expected an identifier but found %s\n", yylineno, yytext);
			validString = 1;
		}
		ntoken = yylex();
		checkForPipe(ntoken);
	}
	else
	{
		printf("Syntax error in line %d, Expected Reg_Number, found %s\n", yylineno, yytext);
		validString = 1;
	}

	ntoken = yylex();

	if (ntoken == REG_NUMBER)
	{
		ntoken = yylex();
		checkForSeperator(ntoken);
		vtoken = yylex();

		int regLength = strlen(yytext);
		if (regLength != 7)
		{
			printf("Syntax error in line %d, %s is not a valid registration number\n", yylineno, yytext);
			validString = 1;
		}

		if (vtoken != INTEGER)
		{
			printf("Syntax error in line %d, Expected an integer but found %s\n", yylineno, yytext);
			validString = 1;
		}
		ntoken = yylex();
		checkForPipe(ntoken);
	}
	else
	{
		printf("Syntax error in line %d, Expected Reg_Number, found %s\n", yylineno, yytext);
		validString = 1;
	}

	ntoken = yylex();
	if (ntoken == DEPTT)
	{
		ntoken = yylex();
		checkForSeperator(ntoken);
		vtoken = yylex();
		if (vtoken != IDENTIFIER)
		{
			printf("Syntax error in line %d, Expected an identifier but found %s\n", yylineno, yytext);
			validString = 1;
		}
		ntoken = yylex();
		checkForPipe(ntoken);
	}
	else
	{
		printf("Syntax error in line %d, Expected Deptt, found %s\n", yylineno, yytext);
		validString = 1;
	}

	if (!validString)
	{
		printf("String is valid!\n");
	}
	else
	{
		printf("String is not valid!\n");
	}

	return 0;
}
