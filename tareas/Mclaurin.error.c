#include <stdio.h>
#include <math.h>

int main() {
  double x = 0.5;
  double e_lim = 0.01;
  double aprox = 1;
  double termino = 1;
  double e_porcent = 100;
  int i = 0;
  printf("Iteración |  Aproximación  |   Término añadido   | Error %%\n");
    printf("----------|----------------|---------------------|----------\n");
    printf("    %2d    | %14.10f | %19.10f | %8s\n", i, aprox, termino, "N/A");
    
    do {
        i++;
        double aprox_ant = aprox;
        
        termino = termino * x / i;
        aprox += termino;
        if (aprox !=0){
          e_porcent = fabs((aprox - aprox_ant)/aprox)*100;
        } else {
          e_porcent = 100;
        }
        printf("    %2d    | %14.10f | %19.10f | %8.6f%%\n", i, aprox, termino, e_porcent);
        
    } while (e_porcent > e_lim && i < 50);
    
    printf("\n La convergencia se alcanzó a las %d iteraciones\n", i);
    printf("Error total: %.8f%% (límite: %.4f%%)\n", e_porcent, e_lim);
}
