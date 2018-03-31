#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include "wordprocessor.h"


int main(int argc, char *argv[]) {
    FILE *inFile, *outFile, *wordsFile;
    int colSize;
    char *buffer = 0;
    char **token = 0;
    char *line;
    int i = 0;
    check_arguments(argc, argv);
    /* arguments are valid, put them into variables */
    colSize = (int) strtol(argv[1], NULL, 10);
    buffer = malloc(300);
    token = malloc(300);
    inFile = fopen(argv[2], "r");
    outFile = fopen(strcat(argv[2], ".out"), "w");
    wordsFile = fopen(strcat(argv[2], ".words"), "w");
    /* check for NULL files.. */
    if (inFile == NULL || outFile == NULL || wordsFile == NULL) {
        printf("ERROR: A file handle is NULL! Unable to get file handle!\n");
        exit(EXIT_FAILURE);
    }
    /* read in file */
    line = malloc(LINE_SIZE);
    while (fgets(line, LINE_SIZE, inFile) != NULL) {
        printf("LINE: %s\n", line);
        token[i] = strtok(line, " ");
        do {
            if (strcmp(token[i], "\n") != 0) {
                printf("token: %s\n", token[i]);
                if ((strlen(buffer) + strlen(token[i])) > colSize) {
                    printf("buffer is full...writing out...\n");
                    /* trim last whitespace and add newline */
                    buffer[strlen(buffer) - 1] = '\n';
                    fputs(buffer, outFile);
                    memset(buffer, '\0', sizeof(char));
                } else {
                    printf("buffer not full, at %d, copying token...\n", (int) strlen(buffer));
                }
                strcat(buffer, token[i]);
                strcat(buffer, " ");
            }
            i++;
            token[i] = strtok(NULL, " ");
        } while (token[i] != NULL);
        i = 0;
    }
    if (buffer[0] != '\0') {
        buffer[strlen(buffer) - 1] = '\n';
        fputs(buffer, outFile);
    }
    free(token);
    free(line);
    fclose(inFile);
    fclose(outFile);
    return EXIT_SUCCESS;
}

void check_arguments(int argc, char **argv) {
    /* validate arguments exist */
    int columnSize;
    if (argc != REQUIRED_ARGS) {
        printf("Usage: wordprocessor <column limit> <file>\n");
        exit(EXIT_FAILURE);
    }
    /* validate the column limit parameter */
    columnSize = (int) strtol(argv[1], NULL, 10);
    if (columnSize < MIN_COLSIZE || columnSize > MAX_COLSIZE) {
        printf("ERROR: Column limit of '%d' is unsupported! (Must be 25 <= limit <= 100)\n", columnSize);
        exit(EXIT_FAILURE);
    }
    /* verify the file passed in actually exists */
    if (access(argv[2], F_OK) != -1) {
        printf("You passed in %d arguments, and the column limit is: %s, filename: %s\n", argc, argv[1], argv[2]);
        return;
    } else {
        printf("ERROR: Specified file '%s' doesn't exist!\n", argv[2]);
        exit(EXIT_FAILURE);
    }
}