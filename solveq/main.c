#include "solvers.h"
#include "user_io.h"
#include "test_solveq.h"

int main(int argc, char* argv[]) {
    if (shouldStartTest(argc, argv)) {
        runTests();
        return 0;
    }

    printWelcomeMessage();

    double a = 0, b = 0, c = 0;

    enum ScanCoefficientsStatus isValidCoefficients = scanCoefficients(&a, &b, &c);

    if (isValidCoefficients == INVALID) {
        printInputError();
        return 0;
    }

    double x1 = 0, x2 = 0;

    int countSolution = solveQuadratic(a, b, c, &x1, &x2);

    printSolution(countSolution, x1, x2);
    return 0;
}

