#include "solvers.h"

const unsigned int countTests = 5;

struct TestCase {
    double a;
    double b;
    double c;
    enum CountSolution correctCountSolution;
    double correctX1;
    double correctX2;
};

void runTests();
void runTest(struct TestCase test);