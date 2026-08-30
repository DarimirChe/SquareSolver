#ifndef TEST_SOLVEQ_H
#define TEST_SOLVEQ_H

#include "solvers.h"

const int NUMBER_TESTS = 7;
const char FILENAME[50] = "tests.txt";

enum ScanFileStatusCode {
    OK             = 1,
    INCORRECT_PATH = 2,
    INCORRECT_DATA = 3,
    ERROR_NULL_PTR = 4
};

enum RunTestStatus {
    FAILED = 0,
    PASSED = 1
};

struct TestCase {
    double a;
    double b;
    double c;
    int correctCountSolution;
    double correctX1;
    double correctX2;
};

struct ScanFileTestsStatus {
    enum ScanFileStatusCode code;
    int numberLine;
};

int runTests();
enum RunTestStatus runOneTest(struct TestCase test);

bool isEqualAnswers(double x1, double x2, double x1Ref, double x2Ref);

struct ScanFileTestsStatus scanFileTests(struct TestCase tests[]);

void printIncorrectCountSolution(int correctCountSolution, int currentCountSolution);
void printIncorrectAnswer       (double correctX1, double correctX2, double currentX1, double currentX2);
void printScanFileTestsError    (struct ScanFileTestsStatus status);

#endif /* TEST_SOLVEQ_H */
