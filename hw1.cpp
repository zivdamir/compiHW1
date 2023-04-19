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
const char* token_array[] = {
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
    "OVERRIDE"
  };
void handleLineFeed(string* str,char linefeed_symb,int index);
void showToken(const char * token_type);
void handleHexInString(string *str, int index);
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
    string hex_identifier = "x";
    string escape_chars = "nr0t\"\\";
    
    if (str_token_type != "STRING" )
    {
        if(str_token_type == "COMMENT //")
            cout << "COMMENT //" << endl;
        else{
        cout << yylineno << " " << token_type << " " << yytext << endl;
        }
    }
    else{
    if (str_token_type == "STRING"){
    /**/
        for (int i = 0; i < str_token_type.size()-1 ; i++)
        {
            if(yytext_string[i]=='\\')/**/ 
            {
                char c = yytext_string[i + 1];
                if(hex_identifier.find(c) !=std::string::npos)
                {
                    handleHexInString(&yytext_string, i);
                    exit(-1);
                }
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
                    std::cout << yylineno <<" "<<str_token_type<<" "<< yytext_string << std::endl;
                    
                
                
            }
        }
    }
    }
}
void handleHexInString(string *str, int index){
    string s = *str;
    int s_len = s.length();
    bool is_invalid_scnd_hex_digit = s[index + 2] < '0' || s[index + 2] > '7'; // might be 9 instead of 7? TODO
    bool is_invalid_third_hex_digit = s[index + 3] < '0' || (s[index + 3] > '9' && s[index + 3] < 'A') || (s[index + 3] > 'F' && s[index + 3] < 'a') || s[index + 3] > 'f';

    if (index + 3 >= s_len || is_invalid_scnd_hex_digit || is_invalid_third_hex_digit)
    {
        //less then two symbols after \x
        std::cout << "Error undefined escape sequence " << s.erase(0,index+1).substr(0,3) << std::endl;
        exit(0);
    }
    std::string hex_val = s.std::string::substr(index+2,2);
    s[index] = std::stoi(hex_val, 0, 16);
    if(s[index] < 0 || s[index] > 127)
    {
        //error
        std::cout << "Error undefined escape sequence " << std::string(yytext).erase(0,index+1).substr(0,3) << std::endl;
        exit(0);
    }
    s.std::string::erase(index+1, 3);

}
void handleLineFeed(string *str, char linefeed_symb, int index)
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