#include <stdio.h>
#include <stdlib.h>

#include "test_solveq.h"
#include "solvers.h"
#include "utilits.h"

/* Runs all the tests. */
int runTests() {
    struct TestCase tests[NUMBER_TESTS] = {};
    
    struct ScanFileTestsStatus status = scanFileTests(tests);

    if (status.code != OK) {
        printScanFileTestsError(status);
    }

    for (int testNumber = 0; testNumber < NUMBER_TESTS; testNumber++) {
        printf("Test %d/%d processing...\n", testNumber + 1, NUMBER_TESTS);
        if(runTest(tests[testNumber]) == PASSED) {
            printf("Passed\n");
        }
        printf("\n");
    }
    return 0;
}

/* Runs one test. */
enum RunTestStatus runTest(struct TestCase test) {
    double currentX1 = 0, currentX2 = 0;
    enum CountSolution currentCountSolution = solveQuadratic(test.a, test.b, test.c, &currentX1, &currentX2);

    if (currentCountSolution != test.correctCountSolution) {
        printIncorrectCountSolution(test.correctCountSolution, currentCountSolution);
        return FAILED;
    }
    if (!((isEqual(currentX1, test.correctX1, PRECISION) && isEqual(currentX2, test.correctX2, PRECISION)) ||
          (isEqual(currentX1, test.correctX2, PRECISION) && isEqual(currentX2, test.correctX1, PRECISION)))) {

        printIncorrectAnswer(test.correctX1, test.correctX2, currentX1, currentX2);
        return FAILED;
    }
    return PASSED;
}

/* Prints a summary of the test results if the return is incorrect. */
void printIncorrectCountSolution(int correctCountSolution, int currentCountSolution) {
    printf("FAILED\n");
    printf("Incorrect return:\n");
    printf("Correct count solution: %d\n", correctCountSolution);
    printf("Current count solution: %d\n", currentCountSolution);
}

/* Prints a summary of the test results if the answer is incorrect. */
void printIncorrectAnswer(double correctX1, double correctX2, double currentX1, double currentX2) {
    printf("FAILED\n");
    printf("Incorrect answer:\n");
    printf("Correct answer: x1 = %lg, x2 = %lg\n", correctX1, correctX2);
    printf("Current answer: x1 = %lg, x2 = %lg\n", currentX1, currentX2);
        
}

/* Reads tests from a file. */
struct ScanFileTestsStatus scanFileTests(struct TestCase tests[]) {
    struct ScanFileTestsStatus status;
    if (tests == NULL) {
        status.code = ERROR_NULL_PTR;
        return status;
    }

    FILE* file = fopen("./solveq/tests.txt", "r");

    if (file == NULL) {
        status.code = INCORRECT_PATH;
        return status;
    }

    int fscanf_status = 0;

    for (int testNumber = 0; testNumber < NUMBER_TESTS; testNumber++) {
        fscanf_status = fscanf(file, "%lg %lg %lg %d %lg %lg", 
            &tests[testNumber].a,
            &tests[testNumber].b,
            &tests[testNumber].c,
            &tests[testNumber].correctCountSolution,
            &tests[testNumber].correctX1,
            &tests[testNumber].correctX2
        );
        if (fscanf_status != 6) {
            status.code = INCORRECT_DATA;
            status.numberLine = testNumber + 1;
            return status;
        }
    }

    fclose(file);

    status.code = OK;
    return status;
}

/* Prints an error related to reading tests from a file. */
void printScanFileTestsError(struct ScanFileTestsStatus status) {
    switch (status.code)
    {
    case INCORRECT_PATH:
        printf("Error. The file could not be opened. Check that the file path is correct.\n");
        break;
    case INCORRECT_DATA:
        printf("Error. Incorrect data in %d line\n", status.numberLine);
        break;
    case ERROR_NULL_PTR:
        printf("Error. Null pointer\n");
        break;
    case OK:
    default:
        break;
    }
}