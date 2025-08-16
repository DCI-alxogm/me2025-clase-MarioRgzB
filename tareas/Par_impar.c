#include <stdio.h>
int main(){
  int n;
  char r;
  do{
    printf("Ingrese un numero\n");
    scanf("%d",&n);
    if(n%2==0){
      printf("El numero es par\n");
    }
    else
    {
      printf("El numero es impar\n");
    }
    printf("¿Desea realizar otra operacion?(s/n)\n");
    scanf(" %c",&r);
  }while(r=='s'||r=='S');
}