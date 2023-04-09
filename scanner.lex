%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"

%}

%option yylineno
%option noyywrap
void            ('void')
digit   		([0-9])
letter  		([a-zA-Z])

whitespace		([\t\n ])

%%
void                        return VOID;  
{digit}+          			return NUM;
{letter}+					return WORD;
{letter}+@{letter}+\.com	return EMAIL;
{whitespace}				;
.		printf("Lex doesn't know what that is!\n");

%%

