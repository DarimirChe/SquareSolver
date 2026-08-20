#include "utilits.h"
#include <math.h>

/* Comparing a double number with zero up to accuracy decimal places. */
bool isZero(double comparedNumber, double precision) {
    return fabs(comparedNumber) < precision;
}
