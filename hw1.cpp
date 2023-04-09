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
    "UNCLOSED_STRING",
    "ERROR_HEX",
    "ERROR_ESCAPE_SEQUENCE",
  };
void tokenHandler(int token)
{
    bool need_exit = false;
    if (token == ERROR_HEX)
    {
        need_exit = true;
    }
    
    showToken(token_array[token]);

    if( need_exit )
    {
        exit(0);
    }
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