#include <stdlib.h>

int doubleComparator ( const void * first, const void * second ) {
    int firstDouble = * (const double *) first;
    int secondDouble = * (const double *) second;
    return (int) (firstDouble - secondDouble);
}

void sortFloatTab(float tab[],int lenght){
    qsort( tab, lenght, sizeof(float), doubleComparator );
}

void fprintVect(FILE* out,float Unt[],int lenght,float t){
    fprintf(out,"\"U(t) a t = %f\"\n",t);

    for (int i = 0; i < lenght; i++)
    {
        fprintf(out,"%d\t%f\n",i,Unt[i]);
    }
    fprintf(out,"\n\n");
}