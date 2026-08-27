#include <stdio.h>
#include <math.h>

#include "user_io.h"
#include "solvers.h"

/* It outputs the answer based on the number of solutions to the equation. */
void printSolution(int countSolution, double x1, double x2) {
    switch (countSolution)
    {
    case NO_SOLUTION:
        printf("The equation has no solution\n");
        break;
    case ONE_SOLUTION:
        printf("The equation has one solution:\n");
        printf("x = %lg\n", x1);
        break;
    case TWO_SOLUTIONS:
        printf("The equation has two solutions:\n");
        printf("x1 = %lg, x2 = %lg\n", x1, x2);
        break;
    case INFINITY_SOLUTIONS:
        printf("The equation has an infinite number of solutions\n");
        break;
    default:
        printf("error\n");
        break;
    }
}

/* Displays a description of the program and input instructions. */
void printWelcomeMessage() {
    printf("A program for solving quadratic equations of the form: ax^2 + bx + c = 0.\n");
    printf("Enter the coefficients a, b, and c:\n");
}

/* Outputs an error in entering coefficients. */
void printInputError() {
    printf("The entered coefficients are incorrect\n");
}

/* Accepts coefficients a, b, and c from the input buffer. Returns 1 if the data is correct and 0 otherwise. */
enum ScanCoefficientsStatus scanCoefficients(double* a, double* b, double* c) {
    if (a == NULL || b == NULL || c == NULL) {
        return ERROR_POINTER;
    }
    
    if (scanf("%lg %lg %lg", a, b, c) != 3) {
        return INVALID;
    }
    
    if (!bufferIsClear()) {
        return INVALID;
    }

    if (isfinite(*a) && isfinite(*b) && isfinite(*c)) {
        return VALID;
    }

    return INVALID;
}

/* Checks if the buffer is clean. */
bool bufferIsClear() {
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c != ' ' && c != '\t') {
            return false;
        }
    }
    return true;
}
