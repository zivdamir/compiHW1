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
string handleLineFeed(string str,char linefeed_symb,int index);
void showToken(const char * token_type);
string handleHexInString(string str, int index);
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
    string yytext_string = string(yytext);
    if(yytext_string[yytext_string.size()-1]='\\'){
        print_unclosed_string_error_and_exit();
    }
    string malicious_string = yytext_string.substr(1, yytext_string.size() - 1);
    char malicious_char = yytext[strlen(yytext) - 1];
    cout << "Error undefined escape sequence " << malicious_string << endl;
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
    int len = yytext_string.length();

    string hex_identifier = "x";
    string escape_chars = "nr0t\"\\";
    
    if (str_token_type != "STRING" )
    {
        if(str_token_type == "COMMENT //")
            cout <<yylineno<<" "<<"COMMENT //" << endl;
        else{
        cout << yylineno << " " << token_type << " " << yytext << endl;
        }
    }
    else{
    if (str_token_type == "STRING"){
    /**/
        
        if(yytext_string.size()<=2)
        {
            std::cout << yylineno <<" "<<str_token_type<<" "<< std::endl;
            return;
        }
        yytext_string = yytext_string.substr(1, len - 2); // removes the " " from the string.
        
        for (int i = 0; i < yytext_string.size() - 1; i++)
        {
            //cout << continue;
            
            if (yytext_string[i] == '\\') /**/

            {
                char c = char(yytext_string[i + 1]);
                
                
                if(hex_identifier.find(c) !=std::string::npos)
                {
                    
                    yytext_string = handleHexInString(yytext_string, i);
                }
                if (escape_chars.find(c) != std::string::npos) /* c = str_token_type[i+1]
                    if c is in ['n','r','0','t',' " ','\',]*/
                {
                    if ( c == 'n')
                    {
                        yytext_string = handleLineFeed(yytext_string, '\n', i);
                    }
                    else if ( c == 'r')
                    {
                        yytext_string = handleLineFeed(yytext_string, '\r', i);
                    }
                    else if (c == '0'){
                        yytext_string = handleLineFeed(yytext_string, '\0', i);
                    }
                    else if (c == 't'){
                        yytext_string = handleLineFeed(yytext_string, '\t', i);
                    }
                    else if (c == '"'){
                        yytext_string = handleLineFeed(yytext_string, '\"', i);
                    }
                    else if (c == '\\'){
                        yytext_string = handleLineFeed(yytext_string, '\\', i);
                    }
                    //std::cout << yylineno <<" "<<str_token_type<<" "<< yytext_string << std::endl;
                }   
                
                
            }

        }
                    std::cout << yylineno <<" "<<str_token_type<<" "<< yytext_string << std::endl;

    }
    }
}
string handleHexInString(string str, int index){
    string copy = str;
    int s_len = copy.length();
    bool is_invalid_scnd_hex_digit = copy[index + 2] < '0' || copy[index + 2] > '7'; // might be 9 instead of 7? TODO
    bool is_invalid_third_hex_digit = copy[index + 3] < '0' || (copy[index + 3] > '9' && copy[index + 3] < 'A') || (copy[index + 3] > 'F' && copy[index + 3] < 'a') || copy[index + 3] > 'f';

    if (index + 3 >= s_len || is_invalid_scnd_hex_digit || is_invalid_third_hex_digit)
    {
        //less then two symbols after \x
        std::cout << "Error undefined escape sequence  " << copy.erase(0,index+1).substr(0,3) << std::endl;//problematic line
        exit(0);
    }
    std::string hex_val = copy.std::string::substr(index+2,2);
    copy[index] = std::stoi(hex_val, 0, 16);
    if(copy[index] < 0 || copy[index] > 127)
    {
        //error
        std::cout << "Error undefined escape sequence " << std::string(yytext).erase(0,index+1).substr(0,3) << std::endl;
        exit(0);
    }
    copy.std::string::erase(index+1, 3);
    return copy;
}
string handleLineFeed(string str, char linefeed_symb, int index)
{
    string copy = str;
    copy[index] = linefeed_symb;
    copy.erase(index + 1, 1);
    return copy;
}
int main(){
	int token;
	while(token = yylex()) {
        tokenHandler(token);
       
    }
    return 0;
}