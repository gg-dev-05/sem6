/*
    190001016
    Garvit Galgat
    program to identify the tokens such as identifier, operator,
    and keyword of subroutine (string or file) given by a user.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "helper.h"

int main() {
    // open the file where our input resides
    char inputFileName[80] = "input.txt";

    // open input file in read mode
    FILE* filePtr = fopen(inputFileName, "r");

    // unable to open inputFile
    if (filePtr == NULL) {
        printf("Error opening input file\n");
        return 0;
    }

    char str[100];
    while (fscanf(filePtr, "%s", str) != EOF) {
        if (isKeyword(str)) {
            printf("%s is a Keyword\n", str);
        } else if (isIdentifier(str)) {
            printf("%s is an Identifier\n", str);
        } else if (isOperator(str)) {
            printf("%s is an Operator\n", str);
        } else {
            printf("%s invalid token\n", str);
        }
    }

    // close input file
    fclose(filePtr);

    return 0;
}