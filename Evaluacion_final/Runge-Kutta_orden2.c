#include <stdio.h>
#include <math.h>

// Ecuación logística: dC/dt = k * C * (Cmax - C)
double f(double t, double C, double k, double Cmax) {
    return k * C * (Cmax - C);
}

int main() {
    double t0, C0, t_final, h;
    double k, Cmax;
    int n, i;
    
    // Parámetros dados en el problema
    t0 = 0.0;           // tiempo inicial
    C0 = 0.02;          // concentración inicial
    k = 0.45;           // constante cinética
    Cmax = 1.0;         // concentración máxima
    t_final = 25.0;     // tiempo final
    h = 0.1;            // tamaño de paso
    
    // Calcular número de pasos
    n = (int)((t_final - t0) / h);
    
    printf("===========================================\n");
    printf("METODO DE RUNGE-KUTTA DE SEGUNDO ORDEN (RK2)\n");
    printf("===========================================\n");
    printf("Ecuacion: dC/dt = k * C * (Cmax - C)\n");
    printf("Parametros:\n");
    printf("  C(0) = %f mol/L\n", C0);
    printf("  k = %f L/(mol*min)\n", k);
    printf("  Cmax = %f mol/L\n", Cmax);
    printf("  t_final = %f min\n", t_final);
    printf("  h = %f min\n", h);
    printf("  n = %d pasos\n\n", n);
    
    printf("i       t(min)     C(mol/L)   k1         k2\n");
    printf("-------------------------------------------\n");
    
    double t = t0;
    double C = C0;
    
    printf("%d  %10.4f  %10.6f\n", 0, t, C);
    
    for(i = 1; i <= n; i++) {
        double k1, k2;
        
        k1 = f(t, C, k, Cmax);
        k2 = f(t + h/2.0, C + (h * k1)/2.0, k, Cmax);
        
        C = C + h * k2;
        t = t + h;
        
        printf("%d  %10.4f  %10.6f  %10.6f  %10.6f\n", i, t, C, k1, k2);
    }
    
    printf("\n===========================================\n");
    printf("RESULTADO FINAL (RK2):\n");
    printf("C(%f) = %f mol/L\n", t_final, C);
    printf("===========================================\n");
    
    return 0;
}
