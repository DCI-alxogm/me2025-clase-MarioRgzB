#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int leer_datos(double **A, double *B, int *n) {
    char opcion;
    char nombre_archivo[100];
    FILE *archivo;
    
    printf("Solucion de sistemas de ecuaciones\n");
    printf("¿Desea ingresar los datos por (T)erminal o (A)rchivo? ");
    scanf(" %c", &opcion);
    
    if (opcion == 'A' || opcion == 'a') {
        printf("Ingrese el nombre del archivo: ");
        scanf("%s", nombre_archivo);
        
        archivo = fopen(nombre_archivo, "r");
        if (archivo == NULL) {
            printf("Error: No se pudo abrir el archivo.\n");
            return 0;
        }
        
        fscanf(archivo, "%d", n);

        *A = (double**)malloc(*n * sizeof(double*));
        for (int i = 0; i < *n; i++) {
            (*A)[i] = (double*)malloc(*n * sizeof(double));
        }
        *B = (double*)malloc(*n * sizeof(double));

        for (int i = 0; i < *n; i++) {
            for (int j = 0; j < *n; j++) {
                fscanf(archivo, "%lf", &(*A)[i][j]);
            }
        }

        for (int i = 0; i < *n; i++) {
            fscanf(archivo, "%lf", &(*B)[i]);
        }
        
        fclose(archivo);
        printf("Datos cargados correctamente desde el archivo.\n");
        
    } else {
        printf("Ingrese la dimension del sistema (n): ");
        scanf("%d", n);
        *A = (double**)malloc(*n * sizeof(double*));
        for (int i = 0; i < *n; i++) {
            (*A)[i] = (double*)malloc(*n * sizeof(double));
        }
        *B = (double*)malloc(*n * sizeof(double));
        
        printf("Ingrese los elementos de la matriz A (%dx%d):\n", *n, *n);
        for (int i = 0; i < *n; i++) {
            printf("Fila %d: ", i + 1);
            for (int j = 0; j < *n; j++) {
                scanf("%lf", &(*A)[i][j]);
            }
        }
        
        printf("\nIngrese los elementos del vector B:\n");
        for (int i = 0; i < *n; i++) {
            printf("B[%d] = ", i + 1);
            scanf("%lf", &(*B)[i]);
        }
    }
    
    return 1;

void imprimir_sistema(double **A, double *B, int n) {
    printf("Sistema de ecuaciones:\n");
    for (int i = 0; i < n; i++) {
        printf("| ");
        for (int j = 0; j < n; j++) {
            printf("%f ", A[i][j]);
        }
        printf(" | %f |\n", B[i]);
    }
}

void intercambiar_filas(double **A, double *B, int n, int fila1, int fila2) {
    if (fila1 == fila2) return;

    double *temp_fila = A[fila1];
    A[fila1] = A[fila2];
    A[fila2] = temp_fila;

    double temp_elem = B[fila1];
    B[fila1] = B[fila2];
    B[fila2] = temp_elem;
}

int encontrar_pivote(double **A, int n, int columna, int fila_actual) {
    int fila_pivote = fila_actual;
    double max_valor = fabs(A[fila_actual][columna]);
    
    for (int i = fila_actual + 1; i < n; i++) {
        if (fabs(A[i][columna]) > max_valor) {
            max_valor = fabs(A[i][columna]);
            fila_pivote = i;
        }
    }
    
    return fila_pivote;
}
double calcular_determinante(double **A, int n, int *cambios_filas) {
    double det = 1.0;
    
    for (int i = 0; i < n; i++) {
        det *= A[i][i];
    }

    if (*cambios_filas % 2 != 0) {
        det = -det;
    }
    
    return det;
}

int gauss_jordan(double **A, double *B, int n, double *determinante) {
    int cambios_filas = 0;
    
    printf("Metodo GAUSS-JORDAN ===\n");
    
    for (int i = 0; i < n; i++) {
        int fila_pivote = encontrar_pivote(A, n, i, i);
        
        if (fila_pivote != i) {
            intercambiar_filas(A, B, n, i, fila_pivote);
            cambios_filas++;
            printf("Intercambiadas filas %d y %d\n", i + 1, fila_pivote + 1);
        }

        if (fabs(A[i][i]) < 1e-12) {
            printf("Error: Sistema singular detectado (pivote cero).\n");
            *determinante = 0;
            return 0;
        }

        double pivote = A[i][i];
        for (int j = 0; j < n; j++) {
            A[i][j] /= pivote;
        }
        B[i] /= pivote;
        
        printf("Paso %d - Fila %d normalizada:\n", i + 1, i + 1);
        imprimir_sistema(A, B, n);
        
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = A[k][i];
                for (int j = 0; j < n; j++) {
                    A[k][j] -= factor * A[i][j];
                }
                B[k] -= factor * B[i];
            }
        }
        
        printf("Despues de eliminar columna %d:\n", i + 1);
        imprimir_sistema(A, B, n);
    }

    *determinante = calcular_determinante(A, n, &cambios_filas);
    
    return 1;
}

void imprimir_resultados(double *B, int n, double determinante, int exito) {
    printf(" Resultados\n");
    
    if (exito) {
        printf("El sistema tiene solucion unica.\n");
        printf("Determinante: %f\n", determinante);
        
        printf("Solucion del sistema:\n");
        for (int i = 0; i < n; i++) {
            printf("x%d = %f\n", i + 1, B[i]);
        }
    } else {
        printf("El sistema no tiene solucion unica.\n");
        printf("Determinante: %f\n", determinante);
        printf("El problema NO esta bien determinado.\n");
    }
}

int main() {
    double **A = NULL;
    double *B = NULL;
    double determinante;
    int n, exito;
    
    if (!leer_datos(&A, &B, &n)) {
        return 1;
    }
    
    printf("Sistema original \n");
    imprimir_sistema(A, B, n);
    
    exito = gauss_jordan(A, B, n, &determinante);
    
    imprimir_resultados(B, n, determinante, exito);
    
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(B);
    
    printf("Fin\n");
    return 0;
}