#include <stdio.h>
#include <math.h>

double f_sen(double x) { return sin(x); }
double f_cos(double x) { return cos(x); }
double f_exp(double x) { return exp(x); }
double f_log(double x) { return log(1 + x); }
double f_atan(double x) { return atan(x); }

double df_sen(double x, int orden) {
    int ciclo = orden % 4;
    if (ciclo == 0) return sin(x);
    if (ciclo == 1) return cos(x);
    if (ciclo == 2) return -sin(x);
    return -cos(x);
}

double df_cos(double x, int orden) {
    int ciclo = orden % 4;
    if (ciclo == 0) return cos(x);
    if (ciclo == 1) return -sin(x);
    if (ciclo == 2) return -cos(x);
    return sin(x);
}

double df_exp(double x, int orden) { return exp(x); }

double df_log(double x, int orden) {
    if (orden == 0) return log(1 + x);
    double signo = (orden % 2 == 1) ? 1.0 : -1.0;
    double fact = 1.0;
    for (int i = 1; i < orden; i++) fact *= i;
    return signo * fact / pow(1 + x, orden);
}

double df_atan(double x, int orden) {
    if (orden == 0) return atan(x);
    if (orden == 1) return 1 / (1 + x*x);
    if (orden == 2) return -2*x / ((1 + x*x) * (1 + x*x));
    if (orden == 3) return (6*x*x - 2) / pow(1 + x*x, 3);
    return (-24*x*x*x + 24*x) / pow(1 + x*x, 4);
}

int main() {
    double x0, x, xi, h, valor_real, aprox, error, residuo;
    int opcion, orden_max, orden, n;
    
    printf("APROXIMACIONES DE TAYLOR\n");
    printf("========================\n\n");
    
    printf("Funciones disponibles:\n");
    printf("1) sen(x)\n");
    printf("2) cos(x)\n");
    printf("3) exp(x)\n");
    printf("4) ln(1+x)\n");
    printf("5) arctan(x)\n");
    printf("Seleccione opcion: ");
    scanf("%d", &opcion);
    
    printf("\nIngrese punto de expansion (x0): ");
    scanf("%lf", &x0);
    printf("Ingrese punto a evaluar (x): ");
    scanf("%lf", &x);
    printf("Ingrese xi para residuo: ");
    scanf("%lf", &xi);
    printf("Ingrese orden maximo: ");
    scanf("%d", &orden_max);
    
    h = x - x0;

    switch(opcion) {
        case 1: valor_real = f_sen(x); break;
        case 2: valor_real = f_cos(x); break;
        case 3: valor_real = f_exp(x); break;
        case 4: valor_real = f_log(x); break;
        case 5: valor_real = f_atan(x); break;
        default: 
            printf("Opcion invalida\n");
            return 1;
    }
    
    printf("\nRESULTADOS:\n");
    printf("f(%.4f) = %.8f\n", x, valor_real);
    printf("x0 = %.4f, h = %.4f, xi = %.4f\n\n", x0, h, xi);
    printf("Orden  Aproximacion    Error Real     Residuo\n");
    printf("-----  ------------    ----------     -------\n");
    
    for (orden = 0; orden <= orden_max; orden++) {
        aprox = 0.0;
        double termino, fact = 1.0, pot_h = 1.0;
        
        for (n = 0; n <= orden; n++) {
            
            switch(opcion) {
                case 1: termino = df_sen(x0, n); break;
                case 2: termino = df_cos(x0, n); break;
                case 3: termino = df_exp(x0, n); break;
                case 4: termino = df_log(x0, n); break;
                case 5: termino = df_atan(x0, n); break;
            }
            
            aprox += termino * pot_h / fact;
            
            
            if (n < orden) {
                fact *= (n + 1);
                pot_h *= h;
            }
        }
        
        error = valor_real - aprox;
        
        
        if (orden < orden_max) {
            double derivada_sig;
            switch(opcion) {
                case 1: derivada_sig = df_sen(xi, orden+1); break;
                case 2: derivada_sig = df_cos(xi, orden+1); break;
                case 3: derivada_sig = df_exp(xi, orden+1); break;
                case 4: derivada_sig = df_log(xi, orden+1); break;
                case 5: derivada_sig = df_atan(xi, orden+1); break;
            }
            double fact_sig = fact * (orden + 1);
            double pot_h_sig = pot_h * h;
            residuo = derivada_sig * pot_h_sig / fact_sig;
        } else {
            residuo = 0.0;
        }
        
        printf("%3d    %12.8f  %12.8f  %12.8f\n", 
               orden, aprox, error, residuo);
    }
    
    return 0;
}