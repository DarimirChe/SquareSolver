#include <stdio.h>

#include "solvers.h"

bool testSolveLinear(double b, double c, enum countSolution correctReturn, double correctX);

void printIncorrectReturn(double b, double c, enum countSolution currentReturn, enum countSolution correctReturn);
void printIncorrectX(double b, double c, double currentX, double correctX);

struct dataTest {
    double b;
    double c;
    enum countSolution currentCountSolution;
    double currentX;
};

const int COUNT_TESTS = 9;

int main() {
    struct dataTest tests[COUNT_TESTS] = {
        {.b = 1, .c = 1, .currentCountSolution = ONE_SOLUTION, .currentX = -1},
        {.b = 1, .c = -2, .currentCountSolution = ONE_SOLUTION, .currentX = 2},
        {.b = 2, .c = 3, .currentCountSolution = ONE_SOLUTION, .currentX = -1.5},
        {.b = -2, .c = -1, .currentCountSolution = ONE_SOLUTION, .currentX = -0.5},
        {.b = -1.5, .c = 3, .currentCountSolution = ONE_SOLUTION, .currentX = 2},
        {.b = 0.5, .c = -1.25, .currentCountSolution = ONE_SOLUTION, .currentX = 2.5},
        {.b = -3.5, .c = 0, .currentCountSolution = ONE_SOLUTION, .currentX = 2.5},
        {.b = 0, .c = 0, .currentCountSolution = INFINITY_SOLUTIONS, .currentX = 0},
        {.b = 0, .c = 1, .currentCountSolution = NO_SOLUTION, .currentX = 0}
    };

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
    } else if (currentX != correctX) {
        printIncorrectX(b, c, currentX, correctX);
        return false;
    }
    return true;
}

/* Prints the test summary if the return is incorrect */
void printIncorrectReturn(double b, double c, enum countSolution currentCountSolution, enum countSolution correctCountSolution) {
    printf("Incorrect return.\n");
    printf("Input: b = %lg, c = %lg\n", b, c);
    printf("Current return: %d\n", currentCountSolution);
    printf("Correct return: %d\n", correctCountSolution);
}

/* Prints the test summary if the x is incorrect */
void printIncorrectX(double b, double c, double currentX, double correctX) {
    printf("Incorrect x.\n");
    printf("Input: b = %lg, c = %lg\n", b, c);
    printf("Current x: %lg\n", currentX);
    printf("Correct x: %lg\n", correctX);
}
