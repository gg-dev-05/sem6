/*
    190001016
    Garvit Galgat
    program to test whether a given identifier is valid or not.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "helper.h"

int main() {
    char inputFileName[80] = "input.txt";

    // open input file in read mode
    FILE* filePtr = fopen(inputFileName, "r");

    // file does not exist
    if (filePtr == NULL) {
        printf("%s does not exist\n", inputFileName);
        return 0;
    }

    char string[100];
    fscanf(filePtr, "%s", string);

    if (isKeyword(string)) {
        printf("%s is a keyword and thus not an identifier\n", string);
        return 0;
    } else {
        int first_char = 1;

        // reset file ptr
        filePtr = fopen(inputFileName, "r");

        int character;
        while ((character = fgetc(filePtr)) != EOF) {
            // first character can have an _ or any alpha
            if (first_char && !(character == '_' || isalpha(character))) {
                printf("%s contains invalid identifiers\n", inputFileName);
                return 0;
            }

            // further characters can have alpha-numeric value or an _
            if (!isalnum(character) && character != '_') {
                printf("%s contains invalid identifiers\n", inputFileName);
                return 0;
            }

            // set as not first character
            if (first_char) first_char = 0;
        }
        printf("%s contains valid identifiers\n", inputFileName);
    }

    // close input file
    fclose(filePtr);

    return 0;
}