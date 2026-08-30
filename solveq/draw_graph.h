#ifndef DRAW_GRAPH_H
#define DRAW_GRAPH_H

#include <stdio.h>

const char GRAPH_FILENAME[50] = "graph.txt";

const int WIDTH  = 100;
const int HEIGHT = 40;

const int ZERO_POINT_X = WIDTH / 2;
const int ZERO_POINT_Y = HEIGHT / 2;

const int DELTA_X = 3; // DELTA_X symbols = 1
const int DELTA_Y = 3;

const char X_AXIS_CHAR = '-';
const char Y_AXIS_CHAR = '|';
const char GRAPH_CHAR  = '*';

void clearCanvas  (char canvas[][WIDTH]);
void createGraph  (double a, double b, double c);
void drawZeroPoint(char canvas[][WIDTH]);
void drawXAxis    (char canvas[][WIDTH]);
void drawYAxis    (char canvas[][WIDTH]);
void drawParabola (char canvas[][WIDTH], double a, double b, double c);


void saveToFile(char canvas[][WIDTH]);
void printGraph(char canvas[][WIDTH]);

#endif /* DRAW_GRAPH_H */
