#include "test_solveq.h"
#include "solvers.h"
#include "utilits.h"

void runTests() {
    struct TestCase tests[5] = { // пока временно, нужно считывать из файла
        {.a = 1, .b = 1, .c = 1, .correctCountSolution = NO_SOLUTION, .correctX1 = 0, .correctX2 = 0},
        {.a = 1, .b = 0, .c = 0, .correctCountSolution = ONE_SOLUTION, .correctX1 = 0, .correctX2 = 0},
        {.a = 2.5, .b = 6, .c = 0, .correctCountSolution = TWO_SOLUTIONS, .correctX1 = 0, .correctX2 = -2.4},
        {.a = 1e-6, .b = 0, .c = 0, .correctCountSolution = INFINITY_SOLUTIONS, .correctX1 = 0, .correctX2 = 0},
        {.a = -3.12, .b = 86.3, .c = 0.5, .correctCountSolution = TWO_SOLUTIONS, .correctX1 = -0.00579253, .correctX2 = 27.666},
    };
    for (int countTest = 0; countTest < CountTests; countTest++) {
        runTest(tests[countTest]);
    }
}

bool runTest(struct TestCase test) {
    double currentX1 = 0, currentX2 = 0;
    enum CountSolution currentCountSolution = solveQuadratic(test.a, test.b, test.c, &currentX1, &currentX2);

    if (currentCountSolution != test.correctCountSolution) {
        printf("Test failed\n");
        printf("Incorrect return:\n");
        printf("Correct return: %d\n", test.correctCountSolution);
        printf("Current count solution: %d\n", currentCountSolution);
        return false;
    }
    if (!(
        (isEqual(currentX1, test.correctX1, PRECISION) && isEqual(currentX2, test.correctX2, PRECISION)) || 
        (isEqual(currentX1, test.correctX2, PRECISION) && isEqual(currentX2, test.correctX1, PRECISION)))) {

        printf("Test failed\n");
        printf("Incorrect answer:\n");
        printf("Correct x1: %d\n", test.correctCountSolution);
        printf("Current count solution: %d\n", currentCountSolution);
    }
}
