#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getRandom(int min, int max);
char getRandomOperation();
long int getDigit();
long int getProblemCountInput();
long int getDifficultyLevelInput();
typedef struct DifficultyLevel {
    int min;
    int max;
} DifficultyLevel;
int generate_question(struct DifficultyLevel, int questionNumber);
int getActualAnswer(int operand1, int operand2, char operation);
struct DifficultyLevel getDifficultyLevel(long int difficulty);
int answer_question(int realAnswer);
void print_response(int isCorrect, int realAnswer);
void printPositiveFeedback(int random);
void printNegativeFeedback(int random, int realAnswer);
void generateReport(int correctAnswers, long int totalQuestions);

int main() {
    srand((unsigned int)time(NULL));
    long int problems = getProblemCountInput();
    long int difficulty = getDifficultyLevelInput();
    struct DifficultyLevel difficultyLevel = getDifficultyLevel(difficulty);
    int correctAnswers = 0;
    int i;
    for (i = 1; i < problems+1; i++) {
        int realAnswer = generate_question(difficultyLevel, i);
        int isCorrect = answer_question(realAnswer);
        if (isCorrect == 1) {
            correctAnswers++;
        }
        print_response(isCorrect, realAnswer);
    }
    generateReport(correctAnswers, problems);
    exit(0);
}

void generateReport(int correctAnswers, long int totalQuestions) {
    printf("=======================\n");
    printf("Your score was %d/%ld\n", correctAnswers, totalQuestions);
    printf("=======================\n");
}

char getRandomOperation() {
    int random = getRandom(1, 4);
    switch (random) {
        case 1:
            return '+';
        case 2:
            return '-';
        case 3:
            return '*';
        case 4:
            return '/';
        default:
            printf("ERROR: Reached impossible operation type!\n");
            exit(1);
    }
}

void print_response(int isCorrect, int realAnswer) {
    int random = getRandom(1, 3);
    if (isCorrect == 1) {
        printPositiveFeedback(random);
    } else {
        printNegativeFeedback(random, realAnswer);
    }
}

void printPositiveFeedback(int random) {
    switch (random) {
        case 1:
            printf("Great job!\n\n");
            break;
        case 2:
            printf("Good work!\n\n");
            break;
        case 3:
            printf("Fantastic!\n\n");
            break;
        default:
            printf("ERROR: Reached default in positive feedback switch!\n");
            exit(1);
    }
}

void printNegativeFeedback(int random, int realAnswer) {
    switch (random) {
        case 1:
            printf("Sorry, the correct answer was %d\n\n", realAnswer);
            break;
        case 2:
            printf("Better luck next time.  The answer was %d\n\n", realAnswer);
            break;
        case 3:
            printf("Whoops!  The correct answer was %d\n\n", realAnswer);
            break;
        default:
            printf("ERROR: Reached default in negative feedback switch!\n");
            exit(1);
    }
}

int generate_question(struct DifficultyLevel difficultyLevel, int questionNumber) {
    int operand1 = getRandom(difficultyLevel.min, difficultyLevel.max);
    int operand2 = getRandom(difficultyLevel.min, difficultyLevel.max);
    char operation = getRandomOperation();
    /* prevent from dividing by zero */
    while (operation == '/' && operand2 == 0) {
        operand2 = getRandom(difficultyLevel.min, difficultyLevel.max);
    }
    printf("Question %d: %d %c %d = ", questionNumber, operand1, operation, operand2);
    return getActualAnswer(operand1, operand2, operation);
}

int answer_question(int realAnswer) {
    long int userAnswer = getDigit();
    if (userAnswer == realAnswer) {
        return 1;
    }
    return 0;
}

int getActualAnswer(int operand1, int operand2, char operation) {
    switch (operation) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            return operand1 / operand2;
        default:
            printf("ERROR: Attempted to get answer with impossible operation type!\n");
            exit(1);
    }
}

struct DifficultyLevel getDifficultyLevel(long int difficulty) {
    struct DifficultyLevel difficultyLevel;
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

int getRandom(int min, int max) {
  return rand() % (max + 1 - min) + min;
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
