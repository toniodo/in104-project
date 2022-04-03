#include "functions.h"

int min(int a,int b)
{
    return (a > b) ? b : a;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int imaxlist(double *list, int nmax){
    double max=list[0];
    int indice=0;
    for (int i;i<nmax;i++){
        if (list[i]>max){
            indice=i;
        }
    }
    return(indice);
}

double maxlist(double *list, int nmax){
    double max=list[0];
    for (int i=0;i<nmax;i++){
        if (list[i]>max){
            max=list[i];
        }
    }
    return(max);
}
