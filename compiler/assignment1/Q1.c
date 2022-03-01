// 190001016
// Garvit Galgat
// Program to count vowels and consonants of a given string.

#include <stdio.h>   // for I/O operations
#include <string.h>  // for strlen() function i.e to find length of input string
#include <ctype.h>   // for converting input chars to lower case

int main() {
    // creating input buffer
    char input[100];
    printf("Enter Input String: ");
    scanf("%s", input);
    printf("%s\n", input);

    // initialiazing length of input
    int lenOfInput = strlen(input);

    // creating an array of vowels
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};

    // total count of vowels
    int totalVowels = 0;

    // total count of non alphabatical characters
    int totalNonAlpha = 0;
    for (int i = 0; i < lenOfInput; i++) {
        // if character is not alphabet, move to next character
        if (!isalpha(input[i])) {
            totalNonAlpha++;
            continue;
        }

        // converting characters to lowercase
        input[i] = tolower(input[i]);

        // linearly checking if the character is a vowel
        for (int j = 0; j < 5; j++) {
            if (input[i] == vowels[j]) {
                totalVowels++;
                break;
            }
        }
    }

    // displaying total vowels and total consonants (size of string - total non alphabet characters - total vowels)
    printf("Total Vowels = %d\nTotal Consonants = %d\n", totalVowels, lenOfInput - totalNonAlpha - totalVowels);
}