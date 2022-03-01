/*
    190001016
    Garvit Galgat
    C program to count number of spaces and number of lines and number
    of characters used in a string or file given by a user.
*/

#include <stdio.h>

int main() {
    int total_characters = 0, total_lines = 0, total_spaces = 0;

    char inputFileName[80] = "input.txt";
    // open input file
    FILE *filePtr = fopen(inputFileName, "r");

    // file does not exist
    if (filePtr == NULL) {
        printf("%s does not exist\n", inputFileName);
    } else {
        int character;
        // iterate through characters
        while ((character = fgetc(filePtr)) != EOF) {
            total_characters++;
            if (character == ' ')
                total_spaces++;
            if (character == '\n')
                total_lines++;
        }
        fclose(filePtr);

        printf("Total Number of characters = %d\n", total_characters);
        printf("Total Number of spaces = %d\n", total_spaces);
        printf("Total Number of lines = %d\n", total_lines + 1);
    }
    return 0;
}