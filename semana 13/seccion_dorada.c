#include <stdio.h>
#include <math.h>

double funcion(double x) {
    return (x - 2.0) * (x - 2.0);
}

double seccion_dorada(double a, double b, double tol, int max_iter) {
    const double R = 0.618033988749895; 
    
    double x1, x2;
    double f1, f2;
    int iter = 0;
    
    printf("Iter\t  a\t\t  x1\t\t  x2\t\t  b\t\t  f(x1)\t\t  f(x2)\n");
   
    while (fabs(b - a) > tol && iter < max_iter) {

        x1 = b - R * (b - a);
        x2 = a + R * (b - a);

        f1 = funcion(x1);
        f2 = funcion(x2);
        
        printf("%3d\t%8.6f\t%8.6f\t%8.6f\t%8.6f\t%8.6f\t%8.6f\n", 
               iter, a, x1, x2, b, f1, f2);

        if (f1 < f2) {
            b = x2;  // El mínimo está en [a, x2]
        } else {
            a = x1;  // El mínimo está en [x1, b]
        }
        
        iter++;
    }
    double minimo = (a + b) / 2.0;
    
    printf("Resultado final:\n");
    printf("Mínimo encontrado en x = %f\n", minimo);
    printf("Valor de la función: f(x) = %f\n", funcion(minimo));
    printf("Número de iteraciones: %d\n", iter);
    printf("Error: %f\n", fabs(b - a));
    
    return minimo;
}

double seccion_dorada_simple(double a, double b, double tol, int max_iter) {
    const double R = 0.618033988749895;
    
    double x1, x2;
    double f1, f2;
    int iter = 0;
    
    while (fabs(b - a) > tol && iter < max_iter) {
        x1 = b - R * (b - a);
        x2 = a + R * (b - a);
        
        f1 = funcion(x1);
        f2 = funcion(x2);
        
        if (f1 < f2) {
            b = x2;
        } else {
            a = x1;
        }
        
        iter++;
    }
    
    return (a + b) / 2.0;
}

int main() {
    double a, b, tolerancia;
    int max_iteraciones;

    printf("Ingrese el límite inferior del intervalo (a): ");
    scanf("%lf", &a);
    
    printf("Ingrese el límite superior del intervalo (b): ");
    scanf("%lf", &b);
    
    printf("Ingrese la tolerancia: ");
    scanf("%lf", &tolerancia);
    
    printf("Ingrese el máximo número de iteraciones: ");
    scanf("%d", &max_iteraciones);
    
    printf("Tolerancia: %e\n", tolerancia);
    printf("Máximo de iteraciones: %d\n", max_iteraciones);
 
    double resultado = seccion_dorada(a, b, tolerancia, max_iteraciones);

    printf("Puntos alrededor del mínimo:\n");
    for (double x = resultado - 0.1; x <= resultado + 0.1; x += 0.05) {
        printf("f(%f) = %f\n", x, funcion(x));
    }
    
    return 0;
}
