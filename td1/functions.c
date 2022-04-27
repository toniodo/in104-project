#include <stdio.h>
#include "functions.h"
#include <stdbool.h>
#include <stdlib.h>

int min(int a, int b)
{
    return (a > b) ? b : a;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

// TODO : Remake get max for getting index and max in the same function & add random
double maxlist(double *list, int nmax, bool index)
{
    double max = list[0];
    int indice = 0;
    int *listalea = malloc(sizeof(int) * nmax);
    int alea;
    for (int i; i < nmax; i++)
    {
        if (list[i] > max)
        {
            max = list[i];
            listalea[i] = i;
            // indice = i;
        }
    }
    alea = rand() % nmax;
    while (&listalea[alea - 1] == NULL)
    {
        alea = rand() % nmax;
    }
    indice = list[alea];
    if (index)
        return indice;
    else
        return max;
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
