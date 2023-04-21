%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"

%}

%option yylineno
%option noyywrap
valid_esc_seq                                   (\\[\\ntr\"0])
hex_esc_seq                                     (\\x[0-7][0-9A-Fa-f])
invalid_esc_seq                                 (\\[^x\\ntr\"0])
invalid_hex_esc_seq                             \\x([^0-7][0-9A-Fa-f]|[0-7][^0-9A-Fa-f]|[^0-7][^0-9A-Fa-f]|[^0-9A-Fa-f])
whitespace                                      ([ \t\n\r])
digit                                           ([0-9])
letter                                          ([a-zA-Z])
letter_digit                                    ([a-zA-Z0-9])
str_sym_s_t_not_esc_seq                         ([ !#-\[\]-~])


%%
void                                                                                return VOID;
int                                                                                 return INT;
byte                                                                                return BYTE;
b                                                                                   return B;
bool                                                                                return BOOL;
override                                                                            return OVERRIDE;
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
{letter}{letter_digit}*                                                             return ID;
([1-9]+{digit}*)|0                                                                  return NUM;
\"(({str_sym_s_t_not_esc_seq}|{valid_esc_seq}|{hex_esc_seq})*)\"                    return STRING;
\"({str_sym_s_t_not_esc_seq}|{valid_esc_seq}|{hex_esc_seq})*[//]?                   return ERROR_UNCLOSED_STRING;
\"({str_sym_s_t_not_esc_seq}|{valid_esc_seq}|{hex_esc_seq})*({invalid_esc_seq})     return ERROR_ESCAPE_SEQUENCE;
\"({str_sym_s_t_not_esc_seq}|{valid_esc_seq}|{hex_esc_seq})*({invalid_hex_esc_seq})   return ERROR_INVALID_HEX;
{whitespace}                                                                        ;
.                                                                                   return ERROR_ILLEGAL_SIGN;

%%

