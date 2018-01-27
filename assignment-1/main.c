#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getRandom(int max);
char getRandomOperation();
long int getDigit();
long int getProblemCountInput();
long int getDifficultyLevelInput();
typedef struct DifficultyLevel {
    long int difficultyLevel;
    int min;
    int max;
} DifficultyLevel;
int generate_question(struct DifficultyLevel, int questionNumber);
struct DifficultyLevel getDifficultyLevel(long int difficulty);


int main() {
    long int problems = getProblemCountInput();
    long int difficulty = getDifficultyLevelInput();
    struct DifficultyLevel difficultyLevel = getDifficultyLevel(difficulty);
    int i;
    for (i =1; i < problems; i++) {
        int answer = generate_question(difficultyLevel, i);
    }

    exit(0);
}

char getRandomOperation() {
    int random = getRandom(3);
    switch (random) {
        case 0:
            return '+';
        case 1:
            return '-';
        case 2:
            return '*';
        case 3:
            return '/';
        default:
            printf("ERROR: Reached impossible operation type!\n");
            exit(1);
    }
}

int generate_question(struct DifficultyLevel difficultyLevel, int questionNumber) {
    int operand1 = getRandom(difficultyLevel.max);
    int operand2 = getRandom(difficultyLevel.max);

    char operation = getRandomOperation();
    printf("Question %d: %d %c %d\n", questionNumber, operand1, operation, operand2);
}

struct DifficultyLevel getDifficultyLevel(long int difficulty) {
    struct DifficultyLevel difficultyLevel;
    difficultyLevel.difficultyLevel = difficulty;
    switch (difficulty) {
        case 1:
            difficultyLevel.min = 1;
            difficultyLevel.max = 10;
            break;
        case 2:
            difficultyLevel.min = 1;
            difficultyLevel.max = 50;
            break;
        case 3:
            difficultyLevel.min = 1;
            difficultyLevel.max = 100;
            break;
        case 4:
            difficultyLevel.min = -100;
            difficultyLevel.max = 100;
            break;
        default:
            printf("ERROR: Reached impossible difficulty level!\n");
            exit(1);
    }
    return difficultyLevel;
}

int getRandom(int max) {
  /* seed the random number generator */
  srand(time(NULL));
  return srand() % max;
}

long int getProblemCountInput() {
    long int problems;
    while (1) {
        printf("Please enter the number of problems you would like to answer (1-20): ");
        problems = getDigit();
        if (problems > 0 && problems < 21) {
            break;
        }
    }
    return problems;
}

long int getDifficultyLevelInput() {
    long int difficulty;
    while (1) {
        printf("Select difficulty (1-4): ");
        difficulty = getDigit();
        if (difficulty > 0 && difficulty < 5) {
            break;
        }
    }
    return difficulty;
}

long int getDigit() {
    /*
     * The size of this buffer is admittedly an arbitrary number.  It the size is too small, strange things begin to
     * happen, so it's clearly important.
     */
    char buf[4096];
    char *p;
    long int i;

    /* fgets needs a character buffer, the maximum number of characters to read (probably the size of the previous
     * buffer), and the stream to read from, which in this case is stdin.  fgets returns null on failure, so we
     * want to make sure we don't have that. */
    if (fgets(buf, sizeof(buf), stdin) != NULL) {
        /*
         * we give strtol the buffer we read using fgets,a pointer that becomes a pointer to the last character in
         * the array, and the base.  we are using base 10.
         */
        i = strtol(buf, &p, 10);
        /* if the buffer begins with a newline, or ends with a newline or null byte, we don't want it.  thus,
         * we return an obvious invalid input (within the scope of this program) if any of the above is found.
         */
        if (buf[0] != '\n' && (*p == '\n' || *p == '\0')) {
            return i;
        } else {
            return -999;
        }
    }
}
