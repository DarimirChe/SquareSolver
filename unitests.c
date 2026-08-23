#include <stdio.h>
#include <string.h>

#include "solvers.h"
#include "utilits.h"

#define MAX_LEN_COUNT_SOLUTION_VALUE 50
#define STRINGIFY(X) XSTR(X)
#define XSTR(X) #X


enum ScanDataStatusCode {
    OK = 1,
    INCORRECT_PATH,
    INCORRECT_DATA,
    ERROR_NULL_PTR
};

enum TestStatus {
    FAILED = 0,
    PASSED
};

const int COUNT_TESTS = 9;
const int MAX_LEN_FILENAME = 50;
const int MAX_LEN_COUNT_SOLUTION_STR = MAX_LEN_COUNT_SOLUTION_VALUE;

const char FILENAME[MAX_LEN_FILENAME] = "tests.txt";

struct DataTest {
    double b;
    double c;
    enum CountSolution currentCountSolution;
    double currentX;
};

struct ScanDataStatus {
    enum ScanDataStatusCode status;
    int numberLine;
};

void runTests(struct DataTest tests[]);
enum TestStatus testSolveLinear(double b, double c, enum CountSolution correctReturn, double correctX);

void printIncorrectReturn(double b, double c, enum CountSolution currentReturn, enum CountSolution correctReturn);
void printIncorrectX(double b, double c, double currentX, double correctX);
void printScanDataError(struct ScanDataStatus status);

struct ScanDataStatus scanDataTest(struct DataTest* tests);

const char* countSolutionToString(enum CountSolution countSolution);
enum CountSolution stringToCountSolution(char* inputString);

int main() {
    struct DataTest tests[COUNT_TESTS]; 
    
    struct ScanDataStatus status = scanDataTest(tests);
    
    if (status.status != OK) {
        printScanDataError(status);
        return 0;
    }

    runTests(tests);
    return 0;
}

/* Runs all tests from struct DataTest tests */
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
enum TestStatus testSolveLinear(double b, double c, enum CountSolution correctCountSolution, double correctX) {
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

void printScanDataError(struct ScanDataStatus status) {
    switch (status.status)
    {
    case INCORRECT_PATH:
        printf("Error. The file could not be opened. Check that the file path is correct.\n");
        break;
    case INCORRECT_DATA:
        printf("Error. Incorrect data in %s %d line\n", FILENAME, status.numberLine);
        break;
    case ERROR_NULL_POINTER:
        printf("Error. Null ptr\n");
        break;
    case OK:
    default:
        break;
    }
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

/* Returns the value of enum countSolution from the string */
enum CountSolution stringToCountSolution(char* inputString) {
    if (!strncmp(inputString, "NO_SOLUTION", MAX_LEN_COUNT_SOLUTION_STR)) {
        return NO_SOLUTION;
    } else if (!strncmp(inputString, "ONE_SOLUTION", MAX_LEN_COUNT_SOLUTION_STR)) {
        return ONE_SOLUTION;
    } else if (!strncmp(inputString, "INFINITY_SOLUTIONS", MAX_LEN_COUNT_SOLUTION_STR)) {
        return INFINITY_SOLUTIONS;
    }
    return ERROR_NULL_POINTER;
}

/* reads test data from a file */
struct ScanDataStatus scanDataTest(struct DataTest* tests) {
    struct ScanDataStatus status;
    if (tests == NULL) {
        status.status = ERROR_NULL_PTR;
        return status;
    }

    char tempStr[MAX_LEN_COUNT_SOLUTION_STR] = {};

    FILE* testsFile = fopen(FILENAME, "r");

    if (testsFile == NULL) {
        status.status = INCORRECT_PATH;
        return status;
    }

    for (int lineCnt = 0; lineCnt < COUNT_TESTS; lineCnt++) {
        fscanf(testsFile, "%lg %lg %" STRINGIFY(MAX_LEN_COUNT_SOLUTION_VALUE) "s %lg", 
            &tests[lineCnt].b, 
            &tests[lineCnt].c, 
            tempStr, 
            &tests[lineCnt].currentX
        );

        tests[lineCnt].currentCountSolution = stringToCountSolution(tempStr);
    
        if (tests[lineCnt].currentCountSolution == ERROR_NULL_POINTER) {
            status.status = INCORRECT_DATA;
            status.numberLine = lineCnt + 1;
            return status;
        }
    }

    fclose(testsFile);
    status.status = OK;
    return status;
}
