#include <stdio.h>
#define n 99   //Vu que U0 et U100 sont constants au pas n+1 ca sert a rien de les calculer

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
    printf("%.9f\n", x[i]);
  printf("--------------------------------------\n");
}

void CopyTab(float a[n], float b[n]) {
  for (int i = 0; i < n; i++)
    a[i] = b[i];
}

void initU(float Un[n]) {
  int mid = (int)(n/2);
  for (int i = 0; i < n; i++) {
    if (i < mid)
      Un[i] = 1;
    else
      Un[i] = 10;
  }
  Un[mid] = 5.5;
}

void init_C(float h, float a[n], float c[n], float d[n]) {
  for (int i = 0; i < n; i++) {
    a[i] = -h;
    c[i] = -h;
    d[i] = 1 + 2 * h;
  }
}

void resol_LU_Neumann(float l[n], float u[n], float v[n], float x[n], float un[n]) {
  float y[n], float d[n] = {0};
  d[0] = 
  y[0]=un[0]+d[0];
  for (int i = 1; i < n; i++) {
    y[i]=un[i]-l[i]*y[i-1];
  }
  x[n-1]=y[n-1]/u[n-1];
  for (int i = n-2; i >= 0; i--) {
    x[i]=(y[i]-v[i]*x[i+1])/u[i];
  }
}

int main(void) {
  float un[n], un1[n], y[n];
  float a[n], d[n], c[n], l[n], u[n], v[n];
  float dt=0.0001, dx=20./(n-1);
  float mu=dt/(dx*dx);
  initU(un);
  init_C(mu, a, c, d);
  factoriser_tridiago(d, c, a, l, u, v);
  for(int i=0; i*dt<=200; i++) {
    resol_LU_Neumann(l, u, v, un1, un);
    CopyTab(un, un1);
    }
  afficher_vect(un);
  return 0;
}
