#include <stdio.h>
#include <math.h>

#include "user_io.h"
#include "solvers.h"
#include "utilits.h"

/* It outputs the answer based on the number of solutions to the equation. */
void printSolution(int countSolution, double x1, double x2) {
    if (isZero(x1, PRECISION)) {  // so that there is no output of -0 or 0.0000001 and so on
        x1 = 0;
    }
    if (isZero(x2, PRECISION)) {
        x2 = 0;
    }

    switch (countSolution)
    {
    case NO_SOLUTION:
        printf("The equation has no solution\n");
        break;
    case ONE_SOLUTION:
        printf("The equation has one solution:\n");
        printf("x = %.5lg\n", x1);
        break;
    case TWO_SOLUTIONS:
        printf("The equation has two solutions:\n");
        printf("x1 = %.5lg, x2 = %.5lg\n", x1, x2);
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

/* Accepts coefficients a, b, and c from the input buffer. Returns enum ScanCoefficientsStatus VALID if 
the data is correct and INVALID otherwise. */
enum ScanCoefficientsStatus scanCoefficients(double* a, double* b, double* c) {
    if (a == NULL || b == NULL || c == NULL) {
        return ERROR_POINTER;
    }

    if (scanOneCoefficient(a) == INVALID) {
        return INVALID;
    }

    if (scanOneCoefficient(b) == INVALID) {
        return INVALID;
    }

    if (scanOneCoefficient(c) == INVALID) {
        return INVALID;
    }

    if (!bufferIsClear()) {
        return INVALID;
    }

    return VALID;
}

/* Reads one coefficient from the input buffer. Returns the enum ScanCoefficientsStatus VALID if
the data is correct, and INVALID otherwise. */
enum ScanCoefficientsStatus scanOneCoefficient(double* coefficient) {
    if (coefficient == NULL) {
        return ERROR_POINTER;
    }

    if (scanf("%lg", coefficient) != 1) {
        return INVALID;
    }

    if (isfinite(*coefficient)) {
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
