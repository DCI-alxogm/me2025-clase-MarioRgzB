#include <stdio.h>

int main(){
  int a=3,b=4,c=5,d=7;
  int e;

  printf("e=(a+b)*c/d=%d\n",(a+b)*c/d);
  printf("e=((a+b)*c)/d=%d\n",(a+b)*c/d);
  printf("e=(a+b)*c/d=%d\n",(a+b)*c/d);
  printf("e=a+(b*c)/d=%d\n",(a+b)*c/d);
}