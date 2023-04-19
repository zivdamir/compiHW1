#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
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
    "COMMENT //",
	"ID",
    "NUM",
    "STRING",
    "ERROR_ILLEGAL_SIGN",
    "ERROR_UNCLOSED_STRING",
    "ERROR_ESCAPE_SEQUENCE",
    "ERROR_INVALID_HEX",
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
    char malicious_char = yytext[strlen(yytext)-1];
    cout << "Error undefined escape sequence " << malicious_char << endl;
    exit(0);

}
void print_hex_escape_sequence_errorand_exit()
{
    int yytext_len = strlen(yytext);
    

    char two_char_before_last = yytext[yytext_len-3];
    char one_char_before_last = yytext[yytext_len-2];
    char last_char = yytext[yytext_len-1];

    cout << "Error undefined escape sequence ";

    // case one: "some_str" +'\\' + 'x' + 'letter'
    // case two: "some_str" +'\\' + 'x' 
    // comment: some string might end with 'x' and then we have 'x' + '\\' + 'x'
    // but if it so then we will not have '\\'+'x' + '\\' + 'x'
    
    if(yytext_len >= 4 && yytext[yytext_len-4] == '\\' && two_char_before_last == 'x')
    {
        cout << yytext+(yytext_len-3) << endl;
    }
    else if(two_char_before_last == '\\' && one_char_before_last == 'x')
    {
        cout << yytext+(yytext_len-2) << endl;
    }
    else
    {
        cout << last_char << endl;
    }
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
    string yytext_string = string(yytext);
    string escape_chars = "nr0t\"\\";
    if (str_token_type != "STRING")
    {
        cout << yylineno << " " << token_type << " " << yytext << endl;
    }
    else{
    if (str_token_type == "STRING"){
    /**/
        for (int i = 0; i < str_token_type.size()-1 ; i++)
        {
            if(yytext_string[i]=='\\')/**/ 
            {
                char c = yytext_string[i + 1];
                if (escape_chars.find(c) != std::string::npos) /* c = str_token_type[i+1]
                    if c is in ['n','r','0','t',' " ','\',]*/
                    if ( c == 'n')
                    {
                        handleLineFeed(&yytext_string, '\n', i);
                    }
                    if ( c == 'r')
                    {
                        handleLineFeed(&yytext_string, '\r', i);
                    }
                    if (c == '0'){
                        handleLineFeed(&yytext_string, '\0', i);
                    }
                    if (c == 't'){
                        handleLineFeed(&yytext_string, '\t', i);
                    }
                    if (c == '"'){
                        handleLineFeed(&yytext_string, '\"', i);
                    }
                    if (c == '\\'){
                        handleLineFeed(&yytext_string, '\\', i);
                    }
                    std::cout << yylineno <<" "<<str_token_type<<" "<< yytext_string << std::endl
                    
                {
                
                }
                
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