#include <stdio.h>
#include <math.h>

double f(double x) {
    return pow(x,10)-1;
}
double biseccion(double a, double b, double tol, int *its);
double falsa_pos(double a, double b, double tol, int *its);

double biseccion(double a, double b, double tol, int *its) {
    double c, fa, fc;
    *its=0;
    fa=f(a);
    while (*its<1000) {  
        (*its)++;
        c=(a+b)/2.0;
        fc=f(c);
        
        if (fabs(fc)<tol) return c;
        
        if (fa*fc<0) {
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
    while (*its<1000) {  
        (*its)++;
        c=(a*fb-b*fa)/(fb-fa);
        fc=f(c);
        
        if (fabs(fc)<tol) return c;
        
        if (fa*fc<0) {
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
    double a=0.0, b=1.3, tol=1e-6;
    int iter_biseccion, iter_falsa_pos;
    
    printf("f(%f)=%f\n", a, f(a));
    printf("f(%f)=%f\n", b, f(b));
    printf("f(%f)*f(%f)=%f\n", a, b, f(a) * f(b));
    
    double raiz_biseccion = biseccion(a, b, tol, &iter_biseccion);
    double raiz_falsa_pos = falsa_pos(a, b, tol, &iter_falsa_pos);
    
    printf("Metodo de Biseccion:\n");
    printf("Raíz:x=%f\n", raiz_biseccion);
    printf("Iteraciones: %d\n", iter_biseccion);
    printf("f(x)=%e\n", f(raiz_biseccion));
    
    printf("Metodo de Falsa Posicion:\n");
    printf("Raiz: x=%f\n", raiz_falsa_pos);
    printf("Iteraciones:%d\n", iter_falsa_pos);
    printf("f(x)=%e\n", f(raiz_falsa_pos));
    
    return 0;
}