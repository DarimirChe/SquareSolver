#include <math.h>
#include <assert.h>
#include <string.h>

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

/* Checks whether it is worth running the test. Returns true if there is a --test flag, otherwise false. */
void parseArgv(int argc, char* argv[], bool* flagStartTests, bool* flagCreateGraph) {
    for (int argNum = 0; argNum < argc; argNum++) {
        if (!strncmp(argv[argNum], "--test", strlen("--test") + 1)) {
            *flagStartTests = true;
        } else if (!strncmp(argv[argNum], "--graph", strlen("--graph") + 1)) {
            *flagCreateGraph = true;
        }
    }
}
