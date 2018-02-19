#include <stdio.h>
#include <string.h>
#include "wordsearch.h"


int main() {
    char puzzle[50][50] = {{ ' ' }};
    char words[50] = { ' ' };
    populateWordArray(puzzle, words);
    printArray(puzzle);
    return 0;
}

void populateWordArray(char wordArray[50][50], char words[50]) {
    char string[100];
    int counter = 0;
    int wordCounter = 0;
    int index;
    int i;
    while(fgets(string, sizeof(string), stdin)) {
        if (string[1] == ' ') {
            double lineSize = strlen(string);
            index = 0;
            for (i = 0; i < lineSize; i++) {
                /* we don't want to store the whitespace */
                if (string[i] == ' ') {
                    continue;
                /* if it's a null byte, the string has ended */
                } else if (string[i] == '\0') {
                    break;
                } else {
                    wordArray[counter][index] = string[i];
                    index++;
                }
            }
            counter++;
        } else {
            words[wordCounter] = (char) string;
        }
    }
}

void printArray(char array[50][50]) {
    int row,col;
    for (row = 0; row < 50; row++) {
        /* row contains no data */
        if (array[row][0] == '\0') {
            continue;
        }
        for (col = 0; col < 50; col++) {
            /* if it's a null byte, we've reached the end of the values here */
            if (array[row][col] != '\0') {
                /* if it's a newline character, don't print whitespace after it */
                if (array[row][col] == '\n') {
                    printf("\n");
                    break;
                }
                printf("%c ", array[row][col]);
            } else {
                break;
            }
        }
    }
}

void printWords(char words[50]) {
    int i = 0;
    for (i = 0; i < sizeof(words); i++) {
       printf(words[i]);
    }
}

