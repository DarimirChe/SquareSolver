#include <math.h>
#include <assert.h>

#include "utilits.h"

/* Comparing the first double number with the second double number with a given precision. */
bool isEqual(double firstNumber, double secondNumber, double precision) { 
    assert(isfinite(firstNumber));
    assert(isfinite(secondNumber));
    assert(isfinite(precision));

    return fabs(firstNumber - secondNumber) < precision;
}

/* Compares a comparedNumber to zero with the specified precision. */
bool isZero(double comparedNumber, double precision) {
    return isEqual(comparedNumber, 0, precision);
}
