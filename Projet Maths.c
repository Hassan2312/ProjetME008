#include <stdio.h>
#define n 101
#define taille 200000

void afficher_vect(float x[n]) {
  int i;
  printf("--------------------------------------\n");
  for (i = 0; i < taille; i++)
    printf("%f\n", x[i]);
  printf("--------------------------------------\n");
}
void CopyTab(float a[n], float b[n]) {
  for (int i = 0; i < n; i++)
    a[i] = b[i];
}
void init_A(float h, float a[n], float c[n], float d[n]) {
  for (int i = 0; i < n; i++) {
    a[i] = h;
    c[i] = h;
    d[i] = 1 - 2 * h;
  }
  a[n - 1] = 2*h;
  c[0] = 2*h;
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

void Un_instant_t (float Unt[n], float instant, float dt, float dx) {
  float a[n], c[n], d[n];
  float h = dt / (dx * dx);
  init_A(h, a, c, d);
  initU(Unt);
  for (int i = 0; i * dt < instant; i++) {
    updateUn(a, c, d, Unt);
    }
}

void Un_x_fixe (float Ut_x[taille], int position, float dt, float dx) {
  float Unt[n];
  float a[n], c[n], d[n];
  float h = dt / (dx * dx);
  init_A(h, a, c, d);
  initU(Unt);
  for(int i=0; i<taille; i++) {
    Ut_x[i]=Unt[position];
    updateUn(a, c, d, Unt);
  }
}

int main(void) {

  float dt, dx;
  scanf("%f", &dt);
  scanf("%f", &dx);

  float  Un1[n], Un2[n], Un3[n], Un4[n], Un20[n], Ut8[taille];
 
 
 Un_x_fixe (Ut8, 8, dt, dx);


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

  afficher_vect(Ut8);

  return 0;
}
