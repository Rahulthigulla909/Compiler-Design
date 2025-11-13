/*
 * Program 11: Lex Program to Count Words and Lines
 * 
 * This Lex program counts the number of words and lines in a given file or program.
 * Words are defined as sequences of non-whitespace characters.
 * Lines are counted based on newline characters encountered.
 */

%{
#include <stdio.h>
int words = 0;
int lines = 0;
%}

%%
[^\s\n]+ { words++; }
\n { lines++; }
[ \t]+ { ; }
%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
    printf("Number of lines :: %d\n", lines);
    printf("Number of words :: %d\n", words);
    return 0;
}

