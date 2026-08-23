#include <stdio.h>
#include <string.h>

#include "solvers.h"
#include "utilits.h"

enum Errors {
    OK = 1,
    INCORRECT_PATH,
    INCORRECT_DATA,
    ERROR_NULL_PTR
};

enum Status {
    FAILED = 0,
    PASSED
};

struct DataTest {
    double b;
    double c;
    enum CountSolution currentCountSolution;
    double currentX;
};

const int COUNT_TESTS = 9;
const int MAX_LEN_FILENAME = 50;
const int MAX_LEN_TEMP_STR = 50;

const char FILENAME[MAX_LEN_FILENAME] = "tests.txt";

void runTests(struct DataTest tests[]);
enum Status testSolveLinear(double b, double c, enum CountSolution correctReturn, double correctX);

void printIncorrectReturn(double b, double c, enum CountSolution currentReturn, enum CountSolution correctReturn);
void printIncorrectX(double b, double c, double currentX, double correctX);

enum Errors scanDataTest(struct DataTest* tests);

const char* countSolutionToString(enum CountSolution countSolution);
enum CountSolution stringToCountSolution(char* inputString);

int main() {
    struct DataTest tests[COUNT_TESTS]; 

    enum Errors status = scanDataTest(tests);

    if (status == INCORRECT_PATH) {
        printf("Error. The file could not be opened. Check that the file path is correct.\n");
        return 0;
    }

    if (status == INCORRECT_DATA) {
        return 0;
    }

    if (status == ERROR_NULL_PTR) {
        printf("Error. Null ptr\n");
        return 0;
    }

    runTests(tests);

    return 0;
}

void runTests(struct DataTest tests[]) {
    for (int i = 0; i < COUNT_TESTS; i++) {
        printf("Test %d processing...\n", i + 1);

        if (testSolveLinear(tests[i].b, tests[i].c, tests[i].currentCountSolution, tests[i].currentX) == PASSED) {
            printf("Test %d passed.\n", i + 1);
        }
        printf("\n");
    }
}


/* Tests the solveLinear() function, accepts coefficients b, c of the equation of the form: bx + c = 0, 
the correct return and x for these coefficients */
enum Status testSolveLinear(double b, double c, enum CountSolution correctCountSolution, double correctX) {
    double currentX = 0;
    enum CountSolution currentCountSolution = solveLinear(b, c, &currentX);

    if (currentCountSolution != correctCountSolution) {
        printIncorrectReturn(b, c, currentCountSolution, correctCountSolution);
        return FAILED;
    }

    if (!compare(currentX, correctX, PRECISION)) {
        printIncorrectX(b, c, currentX, correctX);
        return FAILED;
    }
    return PASSED;
}

/* Prints the test summary if the return is incorrect */
void printIncorrectReturn(double b, double c, enum CountSolution currentCountSolution, enum CountSolution correctCountSolution) {
    printf("Incorrect return.\n");
    printf("Input: b = %lg, c = %lg\n", b, c);
    printf("Current return: %s\n", countSolutionToString(currentCountSolution));
    printf("Correct return: %s\n", countSolutionToString(correctCountSolution));
}

/* Prints the test summary if the x is incorrect */
void printIncorrectX(double b, double c, double currentX, double correctX) {
    printf("Incorrect x.\n");
    printf("Input: b = %lg, c = %lg\n", b, c);
    printf("Current x: %lg\n", currentX);
    printf("Correct x: %lg\n", correctX);
}

/* Returns the string value of the enum countSolution header */
const char* countSolutionToString(enum CountSolution countSolution) { 
    switch (countSolution)
    {
    case NO_SOLUTION:
        return "NO_SOLUTION";
        break;
    case ONE_SOLUTION:
        return "ONE_SOLUTION";
        break;
    case INFINITY_SOLUTIONS:
        return "INFINITY_SOLUTIONS";
        break;
    default:
        return "";
        break;
    }
}

enum CountSolution stringToCountSolution(char* inputString) {
    if (!strcmp(inputString, "NO_SOLUTION")) {
        return NO_SOLUTION;
    } else if (!strcmp(inputString, "ONE_SOLUTION")) {
        return ONE_SOLUTION;
    } else if (!strcmp(inputString, "INFINITY_SOLUTIONS")) {
        return INFINITY_SOLUTIONS;
    }
    return ERROR_NULL_POINTER;
}

enum Errors scanDataTest(struct DataTest* tests) {
    if (tests == NULL) {
        return ERROR_NULL_PTR;
    }

    char tempStr[MAX_LEN_TEMP_STR] = {};

    FILE* testsFile = fopen(FILENAME, "r");

    if (testsFile == NULL) {
        return INCORRECT_PATH;
    }

    for (int i = 0; i < COUNT_TESTS; i++) {
        fscanf(testsFile, "%lg %lg %s %lg", &tests[i].b, &tests[i].c, tempStr, &tests[i].currentX); //TODO: Needs to check защитить от переполнения буфера tempStr, а как?

        tests[i].currentCountSolution = stringToCountSolution(tempStr);
    
        if (tests[i].currentCountSolution == ERROR_NULL_POINTER) {
            printf("Error. Incorrect data in %s %d line\n", FILENAME, i + 1);
            return INCORRECT_DATA;
        }
    }

    fclose(testsFile);
    return OK;
}
