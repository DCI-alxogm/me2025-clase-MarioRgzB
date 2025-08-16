#include<stdio.h>
#include<math.h>
int main(){
  float a,b,c,disc,x1,x2,xr,xi;
  printf("Introduzca el valor de a");
  scanf("%f",&a);
  printf("Introduzca el valor de b");
  scanf("%f",&b);
  printf("Introduzca el valor de c");
  scanf("%f",&c);
  disc=pow(b,2)-4*a*c;
  if(disc==0){
    printf("\n Existe solo una raíz la cual es:");
    x1=-b/(2*a);
    printf("%f",x1);
  }else{
    if(disc>0){
      printf("La ecuacion posee 2 raices reales \n");
      x1=(-b+sqrt(disc))/(2*a);
      x2=(-b-sqrt(disc))/(2*a);
      printf(" %f",x1);
      printf(" %f",x2);
    }else{
      printf("posee raices complejas");
      xr=(-b)/(2*a);
      xi=(sqrt(-disc))/(2*a);
      printf("x1: %f + %f i",xr,xi);
      printf("\n x2: %f - %f i",xr,xi);
    }
    if(a==0){
      printf("la solucion es trivial");
    }
  }
  }
