#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include "tokens.hpp"

using std::cout;
using std::endl;
using std::string;

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
    "ERROR_ILLEGAL_SIGN",
    "ERROR_ESCAPE_SEQUENCE",
  };

void print_illegal_sign_error_and_exit()
{
    char* illegal_sign = yytext;
    cout << "Error " << illegal_sign << endl;
}

void print_unclosed_string_error_and_exit()
{
    cout << "Error unclosed string"  << endl;
}
void print_unclosed_string_error_and_exit()
{

}
void print_escape_sequence_error_and_exit()
{

}

void tokenHandler(int token)
{
    if (token == ERROR_ILLEGAL_SIGN)
    {
        print_illegal_sign_error_and_exit();
    }
    else if(token == ERROR_UNCLOSED_STRING)
    {
        print_unclosed_string_error_and_exit();
    }
    else if(token == ERROR_ESCAPE_SEQUENCE)
    {
        print_escape_sequence_error_and_exit();
    }

    
    showToken(token_array[token]);
}
void showToken(const char * token_type)
{
    //<line_no> <token_name> <value>
    //token name is "token_type"
        if( )
        printf("%d %s %s\n", yylineno, token_type, yytext);
}

int main(){
	int token;
	while(token = yylex()) {
        showToken(token_array[token]);
    }
    return 0;
}