enum ScanCoefficientsStatus {
    INVALID       = 0,
    VALID         = 1,
    ERROR_POINTER = 2
};

void printSolution(int countOfSolves, double x1, double x2);

void printWelcomeMessage(void);
void printInputError    (void);

enum ScanCoefficientsStatus scanCoefficients(double* a, double* b, double* c);

bool bufferIsClear();
