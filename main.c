#include <stdio.h>

#include "solvers.h"
#include "ui.h"

int main() {
    printWelcomeMessage();

    double a = 0, b = 0, c = 0;

    enum scanCoefficientsStatus isValidCoefficients = scanCoefficients(&a, &b, &c);

    if (isValidCoefficients == INVALID) {
        printInputError();
        return 0;
    }

    double x1 = 0, x2 = 0;

    int countSolution = solveQuadratic(a, b, c, &x1, &x2);

    printSolution(countSolution, x1, x2);
    return 0;
}
