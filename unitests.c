#include <stdio.h>

#include "solvers.h"

void testSolveLinear(double b, double c, enum countSolution correctReturn, double correctX);

void printIncorrectReturn(double b, double c, enum countSolution currentReturn, enum countSolution correctReturn);
void printIncorrectX(double b, double c, double currentX, double correctX);

int main() {
    printf("Test 1 processing\n");
    testSolveLinear(1,    1,     ONE_SOLUTION, -1);
    printf("Test 2 processing\n");
    testSolveLinear(1,    -2,    ONE_SOLUTION, 2);
    printf("Test 3 processing\n");
    testSolveLinear(2,    3,     ONE_SOLUTION, -1.5);
    printf("Test 4 processing\n");
    testSolveLinear(-2,   -1,    ONE_SOLUTION, -0.5);
    printf("Test 5 processing\n");
    testSolveLinear(-1.5, 3,     ONE_SOLUTION, 2);
    printf("Test 6 processing\n");
    testSolveLinear(0.5,  -1.25, ONE_SOLUTION, 2.5);
    printf("Test 7 processing\n");
    testSolveLinear(-3.5, 0,     ONE_SOLUTION, 10);

    printf("Test 8 processing\n");
    testSolveLinear(0, 0, ONE_SOLUTION, 0);

    printf("Test 9 processing\n");
    testSolveLinear(0, 1, NO_SOLUTION, 0);
    return 0;
}

/* Tests the solveLinear() function, accepts coefficients b, c of the equation of the form: bx + c = 0, 
the correct return and x for these coefficients */
void testSolveLinear(double b, double c, enum countSolution correctReturn, double correctX) {
    double currentX = 0;
    enum countSolution currerntReturn = solveLinear(b, c, &currentX);

    if (currerntReturn != correctReturn) {
        printIncorrectReturn(b, c, currerntReturn, correctReturn);
    } else if (currentX != correctX) {
        printIncorrectX(b, c, currentX, correctX);
    }
}

/* Prints the test summary if the return is incorrect */
void printIncorrectReturn(double b, double c, enum countSolution currentReturn, enum countSolution correctReturn) {
    printf("Test failed: incorrect return.\n");
    printf("Input: b = %lg, c = %lg\n", b, c);
    printf("Current return: %d\n", currentReturn);
    printf("Correct return: %d\n", correctReturn);
}

/* Prints the test summary if the x is incorrect */
void printIncorrectX(double b, double c, double currentX, double correctX) {
    printf("Test failed: incorrect x.\n");
    printf("Input: b = %lg, c = %lg\n", b, c);
    printf("Current x: %lg\n", currentX);
    printf("Correct x: %lg\n", correctX);
}
