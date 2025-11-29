#include <stdio.h>
#include <math.h>

double f(double x, double y) {
    return x - y;  
}

int main() {
    double x0, y0, x_final, h;
    int n, i;
    
    printf("Ingrese el punto inicial x0: ");
    scanf("%lf", &x0);
    
    printf("Ingrese el valor inicial y(%f): ", x0);
    scanf("%lf", &y0);
    
    printf("Ingrese el punto final x: ");
    scanf("%lf", &x_final);
    
    printf("Ingrese el numero de pasos: ");
    scanf("%d", &n);
    
    h = (x_final - x0) / n;
    
    printf("x0 = %f\n", x0);
    printf("y0 = %f\n", y0);
    printf("xf = %f\n", x_final);
    printf("h  = %f\n", h);
    printf("n  = %d\n", n);
    
    printf("i       x          y          k1         k2         k3         k4\n");
    
    double x = x0;
    double y = y0;
    
    printf("%d  %f  %f \n", 0, x, y);
    
    for(i = 1; i <= n; i++) {
        double k1, k2, k3, k4;
        
        k1 = f(x, y);
        k2 = f(x + h/2.0, y + (h * k1)/2.0);
        k3 = f(x + h/2.0, y + (h * k2)/2.0);
        k4 = f(x + h, y + h * k3);
        
        y = y + (h/6.0) * (k1 + 2*k2 + 2*k3 + k4);
        x = x + h;

        printf("%d  %f  %f  %f  %f  %f  %f\n", i, x, y, k1, k2, k3, k4);
    }
    
    printf("Resultado: y(%f) = %f\n", x_final, y);
    
    return 0;
}
