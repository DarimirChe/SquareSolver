enum countSolution {
    NO_SOLUTION = 0, 
    ONE_SOLUTION, 
    TWO_SOLUTIONS,
    INFINITY_SOLUTIONS,
    ERROR_NULL_POINTER
};

enum countSolution solveQuadratic(double a, double b, double c, double* x1, double* x2);
enum countSolution solveLinear(double b, double c, double* x);
