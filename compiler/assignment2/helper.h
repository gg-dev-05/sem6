/*
    190001016
    Garvit Galgat
    Helper file for functions in assignment2
*/

int isKeyword(char* str) {
    // List of all possible keywords available in C
    char listOfKeywords[32][10] = {
        "auto", "double", "int", "struct", "break", "else", "long", "switch", "case", "enum", "register", "typedef", "char", "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed", "void", "default", "goto", "sizeof", "voltile", "do", "if", "static", "while"};

    for (int i = 0; i < 32; i++) {
        // check if the string matches any of the possible keywords
        if (strcmp(listOfKeywords[i], str) == 0) {
            return 1;
        }
    }
    return 0;
}

int isIdentifier(char* str) {
    // NULL check
    if (!str) return 0;

    // first char should be _ or alphabet
    if (!(str[0] == '_' || isalpha(str[0])))
        return 0;

    for (int i = 1; i < strlen(str); i++) {
        // should be alpha-numeric or _
        if (!isalnum(str[i]) && str[i] != '_') return 0;
    }

    return 1;
}

int isOperator(char* ch) {
    if (ch[0] == '+' || ch[0] == '-' || ch[0] == '*' || ch[0] == '/' || ch[0] == '>' || ch[0] == '<' || ch[0] == '=')
        return 1;
    return 0;
}