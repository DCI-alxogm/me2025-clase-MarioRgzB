#include <stdio.h>
#include <math.h>

double f(double c) {
    double g=9.8, m=68.1, t=10.0, v=40.0;
    return (g * m / c) * (1 - exp(-c * t / m)) - v;
}

double biseccion(double a, double b, double tol, int *its);
double falsa_pos(double a, double b, double tol, int *its);

double biseccion(double a, double b, double tol, int *its) {
    double c, fa, fc;
    *its=0;
    
    fa=f(a);
    while (*its < 100) {
        (*its)++;
        c=(a+b)/2.0;
        fc=f(c);
        
        if (fabs(fc) < tol) return c;
        
        if (fa * fc < 0) {
            b=c;
        } else {
            a=c;
            fa=fc;
        }
    }
    return c;
}

double falsa_pos(double a, double b, double tol, int *its) {
    double c, fa, fb, fc;
    *its=0;
    
    fa=f(a);
    fb=f(b);
    while (*its < 100) {
        (*its)++;
        c=(a*fb-b*fa)/(fb-fa);
        fc=f(c);
        
        if (fabs(fc) < tol) return c;
        
        if (fa * fc < 0) {
            b=c;
            fb=fc;
        } else {
            a=c;
            fa=fc;
        }
    }
    return c;
}

int main() {
    double a=10.0, b=20.0, tol=1e-6;
    int iter_biseccion, iter_falsa_pos;
    
    double raiz_biseccion = biseccion(a, b, tol, &iter_biseccion);
    double raiz_falsa_pos = falsa_pos(a, b, tol, &iter_falsa_pos);
    
    printf("Metodo de Bisección:\n");
    printf("Raíz:c=%f\n", raiz_biseccion);
    printf("Iteraciones:%d\n", iter_biseccion);
    printf("f(c)=%e\n", f(raiz_biseccion));
    
    printf("Método de Falsa Posición:\n");
    printf("Raíz:c=%f\n", raiz_falsa_pos);
    printf("Iteraciones:%d\n", iter_falsa_pos);
    printf("f(c)=%e\n", f(raiz_falsa_pos));
    
    return 0;
}