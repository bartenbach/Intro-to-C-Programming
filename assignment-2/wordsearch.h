#ifndef ASSIGNMENT_2_WORDSEARCH_H
#define ASSIGNMENT_2_WORDSEARCH_H

#endif

int populateWordArray(char[100][100], char[100][100]);
void printArray(char[100][100], int);
void printRow(char array[100][100], int, int);
void printWords(char[100][100], int);
void findSolution(char[100][100], char[100][100], char[100][100], int);
void checkStartingPoint(char[100][100], int, int, char[100][100], char[100][100], int);
int checkForwards(char puzzle[100][100], char word[100], int row, int col, char solution[100][100]);
int checkBackwards(char puzzle[100][100], char word[100], int row, int col, char solution[100][100]);
int checkDown(char puzzle[100][100], char word[100], int row, int col, char solution[100][100]);
int checkUp(char puzzle[100][100], char word[100], int row, int col, char solution[100][100]);
int checkUpRight(char puzzle[100][100], char word[100], int row, int col, char solution[100][100]);
int checkUpLeft(char puzzle[100][100], char word[100], int row, int col, char solution[100][100]);
int checkDownRight(char puzzle[100][100], char word[100], int row, int col, char solution[100][100]);
int checkDownLeft(char puzzle[100][100], char word[100], int row, int col, char solution[100][100]);
int getPuzzleLength(char puzzle[100][100]);
struct Coordinate {
    int x;
    int y;
};
void copyCoordinates(char puzzle[100][100], struct Coordinate coordinates[100], char solution[100][100], int length);
void populateSolutionArray(char pString[100][100]);
