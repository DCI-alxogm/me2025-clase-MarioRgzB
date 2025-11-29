#include <stdio.h>
#include <math.h>

double f(double x, double y) {
    return x - y;  
}

int main() {
    double x0, y0, x_final, h;
    int n, i;
    
    printf("Punto inicial x0: ");
    scanf("%lf", &x0);
    
    printf("Valor inicial y(%f): ", x0);
    scanf("%lf", &y0);
    
    printf("Punto final x: ");
    scanf("%lf", &x_final);
    
    printf("Numero de pasos: ");
    scanf("%d", &n);
    
    h = (x_final - x0) / n;
    
    printf("x0 = %f\n", x0);
    printf("y0 = %f\n", y0);
    printf("xf = %f\n", x_final);
    printf("h  = %f\n", h);
    printf("n  = %d\n", n);
    
    double x = x0;
    double y = y0;
    
    printf("%d  %f  %f \n", 0, x, y);
    
    for(i = 1; i <= n; i++) {
        double k1, k2;
        
        k1 = f(x, y);
        k2 = f(x + h/2.0, y + (h * k1)/2.0);
        
        y = y + h * k2;
        x = x + h;
        
        printf("%d  %f  %f  %f  %f\n", i, x, y, k1, k2);
    }
    
    printf("Resultado: y(%f) = %f\n", x_final, y);
    
    return 0;
}
