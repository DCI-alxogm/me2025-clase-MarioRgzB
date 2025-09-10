#include <stdio.h>
#include <math.h>

float f(float x);

int main(){
  float Err_max=0.0001;
  float a=3,b=5,k,fk,Eapr,Err,kold=INFINITY;
  printf("raiz \t f(k) \t Eaprox \t E_r \n");
  do{
    k=(a+b)/2;
    fk=f(k);
    if (fk*f(a)<0){
      b=k;
    }else{
      a=k;
    }
    Eapr=k-kold;
    Err=fabsf(Eapr/k);
    kold=k;
    printf("%f \t %f \t %f \t %f \n",k,fk,Eapr,Err);
    }while(Err>Err_max);

}
float f(float c){
  return sen(10*x)-cos(3*x;);
}