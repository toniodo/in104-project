#include <stdio.h>
#include "functions.h"
#include <stdbool.h>
#include <stdlib.h>
#include "mazeEnv.h"
#include "qlearning.h"

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
    bool *listalea = malloc(sizeof(bool) * nmax);
    int cpt = 0;
    for (int i = 0; i < nmax; i++)
    {
        if (list[i] > max)
        {
            max = list[i];
            indice = i;
        }
    }
    /* à revoir (floating point exception sometimes)
    for (int i = 0; i < nmax; i++)
    {
        if (list[i] == max)
        {
            listalea[i] = true;
            cpt++;
        }
        else
        {
            listalea[i] = false;
        }
    }

    int length = cpt;
    int j = 0;
    int *ind = malloc(sizeof(int) * length);
    while (cpt != 0)
    {
        if (listalea[j] == true)
        {
            ind[cpt - 1] = j;
            cpt--;
        }
        j++;
    }
    int alea = rand() % (length);
    indice = ind[alea];
    free(listalea);
    free(ind);
*/
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

int state_from_pos(int row, int col)
{
    return row * cols + col;
}

void pos_from_state(int state, int *row, int *col)
{
    *row = state / cols;
    *col = state % cols;
}