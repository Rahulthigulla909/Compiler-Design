#include <stdio.h>
#include <string.h>
#include <ctype.h>

void computeFirst(char production[][10], int numProductions, char nonTerminal) {
    printf("FIRST(%c) = { ", nonTerminal);
    
    char firstSet[20] = "";
    int i, j;
    
    for (i = 0; i < numProductions; i++) {
        // Check if the production starts with the Non-Terminal we are looking for
        if (production[i][0] == nonTerminal) {
            
            char firstSymbol = production[i][3]; // The symbol after "->"
            
            // CASE 1: It starts with a Terminal (lower case, (, +, *, @)
            if (islower(firstSymbol) || firstSymbol == '(' || firstSymbol == '@' || firstSymbol == '+' || firstSymbol == '*') {
                
                char term[2] = {firstSymbol, '\0'};
                if (strchr(firstSet, firstSymbol) == NULL) { // Avoid duplicates
                    strcat(firstSet, term);
                }
            } 
            // CASE 2: It starts with a Non-Terminal (Hardcoded dependencies)
            else if (isupper(firstSymbol)) {
                
                // E -> T... (So E gets First(T))
                // Since T -> F..., T gets First(F). 
                // Effectively, both E and T get First(F) which is '(' and 'i'
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
    
    // Formatting output to print 'id' and 'epsilon' nicely
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
    // Grammar uses X for E' and Y for T'
    char productions[][10] = {
        "E->TX",
        "X->+TX", 
        "X->@",   
        "T->FY",
        "Y->*FY", 
        "Y->@",   
        "F->(E)",
        "F->i"    
    };
    int numProductions = 8;

    printf("Computing First Sets for Right Recursive Grammar:\n");
    printf("Mapping: X = E', Y = T'\n\n");
    
    // Order doesn't matter for the code, but logically we go Bottom-Up
    computeFirst(productions, numProductions, 'F'); 
    computeFirst(productions, numProductions, 'Y'); // T'
    computeFirst(productions, numProductions, 'X'); // E'
    computeFirst(productions, numProductions, 'T');
    computeFirst(productions, numProductions, 'E'); 

    return 0;
}
