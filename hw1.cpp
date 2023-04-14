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
    exit(0);
}

void print_unclosed_string_error_and_exit()
{
    cout << "Error unclosed string"  << endl;
    exit(0);
}
void print_escape_sequence_error_and_exit()
{
    if(yytext is in the exercise definition& is \)
    {
        print_illegal_sign_error_and_exit();
    }

    cout << "Error undefined escape sequence ";
    if(yytext is in the exercise definition& is \q)
    {
        cout<< "q" << endl;
    }
    else if(yytext is in the exercise definition& is \q)
    {
        cout << "xFT" << endl;
    }
    exit(0);
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
    string str_token_type = string(token_type);
    if (str_token_type != "STRING")
    {
        cout << yylineno << " " << token_type << " " << yytext << endl;
    }
    else{
        for (int i = 0; i < str_token_type.size()-1 ; i++)
        {
            if(str_token_type[i]=='\\') 
            {
                if(str_token_type[i+1]=='n')
                {
                handleLineFeed(&str_token_type, '\n', i);
                }
                
            }
        }
    }
}
void handleLineFeed(string* str,char linefeed_symb,int index)
{
    (*str)[index] = linefeed_symb;
    (*str).erase(index + 1, 1);
}
int main(){
	int token;
	while(token = yylex()) {
        showToken(token_array[token]);
    }
    return 0;
}