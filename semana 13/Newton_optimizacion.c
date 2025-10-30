#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double funcion(double x) {
    return x*x*x - 3*x*x + 2*x;
    
}
double derivada(double x) {
    return 3*x*x - 6*x + 2;
    
}

double segunda_derivada(double x) {
    return 6*x - 6;

}

double newton_optimizacion(double x0, double tol, int max_iter, int *tipo_punto, int *iteraciones) {
    double x = x0;
    double f_prima, f_segunda;
    int iter = 0;

    
    while (iter < max_iter) {
        f_prima = derivada(x);
        f_segunda = segunda_derivada(x);

        if (fabs(f_prima) < tol) {
            if (f_segunda > tol) {
                *tipo_punto = 1; 
            } else if (f_segunda < -tol) {
                *tipo_punto = 2; 
            } else {
                *tipo_punto = 3; 
            }
            
            printf("%d\t%f\t%f\t%f\t%f\t", 
                   iter, x, f_prima, f_segunda, funcion(x));
            
            if (*tipo_punto == 1) printf("minimo\n");
            else if (*tipo_punto == 2) printf("maximo\n");
            else printf("indeterminado\n");
            
            *iteraciones = iter;
            return x;
        }
        if (fabs(f_segunda) < 1e-15) {
            printf("Error");
            *tipo_punto = 0; 
            *iteraciones = iter;
            return x;
        }
        double x_nuevo = x - f_prima / f_segunda;
        
        printf("%d\t%f\t%f\t%f\t%f\t", 
               iter, x, f_prima, f_segunda, funcion(x));
 
        if (f_segunda > 0) {
            printf("Convexo\n");
        } else {
            printf("Cóncavo\n");
        }
 
        if (fabs(x_nuevo - x) < tol) {
            x = x_nuevo
