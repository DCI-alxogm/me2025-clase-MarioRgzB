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
    int n_pasos, i;

    t = 0.0;           
    t_final = 5.0;     
    h = 0.1;           
    n_pasos = (int)((t_final - t) / h);
    
    double y1 = 0.5;   
    double y2 = 0.0;   

    printf("Ecuacion: 2*d^2x/dt^2 + dx/dt + 8x = 2*cos(3t)\n");
    printf("Sistema transformado:\n");
    printf("  dy1/dt = y2\n");
    printf("  dy2/dt = cos(3t) - 0.5*y2 - 4*y1\n");
    printf("Condiciones iniciales:\n");
    printf("  y1(0) = %f m, y2(0) = %f m/s\n", y1, y2);
    printf("Parametros de integracion:\n");
    printf("  t0 = %f s, tf = %f s, h = %f s\n", t, t_final, h);
    printf("  Numero de pasos: %d\n", n_pasos);
    
    printf("Resultados:\n");
    printf("Paso h = %f\n", h);
    printf("   i      t (s)    y1 (pos)    y2 (vel)    k11        k12        k21        k22\n");
    printf("----------------------------------------------------------------------------------\n");
    
    // Mostrar condición inicial
    printf("%4d  %8.1f  %10.6f  %10.6f    ---        ---        ---        ---\n", 
           0, t, y1, y2);

    for(i = 1; i <= n_pasos; i++) {
        double k11, k12, k21, k22;

        k11 = h * f1(t, y1, y2);
        k12 = h * f2(t, y1, y2);
        
        k21 = h * f1(t + h, y1 + k11, y2 + k12);
        k22 = h * f2(t + h, y1 + k11, y2 + k12);

        printf("%d  %f  %f  %f  %f  %f  %f  %f\n", i, t + h, y1, y2, k11, k12, k21, k22);

        y1 = y1 + 0.5 * (k11 + k21);
        y2 = y2 + 0.5 * (k12 + k22);
        t = t + h;

        printf("%d  %f  %f  %f\n", i, t, y1, y2);

    }
    
    printf("En t = %f segundos:\n", t_final);
    printf("  Posicion (y1) = %f m\n", y1);
    printf("  Velocidad (y2) = %f m/s\n", y2);
    
    return 0;
}
