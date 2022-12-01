#include <stdio.h>
#define n 101

void factoriser_tridiago(float d[n], float c[n], float a[n], float l[n],
                         float u[n], float v[n]) {
  int i;
  v[n - 1] = 0, l[0] = 0;
  u[0] = d[0];                                                                  //  d0  c0  0    0   0              1    0   0   0      u0  v0  0   0
  for (i = 0; i < n; i++) {                                                     //  a1  d1  c1   0   0              l1   1   0   0      0   u1  v1  0
    v[i] = c[i];                                                                //  0   a2  d2  c2   0              0   l2   1   0      0   0   u2  v2
    l[i + 1] = a[i + 1] / u[i];                                                 //  ...                             ...                 ...
    u[i + 1] = d[i + 1] - l[i + 1] * v[i];                                      //  0   ...    an-1  dn-1           0   0  ln-1  1      0   0   0  un-1
  }
}

void afficher_vect(float x[n]) {
  int i;
  printf("--------------------------------------\n");
  for (i = 0; i < n; i++)
    printf("%f\n", x[i]);
  printf("--------------------------------------\n");
}

void CopyTab(float a[n], float b[n]) {
  for (int i = 0; i < n; i++)
    a[i] = b[i];
}

void initU(float Un[n]) {
  for (int i = 0; i < n; i++) {
    if (i < 50)
      Un[i] = 1;
    else
      Un[i] = 10;
  }
  Un[49] = 5.5;
}

void updateUn(float a[n], float c[n], float d[n], float Un[n]) {
  float Un1[n];
  Un1[0] = d[0] * Un[0] + c[0] * Un[1];
  Un1[n - 1] = d[n - 1] * Un[n - 1] + a[n - 1] * Un[n - 2];
  for (int i = 1; i < n - 1; i++)
    Un1[i] = a[i] * Un[i - 1] + d[i] * Un[i] + c[i] * Un[i + 1];

  CopyTab(Un, Un1);
}

void init_C(float h, float a[n], float c[n], float d[n]) {
  for (int i = 0; i < n; i++) {
    a[i] = -h;
    c[i] = -h;
    d[i] = 1 + 2 * h;
  }
  c[0] = -2*h;
  a[n - 1] = -2*h;
}


int main(void) {

  float dt, dx;
  scanf("%f", &dt);
  scanf("%f", &dx);

  float  Un1[n], Un2[n], Un3[n], Un4[n], Un20[n];

  

  Un_instant_t (Un1, 1, dt, dx);
  Un_instant_t (Un2, 2, dt, dx);
  Un_instant_t (Un3, 3, dt, dx);
  Un_instant_t (Un4, 4, dt, dx);
  Un_instant_t (Un20, 20, dt, dx);

  FILE *out1 = fopen("Un1.txt","wt");
  for(int i = 0; i<n; i++) {
    fprintf(out1,"%f\t%f\n", i*dx-10, Un1[i]);
  }
  fclose(out1);
  
  afficher_vect(Un1);
  afficher_vect(Un20);
  
  return 0;
}
