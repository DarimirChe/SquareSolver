#include <stdio.h>
#include <string.h>

#include "solvers.h"
#include "utilits.h"

bool testSolveLinear(double b, double c, enum countSolution correctReturn, double correctX);

void printIncorrectReturn(double b, double c, enum countSolution currentReturn, enum countSolution correctReturn);
void printIncorrectX(double b, double c, double currentX, double correctX);

void scanDataTest(struct dataTest* tests);

const char* countSolutionToString(enum countSolution countSolution);
enum countSolution stringToCountSolution(char* inputString);

struct dataTest {
    double b;
    double c;
    enum countSolution currentCountSolution;
    double currentX;
};

const int COUNT_TESTS = 9;
const int MAX_LEN_FILENAME = 50;
const int MAX_LEN_TEMP_STR = 50;

const double precision = 1e-5;

const char FILENAME[MAX_LEN_FILENAME] = "tests.txt";

int main() {
    struct dataTest tests[COUNT_TESTS]; 

    scanDataTest(tests);

    for (int i = 0; i < COUNT_TESTS; i++) {
        printf("Test %d processing...\n", i + 1);
        if (testSolveLinear(tests[i].b, tests[i].c, tests[i].currentCountSolution, tests[i].currentX)) {
            printf("Test %d passed.\n", i + 1);
        }
        printf("\n");
    }
    return 0;
}

/* Tests the solveLinear() function, accepts coefficients b, c of the equation of the form: bx + c = 0, 
the correct return and x for these coefficients */
bool testSolveLinear(double b, double c, enum countSolution correctCountSolution, double correctX) {
    double currentX = 0;
    enum countSolution currentCountSolution = solveLinear(b, c, &currentX);

    if (currentCountSolution != correctCountSolution) {
        printIncorrectReturn(b, c, currentCountSolution, correctCountSolution);
        return false;
    } else if (compare(currentX, correctX, precision)) {
        printIncorrectX(b, c, currentX, correctX);
        return false;
    }
    return true;
}

/* Prints the test summary if the return is incorrect */
void printIncorrectReturn(double b, double c, enum countSolution currentCountSolution, enum countSolution correctCountSolution) {
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
const char* countSolutionToString(enum countSolution countSolution) { 
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

enum countSolution stringToCountSolution(char* inputString) {
    if (!strcmp(inputString, "NO_SOLUTION")) {
        return NO_SOLUTION;
    } else if (!strcmp(inputString, "ONE_SOLUTION")) {
        return ONE_SOLUTION;
    } else if (!strcmp(inputString, "INFINITY_SOLUTIONS")) {
        return INFINITY_SOLUTIONS;
    }
    return ERROR_NULL_POINTER;
}

void scanDataTest(struct dataTest* tests) {
    double b = 0, c = 0, currentX = 0;
    char tempStr[MAX_LEN_TEMP_STR] = {};

    FILE* testsFile = fopen(FILENAME, "r"); //TODO: Needs to check the null pointer

    for (int i = 0; i < COUNT_TESTS; i++) {
        fscanf(testsFile, "%lg %lg %s %lg", &b, &c, tempStr, &currentX); //TODO: Needs to check
        tests[i].b = b;
        tests[i].c = c;
        tests[i].currentCountSolution = stringToCountSolution(tempStr);
        tests[i].currentX = currentX;

        if (tests[i].currentCountSolution == ERROR_NULL_POINTER) {
            printf("Error. Incorrect data in %s %d line\n", FILENAME, i + 1);
        }
    }

    fclose(testsFile);
}