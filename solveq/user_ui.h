enum ScanCoefficientsStatus {
    INVALID = 0,
    VALID,
    ERROR_POINTER
};

/** что делает?
 * @param [in] 
 */
void printSolution(int countOfSolves, double x1, double x2);


void printWelcomeMessage(void);
void printInputError(void);

enum ScanCoefficientsStatus scanCoefficients(double* a, double* b, double* c);

bool bufferIsClear();
