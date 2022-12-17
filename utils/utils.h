#include <stdlib.h>

int doubleComparator ( const void * first, const void * second ) {
    int firstDouble = * (const double *) first;
    int secondDouble = * (const double *) second;
    return (int) (firstDouble - secondDouble);
}

void sortFloatTab(float tab[],int length){
    qsort( tab, length, sizeof(float), doubleComparator );
}

void fprintVect(FILE* out,float Unt[],int length,float t, float dx){
    fprintf(out,"\"U(t) a t = %f\"\n",t);

    for (int i = 0; i < length; i++)
    {
        fprintf(out,"%f\t%f\n",i*dx-10,Unt[i]);
    }
    fprintf(out,"\n\n");
}
