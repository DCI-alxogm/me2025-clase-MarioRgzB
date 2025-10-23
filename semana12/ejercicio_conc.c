#include <stdio.h>
#include <math.h>

#define N 3

void resolver_sistema(double A[N][N], double b[N], double x[N]);
void mostrar_matriz(double A[N][N+1], char* nm);
void verificar_s(double A[N][N], double b[N], double x[N]);

int main() {
    double A[N][N] = {
        {15.0, -3.0, -1.0},
        {-3.0, 18.0, -6.0},
        {-4.0, -1.0, 13.0}
    };
    double b_o[N] = {3800.0, 1200.0, 2350.0};
    double b_mod[N] = {3300.0, 1000.0, 2350.0};
    
    double C_o[N], C_mod[N];
    printf("15C1 - 3C2 - C3 = 3800\n");
    printf("-3C1 + 18C2 - 6C3 = 1200\n");
    printf("-4C1 - C2 + 13C3 = 2350\n\n");
    
    resolver_sistema(A, b_o, C_o);
    
    printf("Concentraciones:\n");
    printf("C1 = %f g/m³\n", C_o[0]);
    printf("C2 = %f g/m³\n", C_o[1]);
    printf("C3 = %f g/m³\n\n", C_o[2]);
    printf("Sistema modificado\n");
    printf("Reduccion: Reactor 1: -500 g/dia, Reactor 2: -200 g/dia\n");
    printf("15C1 - 3C2 - C3 = 3300\n");
    printf("-3C1 + 18C2 - 6C3 = 1000\n");
    printf("-4C1 - C2 + 13C3 = 2350\n");
    
    resolver_sistema(A, b_mod, C_mod);
    
    printf("Nuevas concentraciones:\n");
    printf("C1' = %f g/m³\n", C_mod[0]);
    printf("C2' = %f g/m³\n", C_mod[1]);
    printf("C3' = %f g/m³\n\n", C_mod[2]);
    double red_C3 = C_mod[2] - C_o[2];
    printf("Reduccion en la concentracion del reactor 3:\n");
    printf("C3 original: %f g/m³\n", C_o[2]);
    printf("C3 modificado: %f g/m³\n", C_mod[2]);
    printf("Reduccion: %f g/m³\n\n", red_C3);

    printf("Verificacion \n");
    verificar_solucion(A, b_o, C_o);
    verificar_solucion(A, b_mod, C_mod);
    
    return 0;
}

void resolver_sistema(double A[N][N], double b[N], double x[N]) {
    double matriz[N][N+1];
    int i, j, k;

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            matriz[i][j] = A[i][j];
        }
        matriz[i][N] = b[i];
    }

    for(k = 0; k < N; k++) {
        int fila_max = k;
        double max_val = fabs(matriz[k][k]);
        
        for(i = k+1; i < N; i++) {
            if(fabs(matriz[i][k]) > max_val) {
                max_val = fabs(matriz[i][k]);
                fila_max = i;
            }
        }

        if(fila_max != k) {
            for(j = 0; j <= N; j++) {
                double temp = matriz[k][j];
                matriz[k][j] = matriz[fila_max][j];
                matriz[fila_max][j] = temp;
            }
        }

        for(i = k+1; i < N; i++) {
            double factor = matriz[i][k] / matriz[k][k];
            for(j = k; j <= N; j++) {
                matriz[i][j] -= factor * matriz[k][j];
            }
        }
    }

    for(i = N-1; i >= 0; i--) {
        x[i] = matriz[i][N];
        for(j = i+1; j < N; j++) {
            x[i] -= matriz[i][j] * x[j];
        }
        x[i] /= matriz[i][i];
    }
}

void verificar_solucion(double A[N][N], double b[N], double x[N]) {
    double residuo[N];
    double error_total = 0.0;
    int i, j;
    
    printf("Verificacion para b = [%.1f, %.1f, %.1f]:\n", b[0], b[1], b[2]);
    
    for(i = 0; i < N; i++) {
        residuo[i] = 0.0;
        for(j = 0; j < N; j++) {
            residuo[i] += A[i][j] * x[j];
        }
        double error = fabs(residuo[i] - b[i]);
        error_total += error;
        
        printf("Ecuacion %d: Calculado = %.3f, Esperado = %.1f, Error = %.6f\n",
               i+1, residuo[i], b[i], error);
    }
    
    printf("Error total: %.6f\n", error_total);
}