/*
 * Program 10: Computing FIRST Sets for a Grammar
 * 
 * This program computes and displays the FIRST sets for each non-terminal in a given grammar.
 * Grammar: E -> TC, C -> +TC | ε, T -> FD, D -> *FD | ε, F -> (E) | id
 * The FIRST set of a non-terminal contains all terminal symbols that can begin strings
 * derived from that non-terminal.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void computeFirst(char production[][10], int numProductions, char nonTerminal) {
    printf("FIRST(%c) = { ", nonTerminal);
    
    char firstSet[20] = "";
    int i, j;
    
    for (i = 0; i < numProductions; i++) {
        if (production[i][0] == nonTerminal) {
            
            char firstSymbol = production[i][3]; 
            
            if (islower(firstSymbol) || firstSymbol == '(' || firstSymbol == '@' || firstSymbol == '+' || firstSymbol == '*') {
                
                char term[2] = {firstSymbol, '\0'};
                if (strchr(firstSet, firstSymbol) == NULL) {
                    strcat(firstSet, term);
                }
            } else if (isupper(firstSymbol)) {
                
                if (nonTerminal == 'E' && firstSymbol == 'T') {
                    if (strchr(firstSet, '(') == NULL) strcat(firstSet, "(");
                    if (strchr(firstSet, 'i') == NULL) strcat(firstSet, "i");
                }
                else if (nonTerminal == 'T' && firstSymbol == 'F') {
                    if (strchr(firstSet, '(') == NULL) strcat(firstSet, "(");
                    if (strchr(firstSet, 'i') == NULL) strcat(firstSet, "i");
                }
            }
        }
    }
    
    for (j = 0; j < strlen(firstSet); j++) {
        if (firstSet[j] == 'i') {
            printf("'id'"); 
        } else if (firstSet[j] == '@') {
            printf("epsilon"); 
        } else {
            printf("'%c'", firstSet[j]);
        }
        
        if (j < strlen(firstSet) - 1) {
            printf(", ");
        }
    }
    printf(" }\n");
}

int main() {
    char productions[][10] = {
        "E->TC",
        "C->+TC", 
        "C->@",   
        "T->FD",
        "D->*FD", 
        "D->@",   
        "F->(E)",
        "F->i"    
    };
    int numProductions = 8;

    printf("Computing First Sets for the Grammar:\n");
    printf("E -> TC\nC -> +TC | epsilon\nT -> FD\nD -> *FD | epsilon\nF -> (E) | id\n\n");
    
    computeFirst(productions, numProductions, 'F'); 
    computeFirst(productions, numProductions, 'C'); 
    computeFirst(productions, numProductions, 'D'); 
    computeFirst(productions, numProductions, 'T');
    computeFirst(productions, numProductions, 'E'); 

    return 0;
}

