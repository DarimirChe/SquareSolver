#include <stdio.h>
#include <math.h>

enum countSolution {
    NO_SOLUTION = 0, 
    ONE_SOLUTION, 
    TWO_SOLUTIONS,
    INFINITY_SOLUTIONS,
    ERROR_NULL_POINTER
};

enum scanCoefficientsStatus {
    INVALID = 0,
    VALID,
    ERROR_POINTER
};

enum countSolution solveQuadratic(double a, double b, double c, double* x1, double* x2);
double solveLinear(double b, double c);

void printSolution(int countOfSolves, double x1, double x2);
void printWelcomeMessage(void);
void printInputError(void);

enum scanCoefficientsStatus scanCoefficients(double* a, double* b, double* c);

bool isZero(double x, double precision);

const double PRECISION = 1e-5;

int main() {
    printWelcomeMessage();

    double a = 0, b = 0, c = 0;

    bool isValidCoefficients = scanCoefficients(&a, &b, &c);

    if (isValidCoefficients == INVALID) {
        printInputError();
        return 0;
    }

    double x1 = 0, x2 = 0;

    int countSolution = solveQuadratic(a, b, c, &x1, &x2);

    printSolution(countSolution, x1, x2);
    return 0;
}

/* Solving quadratic equations of the form: ax^2 + bx + c = 0 */
enum countSolution solveQuadratic(double a, double b, double c, double* x1, double* x2) {
    if (x1 == NULL || x2 == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (isZero(a, PRECISION)) {
        if (isZero(b, PRECISION)) {
            if (isZero(c, PRECISION)) {
                return INFINITY_SOLUTIONS;
            }
            return NO_SOLUTION;
        }
        *x1 = solveLinear(b, c);
        return ONE_SOLUTION;
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return NO_SOLUTION;
    }

    if (isZero(discriminant, PRECISION)) {
        *x1 = -b / 2 * a;
        return ONE_SOLUTION;
    }

    *x1 = (-b + sqrt(discriminant)) / (2 * a);
    *x2 = (-b - sqrt(discriminant)) / (2 * a);

    return TWO_SOLUTIONS;
}

/* Solves a linear equation of the form: b*x - c = 0 */
double solveLinear(double b, double c) {
    return -c / b;
}

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

/* Comparing a double number with zero up to accuracy decimal places. */
bool isZero(double comparedNumber, double precision) {
    return fabs(comparedNumber) < precision;
}

/* displays a description of the program and input instructions */
void printWelcomeMessage() {
    printf("A program for solving quadratic equations of the form: ax^2 + bx + c = 0.\n");
    printf("Enter the coefficients a, b, and c:\n");
}

/* Accepts coefficients a, b, and c from the input buffer. Returns 1 if the data is correct and 0 otherwise. */
enum scanCoefficientsStatus scanCoefficients(double* a, double* b, double* c) {
    if (a == NULL || b == NULL || c == NULL) {
        return ERROR_POINTER;
    }

    if (scanf("%lg %lg %lg", a, b, c) != 3) 
        return INVALID;
    if (isfinite(*a) && isfinite(*b) && isfinite(*c)) 
        return VALID;
    return INVALID;
}

void printInputError() {
    printf("The entered coefficients are incorrect\n");
}
