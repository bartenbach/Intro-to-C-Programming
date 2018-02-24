#include <stdio.h>
#include <string.h>
#include "wordsearch.h"

int main() {
    char puzzle[100][100] = {{ ' ' }};
    char solution[100][100] = {{ ' ' }};
    char words[100][100];
    int wordCount = populateWordArray(puzzle, words);
    int puzzleLength;
    populateSolutionArray(solution);
    findSolution(puzzle, words, solution, wordCount);
    puzzleLength = getPuzzleLength(puzzle);
    printArray(solution, puzzleLength);
    return 0;
}

int getPuzzleLength(char puzzle[100][100]) {
    int i;
    for (i = 0; i < 100; i++) {
        if (puzzle[0][i] == ' ' || puzzle[0][i] == '\0') {
            return i;
        }
    }
    return 999;
}

void populateSolutionArray(char pString[100][100]) {
    int i,j;
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
            if (j == 49) {
                pString[i][j] = '\n';
            } else {
                pString[i][j] = ' ';
            }
        }
    }
}

int populateWordArray(char wordArray[100][100], char words[100][100]) {
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
                    wordArray[counter][index] = '\0';
                    break;
                } else {
                    wordArray[counter][index] = string[i];
                    index++;
                }
            }
            counter++;
        } else {
            strcpy(words[wordCounter], string);
            wordCounter++;
        }
    }
    return wordCounter;
}

void printArray(char array[100][100], int length) {
    int row,col;
    for (row = 0; row < length; row++) {
        /* row contains no data */
        if (array[row][0] == '\0') {
            continue;
        }
        for (col = 0; col < 100; col++) {
            if (array[row][col] != ' ' && array[row][col] != '\n') {
                printRow(array, row, length);
                break;
            }

        }
    }
}

