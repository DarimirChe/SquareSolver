#ifndef USER_IO_H
#define USER_IO_H

enum ScanCoefficientsStatus {
    INVALID       = 0,
    VALID         = 1,
    ERROR_POINTER = 2
};

void printSolution(int countOfSolves, double x1, double x2);

void printWelcomeMessage(void);
void printInputError    (void);

enum ScanCoefficientsStatus scanCoefficients  (double* a, double* b, double* c);
enum ScanCoefficientsStatus scanOneCoefficient(double* coefficient);

bool bufferIsClear();

#endif