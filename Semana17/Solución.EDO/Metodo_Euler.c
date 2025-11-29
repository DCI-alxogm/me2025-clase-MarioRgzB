#include <stdio.h>
#include <math.h>

double funcion(double x, double y) {
    return x - y;  
}

int main() {
    double x0, y0, x_final, h;
    int n, i;
    printf("Punto inicial x0: ");
    scanf("%lf", &x0);
    
    printf("Valor inicial y(%f): ", x0);
    scanf("%lf", &y0);
    
    printf("Punto final x: ");
    scanf("%lf", &x_final);
    
    printf("Numero de pasos: ");
    scanf("%d", &n);
    h = (x_final - x0) / n;
    
    printf("resultados obtenidos\n");
    printf("Paso h = %f\n", h);
    printf("   i      x        y\n");
    double x = x0;
    double y = y0;
    
    printf("%d  %f  %f\n", 0, x, y);
    
    for(i = 1; i <= n; i++) {
        double pendiente = funcion(x, y);
        y = y + h * pendiente;
        x = x + h;
        printf("%d  %f  %f\n", i, x, y);
    }
    
    printf("Solucion aproximada en x = %f: y = %f\n", x_final, y);
    
    if(x0 == 0.0 && fabs(funcion(x,y) - (x - y)) < 1e-10) {
        double y_exacta = x_final - 1 + 2*exp(-x_final);
        printf("Solucion exacta en x = %f: y = %f\n", x_final, y_exacta);
        
    }
    
    return 0;
}
