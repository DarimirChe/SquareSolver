#include <math.h>

#include "utilits.h"

/* Comparing a first double number with second duble number up to accuracy decimal places. */
bool compare(double firstNumber, double secondNumber, double precision) {
    return fabs(firstNumber - secondNumber) < precision;
}