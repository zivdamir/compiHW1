%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"

%}

%option yylineno
%option noyywrap
esc              ([\\ntr\"0])
hex              (\\x[0-7][0-9A-Fa-f])
whitespace       ([ \t\n\r])
digit            ([0-9])
letter           ([a-zA-Z])
letter_digit      ([a-zA-Z0-9])
str                ([ !#-\[\]-~])


%%
void                                                                                return VOID;
int                                                                                 return INT;
byte                                                                                return BYTE;
b                                                                                   return B;
bool                                                                                return BOOL;
auto                                                                                return AUTO;
and                                                                                 return AND;
or                                                                                  return OR;
not                                                                                 return NOT;
true                                                                                return TRUE;
false                                                                               return FALSE;
return                                                                              return RETURN;
if                                                                                  return IF;
else                                                                                return ELSE;
while                                                                               return WHILE;
break                                                                               return BREAK;
continue                                                                            return CONTINUE;
;                                                                                   return SC;
,                                                                                   return COMMA;
\(                                                                                  return LPAREN;
\)                                                                                  return RPAREN;
\{                                                                                  return LBRACE;
\}                                                                                  return RBRACE;
=                                                                                   return ASSIGN;
[<>=!]=|>|<                                                                         return RELOP;
[-+*/]                                                                              return BINOP;
\/\/[^\n\r]*                                                                        return COMMENT;
{letter}{letter_digit}*                                                              return ID;
([1-9]+{digit}*)|0                                                                  return NUM;
\"({str}|\\{esc}|{hex})*\"                                                    return str;
\"({str}|(\\{esc})|{hex})*                                                    return UNCLOSED_str;
\"({str}|\\{esc}|{hex})*\\[^\\ntr\"0]                                         return INVALID_esc_SEQUENCE;
\"({str}|\\{esc}|{hex})*\\x([^0-7][0-9A-Fa-f]|[0-7][^0-9A-Fa-f]|[^0-7][^0-9A-Fa-f]|[^0-9A-Fa-f]) return INVALID_HEX;
{whitespace}                                                                        ;
.                                                                                   return ERROR;

%%

