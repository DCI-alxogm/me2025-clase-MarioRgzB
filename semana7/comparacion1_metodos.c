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

void punto_fijo(double x0, double E_max) {
    printf("METODO DE PUNTO FIJO \n");
    double x_act = x0;
    double x_ant;
    double error;
    int iter = 0;
    
    do {
        iter++;
        x_ant = x_act;
        x_act = g(x_ant);
        error = fabs((x_act - x_ant) / x_act) * 100;
        
        printf("Iteracion %d: x=%lf, Error=%lf\n", 
               iter, x_act, error);
               
    } while (error > E_max && iter < 100);
    
    printf("Raiz aproximada: x = %lf\n", x_act);
    printf("f(x) = %e\n\n", f(x_act));
}

void newton_raphson(double x0, double E_max) {
    printf("METODO DE NEWTON-RAPHSON \n");
    double x_act = x0;
    double x_ant;
    double error;
    int iter = 0;
    
    do {
        iter++;
        x_ant = x_act;
        x_act = x_ant - f(x_ant) / df(x_ant);
        error = fabs((x_act - x_ant) / x_act) * 100;
        
        printf("Iteracion %d: x=%lf, Error=%lf\n", 
               iter, x_act, error);
               
    } while (error > E_max && iter < 100);
    
    printf("Raiz aproximada: x = %lf\n", x_act);
    printf("f(x) = %e\n\n", f(x_act));
}

void newton_raphson_modificado(double x0, double E_max) {
    printf("METODO DE NEWTON-RAPHSON MODIFICADO \n");
    double x_act = x0;
    double x_ant;
    double error;
    int iter = 0;
    double derivada_inicial = df(x0); // Se usa la misma derivada en todas las iteraciones
    
    do {
        iter++;
        x_ant = x_act;
        x_act = x_ant - f(x_ant) / derivada_inicial;
        error = fabs((x_act - x_ant) / x_act) * 100;
        
        printf("Iteracion %d: x=%lf, Error=%lf%%\n", 
               iter, x_act, error);
               
    } while (error > E_max && iter < 100);
    
    printf("Raiz aproximada: x = %lf\n", x_act);
    printf("f(x)=%e\n", f(x_act));
}

void secante(double x0, double x1, double E_max) {
    printf("METODO DE LA SECANTE \n");
    double x_ant = x0;
    double x_act = x1;
    double x_sig;
    double error;
    int iter = 0;
    
    do {
        iter++;
        x_sig = x_act - (f(x_act) * (x_ant - x_act)) / 
                     (f(x_ant) - f(x_act));
        error = fabs((x_sig - x_act) / x_sig) * 100;
        
        printf("Iteracion %d: x=%lf, Error=%lf%%\n", 
               iter, x_sig, error);
        
        x_ant = x_act;
        x_act = x_sig;
               
    } while (error > E_max && iter < 100);
    
    printf("Raiz aproximada: x = %lf\n", x_act);
    printf("f(x) = %e\n\n", f(x_act));
}

int main() {
    double x0 = 0.0;      
    double E_max = 0.000001; 
    
    printf("Encontrando la raiz de f(x) = e^(-x) - x\n");
    printf("Punto inicial x0=%lf\n", x0);
    printf("Error maximo permitido:%lf%%\n", E_max);
    
    punto_fijo(x0, E_max);
    newton_raphson(x0, E_max);
    newton_raphson_modificado(x0, E_max);
    secante(x0, 0.1, E_max); 
    
    return 0;
}