// #ifndef UI_H
// #define UI_H

// #include "solvers.h"

enum scanCoefficientsStatus {
    INVALID = 0,
    VALID,
    ERROR_POINTER
};

void printSolution(int countOfSolves, double x1, double x2);
void printWelcomeMessage(void);
void printInputError(void);

enum scanCoefficientsStatus scanCoefficients(double* a, double* b, double* c);

// #endif /* UI_H */