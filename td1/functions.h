#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <math.h>

extern int min(int a, int b);
extern int max(int a, int b);

int imaxlist(double *list, int nmax);
double maxlist(double *list, int nmax);

void show_matrix(double **mat, int n, int m);

#endif
