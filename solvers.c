#include "solvers.h"
#include "utilits.h"
#include <math.h>

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
