#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getRandom();
long int getDigit();
long int getProblemCount();
long int getDifficultyLevel();

int main() {
    long int problems = getProblemCount();
    long int difficulty = getDifficultyLevel();

    exit(0);
}

int getRandom() {
  /* seed the random number generator */
  srand(time(NULL));
  return rand() % 100;
}

long int getProblemCount() {
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

long int getDifficultyLevel() {
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
