#include <stdio.h>
#include "functions.h"

int min(int a, int b)
{
    return (a > b) ? b : a;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int imaxlist(double *list, int nmax)
{
    double max = list[0];
    int indice = 0;
    for (int i; i < nmax; i++)
    {
        if (list[i] > max)
        {
            indice = i;
        }
    }
    return (indice);
}

double maxlist(double *list, int nmax)
{
    double max = list[0];
    for (int i = 0; i < nmax; i++)
    {
        if (list[i] > max)
        {
            max = list[i];
        }
    }
    return (max);
}

void show_matrix(double **mat, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d  ", i);
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] >= 0.)
                printf(" ");
            printf("%.3f ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
