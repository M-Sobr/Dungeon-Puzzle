#include "Utils.h"

bool isBlank(char ch) {
    switch (ch) {
        case ' ':
        case '\n':
            return 1;
        default:
            return 0;    
    }
}

bool equalsIgnoreCase(char char1, char char2) {
    if (('a' <= char1) && (char1 <= 'z')) {
        char1 -= 32;
    }
    if (('a' <= char2) && (char2 <= 'z')) {
        char2 -= 32;
    }
    return char1 == char2;
}

bool equalsIgnoreCase(const char text1[], const char text2[], int charCount) {
    for (int i=0; i<charCount; i++) {
        if (!equalsIgnoreCase(text1[i], text2[i])) {
            return false;
        }
    }
    return true;
}