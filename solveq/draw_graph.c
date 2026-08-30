#include <assert.h>
#include <math.h>

#include "draw_graph.h"

void createGraph(double a, double b, double c) {
    char canvas[HEIGHT][WIDTH] = {};

    clearCanvas(canvas);

    drawXAxis(canvas);
    drawYAxis(canvas);

    drawZeroPoint(canvas);

    drawParabola(canvas, a, b, c);

    saveToFile(canvas);
    printGraph(canvas);
}

void clearCanvas(char canvas[][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            canvas[y][x] = ' ';
        }
    }
}

void drawZeroPoint(char canvas[][WIDTH]) {
    canvas[ZERO_POINT_Y + 1][ZERO_POINT_X - 1] = '0';
}

void drawXAxis(char canvas[][WIDTH]) {
    canvas[ZERO_POINT_Y    ][WIDTH - 1] = '>';
    canvas[ZERO_POINT_Y + 1][WIDTH - 1] = 'X';

    for (int x = 0; x < WIDTH - 1; x++) {
        canvas[ZERO_POINT_Y][x] = X_AXIS_CHAR;
    }
}

void drawYAxis(char canvas[][WIDTH]) {
    canvas[0][ZERO_POINT_X] = '^';
    canvas[0][ZERO_POINT_X + 1] = 'Y';
    
    for (int y = 1; y < HEIGHT; y++) {
        canvas[y][ZERO_POINT_X] = Y_AXIS_CHAR;
    }
}

void drawParabola(char canvas[][WIDTH], double a, double b, double c) {
    double x = 0, y = 0;
    int indexX = 0, indexY = 0;

    for (x = -(WIDTH / 2); x < WIDTH / 2; x += 0.5) {
        y = a * x * x + b * x + c;

        y = HEIGHT / 2 - y;

        indexX = (int) round(x + WIDTH / 2);
        indexY = (int) round(y);
    
        if (0 <= indexY && indexY < HEIGHT) {
            canvas[indexY][indexX] = GRAPH_CHAR;
        }
    }
}

void saveToFile(char canvas[][WIDTH]) {
    FILE *file = fopen(GRAPH_FILENAME, "w");

    for (int line = 0; line < HEIGHT; line++) {
        for (int column = 0; column < WIDTH; column++) {
            fputc(canvas[line][column], file);
        }
        fputc('\n', file);
    }

    fclose(file);
}

void printGraph(char canvas[][WIDTH]) {
    for (int line = 0; line < HEIGHT; line++) {
        for (int column = 0; column < WIDTH; column++) {
            putchar(canvas[line][column]);
        }
        putchar('\n');
    }
}
