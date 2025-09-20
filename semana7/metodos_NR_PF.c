#include <stdio.h>
#include <math.h>

double f(double x) {
    return exp(-x) - x;
}

double df(double x) {
    return -exp(-x) - 1;
}

double g(double x) {
    return exp(-x);
}

void p_f(double x0, double E_max) {
    printf("METODO DE PUNTO FIJO \n");
    printf("Funcion de iteracion: g(x) = e^(-x)\n\n");
    
    double x_act = x0;
    double x_ant;
    double error;
    int iter = 0;
    
    printf("Iteracion %d: x = %.8lf, f(x) = %e\n", iter, x_act, f(x_act));
    
    do {
        iter++;
        x_ant = x_act;
        x_act = g(x_ant);
        error = fabs((x_act - x_ant) / x_act) * 100;
        
        printf("Iteracion %d: x = %lf, Error = %lf%%, f(x) = %e\n", 
               iter, x_act, error, f(x_act));
               
    } while (error > E_max && iter < 100);
    
    printf("RESULTADO FINAL - PUNTO FIJO:\n");
    printf("Raiz aproximada: x = %lf\n", x_act);
    printf("Error final: %lf%%\n", error);
    printf("f(x) = %e\n", f(x_act));
    printf("Iteraciones totales: %d\n\n", iter);
}

void n_r(double x0, double E_max) {
    printf("METODO DE NEWTON-RAPHSON \n");
    printf("f'(x) = -e^(-x) - 1\n");
    
    double x_act = x0;
    double x_ant;
    double error;
    int iter = 0;
    
    printf("Iteracion %d: x = %lf, f(x) = %e, f'(x) = %e\n", 
           iter, x_act, f(x_act), df(x_act));
    
    do {
        iter++;
        x_ant = x_act;
        
        x_act = x_ant - f(x_ant) / df(x_ant);
        error = fabs((x_act - x_ant) / x_act) * 100;
        
        printf("Iteracion %d: x = %lf, Error = %lf%%, f(x) = %e, f'(x) = %e\n", 
               iter, x_act, error, f(x_act), df(x_act));
               
    } while (error > E_max && iter < 100);
    
    printf("RESULTADO FINAL - NEWTON-RAPHSON:\n");
    printf("Raiz aproximada: x = %.8lf\n", x_act);
    printf("Error final: %lf%%\n", error);
    printf("f(x) = %e\n", f(x_act));
    printf("Iteraciones totales: %d\n\n", iter);
}

int main() {
    double x0 = 0.0;       
    double E_max = 0.0001; 
    
    printf("ENCONTRANDO LA RAIZ DE f(x) = e^(-x) - x\n");
    printf("Punto inicial x0 = %lf\n", x0);
    printf("Error maximo permitido: %lf%%\n\n", E_max);

    p_f(x0, E_max);
    n_r(x0, E_max);

    
    return 0;
}