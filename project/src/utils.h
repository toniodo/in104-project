#ifndef __UTILS_H__
#define __UTILS_H__

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

extern int min(int a, int b);
extern int max(int a, int b);

double maxlist(double *list, int nmax, bool index);

void show_matrix(double **mat, int n, int m);

int state_from_pos(int row, int col);

int pos_from_coord(int row, int col);

void coord_from_state(int state, int *row, int *col);

void pos_from_state(int state, int *row, int *col);

int state(int row, int col, bool enemies);

void free_alloc();

#endif