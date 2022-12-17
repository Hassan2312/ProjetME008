#include <stdio.h>
#include <stdlib.h>
#include "utils/utils.h"

#define n 101


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

void init_A(float h, float a[n], float c[n], float d[n], int cond) {
  for (int i = 0; i < n; i++) {
    a[i] = h;
    c[i] = h;
    d[i] = 1 - 2 * h;
  }
  switch(cond) {
    case 1:
      c[0] = 2*h;
      a[n-1] = 2*h;
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
      a[n-1] = 2*h;
      break;
    }
}

void init_un(float un[n]) {
  int mid = (int)(n / 2);
  for (int i = 0; i < n; i++) {
    if (i < mid)
      un[i] = 1;
    else
      un[i] = 10;
  }
  un[mid] = 5.5;
}

void update_un(float a[n], float c[n], float d[n], float un[n]) {
  float un1[n];
  un1[0] = d[0] * un[0] + c[0] * un[1];
  un1[n - 1] = d[n - 1] * un[n - 1] + a[n - 1] * un[n - 2];
  for (int i = 1; i < n - 1; i++)
    un1[i] = a[i] * un[i - 1] + d[i] * un[i] + c[i] * un[i + 1];
  CopyTab(un, un1);
}

void un_instant_t(float unt[n], float instant, float dt, float dx, int cond) {
  float a[n], c[n], d[n];
  float h = dt / (dx * dx);
  init_un(unt);
  init_A(h, a, c, d, cond);
  for (int i = 0; i * dt < instant; i++) {
    update_un(a, c, d, unt);
  }
}


void save_position_x(float dt, float dx, float tmax, float list_x[], int length, int cond){
  float unt[n];
  float a[n], c[n], d[n];
  float h = dt / (dx * dx);
  int position;
  
  init_A(h, a, c, d, cond);
  init_un(unt);

  FILE* out = fopen("output/Explicite_Dirichlet_3.dat","wt");
  
  for(int i = 0; i < tmax/dt; i++) {
	  fprintf( out, "%f\t", i*dt);           //Impression du temps au debut de la ligne 
	  for(int j = 0; j < length; j++) {              //Parcours de la liste de positions
		  position = (int)((list_x[j] + 10)/dx);
	      fprintf( out, "%f\t", unt[position]);
	  }
	  fprintf( out, "\n");
	  update_un(a, c, d, unt);
  }

  fclose(out);

}


void save_instant_T(float dt, float dx, float list_t[], int length, int cond){
  float Unt[n];
  float a[n], c[n], d[n];
  float h = dt / (dx * dx);
  
  init_A(h, a, c, d, cond);
  init_un(Unt);

  FILE* out = fopen("output/Explicite_Dirichlet_2.dat","wt");

  //Parcours de la liste de temps
  int currentTimeIndex = 0;
  
  for (int i = 0; (i * dt) <= list_t[length-1]; i++) {
    if (i*dt>=list_t[currentTimeIndex])
    { 
      fprintVect(out,Unt,n,i*dt, dx);
      currentTimeIndex++;
    }
    
    update_un(a, c, d, Unt);
  }

  fclose(out);

}

int main(void) {

  float dt, dx;
  
  dt=0.001;
  dx=0.2;
  
  int cond;
  
  printf("Bonjour!\nChoisissez les conditions aux limites:\n\n\t1. Neumann-Neumann\t\t2. Dirichlet-Dirichlet\t\t3. Dirichlet-Neumann\n\nSaisir un numéro =>");
  scanf("%d", &cond);
  
  float list_t[5] = {1,2,3,4,200};

  float list_x[5] = {-8,-4,0,4,8};



  save_instant_T(dt, dx, list_t, 5, cond);
  save_position_x(dt, dx, 200, list_x, 5, cond);

  


  system("(cd Script && gnuplot Explicite_Dirichlet_2_q9.p)");
  system("(cd Script && gnuplot Explicite_Dirichlet_3_q9.p)");

  return 0;
}
