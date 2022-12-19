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
    printf("%.9f\n", x[i]);
  printf("--------------------------------------\n");
}

void CopyTab(float a[n], float b[n]) {
  for (int i = 0; i < n; i++)
    a[i] = b[i];
}

void init_un(float un[n]) {
  int mid = (int)(n/2);
  for (int i = 0; i < n; i++) {
    if (i < mid)
      un[i] = 1;
    else
      un[i] = 10;
  }
  un[mid] = 5.5;
}

void init_C(float μ, float a[n], float c[n], float d[n], int cond) {
  for (int i = 0; i < n; i++) {
    a[i] = -μ;
    c[i] = -μ;
    d[i] = 1 + 2 * μ;
  }
  switch(cond) {
    case 1:
      c[0] = -2*μ;
      a[n-1] = -2*μ;
      break;
    case 2:
      d[0] = 1;
      c[0] = 0;
      d[n-1] = 1;
      a[n-1] = 0;
      break;
    case 3:
      d[0] = 1;
      c[0] = 0;
      a[n-1] = -2*μ;
      break;
    }
}

void resol_LU(float l[n], float u[n], float v[n], float x[n], float b[n]) {
  float y[n];
  y[0]=b[0];
  for (int i = 1; i < n; i++) {
    y[i]=b[i]-l[i]*y[i-1];
  }
  x[n-1]=y[n-1]/u[n-1];
  for (int i = n-2; i >= 0; i--) {
    x[i]=(y[i]-v[i]*x[i+1])/u[i];
  }
}

void un_instant_t(float unt[n], float instant, float dt, float dx, int cond) {
  float un[n], y[n];
  float a[n], d[n], c[n], l[n], u[n], v[n];
  float μ = dt / (dx * dx);
  init_un(un);
  init_C(μ, a, c, d, cond);
  factoriser_tridiago(d, c, a, l, u, v);
  for(int i=0; i<instant/dt; i++) {
    resol_LU(l, u, v, unt, un);
    CopyTab(un, unt);
    }
}

int main(void) {
  float un200[n];
  float dt=0.001, dx=20./(n-1);
  int cond;
  
  printf("Bonjour!\nChoisissez les conditions aux limites:\n\n\t1. Neumann-Neumann\t\t2. Dirichlet-Dirichlet\t\t3. Dirichlet-Neumann\n\nSaisir un numéro =>");
  scanf("%d", &cond);

  un_instant_t(un200, 200, dt, dx, cond);
  afficher_vect(un200);
  return 0;
}
