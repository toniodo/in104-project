#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <math.h>
#include <stdbool.h>

extern int min(int a, int b);
extern int max(int a, int b);

double maxlist(double *list, int nmax, bool index);

void show_matrix(double **mat, int n, int m);

#endif
