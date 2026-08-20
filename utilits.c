#include <math.h>

#include "utilits.h"

/* Comparing a double number with zero up to accuracy decimal places. */
bool isZero(double comparedNumber, double precision) {
    return fabs(comparedNumber) < precision;
}
