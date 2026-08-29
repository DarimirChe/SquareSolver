#ifndef SOLVERS_H
#define SOLVERS_H

enum CountSolution {
    NO_SOLUTION        = 0, 
    ONE_SOLUTION       = 1, 
    TWO_SOLUTIONS      = 2,
    INFINITY_SOLUTIONS = 3,
    ERROR_NULL_POINTER = 4,
    INVALID_COEFF      = 5
};

enum CountSolution solveQuadratic(double a, double b, double c, double* x1, double* x2);
enum CountSolution solveLinear   (double k, double m, double* x);

#endif /* SOLVERS_H */