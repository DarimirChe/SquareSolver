#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "solvers.h"
#include "utilits.h"

#define MAX_LEN_COUNT_SOLUTION_VALUE 50
#define STRINGIFY(X) XSTR(X)
#define XSTR(X) #X

enum ScanDataStatusCode {
    OK             = 1,
    INCORRECT_PATH = 2,
    INCORRECT_DATA = 3,
    ERROR_NULL_PTR = 4
};

enum TestStatus {
    FAILED = 0,
    PASSED = 1
};

const int MAX_LEN_FILENAME           = 50;
const int MAX_LEN_COUNT_SOLUTION_STR = MAX_LEN_COUNT_SOLUTION_VALUE;

struct DataTest {
    double b;
    double c;
    enum CountSolution currentCountSolution;
    double currentX;
};

struct ScanDataStatus {
    enum ScanDataStatusCode code;
    int numberLine;
    char filename[MAX_LEN_FILENAME];
};

void            runTests       (struct DataTest tests[], int countTests);
enum TestStatus testSolveLinear(double b, double c, enum CountSolution correctReturn, double correctX);

void printIncorrectReturn(double b, double c, enum CountSolution currentReturn, enum CountSolution correctReturn);
void printIncorrectX     (double b, double c, double currentX, double correctX);
void printScanDataError  (struct ScanDataStatus status);
void printHelp();

struct ScanDataStatus scanDataTest(struct DataTest* tests, int countTests, char* filename);

void parseArgv(int argc, char* argv[], char* filename, int* countTests);

const char*        countSolutionToString(enum CountSolution countSolution);
enum CountSolution stringToCountSolution(char* inputString);

int main(int argc, char* argv[]) {
    char filename[MAX_LEN_FILENAME] = {};
    int countTests = 0;

    parseArgv(argc, argv, filename, &countTests);

    struct DataTest* tests = (struct DataTest*) calloc(countTests, sizeof(struct DataTest)); 
    assert(tests != NULL);

    struct ScanDataStatus status = scanDataTest(tests, countTests, filename);

    if (status.code != OK) {
        printScanDataError(status);
        return 0;
    }

    runTests(tests, countTests);

    free(tests);
    return 0;
}

/* Handles console line flags. */
void parseArgv(int argc, char* argv[], char* filename, int* countTests) {
    for (int argNum = 1; argNum < argc; argNum++) 
    {
        if (!strncmp(argv[argNum], "--file", strlen("--file") + 1)) {
            strncpy(filename, argv[++argNum], MAX_LEN_FILENAME); 

        } else if (!strncmp(argv[argNum], "--count",  strlen("--count") + 1)) {
            *countTests = strtol(argv[++argNum], NULL, 10); // 10 = numeral system

        } else if (!strncmp(argv[argNum], "--help", strlen("--help") + 1)) {
            printHelp();
        }
    }
}

/* Displays help by flags. */
void printHelp() {
    printf("--file <path to the file>\n");
    printf("--count <number of tests>\n");
    printf("--help prints help\n");
}

/* Runs all tests from struct DataTest tests. */
void runTests(struct DataTest tests[], int countTests) {
    for (int testNumber = 0; testNumber < countTests; testNumber++) {
        printf("Test %d processing...\n", testNumber + 1);

        if (testSolveLinear(tests[testNumber].b, tests[testNumber].c, tests[testNumber].currentCountSolution, tests[testNumber].currentX) == PASSED) {
            printf("Test %d passed.\n", testNumber + 1);
        }
        printf("\n");
    }
}

/* Tests the solveLinear() function, accepts coefficients b, c of the equation of the form: bx + c = 0, 
the correct return and x for these coefficients. */
enum TestStatus testSolveLinear(double b, double c, enum CountSolution correctCountSolution, double correctX) {
    double currentX = 0;
    enum CountSolution currentCountSolution = solveLinear(b, c, &currentX);

    if (currentCountSolution != correctCountSolution) {
        printIncorrectReturn(b, c, currentCountSolution, correctCountSolution); // TODO rename func
        return FAILED;
    }

    if (!isEqual(currentX, correctX, PRECISION)) {
        printIncorrectX(b, c, currentX, correctX);
        return FAILED;
    }
    return PASSED;
}

/* Prints the test summary if the return is incorrect. */
void printIncorrectReturn(double b, double c, enum CountSolution currentCountSolution, enum CountSolution correctCountSolution) {
    printf("Incorrect return.\n");
    printf("Input: b = %lg, c = %lg\n", b, c);
    printf("Current return: %s\n", countSolutionToString(currentCountSolution));
    printf("Correct return: %s\n", countSolutionToString(correctCountSolution));
}

/* Prints the test summary if the x is incorrect. */
void printIncorrectX(double b, double c, double currentX, double correctX) {
    printf("Incorrect x.\n");
    printf("Input: b = %lg, c = %lg\n", b, c);
    printf("Current x: %lg\n", currentX);
    printf("Correct x: %lg\n", correctX);
}

/* Displays errors when scanning a test file. */
void printScanDataError(struct ScanDataStatus status) {
    switch (status.code)
    {
    case INCORRECT_PATH:
        printf("Error. The file could not be opened. Check that the file path is correct.\n");
        break;
    case INCORRECT_DATA:
        printf("Error. Incorrect data in %s %d line\n", status.filename, status.numberLine);
        break;
    case ERROR_NULL_POINTER:
        printf("Error. Null ptr\n");
        break;
    case OK:
    default:
        break;
    }
}

/* Returns the string value of the enum countSolution header. */
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

/* Returns the value of enum countSolution from the string. */
enum CountSolution stringToCountSolution(char* inputString) {
    if (inputString == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (!strncmp(inputString, "NO_SOLUTION", MAX_LEN_COUNT_SOLUTION_STR)) {
        return NO_SOLUTION;
    } else if (!strncmp(inputString, "ONE_SOLUTION", MAX_LEN_COUNT_SOLUTION_STR)) {
        return ONE_SOLUTION;
    } else if (!strncmp(inputString, "INFINITY_SOLUTIONS", MAX_LEN_COUNT_SOLUTION_STR)) {
        return INFINITY_SOLUTIONS;
    }
    return ERROR_NULL_POINTER;
}

/* Reads test data from a file. */
struct ScanDataStatus scanDataTest(struct DataTest* tests, int countTests, char* filename) {
    struct ScanDataStatus status;

    if (tests == NULL || filename == NULL) {
        status.code = ERROR_NULL_PTR;
        return status;
    }

    char tempStr[MAX_LEN_COUNT_SOLUTION_STR] = {};

    FILE* testsFile = fopen(filename, "r");

    if (testsFile == NULL) {
        status.code = INCORRECT_PATH;
        return status;
    } 

    for (int lineCnt = 0; lineCnt < countTests; lineCnt++) {
        fscanf(testsFile, "%lg %lg %" STRINGIFY(MAX_LEN_COUNT_SOLUTION_VALUE) "s %lg", 
            &tests[lineCnt].b, 
            &tests[lineCnt].c, 
            tempStr, 
            &tests[lineCnt].currentX
        );

        tests[lineCnt].currentCountSolution = stringToCountSolution(tempStr);

        if (tests[lineCnt].currentCountSolution == ERROR_NULL_POINTER) {
            status.code = INCORRECT_DATA;
            status.numberLine = lineCnt + 1;
            strncpy(status.filename, filename, MAX_LEN_FILENAME);
            return status;
        }
    }

    fclose(testsFile);
    status.code = OK;
    return status;
}
