#include <stdio.h>
#include <stdlib.h>
#include "utils/utils.h"

#define TAILLE_INTERVALLE 20

#define n 99        //Inutile de calculer u0 et u100

void factoriser_tridiago(float d[n], float c[n], float a[n], float l[n],
                         float u[n], float v[n]) {
  int i;
  c[n - 1] = 0, v[n - 1] = 0, l[0] = 0;
  u[0] = d[0];
  for (i = 0; i < n; i++) {
    v[i] = c[i];
    l[i + 1] = a[i + 1] / u[i];
    u[i + 1] = d[i + 1] - l[i + 1] * v[i];
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

void init(float h, float a[n], float c[n], float d[n]) {
  float u0=1, u100=10;
  for (int i = 0; i < n; i++) {
    a[i] = h;
    c[i] = h;
    d[i] = 1 - 2 * h;
  }
}

void initU(float Un[n]) {
  for (int i = 0; i < n; i++) {
    if (i < 50)
      Un[i] = 1;
    else
      Un[i] = 10;
  }
  Un[50] = 5.5;
}

void updateUn(float a[n], float c[n], float d[n], float Un[n], float b[n]) {
  float Un1[n];
  Un1[0] = d[0] * Un[0] + c[0] * Un[1] + b[0];
  Un1[n - 1] = d[n - 1] * Un[n - 1] + a[n - 1] * Un[n - 2] + b[n-1];
  for (int i = 1; i < n - 1; i++)
    Un1[i] = a[i] * Un[i - 1] + d[i] * Un[i] + c[i] * Un[i + 1];

  CopyTab(Un, Un1);
}

void Un_instant_t(float Unt[n], float instant, float dt, float dx, float u0, float u100) {
  float a[n], c[n], d[n];
  float b[n] = {0};
  float h = dt / (dx * dx);
  b[0] = u0*h;
  b[n-1] = u100*h;
  init(h, a, c, d);
  initU(Unt);
  for (int i = 0; i * dt < instant; i++) {
    updateUn(a, c, d, Unt, b);
  }
}


void save_instant_T(float Unt[n],float dt,float dx,float tmax,float u0,float u100, float list_t[], int lenght){
  float a[n], c[n], d[n];
  float b[n] = {0};
  float h = dt / (dx * dx);

  FILE* out = fopen("output/Explicite_Dirichlet_2.dat","wt");

  //gestion de la recherche du temps recherche
  int currentTimeIndex = 0;

  //Range les temps de stop dans l'ordre croissant
  //ne fonctionne pas pour l'instant
  //sortFloatTab(list_t,lenght);  

  b[0] = u0*h;
  b[n-1] = u100*h;
  init(h, a, c, d);
  initU(Unt);


  for (int i = 0; i * dt < list_t[lenght-1]; i++) {
    if (i*dt>list_t[currentTimeIndex])
    { 
      fprintVect(out,Unt,n,i*dt);
      currentTimeIndex++;
    }
    
    updateUn(a, c, d, Unt, b);
  }

  fclose(out);

}


void save_position_X(float Unt[n],float dt,float dx,float tmax,float u0,float u100, float list_x[], int lenght){

  float a[n], c[n], d[n];
  float b[n] = {0};
  float h = dt / (dx * dx);
  float proportionalite = TAILLE_INTERVALLE/(n*1.0);
  
  init(h, a, c, d);
  initU(Unt);

  FILE *out1 = fopen("output/Explicite_Dirichlet_3.dat","wt");
  
 
  for (int i = 0; i * dt < 200; i++) {
    fprintf( out1, "%f\t", i*dt); //Impression du temps au debut de la ligne 
    for (int j = 0; j < lenght; j++)
    {
      int k = ((int)(list_x[j]/proportionalite))+(n/2);
      fprintf(out1, "%f\t",Unt[k]);
    }
    fprintf(out1,"\n");
    
    updateUn(a, c, d, Unt,b);
  }
  fclose(out1);
  
}


int main(void) {

  float dt, dx;
  dt=0.01;
  dx=0.2;
  float Un1[n], Un2[n], Un3[n], Un4[n], Un200[n];
  float u0 = 1;          //Dirichlet u(x=-10, t) = 1
  float u100 = 10;       //Dirichlet u(x=10, t) = 10

  float list_t[5] = {1,2,3,4,20};

  float list_x[5] = {-8,-4,0,4,8};



  save_instant_T(Un1,dt,dx,200,u0,u100,list_t,5);

  
  save_position_X(Un2,dt,dx,200,u0,u100,list_x,5);



  //system("(cd Script && gnuplot Explicite_Dirichlet_2.p)");
  system("(cd Script && gnuplot Explicite_Dirichlet_3.p)");

  return 0;
}