void printRow(char array[100][100], int row, int colSize) {
    int col;
    for (col = 0; col < colSize - 1; col++) {
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
    printf("\n");
}

void findSolution(char puzzle[100][100], char words[100][100], char solution[100][100], int wordCount) {
    int row, col;
    for (row = 0; row < 51; row++) {
        /* row is empty */
        if (puzzle[row][0] == '\0') {
            continue;
        }
        for (col = 0; col < 51; col++) {
            if (puzzle[row][col] == '\0' || puzzle[row][col] == '\n') {
                break;
            } else {
                checkStartingPoint(puzzle, row, col, words, solution, wordCount);
            }
        }
    }
}

void checkStartingPoint(char puzzle[100][100], int row, int col, char words[100][100], char solution[100][100], int wordCount) {
    int i = 0;
    /* end of row */
        for (i=0; i < wordCount; i++) {
            if (puzzle[row][col] == words[i][0]) {
                checkForwards(puzzle, words[i], row, col, solution);
                checkBackwards(puzzle, words[i], row, col, solution);
                checkDown(puzzle, words[i], row, col, solution);
                checkUp(puzzle, words[i], row, col, solution);
                checkUpRight(puzzle, words[i], row, col, solution);
                checkUpLeft(puzzle, words[i], row, col, solution);
                checkDownRight(puzzle, words[i], row, col, solution);
                checkDownLeft(puzzle, words[i], row, col, solution);
            }
        }

}

/* verified */
int checkUpLeft(char puzzle[100][100], char word[100], int row, int col, char solution[100][100]) {
    int i;
    struct Coordinate startingPoint;
    struct Coordinate coordinates[100];
    startingPoint.x = row;
    startingPoint.y = col;
    coordinates[0] = startingPoint;
    for (i = 1; i < 100; i++) {
        if (puzzle[row-i][col-i] == word[i]) {
            coordinates[i].x = row-i;
            coordinates[i].y = col-i;
            if (word[i+1] == '\n') {
                copyCoordinates(puzzle, coordinates, solution, (int) strlen(word+1));
                return 1;
            }
        } else {
            break;
        }
    }
    return 0;
}

int checkDownRight(char puzzle[100][100], char word[100], int row, int col, char solution[100][100]) {
    int i;
    struct Coordinate startingPoint;
    struct Coordinate coordinates[100];
    startingPoint.x = row;
    startingPoint.y = col;
    coordinates[0] = startingPoint;
    for (i = 1; i < 100; i++) {
        if (puzzle[row+i][col+i] == '\0' || puzzle[row+i][col+i] == '\n') {
            return 0;
        }
        if (puzzle[row+i][col+i] == word[i]) {
            coordinates[i].x = row+i;
            coordinates[i].y = col+i;
            if (word[i+1] == '\n') {
                copyCoordinates(puzzle, coordinates, solution, (int) strlen(word+1));
                return 1;
            }
        } else {
            break;
        }
    }
    return 0;
}

int checkDownLeft(char puzzle[100][100], char word[100], int row, int col, char solution[100][100]) {
    int i;
    struct Coordinate startingPoint;
    struct Coordinate coordinates[100];
    startingPoint.x = row;
    startingPoint.y = col;
    coordinates[0] = startingPoint;
    for (i = 1; i < 100; i++) {
        if (puzzle[row+i][col-i] == '\0' || puzzle[row+i][col-i] == '\n') {
            return 0;
        }
        if (puzzle[row+i][col-i] == word[i]) {
            coordinates[i].x = row+i;
            coordinates[i].y = col-i;
            if (word[i+1] == '\n') {
                copyCoordinates(puzzle, coordinates, solution, (int) strlen(word+1));
                return 1;
            }
        } else {
            break;
        }
    }
    return 0;
}

int checkUpRight(char puzzle[100][100], char word[100], int row, int col, char solution[100][100]) {
    int i;
    struct Coordinate startingPoint;
    struct Coordinate coordinates[100];
    startingPoint.x = row;
    startingPoint.y = col;
    coordinates[0] = startingPoint;
    for (i = 1; i < 100; i++) {
        if (puzzle[row-i][col+i] == '\0' || puzzle[row-i][col+i] == '\n') {
            return 0;
        }
        if (puzzle[row-i][col+i] == word[i]) {
            coordinates[i].x = row-i;
            coordinates[i].y = col+i;
            if (word[i+1] == '\n') {
                copyCoordinates(puzzle, coordinates, solution, (int) strlen(word+1));
                return 1;
            }
        } else {
            break;
        }
    }
    return 0;
}

int checkBackwards(char puzzle[100][100], char word[100], int row, int col, char solution[100][100]) {
    int i;
    struct Coordinate startingPoint;
    struct Coordinate coordinates[100];
    startingPoint.x = row;
    startingPoint.y = col;
    coordinates[0] = startingPoint;
    for (i = 1; i < 100; i++) {
        if (puzzle[row][col-i] == '\0' || puzzle[row][col-i] == '\n') {
            return 0;
        }
        if (puzzle[row][col-i] == word[i]) {
            coordinates[i].x = row;
            coordinates[i].y = col-i;
            if (word[i+1] == '\n') {
                copyCoordinates(puzzle, coordinates, solution, (int) strlen(word+1));
                return 1;
            }
        } else {
            break;
        }
    }
    return 0;
}


int checkDown(char puzzle[100][100], char word[100], int row, int col, char solution[100][100]) {
    int i;
    struct Coordinate startingPoint;
    struct Coordinate coordinates[100];
    startingPoint.x = row;
    startingPoint.y = col;
    coordinates[0] = startingPoint;
    for (i = 1; i < 100; i++) {
        if (puzzle[row+i][col] == ' ') { /* end of puzzle */
            return 0;
        }
        if (puzzle[row+i][col] == word[i]) {
            coordinates[i].x = row+i;
            coordinates[i].y = col;
            if (word[i+1] == '\n') {
                copyCoordinates(puzzle, coordinates, solution, (int) strlen(word+1));
                return 1;
            }
        } else {
            break;
        }
    }
    return 0;
}

int checkUp(char puzzle[100][100], char word[100], int row, int col, char solution[100][100]) {
    int i;
    struct Coordinate startingPoint;
    struct Coordinate coordinates[100];
    startingPoint.x = row;
    startingPoint.y = col;
    coordinates[0] = startingPoint;
    for (i = 1; i < 100; i++) {
        /*if (puzzle[row-1][col] == '\0' || puzzle[row][col] == '\n') {
            return 0;
        }*/
        if (puzzle[row-i][col] == word[i]) {
            coordinates[i].x = row-i;
            coordinates[i].y = col;
            if (word[i+1] == '\n') {
                copyCoordinates(puzzle, coordinates, solution, (int) strlen(word+1));
                return 1;
            }
        } else {
            break;
        }
    }
    return 0;
}


int checkForwards(char puzzle[100][100], char word[100], int row, int col, char solution[100][100]) {
    int i;
    struct Coordinate startingPoint;
    struct Coordinate coordinates[100];
    startingPoint.x = row;
    startingPoint.y = col;
    coordinates[0] = startingPoint;
    for (i = 1; i < 100; i++) {
        if (puzzle[row][col+i] == '\0' || puzzle[row][col] == '\n') {
            return 0;
        }
        if (puzzle[row][col+i] == word[i]) {
            coordinates[i].x = row;
            coordinates[i].y = col+i;
            if (word[i+1] == '\n') {
                copyCoordinates(puzzle, coordinates, solution, (int) strlen(word+1));
                return 1;
            }
        } else {
            break;
        }
    }
    return 0;
}

void copyCoordinates(char puzzle[100][100], struct Coordinate coordinates[100], char solution[100][100], int length) {
    int i;
    for (i = 0; i < length; i++) {
        solution[coordinates[i].x][coordinates[i].y] = puzzle[coordinates[i].x][coordinates[i].y];
    }
}

void printWords(char words[100][100], int wordCount) {
    int i = 0;
    for (i = 0; i < wordCount; i++) {
        printf("%s", words[i]);
    }
}

