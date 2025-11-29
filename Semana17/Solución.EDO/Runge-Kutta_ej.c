#include <stdio.h>
#include <math.h>

double f1(double t, double y1, double y2) {
    return y2; 
}

double f2(double t, double y1, double y2) {
    return cos(3*t) - 0.5*y2 - 4*y1;  
}

int main() {
    double t, t_final, h;
    int n, i;
    
    printf("Ingrese el tiempo inicial t0: ");
    scanf("%lf", &t);
    
    printf("Ingrese la posicion inicial y1(%f): ", t);
    double y1;
    scanf("%lf", &y1);
    
    printf("Ingrese la velocidad inicial y2(%f): ", t);
    double y2;
    scanf("%lf", &y2);
    
    printf("Ingrese el tiempo final t: ");
    scanf("%lf", &t_final);
    
    printf("Ingrese el numero de pasos: ");
    scanf("%d", &n);
    
    h = (t_final - t) / n;
    
    printf("t0 = %f\n", t);
    printf("y10 = %f\n", y1);
    printf("y20 = %f\n", y2);
    printf("tf = %f\n", t_final);
    printf("h  = %f\n", h);
    printf("n  = %d\n", n);
    
    printf("i       t          y1         y2         k11        k12        k21        k22        k31        k32        k41        k42\n");
    
    double t_actual = t;
    
    printf("%d  %f  %f  %f\n", 0, t_actual, y1, y2);
    
    for(i = 1; i <= n; i++) {
        double k11, k12, k21, k22, k31, k32, k41, k42;

        k11 = f1(t_actual, y1, y2);
        k12 = f2(t_actual, y1, y2);

        k21 = f1(t_actual + h/2.0, y1 + (h * k11)/2.0, y2 + (h * k12)/2.0);
        k22 = f2(t_actual + h/2.0, y1 + (h * k11)/2.0, y2 + (h * k12)/2.0);

        k31 = f1(t_actual + h/2.0, y1 + (h * k21)/2.0, y2 + (h * k22)/2.0);
        k32 = f2(t_actual + h/2.0, y1 + (h * k21)/2.0, y2 + (h * k22)/2.0);
        
        k41 = f1(t_actual + h, y1 + h * k31, y2 + h * k32);
        k42 = f2(t_actual + h, y1 + h * k31, y2 + h * k32);

        y1 = y1 + (h/6.0) * (k11 + 2*k21 + 2*k31 + k41);
        y2 = y2 + (h/6.0) * (k12 + 2*k22 + 2*k32 + k42);
        t_actual = t_actual + h;

        printf("%d  %f  %f  %f  %f  %f  %f  %f  %f  %f  %f  %f\n", i, t_actual, y1, y2, k11, k12, k21, k22, k31, k32, k41, k42);
    }
    
    printf("Resultado final: y1(%f) = %f, y2(%f) = %f\n", t_final, y1, t_final, y2);
    
    return 0;
}
