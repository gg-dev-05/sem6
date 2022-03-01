// 190001016
// Garvit Galgat
// program to check if a given string is a keyword

#include <iostream>   // for I/O operations
#include <vector>     // for storing all keywords
#include <algorithm>  // for converting input string to lowercase

int main() {
    // vector of string to store all possible (32) keywords
    std::vector<std::string> keywords = {
        "auto",
        "break",
        "case",
        "char",
        "const",
        "continue",
        "default",
        "do",
        "double",
        "else",
        "enum",
        "extern",
        "float",
        "for",
        "goto",
        "if",
        "int",
        "long",
        "register",
        "return",
        "short",
        "signed",
        "sizeof",
        "static",
        "struct",
        "switch",
        "typedef",
        "union",
        "unsigned",
        "void",
        "volatile",
        "while"};

    std::cout << "Enter Input String: ";
    std::string input;
    std::cin >> input;

    // converting input string to lower case
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);

    // boolean for is keyword
    bool isKeyword = false;

    // linearly checking if the input string is present in vector of keywords
    for (auto i : keywords) {
        if (input == i) {
            isKeyword = true;
            break;
        }
    }

    if (isKeyword) {
        std::cout << input << " is a keyword\n";
    } else {
        std::cout << input << " is not a keyword\n";
    }

    return 0;
}