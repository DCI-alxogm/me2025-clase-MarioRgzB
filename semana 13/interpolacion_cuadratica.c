#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double funcion(double x) {
    return (x - 2.0) * (x - 2.0);

}

double interpolacion_cuadratica(double x0, double x1, double x2, double tol, int max_iter) {
    double f0, f1, f2;
    double x_min, f_min;
    double a, b, c, denominador;
    int iter = 0;
    
    do {
        f0 = funcion(x0);
        f1 = funcion(x1);
        f2 = funcion(x2);

        denominador = (x0 - x1) * (x0 - x2) * (x1 - x2);
        
        if (fabs(denominador) < 1e-15) {
            printf("Error\n");
            return (x0 + x1 + x2) / 3.0;
        }
        
        a = ((x2 - x1) * f0 + (x0 - x2) * f1 + (x1 - x0) * f2) / denominador;
        b = ((x1*x1 - x2*x2) * f0 + (x2*x2 - x0*x2) * f1 + (x0*x0 - x1*x1) * f2) / denominador;
        c = ((x1*x2*x2 - x1*x1*x2) * f0 + 
             (x0*x0*x2 - x0*x2*x2) * f1 + 
             (x0*x1*x1 - x0*x0*x1) * f2) / denominador;
        if (a <= 0) {
            printf("Advertencia: El polinomio interpolante no es convexo (a = %f)\n", a);
            if (f0 <= f1 && f0 <= f2) x_min = x0;
            else if (f1 <= f0 && f1 <= f2) x_min = x1;
            else x_min = x2;
        } else {
            x_min = -b / (2.0 * a);
        }
        
        f_min = funcion(x_min);
        
        printf("%d\t%f\t%f\t%f\t%f\t%f\n", 
               iter, x0, x1, x2, x_min, f_min);
        
        // Reordenar los puntos para la siguiente iteración
        // Mantenemos los tres puntos con valores de función más bajos
        double puntos[4][2] = {
            {x0, f0},
            {x1, f1},
            {x2, f2},
            {x_min, f_min}
        };
        
        // Ordenar por valor de función (método de burbuja simple)
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3 - i; j++) {
                if (puntos[j][1] > puntos[j+1][1]) {
                    // Intercambiar puntos
                    double temp_x = puntos[j][0];
                    double temp_f = puntos[j][1];
                    puntos[j][0] = puntos[j+1][0];
                    puntos[j][1] = puntos[j+1][1];
                    puntos[j+1][0] = temp_x;
                    puntos[j+1][1] = temp_f;
                }
            }
        }
        x0 = puntos[0][0];
        x1 = puntos[1][0];
        x2 = puntos[2][0];
        
        iter++;

    } while (iter < max_iter && 
             (fabs(x0 - x1) > tol || fabs(x1 - x2) > tol || fabs(x0 - x2) > tol));

    f0 = funcion(x0);
    f1 = funcion(x1);
    f2 = funcion(x2);
    
    if (f0 <= f1 && f0 <= f2) x_min = x0;
    else if (f1 <= f0 && f1 <= f2) x_min = x1;
    else x_min = x2;
    
    printf("Resultado:\n");
    printf("Mínimo encontrado en x = %f\n", x_min);
    printf("Valor de la función: f(x) = %f\n", funcion(x_min));
    printf("Número de iteraciones: %d\n", iter);
    
    return x_min;
}

// Versión alternativa simplificada
double interpolacion_cuadratica_simple(double x0, double x1, double x2, double tol, int max_iter) {
    double f0, f1, f2;
    double x_min, f_min;
    double a, b, denominador;
    int iter = 0;
    
    while (iter < max_iter) {
        f0 = funcion(x0);
        f1 = funcion(x1);
        f2 = funcion(x2);
        
        denominador = (x0 - x1) * (x0 - x2) * (x1 - x2);
        
        if (fabs(denominador) < 1e-15) break;
        
        a = ((x2 - x1) * f0 + (x0 - x2) * f1 + (x1 - x0) * f2) / denominador;
        b = ((x1*x1 - x2*x2) * f0 + (x2*x2 - x0*x2) * f1 + (x0*x0 - x1*x1) * f2) / denominador;
        
        if (a > 0) {
            x_min = -b / (2.0 * a);
        } else {
            x_min = (x0 + x1 + x2) / 3.0;
        }
        
        f_min = funcion(x_min);
        
        if (f_min < f1) {
            if (x_min < x1) {
                x2 = x1;
                x1 = x_min;
            } else {
                x0 = x1;
                x1 = x_min;
            }
        } else {
            if (x_min < x1) {
                x0 = x_min;
            } else {
                x2 = x_min;
            }
        }

        if (fabs(x0 - x2) < tol) break;
        
        iter++;
    }
    
    return (x0 + x1 + x2) / 3.0;
}

int main() {
    double x0, x1, x2, tolerancia;
    int max_iteraciones;

    printf("Ingrese el primer punto (x0): ");
    scanf("%lf", &x0);
    
    printf("Ingrese el segundo punto (x1): ");
    scanf("%lf", &x1);
    
    printf("Ingrese el tercer punto (x2): ");
    scanf("%lf", &x2);
    
    printf("Ingrese la tolerancia: ");
    scanf("%lf", &tolerancia);
    
    printf("Ingrese el máximo número de iteraciones: ");
    scanf("%d", &max_iteraciones);
    
    printf("\nBuscando el mínimo de f(x) = (x-2)^2\n");
    printf("Puntos iniciales: x0 = %f, x1 = %f, x2 = %f\n", x0, x1, x2);
    printf("Tolerancia: %e\n", tolerancia);
    printf("Máximo de iteraciones: %d\n", max_iteraciones);

    if (fabs(x0 - x1) < 1e-10 || fabs(x1 - x2) < 1e-10 || fabs(x0 - x2) < 1e-10) {
        printf("Error: Los puntos iniciales deben ser distintos\n");
        return 1;
    }

    if (x0 > x1) { double temp = x0; x0 = x1; x1 = temp; }
    if (x0 > x2) { double temp = x0; x0 = x2; x2 = temp; }
    if (x1 > x2) { double temp = x1; x1 = x2; x2 = temp; }
    
    printf("Puntos ordenados: x0 = %f, x1 = %f, x2 = %f\n", x0, x1, x2);

    double resultado = interpolacion_cuadratica(x0, x1, x2, tolerancia, max_iteraciones);

    printf("Punto mínimo: x = %f\n", resultado);
    printf("f(%f) = %f\n", resultado, funcion(resultado));

    printf("Puntos alrededor del mínimo:\n");
    for (double x = resultado - 0.2; x <= resultado + 0.2; x += 0.05) {
        printf("f(%f) = %f\n", x, funcion(x));
    }
    
    return 0;
}
