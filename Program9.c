/*
 * Program 9: Recursive Descent Parser with Lookahead
 * 
 * This program implements a top-down recursive descent parser with lookahead for parsing
 * expressions. Grammar: S -> (L) | a, L -> S L', L' -> , S L' | ε
 * The parser uses a lookahead character to make parsing decisions and validates expressions
 * containing parentheses, commas, and the terminal symbol 'a'.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char input[100];
int pos = 0;
char lookahead;

void S();
void L();
void Lprime();
void Match(char ch);

void Match(char ch) {
    if (lookahead == ch) {
        lookahead = input[++pos];
    }
    else {
        printf("Error: expected '%c' at Position %d\n", ch, pos);
        exit(1);
    }
}

void S() {
    if (lookahead == '(') {
        Match('(');
        L();
        Match(')');
    }
    else if (lookahead == 'a') {
        Match('a');
    }
    else {
        printf("Error: Unexpected symbol %c at position %d\n", lookahead, pos);
        exit(1);
    }
}

void L() {
    S();
    Lprime();
}

void Lprime() {
    if (lookahead == ',') {
        Match(',');
        S();
        Lprime();
    }
}

int main() {
    printf("Enter an expression: ");
    scanf("%s", input);
    lookahead = input[pos];
    S();
    if (lookahead == '#') {
        printf("Parsing successful: Input is valid.\n");
    }
    else {
        printf("Parsing failed\n");
    }
    return 0;
}

