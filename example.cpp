#include <stdio.h>
#include "tokens.hpp"
extern int yylex();

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
	}
	return 0;
}