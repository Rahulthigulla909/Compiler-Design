/*
 * Program 12: Yacc Calculator (Yacc without Lex)
 * 
 * This Yacc program implements a calculator that evaluates arithmetic expressions
 * containing addition (+) and multiplication (*) operations with parentheses.
 * The program includes its own yylex() function instead of using a separate Lex file.
 * Grammar: expr -> expr '+' term | term, term -> term '*' factor | factor, 
 *          factor -> '(' expr ')' | DIGIT
 */

//Yacc without lex.y //

%{
#include<stdio.h>
#include<ctype.h>
%}

%token DIGIT

%%
line:expr '\n' {printf("%d",$1);exit(0);}
    ;

expr:expr '+' term {$$=$1+$3;}
    |term
    ;

term:term '*' factor {$$=$1*$3;}
    |factor
    ;

factor: '(' expr ')' {$$=$2;}
   |DIGIT
   ;

%%
yylex()
 {
  int c;
  c=getchar();
  if(isdigit(c))
  {
   yylval=c-'0';
   return DIGIT;
 }
return c;
 }

void main()
 {
  yyparse();
 }

 void yyerror(char *s)
 {
  printf("%s",s);
 }

