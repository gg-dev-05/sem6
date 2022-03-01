// 190001016
// Garvit Galgat
// program to check if a given string is a comment

#include <stdio.h>   // for I/O operations
#include <string.h>  // for strlen() function i.e to find length of input string
#include <ctype.h>   // for converting input chars to lower case

int main() {
    // input string buffer
    char input[100];
    printf("Enter Input String: ");
    scanf("%s", input);

    int lenOfInput = strlen(input);

    int isComment = 0;
    for (int i = 0; i < lenOfInput; i++) {
        // ignoring all beginning whitespaces
        if (input[i] == ' ') {
            continue;
        }
        // checking if a // is present
        if (input[i] == '/' && i != lenOfInput - 1 && input[i + 1] == '/') {
            isComment = 1;
            break;
        }

        // checking if a /* is present (comment opening)
        if (input[i] == '/' && i != lenOfInput - 1 && input[i + 1] == '*') {
            // checking if a */ is present from ending of the string (comment closing)
            for (int j = lenOfInput - 1; j >= 0; j--) {
                if (input[j] == ' ') {
                    continue;
                }
                if (input[j] == '/' && j != 0 && input[j - 1] == '*' && j - 2 != i) {
                    isComment = 1;
                    break;
                }
            }

            // comment is closed thus break
            if (isComment) break;

            // comment is not closed thus continue in loop
        }
    }

    if (isComment)
        printf("The given input string is a comment!\n");
    else
        printf("The given input string is NOT a comment!\n");
}