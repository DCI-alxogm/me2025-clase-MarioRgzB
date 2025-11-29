#include <stdio.h>
#include <math.h>

double funcion(double x, double y) {
    /* Esta es la función f(x,y) de la EDO dy/dx = f(x,y) */
    return x - y;  /* Ejemplo: dy/dx = x - y */
}

int main() {
    double x0, y0, x_final, h;
    int n, i;
    
    printf("===============================================\n");
    printf("    RESOLUCION DE EDO POR METODO DE EULER\n");
    printf("===============================================\n\n");
    
    /* Parámetros iniciales */
    printf("Punto inicial x0: ");
    scanf("%lf", &x0);
    
    printf("Valor inicial y(%.2f): ", x0);
    scanf("%lf", &y0);
    
    printf("Punto final x: ");
    scanf("%lf", &x_final);
    
    printf("Numero de pasos: ");
    scanf("%d", &n);
    
    /* Calculo del tamaño de paso */
    h = (x_final - x0) / n;
    
    printf("\n--- RESULTADOS ---\n");
    printf("Paso h = %.6f\n", h);
    printf("\n   i      x        y\n");
    printf("----------------------------\n");
    
    /* Variables para el método */
    double x = x0;
    double y = y0;
    
    /* Encabezado de la tabla */
    printf("%4d  %7.4f  %7.4f\n", 0, x, y);
    
    /* Iteración del método de Euler */
    for(i = 1; i <= n; i++) {
        /* Fórmula de Euler: y_{i+1} = y_i + h*f(x_i, y_i) */
        double pendiente = funcion(x, y);
        y = y + h * pendiente;
        x = x + h;
        
        /* Mostrar resultados */
        printf("%4d  %7.4f  %7.4f\n", i, x, y);
    }
    
    printf("\nSolucion aproximada en x = %.4f: y = %.6f\n", x_final, y);
    
    /* Para comparar con solución exacta (solo para este ejemplo específico) */
    /* La solución exacta de dy/dx = x - y, y(0)=1 es y = x - 1 + 2e^(-x) */
    if(x0 == 0.0 && fabs(funcion(x,y) - (x - y)) < 1e-10) {
        double y_exacta = x_final - 1 + 2*exp(-x_final);
        printf("Solucion exacta en x = %.4f: y = %.6f\n", x_final, y_exacta);
        printf("Error: %.6f\n", fabs(y - y_exacta));
    }
    
    return 0;
}
