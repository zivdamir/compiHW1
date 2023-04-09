#ifndef TOKENS_HPP_
#define TOKENS_HPP_
  enum tokentype
  {
    NUM = 1,
    WORD = 2,
    EMAIL = 3,
    VOID = 4,
  };
  extern int yylineno;
  extern char* yytext;
  extern int yyleng;
  extern int yylex();
#endif /* TOKENS_HPP_ */