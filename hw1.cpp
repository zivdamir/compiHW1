#include <stdio.h>
#include <stdlib.h>
#include "tokens.hpp"
extern int yylex();
char* token_array[] = {
    "AUTO",
    "VOID",
    "INT",
    "BYTE",
    "B",
    "BOOL",
    "AND",
    "OR",
    "NOT",
    "TRUE",
    "FALSE",
    "RETURN",
    "IF",
    "ELSE",
    "WHILE",
    "BREAK",
    "CONTINUE",
    "SC",
    "COMMA",
    "LPAREN",
    "RPAREN",
    "LBRACE",
    "RBRACE",
    "ASSIGN",
    "RELOP",
    "BINOP",
    "COMMENT",
	"ID",
    "NUM",
    "STRING",
    "ERROR",
    "ERROR_UNCLOSED_STRING",
    "ERROR_HEX",
    "ERROR_ESCAPE_SEQUENCE",
  };
void tokenHandler(int token)
{
    if (token == ERROR_ILLEGAL_SIGN)
    {
        print_illegal_sign_error_and_exit();
    }
    else
    
    showToken(token_array[token]);
}
void showToken(const char * name)
{
        printf("Lex found a %s, the lexeme is %s and its length is %d\n", name, yytext, yyleng);
}

int main(){
	int token;
	while(token = yylex()) {
        showToken(token_array[token]);
    }
    return 0;
}