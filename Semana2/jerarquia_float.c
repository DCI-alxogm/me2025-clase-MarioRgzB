#include <stdio.h>

int main(){
  float a=3,b=4,c=5,d=7;
  float e;

  printf("e=(a+b)*c/d=%f\n",(a+b)*c/d);
  printf("e=((a+b)*c)/d=%f\n",(a+b)*c/d);
  printf("e=(a+b)*c/d=%f\n",(a+b)*c/d);
  printf("e=a+(b*c)/d=%f\n",(a+b)*c/d);
}