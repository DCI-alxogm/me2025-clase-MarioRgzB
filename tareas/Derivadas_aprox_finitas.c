#include <stdio.h>
#include <math.h>

int main() {
    float x0 = 0.0, f0 = 1.2, x1 = 0.5, f1 = 0.925, x2 = 1.0, f2 = 0.2;
    float d_exact = -0.9125, h = x1 - x0;
    float adelante = (f2 - f1) / h, atras = (f1 - f0) / h, centrada = (f2 - f0) / (2 * h);
    float e_abs_adelante = fabs(adelante - d_exact);
    float e_abs_atras = fabs(atras - d_exact);
    float e_abs_centrada = fabs(centrada - d_exact);
    float e_rel_adelante = (e_abs_adelante / fabs(d_exact)) * 100;
    float e_rel_atras = (e_abs_atras / fabs(d_exact)) * 100;
    float e_rel_centrada = (e_abs_centrada / fabs(d_exact)) * 100;
    
    // Mostrar resultados
    printf("Calculo de derivada en x = 0.5\n");
    printf("f(0.0) = %f\n", f0);
    printf("f(0.5) = %f\n", f1);
    printf("f(1.0) = %f\n\n", f2);
    printf("Aproximaciones de la derivada hacia adelante: f'(0.5) ≈ (f(1.0)-f(0.5))/0.5 = %f\n", adelante);
    printf("Aproximaciones de la derivada hacia atras: f'(0.5) ≈ (f(0.5)-f(0.0))/0.5 = %f\n", atras);
    printf("Aproximaciones de la derivada centrada: f'(0.5) ≈ (f(1.0)-f(0.0))/1.0 = %f\n\n", centrada);
    printf("Valor exacto: f'(0.5) = %f\n\n", d_exact);
    printf("Error absoluto hacia adelante: %f\n", e_abs_adelante);
    printf("Error absoluto hacia atras: %f\n", e_abs_atras);
    printf("Error absoluto centrada: %f\n\n", e_abs_centrada);
    printf("Error relativo hacia adelante: %f\n", e_rel_adelante);
    printf("Error relativo hacia atras: %f\n", e_rel_atras);
    printf("Error relativo centrado:%f\n", e_rel_centrada);
}