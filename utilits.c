#include <math.h>

#include "utilits.h"

/* Comparing the first double number with the second double number with a given precision. */
bool compare(double firstNumber, double secondNumber, double precision) {
    return fabs(firstNumber - secondNumber) < precision;
}

/* Compares a comparedNumber to zero with the specified precision. */
bool isZero(double comparedNumber, double precision) {
    return compare(comparedNumber, 0, precision);
}