/*
 * Program 8: Recursive Descent Parser with Lookahead
 * 
 * This program implements a top-down recursive descent parser with lookahead for arithmetic expressions.
 * Grammar: E -> T E', E' -> + T E' | ε, T -> F T', T' -> * F T' | ε, F -> (E) | id
 * The parser uses a lookahead character to make parsing decisions and validates expressions
 * containing addition (+), multiplication (*), parentheses, and the terminal symbol 'id'.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char input[100];  // input string
int pos = 0;      // current position in input
char lookahead;   // current symbol

// Function prototypes
void E();
void Eprime();
void T();
void Tprime();
void F();

void match(char t) {
    if (lookahead == t) {
        lookahead = input[++pos];
    } else {
        printf("Error: expected '%c' at position %d\n", t, pos);
        exit(1);
    }
}

// Grammar: E -> T E'
void E() {
    T();
    Eprime();
}

// Grammar: E' -> + T E' | ε
void Eprime() {
    if (lookahead == '+') {
        match('+');
        T();
        Eprime();
    }
    // else epsilon → do nothing
}

// Grammar: T -> F T'
void T() {
    F();
    Tprime();
}

// Grammar: T' -> * F T' | ε
void Tprime() {
    if (lookahead == '*') {
        match('*');
        F();
        Tprime();
    }
    // else epsilon → do nothing
}

// Grammar: F -> (E) | id
void F() {
    if (lookahead == '(') {
        match('(');
        E();
        match(')');
    } else if (lookahead == 'i') { // 'id' is represented as "id"
        match('i');
        if (lookahead == 'd') {
            match('d');
        } else {
            printf("Error: expected 'd' after 'i'\n");
            exit(1);
        }
    } else {
        printf("Error: unexpected symbol '%c' at position %d\n", lookahead, pos);
        exit(1);
    }
}

int main() {
    printf("Enter an expression: ");
    scanf("%s", input);

    lookahead = input[pos];  // initialize lookahead

    E();

    if (lookahead == '\0') {
        printf("Parsing successful\n");
    } else {
        printf("Parsing failed\n");
    }

    return 0;
}
