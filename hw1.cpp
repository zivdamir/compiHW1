#include <stdio.h>
#include "tokens.hpp"
extern int yylex();
#define ARR_SIZE 34
char* token_array[ARR_SIZE] = {
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
void stringHandler(int token)
{


}
void showToken(const char * name)
{
        printf("Lex found a %s, the lexeme is %s and its length is %d\n", name, yytext, yyleng);
}

int main(){
	int token;
	while(token = yylex()) {
		if (token == NUM) {
			showToken("NUM");
		} else if (token == WORD) {
			showToken("WORD");
		} else if (token == EMAIL) {
			showToken("EMAIL");
		}
        else if (token == VOID){
            showToken("VOID");
        }
    }
	return 0;
}