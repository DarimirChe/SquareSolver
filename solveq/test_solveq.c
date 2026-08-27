#include "test_solveq.h"

void runTests() {
    struct TestCase tests[5] = { // пока временно, нужно считывать из файла
        {.a = 1, .b = 1, .c = 1, .correctCountSolution = NO_SOLUTION, .correctX1 = 0, .correctX2 = 0},
        {.a = 1, .b = 0, .c = 0, .correctCountSolution = ONE_SOLUTION, .correctX1 = 0, .correctX2 = 0},
        {.a = 2.5, .b = 6, .c = 0, .correctCountSolution = TWO_SOLUTIONS, .correctX1 = 0, .correctX2 = -2.4},
        {.a = 1e-6, .b = 0, .c = 0, .correctCountSolution = INFINITY_SOLUTIONS, .correctX1 = 0, .correctX2 = 0},
        {.a = -3.12, .b = 86.3, .c = 0.5, .correctCountSolution = TWO_SOLUTIONS, .correctX1 = -0.00579253, .correctX2 = 27.666},
    };
    // как узнает кол-во тестов?
    // вызывает runTest
}

void runTest(struct TestCase test) {
    // вызывает solveQuadratic, получаетсянужно его подключить? Будет ли множественное подключение?
}