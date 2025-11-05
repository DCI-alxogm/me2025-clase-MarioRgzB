#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_ITER 1000
#define TOL 1e-6

double funcion(double x, double y) {
    return 2*x*y + 2*x - x*x - 2*y*y;
}

void gradiente(double x, double y, double *g_x, double *g_y) {
    *g_x = 2*y + 2 - 2*x;  
    *g_y = 2*x - 4*y;  
}

double buscar_paso(double x, double y, double dx, double dy, double alpha) {
    double f_act = funcion(x, y);
    double f_n;
    
    for(int i = 0; i < 20; i++) {
        f_n = funcion(x - alpha*dx, y - alpha*dy);
        if(f_n < f_act) {
            break;
        }
        alpha *= 0.5;  
    }
    return alpha;
}

int main() {
    double x = -1.0, y = 1.0;  
    double g_x, g_y;
    double n_g;
    double paso;
    int it;

    printf("Punto inicial: (%f, %f)\n", x, y);
    printf("Iter  |     x     |     y     |    f(x,y)   |   ||gradf||   \n");
    printf("------|-----------|-----------|-------------|------------\n");
    
    for(it = 0; it < MAX_ITER; it++) {
      
        gradiente(x, y, &g_x, &g_y);
        n_g = sqrt(g_x*g_x + g_y*g_y);
        
        printf("%d | %f | %f | %f | %f\n", 
               it, x, y, funcion(x, y), n_g);
        
        if(n_g < TOL) {
            printf("Convergencia alcanzada\n");
            break;
        }
        paso = buscar_paso(x, y, g_x, g_y, 1.0);

        x = x - paso * g_x;
        y = y - paso * g_y;
    }
    
    if(it == MAX_ITER) {
        printf("\nMáximo número de iteraciones alcanzado\n");
    }
    
    printf("Resultado final:\n");
    printf("Punto encontrado en: (%f, %f)\n", x, y);
    printf("Valor de la función: %f\n", funcion(x, y));
    printf("Norma del gradiente: %f\n", n_g);
    printf("Iteraciones totales: %d\n", it);
    
    printf("Verificación analítica (solución exacta):\n");
    double x_ex = 2.0;
    double y_ex = 1.0;
    printf("Solución exacta: (%f, %f)\n", x_ex, y_ex);
    printf("Valor exacto de f: %f\n", funcion(x_ex, y_ex));
    
    return 0;
}