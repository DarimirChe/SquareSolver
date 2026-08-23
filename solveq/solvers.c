#include <math.h>

#include "solvers.h"
#include "utilits.h"

/* Solving quadratic equations of the form: ax^2 + bx + c = 0 */
enum CountSolution solveQuadratic(double a, double b, double c, double* x1, double* x2) {
    if (x1 == NULL || x2 == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (!(isfinite(a) && isfinite(b) && isfinite(c))) {
        return INVALID_COEFF;
    }

    if (isZero(a, PRECISION)) {
        return solveLinear(b, c, x1);
    }

    double discriminant = b * b - 4 * a * c;

    if (isZero(discriminant, PRECISION)) {
        *x1 = -b / 2 * a;
        return ONE_SOLUTION;
    }

    if (discriminant < 0) {
        return NO_SOLUTION;
    }

    *x1 = (-b + sqrt(discriminant)) / (2 * a);
    *x2 = (-b - sqrt(discriminant)) / (2 * a);

    return TWO_SOLUTIONS;
}

/* Solves a linear equation of the form: k*x + m = 0 */
enum CountSolution solveLinear(double k, double m, double* x) {
    if (x == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (!(isfinite(k) && isfinite(m))) {
        return INVALID_COEFF;
    }

    if (isZero(k, PRECISION)) {
        if (isZero(m, PRECISION)) {
            return INFINITY_SOLUTIONS;
        }
        return NO_SOLUTION;
    }
    *x = -m / k;
    return ONE_SOLUTION;
}
