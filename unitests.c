#include <stdio.h>

#include "solvers.h"

void testSolveLinear(double b, double c, enum countSolution correctReturn, double correctX);

void printIncorrectReturn(double b, double c, enum countSolution currentReturn, enum countSolution correctReturn);
void printIncorrectX(double b, double c, double currentX, double correctX);

int testNumber = 1;

int main() {
    testSolveLinear(1, 1, ONE_SOLUTION, -1);
    testSolveLinear(1, -2, ONE_SOLUTION, 2);
    testSolveLinear(2, 3, ONE_SOLUTION, -1.5);
    testSolveLinear(-2, -1, ONE_SOLUTION, -0.5);
    testSolveLinear(0, 1, NO_SOLUTION, 0);
    testSolveLinear(1, 0, INFINITY_SOLUTIONS, 0);
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
    testNumber++;
}

/* Prints the test summary if the return is incorrect */
void printIncorrectReturn(double b, double c, enum countSolution currentReturn, enum countSolution correctReturn) {
    printf("Test #%d failed: incorrect return.\n", testNumber);
    printf("Input: b = %lg, c = %lg\n", b, c);
    printf("Current return: %d\n", currentReturn);
    printf("Correct return: %d\n\n", correctReturn);
}

/* Prints the test summary if the x is incorrect */
void printIncorrectX(double b, double c, double currentX, double correctX) {
    printf("Test #%d failed: incorrect x.\n", testNumber);
    printf("Input: b = %lg, c = %lg\n", b, c);
    printf("Current x: %lg\n", currentX);
    printf("Correct x: %lg\n\n", correctX);
}
