#include <stdio.h>
#include <math.h>

#define N 3 

void mostrarMatriz(double matriz[N][N+1]) {
    printf("\nMatriz aumentada:\n");
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N+1; j++) {
            if(j == N) {
                printf(" | %f", matriz[i][j]);
            } else {
                printf("%f ", matriz[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void cambiarFilas(double matriz[N][N+1], int fila1, int fila2) {
    for(int j = 0; j <= N; j++) {
        double temp = matriz[fila1][j];
        matriz[fila1][j] = matriz[fila2][j];
        matriz[fila2][j] = temp;
    }
}

int main() {
    double matriz[N][N+1] = {
        {0, 2, 3, 8},     
        {4, 6, 7, -3},     
        {2, 1, 6, 5}       
    };
    
    double solucion[N];  
    
    printf("1) 2x_2 + 3x_3 = 8\n");
    printf("2) 4x_1 + 6x_2 + 7x_3 = -3\n");
    printf("3) 2x_1 + x_2 + 6x_3 = 5\n");
    
    mostrarMatriz(matriz);

    for(int i = 0; i < N; i++) {
        
        int filaMax = i;
        double maxValor = fabs(matriz[i][i]);
        
        for(int k = i+1; k < N; k++) {
            if(fabs(matriz[k][i]) > maxValor) {
                maxValor = fabs(matriz[k][i]);
                filaMax = k;
            }
        }

        if(filaMax != i) {
            printf("Intercambiando fila %d con fila %d\n", i+1, filaMax+1);
            cambiarFilas(matriz, i, filaMax);
            mostrarMatriz(matriz);
        }

        for(int k = i+1; k < N; k++) {
            double factor = matriz[k][i] / matriz[i][i];
            printf("Volver cero elemento (%d,%d) usando factor: %f\n", k+1, i+1, factor);
            
            for(int j = i; j <= N; j++) {
                matriz[k][j] -= factor * matriz[i][j];
            }
        }
        
        mostrarMatriz(matriz);
    }
    
    for(int i = N-1; i >= 0; i--) {
        solucion[i] = matriz[i][N];  
        
        for(int j = i+1; j < N; j++) {
            solucion[i] -= matriz[i][j] * solucion[j];
        }
        
        solucion[i] = solucion[i] / matriz[i][i];
    }
    

    printf("Solucion\n");
    for(int i = 0; i < N; i++) {
        printf("x_%d = %.6f\n", i+1, solucion[i]);
    }
    
    return 0;
}